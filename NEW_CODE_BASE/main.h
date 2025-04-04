#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <X11/Xlib.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "./src/glm/glm/glm.hpp"
#include "./src/glm/glm/gtc/matrix_transform.hpp"
#include "./src/glm/glm/gtc/type_ptr.hpp"

#include <dlfcn.h>
#include <memory>
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

void CoreFrameBuffer(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mod);
void CoreKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void refreshWindowCB(GLFWwindow *window);
void glutErrorHandle(int code, const char *msg);
