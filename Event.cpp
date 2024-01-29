#include "Event.h"

Event::Event(Company* ptr,const Time& eventtime,int id)
{
	Event_Time = eventtime;
	Companyptr = ptr;
	ID = id;
}
Time Event::getTime() {
	return Event_Time;
}
