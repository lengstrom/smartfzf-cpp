#ifndef GUARD_smartfzf_h
#define GUARD_smartfzf_h

#include <string>
#include <vector>

bool fz_match(const std::string &, const std::string &);
bool prefix_match(const std::string &input, const std::string &against);

std::vector<std::string> match_from_candidates(const std::string &input, const std::vector<std::string> &candidates);

#endif
