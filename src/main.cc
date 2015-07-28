#include <iostream>
#include <boost/filesystem.hpp>
#include "smartfzf.h"

int main(int argc, char *argv[]) 
{
    std::cout << "It's working!\n";
    // example class from smartfzf.h
    Test foo(5);
    std::cout << "Smartfzf file size: "<< boost::filesystem::file_size("smartfzf") << std::endl;
    return 0;
    // automatic class deconstructor called
    // when Test goes out of scope
}
