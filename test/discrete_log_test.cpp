/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE discrete_log_test
#include <boost/test/included/unit_test.hpp>
#include <boost/integer/discrete_log.hpp>
#include <boost/math/special_functions/prime.hpp>


using boost::integer::trial_multiplication_discrete_log;
using boost::integer::bsgs_discrete_log;

template<class Z>
void test_trial_multiplication_discrete_log()
{
    std::cout << "Testing basic trial multiplication discrete logarithm on type " << boost::typeindex::type_id<Z>().pretty_name() << "\n";
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
    std::cout << "Testing basic baby-step giant-step discrete logarithm on type " << boost::typeindex::type_id<Z>().pretty_name() << "\n";
    bsgs_discrete_log<Z> dl_7(7, 41);
    BOOST_CHECK_EQUAL(dl_7(7).value(), 1);
    BOOST_CHECK_EQUAL(dl_7(8).value(), 2);
    BOOST_CHECK_EQUAL(dl_7(15).value(), 3);
    BOOST_CHECK_EQUAL(dl_7(23).value(), 4);
    BOOST_CHECK_EQUAL(dl_7(38).value(), 5);
    BOOST_CHECK_EQUAL(dl_7(20).value(), 6);
}

template<class Z>
void test_trial_multiplication_with_prime_modulus()
{
    std::cout << "Testing trial multiplication with prime modulus on type " << boost::typeindex::type_id<Z>().pretty_name() << "\n";
    for (Z i = 0; i < boost::math::max_prime; ++i)
    {
        Z modulus = boost::math::prime(i);
        for (Z base = 2; base < modulus; ++base)
        {
            for (Z arg = 1; arg < modulus; ++arg)
            {
                boost::optional<Z> dl = trial_multiplication_discrete_log(base, arg, modulus);
                if (dl)
                {
                    BOOST_CHECK_EQUAL(arg, boost::multiprecision::powm(base, dl.value(), modulus));
                }
            }
        }
    }
}


template<class Z>
void test_bsgs_with_prime_modulus()
{
    std::cout << "Testing baby-step, giant-step with prime modulus on type " << boost::typeindex::type_id<Z>().pretty_name() << "\n";
    for (Z i = 0; i < boost::math::max_prime; ++i)
    {
        Z p = boost::math::prime(i);
        for (Z j = 2; j < p; ++j)
        {
            bsgs_discrete_log<Z> dl_j(j, p);
            for (Z k = 1; k < p; ++k)
            {
                boost::optional<Z> dl = dl_j(k);
                if (dl)
                {
                    BOOST_CHECK_EQUAL(k, boost::multiprecision::powm(j, dl.value(), p));
                }
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(discrete_log_test)
{
    test_trial_multiplication_discrete_log<size_t>();
    test_bsgs_discrete_log<int>();
    test_trial_multiplication_with_prime_modulus<long long>();
    test_bsgs_with_prime_modulus<long long>();
}
