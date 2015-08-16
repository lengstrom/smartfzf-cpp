#ifndef GUARD_fs_h
#define GUARD_fs_h

#include <map>
#include <vector>
#include "boost/filesystem.hpp"

struct Path_Node {
    // lazily evaluated tree structure for storing files implemented as a POD struct
    // don't get child_dirs unless absolutely necessary
    Path_Node * parent_dir;
    bool no_parent = false;
    boost::filesystem::path * dir_name;
    std::vector<const boost::filesystem::path> contents;
    std::map<const boost::filesystem::path, Path_Node*> child_dirs;
};

std::vector<boost::filesystem::path> sorted_dir_contents(boost::filesystem::path &dir_path);
bool is_project(std::vector<boost::filesystem::path> &contents);
std::vector<boost::filesystem::path> recursive_sorted_contents(boost::filesystem::path &dir_path);
#endif
