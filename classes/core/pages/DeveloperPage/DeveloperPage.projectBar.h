class DeveloperPageProjectBar : public Form{
	private:
	FormBackground background;

	public:
	DeveloperPageProjectBar() : Form(){
		background.setUseTexture(false);
		background.setColor(.1, .2, .3);
		background.setCoords(-1, .917, .1);
		background.setWidthHeight(2, .08);
		Form::setBackground(background);
		Form::setHideTitle(true);
	}	
};
