#include "Valtostr.h"
using CSC2110::Valtostr;

#include <iomanip>
#include <sstream>
using namespace std;


Valtostr::Valtostr()
{
	sz = 50;
	ctos = new char[sz];
}


Valtostr::~Valtostr()
{
	delete[] ctos;
}


const char* Valtostr::d_to_c(double number)
{
	
	stringstream out;
	out << setprecision(2) << fixed << number;
	string s = out.str();
	const char* temp = s.c_str();
	for(int i = 0; i < sz; i++)
	{
		ctos[i] = temp[i];
	}
	return ctos;
}

const char* Valtostr::f_to_c(float number)
{
	
	
	stringstream out;
	out << number;
	string s = out.str();
	const char* temp = s.c_str();
	for(int i = 0; i < sz; i++)
	{
		ctos[i] = temp[i];
	}
	return ctos;	
}

const char* Valtostr::i_to_c(int number)
{
	stringstream out;
	out << number;
	string s = out.str();
	const char* temp = s.c_str();
	for(int i = 0; i < sz; i++)
	{
		ctos[i] = temp[i];
	}
	return ctos;	
}