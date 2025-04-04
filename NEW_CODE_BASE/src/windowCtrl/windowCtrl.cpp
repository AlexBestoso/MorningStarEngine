#include "../../main.h"
#include "../error/error.h"
#include "./windowCtrl.error.h"
#include "./windowCtrl.h"
		void WindowCtrl::fetchScreenDimensions(void){
			/*Display *d = XOpenDisplay(NULL);
			Screen *s = DefaultScreenOfDisplay(d);
			this->screenWidth = s->width;
			this->screenHeight = s->height;
			XCloseDisplay(d);
			printf("Screen Size %dx%d\n", this->screenWidth, this->screenHeight);*/
			this->screenWidth = 700;
			this->screenHeight = 700;

		}
		
		WindowCtrl::WindowCtrl(void){
			this->window = NULL;
                        this->title = "";
                        this->screenWidth = 0;
                        this->screenHeight = 0;
		}
		WindowCtrl::WindowCtrl(const char *title){
			this->window = NULL;
                	this->title = "";
                	this->screenWidth = 0;
                	this->screenHeight = 0;
			this->setTitle(title);
			this->init();
		}
		bool WindowCtrl::shouldClose(void){
			return (!glfwWindowShouldClose(this->getWindow()));
		}
		void WindowCtrl::init(void){
			glfwInit();
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
                        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
                        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
			
			this->fetchScreenDimensions();
			this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, title.c_str(), NULL/*glfwGetPrimaryMonitor()*/, NULL);
			if(this->window == NULL){
				glfwTerminate();
				throw WindowCtrlError("WindowCtrl", "glfwCreateWindowFailed");
			}

		}

		void WindowCtrl::setTitle(const char *title){
			this->title = title;
		}
		GLFWwindow *WindowCtrl::getWindow(void){
			if(this->window == NULL)
				throw WindowCtrlError("getWindow", "window is null");
			return this->window;
		}

		void WindowCtrl::alphaBlendFunc(void){
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void WindowCtrl::current(void){
			glfwMakeContextCurrent(window);
		}
		void WindowCtrl::depthTest(bool enabled){
			if(enabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		}
		void WindowCtrl::blend(bool enabled){
			if(enabled) glEnable(GL_BLEND); else glDisable(GL_BLEND);
		}
		
		void WindowCtrl::setFrameResizeCallBack(void(*cb)(GLFWwindow*, int, int)){
			if(this->window == NULL)
				throw WindowCtrlError("setFrameResizeCallBack", "No available window objects.");
			glfwSetFramebufferSizeCallback(this->window, cb);
		}

		void WindowCtrl::setKeyboardCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods)){
                        if(this->window == NULL)
				throw WindowCtrlError("setKeyboarCallback", "No available window objects.");

                        glfwSetKeyCallback(this->window, callback);
                }

		void WindowCtrl::setMouseClickCallback(void(*callback)(GLFWwindow*, int, int, int)){
                        if(this->window == NULL)
				throw WindowCtrlError("setKeyboarCallback", "No available window objects.");
                        glfwSetMouseButtonCallback(this->window, callback);
                }

                void WindowCtrl::setMouseCursorPosCallback(void(*callback)(GLFWwindow*, double, double)){
                        if(this->window == NULL){
				throw WindowCtrlError("setMouseCursorPosCallback", "No available window objects.");
                        }
                        glfwSetCursorPosCallback(this->window, callback);
                }
