#pragma once
#include"Time.h"
#include<iostream>
using namespace std;
#include"PriorityQueue.h"
#include"Cargo.h"
#include"Queue.h"

class Truck
{
private:
	bool delivery_failed;// initialize it with noo && we need way to contact all the cargo with the truck loading it
	Time end_check_time;
	Time start_check_time;
	Time DI;
	static int num_J_to_check;

protected:
	int Truck_ID;
	int Capacity;
	int Speed;
	int Total_Delivered_Cargos;
	int Total_Delivery_journeys;
	Time Active_Time;

	/******************************************/
	PriorityQueue<Cargo*> Loaded_Cargos;
	Time Move_Time;
	int Max_Loaded_Cargo_Time;
	int Total_Loaded_Time;
	int Max_Distance;

public:
	Truck();
	void SetActiveTime(Time t);
	Time GetActiveTime();
	void SetID(int id);
	int GetID()const;
	int GetUtilization(Time Simulation_Time);
	virtual void SetCheckupTime(int Time) = 0;
	friend ostream& operator<<(ostream& Out, const Truck* t);
	void SetCapacity(int TC);
	int GetCapacity();
	void SetSpeed(int s);
	float GetSpeed();

	/*******************************************************/
	float GetPriorityEmpty();
	float GetPriorityMoving();
	void SetMoveTime(Time t);
	Time GetMoveTime();
	void Reorder_Cargo_Moving();
	void Add_Cargo_Loading(Cargo* c);
	void Clear_Info();
	Cargo* Check_Type();
	void Print_Loaded_Cargos();
	int Get_Max_Loaded_Cargo_Time();
	bool CheckDelivery(Time t,Cargo*& c);
	int GetMaxDistance();
	int GetCargosCount();
	int GetDeliveryInterval();

	/*.........................................................*/
	void IN_Active_Time(Time a);
	void IN_Journey_num();
	void IN_Loaded_Cargos(int n);
	void  get_Truck_load_Q(Queue<Cargo*>& Q);
	void set_delivery_failed(bool a);
	bool get_delivery_failed();
	void set_start_check(Time n);
	Time get_start_check();
	void set_end_check(Time n);
	Time get_end_check();
	bool Need_to_checkup(int n);
};