#include "Keywait.h"
using CSC2110::Keywait;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

Keywait::Keywait()
{}

Keywait::~Keywait()
{}

void Keywait::waitForKey()
{

	String* wf = new String("Press any key to continue . . .");
	wf->displayString();
	delete wf;
	cin.clear();
	cin.get();
	cin.ignore();

}