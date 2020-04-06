#include <cstdlib>
#include <time.h>
#include <iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}
ifstream file_load;

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_SIMU:
		SIMULATE();
		break;
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		crrtimestep = CurrentTimeStep;
		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
}
//
void Restaurant::PromoteEvents(int TimeStep)
{

}
//
void Restaurant::CancelEvents(int TimeStep)
{

}
//
Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	Order* pOrd;
	int size;

	//Drawing Orders
	Order** waitingveganOrdersArray = waitingVEGOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(waitingveganOrdersArray[i]);

	Order** waitingNormalOrdersArray = waitingNOROrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(waitingNormalOrdersArray[i]);

	Order** waitingVIPOrdersArray = waitingVIPOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(waitingVIPOrdersArray[i]);

	Order** waitingchineseOrdersArray = waitingCHNOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(waitingchineseOrdersArray[i]);
	Order** waitingmexicanOrdersArray = waitingMEXOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(waitingmexicanOrdersArray[i]);
	//in service orders
	Order** inserviceveganOrdersArray = srvVEGOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(inserviceveganOrdersArray[i]);
	Order** inservicenormalOrdersArray = srvNOROrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(inservicenormalOrdersArray[i]);
	Order** inserviceVIPOrdersArray = srvVIPOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(inserviceVIPOrdersArray[i]);
	Order** inservicechineseOrdersArray = srvCHNOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(inservicechineseOrdersArray[i]);
	Order** inservicemexicanOrdersArray = srvMEXOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(inservicemexicanOrdersArray[i]);

	// done orders

	Order** doneOrdersArray = doneOrders.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(doneOrdersArray[i]);

	//Drawing available cooks
	Cook** VEGcookarray = avVEGCooks.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(VEGcookarray[i]);

	Cook** VIPcookarray = avVIPCooks.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(VIPcookarray[i]);

	Cook** NORcookarray = avNORCooks.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(NORcookarray[i]);

	Cook** CHNcookarray = avCHNCooks.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(CHNcookarray[i]);

	Cook** MEXcookarray = avMEXCooks.toArray(size);
	for (int i = 0; i < size; i++)
		pGUI->AddToDrawingList(MEXcookarray[i]);

	
}

void Restaurant::LoadAll(string filename) {
	int Num_of_events; //variable to read the number of events from the file
	int BO, BN, BG, BV,BC, BM, SN, SG, SV,SC,SM; //variables to read cooks speed ranges and break times
	file_load.open(filename.c_str()); //opening the file
	file_load >> numCNOR >> numCVEG >> numCVIP >> numCCHN >> numCMEX>> SN >> SG >> SV >>SC>>SM>> BO >> BN >> BG >> BV >>BC>>BM>> AutoPromotion;
	//Intializing Cooks lists (cooks will be pushed directly but orders will use functions)
	Cook* CK;
	for (int i = 0; i < numCVIP; i++) {
		CK = new Cook(i + 1, TYPE_VIP);
		CK->setSpeed(SV);
		CK->setBreakTime(BV);
		avVIPCooks.push(CK);
	}
	for (int i = 0; i < numCVEG; i++) {
		CK = new Cook(i + 1, TYPE_VGAN);
		CK->setSpeed(SG);
		CK->setBreakTime(BG);
		avVEGCooks.push(CK);
	}
	for (int i = 0; i < numCNOR; i++) {
		CK = new Cook(i + 1, TYPE_NRM);
		CK->setSpeed(SN);
		CK->setBreakTime(BN);
		avNORCooks.push(CK);
	}

	file_load >> Num_of_events;
	char type; //to read the event type
	enum CurROType {N, G, C, M, V}dir;
	char CurReadOrderType; // to read Order type
	ORD_TYPE CurOrderType; //as the arrival event's constructor needs a parameter from the typr ORD_Type
	int CurTime; int CurID; int CurSize; double CurCost; double ExMoney; //variables to read from the file
	Event* CurEvent; //pointer to event it points to any class object inherited from event as arrival,cancel and promote

	// initializing Orders
	for (int i = 0; i < Num_of_events; i++) {
		file_load >> type;
		switch (type)
		{
		case 'R':
			file_load >> CurReadOrderType >> CurTime >> CurID >> CurSize >> CurCost;
			switch (CurReadOrderType)
			{
			case N:
				CurOrderType = TYPE_NRM;
				break;
			case G:
				CurOrderType = TYPE_VGAN;
				break;
			case C:
				CurOrderType = TYPE_CHN;
				break;
			case M:
				CurOrderType = TYPE_MEX;
				break;
			case V:
				CurOrderType = TYPE_VIP;
				break;
			}
			CurEvent = new ArrivalEvent(CurTime, CurID, CurOrderType, CurCost, CurSize);
			break;
		case 'X':
			file_load >> CurTime >> CurID;
			//CurEvent = new CancelEvent(CurTime, CurID); 
			break;
		case 'P':
			file_load >> CurTime >> CurID >> ExMoney;
			//CurEvent = new PormoteEvent(CurTime, CurID, ExMoney);
			break;
		}
		EventsQueue.enqueue(CurEvent);
	}
	file_load.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  Operation Modes   /////////////////////////////

void Restaurant::SIMULATE()
{
	// Taking the input and initializing the cooks and fill the EventsQueue
	string filename;
	pGUI->PrintMessage("Simulation Mode. Enter INPUT file name:");
	filename = pGUI->GetString();	//get user input as a string
	LoadAll(filename);
	pGUI->PrintMessage("CLICK to start");
	pGUI->waitForClick();

	//Now let's start the simulation
	int CurrentTimeStep = 1;
	while(!EventsQueue.isEmpty()) 	//as long as events queue is not empty yet
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step		

		Order* pOrd;	
		Cook* pCook;	
		/// VIP orders
		if (!waitingVIPOrders.empty()) 
		{
			if (!avVIPCooks.empty())
			{
				// move orders
				rmvwaitingVIPOrders(pOrd);
				pOrd->setStatus(SRV);
				AddtosrvVIPOrders(pOrd);

				// move cooks
				pCook = avVIPCooks.top();
				avVIPCooks.pop();
				pCook->setStatus(NAV);
				pCook->setAOrder(pOrd);
				navVIPCooks.push(pCook);
			}
			else if (!avNORCooks.empty())
			{
				// move orders
				rmvwaitingVIPOrders(pOrd);
				pOrd->setStatus(SRV);
				AddtosrvVIPOrders(pOrd);

				// move cooks
				avNORCooks.pop();
				pCook->setStatus(NAV);
				pCook->setAOrder(pOrd);
				navNORCooks.push(pCook);
			}
			else if (!avVEGCooks.empty())
			{
				// move orders
				rmvwaitingVIPOrders(pOrd);
				pOrd->setStatus(SRV);
				AddtosrvVIPOrders(pOrd);

				// move cooks
				avVEGCooks.pop();
				pCook->setStatus(NAV);
				pCook->setAOrder(pOrd);
				navVEGCooks.push(pCook);
			}
		}

		/// Normal Orders



		/// Vegan Orders


		// Each 5 seconds remove orders to done and cooks to available
		if (CurrentTimeStep % 5 == 0) 
		{
			// Normal
			if (!navNORCooks.empty())
			{
				pCook = navNORCooks.top();
				if (CurrentTimeStep >= (pCook->getAOrder()->getArrivalTime() + pCook->getSpeed()))
				{
					navNORCooks.pop();
					pCook->setdOrders(pCook->getdOrders() + 1);
					// move cook
					if (pCook->getdOrders() % 5) // to be modified to number of orders after which is break
					{
						pCook->setStatus(BRK);
						pCook->setBreakCount(CurrentTimeStep);
						brkNORCooks.push(pCook);
					}
					else
					{
						pCook->setStatus(AV);
						avNORCooks.push(pCook);
					}
					// move order
					pOrd = pCook->getAOrder();
					pOrd->setStatus(DONE);
					AddtodoneOrders(pOrd);
					rmvsrvNOROrders(pOrd);
				}
			}
			
			// Vegan

			// Chinese

			// Mexican
			
			// VIP

		}

		// getting back to work out of the break
		// Normal
		if (!brkNORCooks.empty())
		{			
			pCook = navNORCooks.top();
			if (CurrentTimeStep == (pCook->getBreakTime() + pCook->getBreakCount()))
			{
				// move cook
				navNORCooks.pop();
				pCook->setStatus(AV);
				pCook->setBreakCount(0);
				avNORCooks.push(pCook);
			}
		}

		// Vegan

		// VIP

		FillDrawingList();
		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  List handling functions   /////////////////////////////

void Restaurant::AddtowaitingNOROrders(Order* ptr)
{
}

void Restaurant::AddtowaitingVEGOrders(Order* ptr)
{
}

void Restaurant::AddtowaitingCHNOrders(Order* ptr)
{
}

void Restaurant::AddtowaitingMEXOrders(Order* ptr)
{
}

void Restaurant::AddtowaitingVIPOrders(Order* ptr)
{
}

void Restaurant::AddtosrvNOROrders(Order* ptr)
{
}

void Restaurant::AddtosrvVEGOrders(Order* ptr)
{
}

void Restaurant::AddtosrvCHNOrders(Order* ptr)
{
}

void Restaurant::AddtosrvMEXOrders(Order* ptr)
{
}

void Restaurant::AddtosrvVIPOrders(Order* ptr)
{
}

void Restaurant::AddtodoneOrders(Order* ptr)
{
}

void Restaurant::rmvwaitingNOROrders(Order* ptr)
{
}

void Restaurant::rmvwaitingVEGOrders(Order* ptr)
{
}

void Restaurant::rmvwaitingCHNOrders(Order* ptr)
{
}

void Restaurant::rmvwaitingMEXOrders(Order* ptr)
{
}

void Restaurant::rmvwaitingVIPOrders(Order* ptr)
{
}

void Restaurant::rmvsrvNOROrders(Order* ptr)
{
}

void Restaurant::rmvsrvVEGOrders(Order* ptr)
{
}

void Restaurant::rmvsrvCHNOrders(Order* ptr)
{
}

void Restaurant::rmvsrvMEXOrders(Order* ptr)
{
}

void Restaurant::rmvsrvVIPOrders(Order* ptr)
{
}

void Restaurant::rmvdoneOrders(Order* ptr)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////


