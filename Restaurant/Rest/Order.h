#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	double totalMoney;	//Total order money
	int ArrTime, ServTime, FinishTime, WaitTime = 0;	//arrival, service start, and finish times
	double priority; // added // 
	int size;

public:
	Order(int ID, ORD_TYPE r_Type);
	Order(int ID, ORD_TYPE r_Type, double pir); //constructor for VIP orders
	virtual ~Order();

	//Setters // 
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
	ORD_STATUS getStatus() const;

	int getArrivalTime() const;
	int getServTime() const;
	int getFinishTime() const;
	int getWaitTime() const;
	int getSize() const; // mark // 
	double getMoney() const; // price
	double Getpriority() const;
	void increamentWaitTime();
};

#endif