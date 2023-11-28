//
// Created by zou on 11/27/23.
//
#define BOOST_TEST_MODULE test_apron_interval
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/domain/numeric/apron.hpp>
#include <ikos/core/example/variable_factory.hpp>
#include <ikos/core/number/z_number.hpp>

using ZNumber = ikos::core::ZNumber;
using VariableFactory = ikos::core::example::VariableFactory;
using Variable = ikos::core::example::VariableFactory::VariableRef;
using VariableExpr = ikos::core::VariableExpression< ZNumber, Variable >;
using BinaryOperator = ikos::core::numeric::BinaryOperator;
using Bound = ikos::core::ZBound;
using Interval = ikos::core::numeric::ZInterval;
using Congruence = ikos::core::numeric::ZCongruence;
using IntervalCongruence = ikos::core::numeric::IntervalCongruence< ZNumber >;
using ApronDomain = ikos::core::numeric::
    ApronDomain< ikos::core::numeric::apron::Interval, ZNumber, Variable >;

// By zoush99
using FNumber = ikos::core::FNumber;
//using VariableFactory = ikos::core::example::VariableFactory;
using VariableExprF = ikos::core::VariableExpression< FNumber, Variable >;
using BoundF = ikos::core::FBound;
using IntervalF = ikos::core::numeric::FInterval;
//using Congruence = ikos::core::numeric::ZCongruence;
//using IntervalCongruence = ikos::core::numeric::IntervalCongruence< ZNumber >;
using ApronDomainF = ikos::core::numeric::
    ApronDomain< ikos::core::numeric::apron::Interval, FNumber, Variable >;

BOOST_AUTO_TEST_CASE(is_top_and_bottom_f) {
  VariableFactory vfac;
  Variable x(vfac.get("x"));

  BOOST_CHECK(ApronDomain::top().is_top());
  BOOST_CHECK(!ApronDomain::top().is_bottom());

  BOOST_CHECK(!ApronDomain::bottom().is_top());
  BOOST_CHECK(ApronDomain::bottom().is_bottom());

  auto inv = ApronDomain::top();
  BOOST_CHECK(inv.is_top());
  BOOST_CHECK(!inv.is_bottom());

}
