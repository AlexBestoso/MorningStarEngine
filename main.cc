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
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


// settings

int main(void){
	GraphicsEngine ge;
	ge.init("MSGE III", SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* window = ge.getWindow();
    	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	printf("Trying to build...\n");
	TestTerrain terrain;
	if(!terrain.create()){
		printf("Failed to build terrain\n");
		exit(EXIT_FAILURE);
	}
	
	TestObject testObj;
	if(!testObj.create()){
		printf("Failed to create test object.\n");
		exit(EXIT_FAILURE);
	}

	FpsPlayer playerOne;
	if(!playerOne.create()){
		printf("Failed to create main character\n");
		exit(EXIT_FAILURE);
	}

	TestLight testLight;
	if(!testLight.create()){
		printf("Failed to create light source.\n");
		exit(EXIT_FAILURE);
	}

	ge.setActiveCamera(&playerOne.camera);

    	while (ge.running()){
        	// input
        	// -----
        	processInput(window);
		ge.setBackgroundColor(0.5, 0.5, 0.5, 1.0);

		playerOne.draw();
		
		testLight.camera = ge.getActiveCamera();
		testLight.draw();

		
		testObj.lightPos = testLight.getPos();
		//testObj.lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		testObj.camera = ge.getActiveCamera();
		testObj.draw();

		terrain.camera = ge.getActiveCamera();
		testObj.lightPos = testLight.getPos();
		terrain.draw();
	
		ge.swapAndPoll();
    	}

    	testObj.destroy();
	terrain.destroy();

    	glfwTerminate();
    	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W)){
		gui_engine_global.keyboard.key_w = true;
	}else{
		gui_engine_global.keyboard.key_w = false;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
		gui_engine_global.keyboard.key_s = true;
	else
		gui_engine_global.keyboard.key_s = false;

	if (glfwGetKey(window, GLFW_KEY_A))
		gui_engine_global.keyboard.key_a = true;
	else 
		gui_engine_global.keyboard.key_a = false;

	if (glfwGetKey(window, GLFW_KEY_D))
		gui_engine_global.keyboard.key_d = true;
	else 
		gui_engine_global.keyboard.key_d = false;

	if(glfwGetKey(window, GLFW_KEY_SPACE))
		gui_engine_global.keyboard.key_space = true;
	else
		gui_engine_global.keyboard.key_space = false;
	
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
