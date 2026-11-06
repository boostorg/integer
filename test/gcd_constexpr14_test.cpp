
//  (C) Copyright John Maddock 2017.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

#include <boost/integer/common_factor.hpp>
#include <limits>

#ifndef BOOST_NO_CXX14_CONSTEXPR

void test_constexpr1()
{
   constexpr const boost::int64_t i = 347 * 463 * 727;
   constexpr const boost::int64_t j = 191 * 347 * 281;

   constexpr const boost::int64_t k = boost::integer::gcd(i, j);
   constexpr const boost::int64_t l = boost::integer::lcm(i, j);

   static_assert(k == 347, "Expected result not integer in constexpr gcd.");
   static_assert(l == 6268802158037, "Expected result not integer in constexpr lcm.");
}

void test_constexpr2()
{
   constexpr const boost::uint64_t i = 347 * 463 * 727;
   constexpr const boost::uint64_t j = 191 * 347 * 281;

   constexpr const boost::uint64_t k = boost::integer::gcd(i, j);
   constexpr const boost::uint64_t l = boost::integer::lcm(i, j);

   static_assert(k == 347, "Expected result not integer in constexpr gcd.");
   static_assert(l == 6268802158037, "Expected result not integer in constexpr lcm.");
}

void test_constexpr3()
{
   constexpr const boost::uint64_t i = 347 * 463 * 727;
   constexpr const boost::uint64_t j = 191 * 347 * 281;

   constexpr const boost::uint64_t k = boost::integer::gcd_detail::Euclid_gcd(i, j);

   static_assert(k == 347, "Expected result not integer in constexpr gcd.");
}

void test_constexpr4()
{
   constexpr const boost::uint64_t i = 347 * 463 * 727;
   constexpr const boost::uint64_t j = 191 * 347 * 281;

   constexpr const boost::uint64_t k = boost::integer::gcd_detail::mixed_binary_gcd(i, j);

   static_assert(k == 347, "Expected result not integer in constexpr gcd.");
}

void test_constexpr5()
{
   constexpr const boost::uint64_t i = 347 * 463 * 727;
   constexpr const boost::uint64_t j = 191 * 347 * 281;

   constexpr const boost::uint64_t k = boost::integer::gcd_detail::Stein_gcd(i, j);

   static_assert(k == 347, "Expected result not integer in constexpr gcd.");
}

void test_constexpr_minimum_unit()
{
   constexpr int minimum = (std::numeric_limits<int>::min)();
   static_assert(boost::integer::gcd(minimum, -1) == 1, "Expected gcd(min, -1) == 1.");
   static_assert(boost::integer::gcd(-1, minimum) == 1, "Expected gcd(-1, min) == 1.");

   constexpr boost::int64_t minimum64 = (std::numeric_limits<boost::int64_t>::min)();
   static_assert(boost::integer::gcd(minimum64, boost::int64_t(-1)) == 1, "Expected gcd(min64, -1) == 1.");
   static_assert(boost::integer::gcd(boost::int64_t(-1), minimum64) == 1, "Expected gcd(-1, min64) == 1.");
}

void test_constexpr_unsigned_maximum()
{
   // The minimum of an unsigned type is zero and unsigned(-1) is its maximum.
   constexpr unsigned maximum = (std::numeric_limits<unsigned>::max)();
   static_assert(boost::integer::gcd(0u, maximum) == maximum, "Expected gcd(0, max) == max.");
   static_assert(boost::integer::gcd(maximum, 0u) == maximum, "Expected gcd(max, 0) == max.");

   constexpr boost::uint64_t maximum64 = (std::numeric_limits<boost::uint64_t>::max)();
   static_assert(boost::integer::gcd(boost::uint64_t(0), maximum64) == maximum64, "Expected gcd(0, max64) == max64.");
   static_assert(boost::integer::gcd(maximum64, boost::uint64_t(0)) == maximum64, "Expected gcd(max64, 0) == max64.");
}
#endif


