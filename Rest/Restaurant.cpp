#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\PromotionEvent.h"
#include"..\\CancellationEvent.h"


Restaurant::Restaurant()
{
	pGUI = NULL;
	CurrentTimestep = 0;
	previousevent = nullptr;
	autopromotedcount=urgentorderscount=0;	

	CountInjuires=0;
}

void Restaurant::IsInjured()
{
	//PriorityQueue<Order*> so;
	Order* otemp;

	if (InserviceOrders.peekFront(otemp) && !InserviceOrders.isEmpty())
	{
		bool x = otemp->getmycook()->HEproblems(InjProb);
		if (x)
		{
			int TimeToComplete = (otemp->getFinishtime() - otemp->getServtime());
			int TimeAlreadyCompleted = (CurrentTimestep - otemp->getServtime());
			float pTAC = float(TimeAlreadyCompleted / TimeToComplete) !=1 ? float(TimeAlreadyCompleted / TimeToComplete):0;
			int NewFinishTime = ceil((1 - pTAC) * (TimeToComplete * 2) + otemp->getServtime());
			otemp->setFinishtime(NewFinishTime);
			InserviceOrders.dequeue(otemp);
			CountInjuires++;
		}
		else
			return ;//so.enqueue(otemp);
	}
	if(otemp)
	InserviceOrders.enqueue(otemp);
	/*InserviceOrders = so;*/
}





bool Restaurant::ReadInputFile()
{

	ifstream Project;
	//	char Filename[50];
	//	cin.getline(Filename, 50);
	pGUI->PrintMessage("Please Enter Input Filename in the form (Name.txt) Please !");

	string xx = pGUI->GetString();

	Project.open(xx);
	pGUI->ResetLines();

	if (!Project.is_open())
		return 0;

	/// this function return 0 so must check in its place if zero returned to EXIT !


	float arr[21];

	int i = 0;
	for (int i = 0; i < 21; i++)
	{
		Project >> arr[i];
	}

	InjProb = arr[16];
	rstPrd = arr[17];


	int bo = arr[9];

	char x;

int cookco=0;
	//// DOOOL KDDAAA SPEEED
	int snmin = arr[3];
	int snmax = arr[4];
	int bnmin = arr[10], bnmax = arr[11];
	for (int i = 0; i < arr[0]; i++)
	{
		
		int sn =  rand() % snmax;
		int bn = rand() % bnmax;
		if(sn < snmin)
			sn+=snmin;
		if(bn < bnmin)
			bn+=bnmin;


		// hot variable ya adry fel arr[3]; w nafs kalam b3d kda
		Cook* tmp = new Cook(++cookco, TYPE_NRM, sn);
		tmp->setbreakperiod(bn);
		tmp->setOrderstoBreak(bo);
		//tmp->setordersbeforebreak(arr[9]);
		//	tmp->setBreakduration(arr[7]);
		NormalCooks.enqueue(tmp);
	}

	//READING ALL VEGAN INFORMATION
	
	int sveganmin = arr[5], sveganmax = arr[6];
	int bveganmin = arr[12], bveganmax = arr[13];
	for (int i = 0; i < arr[1]; i++)
	{

		srand(time(0));
		int sv = rand() % sveganmax;
		int bv = rand() % bveganmax;
		if(sv < sveganmin)
			sv+=sveganmin;
		if(bv < bveganmin)
			bv+=bveganmin;

		Cook* tmp = new Cook(++cookco, TYPE_VGAN, sv);
		tmp->setbreakperiod(bv);
		tmp->setOrderstoBreak(bo);
		//	tmp->setBreakduration(arr[8]);
		//tmp->setordersbeforebreak(arr[9]);
		VeganCooks.enqueue(tmp);
	}
	//READING ALL VIP INFORMATION

	int bvipmin = arr[14], bvipmax = arr[15];
	int svipmin = arr[7], svipmax = arr[8];
	for (int i = 0; i < arr[2]; i++)
	{
		srand(time(0));
		int svip =  rand() % svipmax;
		int bvip = rand() % bvipmax;
		if(svip < svipmin)
			svip+=svipmin;
		if(bvip < bvipmin)
			bvip+=bvipmin;
		Cook* tmp = new Cook(++cookco, TYPE_VIP, svip);
		tmp->setbreakperiod(bvip);
		tmp->setOrderstoBreak(bo);
		//tmp->setBreakduration(arr[0]);
		//tmp->setordersbeforebreak(arr[9]);
		VipCooks.enqueue(tmp);
	}


	

	for (int i = 0; i < arr[20]; i++)
	{
		Project >> x;
		char Y;
		ORD_TYPE order_type;
		int TS, ID, SIZE, MONY;
		autop=arr[18];
		int VIPwait=arr[19];
		switch (x)
		{
		case('R'):
		{
			Project >> Y;
			if (Y == 'N'){
				order_type = TYPE_NRM;
				autop=arr[18];
			}else if (Y == 'G')
				order_type = TYPE_VGAN;
			else if (Y == 'V'){
				order_type = TYPE_VIP;
			}
			Project >> TS >> ID >> SIZE >> MONY;
			ArrivalEvent* E = new ArrivalEvent(TS, ID, order_type, SIZE, MONY,autop,VIPwait);
			
			EventsQueue.enqueue(E);
		}
		break;
		case('X'):
		{
			Project >> TS >> ID;
			CancellationEvent* CE = new CancellationEvent(TS, ID);
			EventsQueue.enqueue(CE);
		}
		break;
		case('P'):
		{double ExtraMoney;
		Project >> TS >> ID >> ExtraMoney;
		PromotionEvent* PE = new PromotionEvent(TS, ID, ExtraMoney);
		EventsQueue.enqueue(PE);
		}
		break;

		default:
			break;
		};
	}
	return 1;
}


	bool Restaurant::UrgentServe(Order * tst){
		if(!tst || tst->GetType()!=TYPE_VIP )
			return 0;

		Cook* cooker=nullptr;
		
		if (VipCooks.peekFront(cooker))
		{
			VipCooks.dequeue(cooker);
			tst->setcook(cooker);
			tst->setServtime(CurrentTimestep);
			tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
			cooker->incrementordersdone();
			Busycooks.InsertBeg(cooker);
			tst->setStatus(SRV);
			InserviceOrders.enqueue(tst);
			
		}else if( VipCooks.isEmpty())
			{
				if(!NormalCooks.isEmpty())
				{
					NormalCooks.dequeue(cooker);
					tst->setcook(cooker);
								tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
								tst->setServtime(CurrentTimestep);
								cooker->incrementordersdone();
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
					
				}else if (!VeganCooks.isEmpty())
				{
					VeganCooks.dequeue(cooker);
					tst->setcook(cooker);
					tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
					tst->setServtime(CurrentTimestep);
					cooker->incrementordersdone();
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
					
				}
			}

		if (cooker){
		urgentorderscount++;
		cooker->seturgent(1);
		return 1;
		
		}else		/// Still not done so will go for break cooks
		{
			if (!BreakVipCooks.isEmpty())
			{
					BreakVipCooks.Removefirst(cooker) ;
					tst->setcook(cooker);
					tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
					tst->setServtime(CurrentTimestep);
					cooker->resetordersdone();
					cooker->incrementordersdone();
					/// Lazem ne3raf hayerga3 tany wla eh elkalam
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
					
			}
			else if (!BreakNormalCooks.isEmpty())
			{
					BreakNormalCooks.Removefirst(cooker) ;
					tst->setcook(cooker);
					tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
					tst->setServtime(CurrentTimestep);
					cooker->resetordersdone();
					cooker->incrementordersdone();
					/// Lazem ne3raf hayerga3 tany wla eh elkalam
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
					
			}
			else if (!BreakVeganCooks.isEmpty())
			{
				BreakVeganCooks.Removefirst(cooker) ;
				tst->setcook(cooker);
					tst->setFinishtime(CurrentTimestep +ceil((double)tst->GetSize()/cooker->getSpeed()));
					tst->setServtime(CurrentTimestep);
					cooker->resetordersdone();
					cooker->incrementordersdone();
					
					/// Lazem ne3raf hayerga3 tany wla eh elkalam
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
					
			}
		}
			if (cooker){
				urgentorderscount++;
				cooker->seturgent(1);
			return 1;	
		}else{			/// will go for rest Cooks; 
			if (InjuredCooks.getcount()!=0)
			{
				InjuredCooks.dequeue(cooker) ;
				tst->setcook(cooker);
				tst->setServtime(CurrentTimestep);
				tst->setFinishtime(CurrentTimestep +ceil((double)tst->GetSize()/cooker->getSpeed()));
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
					
			}
		}
		
		/// If All busy and no BREAK OR REST WHAT WILL I DO ?? SHOULD I RETURN IT TO 
		// VIP HEAP AND IT WILL Come again next time step ;
			if (cooker)
			{
					urgentorderscount++;
				cooker->seturgent(1);
				return 1;
			}else{
			VipOrders.insert(tst);
			return 0;
		}
		
}



	
void Restaurant :: Autopromote() {
	Order* tmp =nullptr;
	NormalOrders.peekFront(tmp);
	
	while (NormalOrders.peekFront(tmp))
	{
		if (CurrentTimestep-tmp->getArrtime() >= autop){
			NormalOrders.dequeue(tmp);
			tmp->SetType(TYPE_VIP);
			tmp->setvipPriority();
			VipOrders.insert(tmp); //enq
			autopromotedcount++;
		}
		else
			break ;	
	}
}

void Restaurant::AddEvent(Event* pe)
{
	EventsQueue.enqueue(pe);
}

void Restaurant::AddOrder(Order* o)
{
	if (o->GetType() == TYPE_NRM)
	{
		NormalOrders.enqueue(o);
	}
	else if (o->GetType() == TYPE_VIP)
	{
		VipOrders.insert(o); // enqueue
	}
	else if (o->GetType() == TYPE_VGAN)
	{
		VeganOrders.enqueue(o);
	}
}

bool Restaurant::PromoteEvent(int id, int am)
{
	Event* etemp;
	Queue<Event*> qtemp;
	bool exists = false;
	while (EventsQueue.dequeue(etemp))
	{
		if (etemp->getOrderID() == id)
		{
			ArrivalEvent* av = dynamic_cast<ArrivalEvent*>(etemp);
			if (av && av->getOrderType() == TYPE_NRM)
			{
				av->setOrderType(TYPE_VIP);
				av->setOrdMoney(av->getOrdMoney() + am);
				exists = true;
			}
		}
		qtemp.enqueue(etemp);
	}
	EventsQueue = qtemp;
	return exists;
}


bool Restaurant::DeleteEvent(int id)
{
	Event* etemp;
	Queue<Event*> qtemp;
	bool exists = false;

	while (EventsQueue.dequeue(etemp))
	{
		if (etemp->getOrderID() != id)
		{
			qtemp.enqueue(etemp);
		}
		else
		{
			exists = true;
		}
	}
	EventsQueue = qtemp;
	return exists;
}




bool Restaurant::PromoteOrder(int id, int am)
{
	Order* otemp;
	Queue<Order*> qtemp;
	bool exists = false;

	while (NormalOrders.dequeue(otemp))
	{
		if (otemp->GetID() == id)
		{
			otemp->SetType(TYPE_VIP);
			otemp->SetTotalMoney(otemp->GetTotalMoney() + am);
			otemp->setvipPriority();
			VipOrders.insert(otemp); // enq
			exists = true;
		}
		else
		{
			qtemp.enqueue(otemp);
		}
	}

	NormalOrders = qtemp;
	return exists;
}

bool Restaurant::DeleteOrder(int id)
{
	Order* otemp;
	Queue<Order*> qtemp1;
	//Queue<Order*> qtemp2;
	//PriorityQueue<Order*> qtemp3;
	bool exists = false;

	while (NormalOrders.dequeue(otemp))
	{
		if (otemp->GetID() != id)
		{
			qtemp1.enqueue(otemp);
		}
		else
		{
			exists = true;
		}
	}
	NormalOrders = qtemp1;
	

	return exists;
}

//bool Restaurant::PromoteEvent(int id, int am)
//{
//	Event* etemp;
//	Queue<Event*> qtemp;
//	bool exists = false;
//	while (EventsQueue.dequeue(etemp))
//	{
//		if (etemp->getOrderID() == id)
//		{
//			ArrivalEvent* av = dynamic_cast<ArrivalEvent*>(etemp);
//			if (av && av->getOrderType() == TYPE_NRM)
//			{
//				av->setOrderType(TYPE_VIP);
//				av->setOrdMoney(av->getOrdMoney() + am);
//				exists = true;
//			}
//		}
//		qtemp.enqueue(etemp);
//	}
//	EventsQueue = qtemp;
//	return exists;
//}

//bool Restaurant::DeleteEvent(int id)
//{
//	Event* etemp;
//	Queue<Event*> qtemp;
//	bool exists = false;
//
//	while (EventsQueue.dequeue(etemp))
//	{
//		if (etemp->getOrderID() != id)
//		{
//			qtemp.enqueue(etemp);
//		}
//		else
//		{
//			exists = true;
//		}
//	}
//	EventsQueue = qtemp;
//	return exists;
//}






void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

		if (!ReadInputFile())
		return;

			CurrentTimestep = 1;
	
	if(mode==MODE_INTR){
	while (!(InserviceOrders.isEmpty() && EventsQueue.getcount() ==0 && VeganOrders.getcount()==0 && VipOrders.getcount()==0 
		&& NormalOrders.getcount()==0 && BreakNormalCooks.getcount()==0 && BreakVipCooks.getcount()==0 &&
		BreakVeganCooks.getcount()==0 && InjuredCooks.getcount()==0) )
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimestep, timestep, 10);
		pGUI->PrintMessage("TimeStep: " + to_string(CurrentTimestep));
		
		ExecuteEvents(CurrentTimestep);	//execute all events at current time step

		FinishBreak();		////Handles break and rest

		Autopromote();
		UpdateVip();

		ServeOrder();
		IsInjured();  //must be here not above bec if injuired in same ts he got the order
		/// And before finish to finish order if its in following Ts
		FinishOrder(); // it auto 
		
		FillDrawingList();
		pGUI->UpdateInterface();
		Sleep(1000);
		pGUI->waitForClick();
		CurrentTimestep++;
		
		previousevent = nullptr;
		pGUI->ResetDrawingList();
		pGUI->ResetLines();

	}
	DeleteCooks();
	DeleteFinished();

	}else if(mode==MODE_STEP){
			while (!(InserviceOrders.isEmpty() && EventsQueue.getcount() ==0 && VeganOrders.getcount()==0 && VipOrders.getcount()==0 
		&& NormalOrders.getcount()==0 && BreakNormalCooks.getcount()==0 && BreakVipCooks.getcount()==0 &&
		BreakVeganCooks.getcount()==0 && InjuredCooks.getcount()==0) )
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimestep, timestep, 10);
		pGUI->PrintMessage("TimeStep: " + to_string(CurrentTimestep));
		
		ExecuteEvents(CurrentTimestep);	//execute all events at current time step
		
		
		FinishBreak();		
		Autopromote();
		UpdateVip();
		
		
		ServeOrder();
		IsInjured();
		FinishOrder(); // it auto 
		
		FillDrawingList();
		pGUI->UpdateInterface();
		Sleep(1000);
		//
		CurrentTimestep++;
		
		previousevent = nullptr;
		pGUI->ResetDrawingList();
		pGUI->ResetLines();

	}
			DeleteCooks();
	DeleteFinished();
		
	}else if(mode==MODE_SLNT){
			while (!(InserviceOrders.isEmpty() && EventsQueue.getcount() ==0 && VeganOrders.getcount()==0 && VipOrders.getcount()==0 
		&& NormalOrders.getcount()==0 && BreakNormalCooks.getcount()==0 && BreakVipCooks.getcount()==0 &&
		BreakVeganCooks.getcount()==0 && InjuredCooks.getcount()==0) )
	{

		ExecuteEvents(CurrentTimestep);	//execute all events at current time step
		////
		FinishBreak();		
		//PLACE ----
		Autopromote();
		UpdateVip();
		ServeOrder();
		IsInjured();
		FinishOrder(); // it auto 
		CurrentTimestep++;
		previousevent = nullptr;
	}

	SaveFile();
	DeleteCooks();  ///////

	}else
		return ;

	///	delete[]pC;

	
	pGUI->PrintMessage("Click to end program !");
	pGUI->waitForClick();



}





	/*
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive_Mode();
		break;
	case MODE_STEP:
		Step_by_step_Mode();
		break;
	case MODE_SLNT:
		Silent_Mode();
		break;
	case MODE_DEMO:
		break;
	//	Just_A_Demo();
	};
	*/
	



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);
		if (dynamic_cast<CancellationEvent*>(pE) && dynamic_cast<CancellationEvent*>(pE)->Success())
			previousevent = new CancellationEvent(pE->getEventTime(), pE->getOrderID());		//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}



//A function that takes a ArrayStack<T> S and returns its reverse (without affecting the orignal stack)



void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list


	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

	int count = 0;
	
	Cook** tst = NormalCooks.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(tst[i]);
	}

	count = 0;
	tst = nullptr;
	tst = VipCooks.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(tst[i]);
	}


	count = 0;
	tst = nullptr;
	tst = VeganCooks.toArray(count);
	for (int i = 0; i < count; i++)
	{
		pGUI->AddToDrawingList(tst[i]);
	}

	//}

	if (dynamic_cast<CancellationEvent*>(previousevent)) {
		pGUI->RemoveItem(previousevent->getOrderID());
	}


	count = 0;

	Order** ptr = nullptr;
	ptr = InserviceOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{
		//	if (ptr[i]->getPrinted() == 0){
		//		pGUI->AddToDrawingList(ptr[i]);
		//		ptr[i]->setprinted(1);
		//	}
		pGUI->AddToDrawingList(ptr[i]);
	}

	count = 0;
	ptr = nullptr;
	ptr = NormalOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{
		//if (ptr[i]->getArrtime() <= CurrentTimestep && ptr[i]->getPrinted() == 0) {
		//	ptr[i]->setprinted(1);
		//	pGUI->AddToDrawingList(ptr[i]);
		//}
	//	if (ptr[i]->getArrtime() <= CurrentTimestep)
			pGUI->AddToDrawingList(ptr[i]);
	}

	count = 0;
	ptr = nullptr;

	ptr = VeganOrders.toArray(count);

	for (int i = 0; i < count; i++)
	{
		//	if (ptr[i]->getArrtime() <= CurrentTimestep && ptr[i]->getPrinted() == 0) {
		//		ptr[i]->setprinted(1);
		//		pGUI->AddToDrawingList(ptr[i]);
		//	}
		//if (ptr[i]->getArrtime() <= CurrentTimestep)
			pGUI->AddToDrawingList(ptr[i]);
	}

	count = 0;
	ptr = nullptr;

	ptr = VipOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{
	//	if (ptr[i]->getArrtime() <= CurrentTimestep)
			pGUI->AddToDrawingList(ptr[i]);
	}



	count = 0;
	ptr = nullptr;

	ptr = FinishedOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{
			pGUI->AddToDrawingList(ptr[i]);
	}

	ptr = nullptr;
	/*
	int y;
	y = NormalOrders.getcount();
	string y1 = to_string(y);
	int a = VeganOrders.getcount();
	int b= VipOrders.getcount();
	string y12 = to_string(a);
	string y13 = to_string(b);

	y = VipCooks.getcount() + VeganCooks.getcount() + NormalCooks.getcount();
	string y2 = to_string(y);
	y = InserviceOrders.getcount();
	string y3 = to_string(y);
	y = FinishedOrders.getcount();
	string y4 = to_string(y);
	
	pGUI->PrintMessage(" Number of Available cooks " + y2 );
	pGUI->PrintMessage("Number of Waiting Orders -- Normal : " + y1 + "  VIP:  " + y13 + " Vegan: " + y12 );
	pGUI->PrintMessage("Number of Inservice Orders : " + y3);
	pGUI->PrintMessage(" Number of finished Orders " + y4);
	*/	
	int y;
	y = NormalOrders.getcount();
	string y1 = to_string(y);
	int a = VeganOrders.getcount();
	int b= VipOrders.getcount();
	string y12 = to_string(a);
	string y13 = to_string(b);



	 y = VipCooks.getcount(); 
	string y2 = to_string(y);
	y = VeganCooks.getcount();
	string y8 = to_string(y);
	y= NormalCooks.getcount();
	string y9 = to_string(y);
	y = InserviceOrders.getcount();
	string y3 = to_string(y);
	y = FinishedOrders.getcount();
	string y4 = to_string(y);
	y = BreakNormalCooks.getcount();
	string y5 = to_string(y);
	y = BreakVeganCooks.getcount();
	string y6 = to_string(y);
	y = BreakVipCooks.getcount();
	string y7 = to_string(y);
	int inj=InjuredCooks.getcount();
	string injj=to_string(inj);

	pGUI->PrintMessage("Number of Available cooks: Normal Cooks =  " + y9 + " Vegan Cooks = " + y8 + " Vip Cooks =  " + y2 );
	pGUI->PrintMessage("Number of Waiting Orders -- Normal : " + y1 + "  VIP:  " + y13 + " Vegan: " + y12 );
	pGUI->PrintMessage("Number of Cooks in Break: Normal Cooks =  " + y5 + " Vegan Cooks = " + y6 + " Vip Cooks =  " + y7);

	pGUI->PrintMessage("Number of Cooks in Rest : " + injj);
	
	pGUI->PrintMessage("Number of Inservice Orders : " + y3);
	pGUI->PrintMessage("Number of finished Orders " + y4);
}



void Restaurant::SaveFile(){
	ofstream op;
	pGUI->PrintMessage("Please Enter the name of the output file ");
	string xx = pGUI->GetString();
	op.open(xx);

	op << "FT		ID		AT		WT		ST "<<endl ;
	Order* tst=nullptr;
	int Avgwait=0,Avgserv=0;

	int normorders=0,vegorders=0, viporders=0;

	while (FinishedOrders.dequeue(tst))
	{
		int ft=tst->getFinishtime() ; int at=tst->getArrtime() ; int wt=tst->getServtime()-tst->getArrtime();
		int st=tst->getFinishtime()-tst->getServtime(); int id=tst->GetID();
		Avgwait+=wt;
		Avgserv+=st;
		if (tst->GetType()==TYPE_NRM)
		{
			normorders++;
		}else if(tst->GetType()==TYPE_VGAN)
		{
			vegorders++;
		}else
			viporders++;
		op<< ft << "		"<< id << "		"<<at << "		"<<wt << "		"<<st <<endl;
		delete tst;   //////// In silent modee deleting Manually due to Needing of info
	}op<<endl;

	op<< "Orders: "<< normorders+vegorders+viporders << "  [Norm: " << normorders << ", Veg: " << vegorders << ", Vip : "<<viporders  << "]"<< endl ;
	
	op << "Cooks: "<< NormalCooks.getcount()+VeganCooks.getcount() + VipCooks.getcount() <<
		"    [Norm: "<< NormalCooks.getcount() << ", Veg: " << VeganCooks.getcount() << ", Vip : "<<VipCooks.getcount()<<", injured:" <<
			CountInjuires <<  "]"<< endl ;
	if(normorders+vegorders+viporders !=0)
	op << "Avg Wait = " <<(double)Avgwait/(normorders+vegorders+viporders)  << ",  "<<"Avg Serv = " << (double)Avgserv/(normorders+vegorders+viporders)<< endl ;
	else
	op << "Avg Wait = " << 0 << ",  "<<"Avg Serv = " << 0 << endl ;

	if(normorders+autopromotedcount!=0)
	op << "Urgent orders: " << urgentorderscount << ", Auto-promoted: "<<(double)autopromotedcount/(normorders+autopromotedcount) *100 << "%"<< endl ; 
	else
	op << "Urgent orders: " << urgentorderscount << ", Auto-promoted: "<< 0 << "%"<< endl ; 
	
	op.close();


}


	void Restaurant::UpdateVip(){
		Order* tst=nullptr; 
		bool z=VipOrders.RemoveVipWait(CurrentTimestep,tst);
		bool x=UrgentServe(tst);   /// urgent serve will return it at vip if no cooks found at any partition,rest,break
		if(!x)
			return ;
		tst=nullptr;
		while(z)
		{
			z=VipOrders.RemoveVipWait(CurrentTimestep,tst);
			bool x=UrgentServe(tst);
			if(!x)
				return ;
			tst=nullptr;
		}
	}
	
	
	
	
	
	void Restaurant::MoveCook(Cook* coming)
{
	if (coming->IsInjured() && !coming->geturgent()){
		InjuredCooks.enqueue(coming);
		coming->setrestfinishtime(CurrentTimestep+rstPrd);
		coming->seturgent(0);
		return ;
	}else if(coming->IsInjured() && coming->geturgent()){
		coming->seturgent(0); 
		coming->recover();////////////Fe laghbataaa hena khaly balakkk 
	}
		
	
	if (coming->getOrdersdone() == coming->getOrderstoBreak())
	{
		if (coming->GetType() == TYPE_NRM){		
			coming->settimeatwhichhegoesbreak(CurrentTimestep);
			coming->settimeatwhichbreakfinish();
			BreakNormalCooks.insert(coming);
		}
		else if (coming->GetType() == TYPE_VGAN){
			coming->settimeatwhichhegoesbreak(CurrentTimestep);
			coming->settimeatwhichbreakfinish();
			BreakVeganCooks.insert(coming);					
			
		}
		else if (coming->GetType() == TYPE_VIP){
			coming->settimeatwhichhegoesbreak(CurrentTimestep);
					coming->settimeatwhichbreakfinish();
			BreakVipCooks.insert(coming);
					
		}
	}
	else
	{
		if (coming->GetType() == TYPE_NRM)
			NormalCooks.enqueue(coming);
		else if (coming->GetType() == TYPE_VGAN)
			VeganCooks.enqueue(coming);
		else if (coming->GetType() == TYPE_VIP)
			VipCooks.enqueue(coming);
	}
}



	void Restaurant::ServeOrder() {
		Order* tst = nullptr;
		Cook* cooker;
		
		while (!VipOrders.isEmpty()) /// peak front
		{
			if(!VipCooks.isEmpty()){
			VipOrders.Removefirst(tst); // dequeue

			VipCooks.dequeue(cooker);
			tst->setcook(cooker);
			tst->setServtime(CurrentTimestep);
			tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
			cooker->incrementordersdone();
			Busycooks.InsertBeg(cooker);
			tst->setStatus(SRV);
			InserviceOrders.enqueue(tst);
			}
			else if( VipCooks.isEmpty())
			{
				if(!NormalCooks.isEmpty())
				{
					VipOrders.Removefirst(tst); // deq
					NormalCooks.dequeue(cooker);
					tst->setcook(cooker);
								tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
								tst->setServtime(CurrentTimestep);
								cooker->incrementordersdone();
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
				}else if (!VeganCooks.isEmpty())
				{
					VipOrders.Removefirst(tst); // deq
					VeganCooks.dequeue(cooker);
					tst->setcook(cooker);
								tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
								tst->setServtime(CurrentTimestep);
					cooker->incrementordersdone();
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
				}else
					break ;
			}
		}

		cooker=nullptr;
		tst=nullptr;
		
		while(!VeganOrders.isEmpty()){
			if (!VeganCooks.isEmpty()){
				VeganOrders.dequeue(tst);
					VeganCooks.dequeue(cooker);
					tst->setcook(cooker);
								tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
								tst->setServtime(CurrentTimestep);
					cooker->incrementordersdone();
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
			}
			else
				break ;
		}

		cooker=nullptr;
		tst=nullptr;

		while(!NormalOrders.isEmpty()){
			if (!NormalCooks.isEmpty()){
				NormalOrders.dequeue(tst);

					NormalCooks.dequeue(cooker);
					tst->setcook(cooker);
								tst->setFinishtime(CurrentTimestep + ceil((double)tst->GetSize()/cooker->getSpeed()));
								tst->setServtime(CurrentTimestep);
					cooker->incrementordersdone();
					Busycooks.InsertBeg(cooker);
					tst->setStatus(SRV);
					InserviceOrders.enqueue(tst);
			}
			else
				break ;
		}

	}

	// should be changed in phase 2
	void Restaurant::FinishOrder() {
		Order* tst =nullptr;
		InserviceOrders.peekFront(tst);

		
		while (	tst && tst->getFinishtime() == CurrentTimestep)
		{
			InserviceOrders.dequeue(tst);
			tst->setStatus(DONE);
			FinishedOrders.enqueue(tst);
			Cook* mine= Busycooks.RemoveNode(tst->getmycook());
			MoveCook(mine);
			InserviceOrders.peekFront(tst);
		
		}
		
	}



	void Restaurant::FinishBreak(){  //////// It includes finishing break and rest 
		Cook* tst=nullptr;
		BreakNormalCooks.getfirst(tst);
		while (tst && BreakNormalCooks.getcount()!=0)
		{
			if(tst->gettimeatwhichbreakfinish()==CurrentTimestep){
				BreakNormalCooks.Removefirst(tst);
				NormalCooks.enqueue(tst);
				tst->settimeatwhichhegoesbreak(-1);
				tst->resetordersdone();
				BreakNormalCooks.getfirst(tst);
			}else
				break ;
		}
		
		tst=nullptr;
		BreakVeganCooks.getfirst(tst);
		while (tst && BreakVeganCooks.getcount()!=0)
		{
			if(tst->gettimeatwhichbreakfinish()==CurrentTimestep){
				BreakVeganCooks.Removefirst(tst);
				VeganCooks.enqueue(tst);
				tst->settimeatwhichhegoesbreak(-1);
				tst->resetordersdone();
				BreakVeganCooks.getfirst(tst);
			}else
				break ;
		}

		
		tst=nullptr;
		BreakVipCooks.getfirst(tst);
		while (tst && BreakVipCooks.getcount()!=0)
		{
			if(tst->gettimeatwhichbreakfinish()==CurrentTimestep){
				BreakVipCooks.Removefirst(tst);
				VipCooks.enqueue(tst);
				tst->settimeatwhichhegoesbreak(-1);
				tst->resetordersdone();
				BreakVipCooks.getfirst(tst);
			}else
				break ;
		}
		tst=nullptr;
	
		while (InjuredCooks.peekFront(tst))
		{
			if (tst->getrestfinishtime()==CurrentTimestep)
			{
				InjuredCooks.dequeue(tst);
				tst->recover();
				if (tst->GetType()==TYPE_NRM)
				{
					NormalCooks.enqueue(tst);
				}else if(tst->GetType()==TYPE_VIP)
				{
					VipCooks.enqueue(tst);
				}else
					VeganCooks.enqueue(tst);
			
			}else
				break;
		}
	
	}
	


void Restaurant::DeleteCooks(){
		Cook* cooker=nullptr;
		while (NormalCooks.dequeue(cooker))
		{
			delete cooker;
		}while (VeganCooks.dequeue(cooker))
		{
			delete cooker;
		}
		while (VipCooks.dequeue(cooker))
		{
			delete cooker;
		}
	}

	void Restaurant::DeleteFinished(){
		Order* tst=nullptr;
		while (FinishedOrders.dequeue(tst))
		{
			delete tst ;
		}
	}







