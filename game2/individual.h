
#include <vector>

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

class Individual
{
public:
    std::vector<int> bin; // binary value of individual
    std::vector<int> val; // integer value of individual
    int fit; // individual subjective fitness

    void unitation(); // unitation operation
    void mutate(); // mutation operation

    Individual(int,int); // constructor
};

#endif
