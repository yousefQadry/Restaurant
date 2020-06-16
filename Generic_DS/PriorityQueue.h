#ifndef __PRIORITYQUEUE_H_
#define __PRIORITYQUEUE_H_

#include"Node.h"
#include"..\Rest\Order.h"



template<class T>
class PriorityQueue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	int getcount()const;
	~PriorityQueue();

	
	T* toArray(int& count);
	
};



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/
template <typename T>
T* PriorityQueue<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template<class T>
int PriorityQueue<T>::getcount()const {
	return count;
}


template<class T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template<class T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template<class T>
bool PriorityQueue<T>::enqueue(const T& newEntry)
{
Node<T>* newNodePtr = new Node<T>(newEntry);
// Insert the new node
if (isEmpty())
frontPtr = newNodePtr; // The queue is empty
else
backPtr->setNext(newNodePtr); // The queue was not empty
count++;
backPtr = newNodePtr; // New node is at back
return true;
}
/*
template<class T>
bool PriorityQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* tmp = frontPtr;
	Node<T>* newNodePtr = new Node<T>(newEntry);
	count++;
	// Insert the new node
	if (isEmpty()) {
		frontPtr = backPtr = newNodePtr; // The queue is empty
		return 1;
	}
	if (tmp == frontPtr && newNodePtr > tmp) {
		newNodePtr->setNext(tmp);
		frontPtr = newNodePtr;
		return 1;
	}

	while (tmp->getNext() != nullptr)
	{
		if (newNodePtr > tmp) {
			newNodePtr->setNext(tmp->getNext());
			tmp->setNext(newNodePtr);
		}
		else {
			tmp = tmp->getNext();
			continue;
		}
	}

	if (!tmp->getNext())
	{
		tmp->setNext(newNodePtr);
		backPtr = newNodePtr;
		return 1;
	}
	// checking backptr;
	while (tmp != nullptr)
	{
		if (tmp->getNext() == nullptr)
		{
			backPtr = tmp;
			return 1;
		}

		tmp = tmp->getNext();
	}
	return 1;
} // end enqueue
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/


template<class T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;
	count--;
	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/

template<class T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/


template<>
class PriorityQueue<Order*>
{
private:

	Node<Order*>* backPtr;
	Node<Order*>* frontPtr;
	int count ;

public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(Order*& newEntry);
	bool dequeue(Order*& frntEntry);
	bool peekFront(Order*& frntEntry)  const;
	int getcount()const;
	~PriorityQueue();

//	void VipWait();

	Order** toArray(int& count);
	
};

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/






#endif
