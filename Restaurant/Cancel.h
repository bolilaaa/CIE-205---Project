#pragma once
#include "..\Restaurant\Rest\Restaurant.h"
#include "..\Restaurant\Events\Event.h"
#include "Events/ArrivalEvent.h"
class Cancel : public Event
{
private:
	EVENT_TYPE eventType;

public:
	Cancel(int EveTime, int OrdID); // Constructor
	virtual void Execute(Restaurant* pRest);	//Excute Cancel Event
};



