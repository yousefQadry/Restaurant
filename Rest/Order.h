#ifndef __ORDER_H_
#define __ORDER_H_
#include "..\Defs.h"
#include"Cook.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	double vippriority;
	int size;
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	
	Cook* mycook;
	int VIP_WT;
	

public:
	Order(int ID, ORD_TYPE r_Type);

	Order(int ID, ORD_TYPE r_Type, int at, int s, int tm,int od,int vipwait);

	virtual ~Order();

	void setcook(Cook* x) ;


	int getArrtime()const;
	int getServtime()const;
	int getFinishtime()const;

	void setArrtime(int x);
	void setServtime(int x);
	void setFinishtime(int x);

	Cook* getmycook()const; 

	int GetID();
	int GetSize()const;

	void SetType(ORD_TYPE);
	ORD_TYPE GetType() const;

	void SetSize(int);

	void SetTotalMoney(double);
	double GetTotalMoney() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;

	void setvipPriority();
	double GetvipPriority() const;


	int getvipwait() const;



};

#endif