#define BOOST_TEST_MODULE "smartfzf"
#include <boost/test/unit_test.hpp>
#include "smartfzf.h"
#include "boost/filesystem.hpp"
#include "fs.h"
#include <iostream>
#include <algorithm>

using namespace boost::filesystem;
using std::vector;


BOOST_AUTO_TEST_CASE(fuzzy_function) {
    // Fuzzy matching 
    BOOST_CHECK(fz_match("Hello","inwqpohapoiuoiueasdfaqloiulops"));
    BOOST_CHECK(fz_match("qphaoi","inwqpohapoiuoiueasdfaqloiulops"));
    BOOST_CHECK(fz_match("ntr","inter"));
    BOOST_CHECK(fz_match("is","ijjjjjjjjjjjjjjjjjjs"));
    BOOST_CHECK(fz_match("weare","wearent"));
    BOOST_CHECK(fz_match("gooday","goodday"));
    BOOST_CHECK(fz_match("iz","nifez"));
    BOOST_CHECK(!fz_match("zi","nifez"));
    BOOST_CHECK(!fz_match("z0","nifez"));
 
    // Filesystem checking
    path curr_dir = current_path();
    vector<path> contents = sorted_dir_contents(curr_dir);
    path contents_against[2] = {"sandbox", "test_smartfzf.cc"};
    bool res = true;
    for (int i =0 ; i < 2; i++) {
        if (contents_against[i] != contents[i].filename().string()) {
            res = false;
        }
    }
    BOOST_CHECK(res);
    BOOST_CHECK(!check_for_project(contents));
    
    vector<path> all_contents = recursive_sorted_contents(curr_dir);
    for (auto i : all_contents) {
        std::cout << i << std::endl;
    }

}
