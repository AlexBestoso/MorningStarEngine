FLAGS=-I./src/ -lm -lglfw -lGLESv2 -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lX11 -ldl -lxml2 $(shell pkg-config --cflags freetype2) -lfreetype -z defs -g
all:
	g++ -c main.cpp $(FLAGS) 
	g++ -c ./src/core/core.cpp $(FLAGS)
	g++ -c ./src/windowCtrl/windowCtrl.cpp $(FLAGS)
	g++ -c ./src/shader/shader.cpp $(FLAGS)
	g++ -o morningStarEngine main.o core.o windowCtrl.o shader.o $(FLAGS)
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
