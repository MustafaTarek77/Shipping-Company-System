#pragma once
#include"Event.h"

class Prompote_Event:public Event
{
	int ID;
	int extracost;
public:
	Prompote_Event(Company* ptr,const Time& eventtime,int id,int extramoney);
	virtual void Execute();  
};

