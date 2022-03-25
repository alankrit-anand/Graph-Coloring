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
	int n, p, flag = 0;

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
			cout << "Choice must be between 1 and 3" << endl;
		}

		cout << "Choose the Coloring algorithm" << endl;
		cout << "1: Greedy\n2: DSatur\n3: RLF" << endl;
		cout << "Your choice: ";
		cin >> choice;
		flag = 1;
	}
	while(choice < 1 || choice > 3);


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
			}
		}
	}



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
	assert(graph -> is_valid());

	

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
		cout << graph -> color[i] << ", ";
	}

	cout << "), node_size = 320, font_color = 'white', font_size = 5)\nplt.show()";

}