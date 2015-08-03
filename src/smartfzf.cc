#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include "smartfzf.h"

using std::string;
using std::map;
using std::vector;

/* Eventually add caching */

/* returns true if the first string
 * is an in-order subset of the second
 * string */
bool fz_match(const string &input, const string &against) {
    for (string::const_iterator input_iter = input.begin(),
             against_iter = against.begin(); 
         against_iter != against.end();
         against_iter++) {
        if (tolower(*input_iter) == tolower(*against_iter)) {
            input_iter++;
            if (input_iter == input.end())
                return true;
        }
    }

    return false;
}

/* Given an input string to match to and a vector of candidates (strings) to match to
 * Returns vector of strings that matched using fuzzy_search 
 */
vector<string> match_from_candidates(const string &input, vector<string> &candidates) 
{
    vector<string> results;
    for (vector<string>::const_iterator it = candidates.begin(); 
            it != candidates.end(); it++) {
        const string &curr = *it;
        if (fz_match(input, curr)) {
            results.push_back(curr);
        }
    }

    return results;
}

bool prefix_match(const string &input, const string &against) {
    for (string::const_iterator input_iter = input.begin(),
             against_iter = against.begin();
         against_iter != against.end();
         against_iter++,
             input_iter++
         ) {
        if (tolower(*input_iter) != tolower(*against_iter)) {
            return false;
        } else if (input_iter == input.end()) {
            return true;
        }
    }

    return false;
}
