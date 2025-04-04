class testEnt : public Entity{
	private:
		glm::mat4 model;
		glm::vec3 color;
		float vertecies[9];
		
		bool initalized;

	public:	
		testEnt(void);
		void init(void);

		void draw(void);
};
