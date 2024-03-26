class FpsPlayer : public GraphicsObject{
	private:
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		obj_data_t *sceneData = NULL;
		size_t sceneDataSize = 0;

		float gravity = 0.05;
		float playerHeight = 0.10;
		float playerWidth = 1;
		float playerBredth = 1;
		bool grounded = false;
		bool inXzBound = false;

		void calculateCollision(void){
			grounded = false;
			if(sceneData == NULL || sceneDataSize <= 0)
				return;
			glm::vec3 trianglePoints[3];
			glm::vec3 camera = this->camera.getPos();
			for(int i=0; i<sceneDataSize; i++){
				trianglePoints[i%3] = glm::vec3(sceneData[i].vertex[0], sceneData[i].vertex[1], sceneData[i].vertex[2]);
				if((i%3) == 2){
					float maxX=0, maxZ=0, minX=0, minZ=0, minY=0, maxY=0;
					minX = trianglePoints[0].x;
					maxX = trianglePoints[0].x;
					minZ = trianglePoints[0].z;
					maxZ = trianglePoints[0].z;
					minY = trianglePoints[0].y;
					maxY = trianglePoints[0].y;
					for(int j=1; j<3; j++){
						if(trianglePoints[j].x < minX){
							minX = trianglePoints[j].x;
						}
						if(trianglePoints[j].x > maxX){
							maxX = trianglePoints[j].x;
						}

						if(trianglePoints[j].z < minZ){
							minZ = trianglePoints[j].z;
						}
						if(trianglePoints[j].z > maxZ){
							maxZ = trianglePoints[j].z;
						}

						if(trianglePoints[j].y < minY){
                                                        minY = trianglePoints[j].y;
                                                }
                                                if(trianglePoints[j].y > maxY){
                                                        maxY = trianglePoints[j].y;
                                                }
					}
					
					glm::vec3 minPoint = glm::vec3(minX, minY, minZ);
					glm::vec3 maxPoint = glm::vec3(maxX, maxY, maxZ);

					//glm::vec3 test = glm::cross(glm::vec3(maxX-minX, maxY-minY, maxZ-minZ), camera);
					inXzBound = false;
					if((camera.x >= minPoint.x && camera.x <= maxPoint.x) &&
					   (camera.z >= minPoint.z && camera.z <= maxPoint.z)){
						inXzBound = true;
					}
					if(inXzBound && (camera.y >= minY && camera.y <= minY+playerHeight) && !jumping){
						camera.y = minY;
						this->camera.setPos(camera);
						grounded = true;
					}
				}
			}	
		}
	public:
		void setSceneData(obj_data_t *d, size_t s){
			sceneData = d;
			sceneDataSize = s;
		}
		bool create(void){
	/*		if(!this->addVertexShader("./testObjects/fpsPlayer.vs", 0)){
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
*/
			return true;
		}
		
		bool jumping = false;
		float jumpStrength = 0.05;
		float jumpHeight = 1.75;
		float jumpBase = 0;
		float jumpPeak = 0;
		float cameraSpeed = 0.05f;
		void fpsControls(void){
			/*
			 * Account for player's head position.
			 * */
                        glm::vec3 front;
                        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
                        front.y = sin(glm::radians(pitch));
                        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
                        this->camera.cameraFront = glm::normalize(front);

			/*
			 * Manage horizontal movement
			 * */
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

			// Error correction for invalid camera possitions
			if(isnan(this->camera.cameraPosition.x)){
				this->camera.cameraPosition.x = 0.000001;
			}
			if(isnan(this->camera.cameraPosition.y)){
				this->camera.cameraPosition.y = 0.000001;
			}
			if(isnan(this->camera.cameraPosition.z)){
				this->camera.cameraPosition.z = 0.000001;
			}


			/*
			 * Manage jump physics
			 * */
			if(gui_engine_global.keyboard.key_space){
				jumping = true;
			}else{
				jumping = false;
			}
			
			calculateCollision();
			if(!jumping && !grounded){
                      		this->camera.cameraPosition.y -= this->gravity;
			}else{
				this->camera.cameraPosition.y += jumpStrength;
			}

			/*
			 * Collision processing
			 * */
			// Manage Y axis collision
			
                        //if(this->camera.cameraPosition.y < 0){
                        //        this->camera.cameraPosition.y = 0;
                        //}
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
