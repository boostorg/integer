/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_MODULAR_EXPONENTIATION_HPP
#define BOOST_INTEGER_MODULAR_EXPONENTIATION_HPP
#include <limits>

namespace boost { namespace integer {

template<class Z>
Z modular_exponentiation(Z base, Z exponent, Z modulus)
{
    using std::numeric_limits;
    static_assert(numeric_limits<Z>::is_integer,
                  "Modular exponentiation works on integral types.\n");
    Z result = 1;
    if (exponent < 0 || modulus < 0)
    {
        throw std::domain_error("Both the exponent and the modulus must be > 0.\n");
    }

    while (exponent > 0)
    {
        if (exponent & 1)
        {
            result = (result*base) % modulus;
        }
        base = (base*base) % modulus;
        exponent >>= 1;
    }
    return result;
}


}}
#endif
