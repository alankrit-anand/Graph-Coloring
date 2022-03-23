#include <bits/stdc++.h>
#include "../header/Greedy.hpp"

using namespace std;


void GraphColoring :: Greedy :: color_graph()
{
	mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

	fill(color.begin(), color.end(), -1);

	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	shuffle(order.begin(), order.end(), mt);

	for(int v : order)
	{
		vector<bool> used(n);

		for(int to : graph[v])
		{
			if(color[to] != -1)
			{
				used[color[to]] = 1;
			}
		}

		int col = 0;

		while(used[col])
			col++;

		color[v] = col;
	}

}