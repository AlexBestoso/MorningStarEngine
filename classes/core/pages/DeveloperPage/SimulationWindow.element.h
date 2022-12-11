class SimulationWindow : Periferals{
	private:
	//	ObjectForm simulationForm;
		FormContextMenu rightClickMenu;
		ObjectFormButton rightClickButtonTemplate;
		bool simulationFormInitalized = false;
		bool rightClicked = false;
		int popUpId = 0;

		static int rightClickChangeBGColor(void){
			return 1;
		}
		
		void init(void){
			Display* d = XOpenDisplay(NULL);
                        Screen* s = DefaultScreenOfDisplay(d);

			/* Form Background */
                /*        simulationForm.config.w = s->width/3*2;
                        simulationForm.config.h = s->height/3*2;
                        simulationForm.config.x = (s->width/4)*2 - simulationForm.config.w/2;
                        simulationForm.config.y = s->height - 90 - simulationForm.config.h - 5;
                        simulationForm.config.color[0] = project.data.startingBgColor[0];
                        simulationForm.config.color[1] = project.data.startingBgColor[1];
                        simulationForm.config.color[2] = project.data.startingBgColor[2];
			simulationForm.config.ignoreTitle = true;

			/* Right Click Menu */
                        //rightClickMenu.config.buttonText = "set default bg color";
			rightClickMenu.config.noFormContainer = true;
                        rightClickMenu.setDropDownColor(.5, .3, 0);
                        rightClickMenu.config.dropDownZ = 1;
                        rightClickMenu.config.dropDownW = 200;
                        rightClickMenu.config.dropDownH = 300;
			rightClickMenu.config.showDropDown = false;

			rightClickMenu.config.buttonCount = 1;
                        rightClickMenu.config.buttons = new ObjectFormButton[rightClickMenu.config.buttonCount];
                        rightClickButtonTemplate.setNameAndId("NewProject", 2);
                        rightClickButtonTemplate.setColor(1, 1, 0);
                        rightClickButtonTemplate.setHoverColor(.75,.75,0);
                        rightClickButtonTemplate.setButtonText("Set Default bgColor");
                        rightClickButtonTemplate.setTextColor(0, 0, 0);
                        //buttonTemplate.buttonEvent = &button_backToHomePage;
                        // button 0
                       	rightClickMenu.config.buttons[0] = rightClickButtonTemplate;
                       	rightClickMenu.config.buttons[0].buttonEvent = &rightClickChangeBGColor;

			simulationFormInitalized = true;
		}
		void setRightClickCoords(float x, float y){
			rightClickMenu.config.dropDownY = (y * -1) + rightClickMenu.config.dropDownH + (rightClickMenu.config.dropDownH/3) + 5;
			rightClickMenu.config.dropDownX = x - 5;
			int buttonX = rightClickMenu.config.dropDownX;
                        int buttonY = rightClickMenu.config.dropDownY + rightClickMenu.config.dropDownH - 25;
			for(int i=0; i<rightClickMenu.config.buttonCount; i++){
				rightClickMenu.config.buttons[i].setPositionAndSize(buttonX, buttonY, 1, 200, 25);
				rightClickMenu.config.buttons[i].setTextPosition(buttonX + 5, buttonY+14, 1);
			}	
		}
	public:
		void passiveMouseAction(float x, float y){
		/*	if((!simulationForm.isInHitBox(x, y) && !rightClickMenu.isInDropDownBox(x, y)) || !this->rightClicked){
				this->rightClicked = false;
				rightClickMenu.config.showDropDown = false;
			}else{
				rightClickMenu.passiveMouseAction(x, y);
			}*/
                }
                int mouseClickAction(int button, int state, float x, float y){
		/*	if(simulationForm.isInHitBox(Periferals::getX(x), Periferals::getY(y)) && Periferals::rightClick(button, state)){
				this->setRightClickCoords(x, y);
				rightClickMenu.config.showDropDown = true;
				this->rightClicked = true;
				return -1;
			}
			if(this->rightClicked && Periferals::leftClick(button, state) && !rightClickMenu.isInDropDownBox(Periferals::getX(x), Periferals::getY(y))){
				this->rightClicked = false;
				rightClickMenu.config.showDropDown = false;
				return -1;
			}
			if(this->rightClicked && rightClickMenu.config.showDropDown){
				this->popUpId = rightClickMenu.mouseClickAction(button, state, x, y);
			}
			
                        return -1;*/
                }
		void draw(void){
			if(!simulationFormInitalized)
				this->init();
			//simulationForm.draw();
			rightClickMenu.draw();
			if(this->popUpId > 0){
				switch(this->popUpId){
					case 1: // set default bg color of game.
						printf("launch popup.\n");
						break;
				}
			}
		}
};
