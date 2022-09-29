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
		ObjectFormInput *formInputs;
		size_t inputCount = 0;

		size_t buttonCount = 0;

		void createFormContainer(){
			Object::setColor(this->config.color[0], this->config.color[1], this->config.color[2]);
			Object::startDrawing();
				Object::setVertex(this->config.x, this->config.y, 0);
				Object::setVertex(this->config.x + this->config.w, this->config.y, 0);
				Object::setVertex(this->config.x + this->config.w, this->config.y + this->config.h, 0);
				Object::setVertex(this->config.x, this->config.y + this->config.h, 0);
			Object::stopDrawing();
		
		}

		void createTitle(void){
			title.drawConstrained();
		}

		void createInputs(void){
			for(int i=0; i<this->inputCount; i++){
				this->formInputs[i].drawContained();
			}	
		}

		void createButtons(void){
                        for(int i=0; i<this->buttonCount; i++){
                                this->formButtons[i].drawContained();
                        }
                }
		
	public:
		ObjectFormButton *formButtons;
		struct ObjectFormConfig config;
		ObjectFormTitle title;
		void mouseClickAction(int button, int state, float x, float y){
				
		}
		void passiveMouseAction(float x, float y){
			for(int i=0; i<this->buttonCount; i++)
				this->formButtons[i].passiveMouseAction(x, y);
		}

		void setInputs(ObjectFormInput *inputs, size_t inputCount){
			this->formInputs = inputs;
                        this->inputCount = inputCount;
		}

		void setButtons(ObjectFormButton *buttons, size_t buttonCount){
                        this->formButtons = buttons;
                        this->buttonCount = buttonCount;
                }

		ObjectForm(){}
		ObjectForm(struct ObjectFormConfig config, ObjectFormTitle title, ObjectFormInput *inputs, size_t inputCount){
			Object::setObjectId(config.id);
			Object::setObjectName(config.name);
			this->config = config;
			this->title = title;
		}
		void draw(){
			Object::drawTexturedRectangle("/home/ninjs-grey/Documents/GithubRepositories/bmpParser/BmpParser/sample.bmp", 0, 0, -5, 100, 100);
			this->createFormContainer();
			this->createTitle();
			this->createInputs();
			this->createButtons();
		}
};
