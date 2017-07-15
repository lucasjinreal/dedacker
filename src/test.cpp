//
// Created by jintian on 7/15/17.
//
#include <iostream>
#include <string>


using namespace std;


void test(){
    cout << "hello" <<endl;

    string a = "this is a test";

    string::size_type  sz;
    sz = a.find("6h");
    cout << sz << endl;
    cout << a.size() << endl;
}

