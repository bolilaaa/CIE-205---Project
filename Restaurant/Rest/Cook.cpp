#include "Cook.h"


Cook::Cook()
{
}
Cook::Cook(int id, ORD_TYPE Type) {
	ID = id;
	type = Type;
}

Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


int Cook::getSpeed() const 
{
	return speed;
}


int Cook::getBreakTime() const
{
	return breaktime;
}

COOK_STATUS Cook::getStatus() const
{
	return COOK_STATUS();
}

int Cook::getdOrders() const
{
	return dOrders;
}

Order* Cook::getAOrder() const
{
	return assignedOrder;
}

double Cook::getPriority() const
{
	return priority;
}


void Cook::setID(int id)
{
	ID = id;
}


void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setSpeed(int sp) 
{
	speed = sp;
}


void Cook::setBreakTime(int bt)
{
	breaktime = bt;
}

void Cook::setStatus(COOK_STATUS cs)
{
	status = cs;
}

void Cook::setdOrders(int dOr)
{
	dOrders = dOr;
}

void Cook::setAOrder(Order*& pOrd)
{
	assignedOrder = pOrd;
}

void Cook::setPriority(double r)
{
	priority = r;
}
