#include "..\Restaurant\Promote.h"
#include "..\Restaurant\Rest\Restaurant.h"
#include "..\Restaurant\Events\Event.h"
#include "..\Restaurant\Rest\Order.h"
#include "Events/ArrivalEvent.h"

Promote::Promote(int EveTime, int OrdID, double AdditMoney) : Event(EveTime, OrdID)
{
	eventType = CANCEL;
}
void Promote::Execute(Restaurant* pRest)
{
		Order* P;
		if (OrdType == TYPE_NRM) { // [[Problem]]: OrdType Can not be defined 
			P->setType(TYPE_VIP);
			double pri = (P->getMoney() + PromotionMoney) / (EventTime); //Priority equation
			P->Setpriority(pri);
			pRest->AddtowaitingVIPOrders(P);
		}
	

}