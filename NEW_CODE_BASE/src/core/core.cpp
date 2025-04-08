#include "../../main.h"
#include "../error/error.h"
#include "../entity/entity.h"
#include "../../junk/testEntity.h"

#include "./core.error.h"
#include "./core.h"
extern int global_w, global_h;


void mouse_callback(GLFWwindow* , double , double ){
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
			this->a = 1;
			this->b = 1;
			this->c = 1;
		}
		
		void Core::init(void){
			//glfwSwapInterval(1);
    			//glViewport(0, 0, global_w, global_h);
			test.init();
		}

		bool Core::isAlive(WindowCtrl window){
			alive = (!glfwWindowShouldClose(window.getWindow()));
			return alive;
		}

		void Core::process(void){
			glClearColor(soulColor[0], soulColor[1], soulColor[2], soulColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
			
			soulColor[0] +=  0.01 * a;
			soulColor[1] +=  0.01 * b;
			soulColor[2] +=  0.01 * c;

			if(soulColor[0] > 1 || soulColor[0] < 0){
				a*=-1;
			}

			if(soulColor[1] > 1 || soulColor[1] < 0){
				b*=-1;
			}

			if(soulColor[2] > 1 || soulColor[2] < 0){
				c*=-1;
			}
			test.draw();
		}

		void Core::pulse(WindowCtrl window) {
			try{
				time = glfwGetTime();
				glfwSwapBuffers(window.getWindow());
				glfwPollEvents();
				//test.destroy();
			}catch(CoreException &e){
				throw CoreError(e, "pulse", "failed to get window.");
			}
		}
