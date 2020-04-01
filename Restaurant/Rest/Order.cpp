#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::Order(int id, ORD_TYPE r_Type, double pir) {
	ID = id;
	type = r_Type;
	status = WAIT;
	priority = pir;
}//constructor for VIP orders



/////////////////////////////////////////////////////////////////////////////
//Setters // 
void Order::setStatus(ORD_STATUS s)
{
	status = s;
}
void Order::SetDistance(int d)
{
	Distance = d > 0 ? d : 0;
}

void Order::Setpriority(double r) {
	priority = r;
}
void Order::setWaitTime(int time) {
	WaitTime = time;
}
void Order::setMoney(double Cost) {
	totalMoney = Cost;
}
void Order::setArrivalTime(int Arr) {
	ArrTime = Arr;
}
void Order::setType(ORD_TYPE r_Type) {
	type = r_Type;
}
void Order::setStartSrvTime(int time) {
	ServTime = time;
}
void Order::setFinTime(int time) {
	FinishTime = time;
}

/////////////////////////////////////////////////////////////////////////////
// Getters //
int Order::GetID()
{
	return ID;
}

ORD_TYPE Order::GetType() const
{
	return type;
}

int Order::GetDistance() const
{
	return Distance;
}


ORD_STATUS Order::getStatus() const
{
	return status;
}


int Order::getServTime() const {
	return ServTime;
}
int Order::getFinishTime() const {
	return FinishTime;
}
int Order::getWaitTime() const {
	return WaitTime;
}
// int getArrivalTime() const;
double Order::getMoney() const {
	return totalMoney;
}
// price
double Order::Getpriority() const {
	return priority;
}
void Order::increamentWaitTime() {
	WaitTime++;
}








Order::~Order()
{
}