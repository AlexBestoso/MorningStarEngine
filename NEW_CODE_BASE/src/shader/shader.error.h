class ShaderError : public CoreException{
	private:
		const char *className = "Shader";

	public:
		ShaderError(std::string fName, std::string msg);
                ShaderError(const CoreException &e, std::string func, std::string msg);
};
