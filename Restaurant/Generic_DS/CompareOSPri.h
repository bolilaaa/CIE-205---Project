#pragma once
#include "../Rest/Cook.h"

class CompareOSPri
{
public:
	bool operator()(Order*& O1, Order*& O2) // Returns true if t1 is earlier than t2
	{
		if (O1->getFinishTime() > O2->getFinishTime()) return true;
		return false;
	}
};

