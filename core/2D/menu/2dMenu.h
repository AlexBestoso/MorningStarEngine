#include "./2dMenuButton.h"
class Menu2D : public GraphicsObject{
	private:
		glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 view = camera.getView();
                glm::mat4 projection = glm::mat4(1.0f);
		
		GraphicsTexture texture;
		
		std::string texturePath = "";
		std::string vertexShaderPath = "./core/2D/menu/menu.vs";
		std::string fragmentShaderPath = "./core/2D/menu/menu.fs";
		
		Menu2DButton menuButtons[30];
		int activeMenuButtons[30] = {-1};
		// Input2D menuInputs[30];
		// Label2D menuLables[30];

		float vertices[8*6*6] = {
        		-1.0f, -1.0f, 0.5f,     0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        		 1.0f, -1.0f, 0.5f,     1.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        		 1.0f,  1.0f, 0.5f,     1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
        		 1.0f,  1.0f, 0.5f,     1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
        		-1.0f,  1.0f, 0.5f,     0.0f, 1.0f,    0.0f, 0.0f, -1.0f,
       	 		-1.0f, -1.0f, 0.5f,     0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
			////////
			//////
        		-1.0f, -1.0f,  0.5f,     0.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
         		 1.0f, -1.0f,  0.5f,     1.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
         		 1.0f,  1.0f,  0.5f,     1.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
         		 1.0f,  1.0f,  0.5f,     1.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
       	 		-1.0f,  1.0f,  0.5f,     0.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
       	 		-1.0f, -1.0f,  0.5f,     0.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
			///////
			//////
        		-1.0f,  1.0f,  0.5f,     1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        		-1.0f,  1.0f, 0.5f,     1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        		-1.0f, -1.0f, 0.5f,     0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        		-1.0f, -1.0f, 0.5f,     0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        		-1.0f, -1.0f,  0.5f,     0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        		-1.0f,  1.0f,  0.5f,     1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
			/////
			/////
        		 1.0f,  1.0f,  0.5f,     1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        		 1.0f,  1.0f, 0.5f,     1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        		 1.0f, -1.0f, 0.5f,     0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        		 1.0f, -1.0f, 0.5f,     0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        		 1.0f, -1.0f,  0.5f,     0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        		 1.0f,  1.0f,  0.5f,     1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
			/////
			//////
        		-1.0f, -1.0f, 0.5f,     0.0f, 1.0f,    0.0f, -1.0f, 0.0f,
        		 1.0f, -1.0f, 0.5f,     1.0f, 1.0f,    0.0f, -1.0f, 0.0f,
        		 1.0f, -1.0f,  0.5f,     1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        		 1.0f, -1.0f,  0.5f,     1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        		-1.0f, -1.0f,  0.5f,     0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        		-1.0f, -1.0f, 0.5f,     0.0f, 1.0f,    0.0f, -1.0f, 0.0f,
			/////
        		/////
			-1.0f,  1.0f, 0.5f,     0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
        		 1.0f,  1.0f, 0.5f,     1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
        		 1.0f,  1.0f,  0.5f,     1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        		 1.0f,  1.0f,  0.5f,     1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        		-1.0f,  1.0f,  0.5f,     0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        		-1.0f,  1.0f, 0.5f,     0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
			///

    		};
	public:
		Menu2D(){
			for(int i=0; i<30; i++)
				activeMenuButtons[i] = -1;
		}
		void setTextureFile(const char *path){
			texturePath = path;
		}

	       	void setVertexShaderFile(const char *path){
			vertexShaderPath = path;
		}
		void setFragmentShaderFile(const char *path){
			fragmentShaderPath = path;
		}

		void addButton(int index, Menu2DButton but){
			if(index < 0 || index >= 30){
				return;
			}
			menuButtons[index] = but;
			activeMenuButtons[index] = index;
		}

		Menu2DButton getButtonX(int index){
			return menuButtons[index];
		}

		bool create(void){
			if(!this->addVertexShader(vertexShaderPath.c_str(), 0)){
                                printf("Failed to compile vertex shader '%s'.\n", vertexShaderPath.c_str());
                                return false;
                        }

                        if(!this->addFragmentShader(fragmentShaderPath.c_str(), 1)){
                                printf("Failed to compile fragment shader '%s'\n", fragmentShaderPath.c_str());
                                return false;
                        }

			if(!this->linkShaders()){
                                printf("Faild to link 2D Menu shaders.\n");
                                return false;
                        }

			if(texturePath != ""){
				texture.add2DParameter(0, GL_TEXTURE_WRAP_S, GL_REPEAT);
                       		texture.add2DParameter(1, GL_TEXTURE_WRAP_T, GL_REPEAT);
                        	texture.add2DParameter(2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        	texture.add2DParameter(3, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        	texture.setTextureUnit(0);
                        	if(!texture.loadTexture2D(texturePath.c_str())){
                        	        printf("Failed to import texture '%s'\n", texturePath.c_str());
                        	        return false;
                        	}
			}

			this->generateObjectIds(true, true, false);
                        this->bindVao();
                        this->bindVbo();

			this->storeVertexData(8*6*6, vertices, GL_STATIC_DRAW);

			this->setAttributePointer(0, 3, 8, (void *)0);
                        this->enableArrayAttribute(0);
                        this->setAttributePointer(1, 2, 8, (void *)(3*sizeof(float)));
                        this->enableArrayAttribute(1);
                        this->setAttributePointer(2, 3, 8, (void *)(5*sizeof(float)));
                        this->enableArrayAttribute(2);

			this->unbindVbo();
                        this->unbindVao();

                        this->use();
			if(texturePath != "")
				this->setUniform("menuTexture", 0);


			for(int i=0; i<30; i++){
				if(activeMenuButtons[i] != -1){
					if(!menuButtons[i].create()){
						printf("Failed to create menu button at index %d\n", i);
					}
				}
			}
			return true;
		}

		void destroy(){
			for(int i=0; i<30; i++){
				menuButtons[i].destroy();
			}
			texture.destroy();
			GraphicsObject::destroy();
		}

		void draw(void){
			texture.bind2D();

			this->bindVao();
                        this->use();
			this->setUniform("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			for(int i=0; i<30; i++){
				if(activeMenuButtons[i] != -1){
					menuButtons[i].ges = this->ges;
	                                menuButtons[i].draw();
				}
                        }	
		}
};
