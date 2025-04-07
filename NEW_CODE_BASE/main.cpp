#include "./main.h"
#include "./src/error/error.h"

#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int global_w=100, global_h=100, global_c = 50, global_c2;
void CoreFrameBuffer(GLFWwindow*, int width, int height){
	global_w = width;
	global_h = height;
	global_c = width/2 + (width%2);
	global_c2 = height/2 + (height%2); //height > width ? height/2 + (height%2) : width/2 + (width%2);

	printf(
		"Screen Dimensions: %d x %d\t centers (%d, %d)\n",
		global_w,
		global_h,
		global_c,
		global_c2
	);
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
Entity God("Morning Star Engine");
testEnt adam;
const char *adamVtxShdr = "./junk/testEntity.vetx.glsl"; 
const char *adamFraShdr = "./junk/tetEntity.frag.glsl";
const char *adamGeoShdr = "./junk/testEntity.geom.glsl";
int globsize = 6*2;
GLfloat glob_vertex[6*2] = {
	 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f
        //vertecies[8] = 0.0f;  // top 
};

//WindowCtrl window("MSGE");
int main(int argc, char *argv[]){
//nigger:

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
	//goto nigger;
	exit(EXIT_FAILURE);
}

