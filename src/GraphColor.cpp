
#include <iostream>

#include "../header/GraphColor.hpp"

using namespace std;

GraphColoring :: GraphColor :: GraphColor(int number_of_nodes)
{
    n = number_of_nodes;
    graph.resize(n);
    color.resize(n);
    is_colored = 0;
}


GraphColoring :: GraphColor :: GraphColor(vector<vector<int>> g)
{
    n = g.size();
    graph = g;
    color.resize(n);
    is_colored = 0;
}


bool GraphColoring :: GraphColor :: is_valid()
{
    for(int i = 0; i < n; i++)
    {
        for(int to : graph[i])
        {
            if(color[i] == color[to])
                return 0;
        }
    }

    return 1;
}


int GraphColoring :: GraphColor :: chromatic_number()
{
    int max_color = 0;

    for(int i = 0; i < n; i++)
    {
        max_color = max(max_color, color[i]);
    }

    return max_color + 1;
}


void GraphColoring :: GraphColor :: print_coloring()
{
    cout << "\t\tID\t\t\tColor" << endl;

    for(int i = 0; i < n; i++)
    {
        cout << "\t\t" << i << "\t\t\t" << color[i] << endl;
    }
}

void GraphColoring :: GraphColor :: print_chromatic()
{
    cout << get_algorithm() << " Chromatic Number: " << chromatic_number() << endl;
}




