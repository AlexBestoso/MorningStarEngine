#include "../../main.h"
#include "../error/error.h"
#include "./windowCtrl.error.h"
                WindowCtrlError::WindowCtrlError(std::string fName, std::string msg) : CoreException(fName, msg){
			this->setClassName(className);
                }
		
		WindowCtrlError::WindowCtrlError(const CoreException &e, std::string func, std::string msg) : CoreException(e, func, msg){
			this->setFrom();
			this->setClassName(className);
		}
