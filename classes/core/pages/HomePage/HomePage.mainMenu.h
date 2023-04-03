class HomePageMainMenu : public Form{
	private:
	FormBackground background;
        FormTitle title;
	FormButton *buttons = new FormButton[4];
	FormButton newProject;
	FormButton loadProject;
	FormButton aboutSoftware;
	FormButton exitProgram;
	public:
	HomePageMainMenu() : Form(){
		background.setTexturePath("/home/ninjs-grey/Documents/GithubRepositories/MorningStarEngine-versions/MorningStarEngine/classes/core/pages/HomePage/Assets/Home_MainMenu3.bmp");
		background.setUseTexture(true);

		Form::setBackground(background);
		Form::setHideTitle(true);
		
		// New Project
		newProject.setCoords(
			background.getBgX()+.133,
			background.getBgY()+.606,
			background.getBgZ()+.01
		);
		newProject.setWidthHeight(.73, .107);
		newProject.setButtonColor(.2, .2, .2);
		newProject.setButtonTextCoords(
			newProject.getButtonX()+(newProject.getButtonW()/2),
                        newProject.getButtonY()+(newProject.getButtonY()/2),
                        newProject.getButtonZ()		
		);
		newProject.setButtonText("New Project");
		
		// Load Project
		loadProject.setCoords(
			background.getBgX()+.133,
                        background.getBgY()+.473,
                        background.getBgZ()+.01		
		);
		loadProject.setWidthHeight(.73, .107);
		loadProject.setButtonColor(.2, .2, .2);
		loadProject.setButtonTextCoords(
                        loadProject.getButtonX()+(loadProject.getButtonW()/2),
                        loadProject.getButtonY()+(loadProject.getButtonH()/2),
                        loadProject.getButtonZ()
                );
		loadProject.setButtonText("Load Project");
		
		// About Software
		aboutSoftware.setCoords(
                        background.getBgX()+.135,
                        background.getBgY()+.346,
                        background.getBgZ()+.01
                );
                aboutSoftware.setWidthHeight(.73, .107);
                aboutSoftware.setButtonColor(.2, .2, .2);
		aboutSoftware.setButtonTextCoords(
                        aboutSoftware.getButtonX()+(aboutSoftware.getButtonW()/2),
                        aboutSoftware.getButtonY()+(aboutSoftware.getButtonH()/2),
                        aboutSoftware.getButtonZ()
                );
		aboutSoftware.setButtonText("About Software");

		// Exit Program
		exitProgram.setCoords(
                        background.getBgX()+.135,
                        background.getBgY()+.213,
                        background.getBgZ()+.01
                );
                exitProgram.setWidthHeight(.73, .107);
                exitProgram.setButtonColor(.2, .2, .2);
		exitProgram.setButtonTextCoords(
                        exitProgram.getButtonX()+(exitProgram.getButtonW()/2),
                        exitProgram.getButtonY()+(exitProgram.getButtonH()/2),
                        exitProgram.getButtonZ()
                );
		exitProgram.setButtonText("Exit Program");

		// Apply buttons
		buttons[0] = newProject;
		buttons[1] = loadProject;
		buttons[2] = aboutSoftware;
		buttons[3] = exitProgram;
		Form::setButtons(buttons, 4);
	}
};
