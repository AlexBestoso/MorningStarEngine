class ProjectConfig{
	private:
		FileSnake fileSnake;
		string configFileLocation = "";
		static const int PROJECT_NAME = 0;
		static const int PROJECT_DEFAULT_BG_COLOR = 1;

		string getConfigField(const int position, char *fileBuffer, size_t fileSize){
			string ret = "";
			int posTracker = 0;
			bool found = false;
			for(int i=0; i<fileSize; i++){
				if(posTracker == position){
					if(fileBuffer[i] == '\n'){
						found = true;
						break;
					}
					ret += fileBuffer[i];
				}else if(fileBuffer[i] == '\n'){
					posTracker++;
					continue;
				}

			}

			if(!found){
				fprintf(stderr, "[E] Failed to load Project Field '%d'\n", position);
				return "";
			}
			base64Class base64;
			base64.setInputs((char *)ret.c_str(), ret.size());
			base64.decode();
			ret = base64.getResult();
			return ret;
		}

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

			/* Write Project Name [0] */
			string buffer = this->encode(data.name);
			buffer += '\n';
			fileSnake.writeFileTrunc(this->configFileLocation, (char*)buffer.c_str(), buffer.size());
			
			/* Write Default BG Color [1] */
			buffer = this->encode(floatArrayToString(data.startingBgColor, 3));
			buffer += '\n';
			fileSnake.writeFileAppend(this->configFileLocation, (char*)buffer.c_str(), buffer.size());	
			return true;
		}

		bool load(string projectConfigLocation, struct ProjectStruct *proj){
			if(!fileSnake.fileExists(projectConfigLocation)){
				fprintf(stderr, "[E] Config file cannot be found!\n");
				return false;
			}
			size_t fileSize = fileSnake.getFileSize(projectConfigLocation);
			char *fileBuffer = new char[fileSize];
			if(!fileSnake.readFile(projectConfigLocation, fileBuffer, fileSize)){
				fprintf(stderr, "[E] Failed to read config file.\n");
				delete[] fileBuffer;
				return false;
			}
			string buffer = "";
	
			/* get name [0] */
			proj->name = this->getConfigField(PROJECT_NAME, fileBuffer, fileSize);
			
			/* get default bg color [1] */
			buffer = this->getConfigField(PROJECT_DEFAULT_BG_COLOR, fileBuffer, fileSize);
			this->stringToFloatArray(buffer, proj->startingBgColor, 3);

			return true;	
		}
};
