class GraphicsTexture{
	private:
		int width = 0;
		int height = 0;
		int nrChannels = 0;
		unsigned char *data = NULL;
		unsigned int texture;
		
		int activeParam2D[16];
		GLenum paramName2D[16];
		GLfloat param2D[16];

		int textureUnit = 0;
	public:
		GraphicsTexture(){
			for(int i=0; i<16; i++){
				activeParam2D[i] = -1;
			}
		}

		void setTextureUnit(int id){
			if(id < 0 || id >= 16)
				id = 0;
			textureUnit = id;
		}
		bool add2DParameter(int id, GLenum pname, GLfloat param){
			if(id >= 16 || id < 0){
				return false;
			}
			paramName2D[id] = pname;
			param2D[id] = param;
			activeParam2D[id] = id;
			return true;
		}

		unsigned int loadCubemap(std::string faces[6]){
                        glGenTextures(1, &texture);
                        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
                        int width, height, nrChannels;
                        for (unsigned int i = 0; i < 6; i++){
                                unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &
                                nrChannels, 0);
                                if (data){
                                        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                                        );
                                        stbi_image_free(data);
                                }else{
                                        std::cout << "Cubemap texture failed to load at path: " << faces[i] <<
                                        std::endl;
                                        stbi_image_free(data);
                                }
                        }

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                        return texture;
                }

		bool loadTexture2D(const char *textureLoc){
			glGenTextures(1, &texture);
			glActiveTexture(GL_TEXTURE0+textureUnit);
			glBindTexture(GL_TEXTURE_2D, texture);

			for(int i=0; i<16; i++){
				if(activeParam2D[i] != -1)
					glTexParameteri(GL_TEXTURE_2D, paramName2D[i], param2D[i]);
			}
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(textureLoc, &width, &height, &nrChannels, 0);
			if(!data)
				return false;
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
			data = NULL;
			return true;
		}

		void destroy(void){
			unbind2D();
			if(data != NULL)
				free(data);
		}

		void bind2D(void){
			glActiveTexture(GL_TEXTURE0+textureUnit);
			glBindTexture(GL_TEXTURE_2D, texture);
		}

		void bindCube(void){
			glActiveTexture(GL_TEXTURE0+textureUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		}

		void unbind2D(void){
			glActiveTexture(GL_TEXTURE0+textureUnit);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void unbindCube(void){
			glActiveTexture(GL_TEXTURE0+textureUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
};
