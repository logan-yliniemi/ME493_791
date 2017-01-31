//
//  main.cpp
//  ME493OptimizationInDesign
//
//  Created by Logan Yliniemi on 1/31/17.
//  Copyright © 2017 Logan Yliniemi. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <random>
#include <time.h>

#define LYRAND (double)rand()/RAND_MAX
#define PI 3.1415297

using namespace std;

class solution{
public:
    double fitness;
    double V;
    double R;
    double H;
    double SA;
    
    void init();
    double calc_SA();
    double calc_V();
    bool valid();
    bool manufacturing_test();
    void eval();
    void mutate();
    
};

void solution::mutate(){
    R = R + LYRAND - LYRAND;
    H = H + LYRAND - LYRAND;
    
    if(R<0){R=0;}
    if(H<0){H=0;}
}

void solution::eval(){
    V = calc_V();
    SA = calc_SA();
    fitness = SA;
    if(!valid()){
        fitness = fitness + 100000000;
    }
}

void solution::init(){
    fitness = -1;
    R = 10 + LYRAND;
    H = 10 + LYRAND;
    V = calc_V();
    SA = calc_SA();
}

double solution::calc_SA(){
    double sa;
    sa = 2 * PI * R * R + 2 * PI * R * H;
    return sa;
}

double solution::calc_V(){
    double vol;
    vol = PI * R * R * H;
    return vol;
}

bool solution::valid(){
    bool validity = true;
    if(V < 0.5){
        validity = false;
    }
    
    if(!manufacturing_test()){
        validity = false;
    }
    return validity;
}

bool solution::manufacturing_test(){
    bool passfail = true;
    
    int counter = 0;
    /// virtually manufacture 10000 parts:
    int parts = 10000;
    for(int i=0; i<parts; i++){
        solution surrogate = *this; /// let's create a copy of "this" solution, call it surrogate.
        /// change surrogate's R and H by some value in a distribution around the real R and H.
        surrogate.H = surrogate.H + 0.01*LYRAND - + 0.01*LYRAND;
        surrogate.R = surrogate.R + 0.01*LYRAND - + 0.01*LYRAND;
        surrogate.V = surrogate.calc_V();
        if(surrogate.V>0.5){
            /// if the volume still meets the criteria, add to "counter".
            counter++;
        }
    }
    
    /// if counter is greater than 99% of the number of parts we made, then we passed the QA test, and this is a valid part design.
    if((double)counter > (double)0.99*parts){
        passfail = true;
    }
    else{
        passfail = false;
    }
    
    return passfail;
}

//optimization_
int main() {
    srand(time(NULL));
    
    cout << "PROGRAM IN" << endl;
    
    solution A;
    solution B;
    
    A.init();
    B.init();
    
    int iterations = 10000;
    for(int i=0; i<iterations; i++){
        cout << endl;
        cout << i << "\t";
        
        A.eval();
        B.eval();
        
        if(A.fitness < B.fitness){
            /// A IS BETTER
            cout << "A WINS" << " ";
            B = A;
            B.mutate();
            cout << " SA: " << A.SA;
            cout << " V: " <<A.V;
            cout << " H: " <<A.H;
            cout << " R: " <<A.R;
        }
        else if(B.fitness < A.fitness){
            /// B IS BETTER
            cout << "B WINS";
            A = B;
            A.mutate();
            cout << " SA: " << B.SA;
            cout << " V: " <<B.V;
            cout << " H: " <<B.H;
            cout << " R: " <<B.R;
        }
    }
    
    cout << endl << "PROGRAM OUT" << endl;
    
    return 0;
}
