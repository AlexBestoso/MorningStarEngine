#include "./shader.error.h"
class Shader{
	private:
		unsigned int vertexHandle = 0;
		unsigned int fragmentHandle = 0;
		char fragBuffer[10000];
		char vertBuffer[10000];
	public:
		unsigned int programHandle = 0;
		void setVertexShader(const char *fname){
                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0){
                        	std::string err = fname;
				err += "is empty or cannot be found.";
				throw ShaderError("addVertexShader", err);	
                        }
                        memset(vertBuffer, 0x0, 10000);

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
				throw ShaderError("addVertexShader", "Failed to open vertex shader file.");

                        read(fd, vertBuffer, st.st_size);
                        close(fd);
                        vertBuffer[st.st_size] = 0x00;

                        vertexHandle = glCreateShader(GL_VERTEX_SHADER);
			char *fbuf = vertBuffer;
                        glShaderSource(vertexHandle, 1, &fbuf, NULL);
                        glCompileShader(vertexHandle);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(vertexHandle, 512, NULL, infoLog);
                                vertexHandle = -1;
				throw ShaderError("addVertexShader", infoLog);
                        }
                }

		void setFragmentShader(const char *fname){
                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0)
                                throw ShaderError("addFragmentShader", "Failed to detect fragment shader file.");

			memset(fragBuffer, 0x0, 10000);

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
                                throw ShaderError("addFragmentShader", "Failed to open fragment shader file.");

                        read(fd, fragBuffer, st.st_size);
                        fragBuffer[st.st_size] = 0x00;
                        close(fd);

			char *fbuf = fragBuffer;
                        fragmentHandle  = glCreateShader(GL_FRAGMENT_SHADER);
                        glShaderSource(fragmentHandle, 1, &fbuf, NULL);
                        glCompileShader(fragmentHandle);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(fragmentHandle, 512, NULL, infoLog);
                                fragmentHandle = -1;
				throw ShaderError("addFragmentShader", infoLog);
                        }
                }

		void link(void){
                        programHandle  = glCreateProgram();
                      	glAttachShader(programHandle, vertexHandle);
                      	glAttachShader(programHandle, fragmentHandle);
                        
                        glLinkProgram(programHandle);

                        int success;
                        char infoLog[512];
                        glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
                        if (!success) {
                                glGetProgramInfoLog(programHandle, 512, NULL, infoLog);
                                glDeleteShader(vertexHandle);
                                glDeleteShader(fragmentHandle);
				throw ShaderError("linkShaders", infoLog);
                        }
			
			glDeleteShader(vertexHandle);
                        glDeleteShader(fragmentHandle);
                }

		void use(void){
                        glUseProgram(programHandle);
                }

                void deleteProgram(void){
                        glDeleteProgram(programHandle);
                }


		void getUniform(const char *varName, int *ret){
                        glGetUniformiv(glGetUniformLocation(programHandle, varName), 1, ret);
                }
                void setUniform(const char *varName, int val){
                        glUniform1i(glGetUniformLocation(programHandle, varName), val);
                }

                void setUniform(const char *varName, float val){
                        glUniform1f(glGetUniformLocation(programHandle, varName), val);
                }

                void setUniform(const char *varName, glm::mat4 val){
                        glUniformMatrix4fv(glGetUniformLocation(programHandle, varName), 1, GL_FALSE, &val[0][0]);
                }
                void setUniform(const char *varName, glm::vec3 val){
                        glUniform3fv(glGetUniformLocation(programHandle, varName), 1, &val[0]);
                }
                void setUniform(const char *varName, glm::vec2 val){
                        glUniform2fv(glGetUniformLocation(programHandle, varName), 1, &val[0]);
                }
};
