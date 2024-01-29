#pragma once
#include"Cargo.h"
class Normal_Cargo :public Cargo
{
private:

	//we can add priority concept to differ 
	static int MaxW;           //max w8 time for a Cargo "Loaded from input file"

public:
	Normal_Cargo(const Time& pre, const int& L, const int& D, const int& C,const int& id);

	void IncCost(int c);

	virtual ~Normal_Cargo();

	//normal can be special with some functions


	friend ostream& operator<<(ostream& Out, const Normal_Cargo& c);
};

