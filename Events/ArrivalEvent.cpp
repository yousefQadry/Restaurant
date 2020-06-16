#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int s, double mon,int autop=0,int Vipw=0) :Event(eTime, oID)
{
	OrdType = oType;
	SIZE = s;
	OrdMoney = mon;
	EventTime = eTime;
	autopromotion=autop;
	VIPwait=Vipw;
	Arrtime=eTime;
}

void ArrivalEvent::setOrderType(ORD_TYPE ot)
{
	OrdType = ot;
}

ORD_TYPE ArrivalEvent::getOrderType()
{
	return OrdType;
}

void ArrivalEvent::setOrdMoney(double om)
{
	OrdMoney = om > 0 ? om : OrdMoney;
}

double ArrivalEvent::getOrdMoney()
{
	return OrdMoney;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID, OrdType, Arrtime, SIZE, OrdMoney,autopromotion,VIPwait);
	
	pRest->AddOrder(pOrd);
}
