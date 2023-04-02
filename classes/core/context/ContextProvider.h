class ContextProvider{
	private:
		int current_context = 0;
		bool systemInitialized = false;
		HomePage *homePage = NULL;
	public:
		ContextProvider(){
			float bgColor[4] = {0.25, 0.0, 0.5, 1};
			homePage = new HomePage(0, bgColor);
		}
		void setContext(int newContext){
			this->current_context = newContext;
		}
		void displayContextSwitch(){
			int previousContext = this->current_context;
			switch(this->current_context){
				case 1:
					this->current_context = developerPage.runPage();
					if(this->current_context != previousContext){
                                                developerPage.deconstruct();
                                        }
					break;
				default:
				//	this->current_context = homePage.runPage();
				//	if(this->current_context != previousContext){
                                 //               homePage.deconstruct();
                                 //       }
					this->current_context = homePage->run();
					break;
			}
		}
		
		void mouseClickContextSwitch(int button, int state, int x, int y){
			int previousContext = this->current_context;
                        switch(this->current_context){
                                case 1:
                                        this->current_context = developerPage.mouseClickAction(button, state, x, y);
					if(this->current_context != previousContext){
                                                developerPage.deconstruct();
                                        }
                                        break;
                                default:
                                        //this->current_context = homePage.handleMouseClick(button, state, x, y);
					//if(this->current_context != previousContext){
                                        //        homePage.deconstruct();
                                        //}
					this->current_context = homePage->mouseClick(button, state, x, y);
                                        break;
                        }
                }
	
		void mouseMovementContextSwitch(){
			int previousContext = this->current_context;
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
			int previousContext = this->current_context;
                        switch(this->current_context){
                                case 1:
					developerPage.passiveMouseAction(x, y);
                                        break;
                                default:
                                       // this->current_context = homePage.handleMousePassive(x, y);
				///	if(this->current_context != previousContext){
                                   //             homePage.deconstruct();
                                    //    }
				    	this->current_context = homePage->mousePassive(x, y);
                                        break;
                        }
                }

		void idleContextSwitch(){
			int previousContext = this->current_context;
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
			int previousContext = this->current_context;
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        //this->current_context = homePage.handleKeyDown(key, mouseX, mouseY);
					//if(this->current_context != previousContext){
					//	homePage.deconstruct();
					//}
					this->current_context = homePage->keyDown(key, mouseX, mouseY);
                                        break;
                        }
                }

		void keyupContextSwitch(unsigned char key, int mouseX, int mouseY){
			int previousContext = this->current_context;
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
