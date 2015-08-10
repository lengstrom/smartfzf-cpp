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
    std::vector<boost::filesystem::path*> contents;
    std::map<boost::filesystem::path*, Path_Node*> child_dirs;
} Path_Node;

std::vector<const boost::filesystem::path*> dir_contents(const boost::filesystem::path * dir_path);
std::vector<const boost::filesystem::path*> recursive_sorted_dir_contents(const boost::filesystem::path * dir_path);

#endif
