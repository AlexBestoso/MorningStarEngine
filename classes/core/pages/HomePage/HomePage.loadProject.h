class HomePageLoadProject : public Form{
	private:
	FormBackground background;
        FormTitle title;
	FormButton *buttons = new FormButton[1];
	FormButton backButton;
	FormSelectList *selectLists = new FormSelectList[1];
	FormButton selectListOptionTemplate;

	string *projectNames;
	size_t projectNameMax = 0;
	public:
	HomePageLoadProject() : Form(){
		background.setTexturePath("/home/ninjs-grey/Documents/GithubRepositories/MorningStarEngine-versions/MorningStarEngine/classes/core/pages/HomePage/Assets/Home_loadProject.bmp");
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

		/*
		 * Configure select list
		 * */
		selectLists[0].setMenuCoords(
			background.getBgX()+.133,
                        background.getBgY()+.22,
                        background.getBgZ()		
		);
		selectLists[0].setMenuWidthHeight(.73, .49);
		selectLists[0].setMaxVisibleOptions(6);
		selectLists[0].setOptionsOffset(.015);
		selectLists[0].setMenuColor(.1, .1, .1);

		selectListOptionTemplate.setWidthHeight(.73, .06);
		selectListOptionTemplate.setCoords(
			selectLists[0].getMenuX(),
			selectLists[0].getMenuY()+selectLists[0].getMenuH() - selectListOptionTemplate.getButtonH(),
			selectLists[0].getMenuZ()		
		);
		selectListOptionTemplate.setButtonTextCoords(
			selectListOptionTemplate.getButtonX()+.05,
			selectListOptionTemplate.getButtonY()+.025,
			selectListOptionTemplate.getButtonZ()		
		);
		selectListOptionTemplate.setButtonColor(.2, .2, .2);
		selectListOptionTemplate.setHoverColor(.3, .3, .3);
		
		Form::setSelectLists(selectLists, 1);
	}

	bool useSelectedProject(int projectPositionId){
		if(projectPositionId < 0 || projectPositionId >= projectNameMax || projectNames == NULL){
			return false;
		}
		project.load(projectNames[projectPositionId]);
		return true;
	}

	void fetchListOptions(){
		FileSnake fs;
		string *projects = fs.listDir(project.getProjectDir());
		int ctr = 0;
		while(projects[ctr] != ""){
			ctr++;
		}

		projectNames = projects;
		projectNameMax = ctr;
		FormButton *options = new FormButton[projectNameMax];
		
		for(int i=0; i<projectNameMax; i++){
			options[i] = selectListOptionTemplate;
			options[i].setButtonText(projectNames[i]);
		}

		selectLists[0].setSectionButtonOptions(options, ctr);
	}
};
