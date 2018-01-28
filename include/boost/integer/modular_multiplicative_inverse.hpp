/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_MODULAR_MULTIPLICATIVE_INVERSE_HPP
#define BOOST_INTEGER_MODULAR_MULTIPLICATIVE_INVERSE_HPP
#include <limits>
#include <boost/optional.hpp>
#include <boost/integer/extended_euclidean.hpp>

namespace boost { namespace integer {

// From "The Joy of Factoring", Algorithm 2.7.
template<class Z>
boost::optional<Z> modular_multiplicative_inverse(Z a, Z modulus)
{
    using std::numeric_limits;
    static_assert(numeric_limits<Z>::is_integer,
                  "The modular multiplicative inverse works on integral types.\n");
    if (modulus < 2)
    {
        throw std::domain_error("Modulus must be > 1.\n");
    }
    // make sure a < modulus:
    a = a % modulus;
    if (a == 0)
    {
        // a doesn't have a modular multiplicative inverse:
        return {};
    }
    auto u = extended_euclidean(a, modulus);
    Z gcd = std::get<0>(u);
    if (gcd > 1)
    {
        return {};
    }
    Z x = std::get<1>(u);
    // x might not be in the range 0 < x < m, let's fix that:
    x = x % modulus;
    while (x <= 0)
    {
        x += modulus;
    }
    return x;
}

}}
#endif
