#pragma once
#include"Cargo.h"
#include"Time.h"
class VIP_Cargo :public Cargo
{
private:

	float priority;
	static int MaxW;           //max w8 time for a Cargo "Loaded from input file"
public:
	VIP_Cargo(const Time& pre, const int& L, const int& D, const int& C, const int& id);

	virtual ~VIP_Cargo();

	void setPriority(const int& cost, const int& Distance, const Time& p);

	float getpriority();
};

