#include <bits/stdc++.h>
#include "../header/RLF.hpp"

using namespace std;



int unprocessed;
int neighour_count;
vector<int> degree;
vector<int> neighbours;


void GraphColoring :: RLF :: initialise()
{
	unprocessed = n;
	degree.resize(n);
	neighbours.resize(n);

	for(int i = 0; i < n; i++)
	{
		color[i] = -1;
		degree[i] = graph[i].size();
	}
}


int GraphColoring :: RLF :: max_degree_node()
{
	int node = -1, max_degree = -1;

	for(int i = 0; i < n; i++)
	{
		if(color[i] == -1 && degree[i] > max_degree)
		{
			max_degree = degree[i];
			node = i;
		}
	}

	return node;
}

void GraphColoring :: RLF :: update_neighbours(int col_num)
{
	neighour_count = 0;

	// Add all the uncolored vertex in the set which are not neighbours of nodes of color col-num
	for(int i = 0; i < n; i++)
	{
		if(color[i] == -1)
		{
			bool has_col_num_neighbours = 0;

			for(int to : graph[i])
			{
				has_col_num_neighbours |= (color[to] == col_num); 
			}

			if(!has_col_num_neighbours)
			{
				neighbours[neighour_count++] = i;
			}
		}
	}
}


int GraphColoring :: RLF :: find_suitable_node(int col_num, int &vertices_in_common)
{
	int y = -1;

	for(int i = 0; i < neighour_count; i++)
	{
		// v is vertex being processed
		int v = neighbours[i];

		// stores if vertex is neighbour of v
		vector<bool> neighbours_of_v(n);

		for(int to : graph[v])
		{
			neighbours_of_v[to] = 1;
		}

		// common_neighbours stores number of neighbours in common
		int common_neighbours = 0;

		// stores uncolored vertices except the vertex currently being processed
		vector<bool> scanned(n);

		for(int x = 0; x < n; x++)
		{
			if(color[x] == col_num)
			{
				for(int to : graph[x])
				{
					if(color[to] == -1 && !scanned[to] && neighbours_of_v[to])
					{
						common_neighbours++;
						scanned[to] = 1;
					}
				}
			}
		}

		if(common_neighbours > vertices_in_common)
		{
			vertices_in_common = common_neighbours;
			y = v;
		}

	}

	return y;
}






int GraphColoring :: RLF :: max_degree_in_common_neighbours()
{
	int v = -1, max_degree = -1;

	for(int i = 0; i < neighour_count; i++)
	{
		int u = neighbours[i];
		int cur_degree = 0;

		for(int to : graph[u])
		{
			if(color[to] == -1)
			{
				cur_degree++;
			}
		}

		if(cur_degree > max_degree)
		{
			max_degree = cur_degree;
			v = u;
		}
	}

	return v;
}


void GraphColoring :: RLF :: color_graph()
{
	initialise();

	int col_num = 0;

	while(unprocessed > 0)
	{
		int v = max_degree_node();
		color[v] = col_num;
		unprocessed--;

		update_neighbours(col_num);

		while(neighour_count > 0)
		{
			int vertices_in_common = -1;

			// find the node which has maximum neighbours in common with v 
			int u = find_suitable_node(col_num, vertices_in_common);

			// If vertices_in_common = 0, y is vertex with highest degree in common_neighbours
			if(vertices_in_common == 0)
			{
				u = max_degree_in_common_neighbours();
			}

			color[u] = col_num;
			unprocessed--;
			update_neighbours(col_num);

		}

		col_num++;
	}


}



