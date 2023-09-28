#include "GraphicsShader.h"
#include "GraphicsTexture.h"
#include "GraphicsCamera.h"

#include "GraphicsObject.h"

#include "./test.obj.h"
#include "./testObjects/testTerrain.h"
#include "./testObjects/fpsPlayer.h"
#include "./testObjects/testLight.h"
#include "./importedObjTest.h"

#include "./core/core.h"
#define MASTER_OBJECT_ARRAY_MAX 10
GraphicsObject masterObjectArray[MASTER_OBJECT_ARRAY_MAX];

class GraphicsEngine{
	private:
		GLFWwindow* window = NULL;
		GraphicsCamera *activeCamera = NULL;
		GraphicsContext *context = NULL;
	public:

		void setContext(GraphicsContext *ctx){
			context = ctx;
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
    			return true;
		}

		void contextInit(){
			if(context != NULL){
				context[0].init();
			}
		}
		void contextDestroy(){
			if(context != NULL){
				context[0].destroy();
			}
		}
		

		void setWindow(GLFWwindow* w){
			this->window = w;
		}

		int exec(void){
			int context = 0;
			if(this->context != NULL){
				context = this->context[0].exec(window);
			}
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
