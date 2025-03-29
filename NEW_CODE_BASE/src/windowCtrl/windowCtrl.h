#include "./windowCtrl.error.h"
class WindowCtrl{
	private:
		GLFWwindow *window = NULL;
		std::string title = "";
		int screenWidth = 0;
		int screenHeight = 0;
		
		
		void fetchScreenDimensions(void){
			Display *d = XOpenDisplay(NULL);
			Screen *s = DefaultScreenOfDisplay(d);
			this->screenWidth = s->width;
			this->screenHeight = s->height;
			XCloseDisplay(d);
		}
		
	public:
		WindowCtrl(void){}
		WindowCtrl(const char *title){
			this->setTitle(title);
			this->init();
		}
		void init(void){
			glfwInit();
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			this->fetchScreenDimensions();
			this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, title.c_str(), NULL/*glfwGetPrimaryMonitor()*/, NULL);
			if(this->window == NULL){
				glfwTerminate();
				throw WindowCtrlError("WindowCtrl", "glfwCreateWindowFailed");
			}

		}

		void setTitle(const char *title){
			this->title = title;
		}
		GLFWwindow *getWindow(void){
			if(this->window == NULL)
				throw WindowCtrlError("getWindow", "window is null");
			return this->window;
		}

		void alphaBlendFunc(void){
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void current(void){
			glfwMakeContextCurrent(window);
		}
		void depthTest(bool enabled){
			if(enabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		}
		void blend(bool enabled){
			if(enabled) glEnable(GL_BLEND); else glDisable(GL_BLEND);
		}
		
		void setFrameResizeCallBack(void(*cb)(GLFWwindow*, int, int)){
			if(this->window == NULL)
				throw WindowCtrlError("setFrameResizeCallBack", "No available window objects.");
			glfwSetFramebufferSizeCallback(this->window, cb);
		}

		void setKeyboardCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods)){
                        if(this->window == NULL)
				throw WindowCtrlError("setKeyboarCallback", "No available window objects.");

                        glfwSetKeyCallback(this->window, callback);
                }

		void setMouseClickCallback(void(*callback)(GLFWwindow*, int, int, int)){
                        if(this->window == NULL)
				throw WindowCtrlError("setKeyboarCallback", "No available window objects.");
                        glfwSetMouseButtonCallback(this->window, callback);
                }

                void setMouseCursorPosCallback(void(*callback)(GLFWwindow*, double, double)){
                        if(this->window == NULL){
				throw WindowCtrlError("setMouseCursorPosCallback", "No available window objects.");
                        }
                        glfwSetCursorPosCallback(this->window, callback);
                }
	
};
