//
// Created by jintian on 7/12/17.
//

#include "../include/motto.h"
#include "time.h"
#include "../lib/random.h"

using namespace std;

string getMotto() {
    // this method generate a motto
    vector<string> mottoes;
    mottoes.push_back("fail is the mother of success.");
    mottoes.push_back("every success person must be cute.");
    mottoes.push_back("Ugly is better than beautiful.");
    mottoes.push_back("Word hard never be late.");

    int a = randint(0, 4);
    return mottoes[a];
}
