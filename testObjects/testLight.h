#define TEST_LIGHT_VERTEX_SIZE ((3*6)*6)
class TestLight : public GraphicsObject{
	private:
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		float vertices[TEST_TERRAIN_VERTEX_SIZE] = {
                        // Top Face
                         0.5f, 0.5f,  0.5f,
                         0.5f, 0.5f, -0.5f,
                        -0.5f, 0.5f, -0.5f,
                        -0.5f, 0.5f, -0.5f,
                        -0.5f, 0.5f,  0.5f,
                         0.5f, 0.5f,  0.5f,

                        // Bottom face
                         0.5f, -0.5f,  0.5f,
                         0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f,  0.5f,
                         0.5f, -0.5f,  0.5f,

                        // Left face
                        -0.5f,  0.5f,  0.5f,
                        -0.5f,  0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f,  0.5f,
                        -0.5f,  0.5f,  0.5f,

                        // Right face
                         0.5f,  0.5f,  0.5f,
                         0.5f,  0.5f, -0.5f,
                         0.5f, -0.5f, -0.5f,
                         0.5f, -0.5f, -0.5f,
                         0.5f, -0.5f,  0.5f,
                         0.5f,  0.5f,  0.5f,

                        // Front face
                        -0.5f, -0.5f,  0.5f,
                         0.5f, -0.5f,  0.5f,
                         0.5f,  0.5f,  0.5f,
                         0.5f,  0.5f,  0.5f,
                        -0.5f,  0.5f,  0.5f,
                        -0.5f, -0.5f,  0.5f,

                        // Back face
                        -0.5f, -0.5f, -0.5f,
                         0.5f, -0.5f, -0.5f,
                         0.5f,  0.5f, -0.5f,
                         0.5f,  0.5f, -0.5f,
                        -0.5f,  0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f,
                };
	public:
		bool create(void){
			if(!this->addVertexShader("./testObjects/testLight.vs", 0)){
                                printf("Failed to compile vertex shader.\n");
                                return false;
                        }

                        if(!this->addFragmentShader("./testObjects/testLight.fs", 1)){
                                printf("Failed to compile fragment shader\n");
                                return false;
                        }

                        if(!this->linkShaders()){
                                printf("Faild to link shader.\n");
                                return false;
                        }

			this->generateObjectIds(true, true, false);
                        this->bindVao();
                        this->bindVbo();
                        this->storeVertexData(sizeof(vertices), vertices, GL_STATIC_DRAW);

                        this->setAttributePointer(0, 3, 3, (void *)0);
                        this->enableArrayAttribute(0);

			model = glm::translate(model, glm::vec3(8.0f, 8.0f, 8.0f));
			return true;
		}

		glm::vec3 getPos(){
			return glm::vec3(model[3]);
		}

		void draw(void){
			this->use();
			view = this->camera.getView();
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
			this->setUniform("view", view);
			this->setUniform("projection", projection);
			this->setUniform("model", model);
			//model = glm::rotate(model, glm::radians(-33.0f), glm::vec3(0.5f, 0.5f, 0.5f));
			//model = glm::translate(model, glm::vec3((float)sin(glfwGetTime())*0.04, (float)cos(glfwGetTime())*0.04, 0.0f ));

			this->drawTriangles(0, 36);
		}
};
