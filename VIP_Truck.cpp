#include "VIP_Truck.h"
Time VIP_Truck::Checkup_Time;
Time VIP_Truck::Max_Wait;

VIP_Truck::VIP_Truck()
{
}

void VIP_Truck::SetCheckupTime(int Time)
{
	Checkup_Time.sethour(Time);
}

Time VIP_Truck::get_checkUpTime()
{
	return Checkup_Time;
}
