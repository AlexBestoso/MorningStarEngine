class GraphicsShader{
	private:
		unsigned int shaderHandles[16] = {0};
		int activeShaders[16] = {-1};
	public:
		unsigned int programHandle;
		GraphicsShader(){
			for(int i=0; i<16; i++)
				activeShaders[i] = -1;
		}
		bool addVertexShader(const char *fname, int shaderId){
			if(shaderId >= 16 || shaderId < 0){
				printf("Invalid Shader ID.\n");
				return false;
			}
                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0){
				printf("%s is empty or cannot be found.\n", fname);
                                return false;
			}
                        char *fbuf = new char[st.st_size+1];
                        memset(fbuf, 0x0, st.st_size);

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
                                return false;

                        read(fd, fbuf, st.st_size);
                        close(fd);
                        fbuf[st.st_size] = 0x00;

                        shaderHandles[shaderId] = glCreateShader(GL_VERTEX_SHADER);
                        glShaderSource(shaderHandles[shaderId], 1, &fbuf, NULL);
                        glCompileShader(shaderHandles[shaderId]);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(shaderHandles[shaderId], GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(shaderHandles[shaderId], 512, NULL, infoLog);
                                printf("ERROR : %s\n", infoLog);
				activeShaders[shaderId] = -1;
                                return false;
                        }
			
			activeShaders[shaderId] = shaderId;
                        return true;
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
		
		bool addFragmentShader(const char *fname, int shaderId){
			if(shaderId >= 16 || shaderId < 0){
                                printf("Invalid Shader ID.\n");
                                return false;
                        }

                        struct stat st;
                        stat(fname, &st);
                        if(st.st_size <= 0)
                                return false;
                        char *fbuf = new char[st.st_size+1];

                        int fd = open(fname, O_RDONLY);
                        if(!fd)
                                return false;

                        read(fd, fbuf, st.st_size);
                        fbuf[st.st_size] = 0x00;
                        close(fd);

                        shaderHandles[shaderId]  = glCreateShader(GL_FRAGMENT_SHADER);
                        glShaderSource(shaderHandles[shaderId], 1, &fbuf, NULL);
                        glCompileShader(shaderHandles[shaderId]);

                        int success;
                        char infoLog[512];
                        glGetShaderiv(shaderHandles[shaderId], GL_COMPILE_STATUS, &success);
                        if (!success){
                                glGetShaderInfoLog(shaderHandles[shaderId], 512, NULL, infoLog);
                                printf("ERROR : %s\n", infoLog);
				activeShaders[shaderId] = -1;
                                return false;
                        }
			activeShaders[shaderId] = shaderId;
                        return true;
                }

		bool linkShaders(void){
                        programHandle  = glCreateProgram();
                        for(int i=0; i<16; i++){
				if(activeShaders[i] != -1){
                                	glAttachShader(programHandle, shaderHandles[i]);
				}
			}
                        glLinkProgram(programHandle);

                        int success;
                        char infoLog[512];
                        glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
                        if (!success) {
                                glGetProgramInfoLog(programHandle, 512, NULL, infoLog);
                                printf("ERROR : %s\n", infoLog);
                                for(int i=0; i<16; i++){
					if(activeShaders[i] != -1)
	                                        glDeleteShader(shaderHandles[i]);
				}
                                return false;
                        }
                        for(int i=0; i<16; i++)
                                if(activeShaders[i] != -1)
                      			glDeleteShader(shaderHandles[i]);
                        return true;
                }


		void use(void){
			glUseProgram(programHandle);
		}

		void deleteProgram(void){
			glDeleteProgram(programHandle);
		}
};
