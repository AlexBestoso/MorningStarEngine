class GraphicsScene : public GraphicsObject{
	private:
		GLFWwindow* window = NULL;
		WavefrontImport importer;

	public:
		glm::vec3 lightPos;
		size_t getObjectCount(void){
			return importer.objCount;
		}
		obj_data_t *getObjectPointer(void){
			return importer.obj;
		}
		void draw(void){
			this->bindVao();
                        this->use();

			glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f));
                        model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);
/*
			this->setUniform("material.ambient", material.ambient);
                        this->setUniform("material.diffuse", material.diffuse);
                        this->setUniform("material.specular", material.specular);
                        this->setUniform("material.shininess", material.shininess);

			this->setUniform("light.ambient", light.ambient);
                        this->setUniform("light.diffuse", light.diffuse);
                        this->setUniform("light.specular", light.specular);

			this->setUniform("light.position", camera.cameraPosition);
                        this->setUniform("light.direction", camera.cameraFront);
                        this->setUniform("light.cuttOff", glm::cos(glm::radians(12.5f)));

                        this->setUniform("light.constant", light.constant);
                        this->setUniform("light.linear", light.linear);
                        this->setUniform("light.quadratic", light.quadratic);
*/
                        this->setUniform("useTexture", 1);
  /*                      this->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                        this->setUniform("lightPos", lightPos);
                        this->setUniform("viewPos", camera.getPos())*/;

			view = camera.getView();
                        unsigned int viewLoc = this->getUniformLoc("view");
                        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                        unsigned int projectionLoc = this->getUniformLoc("projection");
                        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, importer.objCount);
			this->setUniform("model", model);
		}

		bool create(std::string sceneLoc, std::string sceneMtlLoc){
			if(!this->addVertexShader("./glsl/vertexShaderScene.glsl", 0)){
                                printf("Failed to compile vertex shader.\n");
                                return false;
                        }

                        if(!this->addFragmentShader("./glsl/fragmentShaderScene.glsl", 1)){
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

			this->importer.setMaterialFile(sceneMtlLoc);
			if(!this->importer.import(sceneLoc.c_str())){
                                printf("Failed to import Cube object.\n");
                                return false;
                        }
                        this->storeVertexData(sizeof(float)*this->importer.glObjBufferSize, this->importer.glObjBuffer, GL_STATIC_DRAW);

			this->setAttributePointer(0, 3, 11, (void *)0);
                        this->enableArrayAttribute(0);
			this->setAttributePointer(1, 2, 11, (void *)(3*sizeof(float)));
                        this->enableArrayAttribute(1);
                        this->setAttributePointer(2, 3, 11, (void *)(5*sizeof(float)));
                        this->enableArrayAttribute(2);
			this->setAttributePointer(3, 3, 11, (void *)(8*sizeof(float)));
                        this->enableArrayAttribute(3);


			this->unbindVbo();
			this->unbindVao();

			this->use();

/*			this->material.ambient = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.specular = glm::vec3(0.5f, 0.5f, 0.3f);
                        this->material.shininess = 32.0f;

			this->light.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
                        //this->light.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
                        //this->light.direction = glm::vec3(-8.0f, -8.0f, -8.0f);
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
			*/
			return true;
		}
};
