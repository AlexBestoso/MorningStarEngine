class testEnt : public Entity{
	private:
		glm::mat4 model = glm::mat4(0.1f);
		float vertecies[3*3] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    		};

	public:	
		testEnt(void){
		}	
		void init(void){
			this->initShader("./junk/testEntity.vetx.glsl", "./junk/tetEntity.frag.glsl");
			this->generateObjectIds(true, true, false);
			this->bindVao();
			
			this->bindVbo();
			printf("pushing : ");
			for(int i=0; i<3*3; i++){
				printf("%f ", vertecies[i]);
			}
			printf("\n");
			this->storeVertexData(sizeof(vertecies), vertecies);

			this->addShaderAttributes(0, 3, 3, 0);

			this->unbindVbo();

			this->unbindVao();
		}

		void draw(void){
			this->bindVao();
			this->use();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//Entity::draw();
		}
};
