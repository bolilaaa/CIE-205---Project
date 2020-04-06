#include "..\Restaurant\Cancel.h"
#include "..\Restaurant\Rest\Restaurant.h"
#include "..\Restaurant\Events\Event.h"
#include "..\Restaurant\Rest\Order.h"
#include "Events/ArrivalEvent.h"

Cancel::Cancel(int EveTime, int OrdID) :Event(EveTime, OrdID)
{
	eventType = CANCEL;
}
void Cancel::Execute(Restaurant* pRest)
{
	if (OrdType == TYPE_NRM) { // [[Problem]]: OrdType Can not be defined 
		Order* pOrd = new Order(OrderID, OrdType);
		pRest->rmvsrvNOROrders(pOrd);

	}
	
}