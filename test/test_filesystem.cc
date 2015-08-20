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
    using std::string;
    BOOST_CHECK(string("asdfwef/asdfwqefij/sadfjio").compare(
                get_base_directory("asdfwef/asdfwqefij/sadfjio/wei.ji\\ sd"))==0);
    BOOST_CHECK(string("asdf").compare(
                get_base_directory("asdf/asdf"))==0);
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
    
    vector<string> all_contents = recursive_sorted_contents(curr_dir);
    std::cout << "Getting all contents" << std::endl;
    for (auto i : all_contents) {
        std::cout << i << std::endl;
    }
}
