#include <iostream>
#include "smartfzf.h"

int main(int argc, char *argv[]) 
{
    std::cout << "It's working!\n";
    // example class from smartfzf.h
    Test foo(5);
    return 0;
    // automatic class deconstructor called
    // when Test goes out of scope
}
