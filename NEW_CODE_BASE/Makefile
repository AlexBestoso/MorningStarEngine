FLAGS=-Wall -Werror -Wextra -Wshadow -pedantic -Wsign-conversion -O2 -I$(pwd)/src -lm -lglfw  -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lGLU -lX11 -ldl -lxml2 $(shell pkg-config --cflags freetype2) -lfreetype -z defs -g
ALL_OBJS=main.o error.o core.o core.error.o windowCtrl.o windowCtrl.error.o shader.o shader.error.o entity.o entity.error.o  testEntity.o
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
	g++ -o morningStarEngine $(ALL_OBJS) $(FLAGS)

main:
	g++ -c main.cpp $(FLAGS)
	g++ -o morningStarEngine $(ALL_OBJS) $(FLAGS)
testEnt:
	g++ -c ./junk/testEntity.cpp $(FLAGS)
	g++ -o morningStarEngine $(ALL_OBJS) $(FLAGS)
clean:
	rm ./*.o
install:
	sudo apt-get install freeglut3-dev libxml2-dev -y
