#include"Heap.h"

	Heap<Order*>::Heap(){
		count=0;
	}

	bool Heap<Order*>::isEmpty() const{
		return count==0;
	}
	int Heap<Order*>::getcount()const{
		return count; 
	}

	void Heap<Order*>::reheapup(int lastchildindx){
		
	//	if(Arr[lastchildindx]->getStatus()==WAIT){

		int hisparent = (lastchildindx-1)/2; 
	if(hisparent<0 || lastchildindx==hisparent)
		return ;

	if (Arr[lastchildindx]->GetvipPriority() > Arr[hisparent]->GetvipPriority())
	{
		Order* tmp= Arr[hisparent];
		Arr[hisparent]=Arr[lastchildindx];
		Arr[lastchildindx]=tmp;
	}
	reheapup(hisparent);
//		}
		
		/// Spare for Priority Queue
		/*else if(Arr[lastchildindx]->getStatus()==SRV){

		int hisparent = (lastchildindx-1)/2; 
	if(hisparent<0 || lastchildindx==hisparent)
		return ;

	if (Arr[lastchildindx]->getFinishtime() < Arr[hisparent]->getFinishtime())
	{
		Order* tmp= Arr[hisparent];
		Arr[hisparent]=Arr[lastchildindx];
		Arr[lastchildindx]=tmp;
	}
	reheapup(hisparent);

	}
	*/
	
	}


	void Heap<Order*>::reheapdown(int firstparent){
	
		int firstchild =firstparent*2 +1;
	int secondchild =firstparent*2 +2;

	if (firstchild >= count)
	return ;
	

	if(Arr[firstparent]->GetvipPriority() < Arr[firstchild]->GetvipPriority()) 
	{
		Order* tmp= Arr[firstparent];
		Arr[firstparent]=Arr[firstchild];
		Arr[firstchild]=tmp ;
	}
	reheapdown(firstchild);

	if (secondchild >= count)
	return ;

	if(Arr[firstparent]->GetvipPriority() < Arr[secondchild]->GetvipPriority()) 
	{
		Order* tmp= Arr[firstparent];
		Arr[firstparent]=Arr[secondchild];
		Arr[secondchild]=tmp ;
	}
	reheapdown(secondchild);


	}
	
	
	void Heap<Order*>::insert(Order* x){
	if(count<1000){
		Arr[count]=x;
		count++ ;
		reheapup(count-1) ;
	}
	}

	void Heap<Order*>::Removefirst(Order* &x){
	x=Arr[0];
	if(count==1)
	{
		count--;
		
		return ;
	}
	Arr[0]=Arr[count-1];
	Arr[count-1]=x;
	count--;
	reheapdown(0);
	}

	//// Will send x in Restaurant X=Current time step
	// Return bool true if there's still another Order needed to be removed 
	// I've done that because i need each order removed so must send one each time
	bool Heap<Order*>::RemoveVipWait(int x,Order* &ord){
	bool found=0 ;
	int countthem=0;
	ord=nullptr;
	for (int i = 0; i < count; i++)
	{
		// X is current time step sent
		if((x-Arr[i]->getArrtime())>=Arr[i]->getvipwait() && countthem==0){
		ord=Arr[i];
		Arr[i]=Arr[count-1];
		Arr[count-1]=ord ;
		count--;
		found=1;
		countthem++;
		}else if((x-Arr[i]->getArrtime())>=Arr[i]->getvipwait()) // to get a feed that there's more
			countthem++;
	}

	if(found)
	reheapdown(0);
	
	return countthem>1;
	}


	Order** Heap<Order*>:: toArray(int &x)
	{
		x=count; 
		Order** A=new Order* [count];

		for (int i = 0; i < count; i++)
		{
			A[i]=Arr[i];
		}

		for (int i = 0; i < count; i++)
		{
			int indx=i ;
			for (int j = i-1; j >=0; j--)
			{
				if (A[indx]->GetvipPriority() > A[j]->GetvipPriority())
				{
					Order* tmp=A[j];
					A[j]=A[indx];
					A[indx]=tmp ;
				}
			}

		}
		return A; 
	}

	//////////////////////////////////////////////////////////////////////////////////////////



void Heap<Cook*>::reheapup(int lastchildindx){
	int hisparent = (lastchildindx-1)/2; 
	if(hisparent<0 || lastchildindx==hisparent)
		return ;

	if (Arr[lastchildindx]->gettimeatwhichbreakfinish() < Arr[hisparent]->gettimeatwhichbreakfinish())
	{
		Cook* tmp= Arr[hisparent];
		Arr[hisparent]=Arr[lastchildindx];
		Arr[lastchildindx]=tmp;
	}
	reheapup(hisparent);
}


void Heap<Cook*>:: reheapdown(int firstparent){
	int firstchild =firstparent*2 +1;
	int secondchild =firstparent*2 +2;

	if (firstchild >= count)
	return ;
	

	if(Arr[firstparent]->gettimeatwhichbreakfinish() > Arr[firstchild]->gettimeatwhichbreakfinish()) 
	{
		Cook* tmp= Arr[firstparent];
		Arr[firstparent]=Arr[firstchild];
		Arr[firstchild]=tmp ;
	}
	reheapdown(firstchild);

	if (secondchild >= count)
	return ;

	if(Arr[firstparent]->gettimeatwhichbreakfinish() > Arr[secondchild]->gettimeatwhichbreakfinish()) 
	{
		Cook* tmp= Arr[firstparent];
		Arr[firstparent]=Arr[secondchild];
		Arr[secondchild]=tmp ;
	}
	reheapdown(secondchild);

}


void Heap<Cook*>::getfirst(Cook* & x){
	if (count==0)
	{
		x=nullptr;
	}else
	x=Arr[0];
}


Heap<Cook*>:: Heap(){
	count =0 ;
	for (int i = 0; i < 1000; i++)
	{
		Arr[i]=nullptr;
	}
}


bool Heap<Cook*>:: isEmpty() const{
	return count==0 ;	
}


void Heap<Cook*>:: Removefirst(Cook* &x){
	if (count==0)
	return ;
	
	x=Arr[0];
	if(count==1)
	{

		count--;
		return ;
	}
	Arr[0]=Arr[count-1];
	Arr[count-1]=x;
	count--;
	reheapdown(0);
}



void Heap<Cook*>:: insert(Cook* x){
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


int Heap<Cook*>:: getcount()const{
	return count;
}






