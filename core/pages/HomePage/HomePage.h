#define HOME_PAGE 0
class HomePage{
	private:
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
		static int newProjectButton(void){
			return 1;
		}

		/*
		 * Main Context Functions and Variables.
		 * */
		ObjectFormButton *mainButtons = new ObjectFormButton[3];
		ObjectForm mainForm;
		void configMainContext(void){
			Display* d = XOpenDisplay(NULL);
	                Screen*  s = DefaultScreenOfDisplay(d);

			// form background
			mainForm.config.id = 0;
			mainForm.config.name = "InstallConfiguration";
			mainForm.config.x = s->width/2 - (s->width/2)/2;
			mainForm.config.y = s->height/2 - (s->height/2)/2;
			mainForm.config.w = s->width/2;
			mainForm.config.h = s->height/2;
			mainForm.config.color[0] = .5;
			mainForm.config.color[1] = .647;
			mainForm.config.color[0] = 0;
			mainForm.setFormTexture("./core/pages/HomePage/Assets/formBackground.bmp");

			/* Configure the title */
			int titleX = (mainForm.config.w + mainForm.config.x)-(500+(mainForm.config.w-500)/2);
			int titleY = (mainForm.config.h + mainForm.config.y)-50;
                        mainForm.title.setIdAndName(1, "FormTitleObject");
                        mainForm.title.setTitle("Main Menu");
                        mainForm.title.setPositionAndSize(titleX, titleY, 500, 50);
                        mainForm.title.setColor(1, .647, 0);
                        mainForm.title.setTextColor(0, 0, 0);
                        mainForm.title.setTextPosition(titleX+200, titleY+20);

			/* Configure Form Buttons */
			int buttonX = (mainForm.config.x + mainForm.config.w) - (200+(mainForm.config.w-200)/2);
			int buttonY = (mainForm.config.y + mainForm.config.h) - (50+(mainForm.config.h-50)/4);
			mainButtons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
			mainButtons[0].setNameAndId("NewProject", 2);
			mainButtons[0].setColor(1, 1, 0);
			mainButtons[0].setHoverColor(.75,.75,0);
			mainButtons[0].setButtonText("New");
			mainButtons[0].setTextColor(1, 1, 1);
			mainButtons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
			mainButtons[0].buttonEvent = &newProjectButton;

			buttonX = (mainForm.config.x + mainForm.config.w) - (200+(mainForm.config.w-200)/2);
                        buttonY = (mainForm.config.y + mainForm.config.h) - (50+(mainForm.config.h-50)/4) - 55;
                        mainButtons[1].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        mainButtons[1].setNameAndId("LoadProject", 3);
                        mainButtons[1].setColor(1, 1, 0);
			mainButtons[1].setHoverColor(.75,.75,0);
                        mainButtons[1].setButtonText("Load");
                        mainButtons[1].setTextColor(1, 1, 1);
                        mainButtons[1].setTextPosition(buttonX + 85, buttonY+20, 1);

			buttonX = (mainForm.config.x + mainForm.config.w) - (200+(mainForm.config.w-200)/2);
                        buttonY = (mainForm.config.y + mainForm.config.h) - (50+(mainForm.config.h-50)/4) - 55*2;
                        mainButtons[2].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        mainButtons[2].setNameAndId("ExitSoftware", 4);
                        mainButtons[2].setColor(1, 1, 0);
			mainButtons[2].setHoverColor(.75,.75,0);
                        mainButtons[2].setButtonText("Exit");
                        mainButtons[2].setTextColor(1, 1, 1);
                        mainButtons[2].setTextPosition(buttonX + 85, buttonY+20, 1);
			mainButtons[2].buttonEvent = &exitButtonFunction;
						      // button count
			mainForm.setButtons(mainButtons, 3);
			
		}

		static int loadFormCancelButton(void){
			return 0;
		}

		static int loadFormCreateProjectButton(void){
			return 1; 
		}

		ObjectForm loadForm;
		ObjectFormButton *loadButtons = new ObjectFormButton[2];
		ObjectFormInput *loadInputs = new ObjectFormInput[1];
		void configLoadContext(void){
			Display* d = XOpenDisplay(NULL);
                        Screen*  s = DefaultScreenOfDisplay(d);

                        // form background
                        loadForm.config.id = 0;
                        loadForm.config.name = "NewProject";
                        loadForm.config.x = s->width/2 - (s->width/2)/2;
                        loadForm.config.y = s->height/2 - (s->height/2)/2;
                        loadForm.config.w = s->width/2;
                        loadForm.config.h = s->height/2;
                        loadForm.config.color[0] = .5;
                        loadForm.config.color[1] = .647;
                        loadForm.config.color[0] = 0;
                        loadForm.setFormTexture("./core/pages/HomePage/Assets/formBackground.bmp");

			// form title
			int titleX = (loadForm.config.w + loadForm.config.x)-(500+(loadForm.config.w-500)/2);
                        int titleY = (loadForm.config.h + loadForm.config.y)-50;
                        loadForm.title.setIdAndName(1, "FormTitleObject");
                        loadForm.title.setTitle("New Project");
                        loadForm.title.setPositionAndSize(titleX, titleY, 500, 50);
                        loadForm.title.setColor(1, .647, 0);
                        loadForm.title.setTextColor(0, 0, 0);
                        loadForm.title.setTextPosition(titleX+200, titleY+20);

			// Form buttons
			int buttonX = (loadForm.config.x + loadForm.config.w) - (200+(loadForm.config.w-200)/2) - 100;
                        int buttonY = (loadForm.config.y + loadForm.config.h) - (50+(loadForm.config.h-50)/4) - 55*4;
                        loadButtons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        loadButtons[0].setNameAndId("Cancel", 2);
                        loadButtons[0].setColor(1, 1, 0);
                        loadButtons[0].setHoverColor(.75,.75,0);
                        loadButtons[0].setButtonText("Cancel");
                        loadButtons[0].setTextColor(1, 1, 1);
                        loadButtons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
                        loadButtons[0].buttonEvent = &loadFormCancelButton;

			buttonX = (loadForm.config.x + loadForm.config.w) - (0+(loadForm.config.w-200)/2) - 80;
                        buttonY = (loadForm.config.y + loadForm.config.h) - (50+(loadForm.config.h-50)/4) - 55*4;
                        loadButtons[1].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        loadButtons[1].setNameAndId("Create", 3);
                        loadButtons[1].setColor(1, 1, 0);
                        loadButtons[1].setHoverColor(.75,.75,0);
                        loadButtons[1].setButtonText("Create");
                        loadButtons[1].setTextColor(1, 1, 1);
                        loadButtons[1].setTextPosition(buttonX + 85, buttonY+20, 1);
                        loadButtons[1].buttonEvent = &loadFormCancelButton;

			loadForm.setButtons(loadButtons, 2);

			// Form Inputs
			int inputX = (loadForm.config.x + loadForm.config.w) - (400+125);
			int inputY = (loadForm.config.y + loadForm.config.h) - (150);
			loadInputs[0].setPositionAndSize(inputX, inputY, 1, 400, 50);
			loadInputs[0].setColor(.5, .5, .5);
			loadInputs[0].setHoverColor(.25, .25, .25);
			loadInputs[0].setFocusColor(1, 1, 1);
			loadInputs[0].setTextColor(0, 0, 0);
			loadInputs[0].setTextPosition(inputX + 85, inputY+20, 1);
			loadInputs[0].setLabelPosition(inputX+5, inputY+20, 1);
			loadInputs[0].setLabel("Project Name:");
			loadInputs[0].setInputData("Project 1");

			loadForm.setInputs(loadInputs, 1);
		}
	public:
		HomePage(){
			this->configMainContext();
			this->configLoadContext();
		}

		int runPage(void){
			this->initPage();
                               switch(this->pageContext){
				case 0: // main menu
                        		this->mainForm.draw();
					break;
				case 1: // new project
					this->loadForm.draw();
					break;
				case 2: // load project
				      	break;
			}
			return HOME_PAGE;
		}

		int handleMouseClick(int button, int state, float x, float y){
			int buttonOption = -1;
                        switch(this->pageContext){
                        	case 0: // main menue
					/* New Project Button */
					buttonOption = this->mainForm.formButtons[0].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						this->pageContext = buttonOption;
						break;
					}
					/* Exit button */
					this->mainForm.formButtons[2].mouseClickAction(button, state, x, y);
                                        break;
				case 1: // new project
					/* Cancel Button */
					buttonOption = this->loadForm.formButtons[0].mouseClickAction(button, state, x, y);
                                        if(buttonOption != -1){
                                                this->pageContext = buttonOption;
                                                break;
                                        }
					/* create Button */
					buttonOption = this->loadForm.formButtons[1].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						printf("creating project\n");
						project.create(this->loadForm.formInputs[0].getInputData());
					}
					/* Project Name Input */
					this->loadForm.formInputs[0].mouseClickAction(button, state, x, y);

					break;
				case 2: // load project
					break;
               		}
                	return HOME_PAGE;
		} 

		int handleKeyDown(unsigned char key, int mouseX, int mouseY){
			switch(this->pageContext){
				case 0:
					break;
				case 1:
					this->loadForm.formInputs[0].keyDownAction(key, mouseX, mouseY);
					break;
				case 2:
					break;
			}
			return HOME_PAGE;
		}

		int handleMousePassive(float x, float y){
			switch(this->pageContext){
                        	case 0: // main menu
					this->mainForm.formButtons[0].passiveMouseAction(x, y);
					this->mainForm.formButtons[1].passiveMouseAction(x, y);
					this->mainForm.formButtons[2].passiveMouseAction(x, y);
					break;
				case 1: // new project
					this->loadForm.formButtons[0].passiveMouseAction(x, y);
					this->loadForm.formButtons[1].passiveMouseAction(x, y);
					this->loadForm.formInputs[0].passiveMouseAction(x, y);
					break;
				case 2: // load project
					break;
			}
			return HOME_PAGE;
		}
}homePage;
