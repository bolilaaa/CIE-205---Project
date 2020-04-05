#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"

#include "Order.h"
#include "Cook.h"

#include <queue>
#include "..\ComparePri.h"

// it is the maestro of the project
class Restaurant  
{	
private:
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
	priority_queue<Order*, vector<Order*>, ComparePri> waitingVIPOrders;	// List of waiting VIP orders

	//// in service ////
	Queue<Order*> srvNOROrders;	// List of in service normal orders
	Queue<Order*> srvVEGOrders;	// List of in service vegan orders
	Queue<Order*> srvCHNOrders;	// List of in service additional chinese orders
	Queue<Order*> srvMEXOrders;	// List of in service additional mexican orders
	Queue<Order*> srvVIPOrders;	// List of in service VIP orders

	//// done ////
	Queue<Order*> doneOrders;	// List of DONE orders

	///////////////////////////////////////////////////////////////////////////

	////////////////////////////////// Cooks //////////////////////////////////

	//// available ////
	Queue<Order*> avNORCooks;	// List of available normal cooks
	Queue<Order*> avVEGCooks;	// List of available vegan cooks
	Queue<Order*> avCHNCooks;	// List of available additional type 1 cooks
	Queue<Order*> avMEXCooks;	// List of available additional type 2 cooks
	Queue<Order*> avVIPCooks;	// List of available VIP cooks

	//// in-available ////
	Queue<Order*> navNORCooks;	// List of in-available normal cooks
	Queue<Order*> navVEGCooks;	// List of in-available vegan cooks
	Queue<Order*> navCHNCooks;	// List of in-available additional chinese cooks
	Queue<Order*> navMEXCooks;	// List of in-available additional mexican cooks
	Queue<Order*> navVIPCooks;	// List of in-available VIP cooks

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
	void AddtowaitingCHNOrders(Order* ptr);
	void AddtowaitingMEXOrders(Order* ptr);
	void AddtowaitingVIPOrders(Order* ptr);

	void AddtosrvNOROrders(Order* ptr);
	void AddtosrvVEGOrders(Order* ptr);
	void AddtosrvCHNOrders(Order* ptr);
	void AddtosrvMEXOrders(Order* ptr);
	void AddtosrvVIPOrders(Order* ptr);

	void AddtodoneOrders(Order* ptr);

	void AddtoavNORCooks(Order* ptr);
	void AddtoavVEGCooks(Order* ptr);
	void AddtoavCHNCooks(Order* ptr);
	void AddtoavMEXCooks(Order* ptr);
	void AddtoavVIPCooks(Order* ptr);


	void AddtonavNORCooks(Order* ptr);
	void AddtonavVEGCooks(Order* ptr);
	void AddtonavCHNCooks(Order* ptr);
	void AddtonavMEXCooks(Order* ptr);
	void AddtonavVIPCooks(Order* ptr);

	/// remove from the lists ///
	void rmvwaitingNOROrders(Order* ptr);
	void rmvwaitingVEGOrders(Order* ptr);
	void rmvwaitingCHNOrders(Order* ptr);
	void rmvwaitingMEXOrders(Order* ptr);
	void rmvwaitingVIPOrders(Order* ptr);


	void rmvsrvNOROrders(Order* ptr);
	void rmvsrvVEGOrders(Order* ptr);
	void rmvsrvCHNOrders(Order* ptr);
	void rmvsrvMEXOrders(Order* ptr);
	void rmvsrvVIPOrders(Order* ptr);


	void rmvdoneOrders(Order* ptr);

	void rmvavNORCooks(Order* ptr);
	void rmvavVEGCooks(Order* ptr);
	void rmvavCHNCooks(Order* ptr);
	void rmvavMEXCooks(Order* ptr);
	void rmvavVIPCooks(Order* ptr);

	void rmvnavNORCooks(Order* ptr);
	void rmvnavVEGCooks(Order* ptr);
	void rmvnavCHNCooks(Order* ptr);
	void rmvnavMEXCooks(Order* ptr);
	void rmvnavVIPCooks(Order* ptr);
};

#endif