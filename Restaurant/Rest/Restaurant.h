#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"

#include "Order.h"
#include "Cook.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	int AutoPromotion, AutoPromoted = 0, numCNOR = 0, numCVEG = 0, numCVIP = 0, numCOR1 = 0, numCOR2 = 0;
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	//	Resturant Lists

	////////////////////////////////// Orders //////////////////////////////////

	//// waiting ////
	Queue<Order*> waitingNOROrders;	// List of waiting normal orders
	Queue<Order*> waitingVEGOrders;	// List of waiting vegan orders
	Queue<Order*> waitingVIPOrders;	// List of waiting VIP orders
	Queue<Order*> waitingOR1Orders;	// List of waiting additional type 1 orders
	Queue<Order*> waitingOR2Orders;	// List of waiting additional type 2 orders
	
	//// in service ////
	Queue<Order*> srvNOROrders;	// List of in service normal orders
	Queue<Order*> srvVEGOrders;	// List of in service vegan orders
	Queue<Order*> srvVIPOrders;	// List of in service VIP orders
	Queue<Order*> srvOR1Orders;	// List of in service additional type 1 orders
	Queue<Order*> srvOR2Orders;	// List of in service additional type 2 orders

	//// done ////
	Queue<Order*> doneOrders;	// List of DONE orders

	///////////////////////////////////////////////////////////////////////////

	////////////////////////////////// Cooks //////////////////////////////////

	//// available ////
	Queue<Order*> avNORCooks;	// List of available normal cooks
	Queue<Order*> avVEGCooks;	// List of available vegan cooks
	Queue<Order*> avVIPCooks;	// List of available VIP cooks
	Queue<Order*> avOR1Cooks;	// List of available additional type 1 cooks
	Queue<Order*> avOR2Cooks;	// List of available additional type 2 cooks

	//// in-available ////
	Queue<Order*> navNORCooks;	// List of in-available normal cooks
	Queue<Order*> navVEGCooks;	// List of in-available vegan cooks
	Queue<Order*> navVIPCooks;	// List of in-available VIP cooks
	Queue<Order*> navOR1Cooks;	// List of in-available additional type 1 cooks
	Queue<Order*> navOR2Cooks;	// List of in-available additional type 2 cooks

	///////////////////////////////////////////////////////////////////////////

public:
	Restaurant();
	~Restaurant();
	/// general operations ///
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void FillDrawingList();
	void LoadAll(string filename);

	/// operation modes ///
	void SIMULATE();	


	/////////////// Lists functions ///////////////
	/// add to the lists ///
	void AddtowaitingNOROrders(Order* ptr);
	void AddtowaitingVEGOrders(Order* ptr);
	void AddtowaitingVIPOrders(Order* ptr);
	void AddtowaitingOR1Orders(Order* ptr);
	void AddtowaitingOR2Orders(Order* ptr);

	void AddtosrvNOROrders(Order* ptr);
	void AddtosrvVEGOrders(Order* ptr);
	void AddtosrvVIPOrders(Order* ptr);
	void AddtosrvOR1Orders(Order* ptr);
	void AddtosrvOR2Orders(Order* ptr);

	void AddtodoneOrders(Order* ptr);

	void AddtoavNORCooks(Order* ptr);
	void AddtoavVEGCooks(Order* ptr);
	void AddtoavVIPCooks(Order* ptr);
	void AddtoavOR1Cooks(Order* ptr);
	void AddtoavOR2Cooks(Order* ptr);

	void AddtonavNORCooks(Order* ptr);
	void AddtonavVEGCooks(Order* ptr);
	void AddtonavVIPCooks(Order* ptr);
	void AddtonavOR1Cooks(Order* ptr);
	void AddtonavOR2Cooks(Order* ptr);

	/// remove from the lists ///
	void rmvwaitingNOROrders(Order* ptr);
	void rmvwaitingVEGOrders(Order* ptr);
	void rmvwaitingVIPOrders(Order* ptr);
	void rmvwaitingOR1Orders(Order* ptr);
	void rmvwaitingOR2Orders(Order* ptr);

	void rmvsrvNOROrders(Order* ptr);
	void rmvsrvVEGOrders(Order* ptr);
	void rmvsrvVIPOrders(Order* ptr);
	void rmvsrvOR1Orders(Order* ptr);
	void rmvsrvOR2Orders(Order* ptr);

	void rmvdoneOrders(Order* ptr);

	void rmvavNORCooks(Order* ptr);
	void rmvavVEGCooks(Order* ptr);
	void rmvavVIPCooks(Order* ptr);
	void rmvavOR1Cooks(Order* ptr);
	void rmvavOR2Cooks(Order* ptr);

	void rmvnavNORCooks(Order* ptr);
	void rmvnavVEGCooks(Order* ptr);
	void rmvnavVIPCooks(Order* ptr);
	void rmvnavOR1Cooks(Order* ptr);
	void rmvnavOR2Cooks(Order* ptr);
};

#endif