#include "./main.h"
#include "./src/error/error.h"

#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int global_w=1918, global_h=1014;
void CoreFrameBuffer(GLFWwindow*, int width, int height){
	printf("resizing to %d %d\n", width, height);
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
int globsize = 4;
GLfloat glob_vertex[4] = {
	 -0.5f, 0.5f,
        0.5f, -0.5f//, 0.0f 
        //vertecies[8] = 0.0f;  // top 
};
int main(int argc, char *argv[]){
	printf("%d %s\n", argc, argv[0]);
	try{
	God.init();
	God.current();
        God.depthTest(true);
        God.blend(true); 
	God.alphaBlendFunc();

	God.setFrameResizeCallBack(CoreFrameBuffer);
	God.setKeyboardCallback(CoreKeyboard);
	
	adam.fillSoul(&God);
	adam.setVertex(glob_vertex, globsize);
	adam.setVertexShader(adamVtxShdr);
	adam.setFragmentShader(adamFraShdr);
	adam.setGeometryShader(adamGeoShdr);
	adam.compile();
	
	adam.defineInput();	
	
	while(God.shouldClose()){
		God.drawClear();
		adam.draw();	
		God.poll();
	}
	}catch(CoreException &e){
		e.out();
	};

	printf("Exiting application.\n");
	God.kill();
	exit(EXIT_FAILURE);
}

