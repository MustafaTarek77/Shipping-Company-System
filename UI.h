#pragma once
#include <iostream>
#include <string>
#include"Company.h"
#include<Windows.h>
using namespace std;

class UI
{
private:
	Company* company;
	int day, hour;
	char mode;
public:
	UI();
	void UserInterFace(Company* company);
	void printdeliveredcargos(Queue<Cargo*>* q);
	void printloadingtrucks(Truck* truck);
	void printmovingcargos(PriorityQueue<Truck*>* q);
};