#include "./main.h"
#include "./src/error/error.h"

#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int global_w=700, global_h=700;
void CoreFrameBuffer(GLFWwindow*, int width, int height){
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

int main(void){
	God.current();
	God.setFrameResizeCallBack(CoreFrameBuffer);
	God.setKeyboardCallback(CoreKeyboard);
	
	adam.fillSoul(&God);
	adam.setVertexShader(adamVtxShdr);
	adam.setFragmentShader(adamFraShdr);
	adam.compile();

	adam.setVao();
	adam.setVbo();
	adam.bindVao();
	adam.bindVbo();
	adam.defineInput();	
	adam.unbindVbo();
	adam.unbindVao();
	
	while(God.shouldClose()){
		God.drawClear();
		adam.draw();	
		God.poll();
	}
	printf("Exiting application.\n");
	God.kill();
	exit(EXIT_FAILURE);
}

