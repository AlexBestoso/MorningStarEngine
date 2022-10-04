class ProjectConfig{
	private:
		FileSnake fileSnake;
		string configFileLocation = "";
		const int PROJECT_NAME = 0;

		string getConfigField(const int position, char *fileBuffer, size_t fileSize){
			string ret = "";
			int posTracker = 0;
			for(int i=0; i<fileSize; i++){
				if(posTracker == position){
					if(fileBuffer[i] == '\n')
						break;
					ret += fileBuffer[i];
				}else if(fileBuffer[i] == '\n'){
					posTracker++;
					continue;
				}

			}

			base64Class base64;
			base64.setInputs((char *)ret.c_str(), ret.size());
			base64.decode();
			ret = base64.getResult();
			return ret;
		}
	public:
		void setConfigFile(string location){
			this->configFileLocation = location;
		}
		
		bool create(string projectName){
			if(this->configFileLocation == ""){
				fprintf(stderr, "[E] Config file location isn't set.\n");
				return false;
			}
			base64Class base64;
			base64.setInputs((char*)projectName.c_str(), projectName.size());
			base64.encode();
			projectName = base64.getResult();
			projectName += '\n';
			fileSnake.writeFileTrunc(this->configFileLocation, (char*)projectName.c_str(), projectName.size());
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
	
			proj->name = this->getConfigField(PROJECT_NAME, fileBuffer, fileSize);
			return true;	
		}
};
