class testEnt{
	private:
		Entity *soul;
		char *vertexShader;
		char *fragmentShader;
		GLuint vao;
		GLuint vbo;
		GLuint veo;


		glm::mat4 model;
		glm::vec3 color;
		float vertecies[9];
		
		bool initalized;

	public:	
		testEnt(void);
		void fillSoul(Entity *grace);
		void setVertexShader(const char *loc);
		void setFragmentShader(const char *loc);
		void compile(void);
		void init(void);
		
		void setVao(void);
		void setVbo(void);
		void setVeo(void);
		void bindVao(void);
		void bindVbo(void);
		void bindVeo(void);
		void unbindVao(void);
		void unbindVbo(void);
		void unbindVeo(void);

		void defineInput(void);

		void draw(void);
};
