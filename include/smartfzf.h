#ifndef SMARTFZF_INCLUDE_SMARTFZF_H_ // include guard
#define SMARTFZF_INCLUDE_SMARTFZF_H_

#include <string>
#include <vector>

bool fz_match(const std::string &, const std::string &);
std::vector<std::string> match_from_candidates(
        const std::string &input, const std::vector<std::string> &candidates);

#endif // SMARTFZF_INCLUDE_SMARTFZF_H_
