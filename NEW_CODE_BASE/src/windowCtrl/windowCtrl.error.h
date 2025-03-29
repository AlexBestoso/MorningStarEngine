class WindowCtrlError : public CoreException {
        private:
                const char *className = "WindowCtrl";
	public:
                WindowCtrlError(std::string fName, std::string msg) : CoreException(msg){
			this->setClassName(className);
                }
		
		WindowCtrlError(const CoreException &e, std::string func, std::string msg) : CoreException(e, func, msg){
			this->setFrom();
			this->setClassName(className);
		}
};
