#define HOME_PAGE 0
class HomePage{
	private:
                size_t inputCount = 0;
                size_t buttonCount = 0;
		ObjectFormInput *inputs = new ObjectFormInput[3];
		ObjectFormButton *buttons = new ObjectFormButton[3];
		ObjectForm configForm;
		int pageContext = 0;

		void initPage(){
			this->setBackgroundColor(.25,0,.5);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		}

		void setBackgroundColor(float r, float g, float b){
			glClearColor(r, g, b, 1);
		}


		static int exitButtonFunction(void){
			exit(EXIT_SUCCESS);
		}
	public:
		HomePage(){
			Display* d = XOpenDisplay(NULL);
	                Screen*  s = DefaultScreenOfDisplay(d);

			// form background
			configForm.config.id = 0;
			configForm.config.name = "InstallConfiguration";
			configForm.config.x = s->width/2 - (s->width/2)/2;
			configForm.config.y = s->height/2 - (s->height/2)/2;
			configForm.config.w = s->width/2;
			configForm.config.h = s->height/2;
			configForm.config.color[0] = .5;
			configForm.config.color[1] = .647;
			configForm.config.color[0] = 0;
			configForm.setFormTexture("./core/pages/HomePage/Assets/formBackground.bmp");

			/* Configure the title */
			int titleX = (configForm.config.w + configForm.config.x)-(500+(configForm.config.w-500)/2);
			int titleY = (configForm.config.h + configForm.config.y)-50;
                        configForm.title.setIdAndName(1, "FormTitleObject");
                        configForm.title.setTitle("Main Menu");
                        configForm.title.setPositionAndSize(titleX, titleY, 500, 50);
                        configForm.title.setColor(1, .647, 0);
                        configForm.title.setTextColor(0, 0, 0);
                        configForm.title.setTextPosition(titleX+200, titleY+20);

			/* Configure Form Buttons */
			int buttonX = (configForm.config.x + configForm.config.w) - (200+(configForm.config.w-200)/2);
			int buttonY = (configForm.config.y + configForm.config.h) - (50+(configForm.config.h-50)/4);

			buttonCount = 3;
			buttons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
			buttons[0].setNameAndId("NewProject", 2);
			buttons[0].setColor(1, 1, 0);
			buttons[0].setHoverColor(.75,.75,0);
			buttons[0].setButtonText("New");
			buttons[0].setTextColor(1, 1, 1);
			buttons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
			buttons[0].buttonEvent = &exitButtonFunction;

			buttonX = (configForm.config.x + configForm.config.w) - (200+(configForm.config.w-200)/2);
                        buttonY = (configForm.config.y + configForm.config.h) - (50+(configForm.config.h-50)/4) - 55;

                        buttons[1].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        buttons[1].setNameAndId("LoadProject", 3);
                        buttons[1].setColor(1, 1, 0);
			buttons[1].setHoverColor(.75,.75,0);
                        buttons[1].setButtonText("Load");
                        buttons[1].setTextColor(1, 1, 1);
                        buttons[1].setTextPosition(buttonX + 85, buttonY+20, 1);

			buttonX = (configForm.config.x + configForm.config.w) - (200+(configForm.config.w-200)/2);
                        buttonY = (configForm.config.y + configForm.config.h) - (50+(configForm.config.h-50)/4) - 55*2;

                        buttons[2].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        buttons[2].setNameAndId("ExitSoftware", 4);
                        buttons[2].setColor(1, 1, 0);
			buttons[2].setHoverColor(.75,.75,0);
                        buttons[2].setButtonText("Exit");
                        buttons[2].setTextColor(1, 1, 1);
                        buttons[2].setTextPosition(buttonX + 85, buttonY+20, 1);
			
			configForm.setButtons(buttons, buttonCount);
		}

		int runPage(void){
			this->initPage();
                               switch(this->pageContext){
				case 0: // main menu
                        		configForm.draw();
					break;
				case 1: // new project
					break;
				case 2: // load project
				      	break;
			}
			return HOME_PAGE;
		}

		int handleMouseClick(int button, int state, float x, float y){
                                switch(this->pageContext){
                                        case 0: // main menue
						/* Exit button */
						this->configForm.formButtons[2].mouseClickAction(button, state, x, y);
                                                break;
					case 1: // new project
						break;
					case 2: // load project
						break;
                                }
                                return HOME_PAGE;
		} 

		int handleMousePassive(float x, float y){
				switch(this->pageContext){
                                        case 0: // main menu
						this->configForm.formButtons[0].passiveMouseAction(x, y);
						this->configForm.formButtons[1].passiveMouseAction(x, y);
						this->configForm.formButtons[2].passiveMouseAction(x, y);
						break;
					case 1: // new project
						break;
					case 2: // load project
						break;
				}
				return HOME_PAGE;
		}
}homePage;
