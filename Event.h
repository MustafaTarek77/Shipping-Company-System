#pragma once
#include"Time.h"
class Company;

class Event
{
protected:
	Time Event_Time;
	Company* Companyptr;
	int ID;
public:
	Event(Company* ptr,const Time& eventtime,int id);
	virtual void Execute() = 0;
	Time getTime();
	
};

