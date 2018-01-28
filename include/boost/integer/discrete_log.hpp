/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Two methods of computing the discrete logarithm over the multiplicative group of integers mod p.
 */

#ifndef BOOST_INTEGER_DISCRETE_LOG_HPP
#define BOOST_INTEGER_DISCRETE_LOG_HPP
#include <limits>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/integer/floor_sqrt.hpp>
#include <boost/integer/modular_multiplicative_inverse.hpp>
#include <boost/integer/modular_exponentiation.hpp>
#include <boost/integer/common_factor.hpp>

namespace boost { namespace integer {

// base^^x = a mod p <-> x = log_base(a) mod p
template<class Z>
boost::optional<Z> trial_multiplication_discrete_log(Z base, Z arg, Z p)
{
    using std::numeric_limits;
    static_assert(numeric_limits<Z>::is_integer,
                 "The discrete log works on integral types.\n");

    if (base <= 1)
    {
        throw std::logic_error("The base must be > 1.\n");
    }
    if (p < 3)
    {
        throw std::logic_error("The modulus must be > 2.\n");
    }
    if (arg < 1)
    {
        throw std::logic_error("The argument must be > 0.\n");
    }
    if (base >= p || arg >= p)
    {
        throw std::logic_error("Error computing the discrete log: Are your arguments in the wrong order?\n");
    }

    if (arg == 1)
    {
        return 0;
    }
    Z s = 1;
    for (Z i = 1; i < p; ++i)
    {
        s = (s * base) % p;
        if (s == arg)
        {
            return i;
        }
    }
    return {};
}

template<class Z>
class baby_step_giant_step_discrete_log
{
public:
    baby_step_giant_step_discrete_log(Z base, Z p) : m_p{p}
    {
        using std::numeric_limits;
        static_assert(numeric_limits<Z>::is_integer,
                      "The baby_step_giant_step discrete log works on integral types.\n");

        if (base <= 1)
        {
            throw std::logic_error("The base must be > 1.\n");
        }
        if (p < 3)
        {
            throw std::logic_error("The modulus must be > 2.\n");
        }
        if (base >= p)
        {
            throw std::logic_error("Error computing the discrete log: Are your arguments in the wrong order?\n");
        }
        m_root_p = floor_sqrt(p);
        if (m_root_p*m_root_p != p)
        {
            m_root_p += 1;
        }

        auto x = modular_multiplicative_inverse(base, p);
        if (!x)
        {
            throw std::logic_error("The gcd of the b and the modulus is > 1, hence the discrete log is not guaranteed to exist. If you don't require an existence proof, use trial multiplication.\n");
        }
        m_inv_base_pow_m = modular_exponentiation(x.value(), m_root_p, p);

        m_lookup_table.reserve(m_root_p);
        // Now the expensive part:
        Z k = 1;
        for (Z j = 0; j < m_root_p; ++j)
        {
            m_lookup_table.emplace(k, j);
            k = k*base % p;
        }

    }

    Z operator()(Z arg) const
    {
        Z ami = m_inv_base_pow_m;
        Z k = arg % m_p;
        if(k == 0)
        {
            throw std::domain_error("Cannot take the logarithm of a number divisible by the modulus.\n");
        }
        for (Z i = 0; i < m_root_p; ++i)
        {
            auto it = m_lookup_table.find(k);
            if (it != m_lookup_table.end())
            {
                return (i*m_root_p + it->second) % m_p;
            }
            ami = (ami*m_inv_base_pow_m) % m_p;
            k = k * ami % m_p;
        }
        // never should get here . . .
        return -1;
    }

private:
    Z m_p;
    Z m_root_p;
    Z m_inv_base_pow_m;
    std::unordered_map<Z, Z> m_lookup_table;
};


}}
#endif
