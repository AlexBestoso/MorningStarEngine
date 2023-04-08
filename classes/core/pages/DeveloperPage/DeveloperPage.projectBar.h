class DeveloperPageProjectBar : public Form{
	private:
	FormBackground background;
	FormDropDown fileDropdown;
	FormDropDown *dropDowns = new FormDropDown[1];
	public:
	DeveloperPageProjectBar() : Form(){
		/*
		 * Background Configureation
		 * */
		background.setUseTexture(false);
		background.setColor(.1, .2, .3);
		background.setCoords(-1, .917, .1);
		background.setWidthHeight(2, .08);
		Form::setBackground(background);
		Form::setHideTitle(true);

		/*
		 * Dropdown Configuration.
		 * */
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
		Form::setDropDowns(dropDowns, 1);
	}	
};
