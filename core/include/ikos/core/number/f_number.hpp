//
// Created by zou on 10/27/23.
//
// Now I need to add the data type for floating point and
// some manipulation functions. By zoush99

#pragma once

#include <functional>
#include <iosfwd>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include <gmpxx.h>
// Floating point numbers used to implement the IEEE754 standard. By zoush99
#include <mpf2mpfr.h>
#include <mpfr.h>

#include <boost/functional/hash.hpp>

#include <ikos/core/number/exception.hpp>
#include <ikos/core/number/supported_float.hpp>
#include <ikos/core/number/supported_integral.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/support/assert.hpp>

namespace ikos {
namespace core {

/// \brief Specified precision of a floating-point number. By zoush99
enum Fpre {
  ha = 11,  // 16 bits
  fl = 24,  // 32 bits
  dou = 53, // 64 bits
  ld = 113  // 128 bits
};

/// \brief Class for unlimited precision floating point number
class FNumber {
private:
  mpfr_t _n;         // It needs to be initialized. By zoush99
  mpfr_prec_t _prec; // Precision of FNumber. unsigned integer
  mpfr_rnd_t _rnd;   // round mode of FNumber.

public:
  /// \name Constructors
  /// @{

  /// \brief Default: double, nearest, 1.0
  FNumber() {
    mpfr_init2(this->_n, 53);
    mpfr_set_d(this->_n, 1.0, MPFR_RNDN);
    this->_prec = 53;
    this->_rnd = MPFR_RNDN;
  }

  /// \brief Copy constructor
  FNumber(const FNumber& f) {
    mpfr_init2(this->_n, f._prec);
    mpfr_set(this->_n, f._n, f._rnd);
    this->_prec = f._prec;
    this->_rnd = f._rnd;
  }

  //  /// \brief Move constructor
  //  // I don't know how to construct
  //  FNumber(const FNumber&& f){
  //
  //  }

  /// \brief Create a FNumber from a mpft_t
  explicit FNumber(const mpfr_t m, mpfr_rnd_t r) {
    mpfr_init2(this->_n, mpfr_get_prec(m));
    mpfr_set(this->_n, m, r);
    this->_prec = mpfr_get_prec(m);
    this->_rnd = r;
  }

  /// \brief Create a FNumber from a floating point type
  ///
  /// I'm going to merge three functions into one,
  /// starting with determining the input data type. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  explicit FNumber(T n) {
    if (std::is_same< T, float >::value) { // float type
      mpfr_init2(this->_n, 24);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = 24;
    } else if (std::is_same< T, double >::value) { // double type
      mpfr_init2(this->_n, 53);
      mpfr_set_d(this->_n, n, MPFR_RNDN);
      this->_prec = 53;
    } else { // long double type
      mpfr_init2(this->_n, 113);
      mpfr_set_ld(this->_n, n, MPFR_RNDN);
      this->_prec = 113;
    }
    this->_rnd = MPFR_RNDN;
  }

  /// \brief Destructor
  ~FNumber() { mpfr_clear(this->_n); }

  /// \brief Display the information of FNumber
  void display() {
    mpfr_printf("\n_n value: %Rf\n", this->_n);
    mpfr_printf("_prec value: %lu\n", this->_prec);
    mpfr_printf("_rnd value: ");
    mpfr_printf(mpfr_print_rnd_mode(this->_rnd));
    mpfr_printf("\n");
  }
  /// @}
  /// \name Assignment Operators
  /// @{

  /// \brief Copy assignment
  FNumber& operator=(const FNumber& f) {
    mpfr_init2(this->_n, f._prec);
    mpfr_set(this->_n, f._n, f._rnd);
    this->_prec = f._prec;
    this->_rnd = f._rnd;
    return *this;
  }

  /// \brief Move assignment
  /// \todo(zoush99)

  /// \brief Assignments for floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator=(T n) {
    if (std::is_same< T, float >::value) { // float type
      mpfr_init2(this->_n, 24);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = 24;
    } else if (std::is_same< T, double >::value) { // double type
      mpfr_init2(this->_n, 53);
      mpfr_set_d(this->_n, n, MPFR_RNDN);
      this->_prec = 53;
    } else { // long double type
      mpfr_init2(this->_n, 113);
      mpfr_set_ld(this->_n, n, MPFR_RNDN);
      this->_prec = 113;
    }
    this->_rnd = MPFR_RNDN;
    return *this;
  }

  /// \brief Addition assignment
  // This operation assumes that the accuracies are all equal,
  // otherwise it converts them to high accuracy. By zoush99
  FNumber& operator+=(const FNumber& x) {
    if (x._prec == this->_prec) { // ()=this means precision is same
      mpfr_add(this->_n, this->_n, x._n, this->_rnd);
    } else if (x._prec > this->_prec) { // ()>this
      mpfr_t _temp;                     // temporary variable
      mpfr_init2(_temp, x._prec);
      mpfr_set(_temp, this->_n, MPFR_RNDN);
      this->_prec = x._prec;
      mpfr_set_prec(this->_n, x._prec); // Set _n=nan
      mpfr_set(this->_n, _temp, MPFR_RNDN);
      mpfr_add(this->_n, this->_n, x._n, this->_rnd);
      mpfr_clear(_temp);
    } else {             // ()<this
      mpfr_t _temp;      // temporary variable
      FNumber _tempF(x); // temporary FNumber
      mpfr_init2(_temp, this->_prec);
      mpfr_set(_temp, _tempF._n, MPFR_RNDN);
      _tempF._prec = this->_prec;
      mpfr_set_prec(_tempF._n, x._prec);
      mpfr_set(_tempF._n, _temp, MPFR_RNDN);
      mpfr_add(this->_n, this->_n, _tempF._n, this->_rnd);
      mpfr_clear(_temp);
    }
    return *this;
  }

  /// \brief Addition assignment with floating point types
  // Arithmetic operations with floating-point and mpfr types. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator+=(T x) {
    FNumber f(x);
    mpfr_t _temp;
    mpfr_init2(_temp, this->_prec);
    mpfr_set(_temp, this->_n, MPFR_RNDN);
    FNumber t(_temp, MPFR_RNDN);
    t += f;
    this->_prec = t._prec;
    mpfr_set(this->_n, t._n, MPFR_RNDN);
    mpfr_clear(_temp);
    return *this;
  }

  /// \brief Subtraction assignment
  // This operation assumes that the accuracies are all equal,
  // otherwise it converts them to high accuracy. By zoush99
  FNumber& operator-=(const FNumber& x) {
    if (x._prec == this->_prec) { // ()=this
      mpfr_sub(this->_n, this->_n, x._n, this->_rnd);
    } else if (x._prec > this->_prec) { // ()>this
      mpfr_t _temp;                     // temporary variable
      mpfr_init2(_temp, x._prec);
      mpfr_set(_temp, this->_n, MPFR_RNDN);
      this->_prec = x._prec;
      mpfr_set_prec(this->_n, x._prec); // Set _n=nan
      mpfr_set(this->_n, _temp, MPFR_RNDN);
      mpfr_sub(this->_n, this->_n, x._n, this->_rnd);
      mpfr_clear(_temp);
    } else {             // ()<this
      mpfr_t _temp;      // temporary variable
      FNumber _tempF(x); // temporary FNumber
      mpfr_init2(_temp, this->_prec);
      mpfr_set(_temp, _tempF._n, MPFR_RNDN);
      _tempF._prec = this->_prec;
      mpfr_set_prec(_tempF._n, x._prec);
      mpfr_set(_tempF._n, _temp, MPFR_RNDN);
      mpfr_sub(this->_n, this->_n, _tempF._n, this->_rnd);
      mpfr_clear(_temp);
    }
    return *this;
  }

  /// \brief Subtraction assignment with floating point types
  // Arithmetic operations with floating-point and mpfr types. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator-=(T x) {
    FNumber f(x);
    mpfr_t _temp;
    mpfr_init2(_temp, this->_prec);
    mpfr_set(_temp, this->_n, MPFR_RNDN);
    FNumber t(_temp, MPFR_RNDN);
    t -= f;
    this->_prec = t._prec;
    mpfr_set(this->_n, t._n, MPFR_RNDN);
    mpfr_clear(_temp);
    return *this;
  }
  /// \brief Multiplication assignment
  // This operation assumes that the accuracies are all equal,
  // otherwise it converts them to high accuracy. By zoush99
  FNumber& operator*=(const FNumber& x) {
    if (x._prec == this->_prec) { // ()=this
      mpfr_mul(this->_n, this->_n, x._n, this->_rnd);
    } else if (x._prec > this->_prec) { // ()>this
      mpfr_t _temp;                     // temporary variable
      mpfr_init2(_temp, x._prec);
      mpfr_set(_temp, this->_n, MPFR_RNDN);
      this->_prec = x._prec;
      mpfr_set_prec(this->_n, x._prec); // Set _n=nan
      mpfr_set(this->_n, _temp, MPFR_RNDN);
      mpfr_mul(this->_n, this->_n, x._n, this->_rnd);
      mpfr_clear(_temp);
    } else {             // ()<this
      mpfr_t _temp;      // temporary variable
      FNumber _tempF(x); // temporary FNumber
      mpfr_init2(_temp, this->_prec);
      mpfr_set(_temp, _tempF._n, MPFR_RNDN);
      _tempF._prec = this->_prec;
      mpfr_set_prec(_tempF._n, x._prec);
      mpfr_set(_tempF._n, _temp, MPFR_RNDN);
      mpfr_mul(this->_n, this->_n, _tempF._n, this->_rnd);
      mpfr_clear(_temp);
    }
    return *this;
  }

  /// \brief Multiplication assignment with floating point types
  // Arithmetic operations with floating-point and mpfr types. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator*=(T x) {
    FNumber f(x);
    mpfr_t _temp;
    mpfr_init2(_temp, this->_prec);
    mpfr_set(_temp, this->_n, MPFR_RNDN);
    FNumber t(_temp, MPFR_RNDN);
    t *= f;
    this->_prec = t._prec;
    mpfr_set(this->_n, t._n, MPFR_RNDN);
    mpfr_clear(_temp);
    return *this;
  }

  /// \brief Division assignment
  // This operation assumes that the accuracies are all equal,
  // otherwise it converts them to high accuracy. By zoush99
  FNumber& operator/=(const FNumber& x) {
    ikos_assert_msg(!mpfr_zero_p(x._n), "division by zero");
    if (x._prec == this->_prec) { // ()=this
      mpfr_div(this->_n, this->_n, x._n, this->_rnd);
    } else if (x._prec > this->_prec) { // ()>this
      mpfr_t _temp;                     // temporary variable
      mpfr_init2(_temp, x._prec);
      mpfr_set(_temp, this->_n, MPFR_RNDN);
      this->_prec = x._prec;
      mpfr_set_prec(this->_n, x._prec); // Set _n=nan
      mpfr_set(this->_n, _temp, MPFR_RNDN);
      mpfr_div(this->_n, this->_n, x._n, this->_rnd);
      mpfr_clear(_temp);
    } else {             // ()<this
      mpfr_t _temp;      // temporary variable
      FNumber _tempF(x); // temporary FNumber
      mpfr_init2(_temp, this->_prec);
      mpfr_set(_temp, _tempF._n, MPFR_RNDN);
      _tempF._prec = this->_prec;
      mpfr_set_prec(_tempF._n, x._prec);
      mpfr_set(_tempF._n, _temp, MPFR_RNDN);
      mpfr_div(this->_n, this->_n, _tempF._n, this->_rnd);
      mpfr_clear(_temp);
    }
    return *this;
  }

  /// \brief Division assignment with floating point types
  // Arithmetic operations with floating-point and mpfr types. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator/=(T x) {
    ikos_assert_msg(x != 0, "division by zero");
    FNumber f(x);
    mpfr_t _temp;
    mpfr_init2(_temp, this->_prec);
    mpfr_set(_temp, this->_n, MPFR_RNDN);
    FNumber t(_temp, MPFR_RNDN);
    t /= f;
    this->_prec = t._prec;
    mpfr_set(this->_n, t._n, MPFR_RNDN);
    mpfr_clear(_temp);
    return *this;
  }

  /// @}
  /// {@
  /// \brief Some function about class FNumber

  /// \brief Get the internal value of FNumber
  const mpfr_t& FNvalue() const { return this->_n; }

  /// \brief Get the precision of FNumber
  const mpfr_prec_t& FNprec() const{
    return this->_prec;
  }

  /// \brief Get the round mode of FNumber
  const mpfr_rnd_t& FNrnd() const{
    return this->_rnd;
  }

  /// \brief Change the infomation of FNumber
  void setFN(mpfr_t m,mpfr_prec_t p,mpfr_rnd_t r){
    mpfr_set_prec(this->_n,p);
    mpfr_set(this->_n,m,MPFR_RNDN);
    this->_prec=p;
    this->_rnd=r;
  }

  /// @}
  friend class QNumber;
  friend class ZNumber;
}; // end class FNumber

/// \brief Addition
inline FNumber operator+(const FNumber& lhs, const FNumber& rhs) {
  if(lhs.FNprec()==rhs.FNprec()){ // left=right
    FNumber _tempF(lhs);
    _tempF+=rhs;
    return _tempF;
  }
  else if(lhs.FNprec()<rhs.FNprec()){  // left<right
    FNumber _tempF(rhs);
    _tempF+=lhs;
    return _tempF;
  }else{  // left>right
    FNumber _tempF(lhs);
    _tempF+=rhs;
    return _tempF;
  }
}

/// \brief Addition with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator+(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF=_tempF+rhs;
  return _tempF;
}

/// \brief Addition with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator+(const FNumber& lhs,T rhs) {
  FNumber _tempF(rhs);
  _tempF=_tempF+lhs;
  return _tempF;
}

/// \brief Subtraction
inline FNumber operator-(const FNumber& lhs, const FNumber& rhs) {
  if(lhs.FNprec()==rhs.FNprec()){ // left=right
    FNumber _tempF(lhs);
    _tempF-=rhs;
    return _tempF;
  }
  else if(lhs.FNprec()<rhs.FNprec()){  // left<right
    FNumber _tempF(lhs);
    _tempF-=rhs;
    return _tempF;
  }else{  // left>right
    FNumber _tempF(lhs);
    _tempF-=rhs;
    return _tempF;
  }
}

/// \brief Subtraction with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator-(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF=_tempF-rhs;
  return _tempF;
}

/// \brief Subtraction with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator-(const FNumber& lhs,T rhs) {
  FNumber _tempF(rhs);
  _tempF=lhs-_tempF;
  return _tempF;
}

/// \brief Multiplication
inline FNumber operator*(const FNumber& lhs, const FNumber& rhs) {
  if(lhs.FNprec()==rhs.FNprec()){ // left=right
    FNumber _tempF(lhs);
    _tempF*=rhs;
    return _tempF;
  }
  else if(lhs.FNprec()<rhs.FNprec()){  // left<right
    FNumber _tempF(rhs);
    _tempF*=lhs;
    return _tempF;
  }else{  // left>right
    FNumber _tempF(lhs);
    _tempF*=rhs;
    return _tempF;
  }
}

/// \brief Multiplication with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator*(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF=_tempF*rhs;
  return _tempF;
}

/// \brief Multiplication with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator*(const FNumber& lhs,T rhs) {
  FNumber _tempF(rhs);
  _tempF=_tempF*lhs;
  return _tempF;
}

/// \brief Division
inline FNumber operator/(const FNumber& lhs, const FNumber& rhs) {
  ikos_assert_msg(!mpfr_zero_p(rhs.FNvalue()), "division by zero");
  if(lhs.FNprec()==rhs.FNprec()){ // left=right
    FNumber _tempF(lhs);
    _tempF/=rhs;
    return _tempF;
  }
  else if(lhs.FNprec()<rhs.FNprec()){  // left<right
    FNumber _tempF(lhs);
    _tempF/=rhs;
    return _tempF;
  }else{  // left>right
    FNumber _tempF(lhs);
    _tempF/=rhs;
    return _tempF;
  }
}

/// \brief Division with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator/(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF=_tempF/rhs;
  return _tempF;
}

/// \brief Division with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber operator/(const FNumber& lhs,T rhs) {
  FNumber _tempF(rhs);
  _tempF=lhs/_tempF;
  return _tempF;
}

/// @}
/// \name Comparison Operators
/// @{

/// \brief Equality operators 1->true, 0->false
inline bool operator==(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_equal_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Equality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator==(const FNumber& lhs, T rhs) {
  FNumber rhsFN(rhs);
  return mpfr_equal_p(lhs.FNvalue(), rhsFN.FNvalue());
}

/// \brief Equality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator==(T lhs, const FNumber& rhs) {
  FNumber lhsFN(lhs);
  return mpfr_equal_p(rhs.FNvalue(), lhsFN.FNvalue());
}

/// \brief Inequality operator
inline bool operator!=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_lessgreater_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Inequality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator!=(const FNumber& lhs, T rhs) {
  FNumber rhsFN(rhs);
  return mpfr_lessgreater_p(lhs.FNvalue(), rhsFN.FNvalue());
}

/// \brief Inequality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator!=(T lhs, const FNumber& rhs) {
  FNumber lhsFN(lhs);
  return mpfr_lessgreater_p(rhs.FNvalue(), lhsFN.FNvalue());
}

/// \brief Less than comparison
inline bool operator<(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_less_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Less than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<(const FNumber& lhs, T rhs) {
  FNumber rhsFN(rhs);
  return mpfr_less_p(lhs.FNvalue(), rhsFN.FNvalue());
}

/// \brief Less than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<(T lhs, const FNumber& rhs) {
  FNumber lhsFN(lhs);
  return mpfr_less_p(lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Less or equal comparison
inline bool operator<=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_lessequal_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Less or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<=(const FNumber& lhs, T rhs) {
  FNumber rhsFN(rhs);
  return mpfr_less_p(lhs.FNvalue(), rhsFN.FNvalue());
}

/// \brief Less or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<=(T lhs, const FNumber& rhs) {
  FNumber lhsFN(lhs);
  return mpfr_lessequal_p(lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Greater than comparison
inline bool operator>(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_greater_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Greater than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>(const FNumber& lhs, T rhs) {
  FNumber rhsFN(rhs);
  return mpfr_greater_p(lhs.FNvalue(), rhsFN.FNvalue());
}

/// \brief Greater than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>(T lhs, const FNumber& rhs) {
  FNumber lhsFN(lhs);
  return mpfr_greater_p(lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Greater or equal comparison
inline bool operator>=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_greaterequal_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Greater or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>=(const FNumber& lhs, T rhs) {
  FNumber rhsFN(rhs);
  return mpfr_greaterequal_p(lhs.FNvalue(), rhsFN.FNvalue());
}

/// \brief Greater or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>=(T lhs, const FNumber& rhs) {
  FNumber lhsFN(lhs);
  return mpfr_greaterequal_p(lhsFN.FNvalue(), rhs.FNvalue());
}

/// @}
/// \name Mathematical function
/// @{
// All by zoush99

/// \brief Return the logarithm of the given number. log2(antilogarithm)
inline FNumber log2(const FNumber& antilogarithm){
  mpfr_t n;
  mpfr_init2(n,antilogarithm.FNprec());
  mpfr_log2(n,antilogarithm.FNvalue(),MPFR_RNDN);
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);  // clear temporary variables. By zoush99
  return f;
}

/// \brief Return the natural logarithm of the given number. ln(antilogarithm)
inline FNumber ln(const FNumber& antilogarithm){
  mpfr_t n;
  mpfr_init2(n,antilogarithm.FNprec());
  mpfr_log(n,antilogarithm.FNvalue(),MPFR_RNDN);
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);  // clear temporary variables. By zoush99
  return f;
}

/// \brief Return the logarithm of the given number. log10(antilogarithm)
inline FNumber log10(const FNumber& antilogarithm){
  mpfr_t n;
  mpfr_init2(n,antilogarithm.FNprec());
  mpfr_log10(n,antilogarithm.FNvalue(),MPFR_RNDN);
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the exponential of the given number. 2(exponent)
inline FNumber exp2(const FNumber& exponent){
  mpfr_t n;
  mpfr_init2(n,exponent.FNprec()); // default
  mpfr_exp2(n,exponent.FNvalue(),MPFR_RNDN);
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the exponential of the given number. e(exponent)
inline FNumber exp(const FNumber& exponent){
  mpfr_t n;
  mpfr_init2(n,exponent.FNprec());
  mpfr_exp(n,exponent.FNvalue(),MPFR_RNDN);
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the exponential of the given number. 10(exponent)
inline FNumber exp10(const FNumber& exponent){
  mpfr_t n;
  mpfr_init2(n,exponent.FNprec());
  mpfr_exp10(n,exponent.FNvalue(),MPFR_RNDN);
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the power of the given number. base**(exponent)
inline FNumber pow(FNumber& base,FNumber& exponent){
  mpfr_t n;
  mpfr_init2(n,exponent.FNprec());
  mpfr_pow(n,base.FNvalue(),exponent.FNvalue(),MPFR_RNDN);  // Result difference between mpfr_powr? By zoush99
  FNumber f(n,MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the sin of the given curve number. sin(n): sin(pi/3)
inline FNumber sin(FNumber& f){
  mpfr_t n;
  mpfr_init2(n,f.FNprec());
  mpfr_sin(n,f.FNvalue(),MPFR_RNDN);
  FNumber e(n,MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brief Return the cos of the given curve number. cos(n): cos(pi/3)
inline FNumber cos(FNumber& f){
  mpfr_t n;
  mpfr_init2(n,f.FNprec());
  mpfr_cos(n,f.FNvalue(),MPFR_RNDN);
  FNumber e(n,MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brief Return the tan of the given curve number. tan(n): tan(pi/3)
inline FNumber tan(FNumber& f){
  mpfr_t n;
  mpfr_init2(n,f.FNprec());
  mpfr_tan(n,f.FNvalue(),MPFR_RNDN);
  FNumber e(n,MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brirf Return the sin of the given degree number. sin(n): sin(120)
inline FNumber sinu(FNumber& f){
  mpfr_t n;
  mpfr_init2(n,f.FNprec());
  mpfr_sinu(n,f.FNvalue(),360,MPFR_RNDN);
  FNumber e(n,MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brirf Return the cos of the given degree number. cos(n): cos(120)
inline FNumber cosu(FNumber& f){
  mpfr_t n;
  mpfr_init2(n,f.FNprec());
  mpfr_cosu(n,f.FNvalue(),360,MPFR_RNDN);
  FNumber e(n,MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brirf Return the tan of the given degree number. tan(n): tan(120)
inline FNumber tanu(FNumber& f){
  mpfr_t n;
  mpfr_init2(n,f.FNprec());
  mpfr_tanu(n,f.FNvalue(),360,MPFR_RNDN);
  FNumber e(n,MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brief If you need other trigonometric functions later,
/// add them separately. By zoush99
// sec, csc, cot, acos, asin, atan, cosh, sinh, tanh, sech, csch, coth

/// @}
/// \name Constant
/// @{

/// \brief Return the value of pi
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber retPi(T f){
  FNumber Pi(f);
  mpfr_t n;
  mpfr_init2(n,Pi.FNprec());
  mpfr_const_pi(n,MPFR_RNDN);
  Pi.setFN(n,Pi.FNprec(),MPFR_RNDN);
  mpfr_clear(n);
  return Pi;
}

/// @}
/// \name Input / Output
/// @{

/// \brief Write a FNumber on a stream, in base 10
inline std::ostream& operator<<(std::ostream& o, const FNumber& n) {
  o << n.FNvalue();
  return o;
}
/// @}
} // namespace core
} // namespace ikos