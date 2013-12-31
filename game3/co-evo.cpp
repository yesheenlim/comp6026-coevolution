
// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "population.h"

// namespaces

// global variables
// set up file write
std::ofstream ave_A;
std::ofstream ave_B;
std::ofstream sub_A;
std::ofstream sub_B;

// typedefs

// definitions
#define sample_size 15
#define string_length 100
#define population_size 25
#define mu 0.005

// execute an iteration
void execute(boost::shared_ptr<Population> A, boost::shared_ptr<Population> B){

    // mutate
    A->mutate();
    B->mutate();
    //    for(int i=0; i<A->data.size(); i++){
    //        for(int j=0; j<A->data[i].val.size(); j++)
    //            std::cout << A->data[i].val[j] << " ";
    //        std::cout << std::endl;
    //    }

    // evaluate fitness
    for(int i=0; i<A->data.size(); i++){
        std::vector<std::vector<int> > S = B->getSample();
        A->score3(i,S);
    }
    //    std::cout << "fitness A..." << A->fitsum() << std::endl;
    for(int i=0; i<B->data.size(); i++){
        std::vector<std::vector<int> > S = A->getSample();
        B->score3(i,S);
    }
    //    std::cout << "fitness B..." << B->fitsum() << std::endl;
    //    std::cout << "average objective..." << A->average_obj() << std::endl;


    // print to file before reproduction
    ave_A << A->average_obj() << "\n";
    ave_B << B->average_obj() << "\n";
    sub_A << A->fitsum() << "\n";
    sub_B << B->fitsum() << "\n";

    // reproduce
    A->roulette();
    B->roulette();
}

// main function
int main(){

    // intialize populations
    boost::shared_ptr<Population> A(new Population(population_size, string_length,0));
    boost::shared_ptr<Population> B(new Population(population_size, string_length,0));

    // seed rand()
    srand(time(0));


    ave_A.open("ave_A.dat");
    ave_B.open("ave_B.dat");
    sub_A.open("sub_A.dat");
    sub_B.open("sub_B.dat");

    // execute co-evolution
    for(int ite=0; ite<600; ite++){
        execute(A,B);

    }

    // close files
    ave_A.close();
    ave_B.close();
    sub_A.close();
    sub_B.close();
}
