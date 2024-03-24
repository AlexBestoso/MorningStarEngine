COMPILE=g++ main.cc -lm -lglfw -lGLESv2 -lXrandr -lpthread -lXi -lX11 -lXmu -lglut -lGL -lX11 -ldl -lxml2 -o glutTest
all:
	$(COMPILE) 
run:
	$(COMPILE); ./glutTest
complete:
	mkdir ./projects 
	$(COMPILE) 
clean:
	rm ./glutTest
install:
	sudo apt-get install freeglut3-dev libxml2-dev -y
