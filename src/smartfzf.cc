#include "smartfzf.h"
#include <iostream>

Test::Test(int h) {
    std::cout << h << std::endl; //flushes output buffer
}

Test::~Test() {
    std::cout << "Destruction." << std::endl;
}

// do stuff
