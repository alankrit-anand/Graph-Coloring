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



int main()
{
	int n, e, flag = 0;

	cout << "Number of nodes in the graph: ";
	cin >> n;


	do
	{
		if(flag)
		{
			cout << "Number of edges must be between 0 and " << n * (n - 1) / 2 << endl;
		}

		cout << "Number of edges in the graph: ";
		cin >> e;
		flag = 1;
	}
	while(e < 0 && e > n * (n - 1) / 2);


	vector<vector<int>> g(n);
	set<pair<int, int>> edges_added;

	for(int i = 1; i <= e; i++)
	{
		int u, v;
		flag = 0;

		do
		{
			if(flag)
			{
				cout << "Edge already added" << endl;
			}

			bool flag1 = 0;

			do
			{	
				if(flag1)
				{
					cout << "Nodes must be between 0 and " << n - 1 << endl;
				}

				cout << "Edge " << i << ": ";
				cin >> u >> v;
				flag1 = 1;
			}
			while(u < 0 || u > n - 1 || v < 0 || v > n - 1);

			flag = 1;
		}
		while(edges_added.count({u, v}));
		
		edges_added.insert({u, v});
		edges_added.insert({v, u});

		g[u].push_back(v);
		g[v].push_back(u);

	}


	
	int choice;
	flag = 0;

	do
	{
		if(flag)
		{
			cout << "Choice must be between 1 and 3" << endl;
		}

		cout << "Choose the Coloring algorithm" << endl;
		cout << "1: Greedy\n2: DSatur\n3: RLF\n4: Genetic Algorithm\n5: Simulated Annealing" << endl;
		cout << "Your choice: ";
		cin >> choice;
		flag = 1;
	}
	while(choice < 1 || choice > 5);


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


		GA GA_Solution(n_individuals, n, 2 * e, g);
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

        SA SA_solution(initial_temp, n, 2 * e, g);
        SA_solution.MainLoop(max_iterations, min_temp, total_iteration, min_colors);


        Individual solution = SA_solution.GetBestState();
        assert(solution.is_valid(g));

        color = solution.chromosome;
	    num_of_colors = solution.getNumOfColours();
	}


	// generate python code

	freopen("color_graph.py", "w", stdout);

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