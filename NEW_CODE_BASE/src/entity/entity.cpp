#include "../../main.h"
#include "../error/error.h"

#include "./entity.error.h"
#include "./entity.h"
		Entity::Entity(void) : WindowCtrl(){
			elementBufferObject = 0;
                	vertexBufferObject = 0;
                	vertexArrayObject = 0;
			mode = GL_POINTS;
                	drawStart = 0;
                	indexCount = 0;
                	cubeSize = 0;
                	mass = 0;
                	birthday = 0.0;
                	attributesDefined = false;
			vertecies = NULL;
			verteciesSize = 0;

		}

		Entity::Entity(const char *windowTitle) : WindowCtrl(windowTitle){
			Entity();
		}

		
		void Entity::setVertecies(GLfloat *obj, size_t s){
			this->vertecies = obj;	
			this->verteciesSize = s;
		}

		void Entity::pointMode(void){
			this->mode = GL_POINTS;
		}
		void Entity::triangleMode(void){
			this->mode = GL_TRIANGLES;
		}
		void Entity::lineMode(void){
			this->mode = GL_LINES;
		}

		void Entity::setDrawStart(int i){
			this->drawStart = i;
		}

		void Entity::setIndexCount(int i){
			this->indexCount = i;
		}

		//void Entity::use(void){
	//		shader.use();
	//	}

	/*	void Entity::addShaderAttributes(unsigned int i, int size, unsigned int stride, const void *offset){
			
			glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), &offset);
			glEnableVertexAttribArray(i);
		}*/
		void Entity::initShader(std::string vtxShader, std::string fragShader){
			try{
				this->shader.setVertexShader(vtxShader.c_str());
				this->shader.setFragmentShader(fragShader.c_str());
				this->shader.link();
			}catch(CoreException &e){
				throw EntityError(e, "initShader", "Failed to initalize shader");
			}
		}

		void Entity::generateObjectIds(bool arrayObj, bool vertBuff, bool eleObj){
                        if(arrayObj)
                                glGenVertexArrays(1, &vertexArrayObject);
                        if(vertBuff)
                                glGenBuffers(1, &vertexBufferObject);
                        if(eleObj)
                                glGenBuffers(1, &elementBufferObject);
                }

	//	void Entity::draw(void){
	//		glDrawArrays(mode, drawStart, indexCount);
	//	}

                /*void Entity::bindVao(void){
             		glBindVertexArray(vertexArrayObject);
                }

		void Entity::unbindVao(void){
                        glBindVertexArray(0);
                }

                void Entity::unbindVbo(void){
                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                }

                void Entity::bindVbo(void){
                        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
                }

                void Entity::bindEbo(void){
                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
                }*/
		
		/*void Entity::simpActive(void){
			generateObjectIds(true, true, false);
			bindVao();
			bindVbo();
		}
	
		void Entity::simpDeactive(void){
			unbindVbo();
			unbindVao();
		}*/

                /*void Entity::storeVertexData(GLsizeiptr size, const void * data, GLenum drawMode){
                        glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
                }
		
		void Entity::storeVertexData(GLsizeiptr size, const void * data){
                        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
                }*/
	


                void Entity::setElementArrayData(GLsizeiptr size, const GLvoid *indecies, GLenum drawMode){
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indecies, drawMode);
                }

		void Entity::destroy(void){
                        glDeleteVertexArrays(1, &vertexArrayObject);
                        glDeleteBuffers(1, &vertexBufferObject);
                        glDeleteBuffers(1, &elementBufferObject);
                        shader.deleteProgram();
                }
		
		void Entity::replaceBufferData(GLintptr offset, GLsizeiptr size, const void * data){
                        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
                }

		int Entity::getUniformLoc(const char *name){
                        return glGetUniformLocation(shader.programHandle, name);
                }

                void Entity::setUniform(const char *name, int val){
                        shader.setUniform(name, val);
                }
                void Entity::setUniform(const char *name, float val){
                        shader.setUniform(name, val);
                }
                void Entity::setUniform(const char *name, glm::mat4 val){
                        shader.setUniform(name, val);
                }
                void Entity::setUniform(const char *name, glm::vec3 val){
                        shader.setUniform(name, val);
                }
                void Entity::setUniform(const char *name, glm::vec2 val){
                        shader.setUniform(name, val);
                }
