#include "RadixSort.h"

#include "CSC2110/Keyboard.h" //look for changes to getValidatedInt
using CSC2110::Keyboard;
#include "CSC2110/CD.h"
using CSC2110::CD;
#include "CSC2110/ListArray.h"
using CSC2110::ListArray;
#include "CSC2110/ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CSC2110/Text.h"
using CSC2110::String;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int sortChoice()
{
	//I changed Keyboard.cpp and .h because if you type in a characted for getValidatedInt, it crashes
	Keyboard* kb = Keyboard::getKeyboard();
	
	String* min = new String("1");
	String* max = new String("3");
	String* second = new String("(1)Radix Sort Ascending   --  \r\n  -- (2)Radix Sort Descending  --  \r\n  -- (3)Quit                   ");
	String* first = new String("\r\n  -------------------------------\r\n  --      Radix Sort Menu      --\r\n  -------------------------------\r\n  -- ");
	
	
	first->displayString();
	second->displayString();
	int sort_choice = kb->getValidatedInt("--  \r\n  ------------------------------- \r\n  Menu Choice: ", min, max);
	
	delete min;
	delete max;
	delete first;
	delete second;
	return sort_choice;
}

int surePrompt()
{
	Keyboard* kb = Keyboard::getKeyboard();
	String* sure;
	String* error = new String("Invalid input!\n");
    String* end_line = new String("\n");
	
	char in_p;
	bool loop = true;
	
	while(loop)
	{
		end_line->displayString();
		sure = kb->readString("** Are you sure you want to quit?(Y/N) : ");
		in_p = sure->charAt(0);
		
		if(in_p == 'n' || in_p == 'N')
		{
			end_line->displayString();
			return 2;
		}
		else if(in_p == 'y' || in_p == 'Y')
		{
			end_line->displayString();
			return 3;
		}
		else
		{
			end_line->displayString();
			error->displayString();

		}	
	}

	delete sure;
	delete error;
	delete end_line;

}


//displays sorted cds
void displayDem(CD** c_ds, int size)
{
   String* s = new String("\n");
   for(int i = 0; i < size; i++)
   {
	   //String* t = c_ds[i]->getKey();
	  // t->displayString();
	   //s->displayString();
	   c_ds[i]->displayCD();
   }  

	delete[] c_ds;
}

int main()
{
   ListArray<CD>* list = CD::readCDs("cds.txt");
   int size = list->size();  
   int num_chars = 0;          //for max num of chars
   bool ascending = true;      //boolean for the radixSort parameters
   
   //created strings
   String* end_line = new String("\n");
   String* donezo = new String("done\n");
   String* a = new String("Ascending Sort:\n");
   String* d = new String("Descending Sort:\n");
   
   CD** cds = new CD*[size];
   ListArrayIterator<CD>* iter = list->iterator();
   int count = 0;
   while(iter->hasNext())
   {
      CD* cd = iter->next();
	  cds[count] = cd;
	  
		String* cd_t = cds[count]->getKey();
		int str_size = cd_t->length();
		if(str_size > num_chars) num_chars = str_size;
		
	  count++;
   }
   delete iter;
   
	int choice = 0;
	bool valT = false;
	int i = 0;
	CD** c_ds;
	
   do
   {
	   choice = sortChoice();
	   
	   if(choice == 1)
	   {
			c_ds = RadixSort<CD>::radixSort(cds, size, num_chars, true, &CD::getRadixChar);  //sorts dem cds
			displayDem(c_ds, size);
			a->displayString();
	   }
	   else if(choice == 2)
	   {
			c_ds = RadixSort<CD>::radixSort(cds, size, num_chars, false, &CD::getRadixChar);  //sorts dem cds
			displayDem(c_ds, size);
			d->displayString();

	   }
	   else
	   {
		   i = surePrompt();
		   if(i == 3) break;
	   }
	   
		
   }while(!valT);
   



   delete[] cds;
   deleteCDs(list);
   delete list;
   delete donezo;
   delete end_line;
   delete a;
   delete d;
   
   return 0;
}
