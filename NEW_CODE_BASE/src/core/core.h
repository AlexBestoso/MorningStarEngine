class Core{
	private:
		unsigned int screenWidth = 700;
		unsigned int screenHeight = 700;
		bool alive = true;
		float soulColor[4] = {0.0, 0.2, 0.2, 1.0};
		double time = 0;
		testEnt test;
		bool dbg = false;
	public:
		Core(void);
		void init(void);
		bool isAlive(WindowCtrl window);
		void process();
		void pulse(WindowCtrl window);
};
