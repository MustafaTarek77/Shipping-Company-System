#include "Company.h"
#include <iostream>
#include <fstream>
using namespace std;
int Company::offhours_start = 5;
int Company::offhours_end = 23;


Company::Company(const string File_Name)
{
	Load_Info(File_Name);
	Loading_Normal=NULL;
	Loading_Special=NULL;
	Loading_VIP=NULL;
	NumNormCargos=NumSpecCargos=NumVIPCargos=Num_AutoPromote=0;
}

void Company::Load_Info(const string File_name)
{
	fstream fin(File_name + ".txt", ios::in);
	fin >> Normal_Num;
	fin >> Special_Num;
	fin >> VIP_Num;
	// first line
	fin >> Normal_Speed;
	fin >> Special_Speed;
	fin >> VIP_Speed;
	//second line
	fin >> Normal_Capacity;
	fin >> Special_Capacity;
	fin >> VIP_Capacity;
	//third line 
	fin >> Journey_Limit_CheckUp;
	fin >> Normal_CheckUP_Time;
	fin >> Special_CheckUP_Time;
	fin >> VIP_CheckUP_Time;
	Normal_Truck nt;
	Special_Truck st;
	VIP_Truck vt;
	nt.SetCheckupTime(Normal_CheckUP_Time);
	st.SetCheckupTime(Special_CheckUP_Time);
	vt.SetCheckupTime(VIP_CheckUP_Time);
	// 4 line
	fin >> Auto_Promoting_time;
	fin >> Max_Waiting_Time;
	char Temp_Char, test;
	int day, hr;
	int ID; // shared variable in each case
	fin >> No_Events;
	Event* event = NULL;
	Truck* truck = NULL;
	Time eventtime;

	for (int i = 1; i <= Normal_Num; i++)
	{
		truck = new Normal_Truck();
		truck->SetID(i);
		truck->SetSpeed(Normal_Speed);
		truck->SetCapacity(Normal_Capacity);
		Empty_Normal_Trucks.enqueue(truck,truck->GetPriorityEmpty());
	}
	for (int i = Normal_Num+1; i <= Special_Num+Normal_Num; i++)
	{
		truck = new Special_Truck();
		truck->SetID(i);
		truck->SetSpeed(Special_Speed);
		truck->SetCapacity(Special_Capacity);
		Empty_Special_Trucks.enqueue(truck,truck->GetPriorityEmpty());
	}
	for (int i = Special_Num + Normal_Num+1; i <= Special_Num + Normal_Num+VIP_Num; i++)
	{
		truck = new VIP_Truck();
		truck->SetID(i);
		truck->SetSpeed(VIP_Speed);
		truck->SetCapacity(VIP_Capacity);
		Empty_VIP_Trucks.enqueue(truck,truck->GetPriorityEmpty());
	}

	for (int i = 0; i < No_Events; i++)
	{
		fin >> Temp_Char;
		switch (Temp_Char)
		{
		case ('R'):
			char Cargo_Type;
			int Distance, Time_Loading, Cost;   //some unique variable for this case
			fin >> Cargo_Type;
			fin >> day;
			fin >> test;
			fin >> hr;
			fin >> ID;
			fin >> Distance;
			fin >> Time_Loading;
			fin >> Cost;
			eventtime.settime(day, hr);
			event = new Prepartion_Event(this,eventtime, Time_Loading, Distance, Cost, Cargo_Type,ID);      //Add_New_Cargo();//still needs for variable
			if (Cargo_Type == 'N')
				NumNormCargos++;
			break;
		case ('X'):
			fin >> day;
			fin >> test;
			fin >> hr;
			fin >> ID;
			eventtime.settime(day, hr);
			event = new Cancel_Event(this, eventtime, ID);
			//make new list has all the Cargos
			break;
		case( 'P'):
			int Extra_money;
			fin >> day;
			fin >> test;
			fin >> hr;
			fin >> ID;
			fin >> Extra_money;
			eventtime.settime(day, hr);
			event = new Prompote_Event(this, eventtime, ID, Extra_money);
			break;
		default:
			break;
		}
		Events.enqueue(event);
	}
}

void Company::AddCargo(Cargo* cargo,char type)
{
	switch (type)
	{
	case('N'):
		Waiting_Normal_Cargos.insertend(cargo);
		break;
	case('S'):
		Waiting_Special_Cargos.enqueue(cargo);
		break;
	case('V'):
		VIP_Cargo* vip = new VIP_Cargo(cargo->getPreparation(), cargo->getLoadTime(), cargo->getDistance(), cargo->getCost(), cargo->GetID());
		Waiting_VIP_Cargos.enqueue(cargo, vip->getpriority());
		break;
	}
}

void Company::RemoveCargo(int id)
{
	Time t;
	Cargo* temp = new Normal_Cargo(t,0,0,0,id);
	temp = Waiting_Normal_Cargos.search(temp);
	if (temp)
	{
		Waiting_Normal_Cargos.Remove(temp);
		NumNormCargos--;
	}
}

void Company::PrompoteCargo(int id, int extracost,Time t)
{
	Time n;
	Cargo* temp = new Normal_Cargo(n, 0, 0, 0,id);
    temp = Waiting_Normal_Cargos.search(temp);
	if (temp)
	{
		Waiting_Normal_Cargos.Remove(temp);
		VIP_Cargo* vip = new VIP_Cargo(t, temp->getLoadTime(), temp->getDistance(), temp->getCost()+extracost, temp->GetID());
		Waiting_VIP_Cargos.enqueue(temp, vip->getpriority());
		NumNormCargos--;
		NumVIPCargos++;
	}
}

void Company::AutoPromotion(int day)
{
	Cargo* temp = Waiting_Normal_Cargos.Peek();
	if (temp)
	{
		if (temp->getPreparation().getday() + Auto_Promoting_time == day)
		{
			Waiting_Normal_Cargos.Remove(temp);
			VIP_Cargo* vip = new VIP_Cargo(temp->getPreparation(), temp->getLoadTime(), temp->getDistance(), temp->getCost(), temp->GetID());
			Waiting_VIP_Cargos.enqueue(temp, vip->getpriority());
			NumNormCargos--;
			NumVIPCargos++;
			Num_AutoPromote++;
		}
	}
}

int Company::CountCargos(char c)
{
	int count = 0;
	switch (c)
	{
	case('W'):
		count +=Waiting_Normal_Cargos.getcount() + Waiting_Special_Cargos.getcount() + Waiting_VIP_Cargos.getcount();
		break;
	case('M'):
	{
		Truck* item;
		Queue<Truck*>* tmp = new Queue<Truck*>;
		while (Moving_Trucks.dequeue(item))
		{
			count+=item->GetCargosCount();
			tmp->enqueue(item);
		}
		while (tmp->dequeue(item))
			AddMovingTruck(item);
		break;
	}
		break;
	case('D'):
		count += Delivered_Cargos.getcount();
		break;
	}
	return count;
}

int Company::CountTrucks(char c)
{
	int count = 0;
	switch (c)
	{
	case('E'):
		count += Empty_Normal_Trucks.getcount() + Empty_Special_Trucks.getcount() + Empty_VIP_Trucks.getcount();
		break;
	case('L'):
		if (Loading_Normal)
			count++;
		if (Loading_Special)
			count++;
		if (Loading_VIP)
			count++;
		break;
	case('C'):
		count += InCheckup_Normal_Trucks.getcount() + InCheckup_Special_Trucks.getcount() + InCheckup_VIP_Trucks.getcount();
		break;
	}
	return count;
}

void Company::PrintCargos(int type)
{
	switch (type)
	{
	case(11):    //Normal waiting Cargo
		Waiting_Normal_Cargos.display();
		break;
	case(12):    //Special waiting Cargo
		Waiting_Special_Cargos.print();
		break;
	case(13):    //VIP waiting Cargo
		Waiting_VIP_Cargos.print();
		break;
	}
}

void Company::PrintTrucks(int type)
{
	switch (type)
	{
	case(11):    //Normal empty Trucks
		Empty_Normal_Trucks.print();
		break;
	case(12):    //Special empty Trucks
		Empty_Special_Trucks.print();
		break;
	case(13):    //VIP empty Trucks
		Empty_VIP_Trucks.print();
		break;
	case(21):    //Normal InCheckUp Trucks
		InCheckup_Normal_Trucks.print();
		break;
	case(22):    //Special InCheckUp Trucks
		InCheckup_Special_Trucks.print();
		break;
	case(23):    //VIP InCheckUp Trucks
		InCheckup_VIP_Trucks.print();
		break;
	}
}

bool Company::IsnotWorking()
{
	if (Events.isEmpty()&&(CountCargos('W')==0)&&(CountCargos('M')==0)&& (CountCargos('L') == 0)&& (CountTrucks('C') == 0)&& (CountTrucks('L') == 0)&& (CountTrucks('E') == Normal_Num+Special_Num+ VIP_Num))
		return true;
	else
		return false;
}

bool Company::ExecuteAction(int day, int hour)
{
	Company_Time.settime(day, hour);
	Event* tmp;
	if (!offHours(Company_Time.gethour()))
	{
		while (Events.peek(tmp))

			if (tmp->getTime().getday() == day && tmp->getTime().gethour() == hour)
				Events.dequeue(tmp);

			else break;

		return false;
	}
	AutoPromotion(day);
	if (Events.peek(tmp))
	{
		Time EveT = tmp->getTime();
		if (hour == EveT.gethour() && day == EveT.getday())
		{
			Events.dequeue(tmp);
			tmp->Execute();
			return true;
		}
	}

	return false;
}

/***********************************************************/

Queue<Cargo*>* Company::getdeliveredqueue()
{
	return (&Delivered_Cargos);
}

PriorityQueue<Truck*>* Company::getmovingqueue()
{
	return &Moving_Trucks;
}

Truck* Company::getloadingtruck(char c)
{
	switch (c)
	{
	case('N'):
		return Loading_Normal;
		break;
	case('S'):
		return Loading_Special;
		break;
	case('V'):
		return Loading_VIP;
		break;

	}
}

void Company::LoadCargo()
{
	int N = 0;
	int S = 0;
	MaxWaitingRule(N, S);
	if (Waiting_VIP_Cargos.getcount() >= VIP_Capacity)
	{
		//check the off hours
		Load_VIP_Cargos();
	}
	if (Waiting_Normal_Cargos.getcount() >= Normal_Capacity && N == 0)
	{
		Load_Normal_Cargos();
	}
	if (Waiting_Special_Cargos.getcount() >= Special_Capacity && S == 0)
	{
		Load_Special_Cargos();
	}
}

void Company::Load_VIP_Cargos()// assume that available cargos>= TC
{
	if (!Empty_VIP_Trucks.isEmpty() && Waiting_VIP_Cargos.getcount() >= VIP_Capacity)
	{
		Truck* x;
		Cargo* tmp;
		Empty_VIP_Trucks.dequeue(x);
		Loading_VIP = x;
		for (int i = 0; i < VIP_Capacity; i++)//do we need to add them to a List in the truck ?
		{
			Waiting_VIP_Cargos.dequeue(tmp);
			tmp->Set_Truck(x);
			x->Add_Cargo_Loading(tmp);
			tmp->SetWaitingTime(Company_Time-tmp->getPreparation());
		}
		return;
	}
	else if (!Empty_Normal_Trucks.isEmpty() && Waiting_VIP_Cargos.getcount() >= Normal_Capacity)
	{
		Truck* x;
		Cargo* tmp;
		Empty_Normal_Trucks.dequeue(x);
		Loading_Normal = x;
		for (int i = 0; i < Normal_Capacity; i++)//we are assuming that the Capitcity of VIP is always the smallest
		{
			Waiting_VIP_Cargos.dequeue(tmp);
			tmp->Set_Truck(x);
			x->Add_Cargo_Loading(tmp);
			tmp->SetWaitingTime(Company_Time - tmp->getPreparation());
		}
		return;
	}
	else if (!Empty_Special_Trucks.isEmpty() && Waiting_VIP_Cargos.getcount() >= Special_Capacity)
	{
		Truck* x;
		Cargo* tmp;
		Empty_Special_Trucks.dequeue(x);
		Loading_Special = x;
		for (int i = 0; i < VIP_Capacity; i++)//we are assuming that the Capitcity of VIP is always the smallest
		{
			Waiting_VIP_Cargos.dequeue(tmp);
			tmp->Set_Truck(x);
			x->Add_Cargo_Loading(tmp);
			tmp->SetWaitingTime(Company_Time - tmp->getPreparation());
		}
		return;
	}
	return;
}

void Company::Load_Normal_Cargos()//assuming we finished the VIP and Special Ones
{
	Truck* x;
	Cargo* tmp;
	if (!Empty_Normal_Trucks.isEmpty() && Waiting_Normal_Cargos.getcount() >= Normal_Capacity&&!Loading_Normal) 
	{

		Empty_Normal_Trucks.dequeue(x);
		Loading_Normal = x;
		for (int i = 0; i < Normal_Capacity; i++)
		{
			tmp = Waiting_Normal_Cargos.RemoveFirst();
			tmp->Set_Truck(x);
			x->Add_Cargo_Loading(tmp);
			tmp->SetWaitingTime(Company_Time - tmp->getPreparation());
		}
		return;

	}
	else if (!Empty_VIP_Trucks.isEmpty() && Waiting_Normal_Cargos.getcount() >= VIP_Capacity&&!Loading_VIP)
	{

		Empty_VIP_Trucks.dequeue(x);
		Loading_VIP = x;
		for (int i = 0; i < VIP_Capacity; i++)//check
		{
			tmp = Waiting_Normal_Cargos.RemoveFirst();
			tmp->Set_Truck(x);
			x->Add_Cargo_Loading(tmp);
			tmp->SetWaitingTime(Company_Time - tmp->getPreparation());
		}
		return;
	}
	return;
}

void Company::Load_Special_Cargos()
{
	Truck* x;
	Cargo* tmp;
	if (!Empty_Special_Trucks.isEmpty() && Waiting_Special_Cargos.getcount() >= Special_Capacity&&!Loading_Special)
	{
		Empty_Special_Trucks.dequeue(x);
		Loading_Special = x;
		for (int i = 0; i < Special_Capacity; i++) {

			Waiting_Special_Cargos.dequeue(tmp);
			tmp->Set_Truck(x);
			x->Add_Cargo_Loading(tmp);
			tmp->SetWaitingTime(Company_Time - tmp->getPreparation());
		}
		return;
	}
	return;
}

void Company::Loading_To_Moving()
{
	Truck* t;
	if (Loading_Normal)
		if (Loading_Normal->Get_Max_Loaded_Cargo_Time() <= Company_Time.transfHours())
		{
			t = Loading_Normal;
			t->SetMoveTime(Company_Time);
			t->Reorder_Cargo_Moving();
			AddMovingTruck(t);
			t->IN_Journey_num();
			t->IN_Loaded_Cargos(t->GetCargosCount());
			Time DT(0, t->GetDeliveryInterval());
			t->IN_Active_Time(DT);
			Loading_Normal = NULL;
		}
	if (Loading_Special)
		if (Loading_Special->Get_Max_Loaded_Cargo_Time() <= Company_Time.transfHours())
		{
			t = Loading_Special;
			t->SetMoveTime(Company_Time);
			t->Reorder_Cargo_Moving();
			AddMovingTruck(t);
			t->IN_Journey_num();
			t->IN_Loaded_Cargos(t->GetCargosCount());
			Time DT(0, t->GetDeliveryInterval());
			t->IN_Active_Time(DT);
			Loading_Special = NULL;
		}
	if (Loading_VIP)
		if (Loading_VIP->Get_Max_Loaded_Cargo_Time() <= Company_Time.transfHours())
		{
			t = Loading_VIP;
			t->SetMoveTime(Company_Time);
			t->Reorder_Cargo_Moving();
			AddMovingTruck(t);
			t->IN_Journey_num();
			t->IN_Loaded_Cargos(t->GetCargosCount());
			Time DT(0, t->GetDeliveryInterval());
			t->IN_Active_Time(DT);
			Loading_VIP = NULL;
		}
}

void Company::AddMovingTruck(Truck* truck)
{
	Moving_Trucks.enqueue(truck, truck->GetPriorityMoving());
}

void Company::ExecuteLoading()
{
	if (offHours(Company_Time.gethour()))
	{
		Loading_To_Moving();
		LoadCargo();
	}
	Deliver_Cargos();
	moving_T_company();
	checkUp_T_available();
}

void Company::Deliver_Cargos()
{
	Truck* t;
	Cargo* c;
	PriorityQueue<Cargo*> tmp;
	bool test = true;
	while (Moving_Trucks.peek(t)&&test)
	{
		if (!t->get_delivery_failed())
		{
			while (t->CheckDelivery(Company_Time, c))
				tmp.enqueue(c, -c->GetCDT());
			if (t->GetCargosCount() == 0)
			{
				Moving_Trucks.dequeue(t);
				Moving_Back_Trucks.enqueue(t, -t->GetMaxDistance());
				t->Clear_Info();
			}
			else
				test = false;
		}
		else
			test=false;
	}
	while (tmp.dequeue(c))
		Delivered_Cargos.enqueue(c);
}


/*---------------------------------------------------------------------------------*/
bool Company::offHours(int y)
{
	if (y >= offhours_start && y < offhours_end)
		return true;

	return false;
}


void Company::MaxWaitingRule(int& n, int& s)
{
	Cargo* temp1 = Waiting_Normal_Cargos.Peek();
	Cargo* temp2;
	if (temp1)
	{
		if (temp1->getPreparation().transfHours() + Max_Waiting_Time <= Company_Time.transfHours())
		{
			if (!Empty_Normal_Trucks.isEmpty()) {

				Truck* x;
				Empty_Normal_Trucks.dequeue(x);
				temp1 = Waiting_Normal_Cargos.RemoveFirst();
				temp1->Set_Truck(x);
				x->Add_Cargo_Loading(temp1);
				Loading_Normal = x;
				n++;


			}
			else if (!Empty_VIP_Trucks.isEmpty()) {

				Truck* x;
				Empty_VIP_Trucks.dequeue(x);
				temp1 = Waiting_Normal_Cargos.RemoveFirst();
				temp1->Set_Truck(x);
				x->Add_Cargo_Loading(temp1);
				Loading_VIP = x;



				n++;

			}

		}
	}
	if (Waiting_Special_Cargos.peek(temp2))
	{
		if (temp2->getPreparation().transfHours() + Max_Waiting_Time <= Company_Time.transfHours())
		{
			if (!Empty_Special_Trucks.isEmpty()) {

				Truck* x;
				Empty_Special_Trucks.dequeue(x);
				Waiting_Special_Cargos.dequeue(temp2);
				temp2->Set_Truck(x);
				x->Add_Cargo_Loading(temp2);
				Loading_Special = x;
				s++;
			}
			//load function
		}
	}
}

/*..............................................................................................................*/

void Company::moving_T_company()
{   //////// you may need to change all ''moving'' to "loading " only 
	//////// may be into queue InMaintance
	Truck* temp;
	while (!Moving_Back_Trucks.isEmpty())
	{
		Moving_Back_Trucks.peek(temp); // we look at the peek 
		if (temp->GetDeliveryInterval()+temp->GetMoveTime().transfHours()<= Company_Time.transfHours()) { // if its the time to be back we will choose whether
			Moving_Back_Trucks.dequeue(temp);

			///newwwwwwwwwww  
			if (temp->get_delivery_failed())
			{
				temp->set_start_check(Company_Time);
				if (dynamic_cast<Normal_Truck*>(temp)) {
					temp->set_end_check(Company_Time + Normal_Truck::get_checkUpTime());
					InCheckup_Normal_Trucks.enqueue(temp);
				}
				else if (dynamic_cast<Special_Truck*>(temp)) {
					temp->set_end_check(Company_Time + Special_Truck::get_checkUpTime());
					InCheckup_Special_Trucks.enqueue(temp);
				}
				else
				{
					temp->set_end_check(Company_Time + VIP_Truck::get_checkUpTime());
					InCheckup_VIP_Trucks.enqueue(temp);
				}
				Cargo* x = temp->Check_Type();
				Queue<Cargo*>tempQQ;
				temp->get_Truck_load_Q(tempQQ);
				if (dynamic_cast<Normal_Cargo*>(x)) {
					while (!tempQQ.isEmpty())
					{
						tempQQ.dequeue(x);
						Waiting_Normal_Cargos.insertfirst(x);
					}

				}
				else if (dynamic_cast<Special_Cargo*>(x)) {
					while (!tempQQ.isEmpty())
					{
						tempQQ.dequeue(x);
						Waiting_Special_Cargos.enqueue(x);
					}
				}
				else
				{
					while (!tempQQ.isEmpty())
					{
						tempQQ.dequeue(x);
						VIP_Cargo y(x->getPreparation(), x->getLoadTime(), x->getDistance(), x->getCost(), x->GetID());
						Waiting_VIP_Cargos.enqueue(x,y.getpriority());
					}
				}
			}
			else if (temp->Need_to_checkup(Journey_Limit_CheckUp)) { // truck to checkup queue
				temp->set_start_check(Company_Time);
				if (dynamic_cast<Normal_Truck*>(temp)) {
					temp->set_end_check(Company_Time + Normal_Truck::get_checkUpTime());
					InCheckup_Normal_Trucks.enqueue(temp);
				}
				else if (dynamic_cast<Special_Truck*>(temp)) {
					temp->set_end_check(Company_Time + Special_Truck::get_checkUpTime());
					InCheckup_Special_Trucks.enqueue(temp);
				}
				else
				{
					temp->set_end_check(Company_Time + VIP_Truck::get_checkUpTime());
					InCheckup_VIP_Trucks.enqueue(temp);
				}
			}
			else { // truck to empty queue

				if (dynamic_cast<Normal_Truck*>(temp)) {
					Empty_Normal_Trucks.enqueue(temp, temp->GetPriorityEmpty());
				}
				else if (dynamic_cast<Special_Truck*>(temp)) {
					Empty_Special_Trucks.enqueue(temp, temp->GetPriorityEmpty());
				}
				else
				{
					Empty_VIP_Trucks.enqueue(temp, temp->GetPriorityEmpty());
				}
			}
		}
		else
			break;
	}
}

void Company::checkUp_T_available()
{
	Truck* temp;

	while (!InCheckup_Normal_Trucks.isEmpty())
	{
		InCheckup_Normal_Trucks.peek(temp); // we look at the peek 
		if (temp->get_end_check() <= Company_Time) {
			InCheckup_Normal_Trucks.dequeue(temp);
			Empty_Normal_Trucks.enqueue(temp, temp->GetPriorityEmpty());
		}
		else
			break;

	}

	while (!InCheckup_Special_Trucks.isEmpty())
	{
		InCheckup_Special_Trucks.peek(temp); // we look at the peek 
		if (temp->get_end_check() <= Company_Time) {
			InCheckup_Special_Trucks.dequeue(temp);
			Empty_Special_Trucks.enqueue(temp, temp->GetPriorityEmpty());
		}
		else
			break;

	}

	while (!InCheckup_VIP_Trucks.isEmpty())
	{
		InCheckup_VIP_Trucks.peek(temp); // we look at the peek 
		if (temp->get_end_check() <= Company_Time) { // if its the time to be back we will choose whether
			InCheckup_VIP_Trucks.dequeue(temp);
			Empty_VIP_Trucks.enqueue(temp, temp->GetPriorityEmpty());
		}
		else
			break;

	}

}

void Company::OutPut_file()
{
	fstream fout("Output_File", ios::out);
	Time Total_Waiting(0, 0);//1
	Time Avg_Active(0, 0);//2
	int totalTrucks = Normal_Num + Special_Num + VIP_Num;
	int totalUtillization = 0;
	// here we will calculate 1 && 2
	Queue<Cargo*> tmp;
	Truck* t;
	Cargo* temp;
	fout << "CDT          ID          PT          WT          TID" << endl;
	
	while (!Delivered_Cargos.isEmpty())
	{
		Delivered_Cargos.dequeue(temp);
		Total_Waiting = Total_Waiting+ temp->GetWaitingTime();
		tmp.enqueue(temp);
		if (dynamic_cast<Normal_Cargo*>(temp))
			NumNormCargos++;
		else if (dynamic_cast<Special_Cargo*>(temp))
			NumSpecCargos++;
		else
			NumVIPCargos++;
	}
	int totalCargos = NumNormCargos + NumSpecCargos + NumVIPCargos;

	while (Empty_Normal_Trucks.dequeue(t))
	{
		totalUtillization += t->GetUtilization(Company_Time);
		Avg_Active = Avg_Active + t->GetActiveTime();
	}
	while (Empty_Special_Trucks.dequeue(t))
	{
		totalUtillization += t->GetUtilization(Company_Time);
		Avg_Active = Avg_Active + t->GetActiveTime();
	}
	while (Empty_VIP_Trucks.dequeue(t))
	{
		totalUtillization += t->GetUtilization(Company_Time);
		Avg_Active = Avg_Active + t->GetActiveTime();
	}

	while (!tmp.isEmpty())
	{
		tmp.dequeue(temp);
		Time CDT(0, temp->GetCDT());
		fout<<CDT.getday()<<":"<<CDT.gethour()<< "          " << temp->GetID()<< "          " << temp->getPreparation().getday() << ":" << temp->getPreparation().gethour() << "          " << temp->GetWaitingTime().getday() << ":" << temp->GetWaitingTime().gethour() << "          " << temp->GetTruckID() << endl;
	}
	fout << "-----------------------------------------------------------" << endl;
	fout << "-----------------------------------------------------------" << endl;
	fout << "Cargos:  " << totalCargos << "[N:" << NumNormCargos << ",S:" << NumSpecCargos << ",V:" << NumVIPCargos << "]" << endl;
	fout << "Cargo Avg Wait = " << Total_Waiting.getday() << ":" << Total_Waiting.gethour() << endl;
	fout << "Auto - promoted Caros :" << float(((Num_AutoPromote * 1.0) /(Num_AutoPromote + NumNormCargos))* 100.0) << "%" << endl;
	fout << "Trucks:  " << totalTrucks << "[N:" << Normal_Num << ",S:" << Special_Num << ",V:" << VIP_Num << "]" << endl;
	fout << "Avg Active time = " << float(((Avg_Active.transfHours() * 1.0) / totalTrucks) * 100.0) << "%" << endl;
	fout << "Avg utilization = " << float(((totalUtillization * 1.0) / totalTrucks) * 100.0) << "%" << endl;
	fout.close();
}
