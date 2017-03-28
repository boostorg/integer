
//  (C) Copyright John Maddock 2017.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/integer/common_factor.hpp>

#ifndef BOOST_NO_CXX14_CONSTEXPR

void test_constexpr()
{
   constexpr const boost::int64_t i = 347 * 463 * 727;
   constexpr const boost::int64_t j = 191 * 347 * 281;

   constexpr const boost::int64_t k = boost::integer::gcd(i, j);
   constexpr const boost::int64_t l = boost::integer::lcm(i, j);

   static_assert(k == 347, "Expected result not found in constexpr gcd.");
   static_assert(l == 6268802158037, "Expected result not found in constexpr lcm.");
}

#endif

#ifndef BOOST_NO_CXX11_NOEXCEPT

void test_noexcept()
{
   static_assert(noexcept(boost::integer::gcd(static_cast<unsigned char>(2), static_cast<unsigned char>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<char>(2), static_cast<char>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<signed char>(2), static_cast<signed char>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<short>(2), static_cast<short>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<unsigned short>(2), static_cast<unsigned short>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<int>(2), static_cast<int>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<unsigned int>(2), static_cast<unsigned int>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<long>(2), static_cast<long>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<unsigned long>(2), static_cast<unsigned long>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<long long>(2), static_cast<long long>(4))), "Expected a noexcept function.");
   static_assert(noexcept(boost::integer::gcd(static_cast<unsigned long long>(2), static_cast<unsigned long long>(4))), "Expected a noexcept function.");
}

#endif
