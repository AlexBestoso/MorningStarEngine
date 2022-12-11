#define HOME_PAGE 0
#define HOME_MAIN 0
#define HOME_NEW  1
#define HOME_LOAD 2
class HomePage{
	private:
		SoLoader soLoader;
		SoFunctions functions;

		int pageContext = 0;
		int formObjectHandle = -1;
		
		ObjectForm *forms[3];
		
		ObjectFormButton *mainButtons = new ObjectFormButton[3];
		ObjectFormButton *newButtons = new ObjectFormButton[2];
                ObjectFormButton *loadButtons = new ObjectFormButton[2];
		
		ObjectFormInput *newInputs = new ObjectFormInput[1];
                
		FormSelectList *loadSelectList = new FormSelectList[1];
		
		ObjectFormButton templateButton;


		void initPage(void){
			if(forms[HOME_MAIN] == NULL && forms[HOME_NEW] == NULL && forms[HOME_LOAD] == NULL){
				formObjectHandle = soLoader.openLazy("./objects/forms/formObject/form.object.so");
                        	if(formObjectHandle <= -1){
                        	        fprintf(stderr, "[E] Failed to load ./objects/forms/formObject/form.object.so");
                        	        return;
                        	}
	
                        	this->functions.ObjectForm_create = (ObjectForm*(*)())soLoader.loadSymbol(formObjectHandle, "create_object");
                        	this->functions.ObjectForm_destroy = (void(*)(ObjectForm*))soLoader.loadSymbol(formObjectHandle, "destroy_object");

                        	forms[HOME_MAIN] = (ObjectForm*)this->functions.ObjectForm_create();
                        	forms[HOME_NEW] = (ObjectForm*)this->functions.ObjectForm_create();
                        	forms[HOME_LOAD] = (ObjectForm*)this->functions.ObjectForm_create();

				this->configMainContext();
                        	this->configNewContext();
                        	this->configLoadContext();
			}
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
		void configMainContext(void){
			Display* d = XOpenDisplay(NULL);
	                Screen*  s = DefaultScreenOfDisplay(d);

			// form background
			forms[HOME_MAIN]->config.id = 0;
			forms[HOME_MAIN]->config.name = "InstallConfiguration";
			forms[HOME_MAIN]->config.x = s->width/2 - (s->width/2)/2;
			forms[HOME_MAIN]->config.y = s->height/2 - (s->height/2)/2;
			forms[HOME_MAIN]->config.w = s->width/2;
			forms[HOME_MAIN]->config.h = s->height/2;
			forms[HOME_MAIN]->config.color[0] = .5;
			forms[HOME_MAIN]->config.color[1] = .647;
			forms[HOME_MAIN]->config.color[2] = 0;
			forms[HOME_MAIN]->setFormTexture("./Assets/bitmaps/formBackground.bmp");

			/* Configure the title */
			int titleX = (forms[HOME_MAIN]->config.w + forms[HOME_MAIN]->config.x)-(500+(forms[HOME_MAIN]->config.w-500)/2);
			int titleY = (forms[HOME_MAIN]->config.h + forms[HOME_MAIN]->config.y)-50;
                        forms[HOME_MAIN]->title.setIdAndName(1, "FormTitleObject");
                        forms[HOME_MAIN]->title.setTitle("Main Menu");
                        forms[HOME_MAIN]->title.setPositionAndSize(titleX, titleY, 500, 50);
                        forms[HOME_MAIN]->title.setColor(1, .647, 0);
                        forms[HOME_MAIN]->title.setTextColor(0, 0, 0);
                        forms[HOME_MAIN]->title.setTextPosition(titleX+200, titleY+20);

			/* Configure Form Buttons */
			int buttonX = (forms[HOME_MAIN]->config.x + forms[HOME_MAIN]->config.w) - (200+(forms[HOME_MAIN]->config.w-200)/2);
			int buttonY = (forms[HOME_MAIN]->config.y + forms[HOME_MAIN]->config.h) - (50+(forms[HOME_MAIN]->config.h-50)/4);
			mainButtons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
			mainButtons[0].setNameAndId("NewProject", 2);
			mainButtons[0].setColor(1, 1, 0);
			mainButtons[0].setHoverColor(.75,.75,0);
			mainButtons[0].setButtonText("New");
			mainButtons[0].setTextColor(0, 0, 0);
			mainButtons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
			mainButtons[0].buttonEvent = &newProjectButton;

			buttonX = (forms[HOME_MAIN]->config.x + forms[HOME_MAIN]->config.w) - (200+(forms[HOME_MAIN]->config.w-200)/2);
                        buttonY = (forms[HOME_MAIN]->config.y + forms[HOME_MAIN]->config.h) - (50+(forms[HOME_MAIN]->config.h-50)/4) - 55;
                        mainButtons[1].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        mainButtons[1].setNameAndId("LoadProject", 3);
                        mainButtons[1].setColor(1, 1, 0);
			mainButtons[1].setHoverColor(.75,.75,0);
                        mainButtons[1].setButtonText("Load");
                        mainButtons[1].setTextColor(0, 0, 0);
                        mainButtons[1].setTextPosition(buttonX + 85, buttonY+20, 1);
			mainButtons[1].buttonEvent = &loadProjectButton;

			buttonX = (forms[HOME_MAIN]->config.x + forms[HOME_MAIN]->config.w) - (200+(forms[HOME_MAIN]->config.w-200)/2);
                        buttonY = (forms[HOME_MAIN]->config.y + forms[HOME_MAIN]->config.h) - (50+(forms[HOME_MAIN]->config.h-50)/4) - 55*2;
                        mainButtons[2].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        mainButtons[2].setNameAndId("ExitSoftware", 4);
                        mainButtons[2].setColor(1, 1, 0);
			mainButtons[2].setHoverColor(.75,.75,0);
                        mainButtons[2].setButtonText("Exit");
                        mainButtons[2].setTextColor(0, 0, 0);
                        mainButtons[2].setTextPosition(buttonX + 85, buttonY+20, 1);
			mainButtons[2].buttonEvent = &exitButtonFunction;
						      // button count
			forms[HOME_MAIN]->setButtons(mainButtons, 3);
			
		}

		static int newFormCancelButton(void){
			return 0;
		}

		static int newFormCreateProjectButton(void){
			return 1; 
		}

		void configNewContext(void){
			Display* d = XOpenDisplay(NULL);
                        Screen*  s = DefaultScreenOfDisplay(d);

                        // form background
                        forms[HOME_NEW]->config.id = 0;
                        forms[HOME_NEW]->config.name = "NewProject";
                        forms[HOME_NEW]->config.x = s->width/2 - (s->width/2)/2;
                        forms[HOME_NEW]->config.y = s->height/2 - (s->height/2)/2;
                        forms[HOME_NEW]->config.w = s->width/2;
                        forms[HOME_NEW]->config.h = s->height/2;
                        forms[HOME_NEW]->config.color[0] = .5;
                        forms[HOME_NEW]->config.color[1] = .647;
                        forms[HOME_NEW]->config.color[2] = 0;
                        forms[HOME_NEW]->setFormTexture("./Assets/bitmaps/formBackground.bmp");

			// form title
			int titleX = (forms[HOME_NEW]->config.w + forms[HOME_NEW]->config.x)-(500+(forms[HOME_NEW]->config.w-500)/2);
                        int titleY = (forms[HOME_NEW]->config.h + forms[HOME_NEW]->config.y)-50;
                        forms[HOME_NEW]->title.setIdAndName(1, "FormTitleObject");
                        forms[HOME_NEW]->title.setTitle("New Project");
                        forms[HOME_NEW]->title.setPositionAndSize(titleX, titleY, 500, 50);
                        forms[HOME_NEW]->title.setColor(1, .647, 0);
                        forms[HOME_NEW]->title.setTextColor(0, 0, 0);
                        forms[HOME_NEW]->title.setTextPosition(titleX+200, titleY+20);

			// Form buttons
			int buttonX = (forms[HOME_NEW]->config.x + forms[HOME_NEW]->config.w) - (200+(forms[HOME_NEW]->config.w-200)/2) - 100;
                        int buttonY = (forms[HOME_NEW]->config.y + forms[HOME_NEW]->config.h) - (50+(forms[HOME_NEW]->config.h-50)/4) - 55*4;
                        newButtons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        newButtons[0].setNameAndId("Cancel", 2);
                        newButtons[0].setColor(1, 1, 0);
                        newButtons[0].setHoverColor(.75,.75,0);
                        newButtons[0].setButtonText("Cancel");
                        newButtons[0].setTextColor(0, 0, 0);
                        newButtons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
                        newButtons[0].buttonEvent = &newFormCancelButton;

			buttonX = (forms[HOME_NEW]->config.x + forms[HOME_NEW]->config.w) - (0+(forms[HOME_NEW]->config.w-200)/2) - 80;
                        buttonY = (forms[HOME_NEW]->config.y + forms[HOME_NEW]->config.h) - (50+(forms[HOME_NEW]->config.h-50)/4) - 55*4;
                        newButtons[1].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        newButtons[1].setNameAndId("Create", 3);
                        newButtons[1].setColor(1, 1, 0);
                        newButtons[1].setHoverColor(.75,.75,0);
                        newButtons[1].setButtonText("Create");
                        newButtons[1].setTextColor(0, 0, 0);
                        newButtons[1].setTextPosition(buttonX + 85, buttonY+20, 1);
                        newButtons[1].buttonEvent = &newFormCancelButton;

			forms[HOME_NEW]->setButtons(newButtons, 2);

			// Form Inputs
			int inputX = (forms[HOME_NEW]->config.x + forms[HOME_NEW]->config.w) - (400+125);
			int inputY = (forms[HOME_NEW]->config.y + forms[HOME_NEW]->config.h) - (150);
			newInputs[0].setPositionAndSize(inputX, inputY, 1, 400, 50);
			newInputs[0].setColor(.5, .5, .5);
			newInputs[0].setHoverColor(.25, .25, .25);
			newInputs[0].setFocusColor(1, 1, 1);
			newInputs[0].setTextColor(0, 0, 0);
			newInputs[0].setTextPosition(inputX + 85, inputY+20, 1);
			newInputs[0].setLabelPosition(inputX+5, inputY+20, 1);
			newInputs[0].setLabel("Project Name:");
			newInputs[0].setInputData("Project 1");

			forms[HOME_NEW]->setInputs(newInputs, 1);
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

                void configLoadContext(void){
			Display* d = XOpenDisplay(NULL);
                        Screen*  s = DefaultScreenOfDisplay(d);

                        // form background
                        forms[HOME_LOAD]->config.id = 0;
                        forms[HOME_LOAD]->config.name = "LoadProject";
                        forms[HOME_LOAD]->config.x = s->width/2 - (s->width/2)/2;
                        forms[HOME_LOAD]->config.y = s->height/2 - (s->height/2)/2;
                        forms[HOME_LOAD]->config.w = s->width/2;
                        forms[HOME_LOAD]->config.h = s->height/2;
                        forms[HOME_LOAD]->config.color[0] = .5;
                        forms[HOME_LOAD]->config.color[1] = .647;
                        forms[HOME_LOAD]->config.color[2] = 0;
                        forms[HOME_LOAD]->setFormTexture("./Assets/bitmaps/formBackground.bmp");
			
			// form title
                        int titleX = (forms[HOME_LOAD]->config.w + forms[HOME_LOAD]->config.x)-(500+(forms[HOME_LOAD]->config.w-500)/2);
                        int titleY = (forms[HOME_LOAD]->config.h + forms[HOME_LOAD]->config.y)-50;
                        forms[HOME_LOAD]->title.setIdAndName(1, "FormTitleObject");
                        forms[HOME_LOAD]->title.setTitle("Load Project");
                        forms[HOME_LOAD]->title.setPositionAndSize(titleX, titleY, 500, 50);
                        forms[HOME_LOAD]->title.setColor(1, .647, 0);
                        forms[HOME_LOAD]->title.setTextColor(0, 0, 0);
                        forms[HOME_LOAD]->title.setTextPosition(titleX+200, titleY+20);

			// Form buttons
                        int buttonX = (forms[HOME_LOAD]->config.x + forms[HOME_LOAD]->config.w) - (200+(forms[HOME_LOAD]->config.w-200)/2) - 100;
                        int buttonY = (forms[HOME_LOAD]->config.y + forms[HOME_LOAD]->config.h) - (50+(forms[HOME_LOAD]->config.h-50)/4) - 55*4;
                        loadButtons[0].setPositionAndSize(buttonX, buttonY, 1, 200, 50);
                        loadButtons[0].setNameAndId("Cancel", 2);
                        loadButtons[0].setColor(1, 1, 0);
                        loadButtons[0].setHoverColor(.75,.75,0);
                        loadButtons[0].setButtonText("Cancel");
                        loadButtons[0].setTextColor(0, 0, 0);
                        loadButtons[0].setTextPosition(buttonX + 85, buttonY+20, 1);
                        loadButtons[0].buttonEvent = &newFormCancelButton;
			
			forms[HOME_LOAD]->setButtons(loadButtons, 1);

			// Select List
			int selectX = (forms[HOME_LOAD]->config.w + forms[HOME_LOAD]->config.x)-(500+(forms[HOME_LOAD]->config.w-500)/2);
			int selectY = (forms[HOME_LOAD]->config.h + forms[HOME_LOAD]->config.y)-(100+50);
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
                        loadSelectList[0].buttonTemplate.setTextColor(0, 0, 0);
                        loadSelectList[0].buttonTemplate.setTextPosition(loadSelectList[0].config.x + 10, loadSelectList[0].config.y+loadSelectList[0].config.h-25, 1);
                        loadSelectList[0].buttonTemplate.buttonEvent_int = &itemSelect;
			
			forms[HOME_LOAD]->setSelectLists(loadSelectList, 1);
		}
	public:
		HomePage(){
			this->initPage();
			this->configMainContext();
			this->configNewContext();
			this->configLoadContext();
		}

		void deconstruct(void){
			for(int i=0; i<3; i++){
				if(forms[i] != NULL){
					this->functions.ObjectForm_destroy(forms[i]);
					forms[i] = NULL;
				}
			}
			if(formObjectHandle > -1){
				soLoader.closeHandle(formObjectHandle);
			}
		}

		int runPage(void){
			this->initPage();
                        switch(this->pageContext){
				case 0: // main menu
                        		this->forms[HOME_MAIN]->draw();
					break;
				case 1: // new project
					this->forms[HOME_NEW]->draw();
					break;
				case 2: // load project
					this->forms[HOME_LOAD]->draw();
				      	break;
			}
			return HOME_PAGE;
		}

		int handleMouseClick(int button, int state, float x, float y){
			this->initPage();
			int buttonOption = -1;
                        switch(this->pageContext){
                        	case 0: // main menue
					/* New Project Button */
					buttonOption = this->forms[HOME_MAIN]->formButtons[0].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						this->pageContext = buttonOption;
						break;
					}
					/* load Project Button */
                                        buttonOption = this->forms[HOME_MAIN]->formButtons[1].mouseClickAction(button, state, x, y);
                                        if(buttonOption != -1){
                                                this->pageContext = buttonOption;
                                                break;
                                        }
					/* Exit button */
					this->forms[HOME_MAIN]->formButtons[2].mouseClickAction(button, state, x, y);
                                        break;
				case 1: // new project
					/* Cancel Button */
					buttonOption = this->forms[HOME_NEW]->formButtons[0].mouseClickAction(button, state, x, y);
                                        if(buttonOption != -1){
                                                this->pageContext = buttonOption;
                                                break;
                                        }
					/* create Button */
					buttonOption = this->forms[HOME_NEW]->formButtons[1].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						project.create(this->forms[HOME_LOAD]->formInputs[0].getInputData());
						return DEVELOPER_PAGE;
					}
					/* Project Name Input */
					this->forms[HOME_NEW]->formInputs[0].mouseClickAction(button, state, x, y);

					break;
				case 2: // load project
					/* Cancel Button */
					buttonOption = this->forms[HOME_LOAD]->formButtons[0].mouseClickAction(button, state, x, y);
					if(buttonOption != -1){
						this->pageContext = buttonOption;
						break;
					}
					buttonOption = this->forms[HOME_LOAD]->selectLists[0].mouseClickAction(button, state, x, y);
					if(buttonOption > -1){
						project.load(this->forms[HOME_LOAD]->selectLists[0].buttons[buttonOption].config.label);
						return DEVELOPER_PAGE;
					}
					break;
               		}
                	return HOME_PAGE;
		} 

		int handleKeyDown(unsigned char key, int mouseX, int mouseY){
			this->initPage();
			switch(this->pageContext){
				case 0:
					break;
				case 1:
					this->forms[HOME_NEW]->formInputs[0].keyDownAction(key, mouseX, mouseY);
					break;
				case 2:
					break;
			}
			return HOME_PAGE;
		}

		int handleMousePassive(float x, float y){
			this->initPage();
			switch(this->pageContext){
                        	case 0: // main menu
					this->forms[HOME_MAIN]->formButtons[0].passiveMouseAction(x, y);
					this->forms[HOME_MAIN]->formButtons[1].passiveMouseAction(x, y);
					this->forms[HOME_MAIN]->formButtons[2].passiveMouseAction(x, y);
					break;
				case 1: // new project
					this->forms[HOME_NEW]->formButtons[0].passiveMouseAction(x, y);
					this->forms[HOME_NEW]->formButtons[1].passiveMouseAction(x, y);
					this->forms[HOME_NEW]->formInputs[0].passiveMouseAction(x, y);
					break;
				case 2: // load project
					this->forms[HOME_LOAD]->formButtons[0].passiveMouseAction(x, y);
					this->forms[HOME_LOAD]->selectLists[0].passiveMouseAction(x, y);
					break;
			}
			return HOME_PAGE;
		}
}homePage;
