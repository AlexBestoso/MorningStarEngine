class MorningButton : public GraphicsObject{
	private:
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 extraColor = glm::vec3(0.0f);

		GraphicsTexture texture;

		std::string texturePath = "";
		
		std::string vertexShaderPath = "./core/2D/button/button.vs";
                std::string fragmentShaderPath = "./core/2D/button/button.fs";

		int hovered = 0;

		float x_min=2, y_min=2, x_max=-2, y_max=-2;
		

		float vertices[8*6] = {
        		-1.0f, -1.0f, -0.5f,     0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        		 1.0f, -1.0f, -0.5f,     1.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        		 1.0f,  1.0f, -0.5f,     1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
        		 1.0f,  1.0f, -0.5f,     1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
        		-1.0f,  1.0f, -0.5f,     0.0f, 1.0f,    0.0f, 0.0f, -1.0f,
       	 		-1.0f, -1.0f, -0.5f,     0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        	};
		
	public:
		graphics_master_t *vtex = (graphics_master_t *)&vertices;
		size_t vtex_size = 6;
		std::string name = "";

		void setSize(float x, float y, float z){
			model = glm::scale(model, glm::vec3(x, y, z));
		}

		void setPos(float x, float y, float z){
			model = glm::translate(model, glm::vec3(x, y, z));
		}

		void setColor(float r, float g, float b){
			this->extraColor = glm::vec3(r, g, b);
		}

		bool create(){
			// Setup Shaders
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

			// Setup Texture
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

			// Generate and bind glut objects
			this->generateObjectIds(true, true, false);
                        this->bindVao();
                        this->bindVbo();

			// Store vertex data.
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
                        if(texturePath != ""){
                                this->setUniform("buttonTexture", 0);
				this->setUniform("textureActive", 1);
			}else{
				this->setUniform("textureActive", 0);
			}

			this->setUniform("extraColor", this->extraColor);
			this->setUniform("hovered", hovered);


			//x_min = vertices[0];
			//x_max = vertices[0];
			//y_min = vertices[1];
			//y_max = vertices[1];
                        for(int i=0; i<8*vtex_size; i++){
                                glm::vec4 val(vertices[i], vertices[i+1], 1, 1);
                                val = model * val;
                                if(val.x < x_min)
                                        x_min = val.x;
                                if(val.x > x_max)
                                        x_max = val.x;

                                if(val.y < y_min)
                                        y_min = val.y;
                                if(val.y > y_max)
                                        y_max = val.y;
                                i+=7;
                        }
			return true;
		}

		void setMouseHover(){
			float a = (2*(this->ges.mouse.mouseX/this->ges.displayX)-1);
			float b = -2*(this->ges.mouse.mouseY/this->ges.displayY)+1;
			glm::vec4 mouse(a, b, 0, 0);
			if((mouse.x >= x_min && mouse.x <= x_max) && (mouse.y >= y_min && mouse.y <= y_max)){
				hovered = 1;
			}else{
				hovered = 0;
			}


		}
		
		bool isHovered(void){
			return (hovered == 0) ? false : true;
		}
		void draw(){
			if(texturePath != "")
				texture.bind2D();

                        this->bindVao();
                        this->use();
			setMouseHover();
                        this->setUniform("model", this->model);
			this->setUniform("extraColor", this->extraColor);
			this->setUniform("hovered", this->hovered);

                        glDrawArrays(GL_TRIANGLES, 0, vtex_size);
		}

		void destroy(){
                        texture.destroy();
                        GraphicsObject::destroy();
                }
};
