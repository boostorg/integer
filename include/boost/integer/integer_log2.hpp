// -----------------------------------------------------------
// integer_log2.hpp
//
//   Gives the integer part of the logarithm, in base 2, of a
// given number. Behavior is undefined if the argument is <= 0.
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_INTEGER_INTEGER_LOG2_HPP
#define BOOST_INTEGER_INTEGER_LOG2_HPP

#include <climits>
#include <boost/config.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace detail {

template <typename T>
inline int integer_log2_impl(T x, unsigned int n)
{
    int result = 0;

    while (x != 1)
    {
        const T t = static_cast<T>(x >> n);
        if (t)
        {
            result += static_cast<int>(n);
            x = t;
        }
        n >>= 1u;
    }

    return result;
}

// helper to find the maximum power of two
// less than p
template <unsigned int p, unsigned int n, bool = (2u*n < p)>
struct max_pow2_less :
    public max_pow2_less< p, 2u*n >
{
};

template <unsigned int p, unsigned int n>
struct max_pow2_less<p, n, false>
{
    BOOST_STATIC_CONSTANT(unsigned int, value = n);
};

} // namespace detail


// ------------
// integer_log2
// ------------
template <typename T>
inline int integer_log2(T x)
{
    BOOST_ASSERT(x > 0);

    return detail::integer_log2_impl
    (
        x,
        detail::max_pow2_less<
            // We could simply rely on numeric_limits but sometimes
            // Borland tries to use numeric_limits<const T>, because
            // of its usual const-related problems in argument deduction
            // - gps
            // Also, numeric_limits is not specialized for __int128 in libstdc++.
            sizeof(T) * CHAR_BIT,
            CHAR_BIT / 2u
        >::value
    );
}

}

#endif // BOOST_INTEGER_INTEGER_LOG2_HPP
