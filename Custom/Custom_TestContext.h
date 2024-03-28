class CustomTestContext : public GraphicsContext{
	private:
		GraphicsScene scene;
	        TestTerrain terrain;
		GraphicsSkybox skybox;
	        TestObject testObj;
	        FpsPlayer playerOne;
		TestLight testLight;
		Menu2D menu;

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

		}

	public:
		void init(){	
			printf("Trying to build...\n");
		        if(!terrain.create()){
		                printf("Failed to build terrain\n");
		                exit(EXIT_FAILURE);
		        }

			if(!scene.create("./scenes/sampleScene", "SampleScene")){
				printf("Failed to build scene.\n");
				exit(EXIT_FAILURE);
			}

			if(!skybox.create("./scenes/sampleSkyBox/sampleSkyBox.obj", "./scenes/sampleSkyBox/skyboxTexture.jpg")){
                                printf("Failed to load skybox.\n");
                                exit(EXIT_FAILURE);
                        }
	
		        //if(!testObj.create()){
		        //        printf("Failed to create test object.\n");
		        //        exit(EXIT_FAILURE);
		        //}

			playerOne.setSceneData(scene.getObjectPointer(), scene.getObjectCount());
		        if(!playerOne.create()){
		                printf("Failed to create main character\n");
		                exit(EXIT_FAILURE);
		        }
	
		        if(!testLight.create()){
		                printf("Failed to create light source.\n");
		                exit(EXIT_FAILURE);
		        }

			this->activeCamera = &playerOne.camera;
			
			this->context = 1;
		}

		void destroy(){
			terrain.destroy();
			testObj.destroy();
			scene.destroy();
			playerOne.destroy();
			testLight.destroy();
		}
		int exec(GLFWwindow* window){
			this->processInput(window);
			playerOne.draw();


        	        testLight.camera = this->activeCamera[0];
        	        //testLight.draw();

	                skybox.lightPos = testLight.getPos();
			skybox.camera = this->activeCamera[0];
			skybox.draw();

	                //testObj.lightPos = testLight.getPos();
	               // testObj.camera = this->activeCamera[0];
	                //testObj.draw();

	                //terrain.camera = this->activeCamera[0];
	                //terrain.lightPos = testLight.getPos();
	                //terrain.draw();

			scene.camera = this->activeCamera[0];
			scene.lightPos = testLight.getPos();
			scene.draw();
			return this->context;
		}
}customTestContext;
