typedef struct obj_data{
	float vertex[3];
	float texture[2];
	float normal[3];
	float material_color[3];
}obj_data_t;

typedef struct obj_face_data{
	int vector;
	int texture;
	int normal;
}obj_face_data_t;

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
	
	float *vertex_set = NULL;
        float *texture_set = NULL;
	float *normal_set = NULL;
	
	size_t vertex_count = 0;
	size_t texture_count = 0;
	size_t normal_count = 0;
	size_t face_count = 0;
	
	size_t buffer_size = 0;
	int buffer_start = 0;
	int buffer_count = 0;

	int vertex_start = 0;
	int texture_start = 0;
	int normal_start = 0;

	int vertex_end = 0;
	int texture_end = 0;
	int normal_end = 0;
}obj_t;


class WavefrontImport{
	private:
		std::string materialFileLoc = "";
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
			printf("Offset Debug, Face count : %ld\n", varTracker.face_count);
			for(int i=0; i<varTracker.face_count; i++){
				int val = (faceArrayLens[i]%3) == 1 ? 2 : (faceArrayLens[i]%3) == 2 ? 1 : 0; // Magical line that corrects a flaw in the population of this array.
				if(o > varTracker.object_count)
					break;
				importedObjects[o].buffer_size += (faceArrayLens[i]+val)*11; // 8 becase 3v / 2t/ 3n
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

		void createGlBuffer(void){
			glObjBufferSize = 0;
			for(int i=0; i<varTracker.face_count; i++){
				int val = (faceArrayLens[i]%3) == 1 ? 2 : (faceArrayLens[i]%3) == 2 ? 1 : 0;
				if(materialFileLoc == "")
					glObjBufferSize += 8*(faceArrayLens[i]+val);
				else
					glObjBufferSize += 11*(faceArrayLens[i]+val);
			}
                	glObjBuffer = new float[glObjBufferSize];
			int tracker = 0;
			int faceTrack = 0;
			for(int i=0; i<varTracker.face_count; i++){
				int vec_a=0, vec_b=0, vec_c=0;
				int tex_a=0, tex_b=0, tex_c=0;
				int norm_a=0, norm_b=0, norm_c=0;
				int vec=0, tex=0, norm=0;
				int correct = faceArrayLens[i] % 3;
				for(int j=0; j<3*faceArrayLens[i]; j++){
					vec_c = vec_b;
					tex_c = tex_b;
					norm_c = norm_b;

					vec_b = vec_a;
					tex_b = tex_a;
					norm_b = norm_a;

					vec_a = vec;
					tex_a = tex;
					norm_a = norm;

					vec = (faceArray[faceTrack] - 1)*vertexMultiplyer;
                                        tex = (faceArray[faceTrack+1] - 1)*textureMultiplyer;
                                        norm = (faceArray[faceTrack+2] - 1)*normalMultiplyer;

					faceTrack+=3;

					if(correct == 1 && j-3 >= faceArrayLens[i] || correct == 2 && j-6 >=faceArrayLens[i]){
						break;
					
					}
					if(correct == 0){
						printf("In thirds %d %d\n", i, j);
						printf("\t%f, %f, %f\n", vertexArray[vec], vertexArray[vec+1], vertexArray[vec+1]);
					}
					
					glObjBuffer[tracker] = vertexArray[vec];
                                        glObjBuffer[tracker+1] = vertexArray[vec+1];
                                        glObjBuffer[tracker+2] = vertexArray[vec+2];
                                        glObjBuffer[tracker+3] = textureArray[tex];
                                        glObjBuffer[tracker+4] = textureArray[tex+1];
                                        glObjBuffer[tracker+5] = normalArray[norm];
                                        glObjBuffer[tracker+6] = normalArray[norm+1];
                                        glObjBuffer[tracker+7] = normalArray[norm+2];
					if(materialFileLoc != ""){
						glObjBuffer[tracker+8] = materials[materialMap[i]].Ka[0];
                                                glObjBuffer[tracker+9] = materials[materialMap[i]].Ka[1];
                                                glObjBuffer[tracker+10] = materials[materialMap[i]].Ka[2];
						tracker += 11;
					}else{
                                        	tracker +=8;
					}
                                        	j+=2;
				}

				if(correct == 1){ // We have one vertex placed and need to place 2 more.
					glObjBuffer[tracker] = vertexArray[vec_a];
                                        glObjBuffer[tracker+1] = vertexArray[vec_a+1];
                                        glObjBuffer[tracker+2] = vertexArray[vec_a+2];
                                        glObjBuffer[tracker+3] = textureArray[tex_a];
                                        glObjBuffer[tracker+4] = textureArray[tex_a+1];
                                        glObjBuffer[tracker+5] = normalArray[norm_a];
                                        glObjBuffer[tracker+6] = normalArray[norm_a+1];
                                        glObjBuffer[tracker+7] = normalArray[norm_a+2];
					if(materialFileLoc != ""){
						glObjBuffer[tracker+8] = materials[materialMap[i]].Ka[0];
                                                glObjBuffer[tracker+9] = materials[materialMap[i]].Ka[1];
                                                glObjBuffer[tracker+10] = materials[materialMap[i]].Ka[2];
						tracker += 11;
                                        }else{
						tracker +=8;
					}

					glObjBuffer[tracker] = vertexArray[vec];
                                        glObjBuffer[tracker+1] = vertexArray[vec+1];
                                        glObjBuffer[tracker+2] = vertexArray[vec+2];
                                        glObjBuffer[tracker+3] = textureArray[tex];
                                        glObjBuffer[tracker+4] = textureArray[tex+1];
                                        glObjBuffer[tracker+5] = normalArray[norm];
                                        glObjBuffer[tracker+6] = normalArray[norm+1];
                                        glObjBuffer[tracker+7] = normalArray[norm+2];
					if(materialFileLoc != ""){
						glObjBuffer[tracker+8] = materials[materialMap[i]].Ka[0];
                                                glObjBuffer[tracker+9] = materials[materialMap[i]].Ka[1];
                                                glObjBuffer[tracker+10] = materials[materialMap[i]].Ka[2];
						tracker += 11;
                                        }else{
						tracker += 8;
					}

					glObjBuffer[tracker] = vertexArray[vec_c];
                                        glObjBuffer[tracker+1] = vertexArray[vec_c+1];
                                        glObjBuffer[tracker+2] = vertexArray[vec_c+2];
                                        glObjBuffer[tracker+3] = textureArray[tex_c];
                                        glObjBuffer[tracker+4] = textureArray[tex_c+1];
                                        glObjBuffer[tracker+5] = normalArray[norm_c];
                                        glObjBuffer[tracker+6] = normalArray[norm_c+1];
                                        glObjBuffer[tracker+7] = normalArray[norm_c+2];
					if(materialFileLoc != ""){
						glObjBuffer[tracker+8] = materials[materialMap[i]].Ka[0];
                                                glObjBuffer[tracker+9] = materials[materialMap[i]].Ka[1];
                                                glObjBuffer[tracker+10] = materials[materialMap[i]].Ka[2];
						tracker += 11;
                                        }else{
						tracker += 8;
					}
				}

				if(correct == 2){
					printf("Correct 2 by adding 1\n");
					glObjBuffer[tracker] = vertexArray[vec_b];
                                        glObjBuffer[tracker+1] = vertexArray[vec_b+1];
                                        glObjBuffer[tracker+2] = vertexArray[vec_b+2];
                                        glObjBuffer[tracker+3] = textureArray[tex_b];
                                        glObjBuffer[tracker+4] = textureArray[tex_b+1];
                                        glObjBuffer[tracker+5] = normalArray[norm_b];
                                        glObjBuffer[tracker+6] = normalArray[norm_b+1];
                                        glObjBuffer[tracker+7] = normalArray[norm_b+2];
					if(materialFileLoc != ""){
						glObjBuffer[tracker+8] = materials[materialMap[i]].Ka[0];
                                                glObjBuffer[tracker+9] = materials[materialMap[i]].Ka[1];
                                                glObjBuffer[tracker+10] = materials[materialMap[i]].Ka[2];
						tracker+=11;
                                        }else{
                                        	tracker += 8;
					}
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


		bool importComplex(std::string objectDir, std::string objectName){
			std::string objectFile = objectDir + "/" + objectName + ".obj";
			materialFileLoc = objectDir + "/" + objectName + ".mtl";
			if(access(objectFile.c_str(), F_OK) == -1){
				printf("Error: object file '%s' doesn't exist.\n", objectFile.c_str());
				return false;
			}
		
			if(access(materialFileLoc.c_str(), F_OK) == -1)
				materialFileLoc = "";

			if(!this->readFile(objectFile.c_str())){
                                return false;
                        }

			// Parse out the .obj and .mtl files
			countFields();
			allocateFieldStrings();
                        parseVertexFloats();
                        parseTextureFloats();
                        parseNormalFloats();
                        parseFaceIndecies();
                        parseMaterials();
			calculateOffsets();
			
			// check for texutre images
			for(int i=0; i<varTracker.object_count; i++){
				importedObjects[i].textureLocation = objectDir + "/" + importedObjects[i].name + ".jpg";
				if(access(importedObjects[i].textureLocation.c_str(), F_OK) == -1){
					importedObjects[i].textureLocation = "";
				}else{
					printf("Debug Found Texture '%s'\n", importedObjects[i].textureLocation.c_str());
				}
			}

			// debug code
			createGlBuffer();
                        delete[] this->objFileData;

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
