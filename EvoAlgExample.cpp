//
//  main.cpp
//  EvoAlg_Example
//
//  Created by Logan Yliniemi on 3/6/17.
//  Copyright © 2017 Logan Yliniemi. All rights reserved.
//

#include <iostream>
#include <random>
#include <time.h>
#include <assert.h>

#define LYRAND (double)rand()/RAND_MAX
#define PI 3.1415296

using namespace std;

class policy{
public:
    double R;
    double H;
    double volume;
    double calc_volume();
    double SA;
    double calc_SA();
    void init(double min, double max);
    void eval();
    double fitness;
    void mutate();
};

void policy::eval(){
    volume = calc_volume();
    SA = calc_SA();
    if(volume > 0.5){
        fitness = SA;
    }
    else if(volume <= 0.5){
        fitness = SA + 10000;
    }
}

void policy::mutate(){
    if(rand()%2){
        H = H + LYRAND - LYRAND;
    }
    else{
        H = H + LYRAND*0.1 - LYRAND*0.1;
    }
    
    if(rand()%2){
        R = R + LYRAND - LYRAND;
    }
    else{
        R = R + LYRAND*0.1 - LYRAND*0.1;
    }
    
    if (H<0){
        H = 0;
    }
    if (R<0){
        R = 0;
    }
}

void policy::init(double min, double max){
    R = LYRAND*max+min;
    H = LYRAND*max+min;
    volume = calc_volume();
    SA = calc_SA();
}

double policy::calc_volume(){
    double v;
    v = PI * R * R * H;
    return v;
}

double policy::calc_SA(){
    double s;
    s = 2 * PI * R * R + 2 * PI * R * H;
    return s;
}

vector<policy> EA_init(int num, double min, double max){
    vector<policy> population;
    
    for(int i=0; i<num; i++){
        policy A;
        A.init(min,max);
        population.push_back(A);
    }
    
    return population;
}

vector<policy> EA_replicate(vector<policy> P,int pop_size){
    vector<policy> population;
    population = P;
    
    while(population.size()<pop_size){
        int spot = rand()%population.size();
        policy A;
        A = population.at(spot);
        A.mutate();
        population.push_back(A);
    }
    
    return population;
}

int EA_main(int argc, const char * argv[]) {
    // hello world to start the program.
    std::cout << "Hello, World!\n";
    
    // initialize random number generator
    srand((unsigned)time(NULL));
    
    /// vector of objects that are of type policy
    vector<policy> pop;
    
    /// min and max height, width to initialize our policies to
    double i_min_dim = 2;
    double i_max_dim = 12;
    
    /// total number of individual policies we will make in our vector (carrying capacity)
    int pop_size = 10;
    
    /// create a vector of policies, and return that to pop.
    pop = EA_init(pop_size/2, i_min_dim, i_max_dim); /// I
    
    /// pop should now be size pop_size/2.
    assert(pop.size() == pop_size/2);
    
    /// check to see that every policy in pop meets our expectations for initial dimensions
    for(int i=0; i<pop.size(); i++){
        assert(pop.at(i).H>i_min_dim);
        assert(pop.at(i).H<i_max_dim);
        assert(pop.at(i).R>i_min_dim);
        assert(pop.at(i).R<i_max_dim);
    }
    
    /// number of generation loops to do
    int max_generations = 3;
    
    /// generation loop
    for(int generation = 0; generation < max_generations; generation++){
        /// bgn generation loop
        pop = EA_replicate(pop,pop_size); /// R
        assert(pop.size() == pop_size);
        /// lines below here to be completed on lecture Thursday March 9
        //EA_evaluate(); /// E
        //EA_downselect(); /// D
    } // end generation loop
    
    cout << "end" << endl;
    
    return 0;
}
