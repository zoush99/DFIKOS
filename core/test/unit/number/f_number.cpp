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
#include <ikos/core/number/f_number.hpp>
#include <ikos/core/number/q_number.hpp>

BOOST_AUTO_TEST_CASE(test_f_number) {
  using Z = ikos::core::ZNumber;
  using Q = ikos::core::QNumber;
  using F = ikos::core::FNumber;
  using NumberError = ikos::core::NumberError;

  mpfr_t _n;
  mpfr_init2(_n, 53);
  mpfr_set_d(_n, 1.2, MPFR_RNDN);
  int _i;
  _i = 1024;
  float _f;
  _f = 3.14;
  std::string str;
  str="3.14";
  F _F(_f);
  F _E;

  // Constructor
  BOOST_CHECK(F(1) == F());
  BOOST_CHECK(F(1).FNprec() == 24);
  BOOST_CHECK(F(1.2).FNprec() == 53);
  BOOST_CHECK(F(1.2) == 1.2);
  BOOST_CHECK(F(_n, MPFR_RNDN) == F(1.2));
  BOOST_CHECK(F(_i).FNprec() == 24);
  BOOST_CHECK(F(static_cast< long int >(_i)).FNprec() == 53);
  BOOST_CHECK(F(static_cast< long long int >(_i)).FNprec() == 113);
  BOOST_CHECK(F(_f).FNprec()==24);
  BOOST_CHECK(F(static_cast<double>(_f)).FNprec()==53);
  BOOST_CHECK(F(static_cast<long double>(_f)).FNprec()==113);
  /// \todo bugs here!!!
//  BOOST_CHECK(_F.from_string(str,10)==F(static_cast<double>(_f)));
//  BOOST_CHECK(_F.to_string(10)==str);
  // bugs here!!!
  BOOST_CHECK(_F==(_E=_F));
  BOOST_CHECK(_F==(_E=_f));
  //  BOOST_CHECK(F(1) + F(2) == F(3));
  //  BOOST_CHECK(-F(1) == F(-1));
  //  BOOST_CHECK(F(-1).absolute() == F(1));
  //  BOOST_CHECK(false == F(1).is_zero());
  //  BOOST_CHECK(F(1).signcast() == F(-1));
}