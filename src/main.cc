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
    path this_dir(".");
    
    std::string curr_line = "";
    vector<string> matched_items;
    Renderer r(curr_line, matched_items);
    Input i(r);
    Path_Node * base_directory;
    string current_directory = this_dir.filename().string();
    base_directory.dir_name = current_directory;
    
    while (true) {
        vector<string> dir_contents = sorted_dir_contents(this_dir);
        matched_items = match_from_candidates(curr_line,dir_contents);
        r.rerender_window();
        current_directory.contents = dir_contents;
        curr_line = i.read_char();
        current_directory = get_base_directory(curr_line);
    }

    return 0;
}
