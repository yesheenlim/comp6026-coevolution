
#include <vector>
#include "individual.h"

#ifndef POPULATION_H
#define POPULATION_H

class Population
{
public:
    std::vector<Individual> data; // population individuals

    Population(int,int,int); // constructor
    void roulette(); // roulette wheel
    void mutate(); // mutation
    void score1(int, std::vector<int>); // evaluate subjective fitness 1
    std::vector<int> getSample(); // get samples S
    int fitsum(); // returns total fitness of population
    int average_obj(); // returns population average objective fitness
    void penalize(); // penalizes fit individuals
};

#endif // POPULATION_H
