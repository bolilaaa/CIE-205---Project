#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	double OrdSize;		//order size
	ORD_TYPE OrdType;	//order type: Normal, vegan, VIP	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, double oMoney, double oSize);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant* ptr);		//override execute function
	virtual void Promote(Restaurant* ptr);		//override promote function
	virtual void Cancel(Restaurant* ptr);		//override cancel function

};


#endif