#include "./main.h"
#include "./src/error/error.h"

#include "./src/windowCtrl/windowCtrl.h"
#include "./src/shader/shader.h"
#include "./src/entity/entity.h"

#include "./junk/testEntity.h"

#include "./src/core/core.h"

int main(int argc, char *argv[]){
	try{
		Core core;
		
		core.init();

		while(core.isAlive()){
			core.process();
			core.pulse();
		}
	}catch(CoreException &e){
		e.out();
		e.halt();
	}
	glfwTerminate();
	exit(EXIT_FAILURE);
}

