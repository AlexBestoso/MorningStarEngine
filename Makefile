all:
	g++ main.cc -lglut -lGL -lX11 -ldl -lxml2 -o msge
clean:
	rm ./msge
