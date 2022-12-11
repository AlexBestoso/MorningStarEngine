#include "./ProjectBar.element.h"
#include "./SimulationWindow.element.h"
class DeveloperPage{
	private:
		ProjectBar projectBar;
		//SimulationWindow simulationWindow;
		int pageContext = 0;
		int projectBarHandler = -1;

                void initPage(){
			projectBar.init();
                        this->setBackgroundColor(.25,0,.5);
                        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                }

                void setBackgroundColor(float r, float g, float b){
                        glClearColor(r, g, b, 1);
                }

		void drawMainContext(void){
			this->projectBar.draw();
		//	this->simulationWindow.draw();
		}

	public:
		DeveloperPage(){
			this->initPage();
		}

		void deconstruct(void){
			projectBar.reset();
		}
		void passiveMouseAction(float x, float y){
			this->initPage();
			projectBar.passiveMouseAction(x, y);
		//	simulationWindow.passiveMouseAction(x, y);
		}
		int mouseClickAction(int button, int state, float x, float y){
			this->initPage();
			int res = projectBar.mouseClickAction(button, state, x, y);
			if(res == HOME_PAGE){
				projectBar.reset();
				return HOME_PAGE;
			}
		//	res = simulationWindow.mouseClickAction(button, state, x, y);
			return DEVELOPER_PAGE;
		}
		int runPage(void){
			this->initPage();
                        switch(this->pageContext){
                                case 0: // main menu
                                        this->drawMainContext();
					break;
                        }
                        return DEVELOPER_PAGE;
                }

}developerPage;
