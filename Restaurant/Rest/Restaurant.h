#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\priorityQueue.h"
#include "..\Events\Event.h"
#include<iostream>
#include<fstream>

#include "Order.h"
#include "Cook.h"

#include <queue>
#include "..\Generic_DS\CompareOWPri.h"
#include "..\Generic_DS\CompareOSPri.h"
#include "..\Generic_DS\CompareCPri.h"
#include "..\Generic_DS\CompareBPri.h"
using namespace std;

// it is the maestro of the project
class Restaurant  
{	
public:
	ifstream file_load;
	double crrtimestep = 0;
//private:
	int AutoPromotion, AutoPromoted = 0, numCNOR = 0, numCVEG = 0, numCVIP = 0, numCCHN = 0, numCMEX = 0;
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	//	Resturant Lists

	////////////////////////////////// Orders //////////////////////////////////

	//// waiting ////
	Queue<Order*> waitingNOROrders;	// List of waiting normal orders
	Queue<Order*> waitingVEGOrders;	// List of waiting vegan orders
	Queue<Order*> waitingCHNOrders;	// List of waiting additional chinese
	Queue<Order*> waitingMEXOrders;	// List of waiting additional mexican
	priorityQueue<Order*> waitingVIPOrders;	// List of waiting VIP orders

	//// in service ////
	priorityQueue<Order*> srvNOROrders;	// List of in service normal orders
	priorityQueue<Order*> srvVEGOrders;	// List of in service vegan orders
	priorityQueue<Order*> srvCHNOrders;	// List of in service additional chinese orders
	priorityQueue<Order*> srvMEXOrders;	// List of in service additional mexican orders
	priorityQueue<Order*> srvVIPOrders;	// List of in service VIP orders

	//// done ////
	Queue<Order*> doneOrders;	// List of DONE orders

	///////////////////////////////////////////////////////////////////////////

	////////////////////////////////// Cooks //////////////////////////////////

	//// available ////
	priorityQueue<Cook*> avNORCooks;	// List of available normal cooks
	priorityQueue<Cook*> avVEGCooks;	// List of available vegan cooks
	priorityQueue<Cook*> avCHNCooks;	// List of available additional type 1 cooks
	priorityQueue<Cook*> avMEXCooks;	// List of available additional type 2 cooks
	priorityQueue<Cook*> avVIPCooks;	// List of available VIP cooks

	//// in-available ////
	priorityQueue<Cook*> navNORCooks;	// List of in-available normal cooks
	priorityQueue<Cook*> navVEGCooks;	// List of in-available vegan cooks
	priorityQueue<Cook*> navCHNCooks;	// List of in-available additional chinese cooks
	priorityQueue<Cook*> navMEXCooks;	// List of in-available additional mexican cooks
	priorityQueue<Cook*> navVIPCooks;	// List of in-available VIP cooks

	//// break ////
	priorityQueue<Cook*> brkNORCooks;	// List of in-available normal cooks
	priorityQueue<Cook*> brkVEGCooks;	// List of in-available vegan cooks
	priorityQueue<Cook*> brkCHNCooks;	// List of in-available additional chinese cooks
	priorityQueue<Cook*> brkMEXCooks;	// List of in-available additional mexican cooks
	priorityQueue<Cook*> brkVIPCooks;	// List of in-available VIP cooks

	///////////////////////////////////////////////////////////////////////////

public:
	Restaurant();
	~Restaurant();
	/// general operations ///
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void PromoteEvents(int TimeStep);
	void CancelEvents(int TimeStep);

	void RunSimulation();
	void FillDrawingList();
	void LoadAll(string filename);

	/// operation modes ///
	void SIMULATE();	

	/////////////// Lists functions ///////////////
	/// add to the lists ///
	void AddtowaitingNOROrders(Order*& ptr);
	void AddtowaitingVEGOrders(Order*& ptr);
	void AddtowaitingCHNOrders(Order*& ptr);
	void AddtowaitingMEXOrders(Order*& ptr);
	void AddtowaitingVIPOrders(Order*& ptr);

	void AddtosrvNOROrders(Order*& ptr);
	void AddtosrvVEGOrders(Order*& ptr);
	void AddtosrvCHNOrders(Order*& ptr);
	void AddtosrvMEXOrders(Order*& ptr);
	void AddtosrvVIPOrders(Order*& ptr);

	void AddtodoneOrders(Order*& ptr);

	/// remove from the lists ///
	void rmvwaitingNOROrders(Order*& ptr);
	void rmvwaitingVEGOrders(Order*& ptr);
	void rmvwaitingCHNOrders(Order*& ptr);
	void rmvwaitingMEXOrders(Order*& ptr);
	void rmvwaitingVIPOrders(Order*& ptr);


	void rmvsrvNOROrders(Order*& ptr);
	void rmvsrvVEGOrders(Order*& ptr);
	void rmvsrvCHNOrders(Order*& ptr);
	void rmvsrvMEXOrders(Order*& ptr);
	void rmvsrvVIPOrders(Order*& ptr);


	void rmvdoneOrders(Order* &ptr);
};

#endif