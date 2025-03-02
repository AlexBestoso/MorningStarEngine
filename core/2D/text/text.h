#include <map>
struct MorningCharacter{
	GLuint textureId;  	//ID handle of glyph texture;
	glm::ivec2 size;	//Size of glyph
	glm::ivec2 bearing;	//Offset from baseline to left/top of glyph
	GLuint advance;		//Offset to advance to next glyph.
};

const GLuint WIDTH = 800, HEIGHT = 600;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    FT_Pos Advance;    // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
GLuint VAO, VBO;

class MorningText : public GraphicsObject{
	private:
		FT_Library freetypeLib;
		FT_Face freetypeFace;
		std::string selectedFont = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf";
		const char *defaultFont = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf";
		std::map<GLchar, MorningCharacter> characters;
		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

		std::string renderText = "";
		GLfloat x = 0.0f;
		GLfloat y = 0.0f;
		GLfloat scale = 0;
		glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

	public:

		void setText(const char *str){
			this->renderText = str;
		}

		void setPos(float x, float y){
			this->x = x;
			this->y = y;
		}

		void setScale(float s){
			this->scale = s;
		}

		void setColor(float r, float g, float b){
			this->color = glm::vec3(r, g, b);
		}
			
		MorningText(std::string selectedFont){
			this->selectedFont = selectedFont;
			this->init();

			if(FT_New_Face(freetypeLib, selectedFont.c_str(), 0, &this->freetypeFace))
				printf("[E] Failed to initalize default font '%s'\n", selectedFont.c_str());
		}

		MorningText(void){
		//	this->init();
		}
		
		bool init(){
			if(FT_Init_FreeType(&this->freetypeLib)){
				printf("[E] Failed to initalize FreeType.\n");	
				return false;
			}
			return true;
		}

		bool useDefaultFont(void){
			return this->setFont(this->defaultFont);
		}		

		bool setFont(std::string selectedFont){
			if(FT_New_Face(freetypeLib, selectedFont.c_str(), 0, &this->freetypeFace)){
				printf("[E] Failed to initalize default font '%s'\n", selectedFont.c_str());
				return false;
			}
			return true;
		}
		
		void setSize(int width, int height){
			FT_Set_Pixel_Sizes(this->freetypeFace, width, height);
		}

		int loadChar(char ch){
			if(int err = FT_Load_Char(this->freetypeFace, ch, FT_LOAD_RENDER))
				return err;
			return 0;
		}

		void freeFace(void){
			FT_Done_Face(this->freetypeFace);
		}
	
		void freeLib(void){
			FT_Done_FreeType(this->freetypeLib);
		}

		void createCharacterMap(void){
			GraphicsTexture *texture = this->getTexture();	
    			// Disable byte-alignment restriction
    			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

    			// Load first 128 characters of ASCII set
    			for (GLubyte c = 0; c < 128; c++){
        			// Load character glyph 
        			if (loadChar(c)){
        		    		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        		    		continue;
        			}
        			// Generate texture
		
        			//GLuint texture;
        			//glGenTextures(1, &texture);
				texture->genTexture();
//      		  	glBindTexture(GL_TEXTURE_2D, texture);
				texture->bind2D();
        			glTexImage2D(
        	    			GL_TEXTURE_2D,
        	    			0,
        	    			GL_RED,
        	    			this->freetypeFace->glyph->bitmap.width,
        	    			this->freetypeFace->glyph->bitmap.rows,
        	    			0,
        	    			GL_RED,
        	    			GL_UNSIGNED_BYTE,
        	    			this->freetypeFace->glyph->bitmap.buffer
        			);
        			
				// Set texture options
        			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        			// Now store character for later use
        			Character character = {
        	    			texture->getTexture(),
        	    			glm::ivec2(this->freetypeFace->glyph->bitmap.width, this->freetypeFace->glyph->bitmap.rows),
        	    			glm::ivec2(this->freetypeFace->glyph->bitmap_left, this->freetypeFace->glyph->bitmap_top),
        	    			this->freetypeFace->glyph->advance.x
        			};
        			Characters.insert(std::pair<GLchar, Character>(c, character));
    			}
    			texture->unbind2D();
    			// Destroy FreeType once we're finished
    			this->freeFace();
    			this->freeLib();	
		}

		bool create(){
			if(!this->addVertexShader("./core/2D/text/textVertex.glsl", 0)){
                                printf("Failed to compile vertex shader .\n");
                                return false;
                        }

                        if(!this->addFragmentShader("./core/2D/text/textFragment.glsl", 1)){
                                printf("Failed to compile fragment shader \n");
                                return false;
                        }

                        if(!this->linkShaders()){
                                printf("Faild to link 2D Menu shaders.\n");
                                return false;
                        }
			projection = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));
			this->use();

			this->setUniform("projection", projection);

    			// FreeType
			this->init();

    			// Load font as face
			this->setFont(selectedFont.c_str());

    			// Set size to load glyphs as
			this->setSize(0, 48);

			this->createCharacterMap();
    
    // Configure VAO/VBO for texture quads
	
			this->generateObjectIds(true, true, false);
                        this->bindVao();
                     	this->bindVbo();

    			this->storeVertexData(sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    			this->enableArrayAttribute(0);
    			this->setAttributePointer(0, 4, 4, 0);
			this->unbindVbo();
			this->unbindVao();

			return true;
		}


		void draw(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color){
			GraphicsTexture *texture = this->getTexture();
                        this->use();
			setUniform("textColor", color);
			texture->setTextureUnit(0);
			texture->activate();

			this->bindVao();

    			// Iterate through all characters
    			std::string::const_iterator c;
    			for (c = text.begin(); c != text.end(); c++) {
        			Character ch = Characters[*c];

        			GLfloat xpos = x + ch.Bearing.x * scale;
        			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        			GLfloat w = ch.Size.x * scale;
        			GLfloat h = ch.Size.y * scale;
        			// Update VBO for each character
        			GLfloat vertices[6][4] = {
            				{ xpos,     ypos + h,   0.0, 0.0 },            
            				{ xpos,     ypos,       0.0, 1.0 },
            				{ xpos + w, ypos,       1.0, 1.0 },
		
		            		{ xpos,     ypos + h,   0.0, 0.0 },
		            		{ xpos + w, ypos,       1.0, 1.0 },
		            		{ xpos + w, ypos + h,   1.0, 0.0 }           
		        	};
	        		// Render glyph texture over quad
	        		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
	        		// Update content of VBO memory
				this->bindVbo();
	        		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
				this->unbindVbo();
	        		// Render quad
	        		glDrawArrays(GL_TRIANGLES, 0, 6);
	        		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
	        		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	    		}
			this->unbindVao();
			texture->unbind2D();
		}
		
		void destroy(){
                        GraphicsObject::destroy();
                }
};
