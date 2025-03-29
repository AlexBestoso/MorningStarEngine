class CoreException : public std::exception{
        private:
		std::string className="CoreException";
		std::string functionName="";
                std::string errorMessage="";
		std::string from="";
                uint32_t _errorCode;
        public:
                CoreException(std::string msg){
			this->errorMessage = msg;
		}
		CoreException(std::string func, std::string msg){
			this->errorMessage = msg;
			this->functionName = func;
		}
                CoreException(std::string msg, uint8_t errorCode){
			this->errorMessage = msg;
			this->_errorCode = errorCode;	
		}

		CoreException(const CoreException &e, std::string func, std::string msg){
			this->errorMessage = msg;
			this->functionName = func;
		}
		
		void setFrom(void){
			this->from = className;
			this->from += "::";
			this->from += functionName;
			this->from += " - ";
			this->from += errorMessage;
			
		}
	
		void setClassName(std::string cName){
			this->className = cName;
		}

		std::string who(void){
			std::string ret = this->className;
			ret += "::";
			ret += this->functionName;
			return ret;
		}
                std::string what(void){
			return this->errorMessage;
		}
		std::string when(void){
			return this->from;
		}


                virtual void out(void){
			printf("[E] %s", this->what().c_str());
		}
                void halt(void){
			while(1){sleep(60);}
		}
		void log(void){
			printf("Error logging not built.\n");
		}
};
