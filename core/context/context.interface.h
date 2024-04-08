class ContextInterface : public GraphicsObject{
	public:
		int context = 0;
                GraphicsCamera *activeCamera = NULL;
		void update(struct GuiEngineStruct ges){
			gui_engine_global = ges;
		}
		virtual ~ContextInterface(){}
		virtual void destroy(){}
		virtual void init(){}
		virtual int exec(GLFWwindow* window){return -1;}
};
using context_interface_t = ContextInterface *(*)();
