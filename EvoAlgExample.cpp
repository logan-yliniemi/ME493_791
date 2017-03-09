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
#include <algorithm>

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
    R = LYRAND*(max-min)+min;
    H = LYRAND*(max-min)+min;
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
    
    assert(population.size() == pop_size/2);
    
    while(population.size()<pop_size){
        int spot = rand()%population.size();
        policy A;
        A = population.at(spot);
        A.mutate();
        //test_mututation(population.at(spot),A);
        population.push_back(A);
    }
    
    assert(population.size() == pop_size);
    
    return population;
}

vector<policy> EA_evaluate(vector<policy> P, int pop_size){
    vector<policy> population;
    population = P;
    for(int testing=0; testing<population.size(); testing++){
        population.at(testing).fitness = -1;
    }
    
    /// assign fitness
    for(int i=0; i<population.size(); i++){
        population.at(i).eval();
        assert(population.at(i).fitness != -1);
    }
    
    for(int testing=0; testing<population.size(); testing++){
        assert(population.at(testing).fitness != -1);
    }
    assert(population.size() == pop_size);
    return population;
}

vector<policy> EA_downselect(vector<policy> P, int pop_size){
    vector<policy> population;
    /// population is empty
    assert(population.size() == 0);
    assert(P.size() == pop_size);
    
    bool binarytournament = false;
    bool strict = true;
    
    if(strict){
        /// select the top half, only.
        vector<double> fits;
        for(int i=0; i<P.size(); i++){
            fits.push_back(P.at(i).fitness);
        }
        sort(fits.begin(),fits.end());
        //cout << fits.at(0) << "\t" << fits.back() << endl;
        double survivorline = fits.at(pop_size/2);
        for(int i=P.size(); i>0; i--){
            if(P.at(i).fitness > survivorline){
                P.erase(P.begin()+i);
            }
        }
    }
    
    
    if(binarytournament){
        /// remove half by binary tournament
        while(population.size() < pop_size / 2){
            /// choose 2 at random
            int spot1 = rand()%P.size();
            int spot2 = rand()%P.size();
            while(spot2 == spot1){
                spot2 = rand()%P.size();
            }
            assert(spot1!=spot2);
            double fit1 = P.at(spot1).fitness;
            double fit2 = P.at(spot2).fitness;
            
            if(fit1<fit2){
                //// fit1 wins
                //  copy fit1 into "population"
                policy A1 = P.at(spot1);
                population.push_back(A1);
            }
            else if(fit2<=fit1){
                //// fit2 wins
                // copy fit2 into "population"
                policy A2 = P.at(spot2);
                population.push_back(A2);
            }
        }
    }
    
    assert(population.size() == pop_size/2);
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
    double i_min_dim = 0.01;
    double i_max_dim = 0.1;
    
    /// total number of individual policies we will make in our vector (carrying capacity)
    int pop_size = 100;
    
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
    int max_generations = 300;
    
    /// generation loop
    for(int generation = 0; generation < max_generations; generation++){
        /// bgn generation loop
        pop = EA_replicate(pop,pop_size); /// R
        assert(pop.size() == pop_size);
        /// lines below here to be completed on lecture Thursday March 9
        pop = EA_evaluate(pop,pop_size); /// E
        assert(pop.size() == pop_size);
        pop = EA_downselect(pop,pop_size); /// D
        assert(pop.size() == pop_size/2);
    } // end generation loop
    
    
    for(int i=0; i<pop.size(); i++){
        cout << "R= " << pop.at(i).R << "\t";
        cout << "H= " << pop.at(i).H << "\t";
        cout << "V= " << pop.at(i).volume << "\t";
        cout << "fit= " << pop.at(i).fitness << "\t";
        cout << endl;
    }
    
    
    cout << "end" << endl;
    
    return 0;
}
