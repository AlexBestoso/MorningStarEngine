#include "./main.h"
#include "./src/error/error.h"

#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int global_w=700, global_h=700;
void CoreFrameBuffer(GLFWwindow*, int width, int height){
	global_w=width;
	global_h=height;
    glViewport(0, 0, width, height);
}

void CoreKeyboard(GLFWwindow* window, int key, int /*scancode*/, int /*action*/, int mods){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
        if((key >= 0x41 && key <= 0x5a) && mods ==0){
                key += (0x61-0x41);
        }
       // updateKeyboard((GLFW_PRESS == action || GLFW_REPEAT == action), key, action, mods);
        //updateKeyboardSpecial((GLFW_PRESS == action || GLFW_REPEAT == action), key);
}

void glutErrorHandle(int code, const char *msg){
        printf("GLUT ERROR [%d : %s]\n", code, msg);
}
//WindowCtrl window("MSGE");
Entity God("Morning Star Engine");
testEnt adam;
const char *adamVtxShdr = "./junk/testEntity.vetx.glsl"; 
const char *adamFraShdr = "./junk/tetEntity.frag.glsl";
const char *adamGeoShdr = "./junk/testEntity.geom.glsl";

int main(void){
	God.alphaBlendFunc();
        God.depthTest(true);
        God.blend(true); 
        God.clipDistance(true, 1); 
        God.colorLogic(false); 
        God.cullFace(false); 
        God.debugOutput(false); 
        God.syncDebugOutput(false); 
        God.depthClamp(false); 
        God.dither(false); 
        God.framebufferSRGB(false); 
        God.lineSmooth(false); 
        God.multiSample(false); 
        God.polygonOffsetFill(false); 
        God.polygonOffsetLine(false); 
        God.polygonOffsetPoint(false); 
        God.ploygonSmooth(false); 
        God.primitiveRestart(false); 
        God.primitiveResartFixedIndex(false); 
        God.rasterizerDiscard(false); 
        God.sampleAlphaToCoverage(false); 
        God.sampleAlphaToOne(false); 
        God.sampleCoverage(false); 

	God.setFrameResizeCallBack(CoreFrameBuffer);
	God.setKeyboardCallback(CoreKeyboard);
	God.current();
	glViewport(0, 0, global_w, global_w);
	
	adam.fillSoul(&God);
	adam.setVertexShader(adamVtxShdr);
	adam.setFragmentShader(adamFraShdr);
	try{
		adam.setGeometryShader(adamGeoShdr);
	}catch(CoreException &e){
		e.out();
	};
	adam.compile();

	adam.setVao();
	adam.setVbo();
	adam.bindVao();
	adam.bindVbo();
	adam.defineInput();	
	adam.unbindVbo();
	adam.unbindVao();
	
	glViewport(0, 0, global_w, global_w);
	while(God.shouldClose()){
		God.drawClear();
		adam.draw();	
		God.poll();
	}
	printf("Exiting application.\n");
	God.kill();
	exit(EXIT_FAILURE);
}

