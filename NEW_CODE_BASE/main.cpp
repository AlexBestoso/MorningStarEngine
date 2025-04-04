#include "./main.h"
#include "./src/error/error.h"

#include "./src/windowCtrl/windowCtrl.h"
#include "./src/shader/shader.h"
#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int global_w=700, global_h=700;
void CoreFrameBuffer(GLFWwindow*, int width, int height){
        global_w = width;
        global_h = height;
    glViewport(0, 0, width, height);
}

void glutErrorHandle(int code, const char *msg){
        printf("GLUT ERROR [%d : %s]\n", code, msg);
}
Core core;
WindowCtrl window("MSGE");

int main(/*int argc, char *argv[]*/void){
		//try{
	glfwInit();
	window.init();
                        window.current();
                        window.blend(false);
                        window.depthTest(false);
                        //window.alphaBlendFunc();
                        window.setFrameResizeCallBack(CoreFrameBuffer);
                        window.setKeyboardCallback(keyboard_callback);
                        window.setMouseClickCallback(mouse_click_callback);
                        window.setMouseCursorPosCallback(mouse_callback);
			window.setErrorHandleCallback(glutErrorHandle);

			window.clipDistance(false, 0); 
                	window.colorLogic(false); 
                	window.cullFace(false); 
                	window.debugOutput(false); 
                	window.syncDebugOutput(false); 
                	window.depthClamp(false); 
                	window.dither(false); 
                	window.framebufferSRGB(false); 
                	window.lineSmooth(false); 
                	window.multiSample(false); 
                	window.polygonOffsetFill(false); 
                	window.polygonOffsetLine(false); 
                	window.polygonOffsetPoint(false); 
                	window.ploygonSmooth(false);	
			window.primitiveRestart(false); 
                	window.primitiveResartFixedIndex(false); 
                	window.rasterizerDiscard(false); 
                	window.sampleAlphaToCoverage(false); 
                	window.sampleAlphaToOne(false); 
               		window.sampleCoverage(false); 
                	window.sampleShading(false); 
                	window.sampleMask(false); 
                	window.scissorTest(false); 
                	window.stencilTest(false); 
                	window.textureCubeMapSeamless(false); 
                	window.programPointSize(false);

		glfwSwapInterval(1);
//		while(core.isAlive(window)){
			core.init();
		while(window.shouldClose()){
                        window.current();
			core.process();
		//	time = glfwGetTime();
                                glfwSwapBuffers(window.getWindow());
                                glfwPollEvents();
		//	core.pulse(window);
		}
	//}catch(CoreException &e){
	//	e.out();
	//	e.halt();
	//}
	printf("Exiting application.\n");
	glfwTerminate();
	exit(EXIT_FAILURE);
}

