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
    vector<string> lines_to_render;
    path current_dir(".");
    vector<string> dir_contents = sorted_dir_contents(current_dir);
    std::string curr_line = "";
    vector<string> matched_items;
    Renderer r(curr_line, matched_items);
    Input i(r);
    Path_Node * base_directory;
    
    while (true) {
        matched_items = match_from_candidates(curr_line,dir_contents);
        r.rerender_window();
        curr_line = i.read_char();
    }

    return 0;
}
