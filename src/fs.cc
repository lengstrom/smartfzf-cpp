#include <vector>
#include <algorithm>
#include "fs.h"
#include <string>
#include <map>
#include <iostream>
#include "boost/filesystem.hpp"

using std::vector;
using std::string;
using namespace boost::filesystem;

const string PROJECT_MARKERS[2] = {".git", ".svn"};
const int PROJECT_MARKERS_SIZE = 2;

vector<path> sorted_dir_contents(path &dir_path) {
    /* 
     * Possible issues:
     * Permissions - unable to read into directory (Does this actually happen???)
     * File/directory doesn't exist - what should this return in that case?
     */

    // For now use naive implementation assuming no errors occur
    // Research done: try catch blocks have 0 performance hit (unless there's an exception, obv)
    // dir_path has type const path
    vector<path> contents;
    directory_iterator end_itr; // default constructor = object past end
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        path curr_file = (*itr).path();
        contents.push_back(curr_file);
    }
   
    return contents;
}

bool check_for_project(vector<path> &contents) {
    // assume that dir_path is a directory
    for (auto itr : contents) {
        string file_name = itr.filename().string();
        for (int i = 0; i < PROJECT_MARKERS_SIZE; i++) {
            if (PROJECT_MARKERS[i] == file_name) {
                return true;
            }
        }
    }

    return false;
}

// recursively copy dir contents
vector<path> recursive_sorted_contents(path &dir_path) {
    std::cout << dir_path << std::endl;
    vector<path> appended_contents;
    vector<path> sorted_contents;

    directory_iterator end_itr;
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        path curr_path = itr->path();
        if (is_directory(itr->status())) {
            vector<path> curr_contents = recursive_sorted_contents(curr_path);
            vector<path> tmp;
            tmp.reserve(sorted_contents.size() + curr_contents.size());
            std::merge(curr_contents.begin(), curr_contents.end(),
                       sorted_contents.begin(), sorted_contents.end(),
                       tmp.begin());
            sorted_contents.swap(tmp);
        } else {
            appended_contents.push_back(curr_path);
        }
    }
    
    std::cout << dir_path << std::endl;
    for (auto i : appended_contents) {
        std::cout << i << std::endl;
    }
    std::sort(appended_contents.begin(), sorted_contents.end());

    vector<path> final_sorted;
    final_sorted.reserve(appended_contents.size() + sorted_contents.size());
    std::merge(appended_contents.begin(), appended_contents.end(),
               sorted_contents.begin(), sorted_contents.end(),
               final_sorted.begin());

    return final_sorted;
}
