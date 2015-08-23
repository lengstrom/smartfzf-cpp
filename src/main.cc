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
    const path base_directory (".");
    vector<string> lines_to_render;
    path this_dir(".");
    
    std::string curr_line = "";
    vector<string> matched_items;
    Renderer r(curr_line, matched_items);
    Input i(r);
    string current_directory = this_dir.filename().string();
    vector<string> split_path;
    split_path.push_back(current_directory);

    while (true) {
        vector<string> dir_contents = sorted_dir_contents(this_dir);
        matched_items = match_from_candidates(curr_line,dir_contents);
        r.rerender_window();
        curr_line = i.read_char();
        // current_directory = get_directory_vector(curr_line);
    }

    return 0;
}
