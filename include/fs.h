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
    std::vector<const boost::filesystem::path*> contents;
    std::map<const boost::filesystem::path*, Path_Node*> child_dirs;
};

std::vector<const boost::filesystem::path*> sorted_dir_contents(const boost::filesystem::path *dir_path);
bool check_for_project(const Path_Node *dir_node);
std::vector<const boost::filesystem::path*> recursive_sorted_dir_contents(const boost::filesystem::path *dir_path);
#endif
