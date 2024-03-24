class CustomMainMenuContext : public GraphicsContext{
	private:
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
		
		        if(glfwGetKey(window, GLFW_KEY_SPACE)){
		                gui_engine_global.keyboard.key_space = true;
				this->context = 1;
			}else{
		                gui_engine_global.keyboard.key_space = false;
			}

		}


	public:
		void init(){	
			this->context = 0;
			menu.setTextureFile("./Custom/images/GameMenuTexture.jpeg");
			menu.setVertexShaderFile("./core/2D/menu/menu.vs");
                	menu.setFragmentShaderFile("./core/2D/menu/menu.fs");

			Menu2DButton button;
			button.name = "Red Button";
			button.setPos(0, 0, -1.0);
			button.setSize(-0.2, -0.1, 0.0);
			button.setColor(1.0f, 0.2f, 0.2f);
			menu.addButton(0, button);

			Menu2DButton button2;
			button2.name = "Green Button";
			button2.setPos(0.0, -0.4, -1.0);
			button2.setSize(-0.2, -0.1, 0.0);
			button2.setColor(0.2f, 1.0f, 0.2f);
			menu.addButton(1, button2);

			if(!menu.create()){
				printf("Failed to create 2D menu.\n");
			}
                    
			this->activeCamera = &menu.camera;
		}

		void destroy(){
			menu.destroy();
		}
		int exec(GLFWwindow* window){
			this->processInput(window);
			menu.draw();

			return this->context;
		}
}customMainMenu;
