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
    Archive archive = Archive(curr_dir_node, base_directory);
    while (true) {
        r.rerender_window();
        curr_line = i.read_char();
        // current_directory = get_directory_vector(curr_line);
    }
    return 0;
}
