class Function{
	private:

	public:
		int (*intReturnFunction_ptr)(void);
		int (*intReturnFunction_int_ptr)(int);
		int intReturnFunction_int(int a){
			return intReturnFunction_int_ptr(a);
		}
		int intReturnFunction(void){
			return intReturnFunction_ptr();
		}
};
