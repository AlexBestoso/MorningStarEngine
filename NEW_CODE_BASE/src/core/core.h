class Core{
	private:
		unsigned int screenWidth;
		unsigned int screenHeight;
		bool alive;
		float soulColor[4];
		double time;
		testEnt test;
		bool dbg;
		int a, b, c;
	public:
		Core(void);
		void init(void);
		bool isAlive(WindowCtrl window);
		void process();
		void pulse(WindowCtrl window);
};
