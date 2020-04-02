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


void Cook::setID(int id)
{
	ID = id;
}
void Cook::setSpeed(int sp) {
	speed = sp;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
int Cook::getSpeed() const {
	return speed;
}


