#include <cstdlib>
#include <time.h>
#include <iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\PromoteEvent.h"
#include "..\Events\CancelEvent.h"



Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		INTERACT();
		break;
	case MODE_STEP:
		STEPBYSTEP();
		break;
	case MODE_SLNT:
		SILENT();
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

void Restaurant::Work(int CurrentTimeStep, string* VIParr, string* Narr, string* Garr, int& Vc, int& Nc, int& Gc)
{
	Order* pOrd;
	Cook* pCook;
	/// VIP orders
	if (!waitingVIPOrders.empty())
	{
		if (!avVIPCooks.empty())
		{
			// move cooks
			avVIPCooks.deleteMax(pCook);
			pCook->setStatus(NAV);

			// move orders
			rmvwaitingVIPOrders(pOrd);
			pOrd->setStatus(SRV);
			pOrd->setStartSrvTime(CurrentTimeStep);
			pCook->setAOrder(pOrd);
			pOrd->setFinTime(CurrentTimeStep + pCook->getSpeed());

			// add with pri
			navVIPCooks.insert(-(pCook->getAOrder()->getFinishTime()), pCook);
			AddtosrvVIPOrders(-(pOrd->getFinishTime()), pOrd);

			VIParr[0] = "V" + to_string(pCook->GetID());
			VIParr[1] = "V" + to_string(pOrd->GetID());
		}
		else if (!avNORCooks.empty())
		{
			// move cooks
			avNORCooks.deleteMax(pCook);
			pCook->setStatus(NAV);

			// move orders
			rmvwaitingVIPOrders(pOrd);
			pOrd->setStatus(SRV);
			pOrd->setStartSrvTime(CurrentTimeStep);
			pCook->setAOrder(pOrd);
			pOrd->setFinTime(CurrentTimeStep + pCook->getSpeed());

			// add with pri
			navNORCooks.insert(-(pCook->getAOrder()->getFinishTime()), pCook);
			AddtosrvVIPOrders(-(pOrd->getFinishTime()), pOrd);

			VIParr[0] = "N" + to_string(pCook->GetID());
			VIParr[1] = "V" + to_string(pOrd->GetID());
		}
		else if (!avVEGCooks.empty())
		{
			// move cooks
			avVEGCooks.deleteMax(pCook);
			pCook->setStatus(NAV);

			// move orders
			rmvwaitingVIPOrders(pOrd);
			pOrd->setStatus(SRV);
			pOrd->setStartSrvTime(CurrentTimeStep);
			pCook->setAOrder(pOrd);
			pOrd->setFinTime(CurrentTimeStep + pCook->getSpeed());

			// add with pri
			navVEGCooks.insert(-(pCook->getAOrder()->getFinishTime()), pCook);
			AddtosrvVIPOrders(-(pOrd->getFinishTime()), pOrd);

			VIParr[0] = "G" + to_string(pCook->GetID());
			VIParr[1] = "V" + to_string(pOrd->GetID());
		}
	}

	/// Vegan Orders
	if (!waitingVEGOrders.isEmpty())
	{
		if (!avVEGCooks.empty())
		{
			// move cooks
			avVEGCooks.deleteMax(pCook);
			pCook->setStatus(NAV);

			// move orders
			rmvwaitingVEGOrders(pOrd);
			pOrd->setStatus(SRV);
			pOrd->setStartSrvTime(CurrentTimeStep);
			pCook->setAOrder(pOrd);
			pOrd->setFinTime(CurrentTimeStep + pCook->getSpeed());

			// add with pri
			navVEGCooks.insert(-(pCook->getAOrder()->getFinishTime()), pCook);
			AddtosrvVEGOrders(-(pOrd->getFinishTime()), pOrd);

			Garr[0] = "G" + to_string(pCook->GetID());
			Garr[1] = "G" + to_string(pOrd->GetID());
		}
	}

	/// Normal Orders
	if (!waitingNOROrders.isEmpty())
	{
		if (!avNORCooks.empty())
		{
			// move cooks
			avNORCooks.deleteMax(pCook);
			pCook->setStatus(NAV);

			// move orders
			rmvwaitingNOROrders(pOrd);
			pOrd->setStatus(SRV);
			pOrd->setStartSrvTime(CurrentTimeStep);
			pCook->setAOrder(pOrd);
			pOrd->setFinTime(CurrentTimeStep + pCook->getSpeed());

			// add with pri
			navNORCooks.insert(-(pCook->getAOrder()->getFinishTime()), pCook);
			AddtosrvNOROrders(-(pOrd->getFinishTime()), pOrd);

			Narr[0] = "N" + to_string(pCook->GetID());
			Narr[1] = "N" + to_string(pOrd->GetID());
		}
		else if (!avVIPCooks.empty())
		{
			// move cooks
			avVIPCooks.deleteMax(pCook);
			pCook->setStatus(NAV);

			// move orders
			rmvwaitingNOROrders(pOrd);
			pOrd->setStatus(SRV);
			pOrd->setStartSrvTime(CurrentTimeStep);
			pCook->setAOrder(pOrd);
			pOrd->setFinTime(CurrentTimeStep + pCook->getSpeed());

			// add with pri
			navVIPCooks.insert(-(pCook->getAOrder()->getFinishTime()), pCook);
			AddtosrvNOROrders(-(pOrd->getFinishTime()), pOrd);

			Narr[0] = "V" + to_string(pCook->GetID());
			Narr[1] = "N" + to_string(pOrd->GetID());
		}
	}

	// Normal
	if (!navNORCooks.empty())
	{
		navNORCooks.peekFront(pCook);
		if (CurrentTimeStep >= pCook->getAOrder()->getFinishTime())
		{
			navNORCooks.deleteMax(pCook);
			pCook->setdOrders(pCook->getdOrders() + 1);
			// move cook
			if (pCook->getdOrders() % pCook->getBreakOrders() == 0) // to be modified to number of orders after which is break
			{
				pCook->setStatus(BRK);
				pCook->setBreakCount(CurrentTimeStep);
				brkNORCooks.insert(-(pCook->getBreakTime() + pCook->getBreakCount()), pCook);
			}
			else
			{
				pCook->setStatus(AV);
				avNORCooks.insert(pCook->getSpeed(), pCook);
			}
			// move order
			pOrd = pCook->getAOrder();
			pOrd->setStatus(DONE);
			AddtodoneOrders(pOrd);
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				rmvsrvNOROrders(pOrd);
				Nc++;
				break;
			case TYPE_VGAN:
				rmvsrvVEGOrders(pOrd);
				Gc++;
				break;
			case TYPE_VIP:
				rmvsrvVIPOrders(pOrd);
				Vc++;
				break;
			}
		}
	}

	// Vegan
	if (!navVEGCooks.empty())
	{
		navVEGCooks.peekFront(pCook);
		if (CurrentTimeStep >= (pCook->getAOrder()->getFinishTime()))
		{
			navVEGCooks.deleteMax(pCook);
			pCook->setdOrders(pCook->getdOrders() + 1);
			// move cook
			if (pCook->getdOrders() % pCook->getBreakOrders() == 0) // to be modified to number of orders after which is break
			{
				pCook->setStatus(BRK);
				pCook->setBreakCount(CurrentTimeStep);
				brkVEGCooks.insert(-(pCook->getBreakTime() + pCook->getBreakCount()), pCook);
			}
			else
			{
				pCook->setStatus(AV);
				avVEGCooks.insert(pCook->getSpeed(), pCook);
			}
			// move order
			pOrd = pCook->getAOrder();
			pOrd->setStatus(DONE);
			AddtodoneOrders(pOrd);
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				rmvsrvNOROrders(pOrd);
				Nc++;
				break;
			case TYPE_VGAN:
				rmvsrvVEGOrders(pOrd);
				Gc++;
				break;
			case TYPE_VIP:
				rmvsrvVIPOrders(pOrd);
				Vc++;
				break;
			}
		}
	}

	// VIP
	if (!navVIPCooks.empty())
	{
		navVIPCooks.peekFront(pCook);
		if (CurrentTimeStep >= (pCook->getAOrder()->getFinishTime()))
		{
			navVIPCooks.deleteMax(pCook);
			pCook->setdOrders(pCook->getdOrders() + 1);
			// move cook
			if (pCook->getdOrders() % pCook->getBreakOrders() == 0) // to be modified to number of orders after which is break
			{
				pCook->setStatus(BRK);
				pCook->setBreakCount(CurrentTimeStep);
				brkVIPCooks.insert(-(pCook->getBreakTime() + pCook->getBreakCount()), pCook);
			}
			else
			{
				pCook->setStatus(AV);
				avVIPCooks.insert(pCook->getSpeed(), pCook);
			}
			// move order
			pOrd = pCook->getAOrder();
			pOrd->setStatus(DONE);
			AddtodoneOrders(pOrd);
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				rmvsrvNOROrders(pOrd);
				Nc++;
				break;
			case TYPE_VGAN:
				rmvsrvVEGOrders(pOrd);
				Gc++;
				break;
			case TYPE_VIP:
				rmvsrvVIPOrders(pOrd);
				Vc++;
				break;
			}
		}
	}

	// getting back to work out of the break
	// Normal
	if (!brkNORCooks.empty())
	{
		brkNORCooks.peekFront(pCook);
		if (CurrentTimeStep == (pCook->getBreakTime() + pCook->getBreakCount()))
		{
			// move cook
			brkNORCooks.deleteMax(pCook);
			pCook->setStatus(AV);
			pCook->setBreakCount(0);
			avNORCooks.insert(pCook->getSpeed(), pCook);
		}
	}

	// Vegan
	if (!brkVEGCooks.empty())
	{
		brkVEGCooks.peekFront(pCook);
		if (CurrentTimeStep == (pCook->getBreakTime() + pCook->getBreakCount()))
		{
			// move cook
			brkVEGCooks.deleteMax(pCook);
			pCook->setStatus(AV);
			pCook->setBreakCount(0);
			avVEGCooks.insert(pCook->getSpeed(), pCook);
		}
	}

	// VIP
	if (!brkVIPCooks.empty())
	{
		brkVIPCooks.peekFront(pCook);
		if (CurrentTimeStep == (pCook->getBreakTime() + pCook->getBreakCount()))
		{
			// move cook
			brkVIPCooks.deleteMax(pCook);
			pCook->setStatus(AV);
			pCook->setBreakCount(0);
			avVIPCooks.insert(pCook->getSpeed(), pCook);
		}
	}
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
}

void Restaurant::LoadAll(string filename) {
	int Num_of_events; //variable to read the number of events from the file
	int BO, BN, BG, BV,BC, BM, SN, SG, SV,SC,SM; //variables to read cooks speed ranges and break times
	file_load.open(filename.c_str()); //opening the file
	file_load >> numCNOR >> numCVEG >> numCVIP >> SN >> SG >> SV >> BO >> BN >> BG >> BV >> AutoPromotion;
	//Intializing Cooks lists (cooks will be pushed directly but orders will use functions)
	Cook* CK;
	for (int i = 0; i < numCVIP; i++) {
		CK = new Cook(i + 1, TYPE_VIP);
		CK->setSpeed(SV/2 + rand() % SV);
		CK->setBreakTime(BV);
		CK->setBreakOrders(BO);
		avVIPCooks.insert(CK->getSpeed(), CK);
	}
	for (int i = 0; i < numCVEG; i++) {
		CK = new Cook(i + 1, TYPE_VGAN);
		CK->setSpeed(SG / 2 + rand() % SG);
		CK->setBreakTime(BG);
		CK->setBreakOrders(BO);
		avVEGCooks.insert(CK->getSpeed(), CK);
	}
	for (int i = 0; i < numCNOR; i++) {
		CK = new Cook(i + 1, TYPE_NRM);
		CK->setSpeed(SN / 2 + rand() % SN);
		CK->setBreakTime(BN);
		CK->setBreakOrders(BO);
		avNORCooks.insert(CK->getSpeed(), CK);
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
			case 'N':
				CurOrderType = TYPE_NRM;
				break;
			case 'G':
				CurOrderType = TYPE_VGAN;
				break;
			case 'V':
				CurOrderType = TYPE_VIP;
				break;
			}
			CurEvent = new ArrivalEvent(CurTime, CurID, CurOrderType, CurCost, CurSize);
			break;
		case 'X':
			file_load >> CurTime >> CurID;
			CurEvent = new CancelEvent(CurTime, CurID); 
			break;
		case 'P':
			file_load >> CurTime >> CurID >> ExMoney;
			CurEvent = new PromoteEvent(CurTime, CurID, ExMoney);
			break;
		}
		EventsQueue.enqueue(CurEvent);
	}
	file_load.close();
}

void Restaurant::Output(string filename, int& Nc, int& Gc, int& Vc) {
	Order* ord;
	double sumWait = 0, sumSRV = 0;
	file_save.open(filename.c_str()); //opening the file
	file_save << "FT     ID     AT    WT    ST" << endl;
	//getting the data of each order from the done queue
	while (!doneOrders.isEmpty()) {
		doneOrders.dequeue(ord);
		file_save << ord->getFinishTime() << "      " << ord->GetID() << "      " << ord->getArrivalTime() << "     " << (ord->getFinishTime() - ord->getArrivalTime()) << "     " << (ord->getFinishTime() - ord->getServTime()) << endl;
		sumWait += (ord->getFinishTime() - ord->getArrivalTime());
		sumSRV += (ord->getFinishTime() - ord->getServTime());
		delete ord;
	}
	file_save << "..........................................." << endl;
	file_save << "..........................................." << endl;
	int SumOrd = Vc + Nc + Gc;
	file_save << "Orders: " << SumOrd << "  [Norm : " << Nc << ", Veg : " << Gc << ", VIP : " << Vc << " ]" << endl;
	file_save << "cooks: " << numCNOR + numCVEG + numCVIP << "  [Norm : " << numCNOR << ", Veg : " << numCVEG << ", VIP : " << numCVIP << " ]" << endl;
	file_save << "AVG Wait = " << sumWait / SumOrd << ",  AVG SRV = " << sumSRV / SumOrd << endl;
	file_save << "Auto Promoted : " << AutoPromoted << endl;
	file_save.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  Operation Modes   /////////////////////////////

void Restaurant::INTERACT()
{
	// Taking the input and initializing the cooks and fill the EventsQueue
	string filename;
	pGUI->PrintMessage("Interactive Mode. Enter INPUT file name:");
	filename = pGUI->GetString();	//get user input as a string
	LoadAll(filename);
	pGUI->PrintMessage("CLICK to start");
	pGUI->waitForClick();

	//Now let's start the simulation
	int CurrentTimeStep = 1;

	string VIParr[2] = { "0","0" }, Narr[2]= { "0","0" }, Garr[2]= { "0","0" };
	int dVIP = 0, dN = 0, dG = 0;

	bool Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();

	while (!Stop) 	//as long as events queue is not empty yet
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step		

		Work(CurrentTimeStep, VIParr, Narr, Garr, dVIP, dN, dG);

		FillDrawingList();
		pGUI->UpdateInterface();
		string msg1 = "[TS: " + to_string(CurrentTimeStep) + "]";
		string msg2 = "Waiting VIP Orders: " + to_string(waitingVIPOrders.CountHNodes()) + "         |    Waiting N Orders: " + to_string(waitingNOROrders.CountNodes()) + "       |   Waiting G Orders: " + to_string(waitingVEGOrders.CountNodes());
		string msg3 = "Available VIP Cooks: " + to_string(avVIPCooks.CountHNodes()) + "       |     Available N cooks: " + to_string(avNORCooks.CountHNodes()) + "      |   Available G cooks: " + to_string(avVEGCooks.CountHNodes());
		string msg4 = "Total done VIP Orders: " + to_string(dVIP) + "   |   Total done N Orders: " + to_string(dN) + "   |   Total done G Orders: " + to_string(dG) + "         ||-> CLICK to continue";
		string msg5;
		if (VIParr[0] != "0")
		{
			msg5 += VIParr[0] + "(" + VIParr[1] + ") ";
		}
		if (Narr[0] != "0")
		{
			msg5 += Narr[0] + "(" + Narr[1] + ") ";
		}
		if (Garr[0] != "0")
		{
			msg5 += Garr[0] + "(" + Garr[1] + ") ";
		}

		pGUI->PrintMessage(msg1);
		pGUI->PrintMessage2(msg2);
		pGUI->PrintMessage3(msg3);
		pGUI->PrintMessage4(msg4);
		pGUI->PrintMessage5(msg5);
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
		VIParr[0] = "0"; VIParr[1] = "0"; Narr[0] = "0"; Narr[1] = "0"; Garr[0] = "0"; Garr[1] = "0";
		Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();
	}

	string filenamee;
	pGUI->PrintMessage("Interactive Mode. Enter OUTPUT file name:");
	filenamee = pGUI->GetString();
	Output(filenamee, dN, dG, dVIP);

	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

void Restaurant::STEPBYSTEP()
{
	// Taking the input and initializing the cooks and fill the EventsQueue
	string filename;
	pGUI->PrintMessage("StepByStep Mode. Enter INPUT file name:");
	filename = pGUI->GetString();	//get user input as a string
	LoadAll(filename);
	pGUI->PrintMessage("CLICK to start");
	pGUI->waitForClick();

	//Now let's start the simulation
	int CurrentTimeStep = 1;

	string VIParr[2] = { "0","0" }, Narr[2] = { "0","0" }, Garr[2] = { "0","0" };
	int dVIP = 0, dN = 0, dG = 0;

	bool Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();

	while (!Stop) 	//as long as events queue is not empty yet
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step		

		Work(CurrentTimeStep, VIParr, Narr, Garr, dVIP, dN, dG);

		FillDrawingList();
		pGUI->UpdateInterface();
		string msg1 = "[TS: " + to_string(CurrentTimeStep) + "]";
		string msg2 = "Waiting VIP Orders: " + to_string(waitingVIPOrders.CountHNodes()) + "         |    Waiting N Orders: " + to_string(waitingNOROrders.CountNodes()) + "       |   Waiting G Orders: " + to_string(waitingVEGOrders.CountNodes());
		string msg3 = "Available VIP Cooks: " + to_string(avVIPCooks.CountHNodes()) + "       |     Available N cooks: " + to_string(avNORCooks.CountHNodes()) + "      |   Available G cooks: " + to_string(avVEGCooks.CountHNodes());
		string msg4 = "Total done VIP Orders: " + to_string(dVIP) + "   |   Total done N Orders: " + to_string(dN) + "   |   Total done G Orders: " + to_string(dG) + "        ";
		string msg5;
		if (VIParr[0] != "0")
		{
			msg5 += VIParr[0] + "(" + VIParr[1] + ") ";
		}
		if (Narr[0] != "0")
		{
			msg5 += Narr[0] + "(" + Narr[1] + ") ";
		}
		if (Garr[0] != "0")
		{
			msg5 += Garr[0] + "(" + Garr[1] + ") ";
		}

		pGUI->PrintMessage(msg1);
		pGUI->PrintMessage2(msg2);
		pGUI->PrintMessage3(msg3);
		pGUI->PrintMessage4(msg4);
		pGUI->PrintMessage5(msg5);
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
		VIParr[0] = "0"; VIParr[1] = "0"; Narr[0] = "0"; Narr[1] = "0"; Garr[0] = "0"; Garr[1] = "0";
		Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();
	}

	string filenamee;
	pGUI->PrintMessage("StepByStep Mode. Enter OUTPUT file name:");
	filenamee = pGUI->GetString();
	Output(filenamee, dN, dG, dVIP);

	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

void Restaurant::SILENT()
{
	// Taking the input and initializing the cooks and fill the EventsQueue
	string filename;
	pGUI->PrintMessage("Silent Mode. Enter INPUT file name:");
	filename = pGUI->GetString();	//get user input as a string
	LoadAll(filename);

	//Now let's start the work
	int CurrentTimeStep = 1;

	string VIParr[2], Narr[2], Garr[2];
	int dVIP = 0, dN = 0, dG = 0;

	bool Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();

	while (!Stop) 	//as long as events queue is not empty yet
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step		

		Work(CurrentTimeStep, VIParr, Narr, Garr, dVIP, dN, dG);

		CurrentTimeStep++;	//advance timestep

		Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();
	}

	string filenamee;
	pGUI->PrintMessage("Silent Mode. Enter OUTPUT file name:");
	filenamee = pGUI->GetString();
	Output(filenamee, dN, dG, dVIP);

	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

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

	string VIParr[2], Narr[2], Garr[2];
	int dVIP = 0, dN = 0, dG = 0;

	bool Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();

	while(!Stop) 	//as long as events queue is not empty yet
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step		

		Work(CurrentTimeStep, VIParr, Narr, Garr, dVIP, dN, dG);
		
		FillDrawingList();
		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();

		Stop = EventsQueue.isEmpty() && waitingVIPOrders.empty() && waitingNOROrders.isEmpty() && waitingVEGOrders.isEmpty() && srvVIPOrders.empty() && srvNOROrders.empty() && srvVEGOrders.empty() && navVIPCooks.empty() && navNORCooks.empty() && navVEGCooks.empty();
	}

	string filenamee;
	pGUI->PrintMessage("Simulation Mode. Enter OUTPUT file name:");
	filenamee = pGUI->GetString();
	Output(filenamee, dN, dG, dVIP);

	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  List handling functions   /////////////////////////////
/////// waiting ///////
void Restaurant::AddtowaitingNOROrders(Order*& ptr)
{
	waitingNOROrders.enqueue(ptr);
}

void Restaurant::AddtowaitingVEGOrders(Order*& ptr)
{
	waitingVEGOrders.enqueue(ptr);
}

void Restaurant::AddtowaitingVIPOrders(Order*& ptr)
{
	waitingVIPOrders.insert(ptr->Getpriority(),ptr);
}


/////// in service ///////
void Restaurant::AddtosrvNOROrders(int pri, Order*& ptr)
{
	srvNOROrders.insert(pri, ptr);
}

void Restaurant::AddtosrvVEGOrders(int pri, Order*& ptr)
{
	srvVEGOrders.insert(pri, ptr);
}


void Restaurant::AddtosrvVIPOrders(int pri, Order*& ptr)
{
	srvVIPOrders.insert(pri, ptr);
}

/////// add DONE ///////
void Restaurant::AddtodoneOrders(Order*& ptr)
{
	doneOrders.enqueue(ptr);
}


/////// remove waiting ///////
void Restaurant::rmvwaitingNOROrders(Order*& ptr)
{
	waitingNOROrders.dequeue(ptr);
}

void Restaurant::rmvwaitingVEGOrders(Order*& ptr)
{
	waitingVEGOrders.dequeue(ptr);
}

void Restaurant::rmvwaitingVIPOrders(Order*& ptr)
{
	waitingVIPOrders.deleteMax(ptr);
}


/////// remove service ///////***
void Restaurant::rmvsrvNOROrders(Order*& ptr)
{
	srvNOROrders.deleteMax(ptr);
}

void Restaurant::rmvsrvVEGOrders(Order*& ptr)
{
	srvVEGOrders.deleteMax(ptr);
}

void Restaurant::rmvsrvVIPOrders(Order*& ptr)
{
	srvVIPOrders.deleteMax(ptr);
}


/////// remove DONE ///////
void Restaurant::rmvdoneOrders(Order* &ptr)
{
	doneOrders.dequeue(ptr);
}

//////////////////////////////////////////////////////////////////////////////////////////////
