COMPILE=-lm -lglfw -lGLESv2 -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lX11 -lxml2 $(shell pkg-config --cflags freetype2) -lfreetype -z defs -g
all:
	g++ mainMenu.cc $(COMPILE) -fPIC -shared -o ../a.so
