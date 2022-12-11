class ObjectFormInput : Object{
	private:
		const int labelBlock = 0;
                const int inputFieldBlock = 1;

                float x, y, z, w, h;
                float textX, textY, textZ, textW, textH;
		float labelX, labelY, labelZ;
                float color[3] = {0, 0, 0};
                float textColor[3] = {0, 0 , 0};
                float hoverColor[3] = {0, 0, 0};
		float focusColor[3] = {0, 0, 0};
                string label = "";
		string inputData = "";

                bool isInHitbox(float x, float y){

                        y = y * -1;
                        float b_x = Object::getX(this->x);
                        float b_y  = Object::getY(this->y);
                        float b_w = Object::getX(this->w + this->x);
                        float b_h  = Object::getY(this->h + this->y);

                        if((x > b_x && x < b_w) && (y > b_y && y < b_h)){
                                return true;
                        }
                        return false;
                }

                int mousePassiveHover = 0;
		bool focused = false;

	public:
                ObjectFormInput(int id, string name){
                        Object::setObjectId(id);
                        Object::setObjectName(name);
                }
                ObjectFormInput(){
                }

                int mouseClickAction(int button, int state, float x, float y){
                        if(mousePassiveHover == 1){
                                if(button == 0 && state == 1){
                                       	this->focused = true;
                                }
                        }else{
				if(button == 0 && state == 1){
                                        this->focused = false;
                                }
			}
                        return -1;
                }
		int keyDownAction(unsigned char key, int mouseX, int mouseY){
			if(this->focused){
				if(key == 0x08){
					if(this->inputData.size() > 0)
						this->inputData.pop_back();
				}else if((key >= 0x61 && key <= 0x7a) || (key >= 0x41 && key <= 0x5a) || (key >= 0x30 && key <= 0x39) || key == 0x20){
					this->inputData += key;
				}else if(key == 0x0d){
					this->focused = false;
				}
			}
		}
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

		void setFocusColor(float r, float g, float b){
			this->focusColor[0] = r;
			this->focusColor[1] = g;
			this->focusColor[2] = b;
		}

		void setConstraints(int x, int y, int w, int h){
                        Object::setConstraints(x, y, w, h);
                }

                void setInputData(string text){
                        this->inputData = text;
                }
		void setLabel(string label){
			this->label = label;
		}
		
		string getInputData(void){
			return this->inputData;	
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
                void setTextColor(float r, float g, float b){
                        this->textColor[0] = r;
                        this->textColor[1] = g;
                        this->textColor[2] = b;
                }
                void setPositionAndSize(float x, float y, float z, float w, float h){
                        this->x = x;
                        this->y = y;
                        this->z = z;
                        this->w = w;
                        this->h = h;
                }
                void setTextPosition(float x, float y, float z){
                        this->textX = x;
                        this->textY = y;
                        this->textZ = z;
                }
		void setLabelPosition(float x, float y, float z){
			this->labelX = x;
			this->labelY = y;
			this->labelZ = z;
		}

		void drawContained(){
                        /* Core Container.*/
                        if(this->focused){
				Object::setColor(this->focusColor[0], this->focusColor[1], this->focusColor[2]);
			}else if(this->mousePassiveHover == 0){
                                Object::setColor(this->color[0], this->color[1], this->color[2]);
                        }else{
                                Object::setColor(this->hoverColor[0], this->hoverColor[1], this->hoverColor[2]);
                        }
                        Object::drawRectangle(this->x, this->y, this->z, this->w, this->h);
			
			/* Label Text*/
                        Object::setColor(this->textColor[0], this->textColor[1], this->textColor[2]);
                        Object::drawText(this->labelX,
                                         this->labelY,
                                         this->labelZ,
                                         this->label,
                                         GLUT_BITMAP_HELVETICA_12
                        );
			
                        /* Input Data Text */
                        Object::setColor(this->textColor[0], this->textColor[1], this->textColor[2]);
                        Object::drawText(this->textX,
                                         this->textY,
                                         this->textZ,
                                         this->inputData,
                                         GLUT_BITMAP_HELVETICA_12
                        );

                }
};
