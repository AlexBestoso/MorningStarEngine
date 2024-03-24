class GraphicsContext{
	private:

	public:
		int context = 0;
		GraphicsCamera *activeCamera = NULL;

		virtual void destroy(){}
		virtual void init(){}
		virtual int exec(GLFWwindow* window){
			return context;
		}
};
