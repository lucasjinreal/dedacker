//
// Created by jintian on 7/12/17.
//

// provide multi random value

#include <cstdlib>
#include <stdexcept>
#include "time.h"

using namespace std;

int randint(int a, int b){

    if (a >= b){
        throw std::invalid_argument("randint argument a must less than b.");
    }
    srand((unsigned) time(NULL));
    return a + rand() % (a + b -1);
}

float randnorm(){
    // return a float value random in 0-1
    return rand();
}