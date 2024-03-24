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
		unsigned int elementBufferObject;
		unsigned int vertexBufferObject;
		unsigned int vertexArrayObject;
		unsigned int *vIndecies = NULL;
		GraphicsTexture texture;
		float *vertices = NULL;
		GraphicsShader shader;
	public:
		GraphicsCamera camera;
		graphics_material_t material;
		graphics_light_t light;
		WavefrontImport objImporter;

		size_t calcVertexFileSize(std::string vertexFile){
                        size_t ret = 0;

                        return ret;
                }
                void loadVertexFile(std::string vertextFile, float *ret, size_t retSize){

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
		}

		void use(void){
			this->shader.use();
		}

		void drawTriangles(int a, int vertexCount){
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}

		virtual void draw(void){
			
		}

		virtual bool create(void){
			return false;	
		}
};
