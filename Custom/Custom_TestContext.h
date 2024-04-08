class CustomTestContext : public GraphicsContext{
	private:
		GraphicsScene scene;
		GraphicsSkybox skybox;
	        TestObject testObj;
	        FpsPlayer playerOne;
		TestLight testLight;
		Menu2D menu;
		DevTools devtools;

		void processInput(GLFWwindow *window){
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

			if (glfwGetKey(window, GLFW_KEY_E))
                                gui_engine_global.keyboard.key_e = true;
                        else
                                gui_engine_global.keyboard.key_e = false;

			if (glfwGetKey(window, GLFW_KEY_1))
                                gui_engine_global.keyboard.key_1 = true;
                        else
                                gui_engine_global.keyboard.key_1 = false;

			if (glfwGetKey(window, GLFW_KEY_2)){
				// Debug Commands.
                                gui_engine_global.keyboard.key_2 = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				printf("Dev Consol\n:");
				printf("> ");
				std::string input = "";
				std::getline(std::cin, input);
				devtools.runCommand(input, window, this->scene);
				printf("input : %s\n", input.c_str());
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}else{
                                gui_engine_global.keyboard.key_2 = false;
			}

			if (glfwGetKey(window, GLFW_KEY_3))
                                gui_engine_global.keyboard.key_3 = true;
                        else
                                gui_engine_global.keyboard.key_3 = false;

		}

	public:
		void init(){	
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

		void destroy(){
			printf("Destroying Scene.\n");
			scene.destroy();
			playerOne.destroy();
			//testLight.destroy();
		}
		int exec(GLFWwindow* window){
			this->processInput(window);
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
}customTestContext;
