#include "Prompote_Event.h"
#include"Company.h"

Prompote_Event::Prompote_Event(Company* ptr,const Time& eventtime, int id,int extramoney):Event(ptr,eventtime,id)
{
	ID = id;
	extracost = extramoney;
}

void Prompote_Event::Execute()   //if there is error add char type
{
	Companyptr->PrompoteCargo(ID,extracost,Event_Time);
}
