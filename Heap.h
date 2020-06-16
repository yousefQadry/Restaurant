#ifndef __HEAP_H_
#define __HEAP_H_
#include<iostream>
using namespace std;
#include"Generic_DS\Node.h"
#include"Rest\Order.h"



template<class T>
class Heap
{
private:

	T Arr[1000];
	int count;
	
public:
	Heap();
	bool isEmpty() const;
	void reheapup(int lastchild);
	void reheapdown(int y);
	void insert(T x);
	int getcount()const;
	void Removekey(T x);

};



template<class T>
Heap<T>:: Heap(){
	count =0 ;
}





template<class T>	
bool Heap<T>:: isEmpty() const{
	return count==0 ;	
}


template<class T>
void Heap<T>:: Removekey(T x){
	
	int indx=-1 ;
	for (int i = 0; i < count; i++)
	{
		if(Arr[i]==x)
			indx=i;
	}
	if(indx==-1)
		return ;

	T tmp=Arr[indx];
	Arr[indx]=Arr[count-1];
	Arr[count-1]=tmp ;
	count--;
	
	reheapdown(0);

}






template<class T>
void Heap<T>::reheapup(int lastchildindx){
	int hisparent = (lastchildindx-1)/2; 
	if(hisparent<0 || lastchildindx==hisparent)
		return ;

	if (Arr[lastchildindx] > Arr[hisparent])
	{
		T tmp= Arr[hisparent];
		Arr[hisparent]=Arr[lastchildindx];
		Arr[lastchildindx]=tmp;
	}
	reheapup(hisparent);

}








	template<class T>
void Heap<T>:: reheapdown(int firstparent){
	int firstchild =firstparent*2 +1;
	int secondchild =firstparent*2 +2;

	if (firstchild >= count)
	return ;
	

	if(Arr[firstparent] < Arr[firstchild]) 
	{
		T tmp= Arr[firstparent];
		Arr[firstparent]=Arr[firstchild];
		Arr[firstchild]=tmp ;
	}
	reheapdown(firstchild);

	if (secondchild >= count)
	return ;

	if(Arr[firstparent] < Arr[secondchild]) 
	{
		T tmp= Arr[firstparent];
		Arr[firstparent]=Arr[secondchild];
		Arr[secondchild]=tmp ;
	}
	reheapdown(secondchild);

}


template<class T>
void Heap<T>:: insert(T x){
	if (count==0){
	Arr[count]=x;
	count++ ;
	return ;
	}
	else if(count<1000){
	Arr[count]=x;
	count++ ;
	reheapup(count-1) ;
	}
}


template<class T>
int Heap<T>:: getcount()const{
	return count;
}















template<>
class Heap<Order*>
{
private:

	Order* Arr[1000];
	int count;
	
public:
	Heap();
	bool isEmpty() const;
	void reheapup(int lastchild);
	void reheapdown(int y);
	void insert(Order* x);
	void Removefirst(Order*&x);
	int getcount()const;
	bool RemoveVipWait(int x,Order*&);
	Order** toArray(int &x); 
};


template<>
class Heap<Cook*>
{
private:

	Cook* Arr[1000];
	int count;
	
public:
	Heap();
	bool isEmpty() const;
	void reheapup(int lastchild);
	void reheapdown(int y);
	void insert(Cook* x);
	int getcount()const;
	void Removefirst(Cook* &x);
	void getfirst(Cook* & x);
};







#endif