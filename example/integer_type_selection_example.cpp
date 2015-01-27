// boost integer_type_selection.cpp 

// Copyright Paul A. Bristow 2015
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Caution: this file contains Quickbook markup as well as code
// and comments, don't change any of the special comment markups!

#include <boost/integer.hpp>
#include <iostream> 
#include <limits>  // for numeric_limits min and max.
// Note use of extra brackets to avoid potential clash for any min and max macros:
// (std::numeric_limits<T>::max)()  (std::numeric_limits<T>::min)()

//! Show info about type
template <const int Bits, typename T>
void show_type()
{ 
  std::cout << typeid(T).name() 
    << " is a signed int using at least " << Bits << " bits uses "
    << std::numeric_limits<boost::int_t<Bits>::least>::digits 
    << " bits, needing at most "
    << std::numeric_limits<boost::int_t<Bits>::least>::digits10
    << " decimal digits, "    " and representing a maximum decimal value of "
    << static_cast<int>((std::numeric_limits<boost::int_t<Bits>::least>::max)())
    << std::endl;
} // template <const int Bits, typename T> void show_type()

template <typename T>
void show_consts()
{ // 
  std::cout << "Type " << typeid(T).name();
  if (std::numeric_limits<T>::is_specialized)
  {
    std::cout << " is specialized for std::numeric_limits,";
    if (std::numeric_limits<T>::is_integer)
    {
      std::cout << " and is integer type." << std::endl;
      // If a constant expression for `min` and `max` are required, see  
      // Boost integer_traits.
      std::cout << "const_max = " << boost::integer_traits<T>::const_max << std::endl;
      std::cout << "const_min = " << boost::integer_traits<T>::const_min << std::endl;
    }
  }
} // void show_consts()

template <typename T>
void show_type()
{
  std::cout << "Type " << typeid(T).name(); // name of resultant type.
  if (std::numeric_limits<T>::is_specialized)
  {
    if (std::numeric_limits<T>::is_integer)
    {
      std::cout << " is an unsigned int with at least 13 bits using "
      << std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0) << " bits,\n"
      // See http://en.cppreference.com/w/cpp/types/numeric_limits/digits for details on the meaning of digits10.
      // The value of std::numeric_limits<T>::digits is the number of digits in base-radix that can be represented 
      // by the type T without change. 
      // For integer types, this is the number of bits *not counting the sign bit*, so add one for the total.
      // (For floating-point types, this is the number of digits in the mantissa).
      "guaranteeing at most " << std::numeric_limits<T>::digits10 << " decimal digits precision,\n"
      "and using at most " << std::numeric_limits<T>::digits10 + 1
      << " decimal digits,\n"
      // See http://en.cppreference.com/w/cpp/types/numeric_limits/digits10 for details on the meaning of digits10.
      // The value of std::numeric_limits<T>::digits is the number of digits in base-radix that can be represented 
      // by the type T without change. 
      // For integer types, the maximum number of digits that may be required is one more than digits10.
      "a maximum decimal value of " << static_cast<long>((std::numeric_limits<T>::max)())
      << " and a minimum decimal value of " << static_cast<long>((std::numeric_limits<T>::min)()) << "."
      << std::endl;
   }
    else
    {
      std::cout << "is floating-point." << std::endl;
    }
  }
  else
  { //  is NOT specialized.
    std::cout << " is NOT specialized for std::numeric_limits!" << std::endl;
  }
} // template <typename T> void show_type()


template <typename T>
void show_type_limits()
{ // 

  std::cout <<"Type " << typeid(T).name();
  if (std::numeric_limits<T>::is_specialized)
  {
    std::cout << " is specialized for std::numeric_limits." << std::endl;
    if (std::numeric_limits<T>::is_integer)
      {
        std::cout << "is integer." << std::endl;

        std::cout << (std::numeric_limits<T>::is_bounded ? "is bounded." : "") << std::endl;
        std::cout << (std::numeric_limits<T>::is_exact ? "is exact." : "") << std::endl;
        std::cout << (std::numeric_limits<T>::is_modulo ? "is modulo." : "") << std::endl;
        std::cout << "radix = " << std::numeric_limits<T>::radix << std::endl;
        std::cout << (std::numeric_limits<T>::is_signed ? "is signed." : "is unsigned.") << std::endl;

        std::cout << "max = " << static_cast<long>((std::numeric_limits<T>::max)()) << std::endl;
        std::cout << "min = " << static_cast<long>((std::numeric_limits<T>::min)()) << std::endl;
        // Can't list const_max or const_min here because compiler will protest that
        // const_max' : is not a member of 'boost::integer_traits<T>' when T is double.
        //std::cout << "const_max = " << boost::integer_traits<T>::const_max << std::endl;
        //std::cout << "const_min = " << boost::integer_traits<T>::const_min << std::endl;

        std::cout << "digits = " << std::numeric_limits<T>::digits << std::endl;
        std::cout << "bits = " << std::numeric_limits<T>::digits +1 << std::endl;
        // digits is the number of bits not counting the sign bit for integer types.

        std::cout << "digits10 = " << std::numeric_limits<T>::digits10 << std::endl;
        // max_digits10 is not defined for integer types.
        //std::cout << "max_digits10 = " << std::numeric_limits<T>::max_digits10 << std::endl;
      }
      else
      { // Not integral, so might be floating-point, or ?
        std::cout << "is NOT integral type." << std::endl;
        if ((std::numeric_limits<T>::max_exponent != 0) && (std::numeric_limits<T>::max_exponent10 != 0))
        { // floating-point type including fundamental float, double and multiprecision like cpp_dec_float_50 and cpp_bin_float_50.
          std::cout << "is floating-point type." << std::endl;
          std::cout << "digits = " << std::numeric_limits<T>::digits << std::endl;
          // digits is the number of bits in the significand (not counting the sign bit) for floating-point types.
          std::cout << "digits10 = " << std::numeric_limits<T>::digits10 << std::endl;
          // http://en.cppreference.com/w/cpp/types/numeric_limits/digits10  
          std::cout << "max_digits10 = " << std::numeric_limits<T>::max_digits10 << std::endl;
          std::cout << "is_modulo = " << std::numeric_limits<T>::is_modulo << std::endl;
          std::cout << "is_iec559 = " << std::numeric_limits<T>::is_iec559 << std::endl;
          std::cout << (std::numeric_limits<T>::is_exact ? "is exact." : "") << std::endl;
          std::cout << (std::numeric_limits<T>::is_signed ? "is signed." : "is unsigned.") << std::endl;
          std::cout << "has_quiet_NaN = " << std::numeric_limits<T>::has_quiet_NaN << std::endl;
          std::cout << "has_infinity = " << std::numeric_limits<T>::has_infinity << std::endl;
          std::cout << "has_denorm_loss = " << std::numeric_limits<T>::has_denorm_loss << std::endl;
          std::cout << "max_exponent = " << std::numeric_limits<T>::max_exponent << std::endl;
          std::cout << "min_exponent = " << std::numeric_limits<T>::min_exponent << std::endl;
          std::cout << "max_exponent10 = " << std::numeric_limits<T>::max_exponent10 << std::endl;
          std::cout << "min_exponent10 = " << std::numeric_limits<T>::min_exponent10 << std::endl;
        }
        else
        { // Unknown type
          std::cout << "Unknown type." << std::endl;
        }
      }
  }
  else 
  { // Not specialized!
    std::cout << " is NOT specialized for std::numeric_limits!" << std::endl;
  }
} // show_type_limits


int main()
{
  try
  { 

// Select, construct and assign an unsigned integer of at least 13 bits.
//[integer_type_selection_1
     boost::uint_t<13>::least my_var13 = 42;  
//] [/integer_type_selection_1]

//[integer_type_selection_2
     show_type<boost::uint_t<13>::least>();
//] [/integer_type_selection_2]

    // Select fastest signed integer of at least 7 bits.
//[integer_type_selection_3
    typedef boost::int_t<7>::fast int_7; 
//] [/integer_type_selection_3]

//[integer_type_selection_4
    show_type<int_7>();
//] [/integer_type_selection_4]


  // Choose an integer size that can hold at least a value of 1000
  // Assignment of this value is guaranteed not to be truncated:
//[integer_value_type_selection_5

    boost::int_max_value_t<1000>::least thousand = 1000;
//] [/integer_value_type_selection_5]

    std::cout << thousand << std::endl;

//[integer_value_type_selection_6

    std::cout << (std::numeric_limits<boost::int_max_value_t<1000>::least>::max)() << std::endl;

//] [/integer_value_type_selection_6]

//[integer_value_type_selection_7

  thousand = 100000; // Probably too big!

  // warning C4305 :  warning C4305: '=' : truncation from 'int' to 'short'
  // warning C4309:  '='  : truncation of constant value

//] [/integer_value_type_selection_7]

//[integer_value_type_selection_8

    boost::int_t<32>::exact my_exact32 = 1000000;
  
    std::cout << "boost::int_t<32>::exact has "
      << std::numeric_limits<boost::int_t<32>::exact>::digits
      << " bits and 1 sign bit." << std::endl;
//  boost::int_t<32>::exact has 31 bits and 1 sign bit.

//] [/integer_value_type_selection_8]

// If we ask for an unachievable number of bits or value

    //boost::int_t<128>::exact exact128;
    //error C2338 : No suitable signed integer type with the requested number of bits is available.
    // see reference to class template instantiation 'boost::int_t<128>' being compiled

    show_consts<boost::int_t<32>::exact>();
    //  const_max = 2147483647  const_min = -2147483648

    show_type<16, boost::int_max_value_t<1000>::least>();

  }
  catch (std::exception ex)
  {
    std::cout << ex.what() << std::endl;
  }
  return 0;
} // int main


/*

//[integer_type_selection_output_1
Type short is an unsigned int with at least 13 bits using 16 bits,
guaranteeing at most 4 decimal digits precision,
and using at most 5 decimal digits,
//] [/integer_type_selection_output_1]

//[integer_type_selection_output_2
Type signed char is an unsigned int with at least 13 bits using 8 bits,
guaranteeing at most 2 decimal digits precision,
and using at most 3 decimal digits,
a maximum decimal value of 127 and a minimum decimal value of -128.
//] [/integer_type_selection_output_2]

*/