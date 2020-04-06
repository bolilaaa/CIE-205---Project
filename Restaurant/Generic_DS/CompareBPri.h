#pragma once
#include "../Rest/Cook.h"
using namespace std;

class CompareBPri
{
public:
	bool operator()(Cook*& C1, Cook*& C2) // Returns true if t1 is earlier than t2
	{
		if ((C1->getBreakCount() + C1->getBreakTime()) > (C2->getBreakCount() + C2->getBreakTime())) return true;
		return false;
	}
};

