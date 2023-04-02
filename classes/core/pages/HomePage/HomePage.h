#define HOME_PAGE 0
#define HOME_MAIN 0
#define HOME_NEW  1
#define HOME_LOAD 2
#include "./HomePage.mainMenu.h"
#include "./HomePage.aboutMenu.h"
#include "./HomePage.newProject.h"
#include "./HomePage.loadProject.h"
class HomePage : public Page{
	private:
		int pageContext = 0;
		HomePageMainMenu mainMenu;
		HomePageAboutMenu aboutMenu;
		HomePageNewProject newProjectMenu;
		HomePageLoadProject loadProjectMenu;
		
	public:
		HomePage(int pageId, float bgColor[4]) : Page(pageId, bgColor){
		}
		
		int run(){
			Page::run();
			switch(pageContext){
				case 1:
					newProjectMenu.run();
					break;
				case 2:
					loadProjectMenu.run();
					break;
				case 3:
					aboutMenu.run();
					break;
				default:
					mainMenu.run();
					break;
			}
			return getPageId();
		}

		int mousePassive(float x, float y){
			//Page::mousePassive(x, y);
			switch(pageContext){
				case 1:
                                        newProjectMenu.mousePassive(x, y);
                                        break;
                                case 2:
                                        loadProjectMenu.mousePassive(x, y);
                                        break;
				case 3: 
					aboutMenu.mousePassive(x, y);
				default:
					mainMenu.mousePassive(x, y);
					break;
			}
			return getPageId();
		}

		int mouseClick(int button, int state, float x, float y){
			//Page::mouseClick(button, state, x, y);
			if(pageContext == 0){
				int clickCode = mainMenu.mouseClick(button, state, x, y);
				if(clickCode != -1 && (clickCode&0b1) == 1 && (clickCode>>1) == 0){
					switch(mainMenu.getClickedButton()){
						case 0:
							pageContext = 1;
							break;
						case 1:
							pageContext = 2;
							break;
						case 2:
							pageContext = 3;
							break;
						case 3:
							exit(EXIT_SUCCESS);
							break;
					}
				}
			}else if(pageContext == 1){
				int clickCode = newProjectMenu.mouseClick(button, state, x, y);
                                if(clickCode != -1 && (clickCode&0b1) == 1 && (clickCode>>1) == 0){
                                        switch(newProjectMenu.getClickedButton()){
                                                case 0:
                                                        pageContext = 0;
                                                        break;
                                        }
                                }
			}else if(pageContext == 2){
				int clickCode = loadProjectMenu.mouseClick(button, state, x, y);
                                if(clickCode != -1 && (clickCode&0b1) == 1 && (clickCode>>1) == 0){
                                        switch(loadProjectMenu.getClickedButton()){
                                                case 0:
                                                        pageContext = 0;
                                                        break;
                                        }
                                }
			}else if(pageContext == 3){
				int clickCode = aboutMenu.mouseClick(button, state, x, y);
                                if(clickCode != -1 && (clickCode&0b1) == 1 && (clickCode>>1) == 0){
					switch(aboutMenu.getClickedButton()){
						case 0:
							pageContext = 0;
							break;
					}
				}
			}
			return getPageId();
		}
};
