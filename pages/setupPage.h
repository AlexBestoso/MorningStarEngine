#define SETUP_PAGE 0
class SetupPage{
	private:
                size_t inputCount = 0;
		ObjectFormInput *inputs = new ObjectFormInput[3];
		ObjectFormTitle installFormTitle;
		ObjectForm configForm;
		int pageContext = 0;

		void initPage(){
			this->setBackgroundColor(.5,0,.5);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		}

		void setBackgroundColor(float r, float g, float b){
			glClearColor(r, g, b, 1);
		}

		struct ObjectFormStruct formStruct = {
			.id = 0,
        		.name = "InstallConfiguration",
        		.x = 200,
        		.y = 100,
        		.w = 600,
        		.h = 300,
        		.color = {1, .647, 0}
		};

	public:
		SetupPage(){
			inputCount = 3;
			/* Configure the title */
                        installFormTitle.setIdAndName(1, "FormTitleObject");
                        installFormTitle.setTitle("Configure Musical Typewriter");
                        installFormTitle.setPositionAndSize(250, 400, 500, 50);
                        installFormTitle.setConstraints(formStruct.x, formStruct.y, formStruct.w, formStruct.h);
                        installFormTitle.setColor(1, .647, 0);
                        installFormTitle.setTextColor(0, 0, 0);
                        installFormTitle.setTextPosition(250, 410);

                        /* Configure Form Inputs */
                        inputs[0].setPositionAndSize(250, 300, 1, 500, 100);
                        inputs[0].setNameAndId("StorageLocation", 2);
                        inputs[0].setConstraints(formStruct.x, formStruct.y, formStruct.w, formStruct.h);
                        inputs[0].setColor(1, .647, 0);
                        inputs[0].setLabelColor(1, 1, 1);
                        inputs[0].setLabel("Storage Dir: ");
                        inputs[0].setDefaultValue(settings.getDataStorageLocation());
                        inputs[0].setMaxXOverflow(15);
			inputs[0].setHoverColor(.5, .5, .5);

                        inputs[1].setPositionAndSize(250, 300-100, 1, 500, 100);
                        inputs[1].setNameAndId("StorageLocation", 2);
                        inputs[1].setConstraints(formStruct.x, formStruct.y, formStruct.w, formStruct.h);
                        inputs[1].setColor(1, .647, 0);
                        inputs[1].setLabelColor(1, 1, 1);
                        inputs[1].setLabel("key Pass: ");
			inputs[1].setHoverColor(.5, .5, .5);

			inputs[2].setPositionAndSize(250, 300-200, 1, 500, 100);
                        inputs[2].setNameAndId("StorageLocation", 2);
                        inputs[2].setConstraints(formStruct.x, formStruct.y, formStruct.w, formStruct.h);
                        inputs[2].setColor(1, .647, 0);
                        inputs[2].setLabelColor(1, 1, 1);
                        inputs[2].setLabel("IV Pass: ");	
			inputs[2].setHoverColor(.5, .5, .5);

			ObjectForm configForm(formStruct, installFormTitle, inputs, inputCount);
			this->configForm = configForm;
		}

		int runPage(){
			//ObjectForm configForm(formStruct, installFormTitle, inputs, inputCount);
			if(!settings.isInstalled()){
				this->initPage();
                                switch(this->pageContext){
					case 0:
                        			configForm.draw();
						this->pageContext = 1;
						break;
					case 1: // security context
                        			configForm.draw();
						break;
				}
				return SETUP_PAGE;
                        }else{
				return 1;
                        }
		}

		int handleMouseClick(int button, int state, float x, float y){
                        if(!settings.isInstalled()){
                                switch(this->pageContext){
                                        case 1: // only invoke in the security context
                                                this->configForm.mouseClickAction(button, state, x, y);
                                                break;
                                }
                                return SETUP_PAGE;
                        }else{
                                return 1;
                        }
                

		int handleMousePassive(float x, float y){
			if(!settings.isInstalled()){
				switch(this->pageContext){
                                        case 1: // only invoke in the security context
						this->configForm.passiveMouseAction(x, y);
						break;
				}
				return SETUP_PAGE;
			}else{
				return 1;
			}
		}
}setupPage;
