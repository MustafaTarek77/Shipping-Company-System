#include "Special_Truck.h"
Time Special_Truck::Checkup_Time;
Time Special_Truck::Max_Wait;

Special_Truck::Special_Truck() 
{
}

void Special_Truck::SetCheckupTime(int Time)
{
	Checkup_Time.sethour(Time);
}

Time Special_Truck::get_checkUpTime()
{
	return Checkup_Time;
}
