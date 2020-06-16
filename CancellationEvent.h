#pragma once

#include"Events/Event.h"
class CancellationEvent :public Event
{
	bool succeeded;
public:
	CancellationEvent(int time, int id);

	void Execute(Restaurant* pRest);

	bool Success();
};

