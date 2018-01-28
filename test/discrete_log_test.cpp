/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE discrete_log_test
#include <boost/test/included/unit_test.hpp>
#include <boost/integer/discrete_log.hpp>


using boost::integer::trial_multiplication_discrete_log;
using boost::integer::baby_step_giant_step_discrete_log;

template<class Z>
void test_trial_multiplication_discrete_log()
{

    boost::optional<Z> x = trial_multiplication_discrete_log<Z>(2, 1, 3);
    BOOST_CHECK_EQUAL(0, x.value());
    x = trial_multiplication_discrete_log<Z>(2, 2, 3);
    BOOST_CHECK_EQUAL(1, x.value());

    x = trial_multiplication_discrete_log<Z>(2, 1, 4);
    BOOST_CHECK_EQUAL(0, x.value());

    x = trial_multiplication_discrete_log<Z>(2, 2, 4);
    BOOST_CHECK_EQUAL(1, x.value());

    // No solution to 2^^x mod 4 = 3:
    x = trial_multiplication_discrete_log<Z>(2, 3, 4);
    BOOST_TEST(!x);

    x = trial_multiplication_discrete_log<Z>(7, 7, 41);
    BOOST_CHECK_EQUAL(1, x.value());
    x = trial_multiplication_discrete_log<Z>(7, 8, 41);
    BOOST_CHECK_EQUAL(2, x.value());
    x = trial_multiplication_discrete_log<Z>(7, 15, 41);
    BOOST_CHECK_EQUAL(3, x.value());
    x = trial_multiplication_discrete_log<Z>(7, 23, 41);
    BOOST_CHECK_EQUAL(4, x.value());
    x = trial_multiplication_discrete_log<Z>(7, 38, 41);
    BOOST_CHECK_EQUAL(5, x.value());
    x = trial_multiplication_discrete_log<Z>(7, 20, 41);
    BOOST_CHECK_EQUAL(6, x.value());


    Z k = 1;
    for (Z i = 0; i < 40; ++i)
    {
        x = trial_multiplication_discrete_log<Z>(7, k, 41);
        BOOST_CHECK_EQUAL(i, x.value());
        k = (7*k) % 41;
    }
}

template<class Z>
void test_bsgs_discrete_log()
{
    baby_step_giant_step_discrete_log<Z> dl(7, 41);
    BOOST_CHECK_EQUAL(dl(7), 1);
    BOOST_CHECK_EQUAL(dl(8), 2);
    BOOST_CHECK_EQUAL(dl(15), 3);
    BOOST_CHECK_EQUAL(dl(23), 4);
    BOOST_CHECK_EQUAL(dl(38), 5);
    BOOST_CHECK_EQUAL(dl(20), 6);
}


BOOST_AUTO_TEST_CASE(discrete_log_test)
{
    test_trial_multiplication_discrete_log<size_t>();
    test_bsgs_discrete_log<int>();
}
