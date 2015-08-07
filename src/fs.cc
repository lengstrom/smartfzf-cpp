#include <vector>
#include "fs.h"
#include "boost/filesystem.hpp"

using boost::filesystem;

vector<path> dir_contents(const path &dir_path) {
    /* 
     * Possible issues:
     * Permissions - unable to read into directory (Does this actually happen???)
     * File/directory doesn't exist - what should this return in that case?
     */

    // For now use naive implementation assuming no errors occur
    // Research done: try catch blocks have 0 performance hit (unless there's an exception, obv)
    vector<path> contents;
    directory_iterator end_itr; // default constructor = object past end
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        contents.push_back(itr->path());
    }

    return contents;
}


