//
// Created by zou on 11/21/23.
//
#define BOOST_TEST_MODULE test_f_number
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/version.hpp>

#if BOOST_VERSION >= 107100
#include <boost/test/tools/output_test_stream.hpp>
#else
#include <boost/test/output_test_stream.hpp>
#endif
#include <ikos/core/number/q_number.hpp>
#include <ikos/core/number/f_number.hpp>

BOOST_AUTO_TEST_CASE(test_f_number) {
  using Z = ikos::core::ZNumber;
  using Q = ikos::core::QNumber;
  using F=ikos::core::FNumber;
  using NumberError = ikos::core::NumberError;

  // Constructor
  BOOST_CHECK(F(1)==F());
  BOOST_CHECK(F(1)+F(2)==F(3));
  BOOST_CHECK(-F(1)==F(-1));
  BOOST_CHECK(F(-1).absolute()==F(1));

  BOOST_CHECK(F(1).signcast()==F(-1));
}