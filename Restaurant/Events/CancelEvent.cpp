#include "CancelEvent.h"
#include "..\Rest\Restaurant.h"

CancelEvent::CancelEvent(int eTime, int oID) :Event(eTime, oID)
{

}

void CancelEvent::Execute(Restaurant* pRest)
{
	Order* pOrd;
	Queue<Order*> tempQ;
	while (pRest->waitingNOROrders.dequeue(pOrd))
	{
		if (pOrd->GetID() == OrderID)
		{
			continue;
		}
		else
		{
			tempQ.enqueue(pOrd);
		}
	}
	while (tempQ.dequeue(pOrd))
	{
		pRest->waitingNOROrders.enqueue(pOrd);
	}
}