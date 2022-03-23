#include <iostream>
#include <tuple>
#include <set>

#include "../header/Dsatur.hpp"

using namespace std;


struct Node
{
	int saturation_degree;		// saturation degree of node 
	int degree;					// degree in uncolored graph
	int id;						// ID of node

	// comparision operator to sort nodes first by decreasing saturation_degree and then by degree 
	bool operator < (const Node &other) const
	{
		return tie(saturation_degree, degree, id) > tie(other.saturation_degree, other.degree, other.id);
	}
};



void GraphColoring :: Dsatur :: color_graph()
{
	vector<bool> used(n);
	vector<int> saturation_degree(n);
	vector<int> degree(n);

	set<Node> q;

	// initialise data structures
	for(int i = 0; i < n; i++)
	{
		color[i] = -1;
		degree[i] = graph[i].size();
		q.insert(Node{0, degree[i], i});
	}

	while(q.size())
	{
		// choose the node with highest saturation degree and then by degree
		int v = q.begin() -> id;
		q.erase(q.begin());

		// choose optimal color for node v
		for(int to : graph[v])
		{
			if(color[to] != -1)
			{
				used[color[to]] = 1;
			}
		}

		for(int col = 0; col < n; col++)
		{
			if(!used[col])
			{
				color[v] = col;
				break;
			}
		}

		for(int to : graph[v])
		{
			if(color[to] != -1)
			{
				used[color[to]] = 0;
			}
		}

		// Update the saturation degrees and degrees of all uncolored neighbours;
		for(int to : graph[v])
		{
			if(color[to] == -1)
			{
				q.erase(Node{saturation_degree[to], degree[to], to});
				saturation_degree[to]++;
				degree[to]--;
				q.insert(Node{saturation_degree[to], degree[to], to});
			}
		}
	}
}


