class DeveloperPageEditPopup : public Form{
	private:
	FormBackground background;
	FormTitle title;
	FormButton *buttons = new FormButton[2];
	size_t buttonCount = 2;

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
		Form::setButtons(buttons, buttonCount);
	}
	public:
	void setHidden(bool val){
		hidden = val;
	}
	bool getHidden(void){
		return hidden;
	}

	DeveloperPageEditPopup() : Form(){
                setupBackground();
		setupTitle();
		setupButtons();
        }
};
