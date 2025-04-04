class WindowCtrlError : public CoreException {
        private:
                const char *className = "WindowCtrl";
	public:
                WindowCtrlError(std::string fName, std::string msg);
		
		WindowCtrlError(const CoreException &e, std::string func, std::string msg);
};
