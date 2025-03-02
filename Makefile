COMPILE=g++ main.cc -lm -lglfw -lGLESv2 -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lX11 -ldl -lxml2 $(shell pkg-config --cflags freetype2) -lfreetype -z defs -g -o morningStarEngine
all:
	$(COMPILE) && ./make_shared.sh
main:
	$(COMPILE) 
run:
	$(COMPILE); ./morningStarEngine
complete:
	mkdir ./projects 
	$(COMPILE) 
clean:
	rm ./morningStarEngine
install:
	sudo apt-get install freeglut3-dev libxml2-dev -y
shared:
	./make_shared.sh
