#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include "smartfzf.h"
#include "input.h"
#include "fs.h"

using std::vector;
using std::string;
using boost::filesystem::path;

int main(int argc, char *argv[]) {
    path base_directory ("."); // directory used to run smartfzf
    std::string curr_line = ""; // current typed line on cmdline
    vector<string> matched_items; // items matched within directory
    Renderer r(curr_line, matched_items); // renderer object
    Input i(r); // input object
    Path_Node * curr_dir_node = new Path_Node;
    // Build Path_Node branch
    {
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
        }
    }

    print_string_of_dir_nodes(curr_dir_node);
    exit(1);

    while (true) {
        bool err;
        vector<string> curr_dir_components = dir_components(curr_line, base_directory, err);
        if (!err) {
            std::optional<Path_Node*> list = archived_file_list(curr_dir_components, base_directory);
            vector<string> dir_contents;
            if (list) {
                dir_contents = static_cast<vector<string>>(list);
            } else {
                dir_contents = sorted_dir_contents(this_dir, current_directory.size());
            }    
            
            matched_items = match_from_candidates(curr_line,dir_contents);
        } else {
            matched_items = curr_dir_components;
        }
        
        r.rerender_window();
        curr_line = i.read_char();
        // current_directory = get_directory_vector(curr_line);
    }
    return 0;
}
