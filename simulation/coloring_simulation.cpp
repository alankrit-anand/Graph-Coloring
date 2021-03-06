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
	int n, p, e = 0, flag = 0;

	cout << "Number of nodes in the graph: ";
	cin >> n;

	do
	{
		if(flag)
		{
			cout << "P must be between 0 and 100" << endl;
		}

		cout << "P (2 nodes will be connected with probabilty P%): ";
		cin >> p;
		flag = 1;
	}
	while(p < 0 || p > 100);

	
	int choice;
	flag = 0;

	do
	{
		if(flag)
		{
			cout << "Choice must be between 1 and 5" << endl;
		}

		cout << "Choose the Coloring algorithm" << endl;
		cout << "1: Greedy\n2: DSatur\n3: RLF\n4: Genetic Algorithm\n5: Simulated Annealing" << endl;
		cout << "Your choice: ";
		cin >> choice;
		flag = 1;
	}
	while(choice < 1 || choice > 5);


	// generate graph with n nodes and p % probabilty of edge between two nodes

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
				e += 2;
			}
		}
	}

	vector<int> color;
	int num_of_colors;

	if(choice < 4)
	{
		GraphColor *graph;

		if(choice == 1)
		{
			graph = new Greedy(g);
		}
		else if(choice == 2)
		{
			graph = new Dsatur(g);
		}
		else if(choice == 3)
		{
			graph = new RLF(g);
		}

		graph -> color_graph();
		color = graph -> color;
		num_of_colors = graph -> chromatic_number();

		assert(graph -> is_valid());
	}
	else if(choice == 4)
	{
        //Values for the Genetic Algorithm
		int max_iterations = 1000; 
	    int n_individuals = 20;
	    double p_best = 40.0, p_cross = 40.0,p_mutation = 20.0; 
	    int min_colors = 0;
	    int total_iteration = 0;


		GA GA_Solution(n_individuals, n, e, g);
	    GA_Solution.MainLoop(max_iterations, total_iteration, p_best, p_cross, p_mutation, min_colors);

	    Individual fittest_individual = GA_Solution.population[0];
	    assert(fittest_individual.is_valid(g));

	    color = fittest_individual.chromosome;
	    num_of_colors = fittest_individual.getNumOfColours();
	}
	else if(choice == 5)
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

        color = solution.chromosome;
	    num_of_colors = solution.getNumOfColours();
	}


	// generate python code

	freopen("coloring_simulation.py", "w", stdout);

	cout << "import networkx as nx\nimport matplotlib.pyplot as plt\nimport warnings\nwarnings.filterwarnings(\"ignore\", category=UserWarning)\nfig = plt.figure(1, figsize = (30, 30))\nG = nx.Graph()\npos = nx.circular_layout(G)" << endl;

	// add nodes

	cout << "G.add_nodes_from([";

	for(int i = 0; i < n; i++)
	{
		cout << i << ", ";
	}

	cout << "])" << endl;

	// add edges

	cout << "G.add_edges_from([";

	for(int i = 0; i < n; i++)
	{
		for(int to : g[i])
		{
			if(i < to)
			{
				cout << "(" << i << ", " << to << "), ";
			}
		}
	}

	cout << "])" << endl;

	cout << "nx.draw_circular(G, with_labels = 'true', node_color = (";

	for(int i = 0; i < n; i++)
	{
		cout << color[i] << ", ";
	}

	cout << "), node_size = 1500, font_color = 'white', font_size = 15)" << endl;
	cout << "plt.figtext(0.87, 0.90, \"Colors used: " << num_of_colors << "\", horizontalalignment =\"center\", wrap = True, fontsize = 15, bbox ={\'facecolor\':\'grey\', \'alpha\':0.3, \'pad\':5})" << endl;
	cout << "plt.show()";

}