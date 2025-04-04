#include "../../main.h"
#include "./error.h"
		CoreException::CoreException(std::string msg){
			this->className="CoreException";
			this->errorMessage = msg;
			this->_errorCode = 0;
		}
		CoreException::CoreException(std::string func, std::string msg){
			this->className="CoreException";
			this->errorMessage = msg;
			this->functionName = func;
			this->_errorCode = 0;
		}
                CoreException::CoreException(std::string msg, uint8_t errorCode){
			this->className="CoreException";
			this->errorMessage = msg;
			this->_errorCode = errorCode;	
		}

		CoreException::CoreException(const CoreException &, std::string func, std::string msg){

			this->_errorCode = 0;
			this->className="CoreException";
			this->errorMessage = msg;
			this->functionName = func;
		}
		
		void CoreException::setFrom(void){
			this->from = className;
			this->from += "::";
			this->from += functionName;
			this->from += " - ";
			this->from += errorMessage;
			
		}
	
		void CoreException::setClassName(std::string cName){
			this->className = cName;
		}

		std::string CoreException::who(void){
			std::string ret = this->className;
			ret += "::";
			ret += this->functionName;
			return ret;
		}
                std::string CoreException::what(void){
			return this->errorMessage;
		}
		std::string CoreException::when(void){
			return this->from;
		}


                void CoreException::out(void){
			printf("[E] %s", this->what().c_str());
		}
                void CoreException::halt(void){
			while(1){sleep(60);}
		}
		void CoreException::log(void){
			printf("Error logging not built.\n");
		}
