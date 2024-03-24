#define TEST_TERRAIN_VERTEX_SIZE (8*(6*6))
class TestTerrain : public GraphicsObject{
	private:
		glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 view = glm::mat4(1.0f);
                glm::mat4 projection = glm::mat4(1.0f);

		int terrainX = 1;
		int terrainY = 1;
		size_t objCount = 1;

		
		
		GraphicsTexture cobbleTexture;

		unsigned int transformLocation;

		/*
		 * Vertex Format: (x, y, x)  (Texture X, Texture Y)
		 * */
		float vertices[TEST_TERRAIN_VERTEX_SIZE] = {
			// Top Face
			 0.5f, 0.5f,  0.5f,	1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f, -0.5f,	1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f,	0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f,	0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f,  0.5f,	0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f,  0.5f,	1.0f, 1.0f,   0.0f, 1.0f, 0.0f,

			// Bottom face
			 0.5f, -0.5f,  0.5f,	1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	1.0f, 1.0f,   0.0f, 1.0f, 0.0f,

			// Left face
			-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,

			// Right face
			 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,	1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,   1.0f, 0.0f, 0.0f,

			// Front face
			-0.5f, -0.5f,  0.5f,	1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
			-0.5f, -0.5f,  0.5f,	1.0f, 1.0f,   0.0f, 0.0f, -1.0f,

			// Back face
			-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,   0.0f, 0.0f, -1.0f
		};

	public:
		glm::vec3 lightPos;
		bool create(void){
			if(!this->addVertexShader("./testObjects/testTerrain.vs", 0)){
				printf("Failed to compile vertex shader.\n");
				return false;
			}

			if(!this->addFragmentShader("./testObjects/testTerrain.fs", 1)){
				printf("Failed to compile fragment shader\n");
				return false;
			}

			if(!this->linkShaders()){
				printf("Faild to link shader.\n");
				return false;
			}

        		cobbleTexture.add2DParameter(0, GL_TEXTURE_WRAP_S, GL_REPEAT);
        		cobbleTexture.add2DParameter(1, GL_TEXTURE_WRAP_T, GL_REPEAT);
        		cobbleTexture.add2DParameter(2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        		cobbleTexture.add2DParameter(3, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        		cobbleTexture.setTextureUnit(1);
        		if(!cobbleTexture.loadTexture2D("./cobbleStone.jpg")){
                		printf("Failed to import container texture.\n");
				return false;
        		}

			this->generateObjectIds(true, true, false);
			this->bindVao();
			this->bindVbo();
			this->storeVertexData(sizeof(vertices), vertices, GL_STATIC_DRAW);

			this->setAttributePointer(0, 3, 8, (void *)0);
       	 		this->enableArrayAttribute(0);
        		this->setAttributePointer(1, 2, 8, (void *)(3*sizeof(float)));
        		this->enableArrayAttribute(1);
			this->setAttributePointer(2, 3, 8, (void *)(5*sizeof(float)));
                        this->enableArrayAttribute(2);

			this->unbindVbo();
			this->unbindVao();

			this->use();

			this->material.ambient = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.specular = glm::vec3(0.5f, 0.5f, 0.3f);
                        this->material.shininess = 32.0f;


                        this->light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
                        //this->light.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
                        this->light.direction = glm::vec3(-8.0f, -8.0f, -8.0f);
                        this->light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
                        this->light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        		this->setUniform("material.diffuseMap", 1);
			
			model = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f));
			model = glm::translate(model, glm::vec3(0.0f, -8.0f, 0.0f));

			return true;
		}


		void draw(void){

			model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f));
                        model = glm::translate(model, glm::vec3(0.0f, -8.0f, 0.0f));
			this->cobbleTexture.bind2D();
                	this->use();

			this->setUniform("material.ambient", material.ambient);
                        this->setUniform("material.diffuseMap", material.diffuse);
                        this->setUniform("material.specular", material.specular);
                        this->setUniform("material.shininess", material.shininess);


                        this->setUniform("light.ambient", light.ambient);
                        this->setUniform("light.diffuse", light.diffuse);
                        this->setUniform("light.specular", light.specular);
                        this->setUniform("light.direction", light.direction);

			this->setUniform("light.constant", 1.0f);
                        this->setUniform("light.linear", 0.09f);
                        this->setUniform("light.quadratic", 0.032f);

			this->setUniform("objectColor", glm::vec3(0.643f, 0.643f, 0.612f));
                        this->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                        this->setUniform("lightPos", lightPos);
			this->setUniform("viewPos", camera.getPos());

			view = this->camera.getView();
			this->setUniform("view", view);


			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
			this->setUniform("projection", projection);

                	this->bindVao();

			int cols = 16;
			int rows = 16;
			model = glm::translate(model, glm::vec3((float)(-1*(rows/2)), 0.0f, (float)(-1*(cols/2))));

			for(int i=0; i<cols; i++){
				for(int j=0; j<rows; j++){
					if(j == 0)
						model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
					else
						model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
                        		this->setUniform("model", model);
                        		this->drawTriangles(0, 36);
				}
				model = glm::translate(model, glm::vec3((float)(-1*(rows-1)), 0.0f, 1.0f));
			}
		}
};
