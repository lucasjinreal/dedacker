//
// Created by jintian on 7/14/17.
//

#ifndef _T_OS_H
#define _T_OS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace t_os{

    bool exists(char *path);
    bool isdir(char *path);
    bool isfile(char *path);

    vector<string> listdir(char *path);
    string joinpath(char *path, string filename);

}

#endif //_OS_H
