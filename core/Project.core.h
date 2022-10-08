struct ProjectStruct{
	string name;

};
#include "./projectConfig.core.h"
class Project{
	private:
		FileSnake fileSnake;
		ProjectConfig config;
		const string projectStorage = "./projects";
		const string projectConfig = "project.conf";
		
	public:
		struct ProjectStruct data;
		string getProjectDir(void){
			return this->projectStorage+"/";
		}
		string getProjectPath(string pName){
			return this->getProjectDir()+pName;
		}
		string getProjectConfigPath(string pName){
			return this->getProjectPath(pName)+"/"+this->projectConfig;
		}

		bool create(string projectName){
			this->data.name = projectName;
			if(!fileSnake.dirExists(this->projectStorage)){
				fileSnake.makeDir(this->projectStorage);
			}

			if(fileSnake.dirExists(this->projectStorage+"/"+this->data.name)){
				fprintf(stderr, "[E] Project already exists.\n");
				return false;
			}
			fileSnake.makeDir(this->projectStorage+"/"+this->data.name);
			config.setConfigFile(this->projectStorage+"/"+this->data.name+"/"+this->projectConfig);
			config.create(this->data.name);
			return true;

		}
		bool load(string projectName){
			config.load(this->getProjectConfigPath(projectName), &data);
			printf("Project Data Name : %s\n", data.name.c_str());
			return true;	
		}
}project;
