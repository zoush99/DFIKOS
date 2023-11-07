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
#include <ikos/core/number/supported_integral.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/support/assert.hpp>

namespace ikos {
namespace core {

namespace detail {

/// \brief Helper to handle all supported floating point types with GMP
template < typename T >
struct MpfAdapter {
  T operator()(T n) { return n; }
};

/// \brief Helper to check if a mpf_class fits in the given floating point type
template < typename T >
struct MpfFits;

/// \brief Check if it can be converted to float type, but GMP-6.3.0 didn't
/// realized. By zoush99

/// \brief Helper to convert a mpf_class to the given floating point type
template < typename T >
struct MpfTo;

// MPFR functions that return float.
template <>
struct MpfTo< float > {
  float operator()(const mpfr_t& n) { return mpfr_get_flt(n, MPFR_RNDN); }
};

// MPFR functions that return double.
template <>
struct MpfTo< double > {
  double operator()(const mpfr_t& n) { return mpfr_get_d(n, MPFR_RNDN); }
};

// MPFR functions that return long double.
template <>
struct MpfTo< long double > {
  long double operator()(const mpfr_t& n) { return mpfr_get_ld(n, MPFR_RNDN); }
};

template <>
struct MpfFrom;

/// I'm going to merge three functions into one,
/// starting with determining the input data type. By zoush99

template <typename T, class = std::enable_if_t< IsSupportedFloat< T >::value > >
struct MpfFrom<T>{
  mpfr_t& operator()(const T& f){
    int temp;
    mpfr_t rop;
    mpfr_init(rop);
    if(std::is_same<T,float>::value){
      temp=mpfr_set_flt(rop,f,MPFR_RNDN);
    }
    else if (std::is_same<T,double>::value){
      temp=mpfr_set_d(rop,f,MPFR_RNDN);
    }
    else{ // long double. By zoush99
      temp=mpfr_set_ld(rop,f,MPFR_RNDN);
    }
    return rop;
  }
};
} // end namespace detail

/// \brief Class for unlimited precision floating point number
class FNumber {
private:
  mpfr_t _n; // It needs to be initialized. By zoush99

public:
  /// \brief Create a FNumber from a string representation
  static FNumber from_string(const char* str, int base = 10) {}

  /// \brief Create a FNumber from a string representation
  static FNumber from_string(const std::string& str, int base = 10) {}

  /// \name Constructors
  /// @{

  /// \brief Default constructor that creates a FNumber equals to 0
  FNumber() { mpfr_init(this->_n); }

  /// \brief Copy constructor
  FNumber(const FNumber&) = default;

  /// \brief Move constructor
  FNumber(FNumber&&) = default;

  /// \brief Create a FNumber from a mpfr_t
  explicit FNumber(const mpfr_t& f) {
    mpfr_init(this->_n);
    this->_n = mpfr_get_d(f, MPFR_RNDN);
  }

  /// \brief Create a FNumber from a mpfr_t
  explicit FNumber(mpfr_t&& n) {
    mpfr_init(this->_n);
    this->_n = mpfr_get_d(std::move(n), MPFR_RNDN);
  }

  /// \brief Create a FNumber from an floating point type
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  explicit FNumber(T n) : _n(detail::MpfAdapter< T >()(n)) {}

  /// \brief Destructor
  ~FNumber() = default;
  /// @}
  /// \name Assignment Operators
  /// @{

  /// \brief Copy assignment
  FNumber& operator=(const FNumber&) = default;

  /// \brief Move assignment
  FNumber& operator=(FNumber&&) noexcept = default;

  /// \brief Assignments for floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator=(T n) {
    this->_n = detail::MpfAdapter< T >()(n);
    return *this;
  }

  /// \brief Addition assignment
  FNumber& operator+=(const FNumber& x) {
    int temp;
    temp = mpfr_add(this->_n, this->_n, x._n, MPFR_RNDN);
    return *this;
  }

  /// \brief Addition assignment with floating point types
  // Arithmetic operations with floating-point and mpfr types. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator+=(T x) {
    int temp;
    temp= mpfr_add(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Subtraction assignment
  FNumber& operator-=(const FNumber& x) {
    int temp;
    temp = mpfr_sub(this->_n, this->_n, x._n, MPFR_RNDN);
    return *this;
  }

  /// \brief Subtraction assignment with floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator-=(T x) {
    int temp;
    temp= mpfr_sub(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Multiplication assignment
  FNumber& operator*=(const FNumber& x) {
    int temp;
    temp= mpfr_mul(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Multiplication assignment with floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator*=(T x) {
    int temp;
    temp= mpfr_mul(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }
}; // class FNumber
} // namespace core
} // namespace ikos