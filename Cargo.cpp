#include "Cargo.h"
#include"Truck.h"

Cargo::Cargo(const Time& pre, const int& L, const int& D, const int& C,const int& id) :Preparation(pre), LoadTime(L), Distance(D), Cost(C)
{
	ID = id;
	isloaded = false;
}
Cargo::Cargo(const Cargo& c) :Preparation(c.getPreparation()), LoadTime(c.getLoadTime()), Distance(c.getDistance()), Cost(c.getCost()) {

}
void Cargo::setCost(const int& c) {
	if (c > 0)
		Cost = c;
}
void Cargo::setDistance(const int& D) {

	if (D > 0)
		Distance = D;
}
void Cargo::setLoadTime(const int& L) {
	if (L > 0)
		LoadTime = L;

}
void Cargo::setPreparation(const Time& t) {
	Preparation = t;   //we can overload the = operator in time class and also make func.isValid() "bool" in time
}
int Cargo::getCost()const {
	return Cost;

}
bool Cargo::IsLoaded() const
{
	return isloaded;
}
void Cargo::SetIsLoaded(bool l)
{
	isloaded = l;
}

int Cargo::getDistance()const {
	return Distance;
}
int Cargo::getLoadTime()const {
	return LoadTime;
}
Time Cargo::getPreparation()const {
	return Preparation;
}


void Cargo::SetId(int id)
{
	ID = id;
}

int Cargo::GetID()const
{
	return ID;
}



bool Cargo::operator==(Cargo* c)
{
	if (ID == c->ID)
		return true;
	else
		return false;
}

bool Cargo::operator==(int n)
{
	if (ID == n)
		return true;
	else
		return false;
}

Cargo::~Cargo() {

}


/*********************************************************************************************/
int Cargo::GetCDT()
{
	return truck->GetMoveTime().transfHours()+Distance/truck->GetSpeed()+LoadTime;
}

void Cargo::Set_Truck(Truck* t)
{
	truck = t;
}

void Cargo::SetWaitingTime(Time t)
{
	Waiting_Time = t;
}

Time Cargo::GetWaitingTime()
{
	return Waiting_Time;
}

int Cargo::GetTruckID()
{
	return truck->GetID();
}

