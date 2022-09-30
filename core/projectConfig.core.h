class ProjectConfig{
	private:
		FileSnake fileSnake;
		base64Class base64;
		string configFileLocation = "";
		const int PROJECT_NAME = 0;
	public:
		void setConfigFile(string location){
			this->configFileLocation = location;
		}
		
		void create(string projectName){
			if(this->configFileLocation == ""){
				fprintf(stderr, "[E] Config file location isn't set.\n");
				return;
			}
			base64.setInputs((char*)projectName.c_str(), projectName.size());
			base64.encode();
			projectName = base64.getResult();
			projectName += '\n';
			fileSnake.writeFileTrunc(this->configFileLocation, (char*)projectName.c_str(), projectName.size());
		}	
};
