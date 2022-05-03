#include <bits/stdc++.h>
#include "../header/Dsatur.hpp"

using namespace std;

using GraphColoring :: Dsatur;



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


	GraphColor *graph = new Dsatur(g);
	graph -> color_graph();
	assert(graph -> is_valid());


	cout << endl;

	if(graph -> chromatic_number() <= 2)
	{
		cout << "The Graph is Bipartite" << endl;

		for(int i = 0; i < n; i++)
		{
			cout << "Color " << i << ": " << (graph -> color[i] ? "Black" : "White") << endl;
		}
	}
	else
	{
		cout << "The Graph is Not Bipartite" << endl;
	}

}