//
// Created by jintian on 7/15/17.
//

#include "../lib/t_string.h"
#include "../lib/colors.h"
#include "../lib/t_os.h"

#include "opencv2/opencv.hpp"

#include <map>
#include <istream>
#include <iostream>
#include <fstream>

using namespace t_os;
using namespace colors;
using namespace std;
using namespace cv;

// bounding box struct, can be manipulate
struct BoundingBox {
    int class_index;
    string class_name;
    double x1;
    double y1;
    double x2;
    double y2;
};

map<string, vector<BoundingBox> > loadLabelFileText(char *path);
map<string, vector<BoundingBox> > loadLabelFileJson(char *path);
void drawBoundingBoxOnImage(cv::Mat &image, struct BoundingBox &bbox);


void detection_check_mode(char *argv[]) {
    auto images_dir = argv[1];
    auto label_file = argv[2];

    cout << colors::yellow << "-- detection check mode.\n";
    cout << colors::yellow << "images dir: " << images_dir << colors::reset << endl;
    cout << colors::yellow << "label file: " << label_file << colors::reset << endl;

    if (!exists(images_dir) && !isdir(images_dir)) {
        cout << colors::red << "[BAD] your image dir is not exist or not directory.\n" << colors::reset;
        exit(0);
    }
    if (!isfile(label_file)) {
        cout << colors::red << "[BAD] your label file is not a file or not exist.\n" << colors::reset;
        exit(0);
    }

    // Now reading label file, this will load a map, key is image path and value is vector<BoundingBox>
    map<string, vector<BoundingBox> > image_box_map = loadLabelFileText(label_file);
    cout << colors::green << "got all " << image_box_map.size() << " images labeled.\n";

    map<string, vector<BoundingBox> >::iterator it;
    for (it = image_box_map.begin(); it != image_box_map.end(); ++it) {
        string image_name = it->first;
        string image_path = joinpath(images_dir, image_name);
        cout << colors::reset << "[solving image]: " << image_path << endl;

        // &image_path[0u] converts string to char*
        if (exists(&image_path[0u])) {
            vector<BoundingBox> current_image_boxes = it->second;

            cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
            if (!image.data == 0){
                // iterate vector to draw a box on image

                for (auto it = current_image_boxes.begin(); it != current_image_boxes.end(); ++it) {
                    BoundingBox current_box = *it;
                    drawBoundingBoxOnImage(image, current_box);
                    cout << colors::cyan << "class_index: " << current_box.class_index
                         << " x1: " << current_box.x1
                         << " y1: " << current_box.y1
                         << " x2: " << current_box.x2
                         << " y2: " << current_box.y2 << endl;
                }

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
            } else {
                cout << colors::red << "[BAD] load image failed: " << image_path << endl;
            }
        } else {
            cout << colors::red << "[BAD] this image not exist: " << image_path << endl;
        }
    }
}

map<string, vector<BoundingBox> > loadLabelFileJson(char *path) {
    // load json format label file, return a map, the key is image path
    // value is the vector contains bounding boxes


}

map<string, vector<BoundingBox> > loadLabelFileText(char *path) {
    // load json format label file, return a map, the key is image path
    // value is the vector contains bounding boxes
    // TODO: this function can be changed into different question
    // text format: image_name.jpg 1 90 45 67 234
    ifstream infile(path);
    string line;

    map<string, vector<BoundingBox> > image_box_map;

    while (infile.good()) {
        getline(infile, line);

        vector<string> line_split;
        if (line == ""){
            break;
        }
        SplitString(line, line_split, " ");

        string image_name = line_split[0];
        int class_index = stoi(line_split[1], nullptr, 0);

        string::size_type sz;
        double x1 = stod(line_split[2], &sz);
        double y1 = stod(line_split[3], &sz);
        double x2 = stod(line_split[4], &sz);
        double y2 = stod(line_split[5], &sz);

        BoundingBox bbox;
        bbox.class_index = class_index;
        bbox.x1 = x1;
        bbox.y1 = y1;
        bbox.x2 = x2;
        bbox.y2 = y2;

        map<string, vector<BoundingBox> >::iterator it = image_box_map.find(image_name);
        if (it == image_box_map.end()) {
            // image_name not in map, new a key-value pair
            vector<BoundingBox> bbox_vector;
            bbox_vector.push_back(bbox);
            image_box_map.insert( pair<string, vector<BoundingBox>>(image_name, bbox_vector) );
        } else {
            // if image_name already in map, find this key value push_back into vector
            vector<BoundingBox> current_image_bboxes = image_box_map[image_name];
            current_image_bboxes.push_back(bbox);
            image_box_map[image_name] = current_image_bboxes;
        }
    }
    return image_box_map;
}


void drawBoundingBoxOnImage(cv::Mat &image, struct BoundingBox &bbox) {
    if (!image.data) {
        cout << colors::red << "[BAD] image seems not valid. " << colors::reset << endl;
    } else {

        // draw an box on this image
        int font_face = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double font_scale = 1.5;
        int thickness = 3;

        cv::Point text_origin = cv::Point(bbox.x1, bbox.y1);
        cv::Rect bbox_rect = cv::Rect(bbox.x1, bbox.y1, bbox.x2, bbox.y2);

        cv::putText(image, bbox.class_name, text_origin,
                    font_face, font_scale, cv::Scalar(0, 0, 0), thickness, 8);

        cv::rectangle(image, bbox_rect, Scalar(0, 255, 0), 2, 8, 0);
    }
}

