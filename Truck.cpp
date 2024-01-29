#include "Truck.h"

Truck::Truck()
{
	Capacity = 0;
	Speed = 0;
	Total_Delivered_Cargos=0;
	Total_Delivery_journeys=0;
	Max_Loaded_Cargo_Time = 0;
	Max_Distance = 0;
	Total_Loaded_Time = 0;
}

void Truck::SetActiveTime(Time t)
{
	Active_Time = t;
}

void Truck::SetID(int id)
{
	Truck_ID = id;
}

int Truck::GetID()const
{
	return Truck_ID;
}

Time Truck::GetActiveTime()
{
	return Active_Time;
}

void Truck::SetCapacity(int TC)
{
	Capacity = TC;
}

void Truck::SetSpeed(int s)
{
	Speed = s;
}

float Truck::GetSpeed()
{
	return Speed;
}

int Truck::GetCapacity()
{
	return Capacity;
}

int Truck::GetUtilization(Time Simulation_Time)
{
	/*Truck utilization = tDC / (TC * N) * (tAT / TSim), N ≠ 0 (if N = 0, utilization = 0 %)
	 tDC : total cargos delivered by this truck
	 TC : truck capacity
	 N : total delivery journeys of this truck
	 tAT : total truck active time
	 TSim : total Simulation time*/
	if (Total_Delivery_journeys == 0)
		return 0;
	else
		return double( double(((Total_Delivered_Cargos*1.0) / (Capacity*1.0 * Total_Delivery_journeys))) * double(((1.0*Active_Time.transfHours()) / Simulation_Time.transfHours())));
}



/*********************************************************************************/

float Truck::GetPriorityEmpty()
{
	return 0.5*Speed+0.5*Capacity;
}

float Truck::GetPriorityMoving()
{
	Cargo* c;
	if (Loaded_Cargos.peek(c))
		return (-c->GetCDT());
	else
		return 0;
}

void Truck::SetMoveTime(Time t)
{
	Move_Time.settime(t.getday(), t.gethour());
}

Time Truck::GetMoveTime()
{
	return Move_Time;
}

void Truck::Reorder_Cargo_Moving()
{
	Cargo* c;
	Queue<Cargo*> tmp;
	while (Loaded_Cargos.dequeue(c))
		tmp.enqueue(c);
	while (tmp.dequeue(c))
		Loaded_Cargos.enqueue(c, -c->GetCDT());
}

void Truck::Add_Cargo_Loading(Cargo* c)
{
	Loaded_Cargos.enqueue(c,0);
	if (c->getPreparation().transfHours() + c->getLoadTime() > Max_Loaded_Cargo_Time)
		Max_Loaded_Cargo_Time = c->getPreparation().transfHours() + c->getLoadTime();
	if (c->getDistance() > Max_Distance)
		Max_Distance = c->getDistance();
	Total_Loaded_Time += c->getLoadTime();
}

void Truck::Clear_Info()
{
	Move_Time.settime(0, 0);
	Max_Loaded_Cargo_Time = 0;
	Max_Distance = 0;
	Total_Loaded_Time = 0;
}

Cargo* Truck::Check_Type()
{
	Cargo* c;
	if (Loaded_Cargos.peek(c))
		return c;
	else
		return NULL;
}

void Truck::Print_Loaded_Cargos()
{
	Loaded_Cargos.print();
}

int Truck::Get_Max_Loaded_Cargo_Time()
{
	return Max_Loaded_Cargo_Time;
}

bool Truck::CheckDelivery(Time t,Cargo*& c)
{
	if (Loaded_Cargos.peek(c))
	{
		if (c->GetCDT() <= t.transfHours())
		{
			Loaded_Cargos.dequeue(c);
			return true;
		}
	}
	return false;
}

int Truck::GetMaxDistance()
{
	return Max_Distance;
}

int Truck::GetCargosCount()
{
	return Loaded_Cargos.getcount();
}

int Truck::GetDeliveryInterval()
{
	return Total_Loaded_Time+(2*(Max_Distance/Speed));
}



/*............................................................................*/

void Truck::IN_Active_Time(Time a)
{
	Active_Time = Active_Time + a; // all operator overloading in time ??
}

void Truck::IN_Journey_num()
{
	Total_Delivery_journeys++;
}

void Truck::IN_Loaded_Cargos(int n)
{
	Total_Delivered_Cargos += n;
}

void Truck::set_delivery_failed(bool a)
{
	delivery_failed = a;
}

bool Truck::get_delivery_failed()
{
	return delivery_failed;
}


void Truck::set_end_check(Time n)
{
	end_check_time = n;
}

Time Truck::get_end_check()
{
	return end_check_time;
}


void Truck::set_start_check(Time n)
{
	start_check_time = n;
}

Time Truck::get_start_check()
{
	return start_check_time;
}

bool Truck::Need_to_checkup(int n)
{
	if (Total_Delivery_journeys % n == 0) 
	{
		return true;
	}
	return false;
}


void Truck::get_Truck_load_Q(Queue<Cargo*>& Q)
{// only use when truck back to the company 
	Cargo* temp;
	while (!Loaded_Cargos.isEmpty())
	{
		Loaded_Cargos.dequeue(temp);
		Q.enqueue(temp);
	}

}