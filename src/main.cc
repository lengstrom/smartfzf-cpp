#include <iostream>
#include <vector>
#include <string>
#include "smartfzf.h"

/* read the list of files from
 * stdin, read the current buffer
 * from argv, output to stdout
 *
 * what it does: matches the
 * last token of the current
 * buffer against the list
 * of files, and prints
 * the files that the token
 * matches according to
 * Smartfzf::fz_match()
 *
 * expecting list of files from
 * ls, delimited with newlines
 * */
int main(int argc, char *argv[])
{
    const int NUM_RESERVE = 7; // number of spaces to reserve in vect

    const char *input = argv[argc-1];
    std::vector<std::string> against_vect;
    against_vect.reserve(7);

    std::string temp_string;
    while(std::getline(std::cin,temp_string))
    {
        against_vect.push_back(temp_string);
    }

    for(std::vector<std::string>::iterator it = against_vect.begin();
            it != against_vect.end();
            it++)
    {
        if(Smartfzf::fz_match(input,*it))
            std::cout << *it << ' ';
    }

    return 0;
}

