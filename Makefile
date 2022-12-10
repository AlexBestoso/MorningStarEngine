all:
	g++ main.cc -lglut -lGL -lX11 -o msge
clean:
	rm ./msge
