struct ObjectFormStruct{
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
		struct ObjectFormStruct ofs;
		ObjectFormTitle title;
		ObjectFormInput *formInputs;
		size_t inputCount;

		void createFormContainer(){
			Object::setColor(this->ofs.color[0], this->ofs.color[1], this->ofs.color[2]);
			Object::startDrawing();
				Object::setVertex(this->ofs.x, this->ofs.y, 0);
				Object::setVertex(this->ofs.x + this->ofs.w, this->ofs.y, 0);
				Object::setVertex(this->ofs.x + this->ofs.w, this->ofs.y + this->ofs.h, 0);
				Object::setVertex(this->ofs.x, this->ofs.y + this->ofs.h, 0);
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
		
	public:
		void mouseClickAction(int button, int state, float x, float y){
			
		}
		void passiveMouseAction(float x, float y){
			for(int i=0; i<this->inputCount; i++)
				this->formInputs[i].passiveMouseAction(x, y);
		}

		ObjectForm(){}
		ObjectForm(struct ObjectFormStruct ofs, ObjectFormTitle title, ObjectFormInput *inputs, size_t inputCount){
			Object::setObjectId(ofs.id);
			Object::setObjectName(ofs.name);
			this->ofs = ofs;
			this->title = title;
			this->formInputs = inputs;
			this->inputCount = inputCount;
		}
		void draw(){
			this->createFormContainer();
			this->createTitle();
			this->createInputs();
		}
};
