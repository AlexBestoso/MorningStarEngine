#include "./entity.error.h"
class Entity{
	private:
		GLenum mode = GL_POINTS;
		int drawStart = 0;
		int indexCount = 0;

		Shader shader;

		int cubeSize = 0;
		int mass = 0;
		double birthday = 0.0;
		
		bool attributesDefined = false;
		
	public:
		unsigned int elementBufferObject = 0;
                unsigned int vertexBufferObject = 0;
                unsigned int vertexArrayObject = 0;

		void pointMode(void){
			this->mode = GL_POINTS;
		}
		void triangleMode(void){
			this->mode = GL_TRIANGLES;
		}
		void lineMode(void){
			this->mode = GL_LINES;
		}

		void setDrawStart(int i){
			this->drawStart = i;
		}

		void setIndexCount(int i){
			this->indexCount = i;
		}

		void use(void){
			shader.use();
		}

		void addShaderAttributes(int i, int size, int stride, int offset){
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const void *)&offset);
		}
		void initShader(std::string vtxShader, std::string fragShader){
			try{
				this->shader.setVertexShader(vtxShader.c_str());
				this->shader.setFragmentShader(fragShader.c_str());
				this->shader.link();
			}catch(CoreException &e){
				throw EntityError(e, "initShader", "Failed to initalize shader");
			}
		}

		void generateObjectIds(bool arrayObj, bool vertBuff, bool eleObj){
                        if(arrayObj)
                                glGenVertexArrays(1, &vertexArrayObject);
                        if(vertBuff)
                                glGenBuffers(1, &vertexBufferObject);
                        if(eleObj)
                                glGenBuffers(1, &elementBufferObject);
                }

		virtual void draw(void){
			glDrawArrays(mode, drawStart, indexCount);
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
		
		void simpActive(void){
			generateObjectIds(true, true, false);
			bindVao();
			bindVbo();
		}
	
		void simpDeactive(void){
			unbindVbo();
			unbindVao();
		}

                void storeVertexData(GLsizeiptr size, const void * data, GLenum drawMode){
                        glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
                }
		
		void storeVertexData(GLsizeiptr size, const void * data){
                        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
                }
	


                void setElementArrayData(GLsizeiptr size, const GLvoid *indecies, GLenum drawMode){
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indecies, drawMode);
                }

		void destroy(void){
                        glDeleteVertexArrays(1, &vertexArrayObject);
                        glDeleteBuffers(1, &vertexBufferObject);
                        glDeleteBuffers(1, &elementBufferObject);
                        shader.deleteProgram();
                }
		
		void replaceBufferData(GLintptr offset, GLsizeiptr size, const void * data){
                        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
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
};
