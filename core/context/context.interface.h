class ContextInterface : public GraphicsObject{
	public:
		int context = 0;
                GraphicsCamera *activeCamera = NULL;
		virtual ~ContextInterface(){}
		virtual void destroy(){}
		virtual void init(){}
		virtual int exec(GLFWwindow* window){return -1;}
};
using context_interface_t = ContextInterface *(*)();
