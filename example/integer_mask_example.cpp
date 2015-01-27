// boost integer_mask_example.cpp 

// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Caution: this file contains Quickbook markup as well as code
// and comments, don't change any of the special comment markups!

//[integer_mask_example_0
#include <boost/integer/integer_mask.hpp> // For boost::high_bit_mask_t etc
//] [/integer_masks_example_0]
#include <iostream> 
#include <limits>  // for numeric_limits min and max.

//[integer_mask_example_
//] [/integer_masks_example_]

int main()
{
//[integer_mask_example_1
  typedef boost::high_bit_mask_t<29>  mask1_type;
  typedef boost::low_bits_mask_t<15>  mask2_type;
//] [/integer_masks_example_1]

//[integer_mask_example_2
  // high_bit_mask_t
  std::cout << std::hex << mask1_type::bit_position << std::endl; // 1d
  std::cout << std::hex << mask1_type::high_bit << std::endl; // 20000000
  std::cout << std::hex << mask1_type::high_bit_fast << std::endl; // 20000000

  // low_bits_mask_t
  std::cout << std::hex << mask2_type::bit_count << std::endl; // F
  std::cout << std::hex << mask2_type::sig_bits << std::endl; // 7fff
  std::cout << std::hex << mask2_type::sig_bits_fast << std::endl; // 7fff
//] [/integer_masks_example_2]

//[integer_mask_example_3
  mask1_type::least  my_var1;
  mask2_type::fast   my_var2;
//] [/integer_masks_example_3]

//[integer_mask_example_4
  my_var1 |= mask1_type::high_bit;
  std::cout << std::hex << my_var1 << std::endl; // eccccccc
//] [/integer_masks_example_4]

//[integer_mask_example_5
  my_var2 &= mask2_type::sig_bits;
  std::cout << std::hex << my_var2 << std::endl; // 4ccc
//] [/integer_masks_example_5]

} // int main

/*
//[integer_mask_example_output
1d
20000000
20000000
f
7fff
7fff
eccccccc
4ccc
//] [/integer_mask_example_output]

*/
