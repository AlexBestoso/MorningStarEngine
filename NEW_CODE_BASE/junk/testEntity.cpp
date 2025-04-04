#include "../main.h"

#include "../src/error/error.h"
#include "../src/windowCtrl/windowCtrl.h"
#include "../src/shader/shader.h"
#include "../src/entity/entity.h"

#include "./testEntity.h"

		testEnt::testEnt(void){
			model = glm::mat4(0.1f);
                	color = glm::vec3(1.0f, 0.5f, 0.2f);
                	vertecies[0] = -0.5f;
			vertecies[1] = -0.5f; 
			vertecies[2] = 0.0f; // left  
                        vertecies[3] = 0.5f; 
			vertecies[4] = -0.5f; 
			vertecies[5] = 0.0f; // right 
                        vertecies[6] = 0.0f;  
			vertecies[7] = 0.5f; 
			vertecies[8] = 0.0f;  // top   

                	initalized = false;
		}	
		void testEnt::init(void){
			if(initalized)
				return;
			this->initShader("./junk/testEntity.vetx.glsl", "./junk/tetEntity.frag.glsl");
			this->generateObjectIds(true, true, false);
			this->bindVao();
			
			this->bindVbo();
			this->storeVertexData(sizeof(vertecies), vertecies, GL_STATIC_DRAW);

			this->addShaderAttributes(0, 3, 3, (const void *)0);

			//this->unbindVbo();

			//this->unbindVao();
			
			initalized = true;
		}

		void testEnt::draw(void){
			this->use();
			this->bindVao();
			//this->setUniform("fragColor", color);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//Entity::draw();
		}
