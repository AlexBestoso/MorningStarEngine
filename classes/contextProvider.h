#include "../pages/pageLinker.h"
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
					//login
					break;
				default:
					this->current_context = setupPage.runPage();
					break;
			}
		}
		
		void mouseClickContextSwitch(int button, int state, int x, int y){
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        this->current_context = setupPage.handleMouseClick(button, state, x, y);
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
                                        //login
                                        break;
                                default:
                                        this->current_context = setupPage.handleMousePassive(x, y);
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

		void keydownContextSwitch(){
                        switch(this->current_context){
                                case 1:
                                        //login
                                        break;
                                default:
                                        //this->current_context = setupPage.runPage();
                                        break;
                        }
                }

		void keyupContextSwitch(){
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
