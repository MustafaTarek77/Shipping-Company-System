#pragma once
#include"Truck.h"

class Normal_Truck:public Truck
{
private:
	static Time Max_Wait;
	static Time Checkup_Time;
public:
	Normal_Truck();
	virtual void SetCheckupTime(int Time) ;
	static Time get_checkUpTime();
};

