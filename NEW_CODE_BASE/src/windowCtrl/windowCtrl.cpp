#include "../../main.h"
#include "../error/error.h"
#include "./windowCtrl.error.h"
#include "./windowCtrl.h"
		void WindowCtrl::fetchScreenDimensions(void){
			Display *d = XOpenDisplay(NULL);
			Screen *s = DefaultScreenOfDisplay(d);
			this->screenWidth = s->width;
			this->screenHeight = s->height;
			XCloseDisplay(d);
			printf("Screen Size %dx%d\n", this->screenWidth, this->screenHeight);

		}
		
		WindowCtrl::WindowCtrl(void){
			this->window = NULL;
                        this->title = "";
                        this->screenWidth = 700;
                        this->screenHeight = 700;
		}
		WindowCtrl::WindowCtrl(const char *t){
			this->window = NULL;
                	this->screenWidth = 700;
                	this->screenHeight = 700;
			this->setTitle(t);
			//this->init();
		}
		bool WindowCtrl::shouldClose(void){
			return (!glfwWindowShouldClose(this->getWindow()));
		}
		void WindowCtrl::init(void){
			//if(glfwInit() == GLFW_FALSE)
			//	throw WindowCtrlError("init", "Failed to initalize glfw.");
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
                        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
                        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);
                        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
                        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
                        glfwWindowHint(GLFW_SAMPLES, 1);
                        //glfwWindowHint(GLFW_STEREO, GLFW_TRUE);
                        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
                        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
			glfwWindowHintString(GLFW_X11_CLASS_NAME, "MORNINGCLASS");
			glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "MORNINGINST");
			
			this->fetchScreenDimensions();
			this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, title.c_str(), NULL/*glfwGetPrimaryMonitor()*/, NULL);
			if(this->window == NULL){
				glfwTerminate();
				throw WindowCtrlError("WindowCtrl", "glfwCreateWindowFailed");
			}

		}

		void WindowCtrl::setTitle(const char *t){
			this->title = t;
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
			glfwMakeContextCurrent(this->window);
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

		void WindowCtrl::setWindowRefreshCb(void(*cb)(GLFWwindow*)){
			glfwSetWindowRefreshCallback(this->window, cb);
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
	
		void WindowCtrl::setErrorHandleCallback(void(*cb)(int, const char *)){
			glfwSetErrorCallback(cb);
		}

		void WindowCtrl::clipDistance(bool enabled, GLuint v){
			 if(enabled) glEnable(GL_CLIP_DISTANCE0+v); else glDisable(GL_CLIP_DISTANCE0+v);
		} 
		void WindowCtrl::colorLogic(bool enabled){
			 if(enabled) glEnable(GL_COLOR_LOGIC_OP); else glDisable(GL_COLOR_LOGIC_OP);
		} 
		void WindowCtrl::cullFace(bool enabled){
			 if(enabled) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
		} 
		void WindowCtrl::debugOutput(bool enabled){
			 if(enabled) glEnable(GL_DEBUG_OUTPUT); else glDisable(GL_DEBUG_OUTPUT);
		} 
		void WindowCtrl::syncDebugOutput(bool enabled){
			 if(enabled) glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); else glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		} 
		void WindowCtrl::depthClamp(bool enabled){
			 if(enabled) glEnable(GL_DEPTH_CLAMP); else glDisable(GL_DEPTH_CLAMP);
		} 
		void WindowCtrl::dither(bool enabled){
			 if(enabled) glEnable(GL_DITHER); else glDisable(GL_DITHER);
		} 
		void WindowCtrl::framebufferSRGB(bool enabled){
			 if(enabled) glEnable(GL_FRAMEBUFFER_SRGB); else glDisable(GL_FRAMEBUFFER_SRGB);
		} 
		void WindowCtrl::lineSmooth(bool enabled){
			 if(enabled) glEnable(GL_LINE_SMOOTH); else glDisable(GL_LINE_SMOOTH);
		} 
		void WindowCtrl::multiSample(bool enabled){
			 if(enabled) glEnable(GL_MULTISAMPLE); else glDisable(GL_MULTISAMPLE);
		} 
		void WindowCtrl::polygonOffsetFill(bool enabled){
			 if(enabled) glEnable(GL_POLYGON_OFFSET_FILL); else glDisable(GL_POLYGON_OFFSET_FILL);
		} 
		void WindowCtrl::polygonOffsetLine(bool enabled){
			 if(enabled) glEnable(GL_POLYGON_OFFSET_LINE); else glDisable(GL_POLYGON_OFFSET_LINE);
		} 
		void WindowCtrl::polygonOffsetPoint(bool enabled){
			 if(enabled) glEnable(GL_POLYGON_OFFSET_POINT); else glDisable(GL_POLYGON_OFFSET_POINT);
		} 
		void WindowCtrl::ploygonSmooth(bool enabled){
			 if(enabled) glEnable(GL_POLYGON_SMOOTH); else glDisable(GL_POLYGON_SMOOTH);
		} 
		void WindowCtrl::primitiveRestart(bool enabled){
			 if(enabled) glEnable(GL_PRIMITIVE_RESTART); else glDisable(GL_PRIMITIVE_RESTART);
		} 
		void WindowCtrl::primitiveResartFixedIndex(bool enabled){
			 if(enabled) glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX); else glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
		} 
		void WindowCtrl::rasterizerDiscard(bool enabled){
			 if(enabled) glEnable(GL_RASTERIZER_DISCARD); else glDisable(GL_RASTERIZER_DISCARD);
		} 
		void WindowCtrl::sampleAlphaToCoverage(bool enabled){
			 if(enabled) glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE); else glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		} 
		void WindowCtrl::sampleAlphaToOne(bool enabled){
			 if(enabled) glEnable(GL_SAMPLE_ALPHA_TO_ONE); else glDisable(GL_SAMPLE_ALPHA_TO_ONE);
		} 
		void WindowCtrl::sampleCoverage(bool enabled){
			 if(enabled) glEnable(GL_SAMPLE_COVERAGE); else glDisable(GL_SAMPLE_COVERAGE);
		} 
		void WindowCtrl::sampleShading(bool enabled){
			 if(enabled) glEnable(GL_SAMPLE_SHADING); else glDisable(GL_SAMPLE_SHADING);
		} 
		void WindowCtrl::sampleMask(bool enabled){
			 if(enabled) glEnable(GL_SAMPLE_MASK); else glDisable(GL_SAMPLE_MASK);
		} 
		void WindowCtrl::scissorTest(bool enabled){
			 if(enabled) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
		} 
		void WindowCtrl::stencilTest(bool enabled){
			 if(enabled) glEnable(GL_STENCIL_TEST); else glDisable(GL_STENCIL_TEST);
		} 
		void WindowCtrl::textureCubeMapSeamless(bool enabled){
			 if(enabled) glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); else glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		} 
		void WindowCtrl::programPointSize(bool enabled){
			 if(enabled) glEnable(GL_PROGRAM_POINT_SIZE); else glDisable(GL_PROGRAM_POINT_SIZE);

		} 

