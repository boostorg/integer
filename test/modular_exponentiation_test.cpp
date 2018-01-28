/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#define BOOST_TEST_MODULE modular_exponentiation_test
#include <boost/test/included/unit_test.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/modular_exponentiation.hpp>

using boost::multiprecision::int128_t;
using boost::integer::modular_exponentiation;

template<class Z>
void test_modular_exponentiation()
{
    Z base = 7;
    Z modulus = 51;
    Z expected = 1;
    for (Z exponent = 0; exponent < 10000; ++exponent)
    {
        Z x = modular_exponentiation<Z>(base, exponent, modulus);
        BOOST_CHECK_EQUAL(expected, x);
        expected = (expected*base) % modulus;
    }
}

BOOST_AUTO_TEST_CASE(modular_exponentiation_test)
{
    test_modular_exponentiation<int>();
    test_modular_exponentiation<unsigned>();
    test_modular_exponentiation<short>();
    test_modular_exponentiation<size_t>();
    test_modular_exponentiation<int128_t>();
}
