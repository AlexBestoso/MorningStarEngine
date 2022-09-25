#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <X11/Xlib.h>

using namespace std;

#include "./classes/GodsBlessing.h"
#include "./cryptography/base64.h"
#include "./cryptography/aes128cbc.h"
#include "./classes/fileIO.h"
#include "./classes/settingsController.h"
#include "./classes/keyboard.h"
#include "./objects/linker.h"
#include "./classes/contextProvider.h"
#include "./classes/glutController.h"

int main(int argc, char *argv[]){
	GlutController glutController;

	glutController.startGlutController(argc, argv);
	return 0;
}
