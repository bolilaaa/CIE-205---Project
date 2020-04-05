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
#include "..\CompareOPri.h"
#include "..\Generic_DS\CompareCPri.h"


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
	priority_queue<Order*, vector<Order*>, CompareOPri> waitingVIPOrders;	// List of waiting VIP orders

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
	priority_queue<Cook*, vector<Cook*>, CompareCPri> avNORCooks;	// List of available normal cooks
	priority_queue<Cook*, vector<Cook*>, CompareCPri> avVEGCooks;	// List of available vegan cooks
	priority_queue<Cook*, vector<Cook*>, CompareCPri> avCHNCooks;	// List of available additional type 1 cooks
	priority_queue<Cook*, vector<Cook*>, CompareCPri> avMEXCooks;	// List of available additional type 2 cooks
	priority_queue<Cook*, vector<Cook*>, CompareCPri> avVIPCooks;	// List of available VIP cooks

	//// in-available ////
	priority_queue<Order*, vector<Cook*>, CompareCPri> navNORCooks;	// List of in-available normal cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> navVEGCooks;	// List of in-available vegan cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> navCHNCooks;	// List of in-available additional chinese cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> navMEXCooks;	// List of in-available additional mexican cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> navVIPCooks;	// List of in-available VIP cooks

	//// break ////
	priority_queue<Order*, vector<Cook*>, CompareCPri> brkNORCooks;	// List of in-available normal cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> brkVEGCooks;	// List of in-available vegan cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> brkCHNCooks;	// List of in-available additional chinese cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> brkMEXCooks;	// List of in-available additional mexican cooks
	priority_queue<Order*, vector<Cook*>, CompareCPri> brkVIPCooks;	// List of in-available VIP cooks

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

	void AddtoavNORCooks(Cook* ptr);
	void AddtoavVEGCooks(Cook* ptr);
	void AddtoavCHNCooks(Cook* ptr);
	void AddtoavMEXCooks(Cook* ptr);
	void AddtoavVIPCooks(Cook* ptr);


	void AddtonavNORCooks(Cook* ptr);
	void AddtonavVEGCooks(Cook* ptr);
	void AddtonavCHNCooks(Cook* ptr);
	void AddtonavMEXCooks(Cook* ptr);
	void AddtonavVIPCooks(Cook* ptr);

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

	void rmvavNORCooks(Cook* ptr);
	void rmvavVEGCooks(Cook* ptr);
	void rmvavCHNCooks(Cook* ptr);
	void rmvavMEXCooks(Cook* ptr);
	void rmvavVIPCooks(Cook* ptr);

	void rmvnavNORCooks(Cook* ptr);
	void rmvnavVEGCooks(Cook* ptr);
	void rmvnavCHNCooks(Cook* ptr);
	void rmvnavMEXCooks(Cook* ptr);
	void rmvnavVIPCooks(Cook* ptr);
};

#endif