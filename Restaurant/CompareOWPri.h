#pragma once
#include "..\Restaurant\Rest\Order.h"

class CompareOWPri
{
public:
	bool operator()(Order*& O1, Order*& O2) // Returns true if t1 is earlier than t2
	{
		if (O1->Getpriority() < O2->Getpriority()) return true;
		if (O1->Getpriority() == O2->Getpriority() && O1->getFinishTime() < O2->getFinishTime()) return true;
		return false;
	}
};

