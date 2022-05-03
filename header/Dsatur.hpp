#ifndef _DSATUR_HPP_
#define _DSATUR_HPP_

#include "GraphColor.hpp"

using GraphColoring :: GraphColor;

namespace GraphColoring
{
	class Dsatur : public GraphColor 
	{
		public:

			// Constructors
			Dsatur(int number_of_nodes) : GraphColor(number_of_nodes) {};
			Dsatur(vector<vector<int>> graph) : GraphColor(graph) {};

			// colors the graph
            void color_graph();
            void sudoku_color();

			// returns name of the algorithm
			string get_algorithm() { return "DSATUR"; }

	};
}

#endif //_DSATUR_HPP_