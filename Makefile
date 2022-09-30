all:
	g++ main.cc -lglut -lGL -lX11 -o msge && ./msge
clean:
	rm ./msge
