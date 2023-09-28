#include "GraphicsShader.h"
#include "GraphicsTexture.h"
#include "GraphicsCamera.h"

#include "GraphicsObject.h"

#include "./test.obj.h"
#include "./testObjects/testTerrain.h"
#include "./testObjects/fpsPlayer.h"
#include "./testObjects/testLight.h"
#include "./importedObjTest.h"

class GraphicsEngine{
	private:
		GLFWwindow* window;
		GraphicsCamera *activeCamera = NULL;
	public:
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
};
