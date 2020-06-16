#include"PriorityQueue.h"


Order** PriorityQueue<Order*>::toArray(int& count) {

	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<Order*>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	Order** Arr = new Order *[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;


}

PriorityQueue<Order*>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count=0 ;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/

bool PriorityQueue<Order*>::isEmpty() const
{
	return count==0;
}



int PriorityQueue<Order*>::getcount()const {
	return count;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/



bool PriorityQueue<Order*>::enqueue(Order*& newEntry)
{
	if (newEntry->getStatus() == WAIT) {

		Node<Order*>* tmp = frontPtr;
		Node<Order*>* newNodePtr = new Node<Order*>(newEntry);
		count++;
		// Insert the new node
		if (isEmpty()) {
			frontPtr = backPtr = newNodePtr;
			// The queue is empty
			return 1;
		}
		if (tmp == frontPtr && newNodePtr->getItem()->GetvipPriority() > tmp->getItem()->GetvipPriority()) {
			newNodePtr->setNext(tmp);
			frontPtr = newNodePtr;
			return 1;
		}
		
		while (tmp->getNext() != nullptr)
		{
			if (newNodePtr->getItem()->GetvipPriority() > tmp->getNext()->getItem()->GetvipPriority()) {
				newNodePtr->setNext(tmp->getNext());
				tmp->setNext(newNodePtr);
				return 1;
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
	else if (newEntry->getStatus() == SRV) {
		Node<Order*>* tmp = frontPtr;
		Node<Order*>* newNodePtr = new Node<Order*>(newEntry);
		



		if (isEmpty()) {
			frontPtr = backPtr = newNodePtr;
			count++;
			return 1;
		}


		if (frontPtr->getItem()->getFinishtime() > newEntry->getFinishtime() ) {
			newNodePtr->setNext(tmp);
			frontPtr = newNodePtr;
			count++;

			return 1;	
		}
		else{
		while (tmp->getNext() != nullptr)
		{
			int time1=newNodePtr->getItem()->getFinishtime() ;
			int time2=tmp->getNext()->getItem()->getFinishtime() ;
		if (time1 < time2) {
				newNodePtr->setNext(tmp->getNext());
				tmp->setNext(newNodePtr);
				count++;
				return 1;
			}
			else {
				tmp = tmp->getNext();
				continue;
			}
		}

	}
		if (!tmp->getNext())
		{
			tmp->setNext(newNodePtr);
			backPtr = newNodePtr;
			count++;
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
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/


bool PriorityQueue<Order*>::dequeue(Order*& frntEntry)
{
	if (isEmpty())
		return false;
	count--;
	Node<Order*>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (isEmpty())	 // Special case: one node in queue
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

bool PriorityQueue<Order*>::peekFront(Order*& frntEntr) const
{
	if (isEmpty()){
		frntEntr=nullptr;
		return false;
	}
	frntEntr = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

PriorityQueue<Order*>::~PriorityQueue()
{
}
