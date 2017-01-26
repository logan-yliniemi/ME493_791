//
//  main.cpp
//  ME493_1
//
//  Created by Logan Yliniemi on 1/26/17.
//  Copyright © 2017 Logan Yliniemi. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <string.h>
#include <random>
#include <time.h>

#define LYRAND (double)rand()/RAND_MAX

using namespace std;

class cat{
public:
    double evilness = LYRAND; // number in [0,1] that determines the cat's reaction to being pet. 1 is totally evil.
    int age; // days
    int lives; // lives
    double happiness; // number in [0,1]
    double weight; // number in kg
    
    string breed;
    string gender;
    
    void init();
    void litterbox();
    void meow();
    void eat();
    void sleep();
};

void cat::init(){
    age = 365 + rand()%365; /// mod (%) is remainder
    lives = 9;
    happiness = 0.5 + LYRAND/2;
    weight = 7.0 + LYRAND*3;
}

void cat::eat(){
    weight += .5;
}

void cat::sleep(){
    age++;
}

void pet(cat* pC){
    double reaction = LYRAND;
    if(reaction > pC->evilness){
        /// good things happen
        pC->happiness += LYRAND/10;
    }
    else if(reaction <= pC->evilness){
        /// bad things happen
        pC->happiness = pC->happiness - LYRAND/10;
    }
    else{
        assert(1==0);
    }
}

void pet_all(vector<cat>* pclowder){
    for(int i = 0; i<pclowder->size(); i++){
        double reaction = LYRAND;
        if(reaction > pclowder->at(i).evilness){
            /// good things happen
            pclowder->at(i).happiness += LYRAND/10;
        }
        else if(reaction <= pclowder->at(i).evilness){
            /// bad things happen
            pclowder->at(i).happiness = pclowder->at(i).happiness - LYRAND/10;
        }
        else{
            assert(1==0);
        }
    }
}

void add_one(int c){
    cout << "inside function, before: " << c << endl;
    c = c + 1;
    cout << "inside function, after: " << c << endl;
}

void add_one_ptr(int* pc){
    *pc += 1;
}

int main() {
    srand(time(NULL));
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //assert(1==0); /// test driven development
    
    int a;
    a = 4;
    
    assert(a == 4);
    
    a = a + 1;
    
    assert(a == 5);
    
    a += 1;
    
    assert(a == 6);
    
    a++;
    
    assert(a == 7);
    
    double b;
    b = (double)a/10;
    
    cout << b << std::endl;
    
    assert(b == .7);
    
    
    int c;
    c=4;
    
    cout << "outside function, before: " << c << endl;
    
    add_one(c);
    
    cout << "outside function, after: " << c << endl;
    
    //assert(c==5);
    
    int* pc = &c;
    add_one_ptr(pc);
    
    cout << &c << endl;
    
    assert(c==5);
    
    
    cout << "CAT SECTION " << endl;
    cat Garfield;
    cat* pGarfield = &Garfield;
    cat Garfield_clone;
    Garfield.init();
    
    Garfield_clone = Garfield;
    
    cout << "Garfield before " << Garfield.weight << endl;
    Garfield.eat();
    cout <<  "Garfield after " <<  Garfield.weight << endl;
    cout <<  "Garfield clone " << Garfield_clone.weight << endl;
    
    cout << "Garfield's Hapiness Before\t" << Garfield.happiness << endl;
    pet(pGarfield);
    cout << "Garfield's Hapiness After\t" << Garfield.happiness << endl;
    
    vector<int> V;
    for(int i=0; i<10; i++){
        V.push_back(i);
        for(int j=0; j<V.size(); j++){
            cout << V.at(j) << "\t";
        }
        cout << endl;
    }
    
    vector<cat> clowder;
    vector<cat>* pclowder = &clowder;
    
    for(int i=0; i<5; i++){
        cat C;
        C.init();
        clowder.push_back(C);
    }
    
    pet_all(pclowder);
    
    assert(clowder.size() == 5);
    
    return 0;
}













