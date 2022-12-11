#include "../../../../../main.h"
extern "C" FormContextMenu* create_object(void){
	return new FormContextMenu;
}
extern "C" void destroy_object(FormContextMenu *object){
	delete object;
}
bool FormContextMenu::isInHitbox(float x, float y){
	y = y * -1;
	float b_x = Object::getX(this->config.x);
	float b_y  = Object::getY(this->config.y);
	float b_w = Object::getX(this->config.w + this->config.x);
	float b_h  = Object::getY(this->config.h + this->config.y);
	if((x > b_x && x < b_w) && (y > b_y && y < b_h))
		return true;
	return false;
}
		
bool FormContextMenu::isInDropDownBox(float x, float y){
	y = y * -1;
	float b_x = Object::getX(this->config.dropDownX);
	float b_y  = Object::getY(this->config.dropDownY);
	float b_w = Object::getX(this->config.dropDownW + this->config.dropDownX);
	float b_h  = Object::getY(this->config.dropDownH + this->config.dropDownY);
	if((x > b_x && x < b_w) && (y > b_y && y < b_h))
		return true;
	return false;
}

void FormContextMenu::passiveMouseAction(float x, float y){
	if(!this->config.noFormContainer){
		bool insideButton = isInHitbox(x, y);
		if(insideButton){
			this->mousePassiveHover = 1;
		}else{
			this->mousePassiveHover = 0;
		}

		bool inside = isInDropDownBox(x, y);

		if(this->config.showDropDown && (!inside && !insideButton)){
			this->config.showDropDown = false;
			this->mousePassiveHoverDropDown = 0;
			this->buttonHover = false;
		}else if(this->config.showDropDown && (inside || !insideButton)){ // inside displayed drop down.
			this->mousePassiveHoverDropDown = 1;
			for(int i=0; i<this->config.buttonCount; i++){
				if(this->config.buttons[i].isInHitbox(x, y)){
					this->config.buttons[i].mousePassiveHover = 1;
					this->buttonHover = true;
				}else{
					this->buttonHover = false;
				}
				this->config.buttons[i].passiveMouseAction(x, y);
			}
		}else{
			this->buttonHover = false;
			this->mousePassiveHoverDropDown = 0;
		}
	}else{
		for(int i=0; i<this->config.buttonCount; i++)
			this->config.buttons[i].passiveMouseAction(x, y);
	}
}
int FormContextMenu::mouseClickAction(int button, int state, float x, float y){
	// File Button Click handler.
	if(mousePassiveHover == 1 && !this->config.noFormContainer){
		if(button == 0 && state == 1)
			return 1;     
	}

	// Exit button handler.
	if(mousePassiveHoverDropDown == 1 || this->config.noFormContainer){
		for(int i=0; i<this->config.buttonCount; i++){
			if(this->config.buttons[i].isInHitbox(x, y)){
                        	this->config.buttons[i].mousePassiveHover = 1;
                        }
			int res = this->config.buttons[i].mouseClickAction(button, state, x, y);
			if(res != -1)
				return res;
		}
	}
	return 0;
}
void FormContextMenu::draw(void){
	if(!this->config.noFormContainer){
		if(this->mousePassiveHover == 0)
			Object::setColor(this->config.color[0], this->config.color[1], this->config.color[2]);
		else
			Object::setColor(this->config.hoverColor[0], this->config.hoverColor[1], this->config.hoverColor[2]);
		
		Object::drawRectangle(this->config.x, this->config.y, this->config.z, this->config.w, this->config.h);
		Object::setColor(this->config.textColor[0], this->config.textColor[1], this->config.textColor[2]);
		Object::drawText(this->config.textX, this->config.textY, this->config.textZ, this->config.buttonText, this->config.fontBitMap);
	}

	if(this->config.showDropDown){
		Object::setColor(this->config.dropDownColor[0], this->config.dropDownColor[1], this->config.dropDownColor[2]);
		Object::drawRectangle(this->config.dropDownX, this->config.dropDownY, this->config.dropDownZ, this->config.dropDownW, this->config.dropDownH);
		for(int i=0; i<this->config.buttonCount; i++){
			if(this->buttonHover == true){
				this->config.buttons[i].mousePassiveHover = 1;
			}
			this->config.buttons[i].draw();
		}
	}
}
