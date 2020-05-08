#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\BHeap.h"
#include "..\Events\Event.h"
#include<iostream>
#include<fstream>

#include "Order.h"
#include "Cook.h"
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
	BHeap<Order*> waitingVIPOrders;	// List of waiting VIP orders

	//// in service ////
	BHeap<Order*> srvNOROrders;	// List of in service normal orders
	BHeap<Order*> srvVEGOrders;	// List of in service vegan orders
	BHeap<Order*> srvVIPOrders;	// List of in service VIP orders

	//// done ////
	Queue<Order*> doneOrders;	// List of DONE orders

	///////////////////////////////////////////////////////////////////////////

	////////////////////////////////// Cooks //////////////////////////////////

	//// available ////
	BHeap<Cook*> avNORCooks;	// List of available normal cooks
	BHeap<Cook*> avVEGCooks;	// List of available vegan cooks
	BHeap<Cook*> avVIPCooks;	// List of available VIP cooks

	//// in-available ////
	BHeap<Cook*> navNORCooks;	// List of in-available normal cooks
	BHeap<Cook*> navVEGCooks;	// List of in-available vegan cooks
	BHeap<Cook*> navVIPCooks;	// List of in-available VIP cooks

	//// break ////
	BHeap<Cook*> brkNORCooks;	// List of in-available normal cooks
	BHeap<Cook*> brkVEGCooks;	// List of in-available vegan cooks
	BHeap<Cook*> brkVIPCooks;	// List of in-available VIP cooks

	///////////////////////////////////////////////////////////////////////////

public:
	Restaurant();
	~Restaurant();

	void Work(int CurrentTimeStep, string* Varr, string* Narr, string* Garr, int& Vc, int& Nc, int& Gc);
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
	void AddtowaitingVIPOrders(Order*& ptr);

	void AddtosrvNOROrders(int pri, Order*& ptr);
	void AddtosrvVEGOrders(int pri, Order*& ptr);
	void AddtosrvVIPOrders(int pri, Order*& ptr);

	void AddtodoneOrders(Order*& ptr);

	/// remove from the lists ///
	void rmvwaitingNOROrders(Order*& ptr);
	void rmvwaitingVEGOrders(Order*& ptr);
	void rmvwaitingVIPOrders(Order*& ptr);


	void rmvsrvNOROrders(Order*& ptr);
	void rmvsrvVEGOrders(Order*& ptr);
	void rmvsrvVIPOrders(Order*& ptr);


	void rmvdoneOrders(Order* &ptr);
};

#endif