#pragma once

#include "..\Defs.h"

class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	float speed;		//dishes it can prepare in one clock tick (in one timestep)
	int restfinishtime;
	int ORDERSTOBREAK;
	int ordersDone;
	int timeatwhichhegoesbreak;
	int timeatwhichbreakfinish;
	bool urgent;

	int timeinbreak;


	//int CountInjuries;
	bool injured;
	
	enum
	{
		free ,
		cooking ,
		in_break
	}state;


public:
	
	
	Cook(int id, ORD_TYPE rtype, int s);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	void setSpeed(int s);
	int getSpeed() const;

	void setOrderstoBreak(int x);
	int getOrderstoBreak();
	void incrementordersdone(); 
	void setState(int x);
	int getState();
	int getOrdersdone();
	void resetordersdone();
	
	void setbreakperiod(int x);
	void settimeatwhichhegoesbreak(int x);
	int gettimeatwhichhegoesbreak()const;
	void settimeatwhichbreakfinish();
	int gettimeatwhichbreakfinish()const;
	void setbreakfinish(int ts);
	void setrestfinishtime(int x);
	int getrestfinishtime();
	void seturgent(bool x);
	bool geturgent()const;

	
	bool HEproblems(float);
	bool IsInjured();
	void recover();



};



/*
#pragma once

#include "..\Defs.h"

class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int ORDERSTOBREAK ;
	int timeinbreak; 
	int ordersdone;

public:
	void setBreaktime (int x);
	void setOrderstoBreak(int y);
	Cook(int id, ORD_TYPE rtype, int s);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	void setSpeed(int s);
	int getSpeed() const;
	int getBreaktime();
	int getOrderstoBreak();
	int getordersdone();
	void incrementordersdone();
};
*/