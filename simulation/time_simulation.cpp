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



int main()
{
	int n, flag = 0;

	do
	{
		if(flag)
		{
			cout << "Number of nodes must be between 1 and 1000" << endl;
		}

		cout << "Number of Nodes in the graph: ";
		cin >> n;
		flag = 1;
	}
	while(n < 1 || n > 1000);

	

	freopen("time_simulation.py", "w", stdout);

	cout << "import matplotlib.pyplot as plt\nimport numpy as np\nplt.ylabel('Time (in ms)')\nplt.xlabel('Probability * 100')" << endl;

	// generate x-cordinates

	cout << "xpoints = np.array([";

	for(int p = 1; p <= 100; p++)
	{
		cout << p << ", ";
	}

	cout << "])" << endl;


	for(int rep = 0; rep < 3; rep++)
	{

		if(rep == 0)
		{
			cout << "ypoints1 = np.array([";
		}
		else if(rep == 1)
		{
			cout << "ypoints2 = np.array([";
		}
		else
		{
			cout << "ypoints3 = np.array([";
		}

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

			// initialise clock
			clock_t z = clock();

			graph -> color_graph();
			assert(graph -> is_valid());

			cout << (clock() - z) * 1000 / CLOCKS_PER_SEC << ", ";

			//cout << graph -> chromatic_number() << ", ";
		}

		cout << "])" << endl;

	}

	cout << "plt.plot(xpoints, ypoints1, label = 'Greedy')\nplt.plot(xpoints, ypoints2, label = 'DSatur')\nplt.plot(xpoints, ypoints3, label = 'RLF')\nplt.legend()\nplt.show()";




	return 0;
}