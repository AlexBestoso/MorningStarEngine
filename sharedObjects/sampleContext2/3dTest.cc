#include "../interfaceHeaders.h"
class CustomTestContext : public ContextInterface{
	private:
		const int id = 1;
		GraphicsScene scene;
		//GraphicsSkybox skybox;
	        FpsPlayer playerOne;
		Menu2D menu;
		DevTools devtools;
		bool firstStart = true;

		void processInput(GLFWwindow *window){
		        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		                glfwSetWindowShouldClose(window, true);
	
		        if (glfwGetKey(window, GLFW_KEY_W)){
		                ges.keyboard.key_w = true;
		        }else{
		                ges.keyboard.key_w = false;
		        }
	
		        if (glfwGetKey(window, GLFW_KEY_S))
		                ges.keyboard.key_s = true;
		        else
		                ges.keyboard.key_s = false;
	
		        if (glfwGetKey(window, GLFW_KEY_A))
		                ges.keyboard.key_a = true;
		        else
		                ges.keyboard.key_a = false;
	
		        if (glfwGetKey(window, GLFW_KEY_D))
		                ges.keyboard.key_d = true;
		        else
		                ges.keyboard.key_d = false;
		
		        if(glfwGetKey(window, GLFW_KEY_SPACE))
		                ges.keyboard.key_space = true;
		        else
		                ges.keyboard.key_space = false;

			if (glfwGetKey(window, GLFW_KEY_E))
                                ges.keyboard.key_e = true;
                        else
                                ges.keyboard.key_e = false;

			if (glfwGetKey(window, GLFW_KEY_1))
                                ges.keyboard.key_1 = true;
                        else
                                ges.keyboard.key_1 = false;

			if (glfwGetKey(window, GLFW_KEY_2)){
				// Debug Commands.
                                ges.keyboard.key_2 = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				printf("Dev Consol\n:");
				printf("> ");
				std::string input = "";
				std::getline(std::cin, input);
				devtools.runCommand(input, window, this->scene);
				printf("input : %s\n", input.c_str());
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}else{
                                ges.keyboard.key_2 = false;
			}

			if (glfwGetKey(window, GLFW_KEY_3))
                                ges.keyboard.key_3 = true;
                        else
                                ges.keyboard.key_3 = false;

		}

	public:
		virtual void init() override{	
			printf("Trying to build...\n");
			if(!scene.create("./scenes/sampleScene", "SampleScene")){
				printf("Failed to build scene.\n");
				exit(EXIT_FAILURE);
			}

			//if(!skybox.create("./scenes/sampleSkyBox/sampleSkyBox.obj", "./scenes/sampleSkyBox/skyboxTexture.jpg")){
                        //        printf("Failed to load skybox.\n");
                        //        exit(EXIT_FAILURE);
                        //}
	

			playerOne.setSceneData(scene.getObjectPointer(), scene.getObjectCount());
			playerOne.setCollisionObjects(scene.getObjects(), scene.getObjectCount());
		        if(!playerOne.create()){
		                printf("Failed to create main character\n");
		                exit(EXIT_FAILURE);
		        }
	
		        /*if(!testLight.create()){
		                printf("Failed to create light source.\n");
		                exit(EXIT_FAILURE);
		        }*/

			this->activeCamera = &playerOne.camera;
			
			this->context = 1;
		}

		virtual void destroy() override{
			printf("Destroying Scene.\n");
			scene.destroy();
			playerOne.destroy();
			//testLight.destroy();
		}
		virtual int exec(GLFWwindow* window) override{
			if(firstStart){
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				firstStart = false;
			}
			this->processInput(window);
			playerOne.setGES(ges);
			scene.setGES(ges);
			playerOne.draw();


        	        //testLight.camera = this->activeCamera[0];
        	        //testLight.draw();

	                //skybox.lightPos = testLight.getPos();
			//skybox.camera = this->activeCamera[0];
			//skybox.draw();

			scene.camera = this->activeCamera[0];
			scene.processCollision(playerOne.camera.cameraPosition);
			//scene.lightPos = testLight.getPos();
			scene.draw();
			return this->context;
		}
};

extern "C"{
	CustomTestContext *create(){
		return new CustomTestContext;
	}
}
