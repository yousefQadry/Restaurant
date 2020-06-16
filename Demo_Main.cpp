//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include<iostream>

int main()
{

	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	
	delete pRest;
	return 0;
}
