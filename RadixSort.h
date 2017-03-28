#if !defined (NULL)
   #define NULL 0
#endif

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
		
		static int asc_index(char rad);
		
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
	int x = 0;
	while(x < num_to_sort)
	{
		radix_sorted_array[x] = unsorted[x];
		x++;
	}
	
	//execute the specified sorting function
	if(!asc) radixSortDesc(radix_sorted_array, num_to_sort, num_chars, getRadixChar);
	else radixSortAsc(radix_sorted_array, num_to_sort, num_chars, getRadixChar);		
	
	return radix_sorted_array;

}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{

	//if(num_chars < 0 || n < 0 || sort == NULL) return;
	
	QueueLinked<T>* bin_sort_bin = new QueueLinked<T>();  //creates a queue for binsort
	
	//enqueues all the items in array
	int x = 0;
	while(x < n)
	{
		bin_sort_bin->enqueue(sort[x]);
		x++;
	}
	
	binSort(bin_sort_bin, 1, num_chars, getRadixChar);  //calls binsort to deal with first character first
	
	//puts sorted items back into the array
	x = 0;
	while(x < n)
	{
		sort[x] = bin_sort_bin->dequeue();
		x++;
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
	int x = 0;
	while(x < 37)
	{
		_bin[x] = new QueueLinked<T>();
		x++;
	}
	
	//get items from bin and put them in 37 bins
	while(!bin->isEmpty())
	{
		T* item = bin->dequeue();
		_bin[asc_index((*getRadixChar)(item, curr_char))]->enqueue(item);
	}
	
	//checks all bins
	x = 0;
	while(x < q_num)
	{
		//check for more that one item in bin
		if(_bin[x]->size() > 1) binSort(_bin[x], curr_char + 1, num_chars, getRadixChar);  //recursivly call binsort
		
		while(!_bin[x]->isEmpty())
		{
			bin->enqueue(_bin[x]->dequeue()); 
		}
		delete _bin[x];  //delete each bin
		x++;
	}
	
	delete[] _bin;
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
	if(num_chars < 0 || n < 0 || sort == NULL) return;
	
	int q_num = 37;  //covers letters and digits
	int counter = 0;
	
	QueueLinked<T>** _bin = new QueueLinked<T>*[37];  
	
	//must instantiate each of the queues
	int x = 0;
	while(x < 37)
	{
		_bin[x] = new QueueLinked<T>();
		x++;
	}
	
	//go through max number of characters
	x = num_chars;
	while(x > 0)  //number of times to bin stuff
	{
		//put each word in bin
		int y = 0;
		while(y < n)
		{
			_bin[asc_index((*getRadixChar)(sort[y],x))]->enqueue(sort[y]);
			y++;
		}
		
		int a = 0;  //used for index of the array of items
		int z = 36;
		//take items out of each bin
		while(z >= 0)
		{
			//empty each queue
			while(!_bin[z]->isEmpty())
			{
				sort[a] = _bin[z]->dequeue();
				a++;
			}			
			z--;
		}
		x--;
	}

	//delete the bins
	x = 0;
	while (x < 37) 
	{
		delete _bin[x];
		x++;
	}
	delete[] _bin;
}

template < class T >
int RadixSort<T>::asc_index(char rad)
{
	if(rad >= 48 && rad <= 57) return (rad - 47);
	else if(rad >= 65 && rad <= 90)	return (rad - 54);
	else if(rad >= 97 && rad <= 122) return (rad - 86);
	else return 0;
}


#endif



