#pragma once
#include"Event.h"
class Cancel_Event :public Event
{
private:
	int deletedID;
public:
	Cancel_Event(Company* ptr,const Time& eventtime,int id);
	virtual void Execute();
};

