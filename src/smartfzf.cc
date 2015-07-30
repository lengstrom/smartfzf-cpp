#include "smartfzf.h"
#include <iterator>
#include <algorithm>
#include <iostream>

Smartfzf::Smartfzf(int h)
{
}

Smartfzf::~Smartfzf()
{
}


/* returns true if the first string
 * is a lazy subset of the second
 * string */
bool Smartfzf::fz_match(const std::string &input, const std::string &against)
{
    if(input.empty()) // otherwise, undefined behavior on empty string
        return false;
    for(std::string::const_iterator input_iter = input.begin(),
            against_iter = against.begin();
            against_iter != against.end();
            against_iter++) {
        if(tolower(*input_iter) == tolower(*against_iter)) {
            input_iter++;
            if( input_iter == input.end() )
                return true;
        }
    }
    return false;
}

