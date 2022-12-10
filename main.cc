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

using namespace std;

#include "./classes/tools/fileSnake.class.h"
#include "./classes/tools/parsers/bmpParser.h"
#include "./classes/cryptology/hashing/base64.h"
#include "./classes/cryptology/cryptography/aes128cbc.h"
#include "./classes/keyboard.h"
#include "./classes/core/MorningStarEngine.core.h"

int main(int argc, char *argv[]){
	MorningStarEngine engine;

	engine.startEngine(argc, argv);
	return 0;
}
