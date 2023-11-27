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
  str = "3.14";

  F _F(_f);
  F _E;
  F _G(_f);

  // Constructor
  BOOST_CHECK(F(1) == F());
  BOOST_CHECK(F(1).FNprec() == 24);
  BOOST_CHECK(F(1.2).FNprec() == 53);
  BOOST_CHECK(F(1.2) == 1.2);
  BOOST_CHECK(F(_n, MPFR_RNDN) == F(1.2));
  BOOST_CHECK(F(_i).FNprec() == 24);
  BOOST_CHECK(F(static_cast< long int >(_i)).FNprec() == 53);
  BOOST_CHECK(F(static_cast< long long int >(_i)).FNprec() == 113);
  BOOST_CHECK(F(_f).FNprec() == 24);
  BOOST_CHECK(F(static_cast< double >(_f)).FNprec() == 53);
  BOOST_CHECK(F(static_cast< long double >(_f)).FNprec() == 113);
  BOOST_CHECK(F::from_string("3.14",10)==F(3.14));
  BOOST_CHECK(F(10.12).to_string()=="10.12");

  // operator =
  BOOST_CHECK(_F == (_E = _F));
  BOOST_CHECK(_F == (_E = _f));
  BOOST_CHECK(_F == (_E = std::move(_G)));
  BOOST_CHECK(_F == (_E = static_cast< double >(_f)));
  BOOST_CHECK(_F == (_E = static_cast< long double >(_f)));
  BOOST_CHECK(F(1024.0) == (_E = _i));

  // unary operator -
  BOOST_CHECK(-F(1) == F(-1));
  BOOST_CHECK(F(0) == -F(0));
  BOOST_CHECK(F(3.14) + (-F(3.14)) == F(0));

  // operator +=, -=, *=, /=
  BOOST_CHECK(F(3) == (F(1) += F(2)));
  BOOST_CHECK(F(3.14) == (F(1.1) += F(2.04)));
  BOOST_CHECK(F(3.14) == (F(1) += F(2.14)));
  BOOST_CHECK(F(3.14) == (F(1) += 2.14));
  BOOST_CHECK(F(3.14) == (F(2.14) += 1));

  BOOST_CHECK(F(3) == (F(5) -= F(2)));
  BOOST_CHECK(F(0.2) == (F(0.4) -= F(0.2)));
  BOOST_CHECK(F(2.5) == (F(5) -= F(2.5)));
  BOOST_CHECK(F(2.5) == (F(5) -= 2.5));
  BOOST_CHECK(F(1.5) == (F(2.5) -= 1));

  BOOST_CHECK(F(10) == (F(5) *= F(2)));
  BOOST_CHECK(F(1.5) == (F(0.5) *= F(3)));
  BOOST_CHECK(F(0.25) == (F(0.5) *= F(0.5)));
  BOOST_CHECK(F(5) == (F(2.5) *= 2));
  BOOST_CHECK(F(0.25) == (F(0.5) *= 0.5));

  BOOST_CHECK(F(5) == (F(10) /= F(2)));
  BOOST_CHECK(F(3) == (F(1.5) /= F(0.5)));
  BOOST_CHECK(F(0.5) == (F(0.25) /= F(0.5)));
  BOOST_CHECK(F(2.5) == (F(5) /= 2));
  BOOST_CHECK(F(0.5) == (F(0.25) /= 0.5));
  // BOOST_CHECK(F(0.5)==(F(0.5)/=0));

  // is_zero()
  BOOST_CHECK(false == F(1).is_zero());
  BOOST_CHECK(true == F(0).is_zero());

  // zero()
  BOOST_CHECK((F::zero().is_zero()) == true);

  // absolute value
  BOOST_CHECK(F(-1).absolute() == F(1));
  BOOST_CHECK(F(1).absolute() == F(1));
  BOOST_CHECK(F(0).absolute() == F(0));

  // signcast
  BOOST_CHECK(F(1).signcast() == F(-1));
  BOOST_CHECK(F(0).signcast() == F(0));
  BOOST_CHECK(F(1.2).signcast() == F(-1.2));
  BOOST_CHECK(F(1.2).signcast() == -F(1.2));

  // toInteger
  BOOST_CHECK(F(1.2).toInteger< int >() == 1);
  BOOST_CHECK(F(0.9).toInteger< int >() == 0);

  // toZNumber
  BOOST_CHECK(F(1).to_z_number()==Z(1));
  BOOST_CHECK(F(1.2).to_z_number()==Z(1));

  // addition, subtraction, multiplicatoin, division,
  BOOST_CHECK(F(1) + F(2) == F(3));
  BOOST_CHECK(F(4) - F(2) == F(2));
  BOOST_CHECK(F(3) * F(2) == F(6));
  BOOST_CHECK(F(5) / F(2) == F(2.5));

  // comparasion
  BOOST_CHECK(true == (F(1) <= 2));
  BOOST_CHECK(true == (F(1.2) <= F(1.2)));
  BOOST_CHECK(true == (F(1.2) >= F(1.2)));
  BOOST_CHECK(true == (F(1.2) == F(1.2)));
  BOOST_CHECK(false == (F(1.2) < F(1.2)));
  BOOST_CHECK(false == (F(1.2) > F(1.2)));

  // mathematical function
  BOOST_CHECK(log2(F(32)) == 5);
  BOOST_CHECK(ln(F(3)) > 0);
  BOOST_CHECK(log10(F(100)) == 2);
  BOOST_CHECK(exp2(F(5)) == 32);
  BOOST_CHECK(exp(F(2)) < 9);
  BOOST_CHECK(exp10(F(2)) == 100);
  BOOST_CHECK(pow(F(2),F(5))==F(32));
  BOOST_CHECK(sin(F(3.14)) > 0);
  BOOST_CHECK(cos(F(3.14))>=-1);
  BOOST_CHECK(tan(F(3.14))<0);
  BOOST_CHECK(sinu(F(30))==0.5);
  BOOST_CHECK(cosu(F(60))==0.5);
  BOOST_CHECK(tanu(F(45))==1);
  BOOST_CHECK(ikos::core::retPi<float>()>3.14);

}
