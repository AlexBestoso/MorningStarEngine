#include "../../main.h"
#include "../error/error.h"
#include "./shader.error.h"
		ShaderError::ShaderError(std::string fName, std::string msg) : CoreException(fName, msg){
                        this->setClassName(className);
                }

                ShaderError::ShaderError(const CoreException &e, std::string func, std::string msg) : CoreException(e, func, msg){
                        this->setFrom();
                        this->setClassName(className);
                }
