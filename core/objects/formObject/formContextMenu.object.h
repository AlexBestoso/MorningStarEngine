struct FormContextMenuStruct{
	int x = 0;
	int y = 0;
	int z = 0;
	int w = 0;
	int h = 0;
	int textX = 0;
	int textY = 0;
	int textZ = 0;
	int dropDownX = 0;
	int dropDownY = 0;
	int dropDownZ = 0;
	int dropDownW = 0;
	int dropDownH = 0;
	float color[3] = {0, 0, 0};
	float textColor[3] = {0, 0, 0};
	float hoverColor[3] = {0, 0, 0};
	float dropDownColor[3] = {0, 0, 0};
	void *fontBitMap = GLUT_BITMAP_HELVETICA_12;
	string buttonText = "";
	bool showDropDown = false;

	ObjectFormButton *buttons = NULL;
	size_t buttonCount = 0;
};
class FormContextMenu : Object{
	private:
		int mousePassiveHover = 0;
		int mousePassiveHoverDropDown = 0;
		
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
		
		bool isInDropDownBox(float x, float y){
			y = y * -1;
                        float b_x = Object::getX(this->config.dropDownX);
                        float b_y  = Object::getY(this->config.dropDownY);
                        float b_w = Object::getX(this->config.dropDownW + this->config.dropDownX);
                        float b_h  = Object::getY(this->config.dropDownH + this->config.dropDownY);

                        if((x > b_x && x < b_w) && (y > b_y && y < b_h)){
                                return true;
                        }
                        return false;
		}
	public:
		struct FormContextMenuStruct config;

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
		void setHoverColor(float r, float g, float b){
			this->config.hoverColor[0] = r;
			this->config.hoverColor[1] = g;
			this->config.hoverColor[2] = b;
		}
		void setDropDownColor(float r, float g, float b){
			this->config.dropDownColor[0] = r;
			this->config.dropDownColor[1] = g;
			this->config.dropDownColor[2] = b;
		}
		void passiveMouseAction(float x, float y){
			bool insideButton = isInHitbox(x, y);
			if(insideButton){
                                this->mousePassiveHover = 1;
                        }else{
                                this->mousePassiveHover = 0;
                        }

			bool inside = isInDropDownBox(x, y);
			if(this->config.showDropDown && (!inside && !insideButton)){
				this->config.showDropDown = false;
				mousePassiveHoverDropDown = 0;
			}else if(this->config.showDropDown && (inside || !insideButton)){
				mousePassiveHoverDropDown = 1;
				for(int i=0; i<this->config.buttonCount; i++){
					this->config.buttons[i].passiveMouseAction(x, y);
				}
			}else{
				mousePassiveHoverDropDown = 0;
			}
                }
		int mouseClickAction(int button, int state, float x, float y){
                        if(mousePassiveHover == 1){
                                if(button == 0 && state == 1){
                                	return 1;     
                                }
                        }
			if(mousePassiveHoverDropDown == 1){
				for(int i=0; i<this->config.buttonCount; i++){
					int res = this->config.buttons[i].mouseClickAction(button, state, x, y);
					if(res != -1){
						return res;
					}
				}
			}
                        return 0;
                }
		void draw(void){
			if(this->mousePassiveHover == 0)
				Object::setColor(this->config.color[0], this->config.color[1], this->config.color[2]);
			else
				Object::setColor(this->config.hoverColor[0], this->config.hoverColor[1], this->config.hoverColor[2]);
			Object::drawRectangle(this->config.x, this->config.y, this->config.z, this->config.w, this->config.h);
			Object::setColor(this->config.textColor[0], this->config.textColor[1], this->config.textColor[2]);
			Object::drawText(this->config.textX, this->config.textY, this->config.textZ, this->config.buttonText, this->config.fontBitMap);
			if(this->config.showDropDown){
				Object::setColor(this->config.dropDownColor[0], this->config.dropDownColor[1], this->config.dropDownColor[2]);
				Object::drawRectangle(this->config.dropDownX, this->config.dropDownY, this->config.dropDownZ, this->config.dropDownW, this->config.dropDownH);
				for(int i=0; i<this->config.buttonCount; i++){
					this->config.buttons[i].draw();
				}
			}
		}
};
