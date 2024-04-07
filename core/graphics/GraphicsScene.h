class GraphicsScene : public GraphicsObject{
	private:
		GLFWwindow* window = NULL;
		WavefrontImport importer;
		GraphicsTexture *objectTextures = NULL;
		size_t objectTextureCount = 0;
		obj_t * objs;
		

	public:
		obj_t *getObjs(void){
			return objs;
		}

		
		glm::vec3 lightPos;
		obj_data_t *getObjectPointer(void){
			return importer.obj;
		}
		void draw(void){
			this->bindVao();
			this->bindVbo();
                        this->use();

			glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f));
                        //model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);

			this->setUniform("material.ambient", material.ambient);
                        this->setUniform("material.diffuse", material.diffuse);
                        this->setUniform("material.specular", material.specular);
                        this->setUniform("material.shininess", material.shininess);


                        this->setUniform("light.ambient", light.ambient);
                        this->setUniform("light.diffuse", light.diffuse);
                        this->setUniform("light.specular", light.specular);
                        //this->setUniform("light.direction", light.direction);

                        //Flashling configs
                        this->setUniform("light.position", camera.cameraPosition);
                        this->setUniform("light.direction", camera.cameraFront);
                        this->setUniform("light.cuttOff", glm::cos(glm::radians(12.5f)));

                        this->setUniform("light.constant", light.constant);
                        this->setUniform("light.linear", light.linear);
                        this->setUniform("light.quadratic", light.quadratic);

                        this->setUniform("useTexture", 1);
                        this->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                        this->setUniform("lightPos", lightPos);
                        this->setUniform("viewPos", camera.getPos());

			view = camera.getView();
                        unsigned int viewLoc = this->getUniformLoc("view");
                        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                        unsigned int projectionLoc = this->getUniformLoc("projection");
                        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

			objs = this->getObjects();
			if(objs != NULL){
				for(int i=0; i<this->getObjectCount(); i++){
					if(objs[i].textureLocation != "")
						objectTextures[i].bind2D();
					this->storeVertexData(sizeof(float)*objs[i].glut_size, objs[i].glut_data, GL_STATIC_DRAW);
					glDrawArrays(GL_TRIANGLES, 0, objs[i].element_count);
					this->setUniform("model", model);

					if(objs[i].textureLocation != "")
						objectTextures[i].unbind2D();
				}
			}else{
				printf("Error, No objects loaded.\n");
			}
		}

		bool create(std::string sceneDir, std::string sceneName){
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

			if(!this->import(sceneDir, sceneName)){
			//if(!this->importer.importComplex(sceneDir, sceneName)){
                                printf("Failed to import the object '%s'.\n", sceneName.c_str());
                                return false;
                        }
			//objs = this->importer.getImportedObjects();

			this->setAttributePointer(0, 3, 11, (void *)0); // vertex
                        this->enableArrayAttribute(0);
			this->setAttributePointer(1, 2, 11, (void *)(3*sizeof(float))); // texture
                        this->enableArrayAttribute(1);
                        this->setAttributePointer(2, 3, 11, (void *)(5*sizeof(float))); // normals
                        this->enableArrayAttribute(2);
			this->setAttributePointer(3, 3, 11, (void *)(8*sizeof(float))); // material color
                        this->enableArrayAttribute(3);

			objectTextureCount = this->getObjectCount();
			objectTextures = new GraphicsTexture[objectTextureCount];
			objs = this->getObjects();

			for(int i=0; i<objectTextureCount; i++){
				if(objs[i].textureLocation == ""){
					continue;
				}
				GraphicsTexture test;
				test.add2DParameter(0, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        	test.add2DParameter(1, GL_TEXTURE_WRAP_T, GL_REPEAT);
                        	test.add2DParameter(2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        	test.add2DParameter(3, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        	test.setTextureUnit(0);
                        	if(!test.loadTexture2D(objs[i].textureLocation.c_str())){
                        	        printf("Failed to load texture for object '%s'\n", objs[i].name.c_str());
                        	        return false;
                        	}
				objectTextures[i] = test;
			}


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
                        setUniform("material.specularMap", 0);

			return true;
		}
};
