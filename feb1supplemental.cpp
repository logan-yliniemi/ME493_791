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
    
    vector<dog> C;
    
    cout << C.size() << endl;
    
    C.clear();
    int num_cats = 10;
    for(int i=0; i<num_cats; i++){
        dog temp_c;
        temp_c.age = i*2;
        C.push_back(temp_c);
        cout << i << "\t" << C.size() << endl;
    }
    /// here be num_cats cats.
    cout << C.size() << endl;
    assert(C.size() == num_cats);
    
    vector<dog>* pC = &C;
    
    fxn_1(pC);
    
    for(int i=0; i<C.size(); i++){
        cout << C.at(i).age << "\t";
    }
    cout << endl;
}










