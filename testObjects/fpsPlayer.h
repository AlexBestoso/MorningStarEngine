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
		float previousArea = 0.25;
		bool generalCollision(glm::vec3 camera, triangle3_t surface, float maxOrbit, float *output){
			if(output == NULL)
				return false;
			float area = surface.area;
			triangle3_t a = geometry.createTriangle(surface.vertecies[0], surface.vertecies[1], camera);
                        triangle3_t b = geometry.createTriangle(surface.vertecies[1], surface.vertecies[2], camera);
                        triangle3_t c = geometry.createTriangle(surface.vertecies[2], surface.vertecies[0], camera);
			
			float areap = (a.area + b.area + c.area);
                        if(areap == area){
				output[0] = 0;
				printf("Perfection.\n");
				printf("Area : %f vs %f\n", areap, debugArea);
				exit(1);
				return true;
			}else{
                        	if(areap > area){
                        		areap = areap - area;
                        	}else{
                        		areap = area - areap;
                        	}
				output[0] = areap;
                        	return areap < maxOrbit;
                        }
		}
		
		int getQuadrant(glm::vec3 p){
			if(p.x >= 0 && p.y >= 0 && p.z >= 0)
				return 1;
			else if(p.x < 0 && p.y >= 0 && p.z >= 0)
				return 2;
			else if(p.x < 0 && p.y < 0 && p.z >= 0)
				return 3;
			else if(p.x >= 0 && p.y < 0 && p.z >= 0)
				return 4;
			if(p.x >= 0 && p.y >= 0 && p.z < 0)
                                return 5;
                        else if(p.x < 0 && p.y >= 0 && p.z < 0)
                                return 6;
                        else if(p.x < 0 && p.y < 0 && p.z < 0)
                                return 7;
                        else if(p.x >= 0 && p.y < 0 && p.z < 0)
				return 8;
			return 1;
		}

		int debugA = 0;
		bool inOrbit = false;
		void calculateCollision(void){
			grounded = false;
			bool invertJump = false;
			bool invertFall = false;
			bool invertForward = false;
			bool invertBack = false;
			bool invertLeft = false;
			bool invertRight = false;

			glm::vec3 pointa;
			glm::vec3 normala;
			glm::vec3 pointb;
			glm::vec3 normalb;
			glm::vec3 pointc;
			glm::vec3 normalc;
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
                                        	normala = glm::vec3(pA[j].normal[0], pA[j].normal[1], pA[j].normal[2]);
                                        	tracker++;
                                        	continue;
                                	}
                                	if(test == 1){
                                	        pointb = glm::vec3(pA[j].vertex[0], pA[j].vertex[1], pA[j].vertex[2]);
                                        	normalb = glm::vec3(pA[j].normal[0], pA[j].normal[1], pA[j].normal[2]);
                                	        tracker++;
                                	        continue;
                                	}

					pointc = glm::vec3(pA[j].vertex[0], pA[j].vertex[1], pA[j].vertex[2]);
                                        normalc = glm::vec3(pA[j].normal[0], pA[j].normal[1], pA[j].normal[2]);
					
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

                                	bool hit = generalCollision(camera, triangle, /*previousArea*/1.0, &debugArea);

					glm::vec3 triangleDirection = glm::normalize(normala + normalb + normalc)*-11.0f;
					line3_t magnatude = geometry.createLine(triangleDirection, previousCoords);

						triangle3_t finalizer = geometry.createTriangle(
							glm::vec3(0), 
							camera,
							triangleDirection
						);

					inOrbit = hit;
                                	if(hit){
						this->travel = triangleDirection;
							break;
						//this->camera.cameraPosition -= triangleDirection;

						float grav = 0;
						camera += (force-momentum) * triangleDirection;
						this->camera.cameraPosition = camera;

						//triangleDirection -= camera;
						//camera = glm::vec3(0.0f) + triangleDirection + this->camera.cameraPosition;
						
						//glm::vec3 surfaceToAir = glm::cross(triangleDirection, camera);
						//this->camera.cameraPosition = camera;
						//camera = surfaceToAir;

						// we have a 90 degree angle.
						// Now we just have to shft all the data to be the center of the universe.
						//...
						//camera = ((triangleDirection-camera) + (triangleDirection+camera))/2.0f;
						float test = glm::degrees(glm::dot(triangleDirection, camera));
						//camera *= -1.0f;

						//camera *= cos(glm::radians(test));
						//camera += grav;
						//triangleDirection -= camera;
						//camera -= camera;

							
						line3_t baseMeasure = geometry.createLine(camera, triangleDirection);

						
						//camera += (camera+triangleDirection)-(camera - triangleDirection);
					//	printf("Grav Value : %f\n", grav);
					//	printf("Direction Vectors : (%f, %f, %f) vs (%f, %f, %f), (%f, %f, %f)\n", triangleDirection.x, triangleDirection.y, triangleDirection.z, this->camera.cameraPosition.x, this->camera.cameraPosition.y, this->camera.cameraPosition.z, camera.x, camera.y, camera.z);
					//	printf("Line of interest : |%f| %f, %f, %f\n", baseMeasure.distance, baseMeasure.direction.x, baseMeasure.direction.y, baseMeasure.direction.z);
					//	printf("Angle of interest : %f\n", test);
						this->camera.cameraPosition = camera;
						//`this->camera.setCameraTarget(triangleDirection);

							//-(triangleDirection * glm::vec3(0.0025f));
                                                //glm::vec3 ff = glm::normalize(glm::cross(camera, fart.direction));
						///printf("%f Collision count : %d : %f, %f, %f\n", debugArea, debugA, ff.x, ff.y, ff.z);
						//debugA++;
						break;	
					}
				}
			}
			previousArea = 0.5;
		}
	public:
		glm::vec3 momentum = glm::vec3(0);
		glm::vec3 force = glm::vec3(0);
		glm::vec3 travel = glm::normalize(glm::vec3(1.0f));
		float height = 0.298666;
		float gravity = 0.0667408;
		float jumpStrength = 0.05;
		bool respectGravity = true;

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

		glm::vec3 getPlayerCoords(void){
			return this->camera.cameraPosition;
		}
		
		
		void fpsControls(void){
			/*
			 * Account for player's head position.
			 * */
                        glm::vec3 front;
                        front.x = cos(glm::radians(ges.pitch)) * cos(glm::radians(ges.yaw));
                        front.y = sin(glm::radians(ges.pitch));
                        front.z = cos(glm::radians(ges.pitch)) * sin(glm::radians(ges.yaw));
                        this->camera.cameraFront = front;//glm::normalize(front);
			previousCoords = this->camera.cameraPosition;

			if(ges.keyboard.key_2){
				printf("Player Coords : (%f, %f, %f)\n", this->camera.cameraPosition.x, this->camera.cameraPosition.y, this->camera.cameraPosition.z);
			}
			/*
			 * Manage horizontal movement
			 * */
                        if (ges.keyboard.key_w){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition += cameraSpeed * this->camera.cameraFront;
				this->camera.cameraPosition.y = y;
			}
			
			if (ges.keyboard.key_s){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition -= cameraSpeed * this->camera.cameraFront;
				this->camera.cameraPosition.y = y;	
			}

                        if (ges.keyboard.key_a){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition -= glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * cameraSpeed;
				this->camera.cameraPosition.y = y;
			}
                        if (ges.keyboard.key_d){
				float y = this->camera.cameraPosition.y;
                                this->camera.cameraPosition += glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * cameraSpeed;
				this->camera.cameraPosition.y = y;
			}

			if (ges.keyboard.key_e){
                                this->camera.cameraPosition += this->gravity * glm::vec3(0, -1, 0);
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

			if (ges.keyboard.key_1){
                                this->camera.cameraPosition = glm::vec3(0.0f);
                        }else if(ges.keyboard.key_2){
			}else if(ges.keyboard.key_3){
			}

			if(this->respectGravity){
                                this->camera.cameraPosition.y -= (this->gravity-this->momentum.y);
				this->momentum.y -= (this->momentum.y - this->gravity) <= 0 ? this->momentum.y : this->gravity/4;
				if(this->camera.cameraPosition.y <= this->height) this->camera.cameraPosition.y = this->height;
			}

			if(ges.keyboard.key_space){
				this->momentum.y = this->camera.cameraPosition.y <= this->height ? (this->gravity*10) : this->momentum.y;
			}

			if(firstStart){
				this->camera.cameraPosition = glm::vec3(-7.5, 1.5, -6.5);	
				firstStart = false;
			}
                }
		void draw(void){
			fpsControls();
			view = camera.focus();
		}
};
