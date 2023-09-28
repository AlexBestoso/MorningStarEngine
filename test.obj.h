class TestObject : public GraphicsObject{
	private:
		GLFWwindow* window = NULL;
		GraphicsTexture metalBoxTexture;
		GraphicsTexture metalBoxSpecMap;
		
		unsigned int transformLocation;

		glm::vec3 cubePositions[20]; // ={ glm::vec3(-1.3f, 1.0f, -1.5f) };
		int activeObjectPositions[20];
		
		/*float vertices[32] = {
                	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.5f,   0.0f, 0.0f, // bottom left
                	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
        	};*/

		/*float vertices[20] = {
                         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
                         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
                        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
                        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
                };*/

		// Coordinates |  Texuxture map|   Normalized to plane coordinates|
		float vertices[8*6*6] = {
        		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,    0.0f, 0.0f, -1.0f,
        		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
        		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
        		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    0.0f, 0.0f, -1.0f,
       	 		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
			////////
			//////
        		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
         		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
         		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
         		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
       	 		-0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
       	 		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
			///////
			//////
        		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
			/////
			/////
        		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        		 0.5f, -0.5f, -0.5f,     0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        		 0.5f, -0.5f, -0.5f,     0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        		 0.5f, -0.5f,  0.5f,     0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
			/////
			//////
        		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,    0.0f, -1.0f, 0.0f,
        		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f,    0.0f, -1.0f, 0.0f,
        		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,    0.0f, -1.0f, 0.0f,
			/////
        		/////
			-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
        		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
        		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        		-0.5f,  0.5f,  0.5f,     0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
			///
			 
    		};

		unsigned int drawIndecies[6] = {
                	0, 1, 3,
                	1, 2, 3
        	};

	public:
		glm::vec3 lightPos;
		void setWindow(GLFWwindow* window){
			this->window = window;
		}
		bool create(void){
			for(int i=0; i<20; i++)
					activeObjectPositions[i] = -1;
			if(!this->addVertexShader("./glsl/vertexShader.glsl", 0)){
				printf("Failed to compile vertex shader.\n");
				return false;
			}

			if(!this->addFragmentShader("./glsl/fragmentShader.glsl", 1)){
				printf("Failed to compile fragment shader\n");
				return false;
			}

			if(!this->linkShaders()){
				printf("Faild to link shader.\n");
				return false;
			}

			metalBoxTexture.add2DParameter(0, GL_TEXTURE_WRAP_S, GL_REPEAT);
        		metalBoxTexture.add2DParameter(1, GL_TEXTURE_WRAP_T, GL_REPEAT);
        		metalBoxTexture.add2DParameter(2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        		metalBoxTexture.add2DParameter(3, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        		metalBoxTexture.setTextureUnit(0);
        		if(!metalBoxTexture.loadTexture2D("./Cat_bump.jpg")){
                		printf("Failed to import trippy texture.\n");
				return false;
        		}

        		metalBoxSpecMap.add2DParameter(0, GL_TEXTURE_WRAP_S, GL_REPEAT);
        		metalBoxSpecMap.add2DParameter(1, GL_TEXTURE_WRAP_T, GL_REPEAT);
        		metalBoxSpecMap.add2DParameter(2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        		metalBoxSpecMap.add2DParameter(3, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        		metalBoxSpecMap.setTextureUnit(1);
        		if(!metalBoxSpecMap.loadTexture2D("./Cat_diffuse.jpg")){
                		printf("Failed to import container texture.\n");
				return false;
        		}

			this->generateObjectIds(true, true, false);
			this->bindVao();
			this->bindVbo();
			if(!this->objImporter.import("./12221_Cat_v1_l3.obj")){
				printf("Failed to import Cube object.\n");
				return false;
			}
			this->storeVertexData(sizeof(float)*this->objImporter.glObjBufferSize, this->objImporter.glObjBuffer, GL_STATIC_DRAW);
			//this->storeVertexData(sizeof(vertices), vertices, GL_STATIC_DRAW);
			//this->bindEbo();
			//this->setElementArrayData(sizeof(drawIndecies), drawIndecies, GL_STATIC_DRAW);

			this->setAttributePointer(0, 3, 8, (void *)0);
       	 		this->enableArrayAttribute(0);
        		this->setAttributePointer(1, 2, 8, (void *)(3*sizeof(float)));
        		this->enableArrayAttribute(1);
        		this->setAttributePointer(2, 3, 8, (void *)(5*sizeof(float)));
        		this->enableArrayAttribute(2);

			this->unbindVbo();
			this->unbindVao();

			this->use();

			this->material.ambient = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
                        this->material.specular = glm::vec3(0.5f, 0.5f, 0.3f);
                        this->material.shininess = 32.0f;


                        this->light.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
			//this->light.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
			//this->light.direction = glm::vec3(-8.0f, -8.0f, -8.0f);
                        this->light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
                        this->light.specular = glm::vec3(1.0f, 1.0f, 1.0f); 
			this->light.constant = 1.0f;
			this->light.linear = 0.09f;
			this->light.quadratic = 0.032f;
			// Flashlight configurations
			this->light.position = camera.cameraPosition;
			this->light.direction = camera.cameraFront;
			this->light.cutOff = glm::cos(glm::radians(12.5f));

        		setUniform("material.diffuseMap", 0);
			setUniform("material.specularMap", 1);

			addInstance(glm::vec3(0, 0, 0), 0);
			addInstance(glm::vec3(1.0, 1.0, 1.0), 1);
			addInstance(glm::vec3(-0.4, -1.0, -0.4), 2);
			addInstance(glm::vec3(0.6, 0.6, 0.5), 3);
			addInstance(glm::vec3(-5.0f, 0, -5.0), 4);

			return true;
		}


		bool removeInstance(int id){
			 if(id < 0 || id >= 20)
                                return false;
                        activeObjectPositions[id] = -1;
			return true;
		}
		bool addInstance(glm::vec3 newPos, int id){
			if(id < 0 || id >= 20)	
				return false;
			cubePositions[id] = newPos;
			activeObjectPositions[id] = id;
			return true;
		}

		float deltaTime = 0.0f; 
		float lastFrame = 0.0f; 
		void userInput(){
			camera.fpsControls();
		}
		
		void draw(void){
		//	this->userInput();
		//	this->containerTexture.bind2D();
                //	this->trippyTexture.bind2D();

                /*	glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                	transform = glm::translate(transform, glm::vec3(0.5f+modify_x, -0.5f+modify_y, 0.0f));
			transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
			if(modify_x == 0 && modify_y == 0)
	                	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	                else
				transform = glm::rotate(transform, ((float)glfwGetTime()*-1), glm::vec3(0.0f, 0.0f, 1.0f));
*/
			this->metalBoxTexture.bind2D();
			this->metalBoxSpecMap.bind2D();
                	this->bindVao();
                	this->use();
			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f));
                        glm::mat4 view = glm::mat4(1.0f);
                        glm::mat4 projection = glm::mat4(1.0f);

			this->setUniform("material.ambient", material.ambient);
			this->setUniform("material.diffuse", material.diffuse);
			this->setUniform("material.specular", material.specular);
			this->setUniform("material.shininess", material.shininess);

			
			this->setUniform("light.ambient", light.ambient);
			this->setUniform("light.diffuse", light.diffuse);
			this->setUniform("light.specular", light.specular);
			//this->setUniform("light.direction", light.direction);

			//Flashling configs
			this->setUniform("light.position", camera.cameraPosition);
			this->setUniform("light.direction", camera.cameraFront);
			this->setUniform("light.cuttOff", glm::cos(glm::radians(12.5f)));

			this->setUniform("light.constant", light.constant);
			this->setUniform("light.linear", light.linear);
			this->setUniform("light.quadratic", light.quadratic);
				
			this->setUniform("useTexture", 1);
			this->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			this->setUniform("lightPos", lightPos);
			this->setUniform("viewPos", camera.getPos());

		//	float radius = 10.0f;
		//	float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		//	float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		//	camera.setPos(glm::vec3(camX, 0.0f, camZ));
			
			//view = camera.focus();
			view = camera.getView();
			unsigned int viewLoc = this->getUniformLoc("view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);



			//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.8f));
			
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
			unsigned int projectionLoc = this->getUniformLoc("projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);


			bool hadInstance = false;
			for(int i=0; i<20; i++){
				break;
				if(activeObjectPositions[i] != -1){
					hadInstance = true;
					glm::mat4 modelX = glm::mat4(1.0f);
					modelX = glm::translate(modelX, cubePositions[i]);
                                	float angle = 20.0f * i;
                                	modelX = glm::rotate(modelX, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
					this->setUniform("model", modelX);

                                	//glDrawArrays(GL_TRIANGLES, 0, 36);
					//GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY
                                	glDrawArrays(GL_TRIANGLE_FAN, 0, 24);
				}
			}
			if(!hadInstance){
				//unsigned int modelLoc = this->getUniformLoc("model");
                                //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLES, 0, objImporter.objCount);
                                //glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::rotate(model, (float)glfwGetTime()*glm::radians(-50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
				this->setUniform("model", model);

			}
		//	model = glm::rotate(model, (float)glfwGetTime()*glm::radians(-50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}
};
