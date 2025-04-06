#include "../../main.h"
#include "../error/error.h"
#include "./shader.error.h"
#include "./shader.h"
		Shader::Shader(void){
			this->programHandle = 0;
			this->vertexHandle = 0;
			this->fragmentHandle = 0;
			for(int i=0; i<10000; i++){
				fragBuffer[i] = 0;
				vertBuffer[i] = 0;
				geometryBuffer[i] = 0;
			}

		}

		Shader::~Shader(){
			/*glDeleteShader(vertexHandle);
                        glDeleteShader(geometryHandle);
                        glDeleteShader(fragmentHandle);

			glDetachShader(programHandle, vertexHandle);
                       	glDetachShader(programHandle, geometryHandle);
                        glDetachShader(programHandle, fragmentHandle);
		
			deleteProgram();*/
		}
		void Shader::setGeometryShader(const char *fname){
			printf("Loading geometry shader '%s' size ", fname);
                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0){
                                std::string err = fname;
                                err += "is empty or cannot be found.";
                                throw ShaderError("addGeometryShader", err);
                        }
                        size_t fileSize = 0;
                        for(int i=0; i<st.st_size; i++) fileSize++;
                        printf("%ld bytes\n", fileSize);

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
                                throw ShaderError("addGeometryShader", "Failed to open shader file.");
                        if(read(fd, geometryBuffer, fileSize) != st.st_size){
                                close(fd);
                                throw ShaderError("addGeometryShader", "Failed to read shader file.\n");
                        }
                        close(fd);

			geometryHandle = glCreateShader(GL_GEOMETRY_SHADER);
                        if(geometryHandle == 0)
                                throw ShaderError("addFragmentShader", "Failed to create shader.");
                        const GLchar *fbuf = (const GLchar*)&geometryBuffer;

                        glShaderSource(geometryHandle, 1, &fbuf, NULL);
                        glCompileShader(geometryHandle);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(geometryHandle, GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(geometryHandle, 512, NULL, infoLog);
                                vertexHandle = 0;
                                throw ShaderError("addGeometryShader", infoLog);
                        }
		}
		void Shader::setVertexShader(const char *fname){
			printf("Loading vertex shader '%s' size ", fname);
                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0){
                        	std::string err = fname;
				err += "is empty or cannot be found.";
				throw ShaderError("addVertexShader", err);	
                        }
			size_t fileSize = 0;
			for(int i=0; i<st.st_size; i++) fileSize++;
			printf("%ld bytes\n", fileSize);

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
				throw ShaderError("addVertexShader", "Failed to open vertex shader file.");

                        if(read(fd, vertBuffer, fileSize) != st.st_size){
				close(fd);
				throw ShaderError("addVertexShader", "Failed to read vertex shader file.\n");
			}
                        close(fd);
			
                        vertexHandle = glCreateShader(GL_VERTEX_SHADER);
			if(vertexHandle == 0)
				throw ShaderError("addFragmentShader", "Failed to create shader.");
			const GLchar *fbuf = (const GLchar*)&vertBuffer;
			
                        glShaderSource(vertexHandle, 1, &fbuf, NULL);
                        glCompileShader(vertexHandle);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(vertexHandle, 512, NULL, infoLog);
                                vertexHandle = 0;
				throw ShaderError("addVertexShader", infoLog);
                        }
                }

		void Shader::setFragmentShader(const char *fname){
			printf("Loading fragmet shader '%s' size ", fname);
                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0)
                                throw ShaderError("addFragmentShader", "Failed to detect fragment shader file.");

			size_t fileSize = 0;
                        for(int i=0; i<st.st_size; i++) fileSize++;
			printf("%ld bytes\n", fileSize);

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
                                throw ShaderError("addFragmentShader", "Failed to open fragment shader file.");

                        if(read(fd, fragBuffer, fileSize) != st.st_size){
				close(fd);
				throw ShaderError("addFragmentShader", "Failed to read fragment shader file.");
			}
                        close(fd);

			
                        fragmentHandle  = glCreateShader(GL_FRAGMENT_SHADER);
			if(fragmentHandle == 0)
				throw ShaderError("addFragmentShader", "Failed to create shader.");
			const GLchar *fbuf = (const GLchar*)&fragBuffer;

                        glShaderSource(fragmentHandle, 1, &fbuf, NULL);
                        glCompileShader(fragmentHandle);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(fragmentHandle, 512, NULL, infoLog);
                                fragmentHandle = 0;
				throw ShaderError("addFragmentShader", infoLog);
                        }
                }

		void Shader::link(void){
                        programHandle  = glCreateProgram();
			if(programHandle == 0)
				throw ShaderError("link", "failed to create gl program handle.");
                      	glAttachShader(programHandle, vertexHandle);
                      	glAttachShader(programHandle, geometryHandle);
                      	glAttachShader(programHandle, fragmentHandle);
                        if(programHandle == 0)
				throw ShaderError("link", "Attach failure.");

                        glLinkProgram(programHandle);
                        
                        int success;
                        char infoLog[512];
                        glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
                        if (!success) {
                                glGetProgramInfoLog(programHandle, 512, NULL, infoLog);
                                glDeleteShader(vertexHandle);
				glDeleteShader(geometryHandle);
                                glDeleteShader(fragmentHandle);
				throw ShaderError("linkShaders", infoLog);
                        }

			//glDetachShader(programHandle, vertexHandle);
                       // glDetatchShader(programHandle, geometryHandle);
			//glDetachShader(programHandle, fragmentHandle);
			
			glDeleteShader(vertexHandle);
                        glDeleteShader(geometryHandle);
                        glDeleteShader(fragmentHandle);
			if(programHandle == 0)
				throw ShaderError("link", "Linking Failed");

                }

		void Shader::use(void){
                        glUseProgram(programHandle);
                }

                void Shader::deleteProgram(void){
                        glDeleteProgram(programHandle);
                }


		void Shader::getUniform(const char *varName, int *ret){
			GLint loc = glGetUniformLocation(programHandle, varName);
			GLuint trueLoc = 0;
			for(int i=0; i<loc; i++) trueLoc++;
                        glGetUniformiv(trueLoc, 1, ret);
                }
                void Shader::setUniform(const char *varName, int val){
                        glUniform1i(glGetUniformLocation(programHandle, varName), val);
                }

                void Shader::setUniform(const char *varName, float val){
			if(programHandle == 0)
				throw ShaderError("setUniform", "Invalid program handle.");
			GLint uni = glGetUniformLocation(programHandle, varName);
			switch(uni){
				case GL_INVALID_VALUE:
					throw ShaderError("setUniform", "Invalid value");
				case GL_INVALID_OPERATION:
					throw ShaderError("setUnitform", "Invalid operation");
			}
                        glUniform1f(uni, val);
                }

                void Shader::setUniform(const char *varName, glm::mat4 val){
                        glUniformMatrix4fv(glGetUniformLocation(programHandle, varName), 1, GL_FALSE, &val[0][0]);
                }
                void Shader::setUniform(const char *varName, glm::vec3 val){
                        glUniform3fv(glGetUniformLocation(programHandle, varName), 1, &val[0]);
                }
                void Shader::setUniform(const char *varName, glm::vec2 val){
                        glUniform2fv(glGetUniformLocation(programHandle, varName), 1, &val[0]);
                }
