#include <bits/stdc++.h>

#include "../header/Dsatur.hpp"
#include "../header/RLF.hpp"
#include "../header/Greedy.hpp"
#include "../header/GA.h"
#include "../header/SA.h"

using namespace std;

using GraphColoring :: GraphColor;
using GraphColoring :: Dsatur;
using GraphColoring :: RLF;
using GraphColoring :: Greedy;




bool checkRow(vector<vector<int>> &a, int n)
{
	bool flag = 0;

	for(int i = 0; i < n; i++)
	{
		set<int> s;

		for(int j = 0; j < n; j++)
		{
			if(a[i][j] != -1)
			{
				flag |= s.count(a[i][j]);
				s.insert(a[i][j]);
			}
		}
	}

	return flag;	
}

bool checkCol(vector<vector<int>> a, int n)
{
	bool flag = 0;

	for(int j = 0; j < n; j++)
	{
		set<int> s;

		for(int i = 0; i < n; i++)
		{
			if(a[i][j] != -1)
			{
				flag |= s.count(a[i][j]);
				s.insert(a[i][j]);
			}
		}
	}

	return flag;	
}

bool checkBox(vector<vector<int>> a, int n)
{
	int x = 0;

	while((x + 1) * (x + 1) <= n)
	{
		x++;
	}

	bool flag = 0;

	for(int i = 0; i < n; i += x)
	{
		for(int j = 0; j < n; j += x)
		{
			set<int> s;

			for(int ni = i; ni < i + x; ni++)
			{
				for(int nj = j; nj < j + x; nj++)
				{
					if(a[ni][nj] != -1)
					{
						flag |= s.count(a[ni][nj]);
						s.insert(a[ni][nj]);
					}
				}
			}
		}
	}

	return flag;
}


bool perfect_square(int n)
{
	int x = 0;

	while((x + 1) * (x + 1) <= n)
	{
		x++;
	}

	return x * x == n;
}



int main()
{
	int n, flag = 0;


	do
	{
		if(flag)
		{
			cout << "Number of nodes must be a perfect square" << endl;
		}

		cout << "Number of rows in the Sudoku: ";
		cin >> n;
		flag = 1;
	}
	while(!perfect_square(n));

	flag = 0;
	vector<vector<int>> a(n, vector<int>(n));
	vector<vector<int>> g(n * n);

	do
	{
		if(flag)
		{
			cout << "Please enter a valid sudoku " << endl;
		}

		flag = 0;
		cout << "Enter the configuration of sudoku. Indicate blank cell using -1." << endl;
		
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				cin >> a[i][j];

				if(a[i][j] != -1)
				{
					a[i][j]--;
					flag |= a[i][j] < 0 && a[i][j] >= n;
				}
			}
		}

		flag |= checkRow(a, n);
		flag |= checkCol(a, n);
		flag |= checkBox(a, n);

	}
	while(flag);


	int x = 0;

	while((x + 1) * (x + 1) <= n)
	{
		x++;
	}

	for(int i = 0; i < n * n; i++)
	{
		for(int j = i; j < n * n; j++)
		{
			int r1 = i / n, c1 = i % n;
			int r2 = j / n, c2 = j % n;

			if(r1 == r2 || c1 == c2 || (r1 / x == r2 / x && c1 / x == c2 / x))
			{
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}


	Dsatur *graph = new Dsatur(g);

	for(int i = 0; i < n * n; i++)
	{
		int r = i / n, c = i % n;
		graph -> color[i] = a[r][c];
	}

	graph -> sudoku_color();
	graph -> is_valid();

	cout << endl << "Result:" << endl;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int value = (graph -> color[i * n + j]) + 1;
			cout << value;

			if(value < 10)
				cout << ' ';

			if(j % x == x - 1)
				cout << "\t\t";
			else
				cout << ' ';
		}

		if(i % x == x - 1)
			cout << endl;

		cout << endl;
	}


}