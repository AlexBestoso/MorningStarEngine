COMPILE=-lm -lglfw -lGLESv2 -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lX11 -lxml2 $(shell pkg-config --cflags freetype2) -lfreetype -z defs -g
all:
	g++ 3dTest.cc $(COMPILE) -fPIC -shared -o ../b.so
