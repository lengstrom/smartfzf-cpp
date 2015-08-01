#include "smartfzf.h"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

/* returns true if the first string
 * is a lazy subset of the second
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

vector<string> match_from_candidates(const string &input, vector<string> &candidates) {
    vector<string> results;
    for (vector<string>::const_iterator it = candidates.begin(); it != v.end(); it++) {
        const string &curr = *it;
        if (fz_match(input, curr)) {
            results.push_back(curr);
        }
    }

    return results;
}
