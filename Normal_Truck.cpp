#include "Normal_Truck.h"
Time Normal_Truck::Checkup_Time;
Time Normal_Truck::Max_Wait;

Normal_Truck::Normal_Truck()
{
}

void Normal_Truck::SetCheckupTime(int Time)
{
	Checkup_Time.sethour(Time);
}

Time Normal_Truck::get_checkUpTime()
{
	return Checkup_Time;
}


