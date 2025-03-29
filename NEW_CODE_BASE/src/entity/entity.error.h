class EntityError : public CoreException{
	private:
		const char *className = "entity";
	public:
		EntityError(std::string fname, std::string msg) : CoreException(fname, msg){
			this->setClassName(className);
		}

		EntityError(const CoreException &e, std::string fname, std::string msg) : CoreException(e, fname, msg){
			this->setFrom();
			this->setClassName(className);
		}
};
