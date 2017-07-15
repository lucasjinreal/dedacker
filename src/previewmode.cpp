//
// Created by jintian on 7/15/17.
//
#include "../lib/t_string.h"
#include "../lib/t_os.h"
#include "../lib/colors.h"

#include "opencv2/opencv.hpp"

using namespace t_os;
using namespace colors;

void image_preview_mode(char *argv[]) {
    // load all images under a dir using OpenCV
    auto images_dir = argv[1];

    cout << colors::yellow << "-- image preview mod.\n";
    cout << colors::yellow << "images dir: " << images_dir << colors::reset << endl;

    if (!exists(images_dir)) {
        cout << colors::red << "[BAD] your image dir is not exist.\n" << colors::reset;
        exit(0);
    }

    vector<string> all_files = listdir(images_dir);
    vector<string> all_images;
    for (int i = 0; i < all_files.size(); ++i) {
        vector<string> splitResult;
        SplitString(all_files[i], splitResult, ".");

        if (splitResult.back() == "jpg"){
            all_images.push_back(all_files[i]);
        }
    }

    if (all_images.size() == 0){
        cout << colors::red << "Not find any images under this folder.\n";
        exit(0);
    } else {
        cout << colors::yellow << "Find " << all_images.size() << " images.\n" << colors::reset;
    }

    for (int j = 0; j < all_images.size(); ++j) {
        // this is just a test to show image under an dir
        cv::Mat image;
        image = cv::imread(all_images[j], cv::IMREAD_COLOR);
        if (!image.data){
            cout << colors::red << "This image seems invalid. " << all_images[j] << colors::reset << endl;
        } else {
            cv::namedWindow("image display", cv::WINDOW_AUTOSIZE);
            cv::imshow("image display", image);

            char c = (char) cv::waitKey();
            switch (c){
                case 'q':
                    cv::destroyAllWindows();
                    exit(0);
                default:
                    continue;
            }
        }

    }
}