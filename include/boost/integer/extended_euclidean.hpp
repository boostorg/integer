/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_EXTENDED_EUCLIDEAN_HPP
#define BOOST_INTEGER_EXTENDED_EUCLIDEAN_HPP
#include <tuple>
#include <limits>
#include <stdexcept>
#include <boost/throw_exception.hpp>

namespace boost { namespace integer {

// From "The Joy of Factoring", Algorithm 2.7, with a small optimization to remove tmps from Wikipedia.
// Solves mx + ny = gcd(m,n). Returns tuple with (gcd(m,n), x, y).

template<class Z>
struct euclidean_result_t {
  Z gcd;
  Z x;
  Z y;
};

template<class Z>
euclidean_result_t<Z> extended_euclidean(Z m, Z n)
{
    using std::numeric_limits;
    static_assert(numeric_limits<Z>::is_integer,
                  "The extended Euclidean algorithm works on integral types.\n");

    static_assert(numeric_limits<Z>::is_signed,
                  "The extended Euclidean algorithm only works on signed integer types.\n");

    if (m < 1 || n < 1)
    {
        BOOST_THROW_EXCEPTION(std::domain_error("Arguments must be strictly positive.\n"));
    }

    Z s = 0;
    Z old_s = 1;
    Z r = n;
    Z old_r = m;

    while (r != 0) {
      Z q = old_r/r;
      Z tmp = r;
      r = old_r - q*tmp;
      old_r = tmp;

      tmp = s;
      s = old_s - q*tmp;
      old_s = tmp;
    }

    Z y = (old_r - old_s*m)/n;

    BOOST_ASSERT(old_s*m+y*n==old_r);
    return {old_r, old_s, y};
}

}}
#endif
