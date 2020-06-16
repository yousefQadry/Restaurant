#include "CancellationEvent.h"
#include"Rest/Restaurant.h"

CancellationEvent::CancellationEvent(int eTime, int ordID) :Event(eTime, ordID)
{
	succeeded = 0;
}


void CancellationEvent::Execute(Restaurant* pRest)
{
	succeeded=pRest->DeleteOrder(OrderID);	
}


bool CancellationEvent::Success() {
	return succeeded;
}