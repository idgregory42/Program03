#if !defined NULL
#define NULL 0
#endif

#if !defined (QUEUEDEQUE_H)
#define QUEUEDEQUE_H

#include "DequeArray.h"

template < class T >
class QueueDeque
{
	
	private:
	
		DequeArray<T>* dqA;
	
	public:
	
		QueueDeque();
		~QueueDeque();

		bool isEmpty();
		int size();
		void dequeueAll(); 

		T* peek();
		T* dequeue();
		void enqueue(T* item);
	
	
	
};

template < class T >
QueueDeque<T>::QueueDeque()
{
	dqA = new DequeArray<T>();
}

template < class T >
QueueDeque<T>::~QueueDeque()
{
	dqA->~DequeArray();
}

template < class T >
bool QueueDeque<T>::isEmpty()
{
	return size() == 0;
}

template < class T >
int QueueDeque<T>::size()
{
	return dqA->size();
}

template < class T >
void QueueDeque<T>::dequeueAll()
{
	dqA->dequeueAll();
}

template < class T >
T* QueueDeque<T>::peek()
{
	return dqA->peek();
}

template < class T >
T* QueueDeque<T>::dequeue()
{
	return dqA->dequeue();
}

template < class T >
void QueueDeque<T>::enqueue(T* item)
{
	dqA->enqueue(item);
}



#endif