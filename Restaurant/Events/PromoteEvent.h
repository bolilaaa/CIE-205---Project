#ifndef __PROMOTE_EVENT_H_
#define __PROMOTE_EVENT_H_

#include "Event.h"


//class for the arrival event

//class for the arrival event
class PromoteEvent : public Event
{
    double OrdSize;    //order size
    ORD_TYPE OrdType;  //order type: Normal, vegan, VIP                  
    double OrdMoney;
    double Add_Money;
public:
    PromoteEvent(int eTime, int oID, ORD_TYPE oType, double add_money); // calling from order 

    //Add more constructors if needed

    virtual void Execute(Restaurant* pRest);    //override execute function
};


#endif