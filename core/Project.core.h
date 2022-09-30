#include "./projectConfig.core.h"
class Project{
	private:
		FileSnake fileSnake;
		ProjectConfig config;
		const string projectStorage = "./projects";
		const string projectConfig = "project.conf";
		string projectName;
		
	public:
		bool create(string projectName){
			this->projectName = projectName;
			if(!fileSnake.dirExists(this->projectStorage)){
				fileSnake.makeDir(this->projectStorage);
			}

			if(fileSnake.dirExists(this->projectStorage+"/"+projectName)){
				fprintf(stderr, "[E] Project already exists.\n");
				return false;
			}
			fileSnake.makeDir(this->projectStorage+"/"+projectName);
			config.setConfigFile(this->projectStorage+"/"+projectName+"/"+this->projectConfig);
			config.create(this->projectName);
			return true;

		}
		int load(string projectName){
			return -1;	
		}
}project;
