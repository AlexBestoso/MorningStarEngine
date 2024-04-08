#include "./test.obj.h"
#include "./testObjects/testTerrain.h"
#include "./testObjects/fpsPlayer.h"
#include "./testObjects/testLight.h"
#include "./importedObjTest.h"

#include "./core/context/context.interface.h"
#include "./core/core.h"
#define MASTER_OBJECT_ARRAY_MAX 10
#define SO_LOCATIONS "./sharedObjects"


class GraphicsEngine{
	private:
		GLFWwindow* window = NULL;
		GraphicsCamera *activeCamera = NULL;

		context_interface_t invoker = NULL;
		std::unique_ptr<ContextInterface> _context  = NULL;
		void *contextHandle = NULL;
		size_t contextListSize = 0;
		std::string *availableSoFiles = NULL;
		

		bool isSoFile(std::string v){
			return (v.length() >= 3 && v.rfind(".so", v.length()-3) == v.length()-3);
		}

		static void Reset_dlerror() {
    	    		dlerror();
    		}

    		static void Check_dlerror() {
        		const char * dlsym_error = dlerror();
        		if (dlsym_error) {
        	    		printf(".SO error : %s\n", dlsym_error);
        		}
    		}

	public:
		
		~GraphicsEngine(){
			if(contextHandle)
				dlclose(contextHandle);
		}
		bool fetchContexts(void){
			FileSnake fs;
                        if(!fs.dirExists(SO_LOCATIONS))
                                return false;
                        string *files = fs.listDir(SO_LOCATIONS);
			if(files == NULL)
				return false;
                        contextListSize = 0;
			int listIndex = 0;
                        while(files[listIndex] != ""){
				printf("Files : %s\n", files[listIndex].c_str());
				if(this->isSoFile(files[listIndex])){
                                	contextListSize++;
				}
				listIndex++;
                        }

			availableSoFiles = new std::string[contextListSize];
			int variableIndex = 0;
			listIndex = 0;
			while(files[listIndex] != ""){
				std::string then = files[listIndex];
				if(this->isSoFile(then)){
					availableSoFiles[variableIndex] = SO_LOCATIONS;
				       	availableSoFiles[variableIndex] = availableSoFiles[variableIndex] + "/" + then;
					if(variableIndex == 0){
						contextHandle = dlopen(availableSoFiles[variableIndex].c_str(), RTLD_NOW);
						if(!contextHandle){
							printf("Failed to load first context.\n");
							Check_dlerror();
							exit(1);
						}

						Reset_dlerror();
						invoker = reinterpret_cast<context_interface_t>(dlsym(contextHandle, "create"));
						Check_dlerror();
						_context = std::unique_ptr<ContextInterface>(invoker());
						_context->init();

					}
					variableIndex++;
				}
				listIndex++;
			}
                        delete[] files;
                        return  true;
		}

		void setContext(int ctx){
			if(ctx >= contextListSize || ctx <= -1){
				printf("Invalid context id; exiting.\n");
				exit(EXIT_FAILURE);
			}
			availableSoFiles[ctx];

			contextHandle = dlopen(availableSoFiles[ctx].c_str(), RTLD_NOW);
			if(!contextHandle){
				printf("Failed to load context.\n");
				Check_dlerror();
				exit(EXIT_FAILURE);
			}

			Reset_dlerror();
			invoker = reinterpret_cast<context_interface_t>(dlsym(contextHandle, "create"));
			Check_dlerror();
			_context = std::unique_ptr<ContextInterface>(invoker());
			this->contextInit();
		}
		
		GLFWwindow* getWindow(void){
			return window;
		}
		
		bool init(const char * windowTitle, const unsigned int screenW, const unsigned int screenH){
    			glfwInit();
    			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    			window = glfwCreateWindow(screenW, screenH, windowTitle, NULL, NULL);
    			if (window == NULL){
    			    glfwTerminate();
    			    return false;
    			}
    			glfwMakeContextCurrent(window);
			glEnable(GL_DEPTH_TEST);
			fetchContexts();
    			return true;
		}

		void contextInit(){
			_context->init();
		}
		void contextDestroy(){
			_context->destroy();
			dlclose(contextHandle);
		}
		

		void setWindow(GLFWwindow* w){
			this->window = w;
		}

		int exec(void){
			int context = 0;
			_context->ges = gui_engine_global;
			context = _context->exec(window);
			swapAndPoll();
			return context;
		}

		bool setFrameBufferSizeCallback(void (*callback)(GLFWwindow*, int, int)){
			if(this->window == NULL){
				return false;
			}
			glfwSetFramebufferSizeCallback(this->window, callback);
			return true;
		}
	
		bool setMouseClickCallback(void(*callback)(GLFWwindow*, int, int, int)){
			
			glfwSetMouseButtonCallback(this->window, callback);
			return true;
		}

		bool setMouseCursorPosCallback(void(*callback)(GLFWwindow*, double, double)){
			if(this->window == NULL){
				return false;
			}
			glfwSetCursorPosCallback(this->window, callback);
			return true;
		}

		bool disableMouseCursor(void){
			if(this->window == NULL)
				return false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return true;
		}

		bool emableMouseCursor(void){
                        if(this->window == NULL)
                                return false;
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        return true;
                }

		void setActiveCamera(GraphicsCamera *cam){
			activeCamera = cam;
		}

		GraphicsCamera getActiveCamera(void){
			if(activeCamera == NULL){
				GraphicsCamera ret;
				return ret;
			}
			return activeCamera[0];
		}

		void generateVertexArrayIds(int count, unsigned int *vao){
			glGenVertexArrays(count, vao);
		}
		void generateVertexBufferIds(int count, unsigned int *vbo){
	    		glGenBuffers(count, vbo);
		}

		void bindVaoToVbo(unsigned int *vao, unsigned int *vbo){
    			glBindVertexArray(vao[0]);
    			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		}
		void bindElementArray(unsigned int *ebo){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		}
		void setElementArrayData(GLsizeiptr size, const GLvoid *indecies, GLenum drawMode){
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indecies, drawMode);
		}

		void storeVertexData(GLsizeiptr size, const GLvoid *vertices, GLenum drawMode){
    			glBufferData(GL_ARRAY_BUFFER, size, vertices, drawMode);
		}

		void setVertexAttributePointer(int attributeId, int vertexSize, int strideSize, void* offset){
    			glVertexAttribPointer(attributeId, vertexSize, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), offset);
		}

		void bindVertexArray(unsigned int *vArray){
			glBindVertexArray(vArray[0]);
		}

		void enableVertexArrayAttribute(int id){
			glEnableVertexAttribArray(id);
		}

		bool running(void){
			return (!glfwWindowShouldClose(window));
		}

		void swapAndPoll(){
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		void setBackgroundColor(float r, float g, float b, float a){
			glClearColor(r, g, b, a);
                	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
}ge;
