#include "Prepartion_Event.h"
#include"Company.h"

Prepartion_Event::Prepartion_Event(Company* ptr,const Time& eventtime, const int& load, const int& distance, const int& cost,char t,int id):Event(ptr,eventtime,id)
{
	type = t;
	switch (type)
	{
	case 'N':
		newcargo = new Normal_Cargo(eventtime, load, distance, cost,id);
		break;
	case 'S':
		newcargo = new Special_Cargo(eventtime, load, distance, cost,id);
		break;
	case 'V':
		newcargo = new VIP_Cargo(eventtime, load, distance, cost,id);
		break;
	}
}


void Prepartion_Event::Execute()
{
	Companyptr->AddCargo(newcargo,type);
}
