#define TRIANGLE_UNDEFINED -1
#define TRIANGLE_SCALENE 0
#define TRIANGLE_ISOSCELES 1
#define TRIANGLE_EQUILATERAL 2
typedef struct Line2D{
	glm::vec2 vertecies[2];
	float y = 0; // height
	float m = 0; // slope
	float x = 0; // width
	float b = 0; // y intercept
	float distance = 0;
}line2_t;

typedef struct Line3D{
        glm::vec3 vertecies[2];
	
	// x perspective
	line2_t perspective_x_z;
	line2_t perspective_x_y;
	// y perspective
	line2_t perspective_y_z;
	line2_t perspective_y_x;
	// z perspective
	line2_t perspective_z_x;
	line2_t perspective_z_y;

	line2_t perspective_xy; // x=x, y=y
	line2_t perspective_yz;	// y=x z=y
	line2_t perspective_xz; //x=x z=y
	glm::vec3 direction;
	glm::vec3 start;
	glm::vec3 end;
	float distance = 0;
}line3_t;

typedef struct Triangle2D{
	glm::vec2 midpoint_a;
	glm::vec2 midpoint_b;
	glm::vec2 midpoint_c;
	float direction;

	glm::vec2 center;
	
	line2_t line_a;
	line2_t line_b;
	line2_t line_c;
	
	float area = 0;
	float perimiter = 0;
	float hypotenuse = 0;
	float angle_a_deg = 0;
	float angle_a_rad = 0;
	float angle_b_deg = 0;
	float angle_b_rad = 0;
	float angle_c_deg = 0;
	float angle_c_rad = 0;

	int type = TRIANGLE_UNDEFINED;
}triangle2_t;

typedef struct Triangle3D{
	glm::vec3 vertecies[3];
	glm::vec3 normal;
	glm::vec3 midpoint_a;
	glm::vec3 midpoint_b;
	glm::vec3 midpoint_c;
	line3_t line_a;
	line3_t line_b;
	line3_t line_c;

	triangle2_t perspective_x_z;
        triangle2_t perspective_x_y;
        triangle2_t perspective_y_z;
        triangle2_t perspective_y_x;
        triangle2_t perspective_z_x;
        triangle2_t perspective_z_y;

	float area = 0;
	float angle_a_deg = 0;
        float angle_a_rad = 0;
        float angle_b_deg = 0;
        float angle_b_rad = 0;
        float angle_c_deg = 0;
        float angle_c_rad = 0;
}triangle3_t;
class GraphicsGeometry{
	private:
		bool error = false;
		line2_t create2dLine(glm::vec2 a, glm::vec2 b){
			line2_t ret;
			ret.vertecies[0] = a;
			ret.vertecies[1] = b;
			ret.m = this->slope(a, b);
			ret.x = b.x - a.x;
			ret.y = b.y - a.y;
			ret.b = ret.y-(ret.m*ret.x);
			ret.distance = distance(a, b);
			if(ret.y != ret.m*ret.x+ret.b){
				error = true;
			}else{
				error = false;
			}
			return ret;
		}



		triangle2_t create2dTriangle(line2_t a, line2_t b, line2_t c){
			triangle2_t ret;
			ret.line_a = a;
			ret.line_b = b;
			ret.line_c = c;

			ret.perimiter = a.distance + b.distance + c.distance;
                        ret.midpoint_a = (a.vertecies[0] + a.vertecies[1])/(float)2.0;
                        ret.midpoint_b = (b.vertecies[0] + b.vertecies[1])/(float)2.0;
                        ret.midpoint_c = (c.vertecies[0] + c.vertecies[1])/(float)2.0;
			ret.hypotenuse = -0;

			ret.direction = ret.line_a.m + ret.line_b.m + ret.line_c.m;

			if(a.distance == b.distance && a.distance == c.distance ){
				ret.hypotenuse = -0;
				ret.type = TRIANGLE_EQUILATERAL;
				ret.angle_a_deg = 60.0;
				ret.angle_b_deg = 60.0;
				ret.angle_c_deg = 60.0;
				ret.angle_a_rad = glm::radians(60.0);
				ret.angle_b_rad = glm::radians(60.0);
				ret.angle_c_rad = glm::radians(60.0);
				ret.area = (sqrt(3)/4)*pow(ret.line_a.distance, 2);
			}else if(a.distance == b.distance && a.distance != c.distance){
				ret.type = TRIANGLE_ISOSCELES;
				ret.hypotenuse = c.distance > a.distance ? c.distance : -0; 
				float base = c.distance;
				float height = (float)sqrt(pow(a.distance,2) - pow(base, 2)/4);
				ret.angle_a_rad = asin(height/a.distance);
				ret.angle_a_deg = glm::degrees(ret.angle_a_rad);
				ret.angle_c_rad = asin(height/b.distance);
				ret.angle_c_deg = glm::degrees(ret.angle_c_rad);
				ret.angle_b_deg = 180 - (ret.angle_a_deg+ret.angle_c_deg);
				ret.angle_b_rad = glm::radians(ret.angle_b_deg);
				ret.area = 0.5 * base * height;
			}else if(b.distance == c.distance && b.distance != a.distance){
				ret.type = TRIANGLE_ISOSCELES;
				ret.hypotenuse = a.distance > c.distance ? a.distance : -0;
				float base = a.distance;
				float height = (float)sqrt(pow(b.distance,2) - pow(base, 2)/4);
				ret.angle_a_rad = asin(height/c.distance);
                                ret.angle_a_deg = glm::degrees(ret.angle_a_rad);
                                ret.angle_b_rad = asin(height/b.distance);
                                ret.angle_b_deg = glm::degrees(ret.angle_c_rad);
                                ret.angle_c_deg = 180 - (ret.angle_a_deg+ret.angle_b_deg);
                                ret.angle_c_rad = glm::radians(ret.angle_c_deg);
				ret.area = 0.5 * base * height;

			}else if(a.distance == c.distance && c.distance != b.distance){
				ret.type = TRIANGLE_ISOSCELES;
				ret.hypotenuse = b.distance > c.distance ? b.distance : -0; 
				float base = b.distance;
				float height = (float)sqrt(pow(a.distance,2) - pow(base, 2)/4);
				ret.angle_b_rad = asin(height/a.distance);
                                ret.angle_b_deg = glm::degrees(ret.angle_a_rad);
                                ret.angle_c_rad = asin(height/c.distance);
                                ret.angle_c_deg = glm::degrees(ret.angle_c_rad);
                                ret.angle_a_deg = 180 - (ret.angle_b_deg+ret.angle_c_deg);
                                ret.angle_a_rad = glm::radians(ret.angle_a_deg);
				ret.area = 0.5 * base * height;
			}else if(a.distance > b.distance && a.distance > c.distance){
				ret.type = TRIANGLE_SCALENE;
				ret.hypotenuse = a.distance;
				float semi = ret.perimiter/2;
				float height = 2/ret.hypotenuse*sqrt(semi*(semi-a.distance)*(semi-b.distance)*(semi-c.distance));
				ret.angle_a_rad = asin(height/c.distance);
				ret.angle_a_deg = glm::degrees(ret.angle_a_rad);
				ret.angle_b_rad = asin(height/b.distance);
				ret.angle_b_deg = glm::degrees(ret.angle_b_rad);
				ret.angle_c_deg = 180 - (ret.angle_a_deg + ret.angle_b_deg);
				ret.angle_c_rad = glm::radians(ret.angle_c_deg);
				ret.area = 0.5 * ret.hypotenuse * height;

			}else if(b.distance > a.distance && b.distance > c.distance){
				ret.type = TRIANGLE_SCALENE;
				ret.hypotenuse = b.distance;
				float semi = ret.perimiter/2;
				float height = 2/ret.hypotenuse*sqrt(semi*(semi-a.distance)*(semi-b.distance)*(semi-c.distance));
				ret.angle_b_rad = asin(height/a.distance);
                                ret.angle_b_deg = glm::degrees(ret.angle_b_rad);
                                ret.angle_c_rad = asin(height/c.distance);
                                ret.angle_c_deg = glm::degrees(ret.angle_c_rad);
                                ret.angle_a_deg = 180 - (ret.angle_c_deg + ret.angle_b_deg);
                                ret.angle_a_rad = glm::radians(ret.angle_a_deg);
				ret.area = 0.5 * ret.hypotenuse * height;
			}else if(c.distance > a.distance && c.distance > b.distance){
				ret.type = TRIANGLE_SCALENE;
				ret.hypotenuse = c.distance;
				float semi = ret.perimiter/2;
				float height = 2/ret.hypotenuse*sqrt(semi*(semi-a.distance)*(semi-b.distance)*(semi-c.distance));
				ret.angle_a_rad = asin(height/a.distance);
                                ret.angle_a_deg = glm::degrees(ret.angle_a_rad);
                                ret.angle_c_rad = asin(height/b.distance);
                                ret.angle_c_deg = glm::degrees(ret.angle_c_rad);
                                ret.angle_b_deg = 180 - (ret.angle_a_deg + ret.angle_c_deg);
                                ret.angle_b_rad = glm::radians(ret.angle_b_deg);
				ret.area = 0.5 * ret.hypotenuse * height;
			}

			return ret;
		}
	public:
		bool failed(void){
			return this->error;
		}
		void clearError(void){
			this->error = false;
		}

		float distance(glm::vec2 a, glm::vec2 b){
			return (float)sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
		}
		float distance(glm::vec3 a, glm::vec3 b){
			return (float)sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2) + pow(b.z-a.z, 2));
		}

		float slope(glm::vec2 a, glm::vec2 b){
			float _a = (b.y-a.y);
			float _b = (b.x-a.x);
			if(_b == 0)
				return -0;
			float ret = _a / _b;
			return ret;
		}

		line3_t createLine(glm::vec3 a, glm::vec3 b){
			line3_t ret;
			ret.vertecies[0] = a;
			ret.vertecies[1] = b;
			
			ret.perspective_x_z = create2dLine(glm::vec2(a.x, a.z), glm::vec2(b.x, b.z));
        		ret.perspective_x_y = create2dLine(glm::vec2(a.x, a.y), glm::vec2(b.x, b.y));
        		// y perspective
        		ret.perspective_y_z = create2dLine(glm::vec2(a.y, a.z), glm::vec2(b.y, b.z));
        		ret.perspective_y_x = create2dLine(glm::vec2(a.y, b.x), glm::vec2(b.y, b.x));
        		// z perspective
        		ret.perspective_z_x = create2dLine(glm::vec2(a.z, a.x), glm::vec2(b.z, b.x));
        		ret.perspective_z_y = create2dLine(glm::vec2(a.z, a.y), glm::vec2(b.z, b.y));

			ret.distance = distance(a, b);
			ret.direction = glm::normalize(glm::cross(a, b));
			if(isnan(ret.direction.x))
				ret.direction.x = -0;
			if(isnan(ret.direction.y))
				ret.direction.y = -0;
			if(isnan(ret.direction.z))
				ret.direction.z = -0;

				//ret.distance == 0 ? glm::vec3(0) : (b-a)/ret.distance;
			//ret.direction = b - a;
			
			ret.start = a;
			ret.end = ret.start + ret.distance*ret.direction;
			if(isnan(ret.end.x))
				ret.end.x = -0;
			if(isnan(ret.end.y))
				ret.end.y = 0;
			if(isnan(ret.end.z))
				ret.end.z = 0;

			if((ret.end.x != b.x && ret.end.y != b.y && ret.end.z != b.z) || error){
				error = true;
			}else{
				//error = false;
			}
			return ret;
		}

		triangle3_t createTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c){
			triangle3_t ret;
			ret.vertecies[0] = a;
			ret.vertecies[1] = b;
			ret.vertecies[2] = c;
			
			ret.line_a = createLine(a, b);
			ret.line_b = createLine(b, c);
			ret.line_c = createLine(c, a);

			ret.perspective_x_z = create2dTriangle(ret.line_a.perspective_x_z, ret.line_b.perspective_x_z, ret.line_c.perspective_x_z);
        		ret.perspective_x_y = create2dTriangle(ret.line_a.perspective_x_y, ret.line_b.perspective_x_y, ret.line_c.perspective_x_y);
        		ret.perspective_y_z = create2dTriangle(ret.line_a.perspective_y_z, ret.line_b.perspective_y_z, ret.line_c.perspective_y_z);
        		ret.perspective_y_x = create2dTriangle(ret.line_a.perspective_y_x, ret.line_b.perspective_y_x, ret.line_c.perspective_y_x);
        		ret.perspective_z_x = create2dTriangle(ret.line_a.perspective_z_x, ret.line_b.perspective_z_x, ret.line_c.perspective_z_x);
        		ret.perspective_z_y = create2dTriangle(ret.line_a.perspective_z_y, ret.line_b.perspective_z_y, ret.line_c.perspective_z_y);

			ret.angle_a_deg = ret.perspective_x_z.angle_a_deg + 
				ret.perspective_x_y.angle_a_deg + 
				ret.perspective_y_z.angle_a_deg + 
				ret.perspective_y_x.angle_a_deg +
				ret.perspective_z_x.angle_a_deg + 
				ret.perspective_z_y.angle_a_deg;

			if(ret.angle_a_deg > 180)
				ret.angle_a_deg -= 180;
			ret.angle_a_rad = glm::radians(ret.angle_a_deg);

			 ret.angle_b_deg = ret.perspective_x_z.angle_b_deg +
                                ret.perspective_x_y.angle_b_deg +
                                ret.perspective_y_z.angle_b_deg +
                                ret.perspective_y_x.angle_b_deg +
                                ret.perspective_z_x.angle_b_deg +
                                ret.perspective_z_y.angle_b_deg;
                        if(ret.angle_b_deg > 180)
                                ret.angle_b_deg -= 180;
                        ret.angle_b_rad = glm::radians(ret.angle_b_deg);

			 ret.angle_c_deg = ret.perspective_x_z.angle_c_deg +
                                ret.perspective_x_y.angle_c_deg +
                                ret.perspective_y_z.angle_c_deg +
                                ret.perspective_y_x.angle_c_deg +
                                ret.perspective_z_x.angle_c_deg +
                                ret.perspective_z_y.angle_c_deg;
                        if(ret.angle_c_deg > 180)
                                ret.angle_c_deg -= 180;
                        ret.angle_c_rad = glm::radians(ret.angle_c_deg);

			ret.midpoint_a = (ret.line_a.vertecies[0] + ret.line_a.vertecies[1])/(float)2.0;
        		ret.midpoint_b = (ret.line_b.vertecies[0] + ret.line_b.vertecies[1])/(float)2.0;
        		ret.midpoint_c = (ret.line_c.vertecies[0] + ret.line_c.vertecies[1])/(float)2.0;

			ret.normal = ret.line_a.direction + ret.line_b.direction + ret.line_c.direction;

			ret.area = ret.perspective_x_z.area +
                                ret.perspective_x_y.area +
                                ret.perspective_y_z.area +
                                ret.perspective_y_x.area +
                                ret.perspective_z_x.area +
                                ret.perspective_z_y.area;
			return ret;
		};
};
