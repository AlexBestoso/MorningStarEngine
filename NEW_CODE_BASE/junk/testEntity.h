class testEnt : public Entity{
	private:
		glm::mat4 model = glm::mat4(0.1f);
		glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f);
		float vertecies[3*3] = {
        		-0.5f, -0.5f, 0.0f, // left  
        		 0.5f, -0.5f, 0.0f, // right 
         		0.0f,  0.5f, 0.0f  // top   
    		};
		
		bool initalized = false;

	public:	
		testEnt(void){
		}	
		void init(void){
			if(initalized)
				return;
			this->initShader("./junk/testEntity.vetx.glsl", "./junk/tetEntity.frag.glsl");
			this->generateObjectIds(true, true, false);
			this->bindVao();
			
			this->bindVbo();
			this->storeVertexData(sizeof(vertecies), vertecies, GL_STATIC_DRAW);

			this->addShaderAttributes(0, 3, 3, 0);

			this->unbindVbo();

			this->unbindVao();
			
			initalized = true;
		}

		void draw(void){
			this->use();
			this->bindVao();
			//this->setUniform("fragColor", color);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			this->unbindVao();
			//Entity::draw();
		}
};
