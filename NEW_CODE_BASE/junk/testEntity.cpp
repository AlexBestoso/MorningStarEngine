#include "../main.h"

#include "../src/error/error.h"
#include "../src/entity/entity.h"

#include "./testEntity.h"

extern int global_w;
extern int global_h;

void testEnt::setVertex(float * vtx, GLsizeiptr vtxS){
	this->vertecies = (float *)&vtx;
	this->verteciesCount = vtxS;
}
void testEnt::fillSoul(Entity *grace){
	this->soul = grace;
}

void testEnt::setVertexShader(const char *loc){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}

	this->soul->setVertexShader(loc);
}
void testEnt::setFragmentShader(const char *loc){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}

	this->soul->setFragmentShader(loc);
}

void testEnt::setGeometryShader(const char *loc){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}

	printf("Setting geometry shader...\n");
	this->soul->setGeometryShader(loc);
}


void testEnt::compile(void){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}
	this->soul->link();
}

void testEnt::setVao(void){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}

	this->soul->generateVao(1, &this->vao);
}
void testEnt::setVbo(void){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}

	this->soul->generateVbo(1, &this->vbo);
}
void testEnt::setVeo(void){
	if(this->soul == NULL){
		printf("Entity is soulless.\n");
		return;
	}

	this->soul->generateVbo(1, &this->veo);
}

void testEnt::bindVao(void){
        if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }

        this->soul->bindVao(this->vao);
}
void testEnt::bindVbo(void){
        if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }

        this->soul->bindVbo(this->vbo);
}
void testEnt::bindVeo(void){
        if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }

        this->soul->bindVeo(this->veo);
}

void testEnt::unbindVao(void){
        if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }

        this->soul->unbindVao();
}
void testEnt::unbindVbo(void){
        if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }

        this->soul->unbindVbo();
}
void testEnt::unbindVeo(void){
        if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }

        this->soul->unbindVeo();
}

void testEnt::defineInput(void){
	if(this->soul == NULL){
                printf("Entity is soulless.\n");
                return;
        }
	this->activate();
	this->bindVbo();
	this->activate();
	this->soul->pushInputDynamic((void *)this->vertecies, verteciesCount);
	this->soul->defineInput(0, 1, 0, (const void *)0);
}

void testEnt::activate(void){
	this->soul->use();
}

testEnt::testEnt(void){
	model = glm::mat4(0.1f);
	color = glm::vec3(1.0f, 0.5f, 0.2f);
	initalized = false;
	soul = NULL;
	vertecies = NULL;
	vertexShader = NULL;
	fragmentShader = NULL;
}	
		void testEnt::init(void){
			
		}

		void testEnt::draw(void){
			if(this->soul == NULL){
                		printf("Entity is soulless.\n");
                		return;
        		}
			this->soul->use();
			this->bindVao();
			//glViewport(20, 20, global_w, global_h);
			this->soul->drawPoint(0, 4);
			
		}
