typedef struct GraphicsMaterial{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
}graphics_material_t;

typedef struct GraphicsLight{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant;
        float linear;
        float quadratic;
	float cutOff;
}graphics_light_t;

class GraphicsObject{
	private:
		unsigned int elementBufferObject = 0;
		unsigned int vertexBufferObject = 0;
		unsigned int vertexArrayObject = 0;
		GraphicsTexture texture;
		GraphicsShader shader;
		obj_t *objects = NULL;
		size_t objectsSize = 0;
		
	public:
		struct GuiEngineStruct ges;
		GraphicsCamera camera;
		graphics_material_t material;
		graphics_light_t light;
		WavefrontImport objImporter;

		virtual void setGES(struct GuiEngineStruct ges){
			this->ges = ges;
			camera.ges = ges;
		}
		void setGes(struct GuiEngineStruct ges){
			setGES(ges);
		}

		size_t getObjectCount(void){
			return objectsSize;
		}

		obj_t *getObjects(void){
			return objects;
		}

		bool updateObject(obj_t newObj, int objIdx){
			if(objIdx <= -1 || objIdx >= this->objectsSize || objects == NULL)
				return false;
			
			this->objects[objIdx] = newObj;
			return true;
		}
		
		bool import(std::string directory, std::string name){
			if(directory == "" || name == "")
				return false;
			objImporter.setFile(directory, name);
			
			if(!objImporter.readFile(objImporter.buildFilePath().c_str())){
				printf("Failed to read object file %s\n", objImporter.buildFilePath().c_str());
			}
			
			objectsSize = objImporter.countObjects();
			if(objectsSize <= 0)
				return false;
			
			objImporter.isoloateObjects();
			objImporter.convertObjects();
			printf("IMPORT COMPLETED\n");
			//objImporter.serializeObjects();
			
			

		/*	objects = new obj_t[objectsSize];
			if(!objImporter.objStat(objects, objectsSize))
				return false;
			if(!objImporter.loadMaterial(objects, objectsSize))
				return false;
			if(!objImporter.loadData(objects, objectsSize))
				return false;*/
			return true;
		}

		bool addVertexShader(const char *fileLoc, int id){
			return shader.addVertexShader(fileLoc, id);
		}

		bool addFragmentShader(const char *fileLoc, int id){
			return shader.addFragmentShader(fileLoc, id);
		}

		bool linkShaders(void){
			return shader.linkShaders();
		}

		void generateObjectIds(bool arrayObj, bool vertBuff, bool eleObj){
			if(arrayObj)
				glGenVertexArrays(1, &vertexArrayObject);
			if(vertBuff)
				glGenBuffers(1, &vertexBufferObject);
			if(eleObj)
				glGenBuffers(1, &elementBufferObject);
		}

		void bindVao(void){
			  glBindVertexArray(vertexArrayObject);
		}
		
		void unbindVao(void){
			glBindVertexArray(0);
		}

		void unbindVbo(void){
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		
		void bindVbo(void){
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		}

		void bindEbo(void){
                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
                }

		void storeVertexData(GLsizeiptr size, const GLvoid *vertices, GLenum drawMode){
			glBufferData(GL_ARRAY_BUFFER, size, vertices, drawMode);
		}

		void setElementArrayData(GLsizeiptr size, const GLvoid *indecies, GLenum drawMode){
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indecies, drawMode);
                }

		void setAttributePointer(int attributeId, int vertexSize, int strideSize, void* offset){
                        glVertexAttribPointer(attributeId, vertexSize, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), offset);
                }

		void enableArrayAttribute(int id){
                        glEnableVertexAttribArray(id);
                }

		unsigned int getUniformLoc(const char *name){
			return glGetUniformLocation(shader.programHandle, name);
		}

		void setUniform(const char *name, int val){
		        shader.setUniform(name, val);
		}
		void setUniform(const char *name, float val){
		        shader.setUniform(name, val);
		}
		void setUniform(const char *name, glm::mat4 val){
			shader.setUniform(name, val);
		}
		void setUniform(const char *name, glm::vec3 val){
			shader.setUniform(name, val);
		}
		void setUniform(const char *name, glm::vec2 val){
			shader.setUniform(name, val);
		}

		void destroy(void){
			glDeleteVertexArrays(1, &vertexArrayObject);
			glDeleteBuffers(1, &vertexBufferObject);
			glDeleteBuffers(1, &elementBufferObject);
			shader.deleteProgram();
			if(objects != NULL){
				for(int i=0; i<objectsSize; i++){
					if(objects[i].glut_data != NULL){
						delete[] objects[i].glut_data;
						objects[i].glut_size = 0;
					}
				}
				delete[] objects;
				objects = NULL;
			}
			objectsSize = 0;
		}

		void use(void){
			this->shader.use();
		}

		void drawTriangles(int a, int vertexCount){
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}

		void directDraw(float *data, size_t dataSize, float strideSize, GLenum drawMode){
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
                        this->setUniform("viewPos", camera.getPos());

                        view = camera.getView();
                        unsigned int viewLoc = this->getUniformLoc("view");
                        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                        unsigned int projectionLoc = this->getUniformLoc("projection");
                        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

			this->storeVertexData(sizeof(float)*dataSize, data, GL_STATIC_DRAW);
			glDrawArrays(drawMode, 0, strideSize);
		}

		virtual void draw(void){
			
		}

		virtual bool create(void){
			return false;	
		}
};
