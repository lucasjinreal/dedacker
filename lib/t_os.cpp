//
// Created by jintian on 7/14/17.
//
// this library provider some function to
// judge a directory is exist or not
#include <sys/types.h>
#include <sys/stat.h>
#include "t_os.h"
#include <iostream>
#include <vector>
#include <dirent.h>


struct stat info;
using namespace std;

bool t_os::exists(char *path) {
    // if path exists, return true else return false
    if (stat(path, &info) != 0) {
        // path not exist
        return false;
    } else {
        // this is a file
        return true;
    }
}

bool t_os::isdir(char *path) {
    // judge is directory or file, if dir return true, if file return false
    if (stat(path, &info) != 0) {
        // path not exist
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // this is a directory
        return true;
    } else {
        return false;
    }

}

bool t_os::isfile(char *path) {
    // return a path is file or not
    if (stat(path, &info) != 0) {
        // path not exist
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // this is a directory
        return false;
    } else {
        return true;
    }
}

vector<string> t_os::listdir(char *path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG) {
            files.push_back(path + string("/") + string(dirP->d_name));
        }
    }

    closedir(dp);
    return files;
}

string t_os::joinpath(char *path, string filename) {
    // path maybe /home/jin/doc1 or /home/jin/doc1/
    // make sure drop the last '/'
    string path_string = string(path);
    string::size_type p;
    p = path_string.find("/");
    if (p < path_string.size()) {
        // if contains "/" then drop it
        path_string.substr(0, path_string.size() - 1);
    }
    string joiner = "/";
#ifdef __WINDOWS_
    joiner = "\\";
#endif

#ifdef _UNIX
    // unix machine
    joiner = "/";
#endif

#ifdef __APPLE__
    joiner = "/";
#endif

    string joined_path = path_string + joiner + filename;
    return joined_path;
}
