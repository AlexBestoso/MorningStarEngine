class ProjectConfig{
	private:
		FileSnake fileSnake;
		XmlSnake xmlSnake;
		string configFileLocation = "";

		string floatArrayToString(float *array, size_t size){
			string ret = "";
			for(int i =0; i<size; i++){
				ret += to_string(array[i]) + ',';
			}
			return ret;
		}
		void stringToFloatArray(string src, float *dst, size_t size){
			if(src == ""){
				for(int i=0; i<size; i++){
					dst[i] = 0;
				}
				return;
			}
			string buffer = "";
			int track = 0;
			for(int i=0; i<src.size(); i++){
				if(src[i] != ','){
					buffer += src[i];
				}else if(track >= size){
					break;	
				}else{
					char *err;
					dst[track] = strtof(buffer.c_str(), &err);
					if(err != 0)
						dst[track] = 0;
					track++;
					buffer = "";
				}
			}
		}
		string encode(string buffer){
			base64Class base64;
                        base64.setInputs((char*)buffer.c_str(), buffer.size());
                        base64.encode();
                        return  base64.getResult();
		}
	public:
		void setConfigFile(string location){
			this->configFileLocation = location;
		}
		
		bool create(struct ProjectStruct data){
			if(this->configFileLocation == ""){
				fprintf(stderr, "[E] Config file location isn't set.\n");
				return false;
			}

			if(!xmlSnake.openFileWriter(this->configFileLocation)){
				fprintf(stderr, "[E] Failed to create project config file");
				return false;
			}

			if(!xmlSnake.startWritingFile()){
				fprintf(stderr, "[E] Failed to start XML writer.\n");
				return false;
			}
			// Root element
			if(!xmlSnake.startWritingElement(data.projectRootElement)){
				fprintf(stderr, "[E] Failed to create xml root element.\n");
				return false;
			}
			// Config Elements
			if(!xmlSnake.writeElement(data.nameElement, data.name)){
				fprintf(stderr, "Failed to write project name element.\n");
				return false;
			}
			if(!xmlSnake.writeElement(data.authorElement, "Project Author")){
                                fprintf(stderr, "Failed to write project name element.\n");
                                return false;
                        }
			if(!xmlSnake.writeElement(data.descriptionElement, "Project Description")){
                                fprintf(stderr, "Failed to write project name element.\n");
                                return false;
                        }
			if(!xmlSnake.writeElement(data.versionElement, "0.0.0")){
                                fprintf(stderr, "Failed to write project name element.\n");
                                return false;
                        }
			xmlSnake.stopWritingElement();
			xmlSnake.stopWritingFile();
			xmlSnake.closeFileWriter();

			
			return true;
		}

		bool load(string projectConfigLocation, struct ProjectStruct *proj){
			if(!fileSnake.fileExists(projectConfigLocation)){
				fprintf(stderr, "[E] Config file cannot be found!\n");
				return false;
			}
			if(!xmlSnake.openFileReader(projectConfigLocation)){
				fprintf(stderr, "[E] Failed to open xml config file for reading\n");
				return false;
			}
			bool properFile = false;
			while(xmlSnake.readLineReader()){
				string resultName = xmlSnake.readResult.name;

				if(resultName == proj->projectRootElement){
					properFile = true;
				}
				if(resultName == proj->versionElement){
					xmlSnake.readLineReader();
					proj->version = xmlSnake.readResult.value;
					xmlSnake.readLineReader();
				}
				if(resultName == proj->nameElement){
					xmlSnake.readLineReader();
					proj->name = xmlSnake.readResult.value;
					xmlSnake.readLineReader();
				}
				if(resultName == proj->authorElement){
					xmlSnake.readLineReader();
					proj->author = xmlSnake.readResult.value;
					xmlSnake.readLineReader();
				}
				if(resultName == proj->descriptionElement){
					xmlSnake.readLineReader();
					proj->description = xmlSnake.readResult.value;
					xmlSnake.readLineReader();
				}
				
				// error handling
				if(!properFile){
					fprintf(stderr, "[E] Invalid project file detected.\n");
					break;
				}
			}
			xmlSnake.closeReader();

			return properFile;
		}

		bool remove(string projectLocation){
			return fileSnake.removeDirRecursive(projectLocation);
		}
};
