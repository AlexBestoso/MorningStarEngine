class FpsPlayer : public GraphicsObject{
	private:
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
	public:
		bool create(void){
			if(!this->addVertexShader("./testObjects/fpsPlayer.vs", 0)){
                                printf("Failed to compile vertex shader.\n");
                                return false;
                        }

                        if(!this->addFragmentShader("./testObjects/fpsPlayer.fs", 1)){
                                printf("Failed to compile fragment shader\n");
                                return false;
                        }

                        if(!this->linkShaders()){
                                printf("Faild to link shader.\n");
                                return false;
                        }

			return true;
		}
		
		bool jumping = false;
		float jumpStrength = 0.05;
		float jumpHeight = 1.75;
		float jumpBase = 0;
		float jumpPeak = 0;
		float cameraSpeed = 0.05f;
		void fpsControls(void){
                        glm::vec3 front;
                        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
                        front.y = sin(glm::radians(pitch));
                        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

                        this->camera.cameraFront = glm::normalize(front);
                        if (gui_engine_global.keyboard.key_w){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition += cameraSpeed * this->camera.cameraFront;
				this->camera.cameraPosition.y = y;
			}
                        if (gui_engine_global.keyboard.key_s){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition -= cameraSpeed * this->camera.cameraFront;
				this->camera.cameraPosition.y = y;
			}
                        if (gui_engine_global.keyboard.key_a){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition -= glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * cameraSpeed;
				this->camera.cameraPosition.y = y;
			}
                        if (gui_engine_global.keyboard.key_d){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition += glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * cameraSpeed;
				this->camera.cameraPosition.y = y;
			}

			
			if(isnan(this->camera.cameraPosition.x)){
				this->camera.cameraPosition.x = 0.000001;
			}
			if(isnan(this->camera.cameraPosition.y)){
				this->camera.cameraPosition.y = 0.000001;
			}
			if(isnan(this->camera.cameraPosition.z)){
				this->camera.cameraPosition.z = 0.000001;
			}

			if(gui_engine_global.keyboard.key_space && this->camera.cameraPosition.y <= 0){
				jumping = true;
				jumpPeak = this->camera.cameraPosition.y + jumpHeight;
			}
			
			if(!jumping){
                        	if(this->camera.cameraPosition.y > 0){
                        	        this->camera.cameraPosition.y -= 0.05;
                        	}
			}else if(this->camera.cameraPosition.y < jumpPeak){
				this->camera.cameraPosition.y += jumpStrength;
			}else{
				jumping = false;
			}
                        if(this->camera.cameraPosition.y < 0){
                                this->camera.cameraPosition.y = 0;
                        }
                }
		void draw(void){
			fpsControls();
			view = camera.focus();
			//this->setUniform("fpsview", view);

			//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
			//this->setUniform("fpsperspective", projection);
			
			//this->drawTriangles(0, 36);
		}
};
