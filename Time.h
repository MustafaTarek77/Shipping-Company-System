#pragma once
#include<iostream>
using namespace std;
class Time
{
private:
	int day;
	int hour;
public:
	Time(int d, int hr);
	Time();
	int gethour();
	int getday();
	void settime(int d, int hr);
	void sethour(int hr);
	void setday(int d);
	void print();
	int transfHours()const;

	/*..............................................*/
	Time operator+(const Time& T)const;
	Time operator-(const Time& T)const;
	void operator=(const Time& T);
	bool operator>(const Time& T)const;
	bool operator>=(const Time& T)const;
	bool operator<(const Time& T)const;
	bool operator<=(const Time& T)const;
	bool operator==(const Time& T)const;
	Time& operator++();

};

