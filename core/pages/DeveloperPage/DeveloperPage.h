class DeveloperPage{
	private:
		int pageContext = 0;

                void initPage(){
                        this->setBackgroundColor(.25,0,.5);
                        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                }

                void setBackgroundColor(float r, float g, float b){
                        glClearColor(r, g, b, 1);
                }

	public:
		int runPage(void){
                        this->initPage();
                               switch(this->pageContext){
                                case 0: // main menu
                                        break;
                        }
                        return DEVELOPER_PAGE;
                }

}developerPage;
