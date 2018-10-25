/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_MOD_INVERSE_HPP
#define BOOST_INTEGER_MOD_INVERSE_HPP
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/optional.hpp>
#include <boost/integer/extended_euclidean.hpp>

namespace boost { namespace integer {

// From "The Joy of Factoring", Algorithm 2.7.
// Here's some others names I've found for this function:
// PowerMod[a, -1, m] (Mathematica)
// mpz_invert (gmplib)
// modinv (some dude on stackoverflow)
// Would mod_inverse be sometimes mistaken as the modular *additive* inverse?
// In any case, I think this is the best name we can get for this function without agonizing.
template<class Z>
boost::optional<Z> mod_inverse(Z a, Z modulus)
{
    if (modulus < 2)
    {
        BOOST_THROW_EXCEPTION(std::domain_error("Modulus must be > 1.\n"));
    }
    // make sure a < modulus:
    a = a % modulus;
    if (a == 0)
    {
        // a doesn't have a modular multiplicative inverse:
        return {};
    }
    euclidean_result_t<Z> u = extended_euclidean(a, modulus);
    Z gcd = u.gcd;
    if (gcd > 1)
    {
        return {};
    }
    Z x = u.x;
    x = x % modulus;
    // x might not be in the range 0 < x < m, let's fix that:
    while (x <= 0)
    {
        x += modulus;
    }
    BOOST_ASSERT(x*a % modulus == 1);
    return x;
}

}}
#endif
