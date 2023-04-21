#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <X11/Xlib.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include <typeinfo>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>

//[>>core_includes<<]
#include "./core/keyboard.h"
#include "./core/ContextProvider.core.h"
#include "./core/MorningStarEngine.core.h"

int main(int argc, char *argv[]){
        MorningStarEngine engine;
        engine.startEngine(argc, argv);
        
	return 0;
}
