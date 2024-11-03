class DevTools : public GraphicsObject{
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
			}else if(argv[0] == "ldraw"){
				return 2;
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

		

		bool objectReady = false;
		float serial_data[6000]; // arbitrary max
		size_t serial_data_s = 0;
		bool ldrawClickMode = false;
		glm::vec3 clickColor = glm::vec3(1.5, 0.0, 0.0);
		GLenum drawMode = GL_LINES;
	
		void ldraw(){
			if(argc == 2){
				if(argv[1] == "clear"){
					for(int i=0; i<6000; i++)
						serial_data[i] = 0;
					serial_data_s = 0;
					objectReady = false;
				}
				
				if(argv[1] == "enum"){
					printf("Current draw buffer : ");
					for(int i=0; i<serial_data_s; i++){
						if((i%6) == 0 && i != 0)
							printf("\n");
						printf("%f ", serial_data[i]);
					}printf("\n");
					return;
				}

				if(argv[1] == "ready"){
					objectReady = true;
					printf("Drawing object...\n");
				}
				if(argv[1] == "unready"){
					objectReady = false;
					printf("hiding object...\n");
				}
				if(argv[1] == "pop"){
					if(serial_data_s < 0 || serial_data_s > 6000)
						return;
					if(serial_data_s - 6 < 6){
						for(int i=0; i<6000; i++)
                                                	serial_data[i] = 0;
                                        	serial_data_s = 0;
                                        	objectReady = false;
						return;
					}
					for(int i=serial_data_s-6; i<serial_data_s; i++)
						serial_data[i] = 0;
					serial_data_s-=6;
					return;
				}
			}else if(argc == 3){
				if(argv[1] == "clickmode" && argv[2] == "on"){
					printf("click mode enabled.\n");
					ldrawClickMode = true;
				}else if(argv[1] == "clickmode"){
					printf("click mode disabled.\n");
					ldrawClickMode = false;
				}


				if(argv[1] == "drawmode" && argv[2] == "lines"){
					drawMode = GL_LINES;
				}
				if(argv[1] == "drawmode" && argv[2] == "points"){
					drawMode = GL_POINTS;
				}
				if(argv[1] == "drawmode" && argv[2] == "linestrip"){
					drawMode = GL_LINE_STRIP;
				}
				if(argv[1] == "drawmode" && argv[2] == "lineloop"){
					drawMode = GL_LINE_LOOP;
				}
				if(argv[1] == "drawmode" && argv[2] == "trianglestrip"){
					drawMode = GL_TRIANGLE_STRIP;
				}
				if(argv[1] == "drawmode" && argv[2] == "trianglefan"){
					drawMode = GL_TRIANGLE_FAN;
				}
				if(argv[1] == "drawmode" && argv[2] == "triangles"){
					drawMode = GL_TRIANGLES;
				}
			
			}else if(argc == 5 || argc == 8){
				if(argv[1] == "push"){
					switch(argc){
						case 5:{
							try{
								int idx = serial_data_s;
								serial_data_s+=6;
								if(serial_data_s > 6000)
									return;
								printf("Pushing data...\n");
								serial_data[idx] = std::stof(argv[2]);
								idx++;
								serial_data[idx] = std::stof(argv[3]);
								idx++;
								serial_data[idx] = std::stof(argv[4]);
							}catch(std::exception e){
								serial_data_s-=6;
								printf("Bad push args... [%s]\n", e.what());
								return;
							}
							break;
						}

						case 8:{
							try{
								int idx = serial_data_s;
								serial_data_s+=6;
								if(serial_data_s > 6000)
									return;
								printf("Pushing data...\n");
								serial_data[idx] = std::stof(argv[2]);
								idx++;
								serial_data[idx] = std::stof(argv[3]);
								idx++;
								serial_data[idx] = std::stof(argv[4]);
								idx++;
								serial_data[idx] = std::stof(argv[5]);
								idx++;
								serial_data[idx] = std::stof(argv[6]);
								idx++;
								serial_data[idx] = std::stof(argv[7]);

							}catch(std::exception e){
								serial_data_s-=6;
								printf("Bad push args... [%s]\n", e.what());
								return;
							}
							break;
						}
					}
				}
			}
		}
	public:

		void draw(void){
			if(!objectReady)
				return;
			this->bindVao();
                        this->bindVbo();
                        this->use(); 
			glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
                        //model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);
			view = camera.getView();
                        unsigned int viewLoc = this->getUniformLoc("view");
                        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

                        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                        unsigned int projectionLoc = this->getUniformLoc("projection");
                        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);	

			this->storeVertexData(sizeof(float)*this->serial_data_s, this->serial_data, GL_STATIC_DRAW);
                        glDrawArrays(drawMode, 0, serial_data_s/6);
		}
		bool create(void){
			int err = 0;
			if((err = this->createShaders("./core/dev/vtx_line.glsl", "./core/dev/fag_line.glsl")) != 0){
                                switch(err){ 
                                        case 1: printf("Vertex Shader error.\n");break;
                                        case 2: printf("Fragment shader error.\n");break;
                                        default: printf("Shader Linking error.\n");break;
                                }
                                return false;
                        }
			this->generateObjectIds(true, true, false);
                        this->bindVao();
                        this->bindVbo();

			this->setAttributePointer(0, 3, 6, (void *)0); // vertex
                        this->enableArrayAttribute(0);
                        this->setAttributePointer(1, 3, 6, (void *)(3*sizeof(float))); // material color
                        this->enableArrayAttribute(1);

			this->unbindVao();
			this->unbindVbo();

			return true;
		}

		void processInput(glm::vec3 val){
			if(ges.mouse.click_left && ldrawClickMode){
				try{
                                        int idx = serial_data_s;
                                        serial_data_s+=6;
                                        if(serial_data_s > 6000)
                                                return;
					ges.mouse.click_left = false;
                                        printf("Pushing data...\n");
                                        serial_data[idx] = val.x;
                                        idx++;
                                        serial_data[idx] = val.y;
                                        idx++;
                                        serial_data[idx] = val.z;
                                        idx++;
                                        serial_data[idx] = clickColor.x;
                                        idx++;
                                        serial_data[idx] = clickColor.y;
                                        idx++;
                                        serial_data[idx] = clickColor.z;
					
					sleep(1);

                       		}catch(std::exception e){
                                	serial_data_s-=6;
                                        printf("Bad push args... [%s]\n", e.what());
                                        return;
                                }
			}else if(ges.mouse.click_right && ldrawClickMode){
				printf("removing line...\n");
				sleep(1);
				ges.mouse.click_right = false;
				
				if(serial_data_s <= 0 || serial_data_s > 6000)
                                                return;

                                if(serial_data_s - 6 < 6){
                                	for(int i=0; i<6000; i++)
                                       		serial_data[i] = 0;
                                        serial_data_s = 0;
                                        return;
                                }
                                for(int i=serial_data_s-6; i<serial_data_s; i++)
                                	serial_data[i] = 0;
                               	serial_data_s-=6;
			}
		}

		void runCommand(std::string cmd, GLFWwindow *window, GraphicsObject go){
			switch(this->processCommand(cmd)){
				case 1: // objenum
					objEnum(go);
					break;
				case 2: // ldraw
					ldraw();
					break;
				default:
					printf("Invalid command '%s'.\n", cmd.c_str());
					return;
			}

			delete[] argv;
                        argv = NULL;
                        argc = 0;
		}
};
