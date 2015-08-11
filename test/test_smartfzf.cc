#define BOOST_TEST_MODULE "smartfzf"
#include <boost/test/unit_test.hpp>
#include "smartfzf.h"
#include "boost/filesystem.hpp"
#include "fs.h"
#include <iostream>

using namespace boost::filesystem;
using std::vector;

//bool t = test_func();

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
    // path curr_dir = current_path();
    // vector<const path*> contents = sorted_dir_contents(&curr_dir);
    // bool t = test_func();
    // for (auto itr : contents) {
    //     std::cout << (*itr) << std::endl;
    // }
}
