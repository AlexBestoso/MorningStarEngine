class EntityError : public CoreException{
	private:
		const char *className = "entity";
	public:
		EntityError(std::string fname, std::string msg); 
		EntityError(const CoreException &e, std::string fname, std::string msg);
};
