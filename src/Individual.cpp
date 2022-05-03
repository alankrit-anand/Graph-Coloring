#include "../header/Individual.h"


    Individual :: Individual(int n_genes){
        this->n_genes = n_genes;
        //chromosome.resize(n_genes);


        
        int random;
        int colour = 0;
        
        for(int i = 0; i < n_genes; i++){

            
            random = this->getRandom(0.0 , n_genes);

            if(random == 0 || i == 0)
                chromosome.push_back(colour);
            else{
                colour++;
                chromosome.push_back(colour);
            } 
        }
    };

    Individual::Individual(vector<int> chromosome){
        this->chromosome = chromosome;
        this->n_genes = chromosome.size();
    };

    int Individual::getNumOfColours(){
        set<int> distinct_colors;

        for(auto curr_int = chromosome.begin(), end = chromosome.end(); curr_int != end; ++curr_int)
        {
            distinct_colors.insert(*curr_int);
        }

        return distinct_colors.size();
    };

    void Individual::printChromosome(){

        for(int i = 0; i < (int) chromosome.size(); i++){
            cout << GREEN << BLACK_FOREGRND << " " << this->chromosome[i]  << END ;
        }
        cout << " N of colour used: " <<this->getNumOfColours() <<endl;            
    };

    int Individual::at(int i){
        return this->chromosome[i];
    };

    void Individual::setFitness(int fitness){
        this->fitness = fitness;
    };

    int Individual::getFitness(){
        return this->fitness;
    };

    void Individual::mutate(){
        this->fitness = 0;
        double max_iterations = n_genes/2;

        //cout << "colours: "<< colours/2 << endl;
        int random_a = this->getRandom(1.0 , max_iterations);
        int random_b;
        //cout << "random_a: "<< random_a << endl;

        for(int i = 0; i < random_a; i++){
            random_b = this->getRandom(0.0 , n_genes - 1);
            replace (chromosome.begin(), chromosome.end(), chromosome[random_b], chromosome[ (random_b + i + random_a)%n_genes ]);
        }

    };

    Individual Individual::reproduce(Individual parent_2){

        double start = n_genes/3;
        int random_a = this->getRandom(start , n_genes);
        //cout << "Random_a: " << random_a << endl;
        vector<int> new_indiviual_chr = this->chromosome;

        for(int i = random_a; i < n_genes; i++){
            new_indiviual_chr[i] = parent_2.at(i);
        }

        Individual new_ind(new_indiviual_chr);
        return new_ind;
    };

    void Individual::insertColor(int p, int c){
        chromosome[p] = c;
    };

    bool Individual :: is_valid(vector<vector<int>> &g)
    {
        bool valid = 1;

        for(int i = 0; i < n_genes; i++)
        {
            for(int to : g[i])
            {
                if(chromosome[i] == chromosome[to])
                {
                    valid = 0;
                }
            }
        }

        return valid;
    }

