#ifndef GUARD_fs_h
#define GUARD_fs_h

#include <map>
#include <vector>
#include <experimental/optional>
#include <boost/filesystem.hpp>

struct Path_Node {
    // lazily evaluated tree structure for storing files implemented as a POD struct
    // don't get child_dirs unless absolutely necessary
    Path_Node * parent;
    bool has_parent = false;
    //    Search_Index * index;
    std::string dir_name;
    std::vector<std::string*> contents;
    std::map<std::string, Path_Node*> children;
};

struct Archive {
    Archive(Path_Node * base_node, boost::filesystem::path &base_directory);
    Path_Node * base_path;
    Path_Node * root;
    std::experimental::optional<Path_Node*> get_archived_file_list(std::vector<std::string> &components);
    void add_archived_files(std::vector<std::string> &components, std::vector<std::string*> &files);
    Path_Node* find_node(std::vector<std::string> &components);
};

std::string get_folder_from_line(std::string &line);
std::vector<std::string> sorted_dir_contents(boost::filesystem::path &dir_path);
bool is_project(std::vector<std::string> &contents);
std::vector<std::string> recursive_sorted_contents(boost::filesystem::path dir_path, std::string prefix);
std::vector<std::string> dir_components(const std::string &input, const boost::filesystem::path &base, bool &err);
std::string get_folder_from_line(std::string &line);
Path_Node* find_node(std::vector<std::string> &components);

#endif
