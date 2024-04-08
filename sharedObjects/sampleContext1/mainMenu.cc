#include "../interfaceHeaders.h"
class MainMenu : public ContextInterface{
	private:
		const int id = 0;
		Menu2D menu;

		void processInput(GLFWwindow *window){
                        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                                glfwSetWindowShouldClose(window, true);

                        if (glfwGetKey(window, GLFW_KEY_W)){
                                this->ges.keyboard.key_w = true;
                        }else{
                                this->ges.keyboard.key_w = false;
                        }

                        if (glfwGetKey(window, GLFW_KEY_S))
                                this->ges.keyboard.key_s = true;
                        else
                                this->ges.keyboard.key_s = false;

                        if (glfwGetKey(window, GLFW_KEY_A))
                                this->ges.keyboard.key_a = true;
                        else
                                this->ges.keyboard.key_a = false;

                        if (glfwGetKey(window, GLFW_KEY_D))
                                this->ges.keyboard.key_d = true;
                        else
                                this->ges.keyboard.key_d = false;

                        if(glfwGetKey(window, GLFW_KEY_SPACE)){
                                this->ges.keyboard.key_space = true;
                                this->context = 1;
                        }else{
                                this->ges.keyboard.key_space = false;
                        }

			Menu2DButton btn = this->menu.getButtonX(0);
                        if(btn.isHovered() && this->ges.mouse.click_left){
                                printf("Clicked Button 0\n");
                                glfwSetWindowShouldClose(window, true);
                        }

                        btn = this->menu.getButtonX(1);
                        if(btn.isHovered() && this->ges.mouse.click_left){
                                printf("Clicked Button 1\n");
                                this->context = 1;
                        }

                }


	public:
		virtual void destroy() override{
			menu.destroy();
		}
        	virtual void init() override{
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
        	virtual int exec(GLFWwindow* window) override{
			this->processInput(window);
			menu.ges = this->ges;
                        menu.draw();
			return context;
		}
};

extern "C" {
	MainMenu *create(){
		return new MainMenu;
	}
}
