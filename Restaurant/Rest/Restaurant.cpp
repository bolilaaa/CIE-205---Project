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

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

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

}

void Restaurant::LoadAll(string filename) {
	int Num_of_events; //variable to read the number of events from the file
	int BO, BN, BG, BV, SN, SG, SV; //variables to read cooks speed ranges and break times
	file_load.open(filename.c_str()); //opening the file
	file_load >> numCNOR >> numCVEG >> numCVIP >> SN >> SG >> SV >> BO >> BN >> BG >> BV >> AutoPromotion;
	//Intializing Cooks lists
	Cook* CK;
	for (int i = 0; i < numCVIP; i++) {
		CK = new Cook(i + 1, TYPE_VIP);
		CK->setSpeed(SV);
		CK->setBreakTime(BV);
		AddtoavVIPCooks(CK);
	}
	for (int i = 0; i < numCVEG; i++) {
		CK = new Cook(i + 1, TYPE_VGAN);
		CK->setSpeed(SG);
		CK->setBreakTime(BG);
		AddtoavVEGCooks(CK);
	}
	for (int i = 0; i < numCNOR; i++) {
		CK = new Cook(i + 1, TYPE_NRM);
		CK->setSpeed(SN);
		CK->setBreakTime(BN);
		AddtoavNORCooks(CK);
	}

	file_load >> Num_of_events;
	char type; //to read the event type
	enum CurROType {N, G, C, M, V}dir;
	char CurReadOrderType; // to read Order type
	ORD_TYPE CurOrderType; //as the arrival event's constructor needs a parameter from the typr ORD_Type
	int CurTime; int CurID; int CurSize; double CurCost; //variables to read from the file
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
	// Taking the input and initializing the events
	string filename;
	pGUI->PrintMessage("Simulation Mode. Enter INPUT file name:");
	filename = pGUI->GetString().c_str();	//get user input as a string
	LoadAll(filename);
	pGUI->PrintMessage("CLICK to continue");
	pGUI->waitForClick();

	
	Event* pEv;
	Order* pOrd;
	srand(time(NULL));		
	int EvTime = 0;
	int O_id = 1;	
	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		O_id += (rand()%4+1);		
		int OType = rand()%TYPE_CNT;	//Randomize order type		
		EvTime += (rand()%5+1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}	

	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;
	

	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		

/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks
		
		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for(int i=0; i<C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);
		
		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);
		
		for(int i=0; i<size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete []pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	


	//while (!StopRunning)
//{
//	//VIP Order
//	if (!waitingVIPOrders.empty()) {
//		if (!avVIPCooks.isEmpty())
//		{
//			rmvwaitingVIPOrders(pOrd);
//			pOrd->setStatus(SRV);
//			AddtosrvVIPOrders(pOrd);

//			rmvavVIPCooks;
//		}

//	}
//}
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

void Restaurant::AddtoavNORCooks(Cook* ptr)
{
}

void Restaurant::AddtoavVEGCooks(Cook* ptr)
{
}

void Restaurant::AddtoavCHNCooks(Cook* ptr)
{
}

void Restaurant::AddtoavMEXCooks(Cook* ptr)
{
}

void Restaurant::AddtoavVIPCooks(Cook* ptr)
{
}

void Restaurant::AddtonavNORCooks(Cook* ptr)
{
}

void Restaurant::AddtonavVEGCooks(Cook* ptr)
{
}

void Restaurant::AddtonavCHNCooks(Cook* ptr)
{
}

void Restaurant::AddtonavMEXCooks(Cook* ptr)
{
}

void Restaurant::AddtonavVIPCooks(Cook* ptr)
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

void Restaurant::rmvavNORCooks(Cook* ptr)
{
}

void Restaurant::rmvavVEGCooks(Cook* ptr)
{
}

void Restaurant::rmvavCHNCooks(Cook* ptr)
{
}

void Restaurant::rmvavMEXCooks(Cook* ptr)
{
}

void Restaurant::rmvavVIPCooks(Cook* ptr)
{
}

void Restaurant::rmvnavNORCooks(Cook* ptr)
{
}

void Restaurant::rmvnavVEGCooks(Cook* ptr)
{
}

void Restaurant::rmvnavCHNCooks(Cook* ptr)
{
}

void Restaurant::rmvnavMEXCooks(Cook* ptr)
{
}

void Restaurant::rmvnavVIPCooks(Cook* ptr)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////


