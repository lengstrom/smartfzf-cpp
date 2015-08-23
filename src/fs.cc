#include <vector>
#include <stdexcept>
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

vector<string> sorted_dir_contents(path &dir_path) {
    /* 
     * Possible issues:
     * Permissions - unable to read into directory (Does this actually happen???)
     * File/directory doesn't exist - what should this return in that case?
     */

    // For now use naive implementation assuming no errors occur
    // Research done: try catch blocks have 0 performance hit (unless there's an exception, obv)
    // dir_path has type const path
    vector<string> contents;
    directory_iterator end_itr; // default constructor = object past end
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        path curr_file = (*itr).path();
        contents.push_back(curr_file.filename().string());
    }
   
    return contents;
}

bool is_project(vector<string> &contents) {
    // assume that dir_path is a directory
    for (auto itr : contents) {
        for (int i = 0; i < PROJECT_MARKERS_SIZE; i++) {
            if (PROJECT_MARKERS[i] == itr) {
                return true;
            }
        }
    }

    return false;
}

// recursively copy dir contents
vector<string> recursive_sorted_contents(path &dir_path) {
    vector<string> appended_contents, all_subdir_contents;
    vector<int> insert_indices;
    int all_subdirs_size = 0;
    int appended_contents_size = 0;
    directory_iterator end_itr;
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        path curr_path = itr->path();
        string curr_basename = curr_path.filename().string();
        // take out hidden files
        if (curr_basename[0] == '.') {
            continue;
        }

        if (is_directory(itr->status())) {
            vector<string> dir_contents = recursive_sorted_contents(curr_path);
            if (dir_contents.size() > 0) {
                all_subdirs_size += dir_contents.size();
                insert_indices.push_back(all_subdirs_size);
                all_subdir_contents.insert(all_subdir_contents.end(), dir_contents.begin(), dir_contents.end());
            }
        } else {
            appended_contents.push_back(curr_path.string());
            appended_contents_size++;
        }
    }

    if (all_subdirs_size == 0) { // nothing in all_subdir_contents
        return appended_contents;
    }

    if (insert_indices.size() > 1) { // one presorted thing in all_subdir_contents
        vector<string>::iterator last_itr = all_subdir_contents.begin();
        vector<string>::iterator scnd_last_itr = last_itr + insert_indices[0];
        for (vector<int>::iterator itr = insert_indices.begin() + 1; itr != insert_indices.end(); itr++) {
            vector<string>::iterator curr = scnd_last_itr + (*itr);
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

std::vector<std::string> dir_components(const std::string &input, const path &base, bool &err ) {
    std::vector<std::string> components;
    path input_path(input);
    boost::system::error_code ec;
    path normalized_in_path = canonical(input_path, base, ec);
    if (ec.value() == boost::system::errc::success) {
        path::iterator itr_end = normalized_in_path.end();
        if (!is_directory(normalized_in_path)) {
            itr_end--;
        }

        for (path::iterator itr = normalized_in_path.begin(); itr != itr_end; itr++) {
            string curr_file  = (*itr).filename().string();
            components.push_back(curr_file);
        }
    } else {
        err = true;
    }

    return components;
}
