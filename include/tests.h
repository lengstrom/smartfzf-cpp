#ifndef GUARD_Test
#define GUARD_Test

#include <string>

class Test {
public:
    Test(int);
    ~Test();
    bool fz_match(const std::string &, const std::string &);
}; // semicolon!


#endif
