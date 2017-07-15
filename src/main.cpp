#include <iostream>
#include <string>
#include "../include/motto.h"
#include "../lib/colors.h"
#include "opencv2/opencv.hpp"

#include "../lib/t_os.h"
#include "../lib/t_string.h"

using namespace std;
using namespace t_os;

void image_preview_mode(char *argv[]);
void detection_check_mode(char *argv[]);
void test();



int main(int argc, char *argv[]) {
    cout << colors::red << "dedacker - detection data checker.\n" << colors::reset;
    string motto = getMotto();
    cout << colors::blue << "[motto] " << motto << colors::reset << endl;

    if (argc < 2) {
        throw invalid_argument("at least provide image dir or image dir and label file. for usage: \n"
                                       "./dedacker /path/to/image_dir/ /label/file/label.txt");
    }

    if (argc == 2) {
        image_preview_mode(argv);
    } else if (argc == 3) {
        detection_check_mode(argv);
    }

    return 0;
}