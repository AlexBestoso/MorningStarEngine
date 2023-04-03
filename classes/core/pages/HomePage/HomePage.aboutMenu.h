class HomePageAboutMenu : public Form{
	private:
	FormBackground background;
        FormTitle title;
	FormButton *buttons = new FormButton[1];
	FormButton backButton;
	public:
	HomePageAboutMenu() : Form(){
		background.setTexturePath("/home/ninjs-grey/Documents/GithubRepositories/MorningStarEngine-versions/MorningStarEngine/classes/core/pages/HomePage/Assets/Home_AboutMenu.bmp");
		background.setUseTexture(true);

		Form::setBackground(background);
		Form::setHideTitle(true);
		
		// Back Button
		backButton.setCoords(
			background.getBgX()+.133,
			background.getBgY()+.05,
			background.getBgZ()+.03
		);
		backButton.setWidthHeight(.73, .107);
		backButton.setButtonColor(.2, .2, .2);
		backButton.setButtonTextCoords(
			backButton.getButtonX()+(backButton.getButtonW()/2),
                        backButton.getButtonY()+(backButton.getButtonH()/2),
                        backButton.getButtonZ()		
		);
		backButton.setButtonText("Exit Menu");
		
		// Apply buttons
		buttons[0] = backButton;
		Form::setButtons(buttons, 1);
	}
};
