using namespace std;
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>

#include <X11/Xlib.h>

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include <iostream>
#include <dirent.h>
#include <fcntl.h>
#include <typeinfo>

#include "../core/tools/tools.h"
unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 800;

float lastX = 400, lastY = 300;
float pitch, yaw;

#include "../core/structs/structs.h"
#include "../core/peripherals/peripherals.h"
#include "../core/physics/physics.h"
#include "../core/graphics/graphics.h"

#include "../core/context/context.interface.h"

#include "../core/core.h"

