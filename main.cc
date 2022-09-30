#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <X11/Xlib.h>
#include <time.h>

using namespace std;

#include "./classes/bmpParser.h"
#include "./cryptography/base64.h"
#include "./cryptography/aes128cbc.h"
#include "./classes/fileIO.h"
#include "./classes/settingsController.h"
#include "./classes/keyboard.h"
#include "./core/MorningStarEngine.core.h"

int main(int argc, char *argv[]){
	MorningStarEngine engine;

	engine.startEngine(argc, argv);
	return 0;
}
