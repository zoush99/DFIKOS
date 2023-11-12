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
    if (x._prec == this->_prec) { // ()=this
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

  /// \brief Get the internal representation
  const mpfr_t& mpfrvalue() const { return this->_n; }

  friend class QNumber;
  friend class ZNumber;
}; // end class FNumber

/// \brief Addition
//inline FNumber operator+(const FNumber& lhs, const FNumber& rhs) {
//  if (lhs.mpfrvalue() == rhs.mpfrvalue()) { //
//    mpfr_add(this->_n, this->_n, x._n, this->_rnd);
//  } else if (x._prec > this->_prec) { // ()>this
//    mpfr_t _temp;                     // temporary variable
//    mpfr_init2(_temp, x._prec);
//    mpfr_set(_temp, this->_n, MPFR_RNDN);
//    this->_prec = x._prec;
//    mpfr_set_prec(this->_n, x._prec); // Set _n=nan
//    mpfr_set(this->_n, _temp, MPFR_RNDN);
//    mpfr_add(this->_n, this->_n, x._n, this->_rnd);
//    mpfr_clear(_temp);
//  } else {             // ()<this
//    mpfr_t _temp;      // temporary variable
//    FNumber _tempF(x); // temporary FNumber
//    mpfr_init2(_temp, this->_prec);
//    mpfr_set(_temp, _tempF._n, MPFR_RNDN);
//    _tempF._prec = this->_prec;
//    mpfr_set_prec(_tempF._n, x._prec);
//    mpfr_set(_tempF._n, _temp, MPFR_RNDN);
//    mpfr_add(this->_n, this->_n, _tempF._n, this->_rnd);
//    mpfr_clear(_temp);
//}

} // namespace core
} // namespace ikos