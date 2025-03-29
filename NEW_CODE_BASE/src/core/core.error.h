class CoreError : public CoreException {
	private:
		const char *className = "Core";
	public:
		CoreError(std::string fName, std::string msg) : CoreException(msg){
			this->setClassName(this->className);
		}
		
		CoreError(const CoreException &e, std::string fname, std::string msg) : CoreException(e, fname, msg){
			this->setFrom();
			this->setClassName(this->className);
		}
};
