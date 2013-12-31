
#include <iostream>
#include <cmath>
#include <numeric>
#include <boost/foreach.hpp>
#include "population.h"

// definitions
#define sample_size 15
#define string_length 100
#define population_size 25
#define mu 0.005

// constructor
Population::Population(int sz, int len, int init): data(sz, Individual(len, init))
{
//    std::cout << "Population of size " << data.size() << " is being created." << std::endl;

}

// mutation
void Population::mutate()
{
    for(int i=0; i<data.size(); i++){
        data[i].mutate();
        //        for(int j=0; j<data[i].bin.size(); j++)
        //            std::cout << data[i].bin[j];
        //        std::cout << std::endl;

        //        for(int j=0; j<data[i].val.size(); j++)
        //            std::cout << data[i].val[j] << " ";
        //        std::cout << std::endl;
    }
}

// get samples S
std::vector<std::vector<int> > Population::getSample()
{
    std::vector<std::vector<int> > S;
    std::vector<int> tmp;

    // make sure same individual not drawn twice
    tmp.push_back(rand()%(population_size-1));
    while(tmp.size()<sample_size){
        int r = rand()%(population_size-1), count = 0;
        for(int m=0; m<tmp.size(); m++){
            if(r==tmp[m])
                count++;
        }
        if(count==0)
            tmp.push_back(r);
    }


    for(int i=0; i<tmp.size(); i++){
        S.push_back(data[tmp[i]].val);
    }

    return S;
}

// compute subjective fitness 2
void Population::score2(int i, std::vector<std::vector<int> > S){

//    std::cout << "checking competitions..." << std::endl;

//    for(int k=0; k<S.size(); k++){
//        for(int j=0; j<S[k].size(); j++){
//            std::cout << S[k][j] << " ";
//        }
//        std::cout << std::endl;
//    }

//    std::cout << "my_value is..." << std::endl;
//    for(int j=0; j<data[i].val.size(); j++){
//        std::cout << data[i].val[j] << " ";
//    }
//    std::cout << std::endl;

    int tmp = 0;
//    std::cout << "play in dimension..." << std::endl;
    for(int d=0; d<S.size(); d++){
        int max = 0, maxv = abs(data[i].val[0]- S[d][0]);
        for(int j=1; j<data[i].val.size(); j++){
            if(abs(data[i].val[j]- S[d][j]) > maxv){
                max = j;
                maxv = abs(data[i].val[j]- S[d][j]);
            }
        }
//        std::cout << max << " ";
        if(data[i].val[max] > S[d][max])
            tmp++;
    }
//    std::cout << std::endl;
//    std::cout << "fitness is... " << tmp << std::endl;

    data[i].fit = tmp;
}

// compute subjective fitness 3
void Population::score3(int i, std::vector<std::vector<int> > S){

//    std::cout << "checking competitions..." << std::endl;

//    for(int k=0; k<S.size(); k++){
//        for(int j=0; j<S[k].size(); j++){
//            std::cout << S[k][j] << " ";
//        }
//        std::cout << std::endl;
//    }

//    std::cout << "my_value is..." << std::endl;
//    for(int j=0; j<data[i].val.size(); j++){
//        std::cout << data[i].val[j] << " ";
//    }
//    std::cout << std::endl;

    int tmp = 0;
//    std::cout << "play in dimension..." << std::endl;
    for(int d=0; d<S.size(); d++){
        int min = 0, minv = abs(data[i].val[0]- S[d][0]);
        for(int j=1; j<data[i].val.size(); j++){
            if(abs(data[i].val[j]- S[d][j]) < minv){
                min = j;
                minv = abs(data[i].val[j]- S[d][j]);
            }
        }
//        std::cout << min << " ";
        if(data[i].val[min] > S[d][min])
            tmp++;
    }
//    std::cout << std::endl;
//    std::cout << "fitness is... " << tmp << std::endl;

    data[i].fit = tmp;
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
    std::vector<int> vsum;

    for(int i=0; i<data.size(); i++){
        int tmp=0;
        for(int j=0; j<data[i].val.size(); j++){
            tmp += data[i].val[j];
        }
//        std::cout << tmp << " ";
        vsum.push_back(tmp);
    }
//    std::cout << std::endl;

    return std::accumulate(vsum.begin(), vsum.end(), 0)/population_size;
}

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
