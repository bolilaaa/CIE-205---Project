#include "PromoteEvent.h"
#include "..\Rest\Restaurant.h"


PromoteEvent::PromoteEvent(int eTime, int oID, ORD_TYPE oType, double add_money) : Event(eTime, oID)
{
    OrdType = oType;
    Add_Money = add_money;
}
void PromoteEvent::Execute(Restaurant* pRest)
{
    Order* pOrd;
    Queue<Order*> tempQ;
    while (pRest->waitingNOROrders.dequeue(pOrd))
    {
        if (pOrd->GetID() == OrderID)
        {
            double pri = ((pOrd->getMoney() + Add_Money) * OrdSize) / EventTime; //Priority equation
            pOrd->setMoney((pOrd->getMoney() + Add_Money));
            pOrd->Setpriority(pri);

            pRest->AddtowaitingVIPOrders(pOrd);

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