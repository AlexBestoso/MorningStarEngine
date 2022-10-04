struct ObjectButtonStruct{
	float x, y, z, w, h;
	float textX, textY, textZ, textW, textH;
        float color[3] = {0, 0, 0};
        float textColor[3] = {0, 0 , 0};
        float hoverColor[3] = {0, 0, 0};
        string label = "";
};

class ObjectFormButton : Object{
	private:
		bool isInHitbox(float x, float y){
			
			y = y * -1;
			float b_x = Object::getX(this->config.x);
			float b_y  = Object::getY(this->config.y);		
			float b_w = Object::getX(this->config.w + this->config.x);
			float b_h  = Object::getY(this->config.h + this->config.y);		
			
			if((x > b_x && x < b_w) && (y > b_y && y < b_h)){
				return true;
			}
			return false;
		}

		int mousePassiveHover = 0;
	public:
		struct ObjectButtonStruct config;
		int (*buttonEvent)(void) = NULL;
		int (*buttonEvent_int)(int) = NULL;

		int mouseClickAction(int button, int state, float x, float y){
			if(mousePassiveHover == 1){
				if(button == 0 && state == 1){
					if(buttonEvent != NULL)
						return buttonEvent();
					else
						return -1;
				}
			}
			return -1;
                }

		int mouseClickAction_intInput(int button, int state, float x, float y, int value){
			if(mousePassiveHover == 1){
                                if(button == 0 && state == 1){
					if(buttonEvent_int != NULL)
	                                        return buttonEvent_int(value);
					else
						return -1;
                                }
                        }
                        return -1;
		}
		void passiveMouseAction(float x, float y){
			if(isInHitbox(x, y)){
				this->mousePassiveHover = 1;
			}else{
				this->mousePassiveHover = 0;
			}
		}

		void setHoverColor(float r, float g, float b){
			this->config.hoverColor[0] = r;
			this->config.hoverColor[1] = g;
			this->config.hoverColor[2] = b;
		}

		void setConstraints(int x, int y, int w, int h){
                        Object::setConstraints(x, y, w, h);
                }

		void setButtonText(string label){
			this->config.label = label;
		}

		void setNameAndId(string name, int id){
			Object::setObjectName(name);
			Object::setObjectId(id);
		}
		void setColor(float r, float g, float b){
			this->config.color[0] = r;
			this->config.color[1] = g;
			this->config.color[2] = b;
		}
		void setTextColor(float r, float g, float b){
			this->config.textColor[0] = r;
			this->config.textColor[1] = g;
			this->config.textColor[2] = b;
		}
		void setPositionAndSize(float x, float y, float z, float w, float h){
			this->config.x = x;
			this->config.y = y;
			this->config.z = z;
			this->config.w = w;
			this->config.h = h;
		}
		void setTextPosition(float x, float y, float z){
			this->config.textX = x;
			this->config.textY = y;
			this->config.textZ = z;
		}
		void drawContained(){
			/* Core Container.*/
			if(mousePassiveHover == 0){
				Object::setColor(this->config.color[0], this->config.color[1], this->config.color[2]);
			}else{
				Object::setColor(this->config.hoverColor[0], this->config.hoverColor[1], this->config.hoverColor[2]);
			}
			Object::drawRectangle(this->config.x, this->config.y, this->config.z, this->config.w, this->config.h);
			
			/* Button Text */
			Object::setColor(0, 0, 0);
			Object::drawText(this->config.textX,
					 this->config.textY,
					 this->config.textZ,
					 this->config.label, 
					 GLUT_BITMAP_HELVETICA_12
			);

		}
		void draw(void){
			this->drawContained();
		}
};
