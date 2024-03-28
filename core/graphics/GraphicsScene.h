class GraphicsScene : public GraphicsObject{
	private:
		GLFWwindow* window = NULL;
		WavefrontImport importer;
		GraphicsTexture *objectTextures = NULL;
		size_t objectTextureCount = 0;
		obj_t *objs = NULL;

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
			this->bindVbo();
                        this->use();

			glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f));
                        model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);
                        this->setUniform("useTexture", 1);

			view = camera.getView();
                        unsigned int viewLoc = this->getUniformLoc("view");
                        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                        unsigned int projectionLoc = this->getUniformLoc("projection");
                        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

			if(objs != NULL){
				for(int i=0; i<this->importer.getObjectCount(); i++){
					this->storeVertexData(sizeof(float)*objs[i].buffer_size, this->importer.glObjBuffer+objs[i].buffer_start, GL_STATIC_DRAW);
					glDrawArrays(GL_TRIANGLES, 0, objs[i].buffer_count);
					this->setUniform("model", model);
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

			if(!this->importer.importComplex(sceneDir, sceneName)){
                                printf("Failed to import Cube object.\n");
                                return false;
                        }
			objs = this->importer.getImportedObjects();

			this->setAttributePointer(0, 3, 11, (void *)0); // vertex
                        this->enableArrayAttribute(0);
			this->setAttributePointer(1, 2, 11, (void *)(3*sizeof(float))); // texture
                        this->enableArrayAttribute(1);
                        this->setAttributePointer(2, 3, 11, (void *)(5*sizeof(float))); // normals
                        this->enableArrayAttribute(2);
			this->setAttributePointer(3, 3, 11, (void *)(8*sizeof(float))); // material color
                        this->enableArrayAttribute(3);


			this->unbindVbo();
			this->unbindVao();

			this->use();

			return true;
		}
};
