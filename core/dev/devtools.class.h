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

			if(argv[0] == "objenum"){
				return 1;
			}
			
			delete[] argv;
			argv = NULL;
			argc = 0;
			return -1;
		}

		void objEnum(GraphicsObject go){
			if(argc == 1){
				printf("Enumerating %d scene objects...\n", go.getObjCount());
				for(int i=0; i<go.getObjCount(); i++){
					WavefrontObject wo = go.getObjs(i);
					wo.enumObj();
					printf("\n");
				}
			}

			if(argc >= 2 && argv[1] == "names"){
				printf("Enumerating %d object names...\n", go.getObjCount());
                                for(int i=0; i<go.getObjCount(); i++){
                                        WavefrontObject wo = go.getObjs(i);
					if(argc == 2){
						printf("%d) %s\n", i, wo.getName().c_str());
					}else if(wo.getName() == argv[2]){
						wo.enumObj();	
						break;
					}
				}
			}else if(argc == 2){
				try{
				int i = std::stoi(argv[1]);
				if(i<go.getObjCount()){
					printf("Enumerating scene object %d...\n", i);
					WavefrontObject wo = go.getObjs(i);
					wo.enumObj();
					printf("\n");
				}}catch(std::exception e){
					printf("Invalid object id '%s'\n", argv[1].c_str());
				}
			}
		}
	public:

		void runCommand(std::string cmd, GLFWwindow *window, GraphicsObject go){
			switch(this->processCommand(cmd)){
				case 1: // objenum
					objEnum(go);
					break;
				default:
					printf("Invalid command '%s'.\n", cmd.c_str());
					break;
			}

			if(this->argv != NULL){
				delete[] argv;
			}
			argc = 0;
		}
};
