#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "CSC2110/CD.h"
using CSC2110::CD;
#include "CSC2110/QueueLinked.h"
using CSC2110::QueueLinked;
#include "CSC2110/text.h"
using CSC2110::String;
#include "CSC2110/Valtostr.h"  //my own class
using CSC2110::Valtostr;

template < class T >
class RadixSort
{
	private:
	
		/*
			Pre : Current character cannot be greater than the total amount of characters
			Post:  Sorts the bin recursivly
		*/
		static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
		
		/*
			Pre :  Num items are greater than 0, num_chars greater than 0
			Post: sorts the items
		*/
		static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1
		
		/*
			Pre : Num items are greater than 0, num chars greater than 0
			Post:  Sorts the items with bins
		*/
		static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2
 
	public:
		
		/*
			Pre : N/A
			Post: returns a sorted array
		*/
		static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
		
		/*
			Pre : N/A
			Post: Returns the index of the bin the character and/or item should be placed
		*/
		static int calc_bin_index(char rad);  //used for convenience
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
	T** radix_sorted_array = new T*[num_to_sort];  //create a new array for items 
   
    //puts items in new array
	for(int i = 0; i < num_to_sort; i++)
	{
		radix_sorted_array[i] = unsorted[i];
	}
	
	//execute the specified sorting function
	if(!asc)
	{
		radixSortDesc(radix_sorted_array, num_to_sort, num_chars, getRadixChar);
	}
	else
	{
		radixSortAsc(radix_sorted_array, num_to_sort, num_chars, getRadixChar);		
	}
	
	return radix_sorted_array;

}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{

	if(num_chars < 0) return;
	if(n < 0) return;
	
	QueueLinked<T>* bin_sort_bin = new QueueLinked<T>();  //creates a queue for binsort
	
	//enqueues all the items in array
	for(int i = 0; i < n; i++)
	{
		bin_sort_bin->enqueue(sort[i]);
	}
	
	binSort(bin_sort_bin, 0, num_chars, getRadixChar);  //calls binsort to deal with first character first
	
	//puts sorted items back into the array
	for(int i = 0; i < n; i++)
	{
		sort[i] = bin_sort_bin->dequeue();
	}
	
	
	delete bin_sort_bin;
	
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
	
	//check to see if parameters are vaid
	if(num_chars < curr_char) return;
	
	int q_num = 37;
	QueueLinked<T>** _bin = new QueueLinked<T>*[q_num];  //creates 37 bins of queues
	
	//put queues in all 37 bins
	for(int i = 0; i < q_num; i++)
	{
		_bin[i] = new QueueLinked<T>();
	}
	
	//get items from bin and put them in 37 bins
	while(!bin->isEmpty())
	{
		T* item = bin->dequeue();                            //holds item from the bin
		char rad_char = (*getRadixChar)(item, curr_char);    //gets radix char 
		int bin_num = calc_bin_index(rad_char);              //number of bin to be inserted
		_bin[bin_num]->enqueue(item);                        //put item in queue
	}
	
	//checks all bins
	for(int i = 0; i < q_num; i++)
	{
		int bin_size = _bin[i]->size();   //gets size
		
		//check for more that one item in bin
		if(bin_size > 1)
		{
			binSort(_bin[i], curr_char + 1, num_chars, getRadixChar);  //recursivly call binsort
		}
		
		while(!_bin[i]->isEmpty())
		{
			T* item = _bin[i]->dequeue();  //get item(s) from the bin at that index
			bin->enqueue(item);            //puts sorted items into original bin they came in
		}
		
		delete _bin[i];  //delete each bin
	}
	
	delete[] _bin;
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
	if(num_chars < 0) return;
	if(n < 0) return;
	
	int q_num = 37;  //covers letters and digits
	int counter = 0;
	
	QueueLinked<T>** _bin = new QueueLinked<T>*[q_num];  
	
	Valtostr* sVal = new Valtostr();      //class object
	
	//created strings
	String* b_str = new String("Bin # ");
	String* created = new String(" Created!\n");
	
	//must instantiate each of the queues
	for (int i = 0; i < q_num; i++)
	{
		_bin[i] = new QueueLinked<T>();
		
		/*
		String* bin_str = new String(sVal->i_to_c(i + 1));
		b_str->displayString();
		bin_str->displayString();
		created->displayString();
		*/
		
	}
	
	//go through max number of characters
	for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
	{
		//put each word in bin
		for(int k = 0; k < n; k++)
		{
			char rad_char = (*getRadixChar)(sort[k],i);
			int track_place = calc_bin_index(rad_char);
			_bin[track_place]->enqueue(sort[k]);			
		}
		
		counter = 0;  //used for index of the array of items
		
		//take items out of each bin
		for(int z = 0; z < q_num; z++)
		{
			//empty each queue
			while(!_bin[z]->isEmpty())
			{
				sort[counter] = _bin[z]->dequeue();
				counter++;
			}			
		}

	}

	//delete the bins
	for (int i = 0; i < q_num; i++) 
	{
		delete _bin[i];
	}
	
	delete[] _bin;
	
	//discard these
	delete sVal;
	delete b_str;
	delete created;
}

template < class T >
int RadixSort<T>::calc_bin_index(char rad)
{

	if(rad >= 48 && rad <= 57)          //for numbers
	{
		return (rad - 47);
	}
	else if(rad >= 65 && rad <= 90)		//for characters
	{
		return (rad - 54);
	}
	else if(rad >= 97 && rad <= 122)	//for characters
	{
		return (rad - 86);
	}
	else								//for special characters
	{
		return 0;
	}
}

#endif
