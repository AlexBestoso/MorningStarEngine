#include "./aes128.h"
#include <string.h>

class Aes128Cbc{
	private:
	Aes128 aes128;

	/*
	 * Used to ensure that the buffer containing the ciphertext 
	 * is a multiple of 16 (128 bits)
	 * */
	size_t calcCipherTextSize(size_t plaintextSize){
		size_t ret = 0;
		if(plaintextSize >= 16){
			// Get number of blocks, ensure it's a multiple of block size.
                	ret = (plaintextSize/16)*16;
                	// if stringSize is greater than stateSize, we're one block short.
                	if(plaintextSize > ret){
                	        ret += 16;
                	}
        	}else{
        	        ret = 16;
        	}

		return ret;
	}

	public:
	const size_t keySize = 16;
	const size_t ivSize = 16;
	const size_t stateSize = 16;
	char key128[16];
	char iv128[16];

	char *result = NULL;
	size_t resultSize = 0;

	void encipher(char *plaintext, size_t plaintextSize, char iv[16], char key[16]){
		size_t messageSize = this->calcCipherTextSize(plaintextSize);
		char message[messageSize]; 
		
		/* Format plaintext so it fits in blocks. */
        	for(int i=0; i<plaintextSize; i++)
        	        message[i] = plaintext[i];

        	for(int i=plaintextSize; i<messageSize; i++)
        	        message[i] = 0x00;


		char tmp_key[16];
		unsigned int blockCount = messageSize/this->stateSize;
	
		char state_container[blockCount][16];
		for(int i=0; i<blockCount; i++){
			for(int j=0; j<this->stateSize; j++)
			state_container[i][j] = '\0';
		}
	
		signed int inc = -1;
		for(int i=0; i<messageSize; i++){
			if((i%this->stateSize) == 0){
				inc++;
			}
			state_container[inc][i%this->stateSize] = message[i];
		}

		for(int i=0; i<blockCount; i++){
			for(int j=0; j<this->keySize; j++)
				tmp_key[j] = key[j];
		
			for(int j=0; j<this->ivSize; j++)
				state_container[i][j] = state_container[i][j] ^ iv[j];
			
			this->aes128.encipher(state_container[i], tmp_key);
	
			for(int j=0; j<this->ivSize; j++)
				iv[j] = state_container[i][j];
		}	
	
		for(int i=0; i<blockCount; i++){
			for(int j=0; j<this->stateSize; j++){
				message[(i*this->stateSize)+j] = state_container[i][j];
			}
		}
		
		if(this->result != NULL){
			free(this->result);
			this->result=NULL;
		}
		this->resultSize = messageSize;
		this->result = (char *)malloc(sizeof(char)*messageSize);
		for(int i=0; i<messageSize; i++)
			this->result[i] = message[i];
	}

	void decipher(char *ciphertext, size_t ciphertextSize, char iv[16], char key[16]){
		size_t messageSize = this->calcCipherTextSize(ciphertextSize);
                char message[messageSize];

		/* Format ciphertext so it fits in blocks. */
                for(int i=0; i<ciphertextSize; i++)
                        message[i] = ciphertext[i];

                for(int i=ciphertextSize; i<messageSize; i++)
                        message[i] = 0x00;

        	char tmp_key[16];
		char tmp_IV[16];
        	unsigned int blockCount = messageSize/this->stateSize;
	
	        char msg_container[blockCount][16];
	        for(int i=0; i<blockCount; i++){
	                for(int j=0; j<this->stateSize; j++)
	                msg_container[i][j] = '\0';
	        }
	
	        signed int inc = -1;
	        for(int i=0; i<messageSize; i++){
	                if((i%this->stateSize) == 0){
	                        inc++;
	                }
	                msg_container[inc][i%this->stateSize] = message[i];
	        }
	
	        for(int i=0; i<blockCount; i++){
	                for(int j=0; j<this->keySize; j++)
	                        tmp_key[j] = key[j];
			for(int j=0; j<this->stateSize; j++){
				tmp_IV[j] = msg_container[i][j];
			}
	
			this->aes128.decipher(msg_container[i], tmp_key);
		
	                for(int j=0; j<this->ivSize; j++)
	                        msg_container[i][j] = msg_container[i][j] ^ iv[j];
	
	                for(int j=0; j<this->ivSize; j++)
	                        iv[j] = tmp_IV[j];
	        }
		
	        for(int i=0; i<blockCount; i++){
	                for(int j=0; j<this->stateSize; j++){
	                        message[(i*this->stateSize)+j] = msg_container[i][j];
	                }
	        }

                if(this->result != NULL){
                        free(this->result);
			this->result = NULL;
		}
		this->resultSize = messageSize;
                this->result = (char *)malloc(sizeof(char)*messageSize);
                for(int i=0; i<messageSize; i++)
                        this->result[i] = message[i];
	}
};
