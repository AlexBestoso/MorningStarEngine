class DeveloperPageEditPopup : public Form{
	private:
	FormBackground background;
	FormTitle title;
	FormButton *buttons = new FormButton[3];
	size_t buttonCount = 3;

	FormTextInput *textInputs = new FormTextInput[4];
	size_t textInputCount = 4;

	bool hidden = true;

	void setupBackground(){
                background.setUseTexture(false);
                background.setColor(.3, .2, .1);
                background.setCoords(-.5, -.5, .2);
                background.setWidthHeight(1, 1);
                Form::setBackground(background);
                Form::setHideTitle(false);
        }
	void setupTitle(){
		title.setText("Edit Project");
		title.setFontWidthOffset(.04);
		title.setFontHeightOffset(.06);
		Form::setTitle(title);
	}
	void setupButtons(){
		// Create close button
		buttons[0].setButtonText("Close");
		buttons[0].setCoords(
			background.getBgX(), 
			background.getBgY(), 
			background.getBgZ()
		);
		buttons[0].setWidthHeight(.07, .05);
		buttons[0].setButtonColor(.4, .3, .2);
		buttons[0].setTextColor(0, 0, 0);
		buttons[0].setButtonTextCoords(
			buttons[0].getButtonX() + .003,
			buttons[0].getButtonY() + .009,
			buttons[0].getButtonZ()
		);

		// Create delete project button
		buttons[1].setButtonText("Delete Project");
		buttons[1].setButtonColor(.5, 0, 0);
		buttons[1].setWidthHeight(.2, .05);
		buttons[1].setCoords(
			background.getBgX(), 
                        background.getBgY()+background.getBgH()-.1,
                        background.getBgZ()		
		);
		buttons[1].setButtonTextCoords(
                        buttons[1].getButtonX() + .003,
                        buttons[1].getButtonY() + .009,
                        buttons[1].getButtonZ()
                );

		// Create Apply Button
		buttons[2].setButtonText("Apply");
                buttons[2].setCoords(
			background.getBgX() + .4 + .05,
                        background.getBgY() + background.getBgH() - buttons[3].getButtonH() - 0.8,
                        background.getBgZ()
                );
                buttons[2].setWidthHeight(.07, .05);
                buttons[2].setButtonColor(.4, .3, .2);
                buttons[2].setTextColor(0, 0, 0);
                buttons[2].setButtonTextCoords(
                        buttons[2].getButtonX() + .003,
                        buttons[2].getButtonY() + .009,
                        buttons[2].getButtonZ()
                );

		Form::setButtons(buttons, buttonCount);
	}

	void setupTextInputs(){
		// create project name input
		textInputs[0].setWidthHeight(.30, .05);
		textInputs[0].setCoords(
                        background.getBgX() + .4,
                        background.getBgY() + background.getBgH() - textInputs[0].getH() - 0.2,
                        background.getBgZ()
                );
		textInputs[0].setInputCoords(
                        textInputs[0].getX() + 0.01,
                        textInputs[0].getY()+(textInputs[0].getH()/2),
                        textInputs[0].getZ()
                );
		textInputs[0].setLabelCoords(
                        textInputs[0].getX()-.1,
                        textInputs[0].getY()+(textInputs[0].getH()/2),
                        textInputs[0].getZ()
                );
		textInputs[0].setLabel("Project Name :");
		textInputs[0].setInputData(project.data.name);
		
		// Create Author Input
		textInputs[1].setWidthHeight(.30, .05);
                textInputs[1].setCoords(
			textInputs[0].getX(),
			textInputs[0].getY() - (textInputs[0].getH() + .006),
			textInputs[0].getZ()
                );
                textInputs[1].setInputCoords(
                        textInputs[1].getX() + 0.01,
                        textInputs[1].getY()+(textInputs[0].getH()/2),
                        textInputs[1].getZ()
                );
                textInputs[1].setLabelCoords(
                        textInputs[1].getX()-.1,
                        textInputs[1].getY()+(textInputs[0].getH()/2),
                        textInputs[1].getZ()
                );
                textInputs[1].setLabel("Author :");
                textInputs[1].setInputData(project.data.author);
		textInputs[1].setDirSafeInput(false);

		// Create Version Input
		textInputs[2].setWidthHeight(.30, .05);
                textInputs[2].setCoords(
                        textInputs[0].getX(),
                        textInputs[0].getY() - (textInputs[0].getH() + .006) * 2,
                        textInputs[0].getZ()
                );
                textInputs[2].setInputCoords(
                        textInputs[2].getX() + 0.01,
                        textInputs[2].getY()+(textInputs[0].getH()/2),
                        textInputs[2].getZ()
                );
                textInputs[2].setLabelCoords(
                        textInputs[2].getX()-.1,
                        textInputs[2].getY()+(textInputs[0].getH()/2),
                        textInputs[2].getZ()
                );
                textInputs[2].setLabel("Version :");
                textInputs[2].setInputData(project.data.version);
		textInputs[2].setDirSafeInput(false);

		// Create description Input
		textInputs[3].setWidthHeight(.30, .05);
                textInputs[3].setCoords(
                        textInputs[0].getX(),
                        textInputs[0].getY() - (textInputs[0].getH() + .006) * 3,
                        textInputs[0].getZ()
                );
                textInputs[3].setInputCoords(
                        textInputs[3].getX() + 0.01,
                        textInputs[3].getY()+(textInputs[0].getH()/2),
                        textInputs[3].getZ()
                );
                textInputs[3].setLabelCoords(
                        textInputs[3].getX()-.1,
                        textInputs[3].getY()+(textInputs[0].getH()/2),
                        textInputs[3].getZ()
                );
                textInputs[3].setLabel("Description :");
                textInputs[3].setInputData(project.data.description);
		textInputs[3].setDirSafeInput(false);

		Form::setTextInputs(textInputs, textInputCount);
	}

	public:
	void setHidden(bool val){
		hidden = val;
	}
	bool getHidden(void){
		return hidden;
	}

	void applyChanges(void){
		project.data.name = textInputs[0].getInputData();
		project.data.author = textInputs[1].getInputData();
		project.data.version = textInputs[2].getInputData();
		project.data.description = textInputs[3].getInputData();

		glutSetWindowTitle(project.data.name.c_str());
		project.update();
	}

	void refresh(){
		setupBackground();
                setupTitle();
                setupButtons();
                setupTextInputs();
	}

	DeveloperPageEditPopup() : Form(){
                setupBackground();
		setupTitle();
		setupButtons();
		setupTextInputs();
        }
};
