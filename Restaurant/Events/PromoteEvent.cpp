#include "PromoteEvent.h"
#include "..\Rest\Restaurant.h"


PromoteEvent::PromoteEvent(int eTime, int oID, double add_money) : Event(eTime, oID)
{
    ExMony = add_money;
}
void PromoteEvent::Execute(Restaurant* pRest)
{
    Order* pOrd;
    Queue<Order*> tempQ;
    while (pRest->waitingNOROrders.dequeue(pOrd))
    {
        if (pOrd->GetID() == OrderID)
        {
            double pri = ((pOrd->getMoney() + ExMony) * pOrd->getSize()) / EventTime; //Priority equation
            pOrd->Setpriority(pri);
            pOrd->setType(TYPE_VIP);
            pOrd->setMoney((pOrd->getMoney() + ExMony));
            pRest->waitingVIPOrders.insert(pri, pOrd);
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