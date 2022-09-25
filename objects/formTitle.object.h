class ObjectFormTitle : Object{
	private:
		string titleText = "";
		int x = 0;
		int y = 0;
		int w = 100;
		int h = 100;
		float color[3] = {1, 1, 1};

		int textX = 0;
		int textY = 0;
		float textColor[3] = {0, 0, 0};

	public:
		ObjectFormTitle(int id, string name){
			Object::setObjectId(id);
			Object::setObjectName(name);
		}
		ObjectFormTitle(){
		
		}
		
		void setIdAndName(int id, string name){
			Object::setObjectId(id);
			Object::setObjectName(name);
		}

		void setTextPosition(int x, int y){
			this->textX = x;
			this->textY = y;
		}

		void setPositionAndSize(int x, int y, int w, int h){
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
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

		void setTitle(string title){
			this->titleText = title;
		}
		string getTitle(void){
			return this->titleText;
		}
		
		void setConstraints(int x, int y, int w, int h){
			Object::setConstraints(x, y, w, h);
		}

		void draw(){
			
		}

		void drawConstrained(){
                        Object::setColor(this->color[0], this->color[1], this->color[2]);
			Object::drawContainedRectangle(this->x, this->y, 1, this->w, this->h);

			Object::setColor(this->textColor[0], this->textColor[1], this->textColor[2]);
			Object::drawContainedText(this->textX, this->textY, 2, this->titleText, GLUT_BITMAP_TIMES_ROMAN_24);
		}
};
