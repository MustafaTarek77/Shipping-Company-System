#pragma once
#include"Cargo.h"
class Special_Cargo :public Cargo
{
private:

	static int MaxW;           //max w8 time for a Cargo "Loaded from input file"
public:

	Special_Cargo(const Time& pre, const int& L, const int& D, const int& C, const int& id);


	~Special_Cargo();
};

