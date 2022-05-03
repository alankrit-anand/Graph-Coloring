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

	char use_ai_algos;
	flag = 0;

	do
	{
		if(flag)
		{
			cout << "Invalid Input" << endl;
		}

		cout << "Use AI algorithms? (y/n): ";
		cin >> use_ai_algos;
		flag = 1;
	}
	while(use_ai_algos != 'y' && use_ai_algos != 'n');

	

	freopen("time_simulation.py", "w", stdout);

	cout << "import matplotlib.pyplot as plt\nimport numpy as np\nplt.ylabel('Time (in ms)')\nplt.xlabel('Probability * 100')" << endl;

	// generate x-cordinates

	cout << "xpoints = np.array([";

	for(int p = 1; p <= 100; p++)
	{
		cout << p << ", ";
	}

	cout << "])" << endl;


	for(int rep = 0; rep < (use_ai_algos == 'y' ? 5 : 3); rep++)
	{

		cout << "ypoints" << (rep + 1) << " = np.array([";


		for(int p = 1; p <= 100; p++)
		{
			vector<vector<int>> g(n);
			int e = 0;

			for(int u = 0; u < n; u++)
			{
				for(int v = u + 1; v < n; v++)
				{
					int x = rng(mt) % 100;

					if(x < p)
					{
						g[u].push_back(v);
						g[v].push_back(u);
						e += 2;
					}
				}
			}

			// initialise clock
			clock_t z = clock();

			if(rep < 3)
			{
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
			}
			else if(rep == 3)
			{
				//Values for the Genetic Algorithm
				int max_iterations = 100; 
			    int n_individuals = 20;
			    double p_best = 40.0, p_cross = 40.0,p_mutation = 20.0; 
			    int min_colors = 0;
			    int total_iteration = 0;


				GA GA_Solution(n_individuals, n, e, g);
			    GA_Solution.MainLoop(max_iterations, total_iteration, p_best, p_cross, p_mutation, min_colors);

			    Individual fittest_individual = GA_Solution.population[0];
			    assert(fittest_individual.is_valid(g));
			}
			else if(rep == 4)
			{
				//Values for the Simulated Annealing Algorithm
				int max_iterations = 1000; 			
		        double initial_temp = 1.0;
		        double min_temp = 0;
		        int min_colors = 0;
		        int total_iteration = 0;

		        SA SA_solution(initial_temp, n, e, g);
		        SA_solution.MainLoop(max_iterations, min_temp, total_iteration, min_colors);


		        Individual solution = SA_solution.GetBestState();
		        assert(solution.is_valid(g));
			}

			cout << (clock() - z) * 1000 / CLOCKS_PER_SEC << ", ";
			cout << flush;
		}

		cout << "])" << endl;

	}

	cout << "plt.plot(xpoints, ypoints1, label = 'Greedy')\nplt.plot(xpoints, ypoints2, label = 'DSatur')\nplt.plot(xpoints, ypoints3, label = 'RLF')";
	if(use_ai_algos == 'y')
		cout << "\nplt.plot(xpoints, ypoints4, label = 'Genetic Algorithm')\nplt.plot(xpoints, ypoints5, label = 'Simulated Annealing')";
	cout << "\nplt.legend()\nplt.show()";




	return 0;
}