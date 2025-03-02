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
		
		float cross_r = 0.5;
		float cross_g = 0.5;
		float cross_b = 0.5;
		float cross_s = 0.0125;
		float crossHair[6*4] = {
			-cross_s, 0.0, 0.0, cross_r, cross_g, cross_b,
			cross_s, 0.0, 0.0, cross_r, cross_g, cross_b,
			0, cross_s, 0.0, cross_r, cross_g, cross_b,
			0, -cross_s, 0.0, cross_r, cross_g, cross_b
		};

	public:
		glm::vec3 momentum = glm::vec3(0);
		glm::vec3 force = glm::vec3(0);
		glm::vec3 travel = glm::normalize(glm::vec3(1.0f));
		float height = 1.000000;//0.298666;
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
			int err = 0;
			if((err = this->createShaders("./glsl/vertexShaderGeneric.glsl", "./glsl/fragmentShaderGeneric.glsl")) != 0){
                                switch(err){
                                        case 1: printf("Vertex Shader error.\n");break;
                                        case 2: printf("Fragment shader error.\n");break;
                                        default: printf("Shader Linking error.\n");break;
                                }
                                return false;
                        }

			
			this->generateObjectIds(true, true, false);
                        this->bindVao();
                        this->bindVbo();

			this->setAttributePointer(0, 3, 6, (void *)0); // vertex
                        this->enableArrayAttribute(0);
                        this->setAttributePointer(1, 3, 6, (void *)(3*sizeof(float))); // material color
                        this->enableArrayAttribute(1);

			this->unbindVbo();
			this->unbindVao();

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

			if(ges.keyboard.key_3){
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
				this->momentum.y = this->camera.cameraPosition.y <= this->height ? (this->gravity*5) : this->momentum.y;
			}

			if(firstStart){
				this->camera.cameraPosition = glm::vec3(-7.5, 1.5, -6.5);	
				firstStart = false;
			}
                }
		void draw(void){
			this->bindVao();
			this->bindVbo();
                        this->use();
		
			this->storeVertexData(sizeof(float)*(6*4), crossHair, GL_DYNAMIC_DRAW);
			glDrawArrays(GL_LINES, 0, 4);
			fpsControls();
			view = camera.focus();
		}
};
