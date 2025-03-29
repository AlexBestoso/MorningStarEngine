#include "./core.error.h"

void CoreFrameBuffer(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

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

	
class Core{
	private:
		unsigned int screenWidth;
		unsigned int screenHeight;
		WindowCtrl window;
		bool alive = true;
		float soulColor[4] = {0.0, 0.2, 0.2, 1.0};
		double time;
		testEnt test;
	public:
		Core(void){
		}
		
		void init(void){
			window.setTitle("MSGE");
                        window.init();
                        window.current();
                        window.blend(true);
                        window.depthTest(true);
                        window.alphaBlendFunc();
                        window.setFrameResizeCallBack(CoreFrameBuffer);
                        window.setKeyboardCallback(keyboard_callback);
                        window.setMouseClickCallback(mouse_click_callback);
                        window.setMouseCursorPosCallback(mouse_callback);
		}

		bool isAlive(void){
			glClearColor(soulColor[0], soulColor[1], soulColor[2], soulColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
			alive = (!glfwWindowShouldClose(this->window.getWindow()));
			return alive;
		}

		void process(){
			test.init();
			test.draw();
		}

		void pulse(void) {
			try{
				//time = glfwGetTime();
				glfwSwapBuffers(window.getWindow());
				glfwPollEvents();
			}catch(CoreException &e){
				throw CoreError(e, "pulse", "failed to get window.");
			}
		}
};
