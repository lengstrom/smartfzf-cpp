#define BOOST_TEST_MODULE "smartfzf"
#include <boost/test/unit_test.hpp>
#include "smartfzf.h"

BOOST_AUTO_TEST_CASE(fuzzy_function)
{
    BOOST_CHECK(fz_match("Hello","inwqpohapoiuoiueasdfaqloiulops"));
    BOOST_CHECK(fz_match("qphaoi","inwqpohapoiuoiueasdfaqloiulops"));
    BOOST_CHECK(fz_match("ntr","inter"));
    BOOST_CHECK(fz_match("is","ijjjjjjjjjjjjjjjjjjs"));
    BOOST_CHECK(fz_match("weare","wearent"));
    BOOST_CHECK(fz_match("gooday","goodday"));
    BOOST_CHECK(fz_match("iz","nifez"));
    BOOST_CHECK(!fz_match("zi","nifez"));
    BOOST_CHECK(!fz_match("z0","nifez"));
}
