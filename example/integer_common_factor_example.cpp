// boost integer_common_factor_example.cpp 

// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Caution: this file contains Quickbook markup as well as code
// and comments, don't change any of the special comment markups!

//[integer_common_factor_example_0

// #include <boost/integer/common_factor.hpp>

#include <boost/integer/common_factor_ct.hpp> // For compile-time GCD & LCM Determination
#include <boost/integer/common_factor_rt.hpp> // For run-time GCD & LCM Determination

//] [/integer_common_factor_example_0]
#include <iostream>
#include <algorithm>
#include <iterator>

#include <limits>  // for numeric_limits min and max.

int main()
{
//[integer_common_factor_example_1
  std::cout << "The run-time GCD and LCM of 6 and 15 are "
    << boost::integer::gcd(6, 15) << " and "
    << boost::integer::lcm(6, 15) << ", respectively."
    << std::endl;
  // The GCD and LCM of 6 and 15 are 3 and 30, respectively.
//] [/integer_common_factor_example_1]

//[integer_common_factor_example_2

  std::cout << "The compile-time GCD and LCM of 8 and 9 are "
    << boost::integer::static_gcd<8, 9>::value
    << " and "
    << boost::integer::static_lcm<8, 9>::value
    << ", respectively." << std::endl;
  // The GCD and LCM of 8 and 9 are 1 and 72, respectively.
//] [/integer_common_factor_example_2]

//[integer_common_factor_example_3
  int  a[] = { 4, 5, 6 }, b[] = { 7, 8, 9 }, c[3];
  std::transform(a, a + 3, b, c, boost::integer::gcd_evaluator<int>());
  std::copy(c, c + 3, std::ostream_iterator<int>(std::cout, " "));
//] [/integer_common_factor_example_3]

} // int main

/*
//[integer_common_factor_example_output
The run-time GCD and LCM of 6 and 15 are 3 and 30, respectively.
The compile-time GCD and LCM of 8 and 9 are 1 and 72, respectively.
1 1 3
//] [/integer_common_factor_example_output]
*/
