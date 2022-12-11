#include "./SoFunctions.h"
#define SOLOADER_MAX_HANDLE 20
class SoLoader{
        private:
	void* handleList[SOLOADER_MAX_HANDLE];
	int activeHandleCount = 0;

	public:
	SoFunctions functions;

	SoLoader(){
		for(int i=0; i<SOLOADER_MAX_HANDLE; i++){
			this->handleList[i] = NULL;
		}
	}

	void *getHandleById(int id){
		return this->handleList[id];
	}

	int openLazy(std::string soLocation){
		if(this->activeHandleCount >= SOLOADER_MAX_HANDLE){
			fprintf(stderr, "[E] Max SO Loader Handle Count Hit. Close some handles.");
			return -1;
		}

		int openSlotId = -1;
		for(int i=0; i<SOLOADER_MAX_HANDLE; i++){
			if(this->handleList[i] == NULL){
				openSlotId = i;
				break;
			}
		}

		if((this->handleList[openSlotId] = dlopen(soLocation.c_str(), RTLD_LAZY)) == NULL){
			fprintf(stderr, "[E] Failed to open targeted so file [%s]\n", soLocation.c_str());
			return -1;
		}

		if(this->activeHandleCount < 0)
			this->activeHandleCount = 0;

		this->activeHandleCount++;

		return openSlotId;
	}

	bool closeHandle(int id){
		if(id >= SOLOADER_MAX_HANDLE){
			return false;
		}
		if(this->handleList[id] == NULL){
			return false;
		}

		dlclose(this->handleList[id]);
		this->activeHandleCount--;
		return true;
	}

	void *loadSymbol(int handleId, string targetSymbol){
		if(handleId >= SOLOADER_MAX_HANDLE){
			fprintf(stderr, "Buffer overflow in loadSymbol.\n");
			return NULL;
		}

		if(this->handleList[handleId] == NULL){
			fprintf(stderr, "Invalid SO Handle ID\n");
			return NULL;
		}

		void *poop = dlsym(this->getHandleById(handleId), targetSymbol.c_str());
		if(poop == NULL){
			fprintf(stderr, "Failed to load symbol %s using id %d\n", targetSymbol.c_str(), handleId);
			return NULL;
		}
		return poop;
	}
};
