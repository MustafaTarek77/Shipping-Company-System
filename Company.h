#pragma once
#include <iostream>
#include <string>
#include "Cargo.h"
#include"Truck.h"
#include"Prepartion_Event.h"
#include"Prompote_Event.h"
#include"Cancel_Event.h"
#include"Queue.h"
#include"LinkedList.h"
#include"PriorityQueue.h"
#include"Normal_Truck.h"
#include"Special_Truck.h"
#include"VIP_Truck.h"
#include"Normal_Cargo.h"
#include"Special_Cargo.h"
#include"VIP_Cargo.h"
using namespace std;


class Company
{
private:
	int Normal_Num, Special_Num, VIP_Num; // number of cars
	int Normal_Speed, Special_Speed, VIP_Speed; // cars speed
	int Normal_Capacity, Special_Capacity, VIP_Capacity; // cars capacity
	int Journey_Limit_CheckUp;// next checkUp time 
	int Normal_CheckUP_Time, Special_CheckUP_Time, VIP_CheckUP_Time;// cars check up time 
	int Auto_Promoting_time;
	int Max_Waiting_Time;
	int No_Events;
	LinkedList<Cargo*> Waiting_Normal_Cargos;
	Queue<Cargo*> Waiting_Special_Cargos;
	PriorityQueue<Cargo*> Waiting_VIP_Cargos;
	Queue<Cargo*> Delivered_Cargos;              
	PriorityQueue<Truck*> Empty_Normal_Trucks, Empty_Special_Trucks, Empty_VIP_Trucks;
	Queue<Truck*> InCheckup_Normal_Trucks, InCheckup_Special_Trucks, InCheckup_VIP_Trucks;
	PriorityQueue<Truck*> Moving_Trucks;
	Queue<Event*> Events;
	PriorityQueue<Truck*> Moving_Back_Trucks;
	Truck* Loading_Normal, *Loading_Special, *Loading_VIP;

	/**********************************************************************************/
	static int offhours_start;
	static int offhours_end;

	Time Company_Time; // the real life time ,,,,,,,,,,,, Increment this by a function
	int NumNormCargos, NumSpecCargos, NumVIPCargos;
	int Num_AutoPromote;



	//private functions
	void Load_VIP_Cargos();
	void Load_Normal_Cargos();
	void Load_Special_Cargos();
	


public:
	Company(const string File_Name); //constructor 

	void Load_Info(const string File_name);

	void AddCargo(Cargo* cargo,char type);

	void RemoveCargo(int id);

	void PrompoteCargo(int id,int extracost,Time t);

	void AutoPromotion(int day);

	int CountCargos(char c);

	int CountTrucks(char c);

	void PrintCargos(int type);

	void PrintTrucks(int type);

	bool IsnotWorking();

	void LoadCargo();

	bool ExecuteAction(int day,int hour);


	/***************************************************/
	Queue<Cargo*>* getdeliveredqueue();
	PriorityQueue<Truck*>* getmovingqueue();
	Truck* getloadingtruck(char c);
	void Loading_To_Moving();
	void AddMovingTruck(Truck* truck);
	void ExecuteLoading();
	void Deliver_Cargos();

	/*--------------------------------------------------*/
	bool offHours(int y);//called by passing current hour
	void MaxWaitingRule(int& n, int& s);


	/*....................................................*/
	void moving_T_company();
	void checkUp_T_available();
	void OutPut_file();
};

