class Page{
	private:
		int _pageId = 0;
		float _bgColorRed = .25;
		float _bgColorGreen = 0;
		float _bgColorBlue = .5;
		float _bgColorAlpha = 1;

		void setBackgroundColor(){
                        glClearColor(
				this->_bgColorRed,
				this->_bgColorGreen, 
				this->_bgColorBlue,
				this->_bgColorAlpha
			);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
                }
	public:
	Page(int pageId, float bgColor[4]){
		this->_pageId = pageId;
		this->_bgColorRed = bgColor[0];
		this->_bgColorGreen = bgColor[1];
		this->_bgColorBlue = bgColor[2];
		this->_bgColorAlpha = bgColor[3];
	}

	int getPageId(void){
		return this->_pageId;
	}
	void setPageId(int id){
		this->_pageId = id;
	}

	void setBgColor(float bgColor[4]){
		this->_bgColorRed = bgColor[0];
                this->_bgColorGreen = bgColor[1];
                this->_bgColorBlue = bgColor[2];
                this->_bgColorAlpha = bgColor[3];
	}
	void getBgColor(float bgColor[4]){
		bgColor[0] = this->_bgColorRed;
		bgColor[1] = this->_bgColorGreen;
		bgColor[2] = this->_bgColorBlue;
		bgColor[3] = this->_bgColorAlpha;
	}

	/*
	 * Core Glut Functions
	 * */
	virtual int run(){
		setBackgroundColor();
		return this->_pageId;
	}

	virtual int mouseClick(int button, int state, float x, float y){
		setBackgroundColor();
		return this->_pageId;
	}

	virtual int mousePassive(float x, float y){
		setBackgroundColor();
		return this->_pageId;
	}

	virtual int keyDown(unsigned char key, int mouseX, int mouseY){
		setBackgroundColor();
		return this->_pageId;
	}
};
