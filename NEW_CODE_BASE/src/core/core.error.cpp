#include "../../main.h"
#include "../error/error.h"
#include "./core.error.h"
		CoreError::CoreError(std::string fName, std::string msg) : CoreException(fName, msg){
			this->setClassName(this->className);
		}
		
		CoreError::CoreError(const CoreException &e, std::string fname, std::string msg) : CoreException(e, fname, msg){
			this->setFrom();
			this->setClassName(this->className);
		}
