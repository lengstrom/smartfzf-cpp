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

path base_dir = path("../test/sandbox/");

bool check_ptr_eql(std::string* a, std::string b) {
    return (*a) == (b);
}

bool check_ptr_vecs(std::vector<std::string*> v1, std::vector<std::string> v2) {
    std::vector<std::string*>::size_type n = v1.size();
    return std::equal(v1.begin(), v1.begin() + n, v2.begin(), check_ptr_eql);
}

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
    vector<string> all_contents = recursive_sorted_contents(base_dir, "");
    // for (auto i : all_contents) {
    //     std::cout << i << std::endl;
    // }
    // vector<string> all_contents_against = {"a", "az", "b", "bb", "c", "dir_1/a", "dir_1/abc", "dir_1/b", "dir_1/c", "dir_1/cee", "dir_1/e", "dir_1/g", "dir_2/77", "dir_2/git_dir/a", "dir_2/git_dir/b", "dir_2/git_dir/c", "dir_2/git_dir/git_dir_b/a", "dir_2/git_dir/git_dir_b/b", "dir_2/git_dir/git_dir_b/c", "dir_2/poi", "dir_2/qq"};
    // bool res_recursive = check_vecs(all_contents, all_contents_against);
    // BOOST_CHECK(res_recursive);
    // std::cout << "Getting all contents" << std::endl;
}
