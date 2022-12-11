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

using namespace std;

#define HOME_PAGE 0
#define DEVELOPER_PAGE 1

//Display *X11_display = NULL;
//Screen *X11_screen = NULL;

#include "./classes/tools/fileSnake.class.h"
#include "./classes/tools/parsers/bmpParser.h"
#include "./classes/cryptology/hashing/base64.h"
#include "./classes/cryptology/cryptography/aes128cbc.h"
#include "./classes/keyboard.h"

#include "./classes/core/objects/objectLinker.h"
#include "./classes/core/soLoader/SoLoader.h"
#include "./classes/core/projects/Project.core.h"
#include "./classes/core/periferals/periferals.core.h"
#include "./classes/core/pages/pageLinker.h"
#include "./classes/core/context/ContextProvider.h"

#include "./classes/core/MorningStarEngine.core.h"
