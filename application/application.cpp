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

		cout << "Choose the Application" << endl;
		cout << "1: Color a Graph\n2: Sudoku Solver\n3: Check if a Graph is Bipartite" << endl;
		cout << "Your choice: ";
		cin >> choice;
		flag = 1;
	}
	while(choice < 1 || choice > 3);

	if(choice == 1)
	{
		system("g++ color_graph.cpp ../src/*.cpp && ./a.out && python color_graph.py");
	}
	else if(choice == 2)
	{
		system("g++ sudoku_solver.cpp ../src/*.cpp && ./a.out");
	}
	else
	{
		system("g++ partite_graph_checker.cpp ../src/*.cpp && ./a.out");
	}





	return 0;
}