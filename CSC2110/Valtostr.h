#if !defined VALTOSTR_H
#define VALTOSTR_H

namespace CSC2110
{
class Valtostr
{


	private:
	
		int sz;
		char* ctos;

		
	public:
	
		Valtostr();
		~Valtostr();
		const char* d_to_c(double number);
		const char* f_to_c(float number);
		const char* i_to_c(int number);
};	
}


#endif