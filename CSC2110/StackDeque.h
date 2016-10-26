#if !defined NULL
#define NULL 0
#endif


#if !defined (STACKDEQUE_H)
#define STACKDEQUE_H

#include "DequeArray.h"

template < class T>
class StackDeque
{
	private:
		
		DequeArray<T>* dqA;
	
	public:
	
		StackDeque();
		~StackDeque();
		
		int size();
		
		bool isEmpty();
		
		T* peek();
		T* pop();
		
		void popAll();
		void push(T* item);
};

template < class T >
StackDeque<T>::StackDeque()
{
	dqA = new DequeArray<T>(); 
}

template < class T >
StackDeque<T>::~StackDeque()
{
	delete dqA;
}

template < class T >
int StackDeque<T>::size()
{
	return dqA->size();
}

template < class T >
bool StackDeque<T>::isEmpty()
{
	return size() == 0;  
}

template < class T >
T* StackDeque<T>::peek()
{
	return dqA->peekDeque(); 
}

template < class T >
T* StackDeque<T>::pop()
{
	return dqA->dequeueDeque(); 
}

template < class T >
void StackDeque<T>::popAll()
{
	 
}

template < class T >
void StackDeque<T>::push(T* item)
{
	dqA->enqueue(item); 
}



#endif