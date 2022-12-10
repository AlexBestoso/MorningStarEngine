struct FormSelectConfig{
	int x = 0;
	int y = 0;
	int z = 0;
	int w = 0;
	int h = 0;
	float color[3] = {0, 0, 0};
	float itemColor[3] = {0, 0, 0};
	float hoverColor[3] = {0, 0, 0};
	int buttonSpacing = 20;
};
class FormSelectList : Object{
	private:
		void drawContainer(void){
			Object::setColor(config.color[0], config.color[1], config.color[2]);
			Object::drawRectangle(config.x, config.y, 1, config.w, config.h);
		}

		bool alreadySpaced = false;
		size_t currentListCount = 0;
		void drawList(void){
			for(int i=0; i<itemCount; i++){
				this->buttons[i].setButtonText(this->itemList[i]);
				if(i > 0 && !alreadySpaced){
                        		this->buttons[i].config.y = this->buttons[i].config.y - (this->buttons[i].config.h*i) - (this->config.buttonSpacing*i);
                        	        this->buttons[i].config.textY = this->buttons[i].config.textY - (this->buttons[i].config.h*i) - (this->config.buttonSpacing*i);
                        	}
				this->buttons[i].draw();
			}
			alreadySpaced = true;
		}

	public:
		string *itemList = NULL;
		size_t itemCount = 0;
		struct FormSelectConfig config;
		string* (*fetchList)(void);
		size_t (*fetchListCount)(string *);
		ObjectFormButton buttonTemplate;
		ObjectFormButton *buttons = NULL;


		void generateList(void){
			if(itemList != NULL)
				delete[] itemList;

			itemList = fetchList();
			itemCount = fetchListCount(this->itemList);

			if(itemCount != currentListCount){
				currentListCount = itemCount;
				delete[] buttons;
				buttons = NULL;
				alreadySpaced = false;
			}
			if(buttons == NULL){
				buttons = new ObjectFormButton[this->itemCount];
				for(int i=0; i<itemCount; i++){
					this->buttons[i] = buttonTemplate;
				}
			}
		}

		void setContainerColor(float r, float g, float b){
			this->config.color[0] = r;
			this->config.color[1] = g;
			this->config.color[2] = b;
		}

		void passiveMouseAction(float x, float y){
			for(int i=0; i<this->itemCount; i++){
				this->buttons[i].passiveMouseAction(x, y);
			}
                }

		int mouseClickAction(int button, int state, float x, float y){
			int ret = -1;
			for(int i=0; i<this->itemCount; i++){
				ret = this->buttons[i].mouseClickAction_intInput(button, state, x, y, i);
				if(ret != -1)
					return ret;
			}
			return -1;
		}

		void setItemColor(float r, float g, float b){
			this->config.itemColor[0] = r;
			this->config.itemColor[1] = g;
			this->config.itemColor[2] = b;
		}

		void setHoverColor(float r, float g, float b){
			this->config.hoverColor[0] = r;
			this->config.hoverColor[1] = g;
			this->config.hoverColor[2] = b;
		}

		void draw(void){
			this->generateList();
			this->drawContainer();
			this->drawList();
		}
};
