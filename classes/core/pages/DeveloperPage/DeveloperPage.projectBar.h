class DeveloperPageProjectBar : public Form{
	private:
	/*
	 * Form Components
	 * */
	FormBackground background;
	FormDropDown *dropDowns = new FormDropDown[2];
	DeveloperPageEditPopup editPopup;
	FormButton *buttons = new FormButton[1];
	size_t buttonCount = 1;

	bool goToHomePage = false;
	/* 
	 * Setup Functions
	 * */
	void setupFileDropDown(){
		FormDropDown fileDropdown;
                FormButton button;
                button.setShowButtonText(true);
                button.setButtonText("File");
                button.setCoords(background.getBgX(), background.getBgY(), background.getBgZ());
                button.setButtonTextCoords(
                        button.getButtonX() + .025,
                        button.getButtonY() + .025,
                        button.getButtonZ()
                );
                button.setWidthHeight(.08, background.getBgH());
                button.setButtonColor(.1, .1, .1);
                button.setHoverColor(.2, .2, .2);
                button.setTextColor(.3, .3, .3);
                fileDropdown.setSectionButton(button);
                fileDropdown.setMenuWidthHeight(.3, .5);
                fileDropdown.setMenuCoords(
                        button.getButtonX(),
                        button.getButtonY() - button.getButtonH() - fileDropdown.getMenuH() + .075,
                        button.getButtonZ()
                );
                fileDropdown.setMenuColor(.2, .2, .2);
                fileDropdown.setMaxVisibleOptions(3);
                fileDropdown.setOptionsOffset(.025);
                FormButton *buttons = new FormButton[3];
                buttons[0].setShowButtonText(true);
                buttons[0].setButtonText("Save");
                buttons[0].setButtonColor(.1, .1, .1);
                buttons[0].setHoverColor(.2, .2, .2);
                buttons[0].setTextColor(.3, .3, .3);
                buttons[0].setWidthHeight(fileDropdown.getMenuW(), button.getButtonH());
                buttons[0].setCoords(
                        fileDropdown.getMenuX(),
                        fileDropdown.getMenuY()+fileDropdown.getMenuH()-buttons[0].getButtonH(),
                        fileDropdown.getMenuZ()
                );
		buttons[0].setButtonTextCoords(
                        buttons[0].getButtonX() + .025,
                        buttons[0].getButtonY() + .025,
                        buttons[0].getButtonZ()
                );

                for(int i=1; i<3;i++){
                        buttons[i] = buttons[0];
                }
                buttons[1].setButtonText("Edit");
                buttons[2].setButtonText("Quit");

                fileDropdown.setSectionButtonOptions(buttons, 3);

                dropDowns[0] = fileDropdown;
	}
	
	void setupBuildDropDown(){
		FormDropDown fileDropdown;
                FormButton button;
                button.setShowButtonText(true);
                button.setButtonText("Build");
                button.setCoords(
			background.getBgX() + .090, 
			background.getBgY(), 
			background.getBgZ()
		);
                button.setButtonTextCoords(
                        button.getButtonX() + .015,
                        button.getButtonY() + .025,
                        button.getButtonZ()
                );
                button.setWidthHeight(.08, background.getBgH());
                button.setButtonColor(.1, .1, .1);
                button.setHoverColor(.2, .2, .2);
                button.setTextColor(.3, .3, .3);
                fileDropdown.setSectionButton(button);
                fileDropdown.setMenuWidthHeight(.3, .5);
                fileDropdown.setMenuCoords(
                        button.getButtonX(),
                        button.getButtonY() - button.getButtonH() - fileDropdown.getMenuH() + .075,
                        button.getButtonZ()
                );
                fileDropdown.setMenuColor(.2, .2, .2);
                fileDropdown.setMaxVisibleOptions(3);
                fileDropdown.setOptionsOffset(.025);

                FormButton *buttons = new FormButton[3];
                buttons[0].setShowButtonText(true);
                buttons[0].setButtonText("Compile");
                buttons[0].setButtonColor(.1, .1, .1);
                buttons[0].setHoverColor(.2, .2, .2);
                buttons[0].setTextColor(.3, .3, .3);
                buttons[0].setWidthHeight(fileDropdown.getMenuW(), button.getButtonH());
                buttons[0].setCoords(
                        fileDropdown.getMenuX(),
                        fileDropdown.getMenuY()+fileDropdown.getMenuH()-buttons[0].getButtonH(),
                        fileDropdown.getMenuZ()
                );
		buttons[0].setButtonTextCoords(
                        buttons[0].getButtonX() + .025,
                        buttons[0].getButtonY() + .025,
                        buttons[0].getButtonZ()
                );
		
		for(int i=1; i<3;i++){
                        buttons[i] = buttons[0];
                }
                buttons[1].setButtonText("Run");
                buttons[2].setButtonText("Compile & Run");

		fileDropdown.setSectionButtonOptions(buttons, 3);
                
		dropDowns[1] = fileDropdown;
	}

	void setupBackground(){
                background.setUseTexture(false);
                background.setColor(.1, .2, .3);
                background.setCoords(-1, .917, .1);
                background.setWidthHeight(2, .08);
                Form::setBackground(background);
                Form::setHideTitle(true);
	}

	void setupButtons(){
		// Setup compile button
		buttons[0].setShowButtonText(true);
                buttons[0].setButtonText("Compile");
		buttons[0].setWidthHeight(.13, background.getBgH());
                buttons[0].setCoords(
			background.getBgX()+.08 +.01, 
			background.getBgY(), 
			background.getBgZ());
                buttons[0].setButtonTextCoords(
                        buttons[0].getButtonX() + .025,
                        buttons[0].getButtonY() + .025,
                        buttons[0].getButtonZ()
                );
                buttons[0].setButtonColor(.1, .1, .1);
                buttons[0].setHoverColor(.2, .2, .2);
                buttons[0].setTextColor(.3, .3, .3);

		Form::setButtons(buttons, buttonCount);
	}

	void buildDropDowns(){
		setupFileDropDown();
		setupBuildDropDown();
                Form::setDropDowns(dropDowns, 2);
	}

	public:
	bool goToHomepage(){
		return goToHomePage;
	}

	DeveloperPageProjectBar() : Form(){
		setupBackground();
		buildDropDowns();
		//setupButtons();
	}

	int keyDown(unsigned char key, int mouseX, int mouseY){
		int ret = Form::keyDown(key, mouseX, mouseY);
		if(!editPopup.getHidden()){
			editPopup.keyDown(key, mouseX, mouseY);
		}
		return ret;
	}
	int mouseClick(int button, int state, float x, float y){
		int ret = Form::mouseClick(button, state, x, y);
		
		if(!editPopup.getHidden()){
			ret = editPopup.mouseClick(button, state, x, y);
			// close edit popup 
			if(editPopup.getClickedButton() == 0 && ((ret>>1)&0b1111) == 0 && (ret&1) == 1){
				editPopup.setHidden(true);	
				editPopup.refresh();
				return -1;
			}

			if(editPopup.getClickedButton() == 1 && ((ret>>1)&0b1111) == 0 && (ret&1) == 1){
                                project.remove(project.data.name);
				goToHomePage = true;
				return -1;
                        }

			if(editPopup.getClickedButton() == 2 && ((ret>>1)&0b1111) == 0 && (ret&1) == 1){
                        	editPopup.applyChanges();
				editPopup.setHidden(true);
				return -1;
			}

		}else{
			// Exit project
			if(getClickedDropDown() == 0 && getClickedDropDownOption() == 2 && ret == 1){
				goToHomePage = true;
				return -1;
			}
			// show edit popup.
			if(getClickedDropDown() == 0 && getClickedDropDownOption() == 1 && ret == 1){
				editPopup.setHidden(false);
			}

			// Compile Project
			if(getClickedDropDown() == 1 && getClickedDropDownOption() == 0 && ret == 1){
				Compiler compiler;
				compiler.compile();
			}
			// Run Project
			if(getClickedDropDown() == 1 && getClickedDropDownOption() == 1 && ret == 1){
				Compiler compiler;
				compiler.run();
			}
			// Compile and Run Project
			if(getClickedDropDown() == 1 && getClickedDropDownOption() == 2 && ret == 1){
				Compiler compiler;
				compiler.compile();
				compiler.run();
			}
		}
		return ret;
	}
	int mousePassive(float x, float y){
		int ret = Form::mousePassive(x, y);
		if(!editPopup.getHidden()){
			editPopup.mousePassive(x, y);
		}
		return ret;
	}
	int run(){
		int ret = Form::run();
		if(!editPopup.getHidden()){
			editPopup.run();
		}

		return ret;
	}

};
