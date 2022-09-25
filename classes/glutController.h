class GlutController{
public:
	int displayX = 0;
	int displayY = 0;
	
	void getDisplayResolution(void){
		Display* d = XOpenDisplay(NULL);
		Screen*  s = DefaultScreenOfDisplay(d);
		this->displayX = s->width;
		this->displayY = s->height;
	}

	int startGlutController(int argc, char *argv[]){
		this->getDisplayResolution();
		
		glutInit(&argc, argv);
        	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
        	glutInitWindowSize(this->displayX, this->displayY);//(1000, 500);
		keyboard.width = this->displayX;
		keyboard.height = this->displayY;
		printf("Screen Resolition %d x %d\n", this->displayX, this->displayY);
        	glutInitWindowPosition(0, 0);
        	glutCreateWindow("Morning Star Engine");
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
		if(x >=0 && x < keyboard.width/2){
			x = -1 + (x*((9999999/(keyboard.width/2))*0.0000001));
		}else if(x == keyboard.width/2){
			x = 0;
		}else if(x > keyboard.width/2 && x < keyboard.width){
			x = -1 + (x*((9999999/(keyboard.width/2))*0.0000001));
		}else if(x == keyboard.width){
			x = 1;
		}
                return x;
        }

        static float getY(float y){
                if(y >=0 && y < keyboard.height/2){
                        y = -1 + (y*((9999999/(keyboard.height/2))*0.0000001));
                }else if(y == keyboard.height/2){
                        y = 0;
                }else if(y > keyboard.height/2 && y < keyboard.height){
                        y = -1 + (y*((9999999/(keyboard.height/2))*0.0000001));
                }else if(y == keyboard.height){
                        y = 1;
                }
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
		keyboard.mouseX = getX(x);
		keyboard.mouseY = getY(y);
		context.mousePassiveContextSwitch(getX(x), getY(y));
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
