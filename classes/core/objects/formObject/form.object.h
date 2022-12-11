struct ObjectFormConfig{
	int id;
	string name;
	int x;
	int y;
	int w;
	int h;
	float color[3];
	bool ignoreTitle = false;
};
class ObjectForm : Object{
	private:
		size_t inputCount = 0;
		size_t buttonCount = 0;
		size_t selectListCount = 0;
		string formTextureLocation = "";
		bool textureLoaded = false;

		void createFormContainer(){
			if(formTextureLocation == ""){
				Object::setColor(this->config.color[0], this->config.color[1], this->config.color[2]);
				Object::drawRectangle(this->config.x, this->config.y, 0, this->config.w, this->config.h);
			}else{
				Object::drawTexturedRectangle(this->formTextureLocation, this->config.x, this->config.y, 0, this->config.w, this->config.h);
			}
		}

		void createTitle(void){
			title.drawConstrained();
		}

		void createInputs(void){
			for(int i=0; i<this->inputCount; i++){
				this->formInputs[i].drawContained();
			}	
		}

		void createSelectList(void){
			for(int i=0; i<this->selectListCount; i++){
				this->selectLists[i].draw();
			}
		}

		void createButtons(void){
                        for(int i=0; i<this->buttonCount; i++){
                                this->formButtons[i].drawContained();
                        }
                }
		
	public:
		ObjectFormButton *formButtons;
		ObjectFormInput *formInputs;
		FormSelectList *selectLists;
		ObjectFormTitle title;
		struct ObjectFormConfig config;

		virtual void mouseClickAction(int button, int state, float x, float y);
		virtual bool isInHitBox(float x, float y);
		virtual void passiveMouseAction(float x, float y);
		virtual void setSelectLists(FormSelectList *selectLists, size_t listCount);
		virtual void setInputs(ObjectFormInput *inputs, size_t inputCount);
		virtual void setButtons(ObjectFormButton *buttons, size_t buttonCount);
		virtual void setFormTexture(string textureLocation);
		virtual void draw(void);
};
