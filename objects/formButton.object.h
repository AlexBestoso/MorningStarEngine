class ObjectFormButton : Object{
	private:
		const int labelBlock = 0;
		const int inputFieldBlock = 1;
		
		float x, y, z, w, h;
		float textX, textY, textZ, textW, textH;
		float color[3] = {0, 0, 0};
		float textColor[3] = {0, 0 , 0};
		float hoverColor[3] = {0, 0, 0};
		string label = "";



		bool isInHitbox(float x, float y){
			
			y = y * -1;
			float b_x = Object::getX(this->x);
			float b_y  = Object::getY(this->y);		
			float b_w = Object::getX(this->w + this->x);
			float b_h  = Object::getY(this->h + this->y);		
			
			if((x > b_x && x < b_w) && (y > b_y && y < b_h)){
				return true;
			}
			return false;
		}

		int mousePassiveHover = 0;
	public:
		int (*buttonEvent)(void);
		ObjectFormButton(int id, string name){
			Object::setObjectId(id);
			Object::setObjectName(name);
		}
		ObjectFormButton(){
		
		}

		void mouseClickAction(int button, int state, float x, float y){
			if(mousePassiveHover == 1){
				if(button == 0 && state == 1){
					buttonEvent();
				}
			}
                }
		void passiveMouseAction(float x, float y){
			if(isInHitbox(x, y)){
				this->mousePassiveHover = 1;
			}else{
				this->mousePassiveHover = 0;
			}
		}

		void setHoverColor(float r, float g, float b){
			this->hoverColor[0] = r;
			this->hoverColor[1] = g;
			this->hoverColor[2] = b;
		}

		void setConstraints(int x, int y, int w, int h){
                        Object::setConstraints(x, y, w, h);
                }

		void setButtonText(string label){
			this->label = label;
		}

		void setNameAndId(string name, int id){
			Object::setObjectName(name);
			Object::setObjectId(id);
		}
		void setColor(float r, float g, float b){
			this->color[0] = r;
			this->color[1] = g;
			this->color[2] = b;
		}
		void setTextColor(float r, float g, float b){
			this->textColor[0] = r;
			this->textColor[1] = g;
			this->textColor[2] = b;
		}
		void setPositionAndSize(float x, float y, float z, float w, float h){
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
			this->h = h;
		}
		void setTextPosition(float x, float y, float z){
			this->textX = x;
			this->textY = y;
			this->textZ = z;
		}
		void drawContained(){
			/* Core Container.*/
			if(mousePassiveHover == 0){
				Object::setColor(this->color[0], this->color[1], this->color[2]);
			}else{
				Object::setColor(this->hoverColor[0], this->hoverColor[1], this->hoverColor[2]);
			}
			Object::drawRectangle(this->x, this->y, this->z, this->w, this->h);
			
			/* Button Text */
			Object::setColor(0, 0, 0);
			Object::drawText(this->textX,
						  this->textY,
						  this->textZ,
						  this->label, 
						  GLUT_BITMAP_HELVETICA_12
			);

		}
};
