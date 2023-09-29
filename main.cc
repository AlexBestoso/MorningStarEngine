#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>

#include <X11/Xlib.h>

#include "./glm/glm/glm.hpp"
#include "./glm/glm/gtc/matrix_transform.hpp"
#include "./glm/glm/gtc/type_ptr.hpp"

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"

#include "./WavefrontImport.h"

unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 800;

float lastX = 400, lastY = 300;
float pitch, yaw;


#include "./guiEngineStruct.struct.h"
#include "./GraphicsEngine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mod);

#include "./Custom/Custom_TestContext.h"
#include "./Custom/Custom_MainMenu.h"

int main(void){
	// Calculate aspect ratio to fix glut bug.
	Display* d = XOpenDisplay(NULL);
	Screen*  s = DefaultScreenOfDisplay(d);
	SCR_WIDTH = s->width;
	SCR_HEIGHT = s->height;
	XCloseDisplay(d);



	ge.init("MSGE III", SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* window = ge.getWindow();
    	ge.setFrameBufferSizeCallback(framebuffer_size_callback);
	ge.setMouseCursorPosCallback(mouse_callback);
	ge.setMouseClickCallback(mouse_click_callback);
	ge.setContext(&customMainMenu);
	//ge.disableMouseCursor();
	int previous = 0;
    	while (ge.running()){
		ge.setBackgroundColor(0.5, 0.3, 0.5, 1.0);
		int ctx = ge.exec();
		
		if(ctx != previous){
			previous = ctx;

			switch(ctx){
				case 0:
				       	
				case 1:
					ge.contextDestroy();
					ge.setContext(&customTestContext);
					ge.disableMouseCursor();
					break;
			}
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

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}
