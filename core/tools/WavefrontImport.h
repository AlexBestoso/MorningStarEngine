typedef struct obj_data{
	float vertex[3];
	float texture[2];
	float normal[3];
	float material_color[3];
}obj_data_t;

typedef struct obj_materia{
	std::string name = "";
	std::string map_Kd;
	float Ka[3] = {0, 0, 0}; // ambient color
	float Kd[3] = {0, 0, 0}; // diffuse color
	float Ks[3] = {0, 0, 0}; // Specular color
	int Ns = 0; // Shininess
	float d = 0.0; // Dissolve
	int illum = 0;
}obj_material_t;

struct obj_mtl{
	std::string name = "";
	std::string map_Kd;
	glm::vec3 Ka; // ambient color
	glm::vec3 Kd; // diffuse color
	glm::vec3 Ks; // Specular color
	float Ns = 0.0; // Shininess
	float d = 0.0; // Dissolve
	int illum = 0;
};

typedef struct obj_var_tracker{
	size_t object_count = 0;
	size_t vertex_count = 0;
	size_t texture_count = 0;
	size_t normal_count = 0;
	size_t face_count = 0;
}obj_var_tracker_t;

typedef struct obj{
	std::string name = "";
	std::string textureLocation = "";
	obj_material_t material;
	float *glut_data = NULL;
	size_t glut_size = 0;
	
	size_t vertex_count = 0;
	size_t texture_count = 0;
	size_t normal_count = 0;
	size_t face_count = 0;
	size_t element_count = 0;


	//TODO: The stuff below can probably be deleted now
	size_t buffer_size = 0;
	int buffer_start = 0;
	int buffer_count = 0;

	int vertex_start = 0;
	int texture_start = 0;
	int normal_start = 0;

	int vertex_end = 0;
	int texture_end = 0;
	int normal_end = 0;

	uint32_t mode = (uint32_t)GL_TRIANGLES;
}obj_t;

class WavefrontMaterial{
	private:
		char *mtlFileData = NULL;
		size_t mtlFileSize = 0;

		size_t mtl_count = 0;

		int mtl_offset = 0;
		
		bool isField(std::string target, std::string src){
                        return src.rfind(target.c_str(), 0) == 0;
                }

		void cleanup(void){
			if(mtlFileData != NULL && mtlFileSize > 0){
				delete[] mtlFileData;
			}
			mtlFileData = NULL;
			mtlFileSize = 0;
		}

		bool readFile(const char *mtlFile){
                        int fd = open(mtlFile, O_RDONLY);
                        if(!fd){
                                printf("Failed to open '%s'\n", mtlFile);
                                return false;
                        }

                        struct stat st;
                        if(fstat(fd, &st)){
                                printf("fstat failed.\n");
                                close(fd);
                                return false;
                        }
                        this->mtlFileSize = st.st_size;
                        this->mtlFileData = new char[mtlFileSize];

                        if(read(fd, mtlFileData, mtlFileSize) < mtlFileSize){
                                printf("Failed to read.\n");
                                close(fd);
                                delete[] this->mtlFileData;
                                return false;
                        }
                        close(fd);
                        return true;
                }

		std::string getStringResult(std::string v, int offset=0){
			std::string ret = "";
			for(int i=offset; i<v.length(); i++){
				ret += v[i];
			}
			return ret;
		}
		glm::vec3 getVec3Result(std::string v, int offset=0){
			v += " ";
			glm::vec3 ret;
			std::string g = "";
			int x = 0;
			for(int i=offset; i<v.length(); i++){
				if(v[i] == ' '){
					float a = 0;
					try{
						a = std::stof(g.c_str());
					}catch(std::invalid_argument e){
						a = 0;
					}
					switch(x){
						case 0: ret.x = a; break;
						case 1: ret.y = a; break;
						case 2: ret.z = a; break;
					}
					x++;
					g = "";
				}else{
					g += v[i];
				}
			}
			return ret;
		}
		float getFloatResult(std::string v, int offset=0){
			float ret;
			std::string g = "";
			for(int i=offset; i<v.length(); i++){
				g += v[i];
			}
			try{
				ret = std::stof(g.c_str());
			}catch(std::invalid_argument e){
				ret = 0.0;
			}
			return ret;
		}
		int getIntResult(std::string v, int offset=0){
			int ret;
			std::string g = "";
			for(int i=offset; i<v.length(); i++){
				g += v[i];
			}
			try{
				ret = std::stoi(g.c_str());
			}catch(std::invalid_argument e){
				ret = 0;
			}
			return ret;
		}

		void calcMtlCount(void){
			std::string g = "";
			this->mtl_count = 0;
			for(int i=0; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("newmtl ", g.c_str())){
						this->mtl_count++;	
					}
					g = "";
				}else{
					g += this->mtlFileData[i];
				}
			}
		}
		
		void calcTargetOffset(std::string target){
			std::string g = "";
			this->mtl_offset = 0;
			for(int i=0; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("newmtl ", g.c_str())){
						std::string test = getStringResult(g, 7);
						if(test == target){
							this->mtl_offset = i-g.length();
							return ;
						}
					}
					g = "";
				}else{
					g += this->mtlFileData[i];
				}
			}
		}

		std::string fetch_mapKd(void){
			std::string ret = "";
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("map_Kd ", g.c_str())){
						return getStringResult(g, 7);
					}
					g = "";
				}else{
					g += this->mtlFileData[i];
				}
			}
			return ret;
		}
		glm::vec3 fetch_Ka(void){
			glm::vec3 ret;
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("Ka ", g.c_str())){
						return getVec3Result(g, 3);
					}
					g = "";
				}else{
					g+=this->mtlFileData[i];
				}

			}
			return ret;
		}
        	glm::vec3 fetch_Kd(void){
			glm::vec3 ret;
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("Kd ", g.c_str())){
						return getVec3Result(g, 3);
					}
					g = "";
				}else{
					g+=this->mtlFileData[i];
				}

			}
			return ret;
		}
        	glm::vec3 fetch_Ks(void){
			glm::vec3 ret;
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("Ks ", g.c_str())){
						return getVec3Result(g, 3);
					}
					g = "";
				}else{
					g+=this->mtlFileData[i];
				}
	
			}
			return ret;
		}
        	float fetch_Ns(void){
			int ret;
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("Ns ", g.c_str())){
						return getFloatResult(g, 3);
					}
					g = "";
				}else{
					g+=this->mtlFileData[i];
				}

			}
			return ret;
		}
        	float fetch_d(void){
			float ret;
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("d ", g.c_str())){
						return getFloatResult(g, 2);
					}
					g = "";
				}else{
					g+=this->mtlFileData[i];
				}

			}
			return ret;
		}
        	int fetch_illum(void){
			int ret;
			std::string g = "";
			for(int i=this->mtl_offset; i<this->mtlFileSize; i++){
				if(this->mtlFileData[i] == '\n'){
					if(isField("illum ", g.c_str())){
						return getIntResult(g, 6);
					}
					g = "";
				}else{
					g+=this->mtlFileData[i];
				}

			}
			return ret;
		}
	public:
		struct obj_mtl mtl;
		bool init(std::string fileLoc, std::string targetMaterial){
			if(!readFile(fileLoc.c_str())){
				return false;
			}
			
			this->calcMtlCount();
			calcTargetOffset(targetMaterial);
			
			this->mtl.name = targetMaterial;
			this->mtl.map_Kd = this->fetch_mapKd();
			this->mtl.Ka = this->fetch_Ka();
        		this->mtl.Kd = this->fetch_Kd();
        		this->mtl.Ks = this->fetch_Ks();
        		this->mtl.Ns = this->fetch_Ns();
        		this->mtl.d = this->fetch_d();
        		this->mtl.illum = this->fetch_illum();

			this->cleanup();
			return true;
		}
};

/*
 * 0 holds coords, 1 holds texture, 2 holds normals
 */
struct wavefront_face{
	int v;
	int t;
	int n;
};

class WavefrontObject{
	private:
		size_t v_size = 0;
		size_t vt_size = 0;
		size_t vn_size = 0;
		size_t f_size = 0;



		std::string material_name = "";
		std::string object_name = "";


		bool isField(std::string target, std::string src){
                        return src.rfind(target.c_str(), 0) == 0;
                }

		void _cleanup(void){
			if(v_data != NULL && v_size > 0)
				delete[] v_data;
                	if(vt_data != NULL && vt_size > 0)
				delete[] vt_data;
                	if(vn_data != NULL && vn_size > 0)
				delete[] vn_data;
                	if(f_data != NULL && f_size > 0)
				delete[] f_data;
			
			v_size = 0;
                	vt_size = 0;
                	vn_size = 0;
                	f_size = 0;

                	/*v_data = NULL;
                	vt_data = NULL;
                	vn_data = NULL;
                	f_data = NULL;*/
		}
		
		struct wavefront_face parseFace(std::string val){
			struct wavefront_face ret;
			std::string g = "";
			int x=0;
			val += "/";
			for(int i=0; i<val.length(); i++){
				if(val[i] == '/'){
					switch(x){
						case 0:try{
							ret.v = std::stoi(g.c_str())-1;
						}catch(std::invalid_argument e){
							ret.v = 0;
						}break;
						
						case 1:try{
							ret.t = std::stoi(g.c_str())-1;
						}catch(std::invalid_argument e){
							ret.t = 0;
						}break;
	
						case 2:try{
							ret.n = std::stoi(g.c_str())-1;
						}catch(std::invalid_argument e){
							ret.n = 0;
						}
					}
					x++;
					g = "";
				}else{
					g += val[i];
				}
			}
			return ret;
		}

		glm::vec3 parse3Var(std::string val, int start){
			glm::vec3 ret;
			std::string g = "";
			int x = 0;
			for(int i=start; i<val.length(); i++){
				if(val[i] == ' '){
					float v = 0;
					try{
						v = std::stof(g.c_str());
					}catch(std::invalid_argument e){
						v = 0;
					}
					switch(x){
						case 0:ret.x = v;break;
						case 1:ret.y = v;break;
						case 2:ret.z = v;break;
					}
					x++;
					g = "";
				}else{
					g += val[i];
				}
			}
			return ret;
		}

		glm::vec2 parse2Var(std::string val, int start=0){
                        glm::vec2 ret;
                        std::string g = "";
                        int x = 0;
                        for(int i=start; i<val.length(); i++){
                                if(val[i] == ' '){
                                        float v = 0;
                                        try{
                                                v = std::stof(g.c_str());
                                        }catch(std::invalid_argument e){
                                                v = 0;
                                        }
                                        switch(x){
                                                case 0:ret.x = v;break;
                                                case 1:ret.y = v;break;
                                        }
                                        x++;
                                }else{
                                        g += val[i];
                                }
                        }
                        return ret;
                }

		void calcVSize(std::string val){
			std::string g = "";
			v_size = 0;
			for(int i=0; i<val.length(); i++){
				if(val[i] == '\n'){
					v_size += isField("v ", g.c_str()) ? 1 : 0;
					g = "";
				}else{
					g += val[i];
				}
			}
		}
		void calcVtSize(std::string val){
			std::string g = "";
                        vt_size = 0;
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        vt_size += isField("vt ", g.c_str()) ? 1 : 0;
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
		}
		void calcVnSize(std::string val){
			std::string g = "";
                        vn_size = 0;
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        vn_size += isField("vn ", g.c_str()) ? 1 : 0;
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
		}
		void calcFSize(std::string val){
			std::string g = "";
                        f_size = 0;
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        if(isField("f ", g.c_str())){
						g+=" ";
						for(int j=2; j<g.length(); j++){
							if(g[j] == ' ')
								f_size++;
						}
					}
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
		}

		void populateVData(std::string val){
			std::string g = "";
			int x = 0;
			for(int i=0; i<val.length(); i++){
				if(val[i] == '\n'){
					if(isField("v ", g.c_str())){
						g+=' ';
						v_data[x] = parse3Var(g, 2);
						x++;
						if(x >= v_size) break;
					}
					g = "";
				}else{
					g += val[i];
				}
			}
		}
		void populateVtData(std::string val){
			std::string g = "";
                        int x = 0;
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        if(isField("vt ", g.c_str())){
                                                g+=' ';
                                                vt_data[x] = parse2Var(g, 3);
                                                x++;
						if(x >= vt_size) break;
                                        } 
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
		}
		void populateVnData(std::string val){
			std::string g = "";
                        int x = 0;
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        if(isField("vn ", g.c_str())){
                                                g+=' ';
                                                vn_data[x] = parse3Var(g, 3);
                                                x++;
						if(x >= vn_size) break;
                                        }
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
		}
		void populateFData(std::string val){
			std::string g = "";
                        int x = 0;
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        if(isField("f ", g.c_str())){
                                                g+=' ';
						std::string _g = "";
						for(int j=2; j<g.length(); j++){
							if(g[j] == ' '){
								f_data[x] = parseFace(_g);
								f_data[x].v -= v_offset;
								f_data[x].t -= vt_offset;
								f_data[x].n -= vn_offset;
                                                		x++;
								if(x >= f_size) break;
								_g = "";
							}else{
								_g += g[j];
							}
						}
                                        }
                                        g = "";
                                }else{     
                                        g += val[i];
                                }
                        }
		}

		void calcObjectName(std::string val){
			std::string g = "";
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        if(isField("o ", g.c_str())){
						this->object_name = "";
						for(int j=2; j<g.length(); j++){
							this->object_name += g[j];
						}
						break;
                                        }
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
		}

		void calcMaterialName(std::string val){
                        std::string g = "";
                        for(int i=0; i<val.length(); i++){
                                if(val[i] == '\n'){
                                        if(isField("usemtl ", g.c_str())){
                                                this->material_name = "";
                                                for(int j=7; j<g.length(); j++){
                                                        this->material_name += g[j];
                                                }
  	                                        break;
                                        } 
                                        g = "";
                                }else{
                                        g += val[i];
                                }
                        }
                }
	public:
		glm::vec3 *v_data = NULL;
		glm::vec2 *vt_data = NULL;
		glm::vec3 *vn_data = NULL;
		int v_offset = 0;
		int vt_offset = 0;
		int vn_offset = 0;
		struct wavefront_face *f_data = NULL;

		WavefrontMaterial material;

		void enumObj(){
			printf("Object: %s\n", object_name.c_str());
			printf("Material : %s\n", material_name.c_str());
			printf("Face Count: %ld\n", f_size);
			printf("V Count: %ld\n", v_size);
			printf("Vt Count: %ld\n", vt_size);
			printf("Vn Count: %ld\n", vn_size);
			//size_t v_size = 0;
                	//size_t vt_size = 0;
                	//size_t vn_size = 0;
                	for(int i=0; i<f_size; i++){
				printf("%d/%d/%d = (%f, %f, %f) (%f, %f) (%f, %f, %f)\n", f_data[i].v, f_data[i].t, f_data[i].n,
					v_data[f_data[i].v].x, v_data[f_data[i].v].y, v_data[f_data[i].v].z, 
					vt_data[f_data[i].t].x, vt_data[f_data[i].t].y, 
					vn_data[f_data[i].n].x, vn_data[f_data[i].n].y, vn_data[f_data[i].n].z);
			}

		}

		void init(std::string objectData, std::string matLoc, int v_o=0, int vt_o=0, int vn_o=0){
			v_offset = v_o;
			vt_offset = vt_o;
			vn_offset = vn_o;

			calcObjectName(objectData);
			calcMaterialName(objectData);

			calcVSize(objectData);
			calcVtSize(objectData);
			calcVnSize(objectData);
			calcFSize(objectData);

			v_data = new glm::vec3[v_size];
			vt_data = new glm::vec2[vt_size];
			vn_data = new glm::vec3[vn_size];
			f_data = new struct wavefront_face[f_size];
			
			populateVData(objectData);
			populateVtData(objectData);
			populateVnData(objectData);
			populateFData(objectData);

			this->material.init(matLoc, this->material_name);
		}

		size_t getVCount(void){
			return v_size;
		}

		size_t getVtCount(void){
			return vt_size;
		}
                size_t getVnCount(void){
			return vn_size;
		}
		size_t getFCount(void){
			return f_size;
		}

		std::string getName(void){
			return this->object_name;
		}

		void cleanup(void){this->_cleanup();}
};

class MorningRawObjects{
	private:
		
	public:
};

class WavefrontImport{
	private:
		std::string *objectBuffers = NULL;

		std::string materialFileLoc = "";
		std::string objectDirectory = "";
		std::string objectName = "";
		obj_var_tracker_t varTracker;
		obj_t *importedObjects = NULL;

		/*
		 * Multipliers are used in parsing to account for variable differences 
		 * in the .obj file format.
		 * */
		int objectMultiplyer = 0;
		int vertexMultiplyer = 0;
		int textureMultiplyer = 0;
		int normalMultiplyer = 0;
		int faceMultiplyer = 0;

		size_t materialCount = 0;
		size_t uniqueMaterialCount = 0;
		obj_material_t *materials = NULL;
		
		size_t objFileSize = 0;
		char *objFileData = NULL;
		
		int fd;

		float *vertexArray = NULL; 
		float *textureArray = NULL;
		float *normalArray = NULL;

		size_t materialMapSize = 0;
		int *materialMap = NULL;

		int *faceArray = NULL;
		int *faceArrayLens = NULL;
		int faceArraySize = 0;

		std::string *textures = NULL;
                std::string *normals = NULL;
                std::string *vertexs = NULL;
                std::string *faces = NULL;
		std::string *materialNames = NULL;

		std::string getLine(int index){
			if(objFileData == NULL)
				return "";

			std::string ret = "";
			for(int i=index; i<objFileSize; i++){
				if(objFileData[i] == '\n')
					return ret;
				else
					ret += objFileData[i];
			}
			return ret;
		}

		void countFields(void){
			materialCount = 0;
			varTracker.object_count = 0;
			varTracker.texture_count = 0;
			varTracker.normal_count = 0;
			varTracker.face_count = 0;

			std::string grabber = "";
			for(int i=0; i<objFileSize; i++){
				if(objFileData[i] == '\n'){
					if(grabber.rfind("vt ", 0) == 0){
						varTracker.texture_count++;
					}else if(grabber.rfind("vn ", 0) == 0){
						varTracker.normal_count++;
					}else if(grabber.rfind("v ", 0) == 0){
						varTracker.vertex_count++;
					}else if(grabber.rfind("f ", 0) == 0){
						varTracker.face_count++;
					}else if(grabber.rfind("usemtl ", 0) == 0){
						materialCount++;
					}else if(grabber.rfind("o ") == 0){
						varTracker.object_count++;
					}
					grabber = "";
				}else{
					grabber += objFileData[i];
				}
			}

			materialMapSize = varTracker.face_count;
			materialMap = new int[materialMapSize];
			importedObjects = new obj_t[varTracker.object_count];
		}

		int getObjectIndexByFace(int faceIndex){
			int ret = -1;
			std::string grabber = "";
			int faceCount = 0;
			for(int i=0; i<objFileSize; i++){
                                if(objFileData[i] == '\n'){
					if(grabber.rfind("o ", 0) == 0){
						ret++;
					}else if(grabber.rfind("f ", 0) == 0){
						faceCount++;
					}
					grabber = "";
				}else{
					grabber += objFileData[i];
				}
				if(faceCount == faceIndex){
					return ret == -1 ? 0 : ret;
				}
			}
			return ret;
		}

		int getObjectVectorOffsetByIndex(int objIndex){
			int ret = 0;
			if(objIndex <= -1 || objIndex >= varTracker.object_count)
				return 0;
			for(int i=0; i<varTracker.object_count; i++){
				if(i == objIndex){
					break;
				}else{
					ret += importedObjects[i].vertex_count;
				}
			}
			return ret;
		}
		




		bool isField(std::string target, std::string src){
			return src.rfind(target.c_str(), 0) == 0;
		}
	
	public:
		size_t objectCount = 0;
		size_t objCount = 0;
		obj_data_t *obj = NULL;

		size_t glObjBufferSize = 0;
		float *glObjBuffer = NULL;

		WavefrontObject *waveObjects = NULL;
		//WavefrontObject waveObjects[1000];
	
		bool readFile(const char *objFile){
			fd = open(objFile, O_RDONLY);
                        if(!fd){
                                printf("Failed to open '%s'\n", objFile);
                                return false;
                        }

                        struct stat st;
                        if(fstat(fd, &st)){
                                printf("fstat failed.\n");
                                close(fd);
                                return false;
                        }
                        this->objFileSize = st.st_size;
                        this->objFileData = new char[objFileSize];

                        if(read(fd, objFileData, objFileSize) < objFileSize){
                                printf("Failed to read.\n");
                                close(fd);
                                delete[] this->objFileData;
                                return false;
                        }
                        close(fd);
			return true;
		}


		size_t getObjectCount(void){
			return varTracker.object_count;
		}

		void setFile(std::string directory, std::string name){
			this->objectDirectory = directory;
			this->objectName = name;
		}

		std::string buildFilePath(void){
			std::string objFileName = objectDirectory + "/" + objectName + ".obj";
			return objFileName;
		}
		std::string buildFilePathMat(void){
			std::string objFileName = objectDirectory + "/" + objectName + ".mtl";
			return objFileName;
		}

		size_t _countObjects(void){
			if(this->objectDirectory == "" || this->objectName == ""){
				return 0;
			}
			std::string objFileName = this->buildFilePath();
			int fd = open(objFileName.c_str(), O_RDONLY);
			if(fd <= -1){
				return 0;
			}
			struct stat st;
			if(fstat(fd, &st) == -1){
				return 0;
			}
			
			size_t ret = 0;
			char *b = new char[st.st_size];

			if(read(fd, b, st.st_size) != st.st_size){
				close(fd);
				delete[] b;
				return 0;
			}
			std::string grabber = "";
			for(int i=0; i<st.st_size; i++){
				if(b[i] == '\n'){
					if(grabber.rfind("o ", 0) == 0){
						ret++;
					}
					grabber = "";
				}else{
					grabber += b[i];
				}
			}
			close(fd);
			delete[] b;
			return ret;
		}



		size_t countObjects(void){
			this->objectCount = 0;
			for(int i=0; i<this->objFileSize; i++){
				i = this->objFileData[i] == '\n' ? i+1 : i;

				std::string g = this->getLine(i);
				i+=g.length();
				if(g.rfind("o ", 0) == 0){
					this->objectCount++;
				}
			}
			
			return (size_t)this->objectCount;
		}

		bool isoloateObjects(void){
			if(this->objectCount <= 0)
				return false;
			if(this->objectBuffers != NULL)
				delete[] this->objectBuffers;
			
			objectBuffers = new std::string[this->objectCount];
			int start = 0;

			for(int i=0; i<this->objectCount; i++){
				int t = 0;
				std::string g = "";
				bool populating = false;
				for(int j=start; j<this->objFileSize; j++){
					if(this->objFileData[j] == '\n'){
						g+= "\n";
						if(populating && isField("o ", g.c_str())){
							break;
						}else if(populating){
							objectBuffers[i] += g;
						}else if(isField("o ", g.c_str()) && t == i){
							objectBuffers[i] = g;
							populating = true;
						}else if(isField("o ", g.c_str()) && t != i){
							t++;
						}
						g = "";
					}else{
						g += this->objFileData[j];
					}
				}
			}

			return true;
		}

		bool convertObjects(void){
			if(this->objectCount <= 0)
				return false;
			if(waveObjects != NULL)
				delete[] waveObjects;
			
			waveObjects = new WavefrontObject[this->objectCount];
			int vo=0, to=0, no=0;
			for(int i=0; i<this->objectCount; i++){
				waveObjects[i].init(this->objectBuffers[i], this->buildFilePathMat(), vo, to, no);
				vo += waveObjects[i].getVCount();
				to += waveObjects[i].getVtCount();
				no += waveObjects[i].getVnCount();
			}
			return true;
		}


		size_t calcGlBufferSize(int idx){
			size_t ret = 0;
			/*
 			 * Current structure is vertex(3), texture(2), normal(3), color(3)
			* */
			int fragmentSize = 11;
			ret = waveObjects[idx].getFCount() * fragmentSize;
			
			return ret;
		}


		bool serializeObject(int idx){
			if(glObjBufferSize > 0 || glObjBuffer != NULL){
                		delete[] glObjBuffer;
			}
			
			glObjBufferSize = calcGlBufferSize(idx);
			if(glObjBufferSize <= 0)
				return false;
			glObjBuffer = new float[glObjBufferSize];

			int x = 0;
			for(int j=0; j<waveObjects[idx].getFCount() && x < glObjBufferSize; j++){
				int vindex = waveObjects[idx].f_data[j].v;
				// Each face contains an index for the respective v/vt/n values....
				glObjBuffer[x] = waveObjects[idx].v_data[vindex].x; x++;
				glObjBuffer[x] = waveObjects[idx].v_data[vindex].y; x++;
				glObjBuffer[x] = waveObjects[idx].v_data[vindex].z; x++;
					
				int vtindex = waveObjects[idx].f_data[j].t;
				glObjBuffer[x] = waveObjects[idx].vt_data[vtindex].x; x++;
				glObjBuffer[x] = waveObjects[idx].vt_data[vtindex].y; x++;

				int vnindex = waveObjects[idx].f_data[j].n;
				glObjBuffer[x] = waveObjects[idx].vn_data[vnindex].x; x++;
				glObjBuffer[x] = waveObjects[idx].vn_data[vnindex].y; x++;
				glObjBuffer[x] = waveObjects[idx].vn_data[vnindex].z; x++;
					
				glObjBuffer[x] = waveObjects[idx].material.mtl.Kd.x; x++;
				glObjBuffer[x] = waveObjects[idx].material.mtl.Kd.y; x++;
				glObjBuffer[x] = waveObjects[idx].material.mtl.Kd.z; x++;
			}

			return true;
		}


		////TODO: Delete this once the skybox class is addressed.
		bool import(const char *objFile){
			/*new import function start*/
		//	if(!this->readFile(objFile)){
                 //               return false;
                  //      }
		//	this->_countObjects();
			
			/*new import function end*/

			/*countFields();
			allocateFieldStrings();
			parseVertexFloats();
			parseTextureFloats();
			parseNormalFloats();
			parseFaceIndecies();
			parseMaterials();
			createGlBuffer();*/
		//	delete[] this->objFileData;


			return true;
		}

		void destroy(void){
			objCount = 0;
                	glObjBufferSize = 0;
                	delete[] glObjBuffer;

			varTracker.vertex_count = 0;
                	vertexMultiplyer = 0;

                	varTracker.texture_count = 0;
                	textureMultiplyer = 0;

                	varTracker.normal_count = 0;
                	normalMultiplyer = 0;

                	varTracker.face_count = 0;
                	faceMultiplyer = 0;

                	objFileSize = 0;
                	objFileData = NULL;

                	vertexArray = NULL;
                	textureArray = NULL;
                	normalArray = NULL;
                	faceArray = NULL;

			textures = NULL;
               		normals = NULL;
               		vertexs = NULL;
             		faces = NULL;
		}

		void setMaterialFile(std::string loc){
			this->materialFileLoc = loc;
		}
};
