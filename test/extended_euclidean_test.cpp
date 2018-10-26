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
using boost::multiprecision::int256_t;
using boost::integer::extended_euclidean;
using boost::integer::gcd;

template<class Z>
void test_extended_euclidean()
{
    std::cout << "Testing the extended Euclidean algorithm on type " << boost::typeindex::type_id<Z>().pretty_name() << "\n";
    // Stress test:
    //Z max_arg = std::numeric_limits<Z>::max();
    Z max_arg = 500;
    for (Z m = max_arg; m > 0; --m)
    {
        for (Z n = m; n > 0; --n)
        {
            boost::integer::euclidean_result_t u = extended_euclidean(m, n);
            int256_t gcdmn = gcd(m, n);
            int256_t x = u.x;
            int256_t y = u.y;
            BOOST_CHECK_EQUAL(u.gcd, gcdmn);
            BOOST_CHECK_EQUAL(m*x + n*y, gcdmn);
        }
    }
}



BOOST_AUTO_TEST_CASE(extended_euclidean_test)
{
    test_extended_euclidean<int16_t>();
    test_extended_euclidean<int32_t>();
    test_extended_euclidean<int64_t>();
    test_extended_euclidean<int128_t>();
}
