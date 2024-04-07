typedef struct triangle{
	int hypotIndex = -1;
	glm::vec3 points[3];
	glm::vec3 centroid;
	glm::vec3 edgeCenters[3];
	glm::vec3 direction[2];
	float lengths[3];
	float angles[3];
	float height = 0;
	float semiperimiter = 0;
	bool equilateral = false;
	bool isosceles = false;
	bool orthogonal = false;
	bool scalene = false;

}triangle_t;

typedef struct collision_vars{
	glm::vec3 origin;

}collision_t;

class FpsPlayer : public GraphicsObject{
	private:
		GraphicsGeometry geometry;

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		
		obj_data_t *sceneData = NULL;
		size_t sceneDataSize = 0;
		obj_t *objs = NULL;
		size_t objsCount = 0;

		//float gravity = 0.000001;
		float gravity = 0.0667408;
		float jumpStrength = 0.05;
		//float jumpStrength = 0.000001;
		float playerSize = 0.10;
		bool grounded = false;
		glm::vec3 previousCoords;

		bool jumping = false;
		float jumpHeight = 1.75;
		float jumpBase = 0;
		float jumpPeak = 0;
		float cameraSpeed = 0.05f;

		bool firstStart = true;

		float debugArea= 0;
		bool generalCollision(glm::vec3 camera, triangle3_t surface){
			float area = surface.area;
			triangle3_t a = geometry.createTriangle(surface.vertecies[0], surface.vertecies[1], camera);
                        triangle3_t b = geometry.createTriangle(surface.vertecies[1], surface.vertecies[2], camera);
                        triangle3_t c = geometry.createTriangle(surface.vertecies[2], surface.vertecies[0], camera);
			
			float areap = (a.area + b.area + c.area);
			debugArea = areap;
                        if(areap == area){
				return true;
			}else{
                        	if(areap > area){
                        		areap = areap - area;
                        	}else{
                        		areap = area - areap;
                        	}

                        	return areap >= 0 && areap < 10;
                        }
		}
		
		bool wallCollision(glm::vec3 camera, triangle3_t surface){
                        float area = surface.area;
                        triangle3_t a = geometry.createTriangle(surface.vertecies[0], surface.vertecies[1], camera);
                        triangle3_t b = geometry.createTriangle(surface.vertecies[1], surface.vertecies[2], camera);
                        triangle3_t c = geometry.createTriangle(surface.vertecies[2], surface.vertecies[0], camera);

                        float areap = (a.area + b.area + c.area);

                        debugArea = areap;
                        if(areap == area){
                                return false;
                        }else{
                                if(areap > area){
                                        areap = areap - area;
                                }else{
                                        areap = area - areap;
                                }

                                return areap >= 0 && areap < 10;
                        }	
			return false;
		}

		int debugA = 0;
		void calculateCollision(void){
			grounded = false;
			bool invertJump = false;
			bool invertFall = false;
			bool invertForward = false;
			bool invertBack = false;
			bool invertLeft = false;
			bool invertRight = false;

			glm::vec3 pointa;
			glm::vec3 pointb;
			glm::vec3 pointc;
			glm::vec3 camera = this->camera.getPos();
			
			int objIndex = 0, tracker=0;
			int objTrack = objs[objIndex].buffer_count;

			obj_data_t *pA = NULL; 
			for(int i=0; i<objsCount; i++){
				pA = (obj_data_t  *)objs[i].glut_data;
				for(int j=0; j<objs[i].element_count; j++){
				 	int test = (j%3);
					if(test == 0){
                                        	pointa = glm::vec3(pA[j].vertex[0], pA[j].vertex[1], pA[j].vertex[2]);
                                        	tracker++;
                                        	continue;
                                	}
                                	if(test == 1){
                                	        pointb = glm::vec3(pA[j].vertex[0], pA[j].vertex[1], pA[j].vertex[2]);
                                	        tracker++;
                                	        continue;
                                	}

					pointc = glm::vec3(pA[j].vertex[0], pA[j].vertex[1], pA[j].vertex[2]);
					
                                	glm::vec3 down = glm::vec3(0, -1, 0);
                                	glm::vec3 up = glm::vec3(0, 1, 0);
                                	glm::vec3 right = glm::vec3(1, 0, 0);
                                	glm::vec3 left = glm::vec3(-1, 0, 0);
                                	glm::vec3 forward = glm::vec3(0, 0, 1);
                                	glm::vec3 backward = glm::vec3(0, 0, -1);

					triangle3_t triangle = geometry.createTriangle(pointa, pointb, pointc);
                                	triangle3_t triangleY = geometry.createTriangle(pointa*down, pointb*down, pointc*down);
                                	triangle3_t triangleYn = geometry.createTriangle(pointa*up, pointb*up, camera*up);
                                	triangle3_t triangleX = geometry.createTriangle(pointa*right, pointb*right, camera*right);
                                	triangle3_t triangleXn = geometry.createTriangle(pointa*left, pointb*left, camera*left);
                                	triangle3_t triangleZ = geometry.createTriangle(pointa*forward, pointb*forward, camera*forward);
                                	triangle3_t triangleZn = geometry.createTriangle(pointa*backward, pointb*backward, camera*backward);

                                	triangle3_t testA = geometry.createTriangle(pointa*down, pointb*down, camera*down);
					line3_t fart = geometry.createLine(previousCoords, camera);
                                	bool hit = generalCollision(camera, triangle);
                                	if(hit){

                                                glm::vec3 ff = glm::normalize(glm::cross(camera, fart.direction));
						printf("%f Collision count : %d : %f, %f, %f\n", debugArea, debugA, ff.x, ff.y, ff.z);
						debugA++;
						if (gui_engine_global.keyboard.key_w){
                        			        float y = this->camera.cameraPosition.y;
							if(debugArea >= 70.0 && debugArea <= 79.0 || (debugArea>=40.0 && debugArea<= 50.0))
	                        			        this->camera.cameraPosition = previousCoords;// + cameraSpeed * this->camera.cameraFront;
                        			        this->camera.cameraPosition.y = y;
                        			}
                        			if (gui_engine_global.keyboard.key_s){
                        			        float y = this->camera.cameraPosition.y;
							if(debugArea >= 70.0 && debugArea <= 79.0 || (debugArea>=40.0 && debugArea<= 50.0))
                        			        	this->camera.cameraPosition = previousCoords;// - cameraSpeed * this->camera.cameraFront;
                        			        this->camera.cameraPosition.y = y;
                        			}
                        			if (gui_engine_global.keyboard.key_a){
                        			        float y = this->camera.cameraPosition.y;
							if(debugArea >= 70.0 && debugArea <= 79.0 || (debugArea>=40.0 && debugArea<= 50.0))
                        			        	this->camera.cameraPosition = previousCoords;// - glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * cameraSpeed;
                        			        this->camera.cameraPosition.y = y;
                        			}
                        			if (gui_engine_global.keyboard.key_d){
                        			        float y = this->camera.cameraPosition.y;
							if(debugArea >= 70.0 && debugArea <= 79.0 || (debugArea>=40.0 && debugArea<= 50.0))
                        			        	this->camera.cameraPosition = previousCoords;// + glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * cameraSpeed;
                        			        this->camera.cameraPosition.y = y;
                        			}
						if(!jumping && !grounded){
                        			        this->camera.cameraPosition.y += this->gravity;
                        			}else{
                        			        this->camera.cameraPosition.y -= jumpStrength;
                        			}
						break;
					}
				}
			}
		}
	public:
		void setSceneData(obj_data_t *d, size_t s){
			sceneData = d;
			sceneDataSize = s;
		}

		void setCollisionObjects(obj_t *objs, size_t objsCount){
			this->objs = objs;
			this->objsCount = objsCount;
		}
		bool create(void){
			return true;
		}
		
		
		void fpsControls(void){
			/*
			 * Account for player's head position.
			 * */
                        glm::vec3 front;
                        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
                        front.y = sin(glm::radians(pitch));
                        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
                        this->camera.cameraFront = front;//glm::normalize(front);
			previousCoords = this->camera.cameraPosition;


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

			if (gui_engine_global.keyboard.key_e){
                                this->camera.cameraPosition.y -= jumpStrength;
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

			if (gui_engine_global.keyboard.key_1){
                                this->camera.cameraPosition = glm::vec3(5.980382, 5.903437, 5.995522);
                        }else if(gui_engine_global.keyboard.key_2){
				this->camera.cameraPosition = glm::vec3(-7.010662, 1.903437, -6.995522);	
			}else if(gui_engine_global.keyboard.key_3){
				this->camera.cameraPosition.x += cameraSpeed;
			}
			

			if(!jumping && !grounded){
                      		this->camera.cameraPosition.y -= this->gravity;
			}else{
				this->camera.cameraPosition.y += jumpStrength;
			}

			calculateCollision();

			if(firstStart){
				this->camera.cameraPosition = glm::vec3(-7.5, 1.5, -6.5);	
				firstStart = false;
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
