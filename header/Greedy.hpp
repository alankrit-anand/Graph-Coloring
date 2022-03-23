#ifndef _GREEDY_HPP_
#define _GREEDY_HPP_

#include "GraphColor.hpp"

using GraphColoring :: GraphColor;

namespace GraphColoring
{
	class Greedy : public GraphColor 
	{
		public:

			// Constructors
			Greedy(int number_of_nodes) : GraphColor(number_of_nodes) {};
			Greedy(vector<vector<int>> graph) : GraphColor(graph) {};

			// colors the graph
            void color_graph();

			// returns name of the algorithm
			string get_algorithm() { return "Greedy"; }
	};
}

#endif //_GREEDY_HPP_