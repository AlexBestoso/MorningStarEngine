#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>

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

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

float lastX = 400, lastY = 300;
float pitch, yaw;


#include "./guiEngineStruct.struct.h"
#include "./GraphicsEngine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#include "./Custom/Custom_TestContext.h"

int main(void){
	ge.init("MSGE III", SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* window = ge.getWindow();
    	ge.setFrameBufferSizeCallback(framebuffer_size_callback);
	ge.disableMouseCursor();
	ge.setMouseCursorPosCallback(mouse_callback);
	ge.setContext(&customTestContext);
	int previous = 0;
    	while (ge.running()){
		ge.setBackgroundColor(0.5, 0.5, 0.5, 1.0);
		int ctx = ge.exec();
		
		if(ctx != previous){
			previous = ctx;

			switch(ctx){
				default:
					ge.contextDestroy();
					ge.setContext(&customTestContext);
					break;
			}
		}
    	}

    	glfwTerminate();
    	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
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
