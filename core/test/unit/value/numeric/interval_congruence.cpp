//
// Created by zou on 11/28/23.
//
#define BOOST_TEST_MODULE test_interval_congruence
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/value/numeric/interval_congruence.hpp>

using namespace ikos::core;
using namespace ikos::core::numeric;

BOOST_AUTO_TEST_CASE(test_join) {
  BOOST_CHECK(ZCongruence(2).join(ZCongruence(4)) ==
              ZCongruence(ZNumber(2), ZNumber(0)));
  BOOST_CHECK(ZCongruence(1).join(ZCongruence(3)) ==
              ZCongruence(ZNumber(2), ZNumber(1)));
  BOOST_CHECK(ZCongruence(ZNumber(2), ZNumber(0))
                  .join(ZCongruence(ZNumber(2), ZNumber(1))) ==
              ZCongruence::top());
}