#include <bits/stdc++.h>

#include "../header/Dsatur.hpp"
#include "../header/RLF.hpp"
#include "../header/Greedy.hpp"

using namespace std;

using GraphColoring :: GraphColor;
using GraphColoring :: Dsatur;
using GraphColoring :: RLF;
using GraphColoring :: Greedy;

mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rng(0, 1e9);



const int k = 5;


const int n = 1000;



int main()
{
	for(int p = 1; p <= 100; p++)
	{
		cout << p << ", ";
	}

	cout << endl;

	for(int rep = 0; rep < 1; rep++)
	{

		for(int p = 1; p <= 100; p++)
		{
			vector<vector<int>> g(n);

			for(int u = 0; u < n; u++)
			{
				for(int v = u + 1; v < n; v++)
				{
					int x = rng(mt) % 100;

					if(x < p)
					{
						g[u].push_back(v);
						g[v].push_back(u);
					}
				}
			}

			GraphColor *graph = new RLF(g);

			if(rep == 0)
			{
				graph = new Greedy(g);
			}
			else if(rep == 1)
			{
				graph = new Dsatur(g);
			}
			else if(rep == 2)
			{
				graph = new RLF(g);
			}

			graph -> color_graph();
			assert(graph -> is_valid());

			cout << graph -> chromatic_number() << ", ";
			cout << flush;
		}

	}


	return 0;
}