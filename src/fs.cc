#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <map>
#include <experimental/optional>
#include <iostream>
#include <boost/filesystem.hpp>
#include "fs.h"

using std::vector;
using std::string;
using namespace boost::filesystem;
using std::experimental::optional;

const string PROJECT_MARKERS[2] = {".git", ".svn"};
const int PROJECT_MARKERS_SIZE = 2;

Archive::Archive(Path_Node * curr_dir_node, path &base_directory) {
    path full_base_dir = canonical(base_directory);
    string base_dir_string = base_directory.string();
    bool err = false;
    vector<string> base_dir_components = dir_components(base_dir_string, full_base_dir, err);
    if (err) {
        exit(1);
    } else {
        vector<string>::reverse_iterator itr = base_dir_components.rbegin();
        curr_dir_node->dir_name = *itr;
        Path_Node * last_temp_node = curr_dir_node;
        for (itr = itr + 1; itr != base_dir_components.rend(); itr++) {
            Path_Node * temp_node = new Path_Node;
            temp_node->dir_name = *itr;
            temp_node->children[temp_node->dir_name] = last_temp_node;
            last_temp_node->parent = temp_node;
            last_temp_node->has_parent = true;
            last_temp_node = temp_node;
        }

        root = last_temp_node;
    }
}

optional<Path_Node*> Archive::get_archived_file_list(std::vector<std::string> &components) {
    Path_Node* curr_node = find_node(components);
    if ((curr_node->contents).empty()) {
        return optional<Path_Node*>();
    } else {
        return optional<Path_Node*>(curr_node);
    }
}

Path_Node* Archive::find_node(vector<string> &components) {
    Path_Node * curr_node = root;
    vector<string>::iterator itr = components.begin();
    while (itr != components.end()) {
        string name = (*itr);
        if (curr_node->children.find(name) == curr_node->children.end()) {
            curr_node = curr_node->children[name];
        } else {
            Path_Node * new_node = new Path_Node;
            new_node->dir_name = name;
            new_node->parent = curr_node;
            curr_node->children[name] = new_node;
        }
        itr++;
    }
    return curr_node;
}

void Archive::add_archived_files(std::vector<std::string> &components, vector<string*> &files) {
    Path_Node * node = find_node(components);
    node->contents = files;
}

std::string get_folder_from_line(std::string &line) {
    if (line.empty()) return "";
    string dir;
    if (line[0] == '/') dir = "/";
    string curr_subpath = "";
    for (string::iterator itr = line.begin(); itr != line.end(); itr++) {
        if (*itr == '/') {
            dir += curr_subpath;
            curr_subpath = "";
        } else {
            curr_subpath += *itr;
        }
    }

    return dir;
}

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
        string curr_file = (*itr).path().filename().string();
        contents.push_back(curr_file);
    }
   
    return contents;
}

bool is_project(vector<string> &contents) {
    // assume that dir_path is a directory
    for (auto file : contents) {
        for (int i = 0; i < PROJECT_MARKERS_SIZE; i++) {
            if (PROJECT_MARKERS[i] == file) {
                return true;
            }
        }
    }

    return false;
}

template<typename It, typename T>
void loc_in_vec(It &vec, It end, T f) {
    while (vec != end && *vec < f) {
        vec++;
    }
}

template<typename T, typename A>
void merge_into_vector(vector<T,A> &vec, T f) {
    typename vector<T, A>::iterator vec_itr = vec.begin();
    loc_in_vec(vec_itr, vec.end(), f);
    vec.insert(vec_itr, f);
}

// recursively copy dir contents
// recursive_sorted_contents(base_dir, "");

vector<string> recursive_sorted_contents(path &dir_path, string prefix) {
    directory_iterator end_itr;
    vector<string> file_entries;
    vector<path> dir_entries;
    for (directory_iterator itr(dir_path); itr != end_itr; itr++) {
        string base_name = itr->path().filename().string();
        if (base_name[0] == '.') {
            continue;
        }

        if (is_directory(itr->status())) {
            path p = itr->path();
            merge_into_vector(dir_entries, p);
        } else {
            merge_into_vector(file_entries, base_name);
        }
    }

    vector<string>::iterator it = file_entries.begin();
    for (auto dir_path : dir_entries) {
        string s = dir_path.filename().string();
        loc_in_vec(it, file_entries.end(), s);
        vector<string> dir_contents = recursive_sorted_contents(dir_path, s + "/");
        file_entries.reserve(dir_contents.size() + file_entries.size());
        file_entries.insert(it, dir_contents.begin(), dir_contents.end());
    }

    for (int i = 0; i < file_entries.size(); i++) {
        file_entries[i] = prefix + file_entries[i];
    }

    std::cout << "Files:" << std::endl;
    for (auto i : file_entries) {
        std::cout << i << std::endl;
    }
    std::cout << "-----" << std::endl;

    return file_entries;
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
