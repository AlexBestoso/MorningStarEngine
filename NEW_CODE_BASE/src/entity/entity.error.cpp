#include "../../main.h"
#include "../error/error.h"
#include "./entity.error.h"
		EntityError::EntityError(std::string fname, std::string msg) : CoreException(fname, msg){
			this->setClassName(className);
		}

		EntityError::EntityError(const CoreException &e, std::string fname, std::string msg) : CoreException(e, fname, msg){
			this->setFrom();
			this->setClassName(className);
		}
