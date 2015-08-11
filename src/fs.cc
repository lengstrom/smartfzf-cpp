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

vector<const path*> sorted_dir_contents(const path *dir_path) {
    /* 
     * Possible issues:
     * Permissions - unable to read into directory (Does this actually happen???)
     * File/directory doesn't exist - what should this return in that case?
     */

    // For now use naive implementation assuming no errors occur
    // Research done: try catch blocks have 0 performance hit (unless there's an exception, obv)
    vector<const path*> contents;
    directory_iterator end_itr; // default constructor = object past end
    for (directory_iterator itr(*dir_path); itr != end_itr; itr++) {
        const path curr_file = itr->path();
        contents.push_back(&curr_file);
    }

    std::sort(contents.begin(), contents.end());
    for (vector<const path*>::iterator iterator = contents.begin(); iterator != contents.end(); iterator++) {
        std::cout << (*iterator)->string() << std::endl;
    }
    return contents;
}

bool check_for_project(const Path_Node *dir_node) {
    // assume that dir_path is a directory
    vector<const path*> contents = dir_node->contents;
    for (auto itr : contents) {
        string file_name = itr->filename().string();
        for (int i = 0; i < PROJECT_MARKERS_SIZE; i++) {
            if (PROJECT_MARKERS[i] == file_name) {
                return true;
            }
        }
    }

    return true;
}

// recursively copy dir contents
vector<const path*> recursive_sorted_contents(const path *dir_path) {
    vector<const path*> appended_contents;
    vector<const path*> sorted_contents;

    directory_iterator end_itr;
    for (directory_iterator itr(*dir_path); itr != end_itr; itr++) {
        const path curr_path = itr->path();
        if (is_directory(itr->status())) {
            vector<const path*> curr_contents = recursive_sorted_contents(&curr_path);
            vector<const path*> tmp;
            tmp.reserve(sorted_contents.size() + curr_contents.size());
            std::merge(curr_contents.begin(), curr_contents.end(),
                       sorted_contents.begin(), sorted_contents.end(),
                       tmp.begin());
            sorted_contents.swap(tmp);
        } else {
            appended_contents.push_back(&curr_path);
        }
    }

    std::sort(appended_contents.begin(), sorted_contents.end());
    vector<const path*> final_sorted;
    final_sorted.reserve(appended_contents.size() + sorted_contents.size());
    std::merge(appended_contents.begin(), appended_contents.end(),
               sorted_contents.begin(), sorted_contents.end(),
               final_sorted.begin());

    return final_sorted;
}
