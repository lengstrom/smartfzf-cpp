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
    std::cout << "smartfzf works!" << std::endl;
    vector<string> lines_to_render;
    path current_dir(".");
    vector<path> dircontents = sorted_dir_contents(current_dir);
    vector<string> dir_strings;
    for(int i=0; i<dircontents.size(); i++) {
        dir_strings.push_back(dircontents[i].filename().string());
    }
    std::string curr_line = "";
    Renderer r(dir_strings, curr_line);
    Input i(r);
    while (true) {
        vector<string> items = match_from_candidates(curr_line,dir_strings);
        r.rerender_window();
        curr_line = i.read_char();
    }

    return 0;
}
