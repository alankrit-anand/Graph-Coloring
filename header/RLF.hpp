#ifndef _RLF_HPP_
#define _RLF_HPP_

#include "GraphColor.hpp"

using GraphColoring :: GraphColor;

namespace GraphColoring
{
	class RLF : public GraphColor 
	{
		public:

			// Constructors
			RLF(int number_of_nodes) : GraphColor(number_of_nodes) {};
			RLF(vector<vector<int>> graph) : GraphColor(graph) {};

			// colors the graph
            void color_graph();

			// returns name of the algorithm
			string get_algorithm() { return "RLF"; }

			// helper functions
			void initialise();
			int max_degree_node();
			void update_neighbours(int col_num);
			int find_suitable_node(int col_num, int &vertices_in_common);
			int max_degree_in_common_neighbours();

	};
}

#endif //_RLF_HPP_