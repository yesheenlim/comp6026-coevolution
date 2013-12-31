
#include <iostream>
#include <boost/foreach.hpp>
#include "population.h"

// definitions
#define sample_size 1
#define string_length 100
#define population_size 25
#define mu 0.005

// constructor
Population::Population(int sz, int len, int init): data(sz, Individual(len, init))
{
    //    std::cout << "Population of size " << data.size() << " is being created." << std::endl;

}

// roulette wheel selection
void Population::roulette()
{
    std::vector<Individual> temp;

    for(int i=0; i<data.size(); i++){
        int r, j = 0, sum = 0;
        if(fitsum() == 0){
            j = 1;
        }else{
            r = rand()%fitsum();
            //        std::cout << "r is " << r << std::endl;
            while(sum<=r){
                sum += data[j].fit;
                j++;
            }
        }
        //        std::cout << "j-1 is " << j-1 << std::endl;
        //        std::cout << data[j-1].val << std::endl;
        temp.push_back(data[j-1]);
    }
    //        std::cout << "Check" << std::endl;
    //    for(int i=0; i<temp.size(); i++){
    //        std::cout << temp[i].val << std::endl;
    //    }
    //    std::cout << "Swap check" << std::endl;
    data.swap(temp);
    //    for(int i=0; i<data.size(); i++){
    //        for(int j=0; j<100; j++){
    //        std::cout << data[i].bin[j];
    //        }
    //        std::cout << std::endl;
    //    }
}

// mutation
void Population::mutate()
{
    for(int i=0; i<data.size(); i++){
        data[i].mutate();
    }
    //    for(int i=0; i<data.size(); i++){
    //        for(int j=0; j<data[i].bin.size(); j++){
    //            std::cout << data[i].bin[j] << " ";
    //        }
    //        std::cout << std::endl << data[i].val << std::endl;
    //    }
}

// get samples S
std::vector<int> Population::getSample()
{
    std::vector<int> S;
    for(int i=0; i<sample_size; i++){
        int r = rand()%(population_size-1);
        S.push_back(data[r].val);
        //        std::cout << "in getsample " << r << " and " << S[i] << std::endl;
    }

    return S;
}

// evaluate fitness 1
void Population::score1(int i, std::vector<int> S)
{
    //    std::cout << "Samples are " << std::endl;
    //    for(int m=0; m<S.size(); m++){
    //        std::cout << S[m] << std::endl;
    //    }
    //    std::cout << "Value is " << data[i].val << std::endl;
    int tmp=0;
    for(int j=0; j<S.size(); j++){
        if(data[i].val>S[j])
            tmp++;
    }
    data[i].fit = tmp;
    //    std::cout << "Fitness is " << data[i].fit << std::endl;
}

// returns total fitness of population
int Population::fitsum()
{
    int sum = 0;
    for(int i=0; i<data.size(); i++){
        sum += data[i].fit;
    }

    return sum;
}

// returns average objective fitness
int Population::average_obj()
{
    int sum = 0;
    for(int i=0; i<data.size(); i++)
        sum += data[i].val;

    return (int)(sum/data.size());
}

// penalize fit individuals
void Population::penalize()
{
    std::vector<int> tmp;

    for(int i=0; i<10; i++){
        int r, j = 0, sum = 0;
        if(fitsum() == 0){
            j = 1;
        }else{
            r = rand()%fitsum();
            //        std::cout << "r is " << r << std::endl;
            while(sum<=r){
                sum += data[j].fit;
                j++;
            }
        }

        tmp.push_back(j-1);
    }
    for(int i=0; i<tmp.size(); i++){
        data[i].mutate();
    }

}
