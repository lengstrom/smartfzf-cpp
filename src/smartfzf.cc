#include "smartfzf.h"
#include <iterator>
#include <algorithm>
#include <iostream>

/* returns true if the first string
 * is a lazy subset of the second
 * string */
bool fz_match(const std::string &input, const std::string &against)
{
    for(std::string::const_iterator input_iter = input.begin(), 
            against_iter = against.begin(); 
            against_iter != against.end();
            against_iter++) {
        // std::cout << "chars: " << *input_iter << " against " << *against_iter << '\n';
        if(tolower(*input_iter) == tolower(*against_iter)) {
            input_iter++;
            if( input_iter == input.end() )
                return true;
        }
    }
    return false;
}

// do stuff
