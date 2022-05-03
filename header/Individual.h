#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <random>
#include <algorithm>
#include <set>

#define END "\e[0m"
#define BLUE "\e[44m"
#define RED "\e[45m"
#define GREEN "\e[42m"
#define BLACK_FOREGRND "\e[30m"
    

using namespace std;

/*
The Individual class is used in the Genetic Algorithm and in the Simulated Annealing
algorithm because the implementation and some methods are useful 
but the usage is different.
The fitness is for the GA but in SA it is used as the cost
*/
class Individual{
    public:
        vector<int> chromosome;
        int n_genes;
        int N_colours_used = 0;
        int fitness = 0;


        Individual(){};

        /*  Initialize a certain individual with random values, 
            and n_genes number of genes
        */
        Individual(int n_genes);

        /*  Create an individual with a given chromosome and the number of colours used
        */
        Individual(vector<int> chromosome);

        /*  Numer of differents colours used in this result
        */
        int getNumOfColours();

        /*  Print the Chromosome and its colours 
        */
        void printChromosome();

        /*  It will return the value of the chromosome at the i position
        */
        int at(int i);

        /*  Assign a value to the fitness
        */
        void setFitness(int fitness);

        /*  Return the fitness of the individual
        */
        int getFitness();

        /*  It will mutate the individual
        */ 
        void mutate();

        /*  Will create a new Individual based on his parents
            Parent 1 will be the Individual that has been instatiated.
            parent_2: The second parent
            It will create a random number that will be the
                percentage used from the parent 1 
                (1-p will be the percentage used from parent_2)
            return: The new individual
        */
        Individual reproduce(Individual parent_2);

        /*  Insert a color c 
            in a certain position p
        */
        void insertColor(int p, int c); 

        bool is_valid(vector<vector<int>> &g);

        double getRandom(double start, double finish){
            random_device rd;
            mt19937 mt(rd());
            uniform_real_distribution<double> dist(start, finish);
        return dist(mt);
        }


        


};

#endif