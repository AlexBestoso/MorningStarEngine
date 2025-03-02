class GraphicsScene : public GraphicsObject{
	private:
		const int id = 0;
		PhysicsScene physics;
		GLFWwindow* window = NULL;
		WavefrontImport importer;
		GraphicsTexture *objectTextures = NULL;
		size_t objectTextureCount = 0;
		obj_t * objs;

	public:
		glm::vec3 lightPos = glm::vec3(1.5833, 12.447, 5.0916);
		bool showSun = true;
		
		obj_data_t *getObjectPointer(void){
			return importer.obj;
		}
		void draw(void){
			this->bindVao();
			this->bindVbo();
                        this->use();

			glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
                        //model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);

                        this->setUniform("useTexture", 0);
                        this->setUniform("lightColor", glm::vec3(0.963f, 0.988f, 0.939f));
                        this->setUniform("lightPos", lightPos);
                        this->setUniform("viewPos", camera.getPos());

			view = camera.getView();
                        unsigned int viewLoc = this->getUniformLoc("view");
                        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                        unsigned int projectionLoc = this->getUniformLoc("projection");
                        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

			for(int i=0; i<this->objImporter.objectCount; i++){
				this->setUniform("material.ambient", this->objImporter.waveObjects[i].material.mtl.Ka);
				this->setUniform("material.diffuse", this->objImporter.waveObjects[i].material.mtl.Kd);
				this->setUniform("material.specular", this->objImporter.waveObjects[i].material.mtl.Ks);
				this->setUniform("material.shininess", this->objImporter.waveObjects[i].material.mtl.Ns);
				this->setUniform("material.dissolve", this->objImporter.waveObjects[i].material.mtl.d);
				/*if(objs[i].textureLocation != ""){
					objectTextures[i].bind2D();
					this->setUniform("useTexture", 1);
				}else{
					this->setUniform("useTexture", 0);
				}*/
				
				this->objImporter.serializeObject(i);
				this->storeVertexData(sizeof(float)*this->objImporter.glObjBufferSize, this->objImporter.glObjBuffer, GL_DYNAMIC_DRAW);
				glDrawArrays(GL_TRIANGLES, 0, this->objImporter.waveObjects[i].getFCount());
				this->setUniform("model", model);
				//	if(objs[i].textureLocation != "")
				//		objectTextures[i].unbind2D();
			}
		}

		bool create(std::string sceneDir, std::string sceneName){
			int err = 0;
			if((err = this->createShaders("./glsl/vertexShaderScene.glsl", "./glsl/fragmentShaderScene.glsl")) != 0){
				switch(err){
					case 1: printf("Vertex Shader error.\n");break;
					case 2: printf("Fragment shader error.\n");break;
					default: printf("Shader Linking error.\n");break;
				}
				return false;
			}

			this->generateObjectIds(true, true, false);
                        this->bindVao();
                        this->bindVbo();

			if(!this->import(sceneDir, sceneName)){
                                printf("Failed to import the object '%s'.\n", sceneName.c_str());
                                return false;
                        }

			this->setAttributePointer(0, 3, 11, (void *)0); // vertex
                        this->enableArrayAttribute(0);
			this->setAttributePointer(1, 2, 11, (void *)(3*sizeof(float))); // texture
                        this->enableArrayAttribute(1);
                        this->setAttributePointer(2, 3, 11, (void *)(5*sizeof(float))); // normals
                        this->enableArrayAttribute(2);
			this->setAttributePointer(3, 3, 11, (void *)(8*sizeof(float))); // material color
                        this->enableArrayAttribute(3);

			//objectTextureCount = this->getObjectCount();
			//objectTextures = new GraphicsTexture[objectTextureCount];
			//objs = this->getObjects();

			/*for(int i=0; i<objectTextureCount; i++){
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
                        	}else{
				}
				objectTextures[i] = test;
			}*/


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

		void processCollision(glm::vec3 objectPos){
			
		}
};
