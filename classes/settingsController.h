class SettingsController{
	private:
		string configStorageLocation = "/tmp/mty_storage";
		string configFile = ".mty_config";
		string configChallengeFile = ".mty_challenge";
		string challengeText = "This is a magical test to determine how many bananas you can eat within one hour.";
		char key[16];
		char iv[16];
		bool installed = false;
	public:
		string getDataStorageLocation(){
			return this->configStorageLocation;
		}
		SettingsController(){
			const char* home = getenv("HOME");
			string home_str(home ? home : "");
			if(home_str.empty()){
				fprintf(stderr, "[E] No $HOME environment variable found. Creating temp storage at /tmp/mty_storage.\n");
				this->configStorageLocation = "/tmp/mty_storage";
			}else{
				this->configStorageLocation = home_str + "/mty_storage";
			}

			FileIO fio;
			bool challenge = fio.fileExists(this->configStorageLocation+"/"+this->configChallengeFile);
			bool config = fio.fileExists(this->configStorageLocation+"/"+this->configFile);

			if(challenge && config)
				this->installed = true;
			else
				this->installed = false;
		}

		bool isInstalled(){
			return this->installed;
		}	
}settings;
