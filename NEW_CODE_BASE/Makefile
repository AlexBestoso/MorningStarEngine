FLAGS=-Wall -Werror -Wextra -Wshadow -pedantic -Wsign-conversion -O2 -I$(pwd)/src -lm -lglfw -lGLESv2 -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lX11 -ldl -lxml2 $(shell pkg-config --cflags freetype2) -lfreetype -z defs -g
all:
	g++ -c main.cpp $(FLAGS) 
	g++ -c ./src/error/error.cpp $(FLAGS)
	g++ -c ./src/core/core.error.cpp $(FLAGS)
	g++ -c ./src/core/core.cpp $(FLAGS)
	g++ -c ./src/windowCtrl/windowCtrl.cpp $(FLAGS)
	g++ -c ./src/windowCtrl/windowCtrl.error.cpp $(FLAGS)
	g++ -c ./src/shader/shader.cpp $(FLAGS)
	g++ -c ./src/shader/shader.error.cpp $(FLAGS)
	g++ -c ./src/entity/entity.cpp $(FLAGS)
	g++ -c ./src/entity/entity.error.cpp $(FLAGS)
	g++ -c ./junk/testEntity.cpp $(FLAGS)
	g++ -o morningStarEngine main.o error.o core.o core.error.o windowCtrl.o windowCtrl.error.o shader.o shader.error.o entity.o entity.error.o  testEntity.o $(FLAGS)
main:
	$(COMPILE) 
run:
	$(COMPILE); ./morningStarEngine
complete:
	mkdir ./projects 
	$(COMPILE) 
clean:
	rm ./*.o
install:
	sudo apt-get install freeglut3-dev libxml2-dev -y
shared:
	./make_shared.sh
