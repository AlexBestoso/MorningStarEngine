class CoreError : public CoreException {
	private:
		const char *className = "Core";
	public:
		CoreError(std::string fName, std::string msg);
		CoreError(const CoreException &e, std::string fname, std::string msg);
};
