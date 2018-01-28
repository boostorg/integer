/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_MODULE modular_multiplicative_inverse_test
#include <boost/test/included/unit_test.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/common_factor.hpp>
#include <boost/integer/modular_multiplicative_inverse.hpp>

using boost::multiprecision::int128_t;
using boost::integer::modular_multiplicative_inverse;
using boost::integer::gcd;

template<class Z>
void test_modular_multiplicative_inverse()
{
    Z max_arg = 1000;
    for (Z modulus = 2; modulus < max_arg; ++modulus)
    {
        for (Z a = 1; a < max_arg; ++a)
        {
            Z gcdam = gcd(a, modulus);
            boost::optional<Z> inv_a = modular_multiplicative_inverse(a, modulus);
            // Should fail if gcd(a, mod) != 1:
            if (gcdam > 1)
            {
                BOOST_CHECK(!inv_a);
            }
            else
            {
                BOOST_CHECK(inv_a.value() > 0);
                Z outta_be_one = (inv_a.value()*a) % modulus;
                BOOST_CHECK_EQUAL(outta_be_one, 1);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(extended_euclidean_test)
{
    test_modular_multiplicative_inverse<int>();
    test_modular_multiplicative_inverse<long>();
    test_modular_multiplicative_inverse<long long>();
    test_modular_multiplicative_inverse<int128_t>();
}
