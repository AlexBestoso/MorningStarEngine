struct ObjectFormConfig{
	int id;
	string name;
	int x;
	int y;
	int w;
	int h;
	float color[3];

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
		void mouseClickAction(int button, int state, float x, float y){
				
		}
		void passiveMouseAction(float x, float y){
			for(int i=0; i<this->buttonCount; i++)
				this->formButtons[i].passiveMouseAction(x, y);
		}

		void setSelectLists(FormSelectList *selectLists, size_t listCount){
			this->selectLists = selectLists;
			this->selectListCount = listCount;
		}
		void setInputs(ObjectFormInput *inputs, size_t inputCount){
			this->formInputs = inputs;
                        this->inputCount = inputCount;
		}

		void setButtons(ObjectFormButton *buttons, size_t buttonCount){
                        this->formButtons = buttons;
                        this->buttonCount = buttonCount;
                }

		void setFormTexture(string textureLocation){
			this->formTextureLocation = textureLocation;
		}

		ObjectForm(){}
		ObjectForm(struct ObjectFormConfig config, ObjectFormTitle title, ObjectFormInput *inputs, size_t inputCount){
			Object::setObjectId(config.id);
			Object::setObjectName(config.name);
			this->config = config;
			this->title = title;
		}
		void draw(){
			this->createFormContainer();
			this->createTitle();
			this->createInputs();
			this->createButtons();
			this->createSelectList();
		}
};
