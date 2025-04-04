#include "../../main.h"
#include "../error/error.h"
#include "../windowCtrl/windowCtrl.h"
#include "../shader/shader.h"
#include "../entity/entity.h"
#include "../../junk/testEntity.h"

#include "./core.error.h"
#include "./core.h"
extern int global_w, global_h;
void mouse_click_callback(GLFWwindow* window, int button, int action, int mod){
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
                //gui_engine_global.mouse.click_left = true;
        }else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
                //gui_engine_global.mouse.click_left = false;
        }

        if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
                //gui_engine_global.mouse.click_right = true;
        }else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
                //gui_engine_global.mouse.click_right = false;
        }

        if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
                //gui_engine_global.mouse.click_middle = true;
        }else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
                //gui_engine_global.mouse.click_middle = false;
        }
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);
        if((key >= 0x41 && key <= 0x5a) && mods ==0){
                key += (0x61-0x41);
        }
       // updateKeyboard((GLFW_PRESS == action || GLFW_REPEAT == action), key, action, mods);
        //updateKeyboardSpecial((GLFW_PRESS == action || GLFW_REPEAT == action), key);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
 /*       gui_engine_global.mouse.mouseX = xpos;
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
                gui_engine_global.pitch = -89.0f;*/
}

	
		Core::Core(void){
			this->screenWidth = 700;
                	this->screenHeight = 700;
                	this->alive = true;
                	this->soulColor[0] = 0.0;
                	this->soulColor[1] = 0.2;
                	this->soulColor[2] = 0.2;
                	this->soulColor[3] = 1.0;
               	 	this->time = 0;
                	this->dbg = false;
		}
		
		void Core::init(void){
			glfwSwapInterval(1);
			global_w = screenWidth;
			global_h = screenHeight;
    			glViewport(0, 0, global_w, global_h);
			test.init();
		}

		bool Core::isAlive(WindowCtrl window){
			alive = (!glfwWindowShouldClose(window.getWindow()));
			return alive;
		}

		void Core::process(void){
			glClearColor(soulColor[0], soulColor[1], soulColor[2], soulColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

			test.draw();
		}

		void Core::pulse(WindowCtrl window) {
			try{
				time = glfwGetTime();
				glfwSwapBuffers(window.getWindow());
				glfwPollEvents();
			}catch(CoreException &e){
				throw CoreError(e, "pulse", "failed to get window.");
			}
		}
