//  Boost static_log2.hpp header file  ------------------------------- //

//  Copyright (C) 2003 Vesa Karvonen.
//  Copyright (C) 2001 Daryle Walker.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.
//
//  --------------------------------------------------------
//  See http://www.boost.org/libs/integer for documentation.
//  --------------------------------------------------------------------------- //

#ifndef BOOST_INTEGER_STATIC_LOG2_HPP
#define BOOST_INTEGER_STATIC_LOG2_HPP


#include "boost/config.hpp" // for BOOST_STATIC_CONSTANT

namespace boost {

 typedef unsigned long static_log2_argument_type;
 typedef int           static_log2_result_type;

 namespace detail {

     namespace log2_impl {

     // choose_initial_n<>
     //
     // Choose an initial value of n for the core template.
     // If we call MAX the maximum value for static_log2_argument_type
     // (for instance, ULONG_MAX) that initial value n is the power of
     // two that satisfies the following relation:
     //
     //    n           2n                  p
     //   2  < MAX <= 2   - 1       [ n = 2  , p >= 4 ]
     //
     // Example: if on your platform unsigned longs have 48 value bits
     //          then n = 32 is chosen (p=5).
     //
     // It's easy to prove that, with such a choice, the core algorithm
     // works correctly for any width of static_log2_argument_type (not
     // only powers of two) and that recursion always terminates with
     // x = 1 and n = 0.

     // argument_type must be unsigned and have a width > 16 (this
     // is guaranteed e.g. for unsigned long). Under that restriction,
     // it can be changed in the future if larger types will be
     // standardized, without affecting the rest of the code.

     typedef static_log2_argument_type argument_type;
     typedef static_log2_result_type   result_type;


     template <result_type n>
         struct choose_initial_n {

         enum { c = (argument_type(1) << n << n) != 0 };
         BOOST_STATIC_CONSTANT(result_type, value = !c*n + choose_initial_n<2*c*n>::value);

     };

     template <>
         struct choose_initial_n<0> {
         BOOST_STATIC_CONSTANT(result_type, value = 0);
     };


     const result_type minimum_arg_type_width = 32;
     const result_type initial_n = choose_initial_n<minimum_arg_type_width/2>::value;

     template <argument_type x, result_type n = initial_n>
     struct static_log2_impl {

         enum { c = (x >> n) > 0 }; // x >= 2**n ?
         BOOST_STATIC_CONSTANT(result_type, value = c*n + (static_log2_impl< (x>>c*n), n/2 >::value) );
     };

     template <>
     struct static_log2_impl<1, 0> {
        BOOST_STATIC_CONSTANT(result_type, value = 0);
     };

     }
 } // detail



 // --------------------------------------
 // static_log2<x>
 // ----------------------------------------

 template <static_log2_argument_type x>
    struct static_log2 {

     BOOST_STATIC_CONSTANT
         (static_log2_result_type, value = detail::log2_impl::static_log2_impl<x>::value);
 };

 template <>
     struct static_log2<0> { };

}



#endif // include guard
