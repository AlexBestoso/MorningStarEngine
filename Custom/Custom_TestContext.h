class CustomTestContext : public GraphicsContext{
	private:
	        TestTerrain terrain;
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
	
		        if(!testObj.create()){
		                printf("Failed to create test object.\n");
		                exit(EXIT_FAILURE);
		        }

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
			playerOne.destroy();
			testLight.destroy();
		}
		int exec(GLFWwindow* window){
			this->processInput(window);
			playerOne.draw();

        	        testLight.camera = this->activeCamera[0];
        	        testLight.draw();


	                testObj.lightPos = testLight.getPos();
	                testObj.camera = this->activeCamera[0];
	                testObj.draw();

	                terrain.camera = this->activeCamera[0];
	                terrain.lightPos = testLight.getPos();
	                terrain.draw();
			return this->context;
		}
}customTestContext;
