//
// Created by jintian on 7/14/17.
//

// this file enables lots of string extend methods

#include "t_string.h"

using namespace std;


void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);

    if (pos2 > s.size()){
        // indicates delimiter not in this string
        // return this string as vector
        v.push_back(s);
    } else {
        pos1 = 0;
        while(std::string::npos != pos2)
        {
            v.push_back(s.substr(pos1, pos2-pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if(pos1 != s.length()) {
            v.push_back(s.substr(pos1));
        }
    }
}