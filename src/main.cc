#include <iostream>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>

#include "smartfzf.h"
#include "input.h"

int main(int argc, char *argv[])
{
    // get listdir
    std::vector<std::string> filenames;
    boost::filesystem::path p(".");
    for(boost::filesystem::directory_iterator it(p);
            it != boost::filesystem::directory_iterator();
            it++)
    {
        filenames.push_back(it->path().filename().string());
    }


    Input in;

    in.write_prompt("Hello! please type here: ");

    std::string below_input;
    for(std::vector<std::string>::iterator it = filenames.begin();
            it != filenames.end();
            it++) {
        below_input.append(*it);
        below_input.append("\t");
    }
    in.write_below_input(below_input);

    std::string input;
    while(true) {
        int ch = in.read_char();
        if(ch == KEY_BACKSPACE) {
            if(input.length() > 0)
            {
                input = input.substr(0,input.length()-1);
            }
        } else {
            input.append(1,(wchar_t)ch);
        }
        std::string below_input;
        std::vector<std::string> matched_filenames = match_from_candidates(input,filenames);
        for(std::vector<std::string>::iterator it = matched_filenames.begin();
                it != matched_filenames.end();
                it++) {
            below_input.append(*it);
            below_input.append("\t");
        }
        in.write_below_input(below_input);
        in.write_input(input);
        if(ch == KEY_BACKSPACE)
            delch();
    }


    return 0;
}

