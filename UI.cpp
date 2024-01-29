#include"UI.h"

UI::UI()
{
	day = hour = 0;
}

void UI::UserInterFace(Company* company)
{
	cout << "Choose the mode:Enter [I->interactive mode OR B->step by step mode OR S->silent mode]" << endl;
	cin >> mode;
	cin.get();
	bool test = !company->IsnotWorking();
	switch (mode)
	{
	case('I'):
		while (test)
		{
			test = !company->IsnotWorking();
			cout << "Current Time(Day:Hour): " << day << ":" << hour << endl;
			cout << company->CountCargos('W') << " Waiting Cargos : [";
			company->PrintCargos(11);
			cout << "] (";
			company->PrintCargos(12);
			cout << ") {";
			company->PrintCargos(13);
			cout << "}" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountTrucks('L') << " Loading Trucks : ";
			printloadingtrucks(company->getloadingtruck('N'));
			printloadingtrucks(company->getloadingtruck('S'));
			printloadingtrucks(company->getloadingtruck('V'));
			cout << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountTrucks('E') << " Empty Trucks : [";
			company->PrintTrucks(11);
			cout << "] (";
			company->PrintTrucks(12);
			cout << ") {";
			company->PrintTrucks(13);
			cout << "}" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountCargos('M') << " Moving Cargos : ";
			printmovingcargos(company->getmovingqueue());
			cout << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountTrucks('C') << " InCheckUp Trucks : [";
			company->PrintTrucks(21);
			cout << "] (";
			company->PrintTrucks(22);
			cout << ") {";
			company->PrintTrucks(23);
			cout << "}" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountCargos('D') << " Delivered Cargos : ";
			printdeliveredcargos(company->getdeliveredqueue());
			cout << endl << endl;
			if (cin.get() == '\n')
			{
				if (hour == 23)
				{
					hour = 0;
					day++;
				}
				else
					hour++;
			}
			company->ExecuteLoading();
			while (company->ExecuteAction(day, hour));
		}
		company->OutPut_file();
		break;
	case('B'):
		while (test)
		{
			test = !company->IsnotWorking();
			cout << "Current Time(Day:Hour): " << day << ":" << hour << endl;
			cout << company->CountCargos('W') << " Waiting Cargos : [";
			company->PrintCargos(11);
			cout << "] (";
			company->PrintCargos(12);
			cout << ") {";
			company->PrintCargos(13);
			cout << "}" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountTrucks('L') << " Loading Trucks : ";
			printloadingtrucks(company->getloadingtruck('N'));
			printloadingtrucks(company->getloadingtruck('S'));
			printloadingtrucks(company->getloadingtruck('V'));
			cout << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountTrucks('E') << " Empty Trucks : [";
			company->PrintTrucks(11);
			cout << "] (";
			company->PrintTrucks(12);
			cout << ") {";
			company->PrintTrucks(13);
			cout << "}" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountCargos('M') << " Moving Cargos : ";
			printmovingcargos(company->getmovingqueue());
			cout << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountTrucks('C') << " InCheckUp Trucks : [";
			company->PrintTrucks(21);
			cout << "] (";
			company->PrintTrucks(22);
			cout << ") {";
			company->PrintTrucks(23);
			cout << "}" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;

			cout << company->CountCargos('D') << " Delivered Cargos : ";
			printdeliveredcargos(company->getdeliveredqueue());
			cout << endl << endl;

			Sleep(1000);
			if (hour == 23)
			{
				hour = 0;
				day++;
			}
			else
				hour++;
			company->ExecuteLoading();
			while (company->ExecuteAction(day, hour));
		}
		company->OutPut_file();
		break;
	case('S'):
		while (test)
		{
			test = !company->IsnotWorking();
			if (hour == 23)
			{
				hour = 0;
				day++;
			}
			else
				hour++;
			company->ExecuteLoading();
			while (company->ExecuteAction(day, hour));
		}
		company->OutPut_file();
		cout << "Silent Mode" << endl;
		cout << "    Simulation Starts... " << endl;
		cout << "    Simulation ends, Output file created" << endl;
		break;
	}
}

void UI::printdeliveredcargos(Queue<Cargo*>* q)
{
	Cargo* item;
	int n = q->getcount();
	for (int i = 0; i < n; i++)
	{
		q->dequeue(item);
		if (dynamic_cast<Normal_Cargo*>(item))
			cout << "[" << item << "] ";
		else if (dynamic_cast<Special_Cargo*>(item))
			cout << "(" << item << ") ";
		else
			cout << "{" << item << "} ";
		q->enqueue(item);
	}
}

void UI::printloadingtrucks(Truck* item)
{
	Cargo* c;
	if (item)
	{
		c = item->Check_Type();
		if (c)
		{
			if (dynamic_cast<Normal_Cargo*>(c))
			{
				cout << item << "[";
				item->Print_Loaded_Cargos();
				cout << "] ";
			}
			else if (dynamic_cast<Special_Cargo*>(c))
			{
				cout << item << "(";
				item->Print_Loaded_Cargos();
				cout << ") ";
			}
			else
			{
				cout << item << "{";
				item->Print_Loaded_Cargos();
				cout << "} ";
			}
			cout << " ";
		}
	}
}

void UI::printmovingcargos(PriorityQueue<Truck*>* q)
{
	Truck* item;
	Queue<Truck*>* tmp = new Queue<Truck*>;
	while (q->dequeue(item))
	{
		if (dynamic_cast<Normal_Cargo*>(item->Check_Type()))
		{
			cout << item << "[";
			item->Print_Loaded_Cargos();
			cout << "] ";
		}
		else if (dynamic_cast<Special_Cargo*>(item->Check_Type()))
		{
			cout << item << "(";
			item->Print_Loaded_Cargos();
			cout << ") ";
		}
		else
		{
			cout << item << "{";
			item->Print_Loaded_Cargos();
			cout << "} ";
		}
		cout << " ";
		tmp->enqueue(item);
	}
	while (tmp->dequeue(item))
		q->enqueue(item, item->GetPriorityMoving());
}


ostream& operator<<(ostream& Out, const Cargo* c)
{
	Out << c->GetID();
	return Out;
}

ostream& operator<<(ostream& Out, const Truck* t)
{
	Out << t->GetID();
	return Out;
}
