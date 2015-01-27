// boost integer_static_minmax_example.cpp 

// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Caution: this file contains Quickbook markup as well as code
// and comments, don't change any of the special comment markups!

#include <boost/integer/static_min_max.hpp> // For boost::static_signed_min
#include <iostream> 
#include <limits>  // for numeric_limits min and max.

//[integer_min_max_example_0

template < unsigned long AddendSize1, unsigned long AddendSize2 >
class adder
{
public:
  static  unsigned long  const  addend1_size = AddendSize1;
  static  unsigned long  const  addend2_size = AddendSize2;
  static  unsigned long  const  sum_size = boost::static_unsigned_max<AddendSize1, AddendSize2>::value + 1;

  typedef int  addend1_type[addend1_size];
  typedef int  addend2_type[addend2_size];
  typedef int  sum_type[sum_size];

  void  operator ()(addend1_type const &a1, addend2_type const &a2, sum_type &s) const;
}; // class adder

//] [/integer_min_max_example_0]

int main()
{
//[integer_min_max_example_1

  std::cout << "boost::static_signed_min< 9, 14>::value = "<< boost::static_signed_min< 9, 14>::value << std::endl;
  std::cout << "boost::static_signed_max< 9, 14>::value = "<< boost::static_signed_max< 9, 14>::value << std::endl;

//] [/integer_min_max_example_1]

//[integer_min_max_example_2
  int const   a1[] = { 0, 4, 3 };  // 340
  int const   a2[] = { 9, 8 };     //  89
  int         s[4];

  adder<3, 2>  obj;
  // adder<sizeof(a1), sizeof(a2)>  obj;

  std::cout << "obj.addend1_size = " << obj.addend1_size << std::endl; // 3
  std::cout << "obj.addend2_size = " << obj.addend2_size << std::endl; // 2
  std::cout << "obj.sum_size = " << obj.sum_size << std::endl; // 4
//] [/integer_min_max_example_2]

  // obj(a1, a2, s);  // 's' should be 429 or { 9, 2, 4, 0 }
  //void adder<3,2>::operator()(int const (&)[3],int const (&)[2],int (&)[4])const 

  std::cout << s[0] << s[1]  << s[2] << s[3]<< std::endl; // 's' should be 429 or { 9, 2, 4, 0 }

} // int main

/*
//[integer_min_max_example_output

boost::static_signed_min< 9, 14>::value = 9
boost::static_signed_max< 9, 14>::value = 14
obj.addend1_size = 3
obj.addend2_size = 2
obj.sum_size = 4
//] [/integer_min_max_example_output]
*/
