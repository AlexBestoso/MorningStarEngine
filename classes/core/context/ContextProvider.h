class ContextProvider{
	private:
		int current_context = 0;
		bool systemInitialized = false;
	public:
		void setContext(int newContext){
			this->current_context = newContext;
		}
		void displayContextSwitch(){
			switch(this->current_context){
				case 1:
					this->current_context = developerPage.runPage();
					break;
				default:
					this->current_context = homePage.runPage();
					break;
			}
		}
		
		void mouseClickContextSwitch(int button, int state, int x, int y){
                        switch(this->current_context){
                                case 1:
                                        this->current_context = developerPage.mouseClickAction(button, state, x, y);
                                        break;
                                default:
                                        this->current_context = homePage.handleMouseClick(button, state, x, y);
                                        break;
                        }
                }
	
		void mouseMovementContextSwitch(){
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        //this->current_context = setupPage.runPage();
                                        break;
                        }
                }

		void mousePassiveContextSwitch(float x, float y){
                        switch(this->current_context){
                                case 1:
					developerPage.passiveMouseAction(x, y);
                                        break;
                                default:
                                        this->current_context = homePage.handleMousePassive(x, y);
                                        break;
                        }
                }

		void idleContextSwitch(){
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        //this->current_context = setupPage.runPage();
                                        break;
                        }
                }

		void keydownContextSwitch(unsigned char key, int mouseX, int mouseY){
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        this->current_context = homePage.handleKeyDown(key, mouseX, mouseY);
                                        break;
                        }
                }

		void keyupContextSwitch(unsigned char key, int mouseX, int mouseY){
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        //this->current_context = setupPage.runPage();
                                        break;
                        }
                }
}context;
