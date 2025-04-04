class CoreException : public std::exception{
        private:
		std::string className;
		std::string functionName;
                std::string errorMessage;
		std::string from;
                uint32_t _errorCode;
        public:
                CoreException(std::string msg);
		CoreException(std::string func, std::string msg);
                CoreException(std::string msg, uint8_t errorCode);
		CoreException(const CoreException &e, std::string func, std::string msg);
		void setFrom(void);
		void setClassName(std::string cName);
		std::string who(void);
                std::string what(void);
		std::string when(void);
                virtual void out(void);
                void halt(void);
		void log(void);
};
