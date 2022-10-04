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
		static int loadProjectButton(void){
			return 2;
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
			mainButtons[1].buttonEvent = &loadProjectButton;

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

		static int newFormCancelButton(void){
			return 0;
		}

		static int newFormCreateProjectButton(void){
			return 1; 
		}

		ObjectForm newForm;
		ObjectFormButton *newButtons = new ObjectFormButton[2];
		ObjectFormInput *newInputs = new ObjectFormInput[1];
		void configNewContext(void){
			Display* d = XOpenDisplay(NULL);
                        Screen*  s = DefaultScreenOfDisplay(d);

                        // form background
                        newForm.config.id = 0;
                        newForm.config.name = "NewProject";
                        newForm.config.x = s->width/2 - (s->width/2)/2;
                        newForm.config.y = s->height/2 - (s->height/2)/2;
                        newForm.config.w = s->width/2;
                        newForm.config.h = s->height/2;
                        newForm.config.color[0] = .5;
                        newForm.config.color[1] = .647;
                        newForm.config.color[0] = 0;
                        newForm.setFormTexture("./core/pages/HomePage/Assets/formBackground.bmp");

			// form title
			int titleX = (newForm.config.w + newForm.config.x)-(500+(newForm.config.w-500)/2);
                        int titleY = (newForm.config.h + newForm.config.y)-50;
                        newForm.title.setIdAndName(1, "FormTitleObject");
                        newForm.title.setTitle("New Project");
                        newForm.title.setPositionAndSize(titleX, titleY, 500, 50);
                        newForm.title.setColor(1, .647, 0);
                        newForm.title.setTextColor(0, 0, 0);
                        newForm.title.setTextPosition(titleX+200, titleY+20);

			// Form buttons
			int buttonX = (newForm.config.x + newForm.config.w) - (200+(newForm.config.w-200)/2) - 100;
                        int buttonY = (newForm.config.y + newForm.config.h) - (50+(newForm.config.h-50)/4) - 55*4;
                        newButtons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        newButtons[0].setNameAndId("Cancel", 2);
                        newButtons[0].setColor(1, 1, 0);
                        newButtons[0].setHoverColor(.75,.75,0);
                        newButtons[0].setButtonText("Cancel");
                        newButtons[0].setTextColor(1, 1, 1);
                        newButtons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
                        newButtons[0].buttonEvent = &newFormCancelButton;

			buttonX = (newForm.config.x + newForm.config.w) - (0+(newForm.config.w-200)/2) - 80;
                        buttonY = (newForm.config.y + newForm.config.h) - (50+(newForm.config.h-50)/4) - 55*4;
                        newButtons[1].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        newButtons[1].setNameAndId("Create", 3);
                        newButtons[1].setColor(1, 1, 0);
                        newButtons[1].setHoverColor(.75,.75,0);
                        newButtons[1].setButtonText("Create");
                        newButtons[1].setTextColor(1, 1, 1);
                        newButtons[1].setTextPosition(buttonX + 85, buttonY+20, 1);
                        newButtons[1].buttonEvent = &newFormCancelButton;

			newForm.setButtons(newButtons, 2);

			// Form Inputs
			int inputX = (newForm.config.x + newForm.config.w) - (400+125);
			int inputY = (newForm.config.y + newForm.config.h) - (150);
			newInputs[0].setPositionAndSize(inputX, inputY, 1, 400, 50);
			newInputs[0].setColor(.5, .5, .5);
			newInputs[0].setHoverColor(.25, .25, .25);
			newInputs[0].setFocusColor(1, 1, 1);
			newInputs[0].setTextColor(0, 0, 0);
			newInputs[0].setTextPosition(inputX + 85, inputY+20, 1);
			newInputs[0].setLabelPosition(inputX+5, inputY+20, 1);
			newInputs[0].setLabel("Project Name:");
			newInputs[0].setInputData("Project 1");

			newForm.setInputs(newInputs, 1);
		}

		static string *getProjectList(void){
			string *ret = NULL;
			FileSnake fileSnake;
			Project p;
			ret = fileSnake.listDir(p.getProjectDir());
			return ret;
		}

		static size_t getProjectCount(string *list){
			size_t track = 0;
                        while(list[track] != ""){
                                track++;
                        }
			return track;
		}

		static int itemSelect(int ret){
			return ret;
		}

		ObjectForm loadForm;
                ObjectFormButton *loadButtons = new ObjectFormButton[2];
                FormSelectList *loadSelectList = new FormSelectList[1];
		ObjectFormButton templateButton;
                void configLoadContext(void){
			Display* d = XOpenDisplay(NULL);
                        Screen*  s = DefaultScreenOfDisplay(d);

                        // form background
                        loadForm.config.id = 0;
                        loadForm.config.name = "LoadProject";
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
                        loadForm.title.setTitle("Load Project");
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
                        loadButtons[0].buttonEvent = &newFormCancelButton;
			
			loadForm.setButtons(loadButtons, 1);

			// Select List
			int selectX = (loadForm.config.w + loadForm.config.x)-(500+(loadForm.config.w-500)/2);
			int selectY = (newForm.config.h + newForm.config.y)-(100+50);
			loadSelectList[0].config.x = selectX;
			loadSelectList[0].config.y = selectY-150;
			loadSelectList[0].config.w = 500;
			loadSelectList[0].config.h = 100+150;
			loadSelectList[0].setContainerColor(.50, .50, .50);
			loadSelectList[0].fetchList = &getProjectList;
			loadSelectList[0].fetchListCount = &getProjectCount;

			loadSelectList[0].buttonTemplate.setPositionAndSize(loadSelectList[0].config.x, loadSelectList[0].config.y+loadSelectList[0].config.h-50, 1, 100, 50);
                        loadSelectList[0].buttonTemplate.setNameAndId("selectButton", 2);
                        loadSelectList[0].buttonTemplate.setColor(1, 1, 0);
                        loadSelectList[0].buttonTemplate.setHoverColor(.75,.75,0);
                        loadSelectList[0].buttonTemplate.setTextColor(1, 1, 1);
                        loadSelectList[0].buttonTemplate.setTextPosition(loadSelectList[0].config.x + 10, loadSelectList[0].config.y+loadSelectList[0].config.h-25, 1);
                        loadSelectList[0].buttonTemplate.buttonEvent_int = &itemSelect;
			
			loadForm.setSelectLists(loadSelectList, 1);
		}
	public:
		HomePage(){
			this->configMainContext();
			this->configNewContext();
			this->configLoadContext();
		}

		int runPage(void){
			this->initPage();
                               switch(this->pageContext){
				case 0: // main menu
                        		this->mainForm.draw();
					break;
				case 1: // new project
					this->newForm.draw();
					break;
				case 2: // load project
					this->loadForm.draw();
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
					/* load Project Button */
                                        buttonOption = this->mainForm.formButtons[1].mouseClickAction(button, state, x, y);
                                        if(buttonOption != -1){
                                                this->pageContext = buttonOption;
                                                break;
                                        }
					/* Exit button */
					this->mainForm.formButtons[2].mouseClickAction(button, state, x, y);
                                        break;
				case 1: // new project
					/* Cancel Button */
					buttonOption = this->newForm.formButtons[0].mouseClickAction(button, state, x, y);
                                        if(buttonOption != -1){
                                                this->pageContext = buttonOption;
                                                break;
                                        }
					/* create Button */
					buttonOption = this->newForm.formButtons[1].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						project.create(this->newForm.formInputs[0].getInputData());
						return DEVELOPER_PAGE;
					}
					/* Project Name Input */
					this->newForm.formInputs[0].mouseClickAction(button, state, x, y);

					break;
				case 2: // load project
					/* Cancel Button */
					buttonOption = this->loadForm.formButtons[0].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						this->pageContext = buttonOption;
						break;
					}
					buttonOption = this->loadForm.selectLists[0].mouseClickAction(button, state, x, y);
					if(buttonOption > -1){
						project.load(this->loadForm.selectLists[0].buttons[buttonOption].config.label);
						return DEVELOPER_PAGE;
					}
					break;
               		}
                	return HOME_PAGE;
		} 

		int handleKeyDown(unsigned char key, int mouseX, int mouseY){
			switch(this->pageContext){
				case 0:
					break;
				case 1:
					this->newForm.formInputs[0].keyDownAction(key, mouseX, mouseY);
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
					this->newForm.formButtons[0].passiveMouseAction(x, y);
					this->newForm.formButtons[1].passiveMouseAction(x, y);
					this->newForm.formInputs[0].passiveMouseAction(x, y);
					break;
				case 2: // load project
					this->loadForm.formButtons[0].passiveMouseAction(x, y);
					this->loadForm.selectLists[0].passiveMouseAction(x, y);
					break;
			}
			return HOME_PAGE;
		}
}homePage;
