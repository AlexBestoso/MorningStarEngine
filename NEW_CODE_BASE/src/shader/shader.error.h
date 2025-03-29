class ShaderError : public CoreException{
	private:
		const char *className = "Shader";

	public:
		ShaderError(std::string fName, std::string msg) : CoreException(msg){
                        this->setClassName(className);
                }

                ShaderError(const CoreException &e, std::string func, std::string msg) : CoreException(e, func, msg){
                        this->setFrom();
                        this->setClassName(className);
                }
};
