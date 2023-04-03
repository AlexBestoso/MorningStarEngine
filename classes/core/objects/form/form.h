#include "./formBackground.h"
#include "./formTitle.h"
#include "./formButton.h"
#include "./formTextInput.h"
#include "./formDropDown.h"
class Form : public CoreObject{
	private:
	int formContext = 0;
	FormBackground background;
	FormTitle title;
	FormButton *buttons;
	size_t buttonCount = 0;
	FormTextInput *textInputs;
	size_t textInputCount = 0;
	FormDropDown *dropDowns;
	size_t dropDownCount = 0;
	bool hideTitle = false;
	
	int clickedButtonId = -1;
	public:
	Form(FormBackground background){
		this->background = background;
	}
	Form(){
		
	}
	
	int getClickedButton(){
		return clickedButtonId;
	}
	void setContext(int context){
		this->formContext = context;
	}
	int getContext(void){
		return formContext;
	}
	
	void setBackground(FormBackground background){
		this->background = background;
	}
	void setTitle(FormTitle title){
		this->title = title;

		this->title.setBounds(
			this->background.getBgX(),		
			this->background.getBgY(),		
			this->background.getBgZ(),		
			this->background.getBgW(),		
			this->background.getBgH()
		);
	}

	void setButtons(FormButton *buttons, size_t buttonCount){
		this->buttons = buttons;
		this->buttonCount = buttonCount;
	}

	void setTextInputs(FormTextInput *inputs, size_t inputCount){
		this->textInputCount = inputCount;
		this->textInputs = inputs;
	}
	void setDropDowns(FormDropDown *drops, size_t count){
		this->dropDowns = drops;
		this->dropDownCount = count;
	}

	void setHideTitle(bool hide){
		hideTitle = hide;
	}

	virtual int run(){
		background.run();
		if(!hideTitle)
			title.run();
		for(int i=0; i<buttonCount; i++){
			buttons[i].run();
		}
		for(int i=0; i<textInputCount; i++){
			textInputs[i].run();
                }
		return this->formContext;
	}

	virtual int mousePassive(float x, float y){
		for(int i=0; i<buttonCount; i++){
                        buttons[i].mousePassive(x, y);
                }
		for(int i=0; i<textInputCount; i++){
			textInputs[i].mousePassive(x, y);
		}
		return this->formContext;
	}

	virtual int mouseClick(int button, int state, float x, float y){
		for(int i=0; i<buttonCount; i++){
                        int val = buttons[i].mouseClick(button, state, x, y);
			if(val != -1){
				clickedButtonId = i;
				return val;
			}
			clickedButtonId = -1;
                }
		// TODO : Finish this.
		for(int i=0; i<textInputCount; i++){
			textInputs[i].mouseClick(button, state, x, y);	
                }
                return -1;
	}

	virtual int keyDown(unsigned char key, float x, float y){
		for(int i=0; i<textInputCount; i++){
			textInputs[i].keyDown(key, x, y);
		}
		return -1;
	}
};
