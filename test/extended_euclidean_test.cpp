/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_MODULE extended_euclidean_test
#include <boost/test/included/unit_test.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/common_factor.hpp>
#include <boost/integer/extended_euclidean.hpp>

using boost::multiprecision::int128_t;
using boost::integer::extended_euclidean;
using boost::integer::gcd;

template<class Z>
void test_extended_euclidean()
{
    Z max_arg = 1000;
    for (Z m = 1; m < max_arg; ++m)
    {
        for (Z n = 1; n < max_arg; ++n)
        {
            std::tuple<Z, Z, Z> u = extended_euclidean(m, n);
            Z gcdmn = gcd(m, n);
            Z x = std::get<1>(u);
            Z y = std::get<2>(u);
            BOOST_CHECK_EQUAL(std::get<0>(u), gcdmn);
            BOOST_CHECK_EQUAL(m*x + n*y, gcdmn);
        }
    }
}

BOOST_AUTO_TEST_CASE(extended_euclidean_test)
{
    test_extended_euclidean<int>();
    test_extended_euclidean<long>();
    test_extended_euclidean<long long>();
    test_extended_euclidean<int128_t>();
}
