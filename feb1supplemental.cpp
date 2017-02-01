//
//  feb1supplemental.cpp
//  ME493_1
//
//  Created by Logan Yliniemi on 2/1/17.
//  Copyright © 2017 Logan Yliniemi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <random>

using namespace std;

class dog{
public:
    int age;
};

void fxn_1(vector<dog>* pD){
    pD->at(200).age += 50;
}

//feb1supplemental_
int main(){
    srand(time(NULL));
    
    vector<dog> D;
    
    cout << D.size() << endl;
    
    D.clear();
    int num_dogs = 10;
    for(int i=0; i<num_dogs; i++){
        dog temp_d;
        temp_d.age = i*2;
        D.push_back(temp_d);
        cout << i << "\t" << D.size() << endl;
    }
    /// here be num_dogs dogs.
    cout << D.size() << endl;
    assert(D.size() == num_dogs);
    
    vector<dog>* pD = &D;
    
    fxn_1(pD);
    
    for(int i=0; i<D.size(); i++){
        cout << D.at(i).age << "\t";
    }
    cout << endl;
}










