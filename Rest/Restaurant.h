#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"fstream"
#include "Order.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"..\\LinkedList.h"
#include"..\\Heap.h"
// it is the maestro of the project
class Restaurant
{
private:

	GUI* pGUI;
	Event* previousevent;

	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	Heap<Order*> VipOrders;
	Queue<Order*> NormalOrders;
	Queue<Order*> VeganOrders;
	
	Queue<Order*> FinishedOrders;
	Queue<Cook*> NormalCooks;
	Queue<Cook*> VipCooks;
	Queue<Cook*> VeganCooks;

	PriorityQueue<Order*>InserviceOrders;
	LinkedList<Cook*> Busycooks;
	
	//PriorityQueue<Cook*> BusyCooks;
	
	Heap<Cook*> BreakNormalCooks;
	Heap<Cook*> BreakVeganCooks;
	Heap<Cook*> BreakVipCooks;
	int autop;

	Queue<Cook*> InjuredCooks;
	float InjProb;
	int rstPrd;

	int CurrentTimestep;
	int CountInjuires;

	int urgentorderscount;
	int autopromotedcount;
	
public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void AddOrder(Order*);
	bool DeleteOrder(int id);
	bool PromoteOrder(int id, int am);

	
	
	bool UrgentServe(Order *);
	void IsInjured();
	void Autopromote() ;
	bool PromoteEvent(int id, int am);

	void FillDrawingList();
	void AddEvent(Event*);
	bool ReadInputFile();
	
	void UpdateVip();
	void MoveCook(Cook* coming);
	void ServeOrder() ;
	void FinishOrder() ;
	void FinishBreak();
	void SaveFile();

	void DeleteCooks();
	void DeleteFinished();
	bool DeleteEvent(int id);


};

#endif