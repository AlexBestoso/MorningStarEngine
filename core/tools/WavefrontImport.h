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

                	v_data = NULL;
                	vt_data = NULL;
                	vn_data = NULL;
                	f_data = NULL;
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
						printf("Parsing '%s'\n", g.c_str());
						v_data[x] = parse3Var(g, 2);
						printf("Stored %f, %f, %f in %d\n", v_data[x].x, v_data[x].y, v_data[x].z, x);
						x++;
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
                                                		x++;
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
                                                this->object_name = "";
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
		struct wavefront_face *f_data = NULL;

		WavefrontMaterial material;

		void init(std::string objectData, std::string matLoc){
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

		void allocateFieldStrings(void){
			textures = new std::string[varTracker.texture_count];
                        normals = new std::string[varTracker.normal_count];
                        vertexs = new std::string[varTracker.vertex_count];
                        faces = new std::string[varTracker.face_count];
			materialNames = new std::string[materialCount];

			int t=0, n=0, v=0, f=0, m=0, o=-1; // incrementers
			std::string grabber = ""; // line buffer
			// parse out the obj data into seperate strings.
                        for(int i=0; i<objFileSize; i++){
				if(objFileData[i] == '\n'){
					if(grabber.rfind("vt ", 0) == 0){
						textures[t] = "";
						for(int j=3; j<grabber.length(); j++)
							textures[t] += grabber[j];
						textures[t] += ' ';
						importedObjects[o].texture_count++;
						t++;
					}else if(grabber.rfind("vn ", 0) == 0){
						normals[n] = "";
						for(int j=3; j<grabber.length(); j++)
							normals[n] += grabber[j];
						normals[n] += ' ';
						importedObjects[o].normal_count++;
						n++;
					}else if(grabber.rfind("v ", 0) == 0){
						vertexs[v] = "";
						for(int j=2; j<grabber.length(); j++)
							vertexs[v] += grabber[j];
						vertexs[v] += ' ';
						importedObjects[o].vertex_count++;
						v++;
					}else if(grabber.rfind("f ", 0) == 0){
                                                faces[f] = "";
                                                for(int j=2; j<grabber.length(); j++)
                                                        faces[f] += grabber[j];
                                                faces[f] += ' ';
						importedObjects[o].face_count++;
                                                f++;
                                        }else if(grabber.rfind("usemtl ", 0) == 0){
                                                materialNames[m] = "";
                                                for(int j=7; j<grabber.length(); j++)
                                                        materialNames[m] += grabber[j];
						importedObjects[o].material.name = materialNames[m];
                                                m++;
                                        }else if(grabber.rfind("o ", 0) == 0){
						o++;
						importedObjects[o].name = "";
						for(int j=2; j<grabber.length(); j++)
							importedObjects[o].name += grabber[j];
						importedObjects[o].vertex_count = 0;
						importedObjects[o].texture_count = 0;
						importedObjects[o].normal_count = 0;
					}
					grabber = "";
				}else{
					grabber += objFileData[i];
				}
                        }

			// Identify unique material names.
			std::string *usedNames = new std::string[materialCount];
			uniqueMaterialCount = 0;
			for(int i=0; i<materialCount; i++){
				grabber = materialNames[i];
				bool unique = true;
				for(int j=0; j<materialCount; j++){
					if(grabber == usedNames[j]){
						unique = false;
						break;
					}
				}
				if(unique){
					usedNames[uniqueMaterialCount] = grabber;
					uniqueMaterialCount++;
					grabber = "";
				}
			}

			materials = new obj_material_t[uniqueMaterialCount];
			for(int i=0; i<uniqueMaterialCount; i++)
				materials[i].name = usedNames[i];
			delete[] usedNames;


		}


		void parseVertexFloats(void){
			vertexMultiplyer = 0;
			for(int i=0; i<vertexs[0].length(); i++){
				if(vertexs[0][i] == ' '){
					vertexMultiplyer++;
				}
			}

			vertexArray = new float[varTracker.vertex_count*vertexMultiplyer];
			int k = 0;
                        for(int i=0; i<varTracker.vertex_count; i++){
                                std::string grab = "";
                                for(int j=0; j<vertexs[i].length(); j++){
                                        if(vertexs[i][j] == ' '){
						if(k >= varTracker.vertex_count*vertexMultiplyer)
							break;
                                                vertexArray[k] = std::stof(grab);
                                                grab = "";
                                                k++;
                                        }else{
                                                grab += vertexs[i][j];
                                        }
                                }
				if(k >= varTracker.vertex_count*vertexMultiplyer)
                                	break;
                        }
			delete[] vertexs;
		}


		void parseTextureFloats(void){
			textureMultiplyer = 0;
			for(int i=0; i<textures[0].length(); i++){
                                if(textures[0][i] == ' '){
                                        textureMultiplyer++;
                                }
                        }

			textureArray = new float[varTracker.texture_count*textureMultiplyer];

			int k = 0;
                        for(int i=0; i<varTracker.texture_count; i++){
                                std::string grab = "";
                                for(int j=0; j<textures[i].length(); j++){
                                        if(textures[i][j] == ' ' && grab.length() != 0){
						if(k >= varTracker.texture_count*textureMultiplyer)
		                                        break;
                                                textureArray[k] = std::stof(grab);
                                                grab = "";
                                                k++;
                                        }else{
                                                grab += textures[i][j];
                                        }
                                }
				if(k >= varTracker.texture_count*textureMultiplyer)
                                        break;
                        }

			delete[] textures;
		}


		void parseNormalFloats(void){
			normalMultiplyer = 0;
			for(int i=0; i<normals[0].length(); i++){
                                if(normals[0][i] == ' '){
                                        normalMultiplyer++;
                                }
                        }

                	normalArray = new float[varTracker.normal_count*normalMultiplyer];
			
			int k = 0;
                        for(int i=0; i<varTracker.normal_count; i++){
                                std::string grab = "";
                                for(int j=0; j<normals[i].length(); j++){
					if(k >= varTracker.normal_count*normalMultiplyer)
                                        	break;
                                        if(normals[i][j] == ' ' && grab.length() != 0){
                                                normalArray[k] = std::stof(grab);
                                                grab = "";
                                                k++;
                                        }else{
                                                grab += normals[i][j];
                                        }
                                }
				if(k >= varTracker.normal_count*normalMultiplyer)
                                        break;
                        }
			delete[] normals;
		}

		void parseFaceIndecies(void){
			faceArrayLens = new int[varTracker.face_count];
			faceArraySize = 0;
			for(int j=0; j<varTracker.face_count; j++){
				faceMultiplyer = 0;
				for(int i=0; i<faces[j].length(); i++){
					if(faces[j][i] == ' '){
						faceMultiplyer++;
					}
				}
				faceArrayLens[j] = faceMultiplyer;
				faceArraySize += 3*faceMultiplyer;
			}

			faceArray = new int[faceArraySize];
			int k = 0;
                        for(int i=0; i<varTracker.face_count; i++){
                                std::string grab = "";
                                for(int j=0; j<faces[i].length(); j++){
					if(k >= faceArraySize)
                                        	break;
                                        if((faces[i][j] == ' ' || faces[i][j] == '/') && grab.length() != 0){
                                                faceArray[k] = std::stoi(grab);
                                                grab = "";
                                                k++;
                                        }else{
                                                grab += faces[i][j];
                                        }
                                }
				if(k >= faceArraySize)
                                        break;
                        }
			delete[] faces;

		}

		

		bool parseMaterials(void){
			fd = open(materialFileLoc.c_str(), O_RDONLY);
                        if(!fd){
                                printf("Failed to open '%s'\n", materialFileLoc.c_str());
                                return false;
                        }

                        struct stat st;
                        if(fstat(fd, &st)){
                                printf("fstat failed.\n");
                                close(fd);
                                return false;
                        }
                        size_t mtlSize = st.st_size;
                        char *mtl = new char[objFileSize];

                        if(read(fd, mtl, mtlSize) < mtlSize){
                                printf("Failed to read.\n");
                                close(fd);
                                delete[] mtl;
                                return false;
                        }
                        close(fd);
			std::string grabber = "";
			int selectedMaterial = -1;
			for(int i=0; i<mtlSize; i++){
				if(mtl[i] == '\n'){
					if(grabber.rfind("newmtl ", 0) == 0){ // Found material name
						std::string name = "";
						for(int j=7; j<grabber.length(); j++){
							name += grabber[j];
						}

						for(int j=0; j<uniqueMaterialCount; j++){
							if(name == materials[j].name){
								selectedMaterial = j;
								break;
							}
						}
					}else if(grabber.rfind("Kd ", 0) == 0){
						std::string value = "";
						int a = 0;
						for(int j=3; j<grabber.length(); j++){
							if(grabber[j] == ' '){
								materials[selectedMaterial].Kd[a] = std::stof(value);
								value = "";
								a++;
							}else{
								value += grabber[j];
							}
						}
						materials[selectedMaterial].Ka[a] = std::stof(value);
					}
					grabber = "";
				}else{
					grabber += mtl[i];
				}
			}
			delete[] mtl;

			// build material map
			grabber = "";
			selectedMaterial = -1;
			int faceTracker = 0;
			for(int i=0; i<objFileSize; i++){
				if(objFileData[i] == '\n'){
					if(grabber.rfind("usemtl ", 0) == 0){
						std::string name = "";
                                                for(int j=7; j<grabber.length(); j++){
                                                        name += grabber[j];
                                                }

                                                for(int j=0; j<uniqueMaterialCount; j++){
                                                        if(name == materials[j].name){
                                                                selectedMaterial = j;
                                                                break;
                                                        }
                                                }
					}else if(grabber.rfind("f ", 0) == 0){
						materialMap[faceTracker] = selectedMaterial;
						faceTracker++;
					}
					grabber = "";
				}else{
					grabber += objFileData[i];
				}
			}
			return true;
		}

		/*
		 * This function is used to map the data of the .obj file to
		 * individual objects when multiple objects are within a single
		 * .obj
		 * */
		void calculateOffsets(void){
			int o = 0;
			int faceTracker = 0;
			for(int i=0; i<varTracker.face_count; i++){
				//int val = (faceArrayLens[i]%3) == 1 ? 2 : (faceArrayLens[i]%3) == 2 ? 1 : 0; // Magical line that corrects a flaw in the population of this array.
				if(o > varTracker.object_count)
					break;
				importedObjects[o].buffer_size += (faceArrayLens[i]/*+val*/)*11; // 8 becase 3v / 2t/ 3n
				if(faceTracker >= importedObjects[o].face_count){
					importedObjects[o].buffer_count = importedObjects[o].buffer_size / 11;
					if(o == 0){
						importedObjects[o].buffer_start = 0;
					}else{
						importedObjects[o].buffer_start = importedObjects[o-1].buffer_start+importedObjects[o-1].buffer_size;
					}
					o++;
					faceTracker = 0;
				}
				if(faceTracker == 0){
					importedObjects[o].buffer_size = 0;
				}
				faceTracker++;
			}
			importedObjects[o].buffer_count = importedObjects[o].buffer_size / 11;
			if(o == 0){
				importedObjects[o].buffer_start = 0;
			}else{
				importedObjects[o].buffer_start = importedObjects[o-1].buffer_start+importedObjects[o-1].buffer_size;
			}
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
		
		int getObjectTextureOffsetByIndex(int objIndex){
                        int ret = 0;
                        if(objIndex <= -1 || objIndex >= varTracker.object_count)
                                return 0;
                        for(int i=0; i<varTracker.object_count; i++){
                                if(i == objIndex){
                                        break;
                                }else{
                                        ret += importedObjects[i].texture_count;
                                }
                        }
                        return ret;
		}

		int getObjectNormalOffsetByIndex(int objIndex){
			int ret = 0;
                        if(objIndex <= -1 || objIndex >= varTracker.object_count)
                                return 0;
                        for(int i=0; i<varTracker.object_count; i++){
                                if(i == objIndex){
                                        break;
                                }else{
                                        ret += importedObjects[i].normal_count;
                                }
                        }
                        return ret;
		}

		size_t calculateBufferSize(void){
			glObjBufferSize = 0;
                        for(int i=0; i<varTracker.object_count; i++){
                                if(materialFileLoc == "")
                                        glObjBufferSize += 8 * importedObjects[i].buffer_count;
                                else
                                        glObjBufferSize += 11 * importedObjects[i].buffer_count;
                        }
			return glObjBufferSize;
		}

		void createGlBuffer(void){
			glObjBufferSize = glObjBufferSize;
			printf("Buffer Size : %ld\n", glObjBufferSize);
                	this->glObjBuffer = new float[glObjBufferSize];
			int tracker = 0;
			int faceTrack = 0;
			for(int i=0; i<varTracker.face_count; i++){
				if(tracker > glObjBufferSize)
					break;
				int objectIndex = getObjectIndexByFace(i);
				if(objectIndex <= -1)
					continue;
				int objectVectorOffset = getObjectVectorOffsetByIndex(objectIndex);
				int objectTextureOffset = getObjectTextureOffsetByIndex(objectIndex);
				int objectNormalOffset = getObjectNormalOffsetByIndex(objectIndex);
				glm::vec3 vert;
				glm::vec2 texture;
				glm::vec3 normal;
				glm::vec3 color;

				// what vector indecies does the first face use?
				int faceCounter = 0;
				for(int j=0; j<faceArrayLens[j]; j++){
					if(i+3 >= varTracker.face_count || tracker > glObjBufferSize)
						break;
				
					int vertIndex = objectVectorOffset+faceArray[(i*j)+j];
					int textureIndex = objectTextureOffset+faceArray[(i*j)+j+1];
					int normalIndex = objectNormalOffset+faceArray[(i*j)+j+2];
					if(vertIndex+2 >= varTracker.vertex_count*vertexMultiplyer)
						break;
					if(textureIndex+1 >= varTracker.texture_count*textureMultiplyer)
						break;
					if(normalIndex+2 >= varTracker.normal_count*normalMultiplyer)
						break;
					vert = glm::vec3(vertexArray[vertIndex], vertexArray[vertIndex+1], vertexArray[vertIndex+2]);
					texture = glm::vec2(textureArray[textureIndex], textureArray[textureIndex+1]);
					normal = glm::vec3(normalArray[normalIndex], normalArray[normalIndex+1], normalArray[normalIndex+2]);
					

					glObjBuffer[tracker] = vert.x; tracker++;
					glObjBuffer[tracker] = vert.y; tracker++;
					glObjBuffer[tracker] = vert.z; tracker++;
					glObjBuffer[tracker] = texture.x; tracker++;
					glObjBuffer[tracker] = texture.x; tracker++;
					glObjBuffer[tracker] = normal.x; tracker++;
					glObjBuffer[tracker] = normal.y; tracker++;
					glObjBuffer[tracker] = normal.z; tracker++;
					if(materialFileLoc != ""){
						color = glm::vec3(materials[materialMap[i]].Ka[0], materials[materialMap[i]].Ka[1], materials[materialMap[i]].Ka[2]);
						glObjBuffer[tracker] = color.x; tracker++;
						glObjBuffer[tracker] = color.y; tracker++;
						glObjBuffer[tracker] = color.z; tracker++;
						tracker+= 11;
					}else{
						tracker += 8;
					}
					
					j+= 2;	
				}
			}

			obj = (obj_data_t *)glObjBuffer;
			if(materialFileLoc != "")
				objCount = glObjBufferSize/11;
			else
				objCount = glObjBufferSize/8;///sizeof(obj_data_t);
			delete[] faceArray;
			delete[] vertexArray;
			delete[] textureArray;
			delete[] normalArray;
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
                obj_t *getImportedObjects(void){
			return importedObjects;
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

		bool objStat(obj_t *o, size_t oSize){
			if(this->objectDirectory == "" || this->objectName == ""){
                                return false;
                        }
                        std::string objFileName = objectDirectory + "/" + objectName + ".obj";
                        int fd = open(objFileName.c_str(), O_RDONLY);
                        if(fd <= -1){
                                return false;
                        }
                        struct stat st;
                        if(fstat(fd, &st) == -1){
                                return false;
                        }

			char *b = new char[st.st_size];
			if(read(fd, b, st.st_size) != st.st_size){
				delete[] b;
				close(fd);
				return false;
			}
			int oi = -1;
			std::string grabber = "";
			for(int i=0; i<st.st_size; i++){
				if(oi >= oSize && oi != -1){
					break;
				}
				if(b[i] == '\n'){
					if(grabber.rfind("o ", 0) == 0){
						oi++;
						o[oi].name = "";
						o[oi].mode = GL_TRIANGLES;
						if(o[oi].glut_data != NULL){
							delete[] o[oi].glut_data;
							o[oi].glut_data = NULL;
						}
						o[oi].glut_size = 0;
						for(int j=2; j<grabber.length(); j++)
							o[oi].name += grabber[j];
					}else if(grabber.rfind("f ", 0) == 0){
						o[oi].face_count++;
						grabber += ' ';
						std::string grab = "";
						for(int j=2; j<grabber.length(); j++){
							if(grabber[j] == ' '){
								o[oi].glut_size+=11;
								o[oi].element_count++;
								grab = "";
							}else{
								grab += grabber[j];
							}
						}
						if(grab != "")
							o[oi].glut_size += 11;
					}else if(grabber.rfind("vn ", 0) == 0){
						o[oi].normal_count++;
					}else if(grabber.rfind("v ", 0) == 0){
                                                o[oi].vertex_count++;
					}else if(grabber.rfind("vt ", 0) == 0){
						o[oi].texture_count++;
					}else if(grabber.rfind("usemtl ", 0) == 0){
						o[oi].material.name = "";
						for(int j=7; j<grabber.length(); j++)
							o[oi].material.name += grabber[j];
					}
					grabber = "";
				}else{
					grabber += b[i];
				}
			}
			close(fd);
			delete[] b;
			return true;
		}

		bool loadMaterial(obj_t *o, size_t oSize){
			if(this->objectDirectory == "" || this->objectName == ""){
                                return false;
                        }
			std::string materialFileLoc = this->objectDirectory + "/" + this->objectName + ".mtl";
                        fd = open(materialFileLoc.c_str(), O_RDONLY);
                        if(!fd){
                                printf("Failed to open '%s'\n", materialFileLoc.c_str());
                                return false;
                        }

                        struct stat st;
                        if(fstat(fd, &st)){
                                printf("fstat failed.\n");
                                close(fd);
                                return false;
                        }
                        size_t mtlSize = st.st_size;
                        char *mtl = new char[mtlSize];

                        int err = read(fd, mtl, mtlSize);
			if(err != mtlSize){
                                printf("Failed to read.\n");
                                close(fd);
                                delete[] mtl;
                                return false;
                        }

                        close(fd);

/*			      std::string name = "";
        float Ks[3] = {0, 0, 0}; // Specular color
        int Ns = 0; // Shininess
        float d = 0.0; // Dissolve
}obj_material_t;*/
			
			obj_material_t matCont;
			
			std::string grabber = "";
			std::string materialName = "";
                        int selectedMaterial = -1;
			
                        for(int i=0; i<mtlSize; i++){
                                if(mtl[i] == '\n'){
                                        if(grabber.rfind("newmtl ", 0) == 0){ // Found material name
                                                matCont.name = "";
                                                for(int j=7; j<grabber.length(); j++){
                                                        matCont.name += grabber[j];
                                                }
                                        }else if(grabber.rfind("Kd ", 0) == 0){
						grabber += " ";
						for(int j=0; j<3; j++) matCont.Kd[j] = 0.0;
						std::string grub = "";
						int x = 0;
						for(int j=3; j<grabber.length(); j++){
							if(grabber[j] == ' '){
								try{
									matCont.Kd[x] = std::stof(grub.c_str());
								}catch(std::invalid_argument e){
									matCont.Kd[x] = 0.0;	
								}
								x++;
								grub = "";
							}else{
								grub += grabber[j];
							}
						}
						for(int j=0; j<oSize; j++){
							if(o[j].material.name == matCont.name){
								o[j].material.Kd[0] = matCont.Kd[0];
								o[j].material.Kd[1] = matCont.Kd[1];
								o[j].material.Kd[2] = matCont.Kd[2];
							}
						}
                                        }else if(grabber.rfind("Ka ", 0) == 0){
                                                grabber += " ";
                                                for(int j=0; j<3; j++) matCont.Ka[j] = 0.0;
                                                std::string grub = "";
                                                int x = 0;
                                                for(int j=3; j<grabber.length(); j++){
                                                        if(grabber[j] == ' '){
                                                                try{    
                                                                        matCont.Ka[x] = std::stof(grub.c_str());
                                                                }catch(std::invalid_argument e){
                                                                        matCont.Ka[x] = 0.0;
                                                                }
                                                                x++; 
                                                                grub = "";
                                                        }else{
                                                                grub += grabber[j];
                                                        }
                                                }
                                                for(int j=0; j<oSize; j++){
                                                        if(o[j].material.name == matCont.name){
                                                                o[j].material.Ka[0] = matCont.Ka[0];
                                                                o[j].material.Ka[1] = matCont.Ka[1];
                                                                o[j].material.Ka[2] = matCont.Ka[2];
                                                        }
                                                }
                                        }else if(grabber.rfind("Ks ", 0) == 0){
                                                grabber += " ";
                                                for(int j=0; j<3; j++) matCont.Ks[j] = 0.0;
                                                std::string grub = "";
                                                int x = 0;
                                                for(int j=3; j<grabber.length(); j++){
                                                        if(grabber[j] == ' '){
                                                                try{    
                                                                        matCont.Ks[x] = std::stof(grub.c_str());
                                                                }catch(std::invalid_argument e){
                                                                        matCont.Ks[x] = 0.0;
                                                                }
                                                                x++; 
                                                                grub = "";
                                                        }else{
                                                                grub += grabber[j];
                                                        }
                                                }
                                                for(int j=0; j<oSize; j++){
                                                        if(o[j].material.name == matCont.name){
                                                                o[j].material.Ks[0] = matCont.Ks[0];
                                                                o[j].material.Ks[1] = matCont.Ks[1];
                                                                o[j].material.Ks[2] = matCont.Ks[2];
                                                        }
                                                }
                                        }else if(grabber.rfind("Ns ", 0) == 0){
                                                grabber += " ";
                                               	matCont.Ns = 0;
                                                std::string grub = "";
                                                int x = 0;
                                                for(int j=3; j<grabber.length(); j++){
                                                        if(grabber[j] == ' '){
                                                                try{    
                                                                	matCont.Kd[x] = std::stoi(grub.c_str());
                                                                }catch(std::invalid_argument e){
                                                                        matCont.Kd[x] = 0;
                                                                }
                                                                x++; 
                                                                grub = "";
                                                        }else{
                                                                grub += grabber[j];
                                                        }
                                                }
                                                for(int j=0; j<oSize; j++){
                                                        if(o[j].material.name == matCont.name){
                                                                o[j].material.Ns = matCont.Ns;
                                                        }
                                                }
                                        }else if(grabber.rfind("Kd ", 0) == 0){
                                                grabber += " ";
                                                matCont.d = 0.0;
                                                std::string grub = "";
                                                int x = 0;
                                                for(int j=3; j<grabber.length(); j++){
                                                        if(grabber[j] == ' '){
                                                                try{    
                                                                        matCont.d = std::stof(grub.c_str());
                                                                }catch(std::invalid_argument e){
                                                                        matCont.d = 0.0;
                                                                }
                                                                x++; 
                                                                grub = "";
                                                        }else{
                                                                grub += grabber[j];
                                                        }
                                                }
                                                for(int j=0; j<oSize; j++){
                                                        if(o[j].material.name == matCont.name){
                                                                o[j].material.d = matCont.d;
                                                        }
                                                }
                                        }else if(grabber.rfind("map_Kd ", 0) == 0){
						matCont.map_Kd = "";
                                                for(int j=7; j<grabber.length(); j++){
                                                        matCont.map_Kd += grabber[j];
                                                }
                                                for(int j=0; j<oSize; j++){
                                                        if(o[j].material.name == matCont.name){
                                                                o[j].material.map_Kd = matCont.map_Kd;
                                                        }
                                                }
                                        }
                                        grabber = "";
                                }else{
                                        grabber += mtl[i];
                                }
                        }
                        delete[] mtl;
			return true;
		}
		bool loadData(obj_t *o, size_t oSize){
			 if(this->objectDirectory == "" || this->objectName == ""){
                                return false;
                        }
                        std::string objFileName = objectDirectory + "/" + objectName + ".obj";
                        int fd = open(objFileName.c_str(), O_RDONLY);
                        if(fd <= -1){
                                return false;
                        }
                        struct stat st;
                        if(fstat(fd, &st) == -1){
                                return false;
                        }

			size_t bSize = st.st_size;
                        char *b = new char[bSize];
                        int err = read(fd, b, bSize);
		       	if(err != st.st_size){
                                delete[] b;
                                close(fd);
				return false;
                        }
			int oi = -1;
			glm::vec3 *v = NULL;
			int vi = 0;
			glm::vec2 *t = NULL;
			int ti = 0;
			glm::vec3 *n = NULL;
			int ni = 0;
			glm::vec3 *f = NULL;
			int fi = 0;
			int glI=0;
			std::string grabber = "";
			bool finalize = false;
			int vTrack = 0;
			int tTrack = 0;
			int nTrack = 0;
			for(int i=0; i<st.st_size; i++){
				if(b[i] == '\n'){
					if(grabber.rfind("o ", 0) == 0){
						if(oi >= 0){
							for(int j=0; j<o[oi].element_count; j++){
								if(glI >= o[oi].glut_size){
									break;
								}

								int vOff = (int)(f[j].x-1); //- (vTrack-o[oi].vertex_count) - 1;
								int tOff = (int)(f[j].y-1); // - (tTrack-o[oi].texture_count) - 1;
								int nOff = (int)(f[j].z-1); //- (nTrack-o[oi].normal_count) - 1;
								if(oi > 1){
									vOff -= o[oi-1].vertex_count;
									tOff -= o[oi-1].texture_count;
									nOff -= o[oi-1].normal_count;
								}

								o[oi].glut_data[glI] = v[vOff].x;
								glI++;
								o[oi].glut_data[glI] = v[vOff].y;
								glI++;
								o[oi].glut_data[glI] = v[vOff].z;
								glI++;

								o[oi].glut_data[glI] = t[tOff].x;
								glI++;
								o[oi].glut_data[glI] = t[tOff].y;
								glI++;
								
								o[oi].glut_data[glI] = n[nOff].x;
								glI++;
								o[oi].glut_data[glI] = n[nOff].y;
								glI++;
								o[oi].glut_data[glI] = n[nOff].z;
								glI++;
								
								o[oi].glut_data[glI] = o[oi].material.Kd[0];
								glI++;
								o[oi].glut_data[glI] = o[oi].material.Kd[1];
								glI++;
								o[oi].glut_data[glI] = o[oi].material.Kd[2];
								glI++;
							}
						}
						oi++;
						if(f != NULL){
                        		        	delete[] f;
							f = NULL;
						}
                        			if(n != NULL){
                        			        delete[] n;
							n = NULL;
						}
                        			if(t != NULL){
                        			        delete[] t;
							t = NULL;
						}
                        			if(v != NULL){
                        		        	delete[] v;
							v = NULL;
						}
						if(o[oi].glut_data){
							delete[] o[oi].glut_data;
							o[oi].glut_data = NULL;

						}
						o[oi].glut_data = new float[o[oi].glut_size];
						vi = 0;
						ti = 0;
						ni = 0;
						fi = 0;
						glI = 0;
						v = new glm::vec3[o[oi].vertex_count];
						t = new glm::vec2[o[oi].texture_count];
						n = new glm::vec3[o[oi].normal_count];
						f = new glm::vec3[o[oi].element_count];
					}else if(grabber.rfind("v ", 0) == 0){
						std::string grab = "";
						bool gotX = false;
						for(int j=2; j<grabber.length(); j++){
							if(grabber[j] == ' '){
								if(!gotX){
									v[vi].x = std::stof(grab.c_str());
									gotX = true;
								}else{
									v[vi].y = std::stof(grab.c_str());
								}
								
								grab = "";
							}else{
								grab += grabber[j];
							}
						}
						if(grab != "")
							v[vi].z = std::stof(grab.c_str());
						vi++;
						vTrack++;
					}else if(grabber.rfind("vn ", 0) == 0){
                                                std::string grab = "";
                                                bool gotX = false;
                                                for(int j=3; j<grabber.length(); j++){
                                                        if(grabber[j] == ' '){
                                                                if(!gotX){
                                                                        n[ni].x = std::stof(grab.c_str());
                                                                        gotX = true;
                                                                }else{
                                                                        n[ni].y = std::stof(grab.c_str());
                                                                }

                                                                grab = "";
                                                        }else{
                                                                grab += grabber[j];
                                                        }
                                                }
                                                if(grab != "")
                                                        n[ni].z = std::stof(grab.c_str());
                                                ni++;
						nTrack++;
                                        }else if(grabber.rfind("vt", 0) == 0){
                                                std::string grab = "";
                                                for(int j=3; j<grabber.length(); j++){
                                                        if(grabber[j] == ' '){
                                                                t[ti].x = std::stof(grab.c_str());
                                                                grab = "";
                                                        }else{
                                                                grab += grabber[j];
                                                        }
                                                }
                                                if(grab != "")
                                                        t[ti].y = std::stof(grab.c_str());
                                                ti++;
						tTrack++;
                                        }else if(grabber.rfind("f ", 0) == 0){
						grabber += " ";
                                                std::string grab = "";
                                                for(int j=2; j<grabber.length(); j++){
                                            		if(grabber[j] == ' '){
								grab += "/";
								std::string g = "";
								bool gotV=false, gotT=false;
								for(int k=0; k<grab.length(); k++){
									try{
										if(grab[k] == '/'){
											if(!gotV){
												gotV=true;
												f[fi].x = std::stof(g.c_str());
											}else if(!gotT){
												gotT=true;
												f[fi].y = std::stof(g.c_str());
											}else{ // got normal
												f[fi].z = std::stof(g.c_str());
												fi++;
												g = "";
												break;
											}
											g = "";
										}else{
											g += grab[k];
										}
									}catch(std::invalid_argument e){
										continue;
									}
								}

                                                                grab = "";
                                                        }else{
                                                                grab += grabber[j];
                                                        }
                                                }
                                        }
					grabber = "";
				}else{
					grabber += b[i];
				}
			}

			// Final process
			for(int j=0; j<o[oi].element_count; j++){
				if(glI >= o[oi].glut_size){
					break;
				}

				int vOff = (int)(f[j].x-1); //- (vTrack-o[oi].vertex_count) - 1;
				int tOff = (int)(f[j].y-1); // - (tTrack-o[oi].texture_count) - 1;
				int nOff = (int)(f[j].z-1); //- (nTrack-o[oi].normal_count) - 1;
				if(oi > 0){
					vOff -= o[oi-1].vertex_count;
					tOff -= o[oi-1].texture_count;
					nOff -= o[oi-1].normal_count;
				}
				o[oi].glut_data[glI] = v[vOff].x;glI++;
				o[oi].glut_data[glI] = v[vOff].y;glI++;
				o[oi].glut_data[glI] = v[vOff].z;glI++;
				
				o[oi].glut_data[glI] = t[tOff].x;glI++;
				o[oi].glut_data[glI] = t[tOff].y;glI++;
				
				o[oi].glut_data[glI] = n[nOff].x;glI++;
				o[oi].glut_data[glI] = n[nOff].y;glI++;
				o[oi].glut_data[glI] = n[nOff].z;glI++;

				o[oi].glut_data[glI] = o[oi].material.Kd[0];glI++;
				o[oi].glut_data[glI] = o[oi].material.Kd[1];glI++;
				o[oi].glut_data[glI] = o[oi].material.Kd[2];glI++;
			}

			for(int i=0; i<oSize; i++){
				o[i].textureLocation = this->objectDirectory;
			       	o[i].textureLocation += "/";
				o[i].textureLocation += o[i].name;
			       	o[i].textureLocation +=	".jpg";
                                if(access(o[i].textureLocation.c_str(), F_OK) == -1){
                                        printf("Debug: Texture Doesn't Exist '%s'\n", o[i].textureLocation.c_str());
                                        o[i].textureLocation = "";
                                }else{
                                        printf("Debug: Found Texture '%s'\n", o[i].textureLocation.c_str());
                                }
			}


			delete[] b; 
                        if(f != NULL)
				delete[] f;
                        if(n != NULL)
				delete[] n;
                        if(t != NULL)
				delete[] t;
			if(v != NULL)
				delete[] v;
			close(fd);
			return true;
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
			printf("New : Object Count : %d\n", (int)this->objectCount);
			
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
			
			printf("Object 1: %s\n", this->objectBuffers[0].c_str());
			printf("Object 2: %s\n", this->objectBuffers[1].c_str());
			printf("Object 3: %s\n", this->objectBuffers[2].c_str());
			return true;
		}

		bool convertObjects(void){
			if(this->objectCount <= 0)
				return false;
			if(waveObjects != NULL)
				delete[] waveObjects;
			
			waveObjects = new WavefrontObject[this->objectCount];
			for(int i=0; i<this->objectCount; i++){
				waveObjects[i].init(this->objectBuffers[i], this->buildFilePathMat());
			}
			return true;
		}

		size_t calcGlBufferSize(void){
			size_t ret = 0;
			/*
 			 * Current structure is vertex(3), texture(2), normal(3), color(3)
			* */
			int fragmentSize = 11;
			for(int i=0; i<this->objectCount; i++){
				ret += waveObjects[i].getFCount() * fragmentSize;
			}
			
			return ret;
		}

		size_t calcGlBufferSize(int idx){
			size_t ret = 0;
			/*
 			 * Current structure is vertex(3), texture(2), normal(3), color(3)
			* */
			int fragmentSize = 11;
			ret += waveObjects[idx].getFCount() * fragmentSize;
			
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

			printf("Serializing %d faces...\n", (int)waveObjects[idx].getFCount());
			int x = 0;
			for(int j=0; j<waveObjects[idx].getFCount() && x < glObjBufferSize; j++){
				int vindex = waveObjects[idx].f_data[j].v;
				printf("\tFace %d using vertex index %d\n", j, vindex);
				// Each face contains an index for the respective v/vt/n values....
				glObjBuffer[x] = waveObjects[idx].v_data[vindex].x; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].v_data[vindex].y; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].v_data[vindex].z; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
					
				int vtindex = waveObjects[idx].f_data[j].t;
				glObjBuffer[x] = waveObjects[idx].vt_data[vtindex].x; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].vt_data[vtindex].y; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);

				int vnindex = waveObjects[idx].f_data[j].n;
				glObjBuffer[x] = waveObjects[idx].vn_data[vnindex].x; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].vn_data[vnindex].y; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].vn_data[vnindex].z; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
					
				glObjBuffer[x] = waveObjects[idx].material.mtl.Kd.x; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].material.mtl.Kd.y; x++;
				printf("\t\t%f\n", glObjBuffer[x-1]);
				glObjBuffer[x] = waveObjects[idx].material.mtl.Kd.z; x++;
				printf("\t\t%f\n\n", glObjBuffer[x-1]);
			}

			return true;
		}

		bool serializeObjects(void){
			if(glObjBufferSize > 0){
                		delete[] glObjBuffer;
			}
			
			glObjBufferSize = calcGlBufferSize();
			if(glObjBufferSize <= 0)
				return false;
			glObjBuffer = new float[glObjBufferSize];

			int x = 0;			
			for(int i=0; i<this->objectCount && x < glObjBufferSize; i++){
				for(int j=0; j<waveObjects[i].getFCount() && x < glObjBufferSize; j++){
					// Each face contains an index for the respective v/vt/n values....
					glObjBuffer[x] = waveObjects[i].v_data[waveObjects[i].f_data[j].v].x; x++;
					glObjBuffer[x] = waveObjects[i].v_data[waveObjects[i].f_data[j].v].y; x++;
					glObjBuffer[x] = waveObjects[i].v_data[waveObjects[i].f_data[j].v].z; x++;
					
					glObjBuffer[x] = waveObjects[i].vt_data[waveObjects[i].f_data[j].t].x; x++;
					glObjBuffer[x] = waveObjects[i].vt_data[waveObjects[i].f_data[j].t].y; x++;

					glObjBuffer[x] = waveObjects[i].vn_data[waveObjects[i].f_data[j].n].x; x++;
					glObjBuffer[x] = waveObjects[i].vn_data[waveObjects[i].f_data[j].n].y; x++;
					glObjBuffer[x] = waveObjects[i].vn_data[waveObjects[i].f_data[j].n].z; x++;
					
					glObjBuffer[x] = waveObjects[i].material.mtl.Kd.x; x++;
					glObjBuffer[x] = waveObjects[i].material.mtl.Kd.y; x++;
					glObjBuffer[x] = waveObjects[i].material.mtl.Kd.z; x++;
				}
			}
			return true;
		}

		bool import(const char *objFile){
			/*new import function start*/
			if(!this->readFile(objFile)){
                                return false;
                        }
			this->_countObjects();
			
			/*new import function end*/

			/*countFields();
			allocateFieldStrings();
			parseVertexFloats();
			parseTextureFloats();
			parseNormalFloats();
			parseFaceIndecies();
			parseMaterials();
			createGlBuffer();*/
			delete[] this->objFileData;


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
