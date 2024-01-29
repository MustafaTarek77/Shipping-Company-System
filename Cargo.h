#pragma once
#include"time.h"            //This can be specified as normal cargos 
class Truck;

class Cargo
{
private:
	Time Preparation;   //the exact time (day/hour) where the cargo is ready
	int LoadTime;           //time to load/unload the cargo to/from the truck
	int Distance;       //Distance in "KM" from the company to the delievry location  
	int Cost;           // cost of delievring the cargo
	int ID;
	bool isloaded;
	Time Waiting_Time;
	
	/*****************************************************/
	Truck* truck;

public:
	Cargo(const Time& pre, const int& L, const int& D, const int& C,const int& id);


	Cargo(const Cargo& c);          //copy constructor


	void SetId(int id);

	int GetID()const; 

	void setPreparation(const Time& t);

	void setLoadTime(const int& L);

	void setDistance(const int& D);                  //simple setters for the Data members

	void setCost(const int& C);

	Time getPreparation()const;

	int getLoadTime()const;                             //Simple getters for data members

	int getDistance()const;

	int getCost()const;

	bool IsLoaded()const;

	void SetIsLoaded(bool l);
	//virtual functions

	bool operator==(Cargo* c);

	bool operator==(int n);

	//virtual Distructor
	virtual ~Cargo();

	friend ostream& operator<<(ostream& Out, const Cargo* c);

	/*******************************************************************************/

	int GetCDT();
	void Set_Truck(Truck* t);
	void SetWaitingTime(Time t);
	Time GetWaitingTime();
	int GetTruckID();


};

