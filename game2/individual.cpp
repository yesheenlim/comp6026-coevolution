
#include <iostream>
#include <numeric>
#include <boost/foreach.hpp>
#include "individual.h"

// definitions
#define sample_size 15
#define string_length 100
#define population_size 25
#define mu 0.005

// constructor
Individual::Individual(int len, int init): bin(len,init), val(10,0), fit(0)
{
//    std::cout << "Individual is being created with string length " << bin.size()/val.size()
//              << " and dimension " << val.size() << "." << std::endl;

}

// unitation operation
void Individual::unitation()
{
    int i = 0;
    for(int a = 0; a<=90; a+=10){
        val[i] = std::accumulate(bin.begin()+int(a),bin.begin()+int(10+a),0);
        i++;
    }

}

// mutation
void Individual::mutate()
{
    for(int j=0; j<bin.size(); j++){
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if(r<0.005){
            if(bin[j]==0)
                bin[j] = 1;
            else
                bin[j] = 0;
        }
    }

    unitation();
}
