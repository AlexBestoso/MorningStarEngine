class Shader{
	private:
		unsigned int vertexHandle;
		unsigned int fragmentHandle;
		unsigned int geometryHandle;

		char fragBuffer[10000];
		char vertBuffer[10000];
		char geometryBuffer[10000];
	public:
		unsigned int programHandle;
		Shader(void);
		~Shader();
		void setVertexShader(const char *fname);
		void setFragmentShader(const char *fname);
		void setGeometryShader(const char *fname);
		void link(void);
		void use(void);
                void deleteProgram(void);
		void getUniform(const char *varName, int *ret);
                void setUniform(const char *varName, int val);
                void setUniform(const char *varName, float val);
                void setUniform(const char *varName, glm::mat4 val);
                void setUniform(const char *varName, glm::vec3 val);
                void setUniform(const char *varName, glm::vec2 val);
};
