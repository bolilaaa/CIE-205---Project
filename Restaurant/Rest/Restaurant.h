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
#include "..\Generic_DS\CompareOWPri.h"
#include "..\Generic_DS\CompareOSPri.h"
#include "..\Generic_DS\CompareCPri.h"
#include "..\Generic_DS\CompareBPri.h"
using namespace std;

// it is the maestro of the project
class Restaurant  
{	
public:
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
	priority_queue<Order*, vector<Order*>, CompareOWPri> waitingVIPOrders;	// List of waiting VIP orders

	//// in service ////
	priority_queue<Order*, vector<Order*>, CompareOSPri> srvNOROrders;	// List of in service normal orders
	priority_queue<Order*, vector<Order*>, CompareOSPri> srvVEGOrders;	// List of in service vegan orders
	priority_queue<Order*, vector<Order*>, CompareOSPri> srvCHNOrders;	// List of in service additional chinese orders
	priority_queue<Order*, vector<Order*>, CompareOSPri> srvMEXOrders;	// List of in service additional mexican orders
	priority_queue<Order*, vector<Order*>, CompareOSPri> srvVIPOrders;	// List of in service VIP orders

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
	priority_queue<Order*, vector<Cook*>, CompareBPri> brkNORCooks;	// List of in-available normal cooks
	priority_queue<Order*, vector<Cook*>, CompareBPri> brkVEGCooks;	// List of in-available vegan cooks
	priority_queue<Order*, vector<Cook*>, CompareBPri> brkCHNCooks;	// List of in-available additional chinese cooks
	priority_queue<Order*, vector<Cook*>, CompareBPri> brkMEXCooks;	// List of in-available additional mexican cooks
	priority_queue<Order*, vector<Cook*>, CompareBPri> brkVIPCooks;	// List of in-available VIP cooks

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

	/// remove from the lists ///
	void rmvwaitingNOROrders(Order* ptr);
	void rmvwaitingVEGOrders(Order* ptr);
	void rmvwaitingCHNOrders(Order* ptr);
	void rmvwaitingMEXOrders(Order* ptr);
	void rmvwaitingVIPOrders(Order* ptr);


	void rmvsrvNOROrders();
	void rmvsrvVEGOrders();
	void rmvsrvCHNOrders();
	void rmvsrvMEXOrders();
	void rmvsrvVIPOrders();


	void rmvdoneOrders(Order* ptr);
};

#endif