#include "Normal_Cargo.h"
int Normal_Cargo::MaxW = 0;
Normal_Cargo::Normal_Cargo(const Time& pre, const int& L, const int& D, const int& C, const int& id) :Cargo(pre, L, D, C,id)
{

}

void Normal_Cargo::IncCost(int c)
{
	setCost(getCost() + c);
}

Normal_Cargo::~Normal_Cargo() {

}


