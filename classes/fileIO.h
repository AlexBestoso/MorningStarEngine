class FileIO{
	private:
	int fd = -1;

	public:
	bool fileExists(string fileName){
		struct stat st;
		if(stat(fileName.c_str(), &st) < 0){
			return false;
		}
		return true;
	}
};
