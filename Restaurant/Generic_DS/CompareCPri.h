#pragma once
#include "../Rest/Cook.h"

class CompareCPri
{
public:
	bool operator()(Cook*& C1, Cook*& C2) // Returns true if t1 is earlier than t2
	{
		if (C1->getSpeed() > C2->getSpeed()) return true;
		return false;
	}
};

