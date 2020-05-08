#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"



ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, double oMoney, double oSize) : Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney = oMoney;
	OrdSize = oSize;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	Order* pOrd = new Order(OrderID, OrdType);
	//checks the order type and adds each type to its appropriate list
	if (OrdType == TYPE_VIP) {
		double pri = (OrdMoney * OrdSize) / EventTime; //Priority equation
		pOrd->Setpriority(pri);
		pOrd->setSize(OrdSize);
		pOrd->setMoney(OrdMoney);
		pOrd->setArrivalTime(EventTime);
		pOrd->setStatus(WAIT);
		pRest->AddtowaitingVIPOrders(pOrd);
	}
	else if (OrdType == TYPE_NRM) {
		//pRest->crrtimestep >= EventTime + pRest->AutoPromotion
		int countwaitingNOR, countsrvNOR, Tprep, avCookSpeed;
		pRest->waitingNOROrders.toArray(countwaitingNOR);
		pRest->srvNOROrders.toArray(countsrvNOR);
		Tprep = countsrvNOR + countwaitingNOR;

		Cook* pCook;
		if (!pRest->avNORCooks.empty())
		{
			pRest->avNORCooks.peekFront(pCook);
			avCookSpeed = pCook->getSpeed();	
			pRest->navNORCooks.peekFront(pCook);
			avCookSpeed += pCook->getSpeed();
			avCookSpeed /= 2;
		}
		else
		{
			pRest->navNORCooks.peekFront(pCook);
			avCookSpeed = pCook->getSpeed();
		}

		if (EventTime + pRest->AutoPromotion <= pRest->crrtimestep + (Tprep*avCookSpeed))
		{
			pOrd->setSize(OrdSize);
			pOrd->setMoney(OrdMoney);
			pOrd->setArrivalTime(EventTime);
			pOrd->setStatus(WAIT);
			pOrd->setType(TYPE_VIP);
			double pri;
			Order* pOrdTemp;
			if (!pRest->waitingVIPOrders.empty())
			{
				pRest->waitingVIPOrders.peekFront(pOrdTemp);
				pri = pOrdTemp->Getpriority();
			}
			else
			{
				pri = (OrdMoney * OrdSize) / EventTime;
			}
			pRest->waitingVIPOrders.insert(pri, pOrd);
			pRest->AutoPromoted++;
		}
		else
		{
			pOrd->setStatus(WAIT);
			pOrd->setSize(OrdSize);
			pOrd->setArrivalTime(EventTime);
			pOrd->setMoney(OrdMoney);
			pRest->AddtowaitingNOROrders(pOrd);
		}
	}
	else if (OrdType == TYPE_VGAN) {
		pOrd->setStatus(WAIT);
		pOrd->setSize(OrdSize);
		pOrd->setArrivalTime(EventTime);
		pOrd->setMoney(OrdMoney);
		pRest->AddtowaitingVEGOrders(pOrd);
	}
}
//void ArrivalEvent::Promote(Restaurant* ptr)
//{
//	if (OrdType == TYPE_NRM) {
//		Order* pOrd = new Order(OrderID, OrdType);
//		ptr-> AddtowaitingVIPOrders(pOrd);
//	}
//}