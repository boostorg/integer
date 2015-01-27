// boost integer_traits_example.cpp 

// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Caution: this file contains Quickbook markup as well as code
// and comments, don't change any of the special comment markups!

#include <boost/integer_traits.hpp>
#include <iostream> 
#include <limits>  // for numeric_limits min and max.

//[integer_traits_example_1
template<int N>
void f()
{ // Entirely contrived templated function.
  std::cout << N << std::endl; // Do something pointless.
}
//] [/integer_traits_example_1]


int main()
{
  std::cout << "Type int, min =  " 
    << (std::numeric_limits<int>::min)() 
    << ", const_min =  " << boost::integer_traits<int>::const_min
    << std::endl; // Type int, min =  -2147483648, const_min =  -2147483648

//[integer_traits_example_2
  f<2>();
//] [/integer_traits_example_2]

//[integer_traits_example_3
  int i = 2;
 // f<i>(); // A local variable cannot be used as a non-type argument.
//] [/integer_traits_example_3]

//[integer_traits_example_4
  const int ci = 2;
  f<ci>(); // But a const variable can.
//] [/integer_traits_example_4]
//[integer_traits_example_5

  // f<std::numeric_limits<int>::min()>(); // Function call must have a constant value in a constant expression.
//] [/integer_traits_example_5]
//[integer_traits_example_6

  f<boost::integer_traits<int>::const_min>();
//] [/integer_traits_example_6]

} // int main

