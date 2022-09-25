class GlutController{
public:
	int startGlutController(int argc, char *argv[]){
		
		glutInit(&argc, argv);
        	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
        	glutInitWindowSize(1000, 500);
        	glutInitWindowPosition(100, 100);
        	glutCreateWindow("Hello world");
		glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

        	glutDisplayFunc(display);
		glutMouseFunc(mouseClick);
		glutMotionFunc(mouseMovement);
		glutPassiveMotionFunc(mousePassive);
		glutKeyboardUpFunc(keyboard_up);
		glutIdleFunc(idle);
		glutKeyboardFunc(keyboard_down);
		glutReshapeFunc(resize);

        	glutMainLoop();
	}
	
	static float getX(float x){
        	if(keyboard.width > keyboard.height)
                        x = -1 + (x * .002);
                else if(keyboard.width < keyboard.height)
                        x = -1 + (x * .002 * (keyboard.height / keyboard.width));
                else
                        x = -1 + x * .002;
                return x;
        }

        static float getY(float y){
                if(keyboard.width > keyboard.height)
                        y = -1 + (y * .002 * (keyboard.width / keyboard.height));
                else if(keyboard.width < keyboard.height)
                        y = -1 + (y * .002);
                else
                        y = -1 + y * .002;
                return y;
        }	

private:
	static void mouseClick(int button, int state, int x, int y){
		keyboard.mouseX = getX(x);
		keyboard.mouseY = getY(y);
		context.mouseClickContextSwitch(button, state, x, y);
	}

	static void resize(int w, int h){
		keyboard.width = w;
		keyboard.height = h;
		glViewport(0, 0, w, h);
	}

	static void mouseMovement(int x, int y){
		keyboard.mouseX = getX(x);
		keyboard.mouseY = getY(y);
		context.mouseMovementContextSwitch();
	}

	static void display(void){
		context.displayContextSwitch();
		glutSwapBuffers();
	}

	static void mousePassive(int x, int y){
		keyboard.mouseX = x;
		keyboard.mouseY = y;
		context.mousePassiveContextSwitch(x, y);
	}

	static void idle(void){
		context.idleContextSwitch();
		glutPostRedisplay();
	}
	
	static void keyboard_down(unsigned char key, int mouseX, int mouseY){
        	keyboard.mouseX = getX(mouseX);
        	keyboard.mouseY = getY(mouseY);
        	keyboard.activateKey(key);
		context.keydownContextSwitch();
        	glutPostRedisplay();
	}

	static void keyboard_up(unsigned char key, int mouseX, int mouseY){
	        keyboard.mouseX = getX(mouseX);
	        keyboard.mouseY = getY(mouseY);
	        keyboard.deactivateKey(key);
		context.keyupContextSwitch();
	        glutPostRedisplay();
	}

};
