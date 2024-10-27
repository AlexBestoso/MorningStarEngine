#include "../interfaceHeaders.h"
class CustomTestContext : public ContextInterface{
	private:
		const int id = 1;
		GraphicsGeometry geom;
		GraphicsScene scene;
		//GraphicsSkybox skybox;
	        FpsPlayer playerOne;
		Menu2D menu;
		DevTools devtools;
		bool firstStart = true;

		glm::vec3 *organizedPoints[8];
		size_t quadrantSize[8] = {0};
		glm::vec3 minX, minY, minZ, maxX, maxY, maxZ, center;

		void processInput(GLFWwindow *window){
		        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				this->context = 0;
		                //glfwSetWindowShouldClose(window, true);
			}	
			if (glfwGetKey(window, GLFW_KEY_2)){
				// Debug Commands.
                /*                ges.keyboard.key_2 = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				printf("Dev Consol\n:");
				printf("> ");
				std::string input = "";
				std::getline(std::cin, input);
				devtools.runCommand(input, window, this->scene);
				printf("input : %s\n", input.c_str());
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/
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
			printf("Setting up the scene\n");
			if(!scene.create("./scenes/sampleScene", "SampleScene")){
				printf("Failed to build scene.\n");
				exit(EXIT_FAILURE);
			}

		        if(!playerOne.create()){
		                printf("Failed to create main character\n");
		                exit(EXIT_FAILURE);
		        }
	
			this->activeCamera = &playerOne.camera;

			//size_t sceneObjCount = scene.getObjectCount();
			//obj_t *sceneObjects = scene.getObjects();
			
			//for(int i=0; i<sceneObjCount; i++){
			//	obj_data_t *data = (obj_data_t *)sceneObjects[i].glut_data;
			//	for(int j=0; j<sceneObjects[i].element_count; j++){
		//		}
		//	}
			
			this->context = 1;
		}

		virtual void destroy() override{
			scene.destroy();
			playerOne.destroy();
			//testLight.destroy();
		}
		virtual int exec(GLFWwindow* window) override{
			if(firstStart){
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				firstStart = false;
			}
			
			scene.setGES(ges);
			playerOne.setGES(ges);
			this->processInput(window);

			scene.camera = this->activeCamera[0];
			scene.draw();
			playerOne.draw();
			return this->context;
		}
};

extern "C"{
	CustomTestContext *create(){
		return new CustomTestContext;
	}
}
