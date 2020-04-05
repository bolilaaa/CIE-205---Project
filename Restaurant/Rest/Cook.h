#pragma once

#include "..\Defs.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	// for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		// dishes it can prepare in one clock tick (in one timestep)
	int breaktime;  // break after serving n consecutive orders.
	COOK_STATUS status; // for each cook there is a corresponding status (Available, in-available)

public:
	Cook();
	Cook(int ID, ORD_TYPE type);
	virtual ~Cook();

	// setters
	int GetID() const;
	ORD_TYPE GetType() const;
	int getSpeed() const;
	int getBreakTime() const;
	COOK_STATUS getStatus() const;


	// getters
	void setID(int);
	void setType(ORD_TYPE) ;
	void setSpeed(int sp);
	void setBreakTime(int bt);
	void setStatus(COOK_STATUS);
};
