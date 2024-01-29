#include "Time.h"

Time::Time(int d, int hr)
{
    day = d;
    hour = hr;
}

Time::Time()
{
    day = 0;
    hour = 0;
}

int Time::gethour()
{
    return hour;
}

int Time::getday()
{
    return day;
}

void Time::settime(int d, int hr)
{
    day = d;
    hour = hr;
}

void Time::sethour(int hr)
{
    if (hr < 24)
        hour = hr;
    else
    {
        day = hr / 24;
        hour = day % hr;
    }
}

void Time::setday(int d)
{
    day = d;
}

void Time::print()
{
     cout << day << ":" << hour << endl;
}

int Time::transfHours()const
{
    return day * 24 + hour;
}



/*...............................................................................*/
bool Time::operator>(const Time& T) const
{
    return (day * 24 + hour) > (T.day * 24 + T.hour);
}

bool Time::operator>=(const Time& T) const
{
    return (day * 24 + hour) >= (T.day * 24 + T.hour);
}

bool Time::operator<(const Time& T) const
{
    return (day * 24 + hour) < (T.day * 24 + T.hour);
}

bool Time::operator<=(const Time& T)const
{
    return (day * 24 + hour) <= (T.day * 24 + T.hour);
}

bool Time::operator==(const Time& T) const
{
    return T.day == day && hour == T.hour;
}

Time Time::operator+(const Time& T) const
{
    Time temp;
    temp.sethour(T.hour + this->hour);
    temp.setday(T.day + this->day);
    return temp;
}

Time Time::operator-(const Time& T) const
{
    Time temp;
    temp.sethour(T.hour - this->hour);
    temp.setday(T.day - this->day);
    return temp;
}

void Time::operator=(const Time& T)
{
    day = T.day;
    hour = T.hour;
}

Time& Time::operator++()
{
    hour++;
    if (hour > 23) {
        day++;
        hour = 0;
    }
    return *this;
}
