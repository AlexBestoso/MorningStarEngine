class ContextProvider{
	private:
		int current_context = 0;
		bool systemInitialized = false;
		float bgColor[4] = {0.25, 0.0, 0.5, 1};

		HomePage *homePage = NULL;
		void initHomePage(void){
			if(homePage == NULL)
				homePage = new HomePage(0, bgColor);
		}
		void destroyHomePage(void){
			if(homePage != NULL){
				delete homePage;
			}
			homePage = NULL;
			
		}

		DeveloperPage *developerPage = NULL;
		void initDeveloperPage(void){
			if(developerPage == NULL){
				developerPage = new DeveloperPage(1, bgColor);
			}
		}
		void destroyDeveloperPage(void){
			delete developerPage;
			developerPage = NULL;
		}
	public:
		ContextProvider(){
		}

		void setContext(int newContext){
			this->current_context = newContext;
		}
		void displayContextSwitch(){
			switch(this->current_context){
				case 1:
					initDeveloperPage();
					this->current_context = developerPage->run();
					if(this->current_context != developerPage->getPageId()){
                                                developerPage->deconstruct();
                                                destroyDeveloperPage();
                                        }
					break;
				default:
					initHomePage();
					this->current_context = homePage->run();
					if(this->current_context != homePage->getPageId()){
						destroyHomePage();
					}
					break;
			}
		}
		
		void mouseClickContextSwitch(int button, int state, int x, int y){
                        switch(this->current_context){
                                case 1:
					initDeveloperPage();
                                        this->current_context = developerPage->mouseClick(button, state, x, y);
					if(this->current_context != developerPage->getPageId()){
                                                developerPage->deconstruct();
						destroyDeveloperPage();
                                        }
                                        break;
                                default:
					initHomePage();
					this->current_context = homePage->mouseClick(button, state, x, y);
					if(this->current_context != homePage->getPageId()){
						destroyHomePage();
					}
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
					initDeveloperPage();
					developerPage->mousePassive(x, y);
                                        break;
                                default:
					initHomePage();
				    	this->current_context = homePage->mousePassive(x, y);
					if(this->current_context != homePage->getPageId()){
						destroyHomePage();
					}
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
					initHomePage();
					this->current_context = homePage->keyDown(key, mouseX, mouseY);
					if(this->current_context != homePage->getPageId()){
						destroyHomePage();
					}
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
