all:
	# Building ObjectForm Shared Object
	g++ -fPIC -shared $(PWD)/classes/core/objects/formObject/form.object.cc -lglut -lGL -lX11 -o $(PWD)/objects/forms/formObject/form.object.so
	g++ main.cc -lglut -lGL -lX11 -ldl -o msge
clean:
	rm ./msge
