#pragma once
#include"Event.h"
#include"Normal_Cargo.h"
#include"Special_Cargo.h"
#include"VIP_Cargo.h"
class Prepartion_Event:public Event
{
private:
	Cargo* newcargo;
	char type;
public:
	Prepartion_Event(Company* ptr, const Time& eventtime, const int& load, const int& distance, const int& cost, char t,int id);
	virtual void Execute();
};

