all:
	g++ main.cc -lglut -lGL -lX11 -o universe && ./universe
clean:
	rm ./universe
