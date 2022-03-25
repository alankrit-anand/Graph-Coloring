#include <bits/stdc++.h>

using namespace std;


int main()
{
	int choice, flag = 0;

	do
	{
		if(flag)
		{
			cout << "Choice must be between 1 and 3" << endl;
		}

		cout << "Choose the Simulation" << endl;
		cout << "1: Coloring Simulation\n2: Probabilty Simulation\n3: Time Simulation" << endl;
		cout << "Your choice: ";
		cin >> choice;
		flag = 1;
	}
	while(choice < 1 || choice > 3);

	if(choice == 1)
	{
		system("g++ coloring_simulation.cpp ../src/*.cpp && ./a.out && python coloring_simulation.py");
	}
	else if(choice == 2)
	{
		system("g++ probability_simulation.cpp ../src/*.cpp && ./a.out && python probability_simulation.py");
	}
	else
	{
		system("g++ time_simulation.cpp ../src/*.cpp && ./a.out && python time_simulation.py");
	}





	return 0;
}