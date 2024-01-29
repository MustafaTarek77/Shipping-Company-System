#include<iostream>
#include"Company.h"
#include"UI.h"
using namespace std;

int main()
{
	Company* company = new Company("z");
	UI ui;
	ui.UserInterFace(company);
}