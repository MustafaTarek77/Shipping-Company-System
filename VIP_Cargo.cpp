#include "VIP_Cargo.h"
int VIP_Cargo::MaxW = 0;
VIP_Cargo::VIP_Cargo(const Time& pre, const int& L, const int& D, const int& C, const int& id) :Cargo(pre, L, D, C,id) {
	setPriority(C, D,pre);
}
void VIP_Cargo::setPriority(const int& c, const int& d, const Time &p) {

	priority = 0.5 * c - 0.25 * d - 0.25 * p.transfHours();
}

float VIP_Cargo::getpriority()
{
	return priority;
}

VIP_Cargo::~VIP_Cargo() {

}
