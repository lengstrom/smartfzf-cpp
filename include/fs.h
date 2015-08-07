#ifndef GUARD_fs_h
#define GUARD_fs_h

#include <map>
#include <string>
#include <vector>
#include "boost/filesystem.hpp" // whats the diff between < and "s??

struct path_node {
    // lazily evaluated tree structure for storing files implemented as a POD struct
    // don't get child_dirs unless absolutely necessary
    path_node parent_dir;
    std::string dir_name;
    std::vector<boost::filesystem::path> contents;
    std::map<path_node> child_dirs;
};

std::vector<boost::filesystem::path> dir_contents(const boost::filesystem::path &dir_path) ;

#endif
