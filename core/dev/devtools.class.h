class DevTools{
	private:
		std::string *argv = NULL;
		size_t argc = 0;
	
		float color[3] = {0.7f, 0.5f, 0.1f};

		int processCommand(std::string command){
			if(command == ""){
				return -1;
			}
			std::string grabber = "";
			for(int i=0; i<command.length(); i++){
				if(command[i] == ' ')
					argc++;
			}
			argc++;
			int track = 0;
			argv = new std::string[argc];
			for(int i=0; i<command.length(); i++){
				if(command[i] == ' '){
					argv[track] = grabber;
					grabber = "";	
					track++;
				}else{
					grabber += command[i];
				}
			}
			if(grabber != ""){
				argv[track] = grabber;
			}

			if(argv[0] == "drawLine"){
				return 1;
			}
			
			delete[] argv;
			argv = NULL;
			argc = 0;
			return -1;
		}
	public:
		void drawLine(GLFWwindow *window, GraphicsObject go){
			if(argc != 7){
				printf("Draw Line usage : drawLine [0.0, 0.0, 0.0] [1.0 1.0 1.0]\n");
				return;
			}

			glm::vec3 a = glm::vec3(std::stof(argv[1]), std::stof(argv[2]), std::stof(argv[3]));
			glm::vec3 b = glm::vec3(std::stof(argv[4]), std::stof(argv[5]), std::stof(argv[6]));

			GraphicsGeometry gg;
			line3_t line = gg.createLine(a, b);
			
			size_t dataSize = 11*2;
			float *lineData = new float[dataSize];
			lineData[0] = a.x;
			lineData[1] = a.y;
			lineData[2] = a.z;
			lineData[3] = 0.0f;
			lineData[4] = 0.0f;
			lineData[5] = line.direction.x;
			lineData[6] = line.direction.y;
			lineData[7] = line.direction.z;
			lineData[8] = color[0];
			lineData[9] = color[1];
			lineData[10] = color[2];
			
			lineData[11] = b.x;
                        lineData[12] = b.y;
                        lineData[12] = b.z;
                        lineData[13] = 0.0f;
                        lineData[14] = 0.0f;
                        lineData[15] = line.direction.x;
                        lineData[16] = line.direction.y;
                        lineData[17] = line.direction.z;
                        lineData[18] = color[0];
                        lineData[19] = color[1];
                        lineData[20] = color[2];

			go.directDraw(lineData, dataSize, 2, GL_LINES);

			delete[] lineData;
		}

		void runCommand(std::string cmd, GLFWwindow *window, GraphicsObject go){
			switch(this->processCommand(cmd)){
				case 1:
					drawLine(window, go);
					break;
				default:
					printf("Invalid command.\n");
					break;
			}

			if(this->argv != NULL){
				delete[] argv;
			}
			argc = 0;
		}
};
