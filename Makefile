all:
	# Building ObjectForm Shared Objects
	mkdir -p $(PWD)/classes/core/objects/formObject
	g++ -fPIC -shared $(PWD)/classes/core/objects/formObject/form.object.cc -lglut -lGL -lX11 -o $(PWD)/objects/forms/formObject/form.object.so
	g++ -fPIC -shared $(PWD)/classes/core/objects/formObject/formContextMenu/formContextMenu.object.cc -lglut -lGL -lX11 -o $(PWD)/objects/forms/formObject/formContextMenu.object.so
	# Building project shared object
	#mkdir -p $(PWD)/classes/core/projects
	#g++ -fPIC -shared $(PWD)/classes/core/projects/project.object.cc -lglut -lGL -lX11 -o $(PWD)/project/project.object.so
	# Build main program
	g++ main.cc -lglut -lGL -lX11 -ldl -o msge
clean:
	rm ./msge
