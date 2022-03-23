#ifndef _GRAPH_COLOR_HPP_
#define _GRAPH_COLOR_HPP_

#include <vector>
#include <string>
using namespace std;

namespace GraphColoring 
{
    class GraphColor 
    {
        public:

            int n;                          // number of nodes in graph
            vector<vector<int>> graph;      // adjacency list
            vector<int> color;              // stores color of the node 
            bool is_colored;                // stores if graph has been colored 

            /* Constructors */
            GraphColor(int number_of_nodes);
            GraphColor(vector<vector<int>> graph);

            // Validates if coloring is valid
            bool is_valid();

            // returns chromatic number
            int chromatic_number();

            // Print Functions
            void print_coloring();
            void print_chromatic();


            /* Virtual Functions to be implemented by individual coloring alorithms */

            // colors the graph
            virtual void color_graph() = 0;

            // returns name of the algorithm used
            virtual string get_algorithm() = 0;
    };
}

#endif // _GRAPH_COLOR_HPP_