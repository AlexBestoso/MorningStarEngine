#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>

#include <X11/Xlib.h>

#include "./glm/glm/glm.hpp"
#include "./glm/glm/gtc/matrix_transform.hpp"
#include "./glm/glm/gtc/type_ptr.hpp"

#include <dlfcn.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include <iostream>
#include <dirent.h>
#include <fcntl.h>
#include <typeinfo>
using namespace std;

#include "./core/tools/tools.h"

unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 800;

float lastX = 400, lastY = 300;
float pitch, yaw;


#include "./core/structs/structs.h"
#include "./core/peripherals/peripherals.h"
#include "./core/physics/physics.h"
#include "./core/graphics/graphics.h"
#include "./GraphicsEngine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mod);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//#include "./Custom/Custom_TestContext.h"
//#include "./Custom/Custom_MainMenu.h"

int main(void){
	// Calculate aspect ratio to fix glut bug.
	Display* d = XOpenDisplay(NULL);
	Screen*  s = DefaultScreenOfDisplay(d);
	SCR_WIDTH = s->width;
	SCR_HEIGHT = s->height;
	XCloseDisplay(d);

	ge.init("MSGE 0.0.0a", SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* window = ge.getWindow();
    	ge.setFrameBufferSizeCallback(framebuffer_size_callback);
	ge.setMouseCursorPosCallback(mouse_callback);
	ge.setMouseClickCallback(mouse_click_callback);
	ge.setKeyboardCallback(keyboard_callback);
	//ge.disableMouseCursor();
	int previous = 0;
    	while (ge.running()){
		ge.setBackgroundColor(0.5, 0.3, 0.5, 1.0);
		int ctx = ge.exec();
		
		if(ctx != previous){
			previous = ctx;
			ge.contextDestroy();
			ge.setContext(ctx);
					

		/*	switch(ctx){
				case 0: // Main eenu
					break;
				case 1: // Scene One
					ge.contextDestroy();
					ge.setContext(&customTestContext);
					ge.disableMouseCursor();
					break;
			}*/
		}
    	}

    	glfwTerminate();
    	return 0;
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mod){
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		gui_engine_global.mouse.click_left = true;
	}else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		gui_engine_global.mouse.click_left = false;
	}

	if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		gui_engine_global.mouse.click_right = true;
	}else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
		gui_engine_global.mouse.click_right = false;
	}

	if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
		gui_engine_global.mouse.click_middle = true;
	}else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
		gui_engine_global.mouse.click_middle = false;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	gui_engine_global.displayX = width;
	gui_engine_global.displayY = height;
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if((key >= 0x41 && key <= 0x5a) && mods ==0){
                key += (0x61-0x41);
        }
	updateKeyboard((GLFW_PRESS == action || GLFW_REPEAT == action), key, action, mods);
	updateKeyboardSpecial((GLFW_PRESS == action || GLFW_REPEAT == action), key);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	gui_engine_global.mouse.mouseX = xpos;
	gui_engine_global.mouse.mouseY = ypos;
	if(firstMouse) // this bool variable is initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;	

	gui_engine_global.yaw += xoffset;
	gui_engine_global.pitch += yoffset;

	if(gui_engine_global.pitch > 89.0f)
		gui_engine_global.pitch = 89.0f;
	if(gui_engine_global.pitch < -89.0f)
		gui_engine_global.pitch = -89.0f;
}
