COMPILE=g++ main.cc -lglut -lGL -lX11 -ldl -lxml2 -o msge
all:
	$(COMPILE) 
run:
	$(COMPILE); ./msge
complete:
	mkdir ./projects 
	$(COMPILE) 
clean:
	rm ./msge
