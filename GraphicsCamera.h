class GraphicsCamera{
	private:
	public:
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 invDirection = glm::normalize(cameraPosition - cameraTarget);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, invDirection));
		glm::vec3 cameraUp = glm::cross(invDirection, cameraRight);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.1f);
		glm::mat4 view;
	
		void refresh(void){
			invDirection = glm::normalize(cameraPosition - cameraTarget);
			cameraRight = glm::normalize(glm::cross(up, invDirection));
			cameraUp = glm::cross(invDirection, cameraRight);
		
		}
		glm::vec3 getCameraFront(){
			return cameraFront;
		}
		glm::mat4 focus(void){
			refresh();
			view = glm::lookAt(cameraPosition, cameraPosition+cameraFront, up);
			return view;
		}

		glm::mat4 getView(void){
			return view;
		}
		
		void setPos(glm::vec3 pos){
			cameraPosition = pos;
		}
		glm::vec3 getPos(void){
			return cameraPosition;
		}

		void setCameraTarget(glm::vec3 target){
			cameraTarget = target;
		}
		glm::vec3 getCameraTarget(void){
			return cameraTarget;
		}
		glm::vec3 getCameraInvDirection(void){
			return invDirection;
		}

		float cameraSpeed = 0.05f;
		void fpsControls(void){
			glm::vec3 front;
                        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
                        front.y = sin(glm::radians(pitch));
                        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
                        cameraFront = glm::normalize(front);
			if (gui_engine_global.keyboard.key_w)
                                cameraPosition += cameraSpeed * cameraFront;
                        if (gui_engine_global.keyboard.key_s)
                                cameraPosition -= cameraSpeed * cameraFront;
                        if (gui_engine_global.keyboard.key_a)
                                cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                        if (gui_engine_global.keyboard.key_d)
                                cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

			if(cameraPosition.y > 0){
				cameraPosition.y -= 0.02;
			}
			if(cameraPosition.y < 0){
				cameraPosition.y = 0;
			}
		}
};
