#include "Cancel_Event.h"
#include"Company.h"

Cancel_Event::Cancel_Event(Company* ptr,const Time& eventtime,int id) :Event(ptr,eventtime,id)
{
	deletedID = id;
}



void Cancel_Event::Execute()
{
	Companyptr->RemoveCargo(deletedID);
}
