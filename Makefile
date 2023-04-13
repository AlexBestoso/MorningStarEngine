COMPILE=g++ main.cc -lglut -lGL -lX11 -ldl -lxml2 -o msge
all:
	mkdir ./projects
	$(COMPILE) 
run:
	$(COMPILE); ./msge
clean:
	rm ./msge
