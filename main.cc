#include "./main.h"

int main(int argc, char *argv[]){
//        printf("Gathering x11 Screen data..\n");
	//X11_display = XOpenDisplay(NULL);
        //X11_screen = DefaultScreenOfDisplay(X11_display);

	MorningStarEngine engine;

	engine.startEngine(argc, argv);
	return 0;
}
