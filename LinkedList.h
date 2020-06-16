#ifndef _LINKEDLIST
#define _LINKEDLIST

#include"Generic_DS/Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	
	bool isEmpty(){
		return Head==nullptr;
	}
	
	
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		Node<T>* p = Head;
		Node<T>* ins = new Node<T>(data);

		if (!p) {
			Head = ins;
			return;
		}

		while (p->getNext() != nullptr) {
			p = p->getNext();
		}

		p->setNext(ins);
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key) {
		Node<T>* p = Head;
		if (!p)
			return false;

		while (p) {
			if (p->getItem() == Key)
				return true;
			p = p->getNext();
		}
		return false;

	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value) {
		int z = 0;
		Node<T>* p = Head;
		if (!p)
			return false;

		while (p) {
			if (p->getItem() == value)
				z++;
			p = p->getNext();
		}
		return z;

	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst() {
		Node<T>* p = Head;
		if (!p)
			return;

		Head = Head->getNext();
		delete p;
		p = nullptr;

	}

	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast() {
		Node<T>* p = Head;
		if (!p)
			return;

		if (p->getNext() == nullptr) {
			DeleteFirst();
			return;
		}


		while (p->getNext()->getNext() != nullptr)
			p = p->getNext();

		Node<T>* tmp = p->getNext();
		p->setNext(nullptr);
		delete tmp;

	}
	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value) {
		Node<T>* p = Head;
		if (!p)
			return false;

		if (p->getItem() == value) {
			DeleteFirst();
			return 1;
		}

		while (p->getNext() != nullptr)
		{
			if (p->getNext()->getItem() == value) {
				Node<T>* del = p->getNext();
				p->setNext(del->getNext());
				delete del;
				del = nullptr;
				return 1;
			}
			p = p->getNext();
		}
		return false;

	}

	T RemoveNode(const T& value) {
		Node<T>* p = Head;
		if (!p)
			return nullptr;

		if (p->getItem() == value) {
			Node<T>* del =Head;
			Head=Head->getNext();
			T x=del->getItem();
			delete del ;
			return x;
		}

		while (p->getNext() != nullptr)
		{
			if (p->getNext()->getItem() == value) {
				Node<T>* del = p->getNext();
				p->setNext(del->getNext());
				T x=del->getItem();
				delete del ;
				return x;
			}
			p = p->getNext();
		}
		return nullptr;
	}


	


	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value) {

		bool z = false;
		z = DeleteNode(value);
		while (z) {
			z = false;
			z = DeleteNode(value);
		}
		return z;

	}
	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L) {

		Node<T>* p = Head;
		if (!p)
		{
			return;
		}

		while (p->getNext() != nullptr)
		{
			p = p->getNext();
		}

		if (!L.Head)
			return;
		Node<T>* tmp = L.Head;

		while (tmp->getNext() != nullptr)
		{
			InsertEnd(tmp->getItem());
			tmp = tmp->getNext();
		}

	}
	// Get Node
	


	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		if (!Head)
			return;
		if (!Head->getNext())
			return;


		Node<T>* p = Head->getNext();

		Node<T>* tmp = p->getNext();
		Head->setNext(nullptr);
		while (p)
		{
			p->setNext(Head);
			Head = p;
			p = tmp;
			if (tmp != nullptr)
				tmp = tmp->getNext();
		}

	}


};

#endif	
