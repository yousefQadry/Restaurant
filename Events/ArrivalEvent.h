#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent : public Event
{
	//info about the order ralted to arrival event
	//    int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP	                
	double OrdMoney;	//Total order money
	int SIZE;
	int Arrtime;
	int autopromotion;
	int VIPwait ;
	/*
	Arrival event line have the following info
		❑ R(letter R in the beginning of its line) means an arrival event
		❑ TYP is the order type(N: normal, G : vegan, V : VIP)
		.❑ TS is the event timestep. (order arrival time)
		❑ ID is a unique sequence number that identifies each order.
		❑ SIZE is the number of dishes of the order
		❑ MONY is the total order money.
		*/
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int Size, double Money, int autop,int Vwait);


	/// MY CONSTRUCTOR (TS, ID, order_type, SIZE, MONY);

	//Add more constructors if needed


	void setOrderType(ORD_TYPE);
	ORD_TYPE getOrderType();
	void setOrdMoney(double);
	double getOrdMoney();
	virtual void Execute(Restaurant* pRest);	//override execute function

};

#endif	