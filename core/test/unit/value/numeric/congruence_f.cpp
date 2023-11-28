//
// Created by zou on 11/28/23.
//
#define BOOST_TEST_MODULE test_congruence_f
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/value/numeric/congruence.hpp>

using namespace ikos::core;
using namespace ikos::core::numeric;


BOOST_AUTO_TEST_CASE(test_addition) {
  BOOST_CHECK(FCongruence(FNumber(2), FNumber(0)) + FCongruence(4) ==
              FCongruence(FNumber(2), FNumber(0)));
  BOOST_CHECK(FCongruence::top() + FCongruence(4) == FCongruence::top());
}


BOOST_AUTO_TEST_CASE(test_substract) {
  BOOST_CHECK(FCongruence(FNumber(2), FNumber(0)) - FCongruence(4) ==
              FCongruence(FNumber(2), FNumber(0)));
  BOOST_CHECK(FCongruence::top() - FCongruence(4) == FCongruence::top());
}

BOOST_AUTO_TEST_CASE(test_multiply) {
  BOOST_CHECK(FCongruence::bottom() * FCongruence(4) == FCongruence::bottom());

  BOOST_CHECK(FCongruence(2) * FCongruence::bottom() == FCongruence::bottom());
  BOOST_CHECK(FCongruence(2) * FCongruence(4) == FCongruence(8));
  BOOST_CHECK(FCongruence(2) * FCongruence(-4) == FCongruence(-8));
  BOOST_CHECK(FCongruence(7) * FCongruence(3) == FCongruence(21));
  BOOST_CHECK(FCongruence(7) * FCongruence(0) == FCongruence(0));
  BOOST_CHECK(FCongruence(4) * FCongruence(FNumber(2), FNumber(0)) ==
              FCongruence(FNumber(8), FNumber(0)));
  BOOST_CHECK(FCongruence(4) * FCongruence(FNumber(2), FNumber(1)) ==
              FCongruence(FNumber(8), FNumber(4)));
  BOOST_CHECK(FCongruence(4.5) * FCongruence(FNumber(2), FNumber(1)) ==
              FCongruence(FNumber(9), FNumber(4.5)));
  BOOST_CHECK(FCongruence(0) * FCongruence(FNumber(2), FNumber(0)) ==
              FCongruence(0));
  BOOST_CHECK(FCongruence(4) * FCongruence::top() ==
              FCongruence(FNumber(4), FNumber(0)));
  BOOST_CHECK(FCongruence(0) * FCongruence::top() == FCongruence(0));

  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) * FCongruence::bottom() ==
              FCongruence::bottom());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) * FCongruence(0) ==
              FCongruence(0));
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) * FCongruence(4) ==
              FCongruence(FNumber(20), FNumber(4)));
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) * FCongruence(-4) ==
              FCongruence(FNumber(20), FNumber(16)));
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) *
                  FCongruence(FNumber(2), FNumber(0)) ==
              FCongruence(FNumber(2), FNumber(0)));
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) *
                  FCongruence(FNumber(2), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) *
                  FCongruence(FNumber(10), FNumber(0)) ==
              FCongruence(FNumber(10), FNumber(0)));
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) *
                  FCongruence(FNumber(10), FNumber(2)) ==
              FCongruence(FNumber(10), FNumber(2)));
}

BOOST_AUTO_TEST_CASE(test_divide) {
  BOOST_CHECK(FCongruence::bottom() / FCongruence(4) == FCongruence::bottom());
  BOOST_CHECK(FCongruence::top() / FCongruence(4) == FCongruence::top());

  BOOST_CHECK(FCongruence(2) / FCongruence::bottom() == FCongruence::bottom());
  BOOST_CHECK(FCongruence(4) / FCongruence(2) == FCongruence(2));
  BOOST_CHECK(FCongruence(-4) / FCongruence(2) == FCongruence(-2));
  BOOST_CHECK(FCongruence(8) / FCongruence(-2) == FCongruence(-4));
  BOOST_CHECK(FCongruence(7) / FCongruence(0) == FCongruence::bottom());
  BOOST_CHECK(FCongruence(4) / FCongruence(FNumber(2), FNumber(0)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(4) / FCongruence(FNumber(2), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(0) / FCongruence(FNumber(2), FNumber(0)) ==
              FCongruence(0));
  BOOST_CHECK(FCongruence(-4) / FCongruence(FNumber(4), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(4) / FCongruence(FNumber(4), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(2) / FCongruence(FNumber(3), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(7) / FCongruence(FNumber(4), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(12) / FCongruence(FNumber(3), FNumber(2)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(6) / FCongruence(FNumber(6), FNumber(3)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(5) / FCongruence(FNumber(5), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(4) / FCongruence::top() == FCongruence::top());
  BOOST_CHECK(FCongruence(0) / FCongruence::top() == FCongruence(0));

  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) / FCongruence::bottom() ==
              FCongruence::bottom());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) / FCongruence(0) ==
              FCongruence::bottom());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) / FCongruence(4) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(4), FNumber(1)) / FCongruence(2) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) / FCongruence(-4) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(8), FNumber(1)) / FCongruence(4) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(8), FNumber(4)) / FCongruence(4) ==
              FCongruence(FNumber(2), FNumber(1)));
  BOOST_CHECK(FCongruence(FNumber(12), FNumber(7)) / FCongruence(3) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) /
                  FCongruence(FNumber(2), FNumber(0)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) /
                  FCongruence(FNumber(2), FNumber(1)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) /
                  FCongruence(FNumber(10), FNumber(0)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(5), FNumber(1)) /
                  FCongruence(FNumber(10), FNumber(2)) ==
              FCongruence::top());
  BOOST_CHECK(FCongruence(FNumber(2), FNumber(0)) / FCongruence(4) ==
              FCongruence::top());
}
