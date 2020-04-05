#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant              
	double totalMoney;	//Total order money
	int ArrTime, ServTime, FinishTime, WaitTime = 0;	//arrival, service start, and finish times
	double priority; // added // 
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type);
	Order(int ID, ORD_TYPE r_Type, double pir); //constructor for VIP orders
	virtual ~Order();

	//Setters // 
	void SetDistance(int d);
	void setStatus(ORD_STATUS s);

	void Setpriority(double r);
	void setWaitTime(int time);
	void setMoney(double Cost);
	void setArrivalTime(int Arr);
	void setType(ORD_TYPE r_Type);
	void setStartSrvTime(int time);
	void setFinTime(int time);
	void setSize(const int size);

	// Getters //
	int GetID();
	ORD_TYPE GetType() const;
	int GetDistance() const;
	ORD_STATUS getStatus() const;

	int getArrivalTime() const;
	int getServTime() const;
	int getFinishTime() const;
	int getWaitTime() const;
	// int getArrivalTime() const;
	double getSize() const; // mark // 
	double getMoney() const; // price
	double Getpriority() const;
	void increamentWaitTime();
};

#endif