class ContextInterface : public GraphicsObject{
	private:
	public:
		int context = 0;
                GraphicsCamera *activeCamera = NULL;
		virtual void destroy(){}
		virtual void init(){}
		virtual int exec(GLFWwindow* window){return -1;}

		~ContextInterface(void){
		}
};
using context_interface_t = ContextInterface *(*)();
