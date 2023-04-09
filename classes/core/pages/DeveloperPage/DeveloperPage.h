#include "./popups/linker.h"
#include "./DeveloperPage.projectBar.h"
class DeveloperPage : public Page{
	private:
		DeveloperPageProjectBar projectBar;
		int pageContext = 0;
		int projectBarHandler = -1;

                void initPage(){
                        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                }

                void setBackgroundColor(float r, float g, float b){
                        glClearColor(r, g, b, 1);
                }


	public:
		DeveloperPage(int pageId, float bgColor[4]) : Page(pageId, bgColor){
		}

		int mousePassive(float x, float y){
			this->initPage();
			projectBar.mousePassive(x, y);
			return Page::getPageId();
		}
		int mouseClick(int button, int state, float x, float y){
			this->initPage();
			int res = projectBar.mouseClick(button, state, x, y);
			if(projectBar.goToHomepage()){
				return 0;
			}

			return Page::getPageId();
		}
		int run(void){
			Page::run();
			projectBar.run();
                        return Page::getPageId();
                }

};
