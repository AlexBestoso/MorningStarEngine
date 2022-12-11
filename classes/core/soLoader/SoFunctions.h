/*
 * Fuctions are to be defined as DATATYPE_create and DATATYPE_destroy
 * */
class SoFunctions{
	private:

	public:
		ObjectForm* (*ObjectForm_create)();
        	void (*ObjectForm_destroy)(ObjectForm*);
};
