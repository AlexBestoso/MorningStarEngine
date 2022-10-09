#include "./ProjectBar.element.h"
class DeveloperPage{
	private:
		ProjectBar projectBar;
		int pageContext = 0;

                void initPage(){
                        this->setBackgroundColor(.25,0,.5);
                        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                }

                void setBackgroundColor(float r, float g, float b){
                        glClearColor(r, g, b, 1);
                }

		void drawPage(void){
			this->projectBar.draw();
		}

	public:
		void passiveMouseAction(float x, float y){
			projectBar.passiveMouseAction(x, y);
		}
		int mouseClickAction(int button, int state, float x, float y){
			return projectBar.mouseClickAction(button, state, x, y);
		}
		int runPage(void){
			this->initPage();
                        switch(this->pageContext){
                                case 0: // main menu
                                        this->drawPage();
					break;
                        }
                        return DEVELOPER_PAGE;
                }

}developerPage;
