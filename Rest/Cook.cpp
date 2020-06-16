#include "Cook.h"
#include <cstdlib>

Cook::Cook(int id, ORD_TYPE rtype, int s)
{
	setID(id);
	setType(rtype);
	setSpeed(s);
	ordersDone = 0;
	restfinishtime=0;
	urgent=false;
}


void Cook::setOrderstoBreak(int x)
{
	ORDERSTOBREAK = x > 0 ? x : 0;

}
int Cook::getOrderstoBreak()
{
	return ORDERSTOBREAK;
}

void Cook::incrementordersdone()
{
	ordersDone++;
}

void Cook::setState(int x)
{
	if (x == 0)
		state = free;
	else if (x == 1)
		state = cooking;
	else if (x == 2)
		state = in_break;
	
}

int Cook::getState()
{
	return state;
}

int Cook::getOrdersdone()
{
	return ordersDone;
}

	void Cook:: resetordersdone(){
		ordersDone=0;
	}


Cook::~Cook()
{
}
void Cook::setSpeed(int s)
{
	speed = s > 0 ? s : 0;
}
int Cook::getSpeed() const
{
	return speed;
}

int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

bool Cook::HEproblems(float prob)
{
	int r = (rand() % 100) + 1;
	if (injured == false && r <= prob * 100 )
	{
		setSpeed((double)speed / 2);
		injured = true;
		return true;
	}
	else {
		return false;
	}
	
}

bool Cook::IsInjured()
{
	return injured;
}

void Cook::recover()
{
	speed =speed * 2;
	injured = false;
}


void Cook::setbreakperiod(int x){
		timeinbreak=x;
	}

	void Cook::settimeatwhichhegoesbreak(int x){
		timeatwhichhegoesbreak=x;
	}
	

	int Cook::gettimeatwhichhegoesbreak()const{
		return timeatwhichhegoesbreak;
	}
	void Cook:: settimeatwhichbreakfinish(){
		timeatwhichbreakfinish=timeatwhichhegoesbreak+timeinbreak;
	}
	
	int Cook::gettimeatwhichbreakfinish()const{
		return timeatwhichbreakfinish;
	}

	void Cook::setbreakfinish(int ts)
	{
		timeatwhichbreakfinish = ts;
	}

		void Cook::setrestfinishtime(int x){
			restfinishtime=x;
		}
	int Cook::getrestfinishtime(){
		return restfinishtime;
	}
	void Cook::seturgent(bool x){
		urgent=x;
	}
	bool Cook::geturgent()const{
		return urgent;
	}