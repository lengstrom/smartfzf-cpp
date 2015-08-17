#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

#include <boost/filesystem.hpp>

#include "fs.h"

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

bool is_project(vector<path> &contents) {
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
    vector<path> appended_contents, all_subdir_contents;
    vector<int> insert_indices;
    int all_subdirs_size = 0;
    int appended_contents_size = 0;
    directory_iterator end_itr;
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        path curr_path = itr->path();
        std::cout << curr_path.filename().string()[0] << std::endl;

        // take out hidden files
        if (curr_path.filename().string()[0] == '.') {
            continue;
        }

        if (is_directory(itr->status())) {
            vector<path> dir_contents = recursive_sorted_contents(curr_path);
            if (dir_contents.size() > 0) {
                all_subdirs_size += dir_contents.size();
                insert_indices.push_back(all_subdirs_size);
                all_subdir_contents.insert(all_subdir_contents.end(), dir_contents.begin(), dir_contents.end());
            }
        } else {
            appended_contents.push_back(curr_path);
            appended_contents_size++;
        }
    }

    if (all_subdirs_size == 0) { // nothing in all_subdir_contents
        return appended_contents;
    }

    if (insert_indices.size() > 1) { // one presorted thing in all_subdir_contents
        vector<path>::iterator last_itr = all_subdir_contents.begin();
        vector<path>::iterator scnd_last_itr = last_itr + insert_indices[0];
        for (vector<int>::iterator itr = insert_indices.begin() + 1; itr != insert_indices.end(); itr++) {
            vector<path>::iterator curr = scnd_last_itr + (*itr);
            std::inplace_merge(last_itr, scnd_last_itr, curr);
            last_itr = scnd_last_itr;
            scnd_last_itr = curr;
        }
    }

    if (appended_contents_size == 0) {
        return all_subdir_contents;
    }

    std::sort(appended_contents.begin(), appended_contents.end());
    appended_contents.insert(appended_contents.end(), all_subdir_contents.begin(), all_subdir_contents.end());
    std::inplace_merge(appended_contents.begin(), appended_contents.begin() + appended_contents_size, appended_contents.end());
    return appended_contents;
}
