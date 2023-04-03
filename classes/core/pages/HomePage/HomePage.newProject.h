class HomePageNewProject : public Form{
	private:
	FormBackground background;
        FormTitle title;
	FormButton *buttons = new FormButton[2];
	FormButton backButton;
	FormButton createButton;

	FormTextInput *inputs = new FormTextInput[1];
	FormTextInput projectName;

	public:
	HomePageNewProject() : Form(){
		background.setTexturePath("/home/ninjs-grey/Documents/GithubRepositories/MorningStarEngine-versions/MorningStarEngine/classes/core/pages/HomePage/Assets/Home_newProject.bmp");
		background.setUseTexture(true);

		Form::setBackground(background);
		Form::setHideTitle(true);
		
		// Back Button
		backButton.setCoords(
			background.getBgX()+.515,
			background.getBgY()+.465,
			background.getBgZ()+.03
		);
		backButton.setWidthHeight(.35, .104);
		backButton.setButtonColor(.2, .2, .2);
		backButton.setButtonTextCoords(
			backButton.getButtonX()+(backButton.getButtonW()/2),
                        backButton.getButtonY()+(backButton.getButtonH()/2),
                        backButton.getButtonZ()		
		);
		backButton.setButtonText("Cancel");

		// Create Button
		createButton.setCoords(
                        background.getBgX()+.135,
                        background.getBgY()+.465,
                        background.getBgZ()+.03
                );
                createButton.setWidthHeight(.35, .104);
                createButton.setButtonColor(.2, .2, .2);
                createButton.setButtonTextCoords(
                        createButton.getButtonX()+(createButton.getButtonW()/2),
                        createButton.getButtonY()+(createButton.getButtonH()/2),
                        createButton.getButtonZ()
                );
                createButton.setButtonText("Create");

		// Apply buttons
		buttons[0] = backButton;
		buttons[1] = createButton;
		Form::setButtons(buttons, 2);

		// Create Text Input 
		projectName.setCoords(
			background.getBgX()+.150,
			background.getBgY()+.600,
			background.getBgZ()
		);
		projectName.setWidthHeight(.70, .104);

		projectName.setLabelCoords(
			projectName.getX(),
			projectName.getY()+.05,
			projectName.getZ()		
		);
		projectName.setLabel("Project Name :");
		projectName.setInputCoords(
			projectName.getX()+.1,
                        projectName.getY()+.05,
                        projectName.getZ()		
		);
		
		inputs[0] = projectName;
		Form::setTextInputs(inputs, 1);
	}

	string getProjectName(){
		return inputs[0].getInputData();
	}

	void resetMenu(void){
		for(int i=0; i<1; i++){
			inputs[0].reset();
		}
		Form::setTextInputs(inputs, 1);
	}
};
