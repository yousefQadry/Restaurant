#include "PromotionEvent.h"
#include"Rest/Restaurant.h"
PromotionEvent::PromotionEvent(int eTime, int ordID, double am) :Event(eTime, ordID)
{
	addedMoney = am > 0 ? am : 0;
}

void PromotionEvent::Execute(Restaurant* prest)
{
	if (!prest->PromoteEvent(OrderID, addedMoney))
	{
		prest->PromoteOrder(OrderID, addedMoney);
	}
}