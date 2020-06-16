#pragma once
#include"Events/Event.h"
class PromotionEvent :public Event
{
	double addedMoney;
public:
	PromotionEvent(int eTime, int ordID, double am);

	void Execute(Restaurant* prest);
};

