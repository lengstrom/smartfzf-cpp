#ifndef GUARD_fs_h
#define GUARD_fs_h

#include <map>
#include <vector>
#include <experimental>
#include <boost/filesystem.hpp>
#include <boost/system.hpp>

struct Path_Node {
    // lazily evaluated tree structure for storing files implemented as a POD struct
    // don't get child_dirs unless absolutely necessary
    Path_Node * parent_dir;
    bool no_parent = false;
    std::string dir_name;
    std::vector<std::string> contents;
    std::map<std::string, Path_Node*>;
};

std::optional
std::vector<std::string> sorted_dir_contents(boost::filesystem::path &dir_path);
bool is_project(std::vector<std::string> &contents);
std::vector<std::string> recursive_sorted_contents(boost::filesystem::path &dir_path);
boost::filesystem::path get_base_directory(const std::string&);

#endif
