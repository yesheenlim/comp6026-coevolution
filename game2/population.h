
#include <vector>
#include "individual.h"

#ifndef POPULATION_H
#define POPULATION_H

class Population
{
public:
    std::vector<Individual> data; // population individuals

    Population(int,int,int); // constructor
    void mutate(); // mutation
    std::vector<std::vector<int> > getSample(); // get samples S
    void score2(int, std::vector<std::vector<int> >); // compute subjective fitness 2
    void score3(int, std::vector<std::vector<int> >); // compute subjective fitness 3
    int fitsum(); // sum of fitness
    int average_obj(); // returns average objective fitness
    void roulette(); // roulette selection
};

#endif // POPULATION_H
