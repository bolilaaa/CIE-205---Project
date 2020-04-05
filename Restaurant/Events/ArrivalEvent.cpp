#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
#include "..\Rest\Restaurant.cpp"



ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID, OrdType);
	//checks the order type and adds each type to its appropriate list
	if (OrdType == TYPE_VIP) {
		double pri = OrdMoney / (EventTime * OrdDistance); //Priority equation
		pOrd->Setpriority(pri);
		pOrd->SetDistance(OrdDistance);
		pOrd->setMoney(OrdMoney);
		pOrd->setArrivalTime(EventTime);
		pOrd->setStatus(WAIT);
		pRest->AddtowaitingVIPOrders(pOrd);
	}
	else if (OrdType == TYPE_NRM) {
		pOrd->setStatus(WAIT);
		pOrd->SetDistance(OrdDistance);
		pOrd->setArrivalTime(EventTime);
		pOrd->setMoney(OrdMoney);
		pRest->AddtowaitingNOROrders(pOrd);
	}
	else if (OrdType == TYPE_VGAN) {
		pOrd->setStatus(WAIT);
		pOrd->SetDistance(OrdDistance);
		pOrd->setArrivalTime(EventTime);
		pOrd->setMoney(OrdMoney);
		pRest->AddtowaitingVEGOrders(pOrd);
	}
}
void ArrivalEvent::Promote(Restaurant* ptr)
{
	if (OrdType == TYPE_NRM) {
		Order* pOrd = new Order(OrderID, OrdType);
		ptr-> AddtowaitingVIPOrders(pOrd);
	}
}
void ArrivalEvent::Cancel(Restaurant* ptr)
{
	if (OrdType == TYPE_NRM) {
		Order* pOrd = new Order(OrderID, OrdType);
		ptr->rmvsrvNOROrders(pOrd);
	
	}
	
}