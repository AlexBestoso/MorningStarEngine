class ProjectBar{
	private:
		ObjectForm projectBarForm;
		FormContextMenu fileContextMenu;
                bool projectBarInitalized = false;

		void init(void){
			Display* d = XOpenDisplay(NULL);
                        Screen* s = DefaultScreenOfDisplay(d);

                        /* Form Background */
                        projectBarForm.config.id = 0;
                        projectBarForm.config.name = "Project Bar";
                        projectBarForm.config.x = 0; 
                        projectBarForm.config.y = s->height - 105;
                        projectBarForm.config.w = s->width; 
                        projectBarForm.config.h = 25;
                        projectBarForm.config.color[0] = .5;
                        projectBarForm.config.color[1] = .647;
                        projectBarForm.config.color[2] = 0;
                        //projectBarForm.setFormTexture("./core/pages/HomePage/Assets/formBackground.bmp");

                        /* Configure the title */
                        projectBarForm.title.setIdAndName(1, "projectBarTitle");
                        projectBarForm.title.setTitle(project.data.name);
                        projectBarForm.title.setPositionAndSize(projectBarForm.config.x, projectBarForm.config.y, 100, 100);
                        projectBarForm.title.setColor(1, .647, 0);
                        projectBarForm.title.setTextColor(0, 0, 0);
                        projectBarForm.title.setTextPosition(projectBarForm.config.x, projectBarForm.config.y + 10);
                        projectBarForm.title.setTitleFont(GLUT_BITMAP_HELVETICA_12);

			fileContextMenu.config.x = projectBarForm.config.x + 100 + 3;
			fileContextMenu.config.y = projectBarForm.config.y;
			fileContextMenu.config.z = 1;
			fileContextMenu.config.w = 75;
			fileContextMenu.config.h = 100;
			fileContextMenu.setColor(.5, .3, 0);
			fileContextMenu.config.textX = fileContextMenu.config.x + 5;
			fileContextMenu.config.textY = fileContextMenu.config.y + 10;
			fileContextMenu.config.textZ = 0;
			fileContextMenu.setTextColor(1, 1, 1);
			fileContextMenu.config.buttonText = "File";
			fileContextMenu.setHoverColor(.3, .5, 0);
			fileContextMenu.setDropDownColor(.5, .3, 0);
			fileContextMenu.config.dropDownX = fileContextMenu.config.x;
			fileContextMenu.config.dropDownY = fileContextMenu.config.y - 500;
			fileContextMenu.config.dropDownZ = 1;
			fileContextMenu.config.dropDownW = 100;
			fileContextMenu.config.dropDownH = 500;

                        this->projectBarInitalized = true;
		}
	public:
		void passiveMouseAction(float x, float y){
			fileContextMenu.passiveMouseAction(x, y);	
		}
		int mouseClickAction(int button, int state, float x, float y){
			if(fileContextMenu.mouseClickAction(button, state, x, y) == 1){
				fileContextMenu.config.showDropDown = true;
			}
		}
		void draw(void){
			if(!this->projectBarInitalized)
				this->init();
                        projectBarForm.draw();
			fileContextMenu.draw();
                }

};
