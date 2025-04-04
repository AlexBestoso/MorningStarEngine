#include "./main.h"
#include "./src/error/error.h"

#include "./src/windowCtrl/windowCtrl.h"
#include "./src/shader/shader.h"
#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int global_w=0, global_h=0;
void CoreFrameBuffer(GLFWwindow* window, int width, int height){
        global_w = width;
        global_h = height;
    glViewport(0, 0, width, height);
}

int main(int argc, char *argv[]){
	Core core;
	WindowCtrl window;
	try{
		window.setTitle("MSGE");
                window.init();
                        window.current();
                        window.blend(true);
                        window.depthTest(true);
                        window.alphaBlendFunc();
                        window.setFrameResizeCallBack(CoreFrameBuffer);
                        window.setKeyboardCallback(keyboard_callback);
                        window.setMouseClickCallback(mouse_click_callback);
                        window.setMouseCursorPosCallback(mouse_callback);
			glViewport(0, 0, global_w, global_h);
		core.init();

//		while(core.isAlive(window)){
		while(window.shouldClose()){
			core.process();
		//	time = glfwGetTime();
                                glfwSwapBuffers(window.getWindow());
                                glfwPollEvents();
		//	core.pulse(window);
		}
	}catch(CoreException &e){
		e.out();
		e.halt();
	}
	glfwTerminate();
	exit(EXIT_FAILURE);
}

