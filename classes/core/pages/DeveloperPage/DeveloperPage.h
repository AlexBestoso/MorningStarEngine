//#include "./ProjectBar.element.h"
//#include "./SimulationWindow.element.h"
#include "./DeveloperPage.projectBar.h"
class DeveloperPage : public Page{
	private:
		//ProjectBar projectBar;
	//	SimulationWindow simulationWindow;
		DeveloperPageProjectBar projectBar;
		int pageContext = 0;
		int projectBarHandler = -1;

                void initPage(){
			//projectBar.init();
			//simulationWindow.init();
                        //this->setBackgroundColor(.25,0,.5);
                        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                }

                void setBackgroundColor(float r, float g, float b){
                        glClearColor(r, g, b, 1);
                }

		void drawMainContext(void){
			//this->projectBar.draw();
			//this->simulationWindow.draw();
		}

	public:
		DeveloperPage(int pageId, float bgColor[4]) : Page(pageId, bgColor){
			//this->initPage();
		}

		int mousePassive(float x, float y){
			this->initPage();
			projectBar.mousePassive(x, y);
			//simulationWindow.passiveMouseAction(x, y);
			return Page::getPageId();
		}
		int mouseClick(int button, int state, float x, float y){
			this->initPage();
			int res = projectBar.mouseClick(button, state, x, y);
			if(projectBar.getClickedDropDown() == 0 && projectBar.getClickedDropDownOption() == 2 && res == 1){
				return 0; // home page
			}
			//res = simulationWindow.mouseClickAction(button, state, x, y);
			return Page::getPageId();
		}
		int run(void){
			Page::run();
			projectBar.run();
			//	this->initPage();
                 //       switch(this->pageContext){
                  //              case 0: // main menu
                   //                     this->drawMainContext();
		//			break;
                 //       }
                        return Page::getPageId();
                }

};
