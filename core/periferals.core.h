class Periferals{
	private:

	public:
		Periferals(){}
		float getX(float x){
        	        if(x >=0 && x < keyboard.width/2){
        	                x = -1 + (x*((9999999/(keyboard.width/2))*0.0000001));
        	        }else if(x == keyboard.width/2){
        	                x = 0;
        	        }else if(x > keyboard.width/2 && x < keyboard.width){
        	                x = -1 + (x*((9999999/(keyboard.width/2))*0.0000001));
        	        }else if(x == keyboard.width){
        	                x = 1;
        	        }
        	        return x;
        	}

        	float getY(float y){
        	        if(y >=0 && y < keyboard.height/2){
        	                y = -1 + (y*((9999999/(keyboard.height/2))*0.0000001));
        	        }else if(y == keyboard.height/2){
        	                y = 0;
        	        }else if(y > keyboard.height/2 && y < keyboard.height){
        	                y = -1 + (y*((9999999/(keyboard.height/2))*0.0000001));
        	        }else if(y == keyboard.height){
        	                y = 1;
        	        }
        	        return y;
        	}
		bool rightClick(int button, int state){
			if(button != 2 || state != 1){
				return false;
			}
			return true;	
		}
		bool leftClick(int button, int state){
			if(button != 0 || state != 1)
				return false;
			return true;
		}
};
