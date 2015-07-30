#ifndef SMARTFZF_INCLUDE_SMARTFZF_H_ // include guard
#define SMARTFZF_INCLUDE_SMARTFZF_H_

#include <string>

class Smartfzf {
public:
    Smartfzf(int);
    ~Smartfzf();
    static bool fz_match(const std::string &, const std::string &);
}; // semicolon!

#endif // SMARTFZF_INCLUDE_SMARTFZF_H_
