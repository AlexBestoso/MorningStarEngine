class Compiler{
	private:
	FileSnake filesnake;
	string projectName;
	string projectLocation;
	string srcLocation;
	string coreLocation;
	string templatesLocation = "./classes/core/compiler/templates/";

	bool copyFile(string src, string dst){
		size_t fileSize = filesnake.getFileSize(src);
		if(fileSize == -1){
			fprintf(stderr, "[E] Failed to get '%s' file size.\n", src.c_str());
			return false;
		}

		char *buf = new char[fileSize];
		if(!filesnake.readFile(src, buf, fileSize)){
			fprintf(stderr, "Failed to read '%s' file.\n", src.c_str());
			return false;
		}

		if(!filesnake.writeFileTrunc(dst, buf, fileSize)){
			fprintf(stderr, "[E] Failed to write '%s' file.\n", dst.c_str());
			return false;
		}
		return true;
	}
	int parseAndReplace(string targetFile, string targetTag, string replacement){
		size_t fileSize = filesnake.getFileSize(targetFile);
		if(fileSize <= 0){
			printf("Failed to get '%s' file size.\n", targetFile.c_str());
			return -1;
		}

		char *buff = new char[fileSize];
		filesnake.readFile(targetFile, buff, fileSize);
		int targetStart = -1;
		int targetEnd = -1;
		bool parsing = false;
		bool found = false;
		string grabber = "";
		for(int i=0; i<fileSize; i++){
			if(targetStart == -1){
				if(buff[i] == '['){
					targetStart = i;
				}
			}else if(!parsing && grabber == "" && (i+1) < fileSize){
				if(buff[i] == '>' && buff[i+1] == '>' && buff[i-1] == '['){
					parsing = true;
					targetEnd = -2;
					continue;
				}else{
					targetStart = -1;
				}
			}else if(parsing && targetEnd == -2){
				targetEnd = -1;
				grabber = "";
				continue;
			}else if((i+2) < fileSize && (buff[i] != '<' && buff[i+1] != '<' && buff[i+2] != ']')){
				grabber+= buff[i];
			}else{
				grabber += buff[i];
				if(grabber != targetTag){
					grabber = "";
					i+=3;
					targetStart = -1;
					targetEnd = -1;
					parsing = false;
				}else{
					targetEnd= i+3;
					found = true;
					break;
				}
			}
		}

		if(!found){
			return 0;
		}

		string newBuff = "";
		for(int i=0; i<fileSize; i++){
			if(i >= targetStart && i <= targetEnd){
				newBuff += replacement;
				i = targetEnd;
			}else{
				newBuff += buff[i];
			}
		}
		filesnake.writeFileTrunc(targetFile, (char *)newBuff.c_str(), newBuff.length());
		return 1;
	}
	void setSrcLocation(){
		srcLocation = projectLocation + "/src/";
		coreLocation = srcLocation + "core/";
	}

	bool initProjectHelloWorld(){
		string target = coreLocation+"MorningStarEngine.core.h";
		if(!filesnake.fileExists(target)){
			printf("Generating Engine Template.\n");
			if(!copyFile(templatesLocation+"MorningStarEngine.template", target))
				return false;
			while(parseAndReplace(target, "project_name", projectName)){
			}
		}

		target = srcLocation+"main.cc";
		if(!filesnake.fileExists(target)){
			printf("Generating main.cc file.\n");
			if(!copyFile(templatesLocation+"main.template", target)){
				return false;
			}
			while(parseAndReplace(target, "engine_location", coreLocation)){}	
		}
		
		target = srcLocation+"Makefile";
		if(!filesnake.fileExists(target)){
			printf("Generating Makefile.\n");
			if(!copyFile(templatesLocation+"Makefile.template", target)){
				return false;
			}
			while(parseAndReplace(target, "main_location", srcLocation)){}
			while(parseAndReplace(target, "project_name", projectName)){}
		}

		target=coreLocation+"ContextProvider.core.h";
		if(!filesnake.fileExists(target)){
			printf("Generating Context Provider.\n");
			if(!copyFile(templatesLocation+"ContextProvider.template", target)){
				return false;
			}
		}

		target=coreLocation+"keyboard.h";
		if(!filesnake.fileExists(target)){
			printf("Generating keyboard class.\n");
			if(!copyFile(templatesLocation+"keyboard.template", target)){
				return false;
			}
		}
		return true;
	}
	public:
	
	bool compile(){
		projectName = project.data.name;
		projectLocation = project.getProjectPath(projectName);
		setSrcLocation();
		filesnake.makeDir(srcLocation);
		filesnake.makeDir(coreLocation);
		printf("Compiling %s\n", projectName.c_str());
		if(!initProjectHelloWorld()){
			printf("Compile Failed.\n");
			return false;
		}
		string command = "./"+srcLocation+"Makefile";
		char *args[] = {
			(char *)"/usr/bin/make",
			(char *)"-f",
			(char *)command.c_str(),
			NULL
		};
		pid_t cpid;
		if(fork() == 0){
			execvp(args[0], args);
			exit(0);
		}else{
			cpid = wait(NULL);
		}
		printf("Compile Complete\n");
		return true;
	}

	bool run(){
		projectName = project.data.name;
		projectLocation = project.getProjectPath(projectName);
		setSrcLocation();
		string command = "./"+srcLocation+projectName;
                char *args[] = {
                        (char *)command.c_str(),
                        NULL
                };
                pid_t cpid;
                if(fork() == 0){
                        execvp(args[0], args);
                        exit(0);
                }else{  
                        cpid = wait(NULL);
                }
	}
};
