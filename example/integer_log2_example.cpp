// boost integer_log2_example.cpp 

// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Caution: this file contains Quickbook markup as well as code
// and comments, don't change any of the special comment markups!

//[integer_log2_example_0
#include <boost/integer/static_log2.hpp> // For boost::static_log2
//] [/integer_log2s_example_0]
#include <iostream> 
#include <limits>  // for numeric_limits min and max.

//[integer_log2_example_
//] [/integer_log2s_example_]

int main()
{
//[integer_log2_example_1
  int n = boost::static_log2<256>::value;
//] [/integer_log2_example_1]

  std::cout << n << std::endl; // 8

  //[integer_log2_example_2
  int n2 = boost::static_log2<65536>::value;
//] [/integer_log2_example_2]

  std::cout << n2 << std::endl; // 16

} // int main

/*
//[integer_log2_example_output
8
//] [/integer_log2_example_output]
*/
