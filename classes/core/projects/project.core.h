struct ProjectStruct{
				string projectRootElement = "projectRoot";
	string author; 		string authorElement = "author";
	string description; 	string descriptionElement = "description";
	string name; 		string nameElement = "name";
	string version;		string versionElement = "version";
};
#include "./projectConfig.core.h"
class Project{
	private:
		FileSnake fileSnake;
		XmlSnake xmlSnake;
		ProjectConfig config;
		const string projectStorage = "./projects";
		const string projectConfig = "project.conf";
		string currentProjectName;
		
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

		void clearDataStruct(){
			data.author = "";
        		data.description = "";
        		data.name = "";
	        	data.version = "";
		}

		bool create(string projectName){
			this->data.name = projectName;
			currentProjectName = projectName;
			if(!fileSnake.dirExists(this->projectStorage)){
				fileSnake.makeDir(this->projectStorage);
			}

			if(fileSnake.dirExists(getProjectPath(data.name))){
				fprintf(stderr, "[E] Project already exists.\n");
				return false;
			}

			fileSnake.makeDir(getProjectPath(data.name));
			config.setConfigFile(getProjectConfigPath(data.name));

			config.create(data);
			return true;

		}

		bool update(void){
			if(currentProjectName != data.name){
				rename(getProjectPath(currentProjectName).c_str(), getProjectPath(data.name).c_str());
				currentProjectName = data.name;
			}
			config.setConfigFile(getProjectConfigPath(data.name).c_str());
			config.create(data);
		}
		bool load(string projectName){
			config.load(this->getProjectConfigPath(projectName), &data);
			currentProjectName = projectName;
			return true;	
		}

		bool remove(string projectName){
			currentProjectName = "";
			bool ret = config.remove(getProjectPath(projectName));
			clearDataStruct();
			return ret;
		}
}project;
