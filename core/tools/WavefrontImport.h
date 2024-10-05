typedef struct obj_data{
	float vertex[3];
	float texture[2];
	float normal[3];
	float material_color[3];
}obj_data_t;

typedef struct obj_materia{
	std::string name = "";
	float Ka[3] = {0, 0, 0};
}obj_material_t;

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

class WavefrontImport{
	private:
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
								materials[selectedMaterial].Ka[a] = std::stof(value);
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

	public:
		size_t objCount = 0;
		obj_data_t *obj = NULL;

		size_t glObjBufferSize = 0;
		float *glObjBuffer = NULL;

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

		size_t countObjects(void){
			if(this->objectDirectory == "" || this->objectName == ""){
				return 0;
			}
			std::string objFileName = objectDirectory + "/" + objectName + ".obj";
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
			
			std::string grabber = "";
			std::string materialName = "";
                        int selectedMaterial = -1;
                        for(int i=0; i<mtlSize; i++){
                                if(mtl[i] == '\n'){
                                        if(grabber.rfind("newmtl ", 0) == 0){ // Found material name
                                                std::string name = "";
                                                for(int j=7; j<grabber.length(); j++){
                                                        name += grabber[j];
                                                        materialName += grabber[j];
                                                }

                                                for(int j=0; j<uniqueMaterialCount; j++){
                                                        if(name == materials[j].name){
                                                                selectedMaterial = j;
                                                                break;
                                                        }
                                                }
                                        }else if(grabber.rfind("Kd ", 0) == 0){
						for(int j=0; j<oSize; j++){
							if(materialName != o[j].material.name){
								continue;
							}
                                                	std::string grab = "";

                                                	bool gotRed = false;
							bool gotGreen = false;
                                                	for(int k=3; k<grabber.length(); k++){
                                                	        if(grabber[j] == ' '){
									if(!gotRed){
										o[j].material.Ka[0] = std::stof(grab);
										gotRed = true;
									}else if(!gotGreen){
										o[j].material.Ka[1] = std::stof(grab);
										gotGreen = true;
									}else{
										o[j].material.Ka[2] = std::stof(grab);
									
									}
                                                	                grab = "";
                                                	        }else{
                                                	                grab += grabber[k];
                                                	        }
                                                	}
							if(grab != ""){
								o[j].material.Ka[2] = std::stof(grab);
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
								
								o[oi].glut_data[glI] = o[oi].material.Ka[0];
								glI++;
								o[oi].glut_data[glI] = o[oi].material.Ka[1];
								glI++;
								o[oi].glut_data[glI] = o[oi].material.Ka[2];
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

				o[oi].glut_data[glI] = o[oi].material.Ka[0];glI++;
				o[oi].glut_data[glI] = o[oi].material.Ka[1];glI++;
				o[oi].glut_data[glI] = o[oi].material.Ka[2];glI++;
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

		bool import(const char *objFile){
			if(!this->readFile(objFile)){
                                return false;
                        }

			countFields();
			allocateFieldStrings();
			parseVertexFloats();
			parseTextureFloats();
			parseNormalFloats();
			parseFaceIndecies();
			parseMaterials();
			createGlBuffer();
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
