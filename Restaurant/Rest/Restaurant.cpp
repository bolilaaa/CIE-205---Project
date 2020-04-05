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
	int BO, BN, BG, BV, SN, SG, SV; //variables to read motorcycle speed ranges
	file_load.open(filename.c_str()); //opening the file
	/*PROG_MODE mode = pGUI->getGUIMode();
	if (mode != MODE_SLNT) {
		while (!file_load) {
			pGUI->PrintMessage("Enter an Existing Input File Name: ");
			filename = pGUI->GetString();
			file_load.open(filename.c_str());
		}
	}*/
	file_load >> numCNOR >> numCVEG >> numCVIP >> SN >> SG >> SV >> BO >> BN >> BG >> BV >> AutoPromotion;
	file_load >> Num_of_events;
	srand(time(0));

	//Intializing Cooks lists
	Cook* CK;
	for (int i = 0; i < numCVIP; i++) {
		CK = new Cook(i + 1, TYPE_VIP);
		CK->setSpeed(SV);
		// Here I will put a function to puch every cook in his queue
	}
	for (int i = 0; i < numCVEG; i++) {
		CK = new Cook(i + 1, TYPE_VGAN);
		CK->setSpeed(SG);
		// Here I will put a function to puch every cook in his queue
	}
	for (int i = 0; i < numCNOR; i++) {
		CK = new Cook(i + 1, TYPE_NRM);
		CK->setSpeed(SN);
		// Here I will put a function to puch every cook in his queue
	}

	Event* CurEvent; //pointer to event it points to any class object inherited from event as arrival,cancel and promote
	ORD_TYPE CurOrderType; //as the arrival event's constructor needs a parameter from the typr ORD_Type
	char type; //to read the event type
	int CurTime; int CurID; int CurType; double CurCost; int CurSize; double ExMoney; //variables to read from the file
	for (int i = 0; i < Num_of_events; i++) {
		file_load >> type;
		switch (type)
		{
		case 'R':
			file_load >> CurType >> CurTime >> CurID >> CurSize >> CurCost;
			//CurOrderType = Restaurant::determineOrderType(CurType); here is a function to know the type of order I will add it after finishing resturant class
			switch (CurOrderType)
			{
			case TYPE_NRM:
				//cNRMord++;
				break;
			case TYPE_VGAN:
				//cFROZord++;
				break;
			case TYPE_VIP:
				//cVIPord++;
				break;
			}
			//CurEvent = new ArrivalEvent(CurTime, CurID, CurOrderType, CurCost, CurDist);
			break;
		case 'X':
			file_load >> CurTime >> CurID;
			//CurEvent = new CancelEvent(CurTime, CurID); I will add it after finshing resturant class
			break;
		case 'P':
			file_load >> CurTime >> CurID >> ExMoney;
			//CurEvent = new PormoteEvent(CurTime, CurID, ExMoney);
			break;
		}
		//EventsQueue.rversedenqueue(CurEvent, CurTime);
	}
	file_load.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  Operation Modes   /////////////////////////////

void Restaurant::SIMULATE()
{
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

	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();
		
	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;	
	Cook *pC = new Cook[C_count];
	int cID = 1;

	for(int i=0; i<C_count; i++)
	{
		cID+= (rand()%15+1);	
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand()%TYPE_CNT));
	}	

		
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

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file

	
	
	
	
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

void Restaurant::AddtoavNORCooks(Order* ptr)
{
}

void Restaurant::AddtoavVEGCooks(Order* ptr)
{
}

void Restaurant::AddtoavCHNCooks(Order* ptr)
{
}

void Restaurant::AddtoavMEXCooks(Order* ptr)
{
}

void Restaurant::AddtoavVIPCooks(Order* ptr)
{
}

void Restaurant::AddtonavNORCooks(Order* ptr)
{
}

void Restaurant::AddtonavVEGCooks(Order* ptr)
{
}

void Restaurant::AddtonavCHNCooks(Order* ptr)
{
}

void Restaurant::AddtonavMEXCooks(Order* ptr)
{
}

void Restaurant::AddtonavVIPCooks(Order* ptr)
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

void Restaurant::rmvavNORCooks(Order* ptr)
{
}

void Restaurant::rmvavVEGCooks(Order* ptr)
{
}

void Restaurant::rmvavCHNCooks(Order* ptr)
{
}

void Restaurant::rmvavMEXCooks(Order* ptr)
{
}

void Restaurant::rmvavVIPCooks(Order* ptr)
{
}

void Restaurant::rmvnavNORCooks(Order* ptr)
{
}

void Restaurant::rmvnavVEGCooks(Order* ptr)
{
}

void Restaurant::rmvnavCHNCooks(Order* ptr)
{
}

void Restaurant::rmvnavMEXCooks(Order* ptr)
{
}

void Restaurant::rmvnavVIPCooks(Order* ptr)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////


