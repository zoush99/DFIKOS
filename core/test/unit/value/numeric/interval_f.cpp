//
// Created by zou on 11/28/23.
//

#define BOOST_TEST_MODULE test_interval
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/value/numeric/interval.hpp>

using namespace ikos::core;
using namespace ikos::core::numeric;

BOOST_AUTO_TEST_CASE(test_arithmetic) {
  BOOST_CHECK(FInterval(4) + FInterval(5) == FInterval(9));
  BOOST_CHECK(FInterval(4) + FInterval::top() == FInterval::top());
  BOOST_CHECK(FInterval(4) + FInterval::bottom() == FInterval::bottom());
  BOOST_CHECK(FInterval(4.2) + FInterval(2.4) == FInterval(6.6));
  BOOST_CHECK(FInterval(4.2) + FInterval::top() == FInterval::top());
  BOOST_CHECK(FInterval(4.2) + FInterval::bottom() == FInterval::bottom());
  BOOST_CHECK(FInterval(FBound(1), FBound(3)) +
                  FInterval(FBound(2), FBound(4)) ==
              FInterval(FBound(3), FBound(7)));
  BOOST_CHECK(FInterval(FBound(-1), FBound(3)) +
                  FInterval(FBound(2), FBound(4)) ==
              FInterval(FBound(1), FBound(7)));
  BOOST_CHECK(FInterval(FBound(-1), FBound(3)) -
                  FInterval(FBound(2), FBound(4)) ==
              FInterval(FBound(-5), FBound(1)));
  BOOST_CHECK(FInterval(FBound(-1.5), FBound(3)) -
                  FInterval(FBound(2.5), FBound(4.5)) ==
              FInterval(FBound(-6), FBound(0.5)));
  BOOST_CHECK(FInterval(FBound(-3), FBound(4)) *
                  FInterval(FBound(-2), FBound(0)) ==
              FInterval(FBound(-8), FBound(6)));
  BOOST_CHECK(FInterval(FBound(-3), FBound(4)) *
                  FInterval(FBound(-2.5), FBound(2.5)) ==
              FInterval(FBound(-10), FBound(10)));
  BOOST_CHECK(FInterval(4) / FInterval::bottom() == FInterval::bottom());
  BOOST_CHECK(FInterval::bottom() / FInterval(2) == FInterval::bottom());
  BOOST_CHECK(FInterval::top() / FInterval(0) == FInterval::bottom());
  BOOST_CHECK(FInterval(4) / FInterval(2) == FInterval(2));
  BOOST_CHECK(FInterval(3) / FInterval(2) == FInterval(1.5));
  BOOST_CHECK(FInterval(-3) / FInterval(2) == FInterval(-1.5));
  BOOST_CHECK(FInterval(FBound(1), FBound(3)) / FInterval(2) ==
              FInterval(FBound(0.5), FBound(1.5)));
  BOOST_CHECK(FInterval(FBound(2), FBound(7)) / FInterval(2) ==
              FInterval(FBound(1), FBound(3.5)));
  BOOST_CHECK(FInterval(FBound(-3), FBound(3)) / FInterval(2) ==
              FInterval(FBound(-1.5), FBound(1.5)));
  BOOST_CHECK(FInterval(FBound(-3), FBound::plus_infinity()) / FInterval(2) ==
              FInterval(FBound(-1.5), FBound::plus_infinity()));
  BOOST_CHECK(FInterval(FBound::minus_infinity(), FBound(3)) / FInterval(2) ==
              FInterval(FBound::minus_infinity(), FBound(1.5)));
  BOOST_CHECK(FInterval(FBound(1), FBound(3)) /
                  FInterval(FBound(1), FBound(2)) ==
              FInterval(FBound(0.5), FBound(3)));
  BOOST_CHECK(FInterval(FBound(-3), FBound(3)) /
                  FInterval(FBound(1), FBound(2)) ==
              FInterval(FBound(-3), FBound(3)));
  BOOST_CHECK(FInterval(FBound(2), FBound(7)) /
                  FInterval(FBound(-2), FBound(3)) ==
              FInterval::top());
  BOOST_CHECK(FInterval(FBound(-2), FBound(7)) /
                  FInterval(FBound(-2), FBound(3)) ==
              FInterval::top());
  BOOST_CHECK(FInterval(FBound::minus_infinity(), FBound(7)) /
                  FInterval(FBound(-2), FBound(3)) ==
              FInterval::top());
  BOOST_CHECK(FInterval(FBound(-2), FBound::plus_infinity()) /
                  FInterval(FBound(-2), FBound(3)) ==
              FInterval::top());
  BOOST_CHECK(FInterval(FBound(-2), FBound(7)) /
                  FInterval(FBound::minus_infinity(), FBound(3)) ==
              FInterval::top());
  BOOST_CHECK(FInterval(FBound(-2), FBound(7)) /
                  FInterval(FBound(-2), FBound::plus_infinity()) ==
              FInterval::top());
  BOOST_CHECK(FInterval(FBound(-6), FBound(-3)) /
                  FInterval(FBound(3), FBound(12)) ==
              FInterval(FBound(-2), FBound(-0.25)));
  BOOST_CHECK(FInterval(FBound(-6), FBound(6)) /
                  FInterval(FBound(3), FBound(9)) ==
              FInterval(FBound(-2), FBound(2)));
  BOOST_CHECK(-FInterval(FBound(-3.5),FBound(4.5))==FInterval(FBound(-4.5),FBound(3.5)));
  BOOST_CHECK(FInterval(FNumber(3.5))==FInterval(3.5));
}

BOOST_AUTO_TEST_CASE(test_widening_threshold) {
  BOOST_CHECK(
      FInterval(FBound(0), FBound(0))
          .widening_threshold(FInterval(FBound(-1), FBound(0)), FNumber(-47)) ==
      FInterval(FBound(-47), FBound(0)));
  BOOST_CHECK(
      FInterval(FBound::minus_infinity(), FBound(0))
          .widening_threshold(FInterval(FBound(0), FBound(1)), FNumber(3)) ==
      FInterval(FBound::minus_infinity(), FBound(3)));
  BOOST_CHECK(
      FInterval(FBound::minus_infinity(), FBound(0))
          .widening_threshold(FInterval(FBound::minus_infinity(), FBound(47)),
                              FNumber(42)) ==
      FInterval(FBound::minus_infinity(), FBound::plus_infinity()));
  BOOST_CHECK(
      FInterval(FBound(0), FBound(0))
          .widening_threshold(FInterval(FBound(-1), FBound(0)), FNumber(-1)) ==
      FInterval(FBound(-1), FBound(0)));
}

BOOST_AUTO_TEST_CASE(test_narrowing_threshold) {
  BOOST_CHECK(
      FInterval(FBound(0), FBound::plus_infinity())
          .narrowing_threshold(FInterval(FBound(0), FBound(10)), FNumber(20)) ==
      FInterval(FBound(0), FBound(10)));
  BOOST_CHECK(
      FInterval(FBound(0), FBound(20))
          .narrowing_threshold(FInterval(FBound(0), FBound(10)), FNumber(20)) ==
      FInterval(FBound(0), FBound(10)));
  BOOST_CHECK(
      FInterval(FBound(0), FBound(30))
          .narrowing_threshold(FInterval(FBound(0), FBound(10)), FNumber(20)) ==
      FInterval(FBound(0), FBound(30)));
  BOOST_CHECK(FInterval(FBound::minus_infinity(), FBound(0))
                  .narrowing_threshold(FInterval(FBound(-10), FBound(0)),
                                       FNumber(-20)) ==
              FInterval(FBound(-10), FBound(0)));
  BOOST_CHECK(FInterval(FBound(-20), FBound(0))
                  .narrowing_threshold(FInterval(FBound(-10), FBound(0)),
                                       FNumber(-20)) ==
              FInterval(FBound(-10), FBound(0)));
  BOOST_CHECK(FInterval(FBound(-30), FBound(0))
                  .narrowing_threshold(FInterval(FBound(-10), FBound(0)),
                                       FNumber(-20)) ==
              FInterval(FBound(-30), FBound(0)));
  BOOST_CHECK(
      FInterval(FBound::minus_infinity(), FBound::plus_infinity())
          .narrowing_threshold(FInterval(FBound(0), FBound(10)), FNumber(20)) ==
      FInterval(FBound(0), FBound(10)));
  BOOST_CHECK(
      FInterval(FBound(-20), FBound(20))
          .narrowing_threshold(FInterval(FBound(0), FBound(10)), FNumber(20)) ==
      FInterval(FBound(-20), FBound(10)));
  BOOST_CHECK(FInterval(FBound(-20), FBound(20))
                  .narrowing_threshold(FInterval(FBound(0), FBound(10)),
                                       FNumber(-20)) ==
              FInterval(FBound(0), FBound(20)));
}
