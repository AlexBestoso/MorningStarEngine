#include "../interfaceHeaders.h"
class CustomTestContext : public ContextInterface{
	private:
		const int id = 1;
		GraphicsGeometry geom;
		GraphicsScene scene;
		GraphicsSkybox skybox;
	        FpsPlayer playerOne;
		Menu2D menu;
		DevTools devtools;
		bool firstStart = true;

		glm::vec3 *organizedPoints[8];
		size_t quadrantSize[8] = {0};
		glm::vec3 minX, minY, minZ, maxX, maxY, maxZ, center;

		std::string skyboxFaces[6] = {
			"./scenes/sampleScene/skybox/right.jpg",
			"./scenes/sampleScene/skybox/left.jpg",
			"./scenes/sampleScene/skybox/top.jpg",
			"./scenes/sampleScene/skybox/bottom.jpg",
			"./scenes/sampleScene/skybox/back.jpg",
			"./scenes/sampleScene/skybox/front.jpg"
		};

		void processInput(GLFWwindow *window){
		        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				this->context = 0;
		                //glfwSetWindowShouldClose(window, true);
			}	
			if (glfwGetKey(window, GLFW_KEY_2)){
				// Debug Commands.
                                ges.keyboard.key_2 = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				printf("Dev Consol\n:");
				printf("> ");
				std::string input = "";
				std::getline(std::cin, input);
				devtools.runCommand(input, window, this->scene);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}else{
                                ges.keyboard.key_2 = false;
			}

			if (glfwGetKey(window, GLFW_KEY_3))
                                ges.keyboard.key_3 = true;
                        else
                                ges.keyboard.key_3 = false;

			glm::mat4 model = glm::mat4(1.0f);
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);

                        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			view = activeCamera[0].getView();
                        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);


			for(int i=0; i<scene.objImporter.objectCount; i++){
				for(int j=0; j<scene.objImporter.waveObjects[i].getVCount(); j++){
                                        glm::vec4 pos = view * model * glm::vec4(scene.objImporter.waveObjects[i].v_data[j], 1.0);
                                        glm::vec4 a = glm::vec4(glm::vec3(0.0125), 1.0);
                                        //printf("%f, %f, %f vs %f, %f, %f\n", a.x, a.y, a.z, pos.x, pos.y, pos.z);
                                        if(pos.x >= -a.x && pos.x <= a.x && pos.y >= -a.y && pos.y <= a.y){
                                                pos = model * glm::vec4(scene.objImporter.waveObjects[i].v_data[j], 1.0);
						devtools.processInput(glm::vec3(pos.x, pos.y, pos.z));
                                                printf("(%f %f %f) : [%d:%d]%s\n", pos.x, pos.y, pos.z, i, j, scene.objImporter.waveObjects[i].getName().c_str());
                                                break;
                                        }

                                }
			}
                        glm::vec4 a = glm::vec4(glm::vec3(0.0125), 1.0);
			glm::vec3 cp = activeCamera[0].getPos() * activeCamera[0].cameraFront;
			glm::vec4 pos = glm::vec4(activeCamera[0].getPos(), 1.0);
	
			printf("dbg : %f %f %f\n", pos.x, pos.y, pos.z);
			devtools.processInput(glm::vec3(pos.x, pos.y, pos.z)); // convert center of screen to world coords.
		}

	public:
		virtual void init() override{	
			if(!scene.create("./scenes/sampleScene", "SampleScene")){
				printf("Failed to build scene.\n");
				exit(EXIT_FAILURE);
			}

		        if(!playerOne.create()){
		                printf("Failed to create main character\n");
		                exit(EXIT_FAILURE);
		        }
		
			if(!skybox.create(skyboxFaces)){
				printf("Failed to create skybox.\n");
				exit(EXIT_FAILURE);
			}

			if(!devtools.create()){
				printf("Failed to create devtools\n");
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
			devtools.setGES(ges);
			this->processInput(window);

			scene.camera = this->activeCamera[0];
			skybox.camera = this->activeCamera[0];
			devtools.camera = this->activeCamera[0];

			skybox.draw();
			scene.draw();
			playerOne.draw();
			devtools.draw();
			return this->context;
		}
};

extern "C"{
	CustomTestContext *create(){
		return new CustomTestContext;
	}
}
