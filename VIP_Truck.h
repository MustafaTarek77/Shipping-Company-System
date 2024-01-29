#pragma once
#include"Truck.h"

class VIP_Truck :public Truck
{
private:
	static Time Max_Wait;
	static Time Checkup_Time;
public:
	VIP_Truck();
	virtual void SetCheckupTime(int Time);
	static Time get_checkUpTime();
};

