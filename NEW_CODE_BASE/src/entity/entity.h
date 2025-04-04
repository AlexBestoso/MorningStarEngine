class Entity{
	private:
		GLenum mode;
		int drawStart;
		int indexCount;

		Shader shader;

		int cubeSize;
		int mass;
		double birthday;
		
		bool attributesDefined;
		
	public:
	
		unsigned int elementBufferObject;
                unsigned int vertexBufferObject;
                unsigned int vertexArrayObject;
	
		Entity(void);		

		void pointMode(void);
		void triangleMode(void);
		void lineMode(void);
		void setDrawStart(int i);
		void setIndexCount(int i);
		void use(void);
		void addShaderAttributes(unsigned int i, int size, unsigned int stride, const void *offset);
		void initShader(std::string vtxShader, std::string fragShader);
		void generateObjectIds(bool arrayObj, bool vertBuff, bool eleObj);
		virtual void draw(void);
                void bindVao(void);
		void unbindVao(void);
                void unbindVbo(void);
                void bindVbo(void);
                void bindEbo(void);
		void simpActive(void);
		void simpDeactive(void);
                void storeVertexData(GLsizeiptr size, const void * data, GLenum drawMode);
		void storeVertexData(GLsizeiptr size, const void * data);
                void setElementArrayData(GLsizeiptr size, const GLvoid *indecies, GLenum drawMode);
		void destroy(void);
		void replaceBufferData(GLintptr offset, GLsizeiptr size, const void * data);
		int getUniformLoc(const char *name);
                void setUniform(const char *name, int val);
                void setUniform(const char *name, float val);
                void setUniform(const char *name, glm::mat4 val);
                void setUniform(const char *name, glm::vec3 val);
                void setUniform(const char *name, glm::vec2 val);
};
