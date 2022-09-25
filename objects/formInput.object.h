struct ObjectFormInputStruct{
		float x, y, z, w, h;
                float color[3] = {0, 0, 0};
};
class ObjectFormInput : Object{
	private:
		const int labelBlock = 0;
		const int inputFieldBlock = 1;
		ObjectFormInputStruct blocks[3];
		
		float x, y, z, w, h;
		float color[3] = {0, 0, 0};
		float labelColor[3] = {0, 0 , 0};
		float hoverColor[3] = {0, 0, 0,};
		string label = "";
		string defaultValue = "Click To Type";
		size_t maxXOverflow = 20;


		bool isInHitbox(float x, float y){
			float _x = x;
			float _y = (y - keyboard.height ) * -1;

			float b_x = Object::getContainedX(this->blocks[inputFieldBlock].x);
			float b_y  = Object::getContainedY(this->blocks[inputFieldBlock].y);		
			float b_w = Object::getContainedX(this->blocks[inputFieldBlock].w + this->blocks[inputFieldBlock].x);
			float b_h  = Object::getContainedY(this->blocks[inputFieldBlock].h + this->blocks[inputFieldBlock].y);		
			
			if((_x > b_x && _x < b_w) && (_y > b_y && _y < b_h)){
				return true;
			}

			return false;
		}

		int mousePassiveHover = 0;
	public:
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

		void setMaxXOverflow(size_t value){
			maxXOverflow = value;
		}
		void setDefaultValue(string value){
			this->defaultValue = value;
		}
		void setConstraints(int x, int y, int w, int h){
                        Object::setConstraints(x, y, w, h);
                }

		void setLabel(string label){
			this->label = label;
		}

		ObjectFormInput(int id, string name){
			Object::setObjectId(id);
			Object::setObjectName(name);
		}
		ObjectFormInput(){
		
		}
		void setDefaultInputValue(string value){
			this->defaultValue = value;
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
		void setLabelColor(float r, float g, float b){
			this->blocks[labelBlock].color[0] = r;
			this->blocks[labelBlock].color[1] = g;
			this->blocks[labelBlock].color[2] = b;
		}
		void setPositionAndSize(float x, float y, float z, float w, float h){
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
			this->h = h;
		}
		void drawContained(){
			/* Core Container.*/
			Object::setColor(this->color[0]+.33, this->color[1]+.55, this->color[2]);
			Object::drawContainedRectangle(this->x, this->y, this->z, this->w, this->h);
			
			/* Input Label.*/
			this->blocks[labelBlock].x = this->x;
			this->blocks[labelBlock].y = this->y+(this->h/4);
			this->blocks[labelBlock].z = this->z+1;
			this->blocks[labelBlock].w = this->w;//this->w/3;
			this->blocks[labelBlock].h = this->h/2;
			
                        Object::setColor(0, 0, 0);
                        Object::drawContainedRectangle(this->blocks[labelBlock].x - 5, 
						       this->blocks[labelBlock].y - 5, 
						       this->blocks[labelBlock].z, 
						       this->blocks[labelBlock].w + 10, 
						       this->blocks[labelBlock].h + 10
			);
			Object::setColor(this->blocks[labelBlock].color[0] - .11, 
					 this->blocks[labelBlock].color[1] - .11, 
					 this->blocks[labelBlock].color[2] - .11
			);
			Object::drawContainedRectangle(this->blocks[labelBlock].x, 
						       this->blocks[labelBlock].y, 
						       this->blocks[labelBlock].z, 
						       this->blocks[labelBlock].w, 
						       this->blocks[labelBlock].h
			);
			Object::setColor(0, 0, 0);
			Object::drawContainedText(this->blocks[labelBlock].x + 20, 
						  this->blocks[labelBlock].y + this->blocks[labelBlock].h/3, 
						  this->blocks[labelBlock].z + 1, 
						  this->label, 
						  GLUT_BITMAP_HELVETICA_12
			);

			/* Input Field */
			this->blocks[inputFieldBlock].x = this->x + this->w/3;
                        this->blocks[inputFieldBlock].y = this->y+(this->h/4);
                        this->blocks[inputFieldBlock].z = this->z+1;
                        this->blocks[inputFieldBlock].w = this->w - this->w/3 - 20;
                        this->blocks[inputFieldBlock].h = this->h/2;
			for(int i=0; i<3; i++)
				this->blocks[inputFieldBlock].color[i] = this->blocks[labelBlock].color[i];
			
			// border
			Object::setColor(0, 0, 0);
                        Object::drawContainedRectangle(this->blocks[inputFieldBlock].x - 5, 
						       this->blocks[inputFieldBlock].y - 5, 
						       this->blocks[inputFieldBlock].z, 
						       this->blocks[inputFieldBlock].w + 10, 
						       this->blocks[inputFieldBlock].h + 10
			);
			// input
			if(this->mousePassiveHover == 0){
                        	Object::setColor(this->blocks[inputFieldBlock].color[0], 
						 this->blocks[inputFieldBlock].color[1], 
						 this->blocks[inputFieldBlock].color[2]
				);
			}else{
				Object::setColor(this->hoverColor[0], this->hoverColor[1], this->hoverColor[2]);		
			}
                        Object::drawContainedRectangle(this->blocks[inputFieldBlock].x, 
						       this->blocks[inputFieldBlock].y, 
						       this->blocks[inputFieldBlock].z + 1, 
						       this->blocks[inputFieldBlock].w, 
						       this->blocks[inputFieldBlock].h
			);
			// default
			Object::setColor(0, 0, 0);
			Object::drawContainedTextArray(this->blocks[inputFieldBlock].x + 5, 
						       this->blocks[inputFieldBlock].y + 20, 
						       this->blocks[inputFieldBlock].z + 2, 
						       this->blocks[inputFieldBlock].w, 
						       this->blocks[inputFieldBlock].h, 
						       this->defaultValue, 
						       GLUT_BITMAP_HELVETICA_12, 
						       18, 
						       this->maxXOverflow
			);
		}
};
