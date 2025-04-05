#include "../main.h"

#include "../src/error/error.h"
#include "../src/entity/entity.h"

#include "./testEntity.h"

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
	this->soul->pushInputStatic(this->vertecies, sizeof(this->vertecies));
	this->soul->defineInput(0, 3, 3, (const void *)0);
}

testEnt::testEnt(void){
	model = glm::mat4(0.1f);
	color = glm::vec3(1.0f, 0.5f, 0.2f);
	vertecies[0] = -0.5f;
	vertecies[1] = -0.5f; 
	vertecies[2] = 0.5f; // left  
	vertecies[3] = 0.5f; 
	vertecies[4] = -0.5f; 
	vertecies[5] = 0.5f; // right 
	vertecies[6] = 0.0f;  
	vertecies[7] = 0.5f; 
	vertecies[8] = 0.5f;  // top   
	initalized = false;
	soul = NULL;
	vertexShader = NULL;
	fragmentShader = NULL;
}	
		void testEnt::init(void){
		/*	if(initalized)
				return;
			this->initShader("./junk/testEntity.vetx.glsl", "./junk/tetEntity.frag.glsl");
			this->generateObjectIds(true, true, false);
			this->bindVao();
			
			this->bindVbo();
			this->storeVertexData(sizeof(vertecies), vertecies, GL_STATIC_DRAW);

			this->addShaderAttributes(0, 3, 3, (const void *)0);

			//this->unbindVbo();

			//this->unbindVao();
			
			initalized = true;*/
		}

		void testEnt::draw(void){
			if(this->soul == NULL){
                		printf("Entity is soulless.\n");
                		return;
        		}
			this->soul->use();
			this->bindVao();
			this->soul->drawTriangle(0, 3);
			
		}
