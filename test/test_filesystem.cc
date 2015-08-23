#define BOOST_TEST_MODULE "filesystem"

#include <iostream>
#include <algorithm>
#include <string>


#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
#include "fs.h"

using std::vector;
using std::string;

path base_dir = path("../test/sandbox");

bool check_vecs(std::vector<std::string> v1, std::vector<std::string> v2) {
    std::vector<std::string>::size_type n = v1.size();
    return (std::equal(v1.begin(), v1.begin() + n, v2.begin()));
}



BOOST_AUTO_TEST_CASE(get_base_directory_test) {
    std::cout << "started test.." << std::endl;
    std::string input = "./a";
    bool err = false;
    std::vector<std::string> strs = dir_components(input, base_dir, err);
    std::vector<std::string> strs_against = {"/","Users", "loganengstrom","projects","smartfzf-cpp","test","sandbox"};
    
    bool res = check_vecs(strs, strs_against);
    BOOST_CHECK(res);
}

BOOST_AUTO_TEST_CASE(filesystem_test) {
    // Filesystem checking
    vector<string> contents = sorted_dir_contents(base_dir);
    vector<string> contents_against = {"a","az","b","bb","c","dir_1","dir_2"};
    bool res = check_vecs(contents, contents_against);
    BOOST_CHECK(res);
    BOOST_CHECK(!is_project(contents));
    
    // some kind of memory error here
    vector<string> all_contents = recursive_sorted_contents(base_dir);
    vector<string> all_contents_against = {"../test/sandbox/a", "../test/sandbox/az", "../test/sandbox/b", "../test/sandbox/bb", "../test/sandbox/c", "../test/sandbox/dir_1/a", "../test/sandbox/dir_1/abc", "../test/sandbox/dir_1/b", "../test/sandbox/dir_1/c", "../test/sandbox/dir_1/cee", "../test/sandbox/dir_1/e", "../test/sandbox/dir_1/g", "../test/sandbox/dir_2/77", "../test/sandbox/dir_2/git_dir/a", "../test/sandbox/dir_2/git_dir/b", "../test/sandbox/dir_2/git_dir/c", "../test/sandbox/dir_2/git_dir/git_dir_b/a", "../test/sandbox/dir_2/git_dir/git_dir_b/b", "../test/sandbox/dir_2/git_dir/git_dir_b/c", "../test/sandbox/dir_2/poi", "../test/sandbox/dir_2/qq"};
    bool res_recursive = check_vecs(all_contents, all_contents_against);
    BOOST_CHECK(res_recursive);
    std::cout << "Getting all contents" << std::endl;
}
