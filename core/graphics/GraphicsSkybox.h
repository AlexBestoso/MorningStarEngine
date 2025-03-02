class GraphicsSkybox : public GraphicsObject{
	private:
		GLFWwindow *window = NULL;
		GraphicsTexture skyBoxTexture;
		GraphicsTexture skyBoxSpaceMap;

		

float skyboxVertices[108] = {
    // positions          
    -10.0f,  10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
     10.0f, -10.0f, -10.0f,
     10.0f, -10.0f, -10.0f,
     10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,

    -10.0f, -10.0f,  10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f, -10.0f,  10.0f,

     10.0f, -10.0f, -10.0f,
     10.0f, -10.0f,  10.0f,
     10.0f,  10.0f,  10.0f,
     10.0f,  10.0f,  10.0f,
     10.0f,  10.0f, -10.0f,
     10.0f, -10.0f, -10.0f,

    -10.0f, -10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
     10.0f,  10.0f,  10.0f,
     10.0f,  10.0f,  10.0f,
     10.0f, -10.0f,  10.0f,
    -10.0f, -10.0f,  10.0f,

    -10.0f,  10.0f, -10.0f,
     10.0f,  10.0f, -10.0f,
     10.0f,  10.0f,  10.0f,
     10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f, -10.0f,

    -10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f,  10.0f,
     10.0f, -10.0f, -10.0f,
     10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f,  10.0f,
     10.0f, -10.0f,  10.0f
};


	public:
		glm::vec3 lightPos;
		size_t getObjectCount(void){
			return objImporter.objCount;
		}
		obj_data_t *getObjectPointer(void){
			return objImporter.obj;
		}
		void draw(void){
			glDepthMask(GL_FALSE);
                        this->bindVao();
			this->bindVbo();
                        this->use();

			glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
                        model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(glm::mat3(camera.getView()));
                        glm::mat4 projection = glm::mat4(1.0f);


			this->setUniform("view", view);
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
			this->setUniform("projection", projection);

			this->skyBoxTexture.bindCube();

			glDrawArrays(GL_TRIANGLES, 0, 36);
			this->setUniform("model", model);

			this->skyBoxTexture.unbindCube();
			glDepthMask(GL_TRUE);
		}

		bool create(std::string skyFaces[6]){
			if(!this->addVertexShader("./glsl/vertexShaderSkybox.glsl", 0)){
                                printf("Failed to compile vertex shader.\n");
                                return false;
                        }

                        if(!this->addFragmentShader("./glsl/fragmentShaderSkybox.glsl", 1)){
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

                        this->storeVertexData(sizeof(float)*108, skyboxVertices, GL_STATIC_DRAW);
			this->setAttributePointer(0, 3, 3, (void *)0);
                        this->enableArrayAttribute(0);

			skyBoxTexture.loadCubemap(skyFaces);

			this->unbindVbo();
                        this->unbindVao();
                        this->use();

			this->material.ambient = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.specular = glm::vec3(0.5f, 0.5f, 0.3f);
                        this->material.shininess = 32.0f;

			this->light.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
                        this->light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
                        this->light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
                        this->light.constant = 1.0f;
                        this->light.linear = 0.09f;
                        this->light.quadratic = 0.032f;

                        // Flashlight configurations
                        this->light.position = camera.cameraPosition;
                        this->light.direction = camera.cameraFront;
                        this->light.cutOff = glm::cos(glm::radians(12.5f));

			setUniform("material.diffuseMap", 0);
                        setUniform("material.specularMap", 1);
			return true;
		}
};
