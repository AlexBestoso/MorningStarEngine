struct FormContextMenuStruct{
	int x = 0;
	int y = 0;
	int z = 0;
	int w = 0;
	int h = 0;
	int textX = 0;
	int textY = 0;
	int textZ = 0;
	int dropDownX = 0;
	int dropDownY = 0;
	int dropDownZ = 0;
	int dropDownW = 0;
	int dropDownH = 0;
	float color[3] = {0, 0, 0};
	float textColor[3] = {0, 0, 0};
	float hoverColor[3] = {0, 0, 0};
	float dropDownColor[3] = {0, 0, 0};
	void *fontBitMap = GLUT_BITMAP_HELVETICA_12;
	string buttonText = "";
	bool showDropDown = false;

	ObjectFormButton *buttons = NULL;
	size_t buttonCount = 0;

	bool noFormContainer = false;
};
class FormContextMenu : Object{
	private:
	public:
		int mousePassiveHover = 0;
		int mousePassiveHoverDropDown = 0;
		bool buttonHover = false;
		struct FormContextMenuStruct config;
		

		void setColor(float r, float g, float b){
			this->config.color[0] = r;
			this->config.color[1] = g;
			this->config.color[2] = b;
		}
		void setTextColor(float r, float g, float b){
			this->config.textColor[0] = r;
			this->config.textColor[1] = g;
			this->config.textColor[2] = b;
		}
		void setHoverColor(float r, float g, float b){
			this->config.hoverColor[0] = r;
			this->config.hoverColor[1] = g;
			this->config.hoverColor[2] = b;
		}
		void setDropDownColor(float r, float g, float b){
			this->config.dropDownColor[0] = r;
			this->config.dropDownColor[1] = g;
			this->config.dropDownColor[2] = b;
		}

		virtual bool isInHitbox(float x, float y);
		virtual bool isInDropDownBox(float x, float y);
		virtual void passiveMouseAction(float x, float y);
		virtual int mouseClickAction(int button, int state, float x, float y);
		virtual void draw(void);
};
