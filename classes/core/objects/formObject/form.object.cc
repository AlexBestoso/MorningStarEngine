#include "../../../../main.h"

extern "C" ObjectForm* create_object(){
	return new ObjectForm;
}

extern "C" void destroy_object(ObjectForm* object){
	delete object;
}


void ObjectForm::mouseClickAction(int button, int state, float x, float y){

}

bool ObjectForm::isInHitBox(float x, float y){
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
void ObjectForm::passiveMouseAction(float x, float y){
	for(int i=0; i<this->buttonCount; i++)
	this->formButtons[i].passiveMouseAction(x, y);
}

void ObjectForm::setSelectLists(FormSelectList *selectLists, size_t listCount){
	this->selectLists = selectLists;
	this->selectListCount = listCount;
}
void ObjectForm::setInputs(ObjectFormInput *inputs, size_t inputCount){
	this->formInputs = inputs;
	this->inputCount = inputCount;
}

void ObjectForm::setButtons(ObjectFormButton *buttons, size_t buttonCount){
	this->formButtons = buttons;
	this->buttonCount = buttonCount;
}

void ObjectForm::setFormTexture(string textureLocation){
	this->formTextureLocation = textureLocation;
}


void ObjectForm::draw(void){
	this->createFormContainer();
	if(!this->config.ignoreTitle)
		this->createTitle();
	this->createInputs();
	this->createButtons();
	this->createSelectList();
}
