#define BOOST_TEST_MODULE "filesystem"

#include <iostream>
#include <algorithm>
#include <string>


#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "fs.h"

using namespace boost::filesystem;
using std::vector;
using std::string;

BOOST_AUTO_TEST_CASE(get_base_directory_test)
{
    std::cout << "started test.." << std::endl;
    std::string input = "./test/test_filesystem";
    boost::filesystem::path base(".");
    bool err = false;
    std::vector<std::string> strs = dir_components(input, base, err);
    std::cout << "Started vector printing..." << std::endl;
    for (auto i : strs) {
        std::cout << i << std::endl;
    }
    std::cout << "Ended vector printing." << std::endl;
}

BOOST_AUTO_TEST_CASE(filesystem_test)
{
    // Filesystem checking
    path curr_dir = current_path();
    vector<string> contents = sorted_dir_contents(curr_dir);
    path contents_against[2] = {"sandbox", "test_smartfzf.cc"};
    bool res = true;
    for (int i =0 ; i < 2; i++) {
        if (contents_against[i] != contents[i]) {
            res = false;
        }
    }
    
    BOOST_CHECK(res);
    BOOST_CHECK(!is_project(contents));

    // some kind of memory error here
    vector<string> all_contents = recursive_sorted_contents(curr_dir);
    // std::cout << "Getting all contents" << std::endl;
    // for (auto i : all_contents) {
    //     std::cout << i << std::endl;
    //}
}
