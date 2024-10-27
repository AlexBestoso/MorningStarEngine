class ContextInterface : public GraphicsObject{
	private:
		obj_data_t *vector = NULL;
		float *vertexStore = NULL;
		size_t vertexStoreSize = 0;
	public:
		int context = 0;
                GraphicsCamera *activeCamera = NULL;
		virtual ~ContextInterface(){}
		virtual void destroy(){}
		virtual void init(){}
		virtual int exec(GLFWwindow* window){return -1;}

		void pushVectorStore(obj_t obj, int *offset){
			if(vertexStore == NULL){
				
			}
		}
};
using context_interface_t = ContextInterface *(*)();
