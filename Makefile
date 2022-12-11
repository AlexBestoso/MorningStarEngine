all:
	# Building ObjectForm Shared Objects
	g++ -fPIC -shared $(PWD)/classes/core/objects/formObject/form.object.cc -lglut -lGL -lX11 -o $(PWD)/objects/forms/formObject/form.object.so
	g++ -fPIC -shared $(PWD)/classes/core/objects/formObject/formContextMenu/formContextMenu.object.cc -lglut -lGL -lX11 -o $(PWD)/objects/forms/formObject/formContextMenu.object.so
	# Build main program
	g++ main.cc -lglut -lGL -lX11 -ldl -o msge
clean:
	rm ./msge
