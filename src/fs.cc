#include <vector>
#include <algorithm>
#include "fs.h"
#include "boost/filesystem.hpp"

using std::vector;
using namespace boost::filesystem;

vector<path*> sorted_dir_contents(const path &dir_path) {
    /* 
     * Possible issues:
     * Permissions - unable to read into directory (Does this actually happen???)
     * File/directory doesn't exist - what should this return in that case?
     */

    // For now use naive implementation assuming no errors occur
    // Research done: try catch blocks have 0 performance hit (unless there's an exception, obv)
    vector<path*> contents;
    directory_iterator end_itr; // default constructor = object past end
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        contents.push_back(&(itr->path()));
    }

    std::sort(contents.begin(), contents.end());
    return contents;
}

// recursively copy dir contents
vector<path> recursive_sorted_dir_contents(const path &dir_path) {
    vector<path*> appended_contents;
    vector<path*> sorted_contents;

    directory_iterator end_itr;
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        path * curr_path = &(itr->path()); // Must be a better way of doing this
        if (is_directory(itr->status())) {
            // way of concatenating vectors without copying objects??
            vector<path*> curr_contents = recursive_sorted_dir_contents(curr_path);
            // merge curr_contents into sorted_contents
            vector<path*> tmp;
            tmp.reserve(sorted_contents.size() + curr_contents.size());

            std::merge(curr_contents.begin(), curr_contents.end(),
                       sorted_contents.begin(), sorted_contents.end(),
                       std::back_inserter(tmp));
        } else {
            appended_contents.push_back(curr_path);
        }
    }

    std::sort(appended_contents.begin(), sorted_coments.end());

    vector<path*> final_sorted;
    std::merge(appended_contents.begin(), appended_contents.end(),
               sorted_contents.begin(), sorted_contents.end(),
               final_sorted.begin());

    // merge appended_contents into sorted_contents
    return sorted_contents;
}

Path_Node * build_path_node(const path &dir_path) { //remember to add a parent (if applicable)
    Path_Node * node;
    node->dir_name = dir_path;
    node->contents = dir_contents(dir_path);
    return node;
}
