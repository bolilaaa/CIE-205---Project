#pragma once
#include "..\Restaurant\Rest\Restaurant.h"
#include "..\Restaurant\Events\Event.h"
#include "Events/ArrivalEvent.h"
class Promote : public Event
{
private:
	EVENT_TYPE eventType;
	double PromotionMoney; //Extra money 

public:
	Promote(int EveTime, int OrdID,double AdditMoney); // Constructor
	virtual void Execute(Restaurant* pRest);	//Excute Cancel Event
};



