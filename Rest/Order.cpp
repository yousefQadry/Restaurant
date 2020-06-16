#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	setvipPriority();
	mycook = nullptr;   

	ServTime=0;
}



Order::Order(int id, ORD_TYPE r_Type, int at, int s, int tm,int ap,int vpwait)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	ArrTime = at;
	size = s;
	totalMoney = tm;
	setvipPriority();
	
	mycook = nullptr;
	
	VIP_WT=vpwait;
		
}


int Order:: getvipwait() const{
	return VIP_WT;
}

Cook* Order:: getmycook()const{
	return mycook;
}


Order::~Order()
{
}

int Order::getArrtime() const
{
	return ArrTime;
}

int Order::getServtime() const
{
	return ServTime;
}
int Order::getFinishtime() const
{
	return FinishTime;
}

void Order::setArrtime(int x ){
		ArrTime=x;
	}

void Order::setServtime(int x){
		ServTime=x;
	}
void Order::setFinishtime(int x){
		FinishTime=x;
	}


void Order::SetTotalMoney(double tm)
{
	totalMoney = tm > 0 ? tm : totalMoney;
}


void Order::SetType(ORD_TYPE ot)
{
	type = ot;
}

void Order::SetSize(int s)
{
	size = s > 0 ? s : size;
}



int Order::GetID()
{
	return ID;
}

int Order::GetSize()const
{
	return size;
}

double Order::GetTotalMoney() const
{
	return totalMoney;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


	void Order:: setcook(Cook* x) {
		mycook=x;  
	}

void Order::SetDistance(int d)
{
	Distance = d > 0 ? d : 0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::setvipPriority()
{
	if (this->GetType() == TYPE_VIP) {
		vippriority = (0.4 * totalMoney) - (0.2 * ArrTime) + (0.4 * size);
	}else
		vippriority = -1;
}

double Order::GetvipPriority() const
{
	return this->vippriority;
}