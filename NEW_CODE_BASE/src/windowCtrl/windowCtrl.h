class WindowCtrl{
	private:
		GLFWwindow *window;
		std::string title;
		int screenWidth;
		int screenHeight;
		
		
		void fetchScreenDimensions(void);
		
	public:
		WindowCtrl(void);
		WindowCtrl(const char *title);
		void init(void);

		void setTitle(const char *title);
		GLFWwindow *getWindow(void);
		bool shouldClose(void);
		void alphaBlendFunc(void);
		void current(void);
		void depthTest(bool enabled);
		void blend(bool enabled);
		void setFrameResizeCallBack(void(*cb)(GLFWwindow*, int, int));
		void setKeyboardCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods));
		void setMouseClickCallback(void(*callback)(GLFWwindow*, int, int, int));
                void setMouseCursorPosCallback(void(*callback)(GLFWwindow*, double, double));
};
