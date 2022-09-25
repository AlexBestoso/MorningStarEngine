class GodsBlessing{
	private:
		
	public:
		string *textArray;
		size_t textArraySize = 0;
		float x,y,z,w,h, spacing;
		void *bitmap;

		void setText(string text){
			if(text.empty())
				return;
			this->textArraySize = text.length();
			textArray = new string[this->textArraySize];
			
			for(int i=0; i<this->textArraySize; i++)
				textArray[i] = text[i];

		}
};
