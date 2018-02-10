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
#include <boost/format.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/integer/common_factor_rt.hpp>
#include <boost/integer/mod_inverse.hpp>

namespace boost { namespace integer {

// base^^x = a mod p <-> x = log_base(a) mod p
template<class Z>
boost::optional<Z> trial_multiplication_discrete_log(Z base, Z arg, Z modulus)
{
    using std::numeric_limits;
    static_assert(numeric_limits<Z>::is_integer,
                 "The discrete log works on integral types.\n");

    if (base <= 1)
    {
        auto e = boost::format("The base b is %1%, but must be > 1.\n") % base;
        throw std::domain_error(e.str());
    }
    if (modulus < 3)
    {
        auto e = boost::format("The modulus must be > 2, but is %1%") % modulus;
        throw std::domain_error(e.str());
    }
    if (arg < 1)
    {
        auto e = boost::format("The argument must be > 0, but is %1%") % arg;
        throw std::domain_error(arg);
    }
    if (base >= modulus || arg >= modulus)
    {
        if (base >= modulus)
        {
            auto e = boost::format("Error computing the discrete log: The base %1% is greater than the modulus %2%. Are the arguments in the wrong order?") % base % modulus;
            throw std::domain_error(e.str());
        }
        if (arg >= p)
        {
            auto e = boost::format("Error computing the discrete log: The argument %1% is greater than the modulus %2%. Are the arguments in the wrong order?") % arg % modulus;
            throw std::domain_error(e.str());
        }
    }

    if (arg == 1)
    {
        return 0;
    }
    Z s = 1;
    for (Z i = 1; i < modulus; ++i)
    {
        s = (s * base) % modulus;
        if (s == arg)
        {
            // Maybe a bit trivial assertion. But still a negligible fraction of the total compute time.
            BOOST_ASSERT(arg == boost::multiprecision::powm(base, i, modulus));
            return i;
        }
    }
    return {};
}

template<class Z>
class bsgs_discrete_log
{
public:
    bsgs_discrete_log(Z base, Z modulus) : m_p{modulus}, m_base{base}
    {
        using std::numeric_limits;
        static_assert(numeric_limits<Z>::is_integer,
                      "The baby-step, giant-step discrete log works on integral types.\n");

        if (base <= 1)
        {
            throw std::logic_error("The base must be > 1.\n");
        }
        if (modulus < 3)
        {
            throw std::logic_error("The modulus must be > 2.\n");
        }
        if (base >= modulus)
        {
            throw std::logic_error("Error computing the discrete log: Are your arguments in the wrong order?\n");
        }
        m_root_p = boost::multiprecision::sqrt(modulus);
        if (m_root_p*m_root_p != modulus)
        {
            m_root_p += 1;
        }

        auto x = mod_inverse(base, modulus);
        if (!x)
        {
            auto d = boost::integer::gcd(base, modulus);
            auto e = boost::format("The gcd of the base %1% and the modulus %2% is %3% != 1, hence the discrete log is not guaranteed to exist, which breaks the baby-step giant step algorithm. If you don't require existence proof for all inputs, use trial multiplication.\n") % base % modulus % d;
            throw std::logic_error(e.str());
        }
        m_inv_base_pow_m = boost::multiprecision::powm(x.value(), m_root_p, modulus);

        m_lookup_table.reserve(m_root_p);
        // Now the expensive part:
        Z k = 1;
        for (Z j = 0; j < m_root_p; ++j)
        {
            m_lookup_table.emplace(k, j);
            k = k*base % modulus;
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
                Z log_b_arg = (i*m_root_p + it->second) % m_p;
                // This computation of the modular exponentiation is laughably quick relative to computing the discrete log.
                // Why not put an assert here for our peace of mind?
                BOOST_ASSERT(arg == boost::multiprecision::powm(m_base, log_b_arg, m_p));
                return log_b_arg;
            }
            ami = (ami*m_inv_base_pow_m) % m_p;
            k = k * ami % m_p;
        }
        // never should get here . . .
        BOOST_ASSERT(false);
        // Suppress compiler warnings.
        return -1;
    }

private:
    Z m_p;
    Z m_base;
    Z m_root_p;
    Z m_inv_base_pow_m;
    std::unordered_map<Z, Z> m_lookup_table;
};


}}
#endif
