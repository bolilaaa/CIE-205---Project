#pragma once

#include "..\Defs.h"
#include "Order.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	// for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		// dishes it can prepare in one clock tick (in one timestep)
	int breaktime;  // break after serving n consecutive orders.
	int breakorders;
	int breakcount; 
	COOK_STATUS status; // for each cook there is a corresponding status (Available, in-available)
	int dOrders;
	Order* assignedOrder;
	double priority; 

public:
	Cook();
	Cook(int ID, ORD_TYPE type);
	virtual ~Cook();

	// getters
	int GetID() const;
	ORD_TYPE GetType() const;
	int getSpeed() const;
	int getBreakTime() const;
	int getBreakOrders() const;
	int getBreakCount() const;
	COOK_STATUS getStatus() const;
	int getdOrders() const;
	Order* getAOrder() const;
	double getPriority() const;


	// setters
	void setID(int);
	void setType(ORD_TYPE) ;
	void setSpeed(int sp);
	void setBreakTime(int bt);
	void setBreakOrders(int bt);
	void setBreakCount(int bt);
	void setStatus(COOK_STATUS);
	void setdOrders(int);
	void setAOrder(Order*& pOrd);
	void setPriority(double r);
};
