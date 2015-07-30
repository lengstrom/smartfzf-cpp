#include <iostream>
#include <boost/filesystem.hpp>
#include "smartfzf.h"


int main(int argc, char *argv[]) 
{
    // example class from smartfzf.h
    std::cout << "Smartfzf file size: "<< boost::filesystem::file_size("smartfzf") << std::endl;
    return 0;
}

