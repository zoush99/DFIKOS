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

/// \brief I'm going to merge three functions into one,
/// starting with determining the input data type. By zoush99

template <typename T, class = std::enable_if_t< IsSupportedFloat< T >::value > >
struct MpfFrom<T>{
  // Curious if this should be a variable representation or
  // a reference representation? By zoush99
  mpfr_t operator()(const T& f){
    mpfr_t rop;
    mpfr_init(rop);
    if(std::is_same<T,float>::value){ // Determining if a variable's data type is float?
      mpfr_set_flt(rop,f,MPFR_RNDN);
    }
    else if (std::is_same<T,double>::value){  //Determining if a variable's data type is double?
      mpfr_set_d(rop,f,MPFR_RNDN);
    }
    else{ // Determining if a variable's data type is long double? By zoush99
      mpfr_set_ld(rop,f,MPFR_RNDN);
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

  /// \name Constructors
  /// @{

  /// \brief Default constructor that creates a FNumber but don't initialize. By zoush99
  FNumber()=default;

  /// \brief Copy constructor
  FNumber(const FNumber&) = default;

  /// \brief Move constructor
  FNumber(FNumber&&) = default;

  /// \brief Create a FNumber from a mpfr_t
  explicit FNumber(const mpfr_t& f) {
    mpfr_init_set(this->_n,f,MPFR_RNDN);
  }

  /// \brief Create a FNumber from a mpfr_t
  explicit FNumber(mpfr_t&& n) {
    mpfr_init_set(this->_n,std::move(n),MPFR_RNDN);
  }

  /// \brief Create a FNumber from an floating point type
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  explicit FNumber(T n){
    mpfr_init(this->_n);
    mpfr_set(this->_n,detail::MpfFrom(n),MPFR_RNDN);
  }

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
    mpfr_init(this->_n);
    mpfr_set(this->_n,detail::MpfFrom(n),MPFR_RNDN);
    return *this;
  }

  /// \brief Addition assignment
  FNumber& operator+=(const FNumber& x) {
    mpfr_add(this->_n, this->_n, x._n, MPFR_RNDN);
    return *this;
  }

  /// \brief Addition assignment with floating point types
  // Arithmetic operations with floating-point and mpfr types. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator+=(T x) {
    mpfr_add(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Subtraction assignment
  FNumber& operator-=(const FNumber& x) {
    mpfr_sub(this->_n, this->_n, x._n, MPFR_RNDN);
    return *this;
  }

  /// \brief Subtraction assignment with floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator-=(T x) {
    mpfr_sub(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Multiplication assignment
  FNumber& operator*=(const FNumber& x) {
    mpfr_mul(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Multiplication assignment with floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator*=(T x) {
    mpfr_mul(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// \brief Floating point division assignment
  ///
  /// Floating point division with rounding towards nearest.
  FNumber& operator/=(const FNumber& x) {
    ikos_assert_msg(!mpfr_zero_p(x._n),"division by zero");
    mpfr_div(this->_n,this->_n,x._n,MPFR_RNDN);
    return *this;
  }

  /// \brief Floating point division assignment with Floating point types
  ///
  /// Floating point division with rounding towards nearest.
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  ZNumber& operator/=(T x) {
    ikos_assert_msg(x != 0, "division by zero");
    mpfr_div(this->_n,detail::MpfFrom(x),MPFR_RNDN);
    return *this;
  }

  /// @}
  /// \name Unary Operatiors
  /// @{

  /// \brief Unary plus
  const FNumber& operator+() const{return *this;}

  /// \brief Prefix increment
  FNumber& operator++(){
    FNumber x;  // It should be initialized before using. By zoush99
    mpfr_init(x._n);
    mpfr_set_flt(x._n,1.0,MPFR_RNDN);
    mpfr_add(this->_n, this->_n, x._n, MPFR_RNDN);
    return *this;
  }

  /// \brief Postfix increment
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  const FNumber operator++(T n){
    FNumber x;
    FNumber r(*this);
    mpfr_init(x._n);
    mpfr_set_flt(x._n,1.0,MPFR_RNDN);
    mpfr_add(this->_n, this->_n, x._n, MPFR_RNDN);
    return r;
  }

  /// \brief Unary minus
  const FNumber operator-() const{
    FNumber r(*this);
    mpfr_neg(r._n,this->_n,MPFR_RNDN);
    return r._n;
  }

  /// \brief Prefix decrement
  FNumber& operator--(){
    FNumber x;  // It should be initialized before using. By zoush99
    mpfr_init(x._n);
    mpfr_set_flt(x._n,1.0,MPFR_RNDN);
    mpfr_sub(this->_n, this->_n, x._n, MPFR_RNDN);
    return *this;
  }

  /// \brief Postfix decrement
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  const FNumber operator--(T f){
    FNumber x;
    FNumber r(*this);
    mpfr_init(x._n);
    mpfr_set_flt(x._n,1.0,MPFR_RNDN);
    mpfr_sub(this->_n, this->_n, x._n, MPFR_RNDN);
    return r;
  }

  /// \brief Get the internal representation
  const mpfr_t mpfvalue() const{
    return this->_n;
  }

  friend class QNumber;
}; // class FNumber

/// \name Binary Operators
/// @{

/// \brief Addition
inline FNumber& operator+(const FNumber& lhs, const FNumber& rhs){
  mpfr_t f;
  mpfr_init(f);
  mpfr_add(f,lhs.mpfvalue(),rhs.mpfvalue(),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Addition with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator+(const FNumber& lhs, T rhs) {
  mpfr_t f;
  mpfr_init(f);
  mpfr_add(f,lhs.mpfvalue(),detail::MpfFrom(rhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Addition with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator+(T lhs, const FNumber& rhs) {
  mpfr_t f;
  mpfr_init(f);
  mpfr_add(f,rhs.mpfvalue(),detail::MpfFrom(lhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Subtraction
inline FNumber& operator-(const FNumber& lhs, const FNumber& rhs){
  mpfr_t f;
  mpfr_init(f);
  mpfr_sub(f,lhs.mpfvalue(),rhs.mpfvalue(),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Subtraction with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator-(const FNumber& lhs, T rhs) {
  mpfr_t f;
  mpfr_init(f);
  mpfr_sub(f,lhs.mpfvalue(),detail::MpfFrom(rhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Subtraction with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator-(T lhs, const FNumber& rhs) {
  mpfr_t f;
  mpfr_init(f);
  mpfr_sub(f,rhs.mpfvalue(),detail::MpfFrom(lhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Multiplication
inline FNumber& operator*(const FNumber& lhs, const FNumber& rhs){
  mpfr_t f;
  mpfr_init(f);
  mpfr_mul(f,lhs.mpfvalue(),rhs.mpfvalue(),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Multiplication with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator*(const FNumber& lhs, T rhs) {
  mpfr_t f;
  mpfr_init(f);
  mpfr_mul(f,lhs.mpfvalue(),detail::MpfFrom(rhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Multiplication with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator*(T lhs, const FNumber& rhs) {
  mpfr_t f;
  mpfr_init(f);
  mpfr_mul(f,rhs.mpfvalue(),detail::MpfFrom(lhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Floating point division
///
/// Floating point division with rounding towards nearest
inline FNumber& operator/(const FNumber& lhs, const FNumber& rhs){
  mpfr_t f;
  mpfr_init(f);
  ikos_assert_msg(!mpfr_zero_p(rhs.mpfvalue()),"division by zero");
  mpfr_div(f,lhs.mpfvalue(),rhs.mpfvalue(),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Floating point division with floating point types
///
/// Floating point division with rounding towards nearest
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator/(const FNumber& lhs, T rhs) {
  mpfr_t f;
  mpfr_init(f);
  ikos_assert_msg(rhs!=0,"division by zero");
  mpfr_div(f,lhs.mpfvalue(),detail::MpfFrom(rhs),MPFR_RNDN);
  return FNumber(f);
}

/// \brief Floating point division with floating point types
///
/// Floating point division with rounding towards nearest
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline FNumber& operator/(T lhs, const FNumber& rhs) {
  mpfr_t f;
  mpfr_init(f);
  ikos_assert_msg(!mpfr_zero_p(rhs.mpfvalue()),"division by zero");
  mpfr_div(f,detail::MpfFrom(lhs),rhs.mpfvalue(),MPFR_RNDN);
  return FNumber(f);
}

/// @}
/// \name Comparision Operators
/// @{

/// \brief Equality operators
inline bool operator==(const FNumber& lhs, const FNumber& rhs){
  return mpfr_equal_p(lhs.mpfvalue(),rhs.mpfvalue());
}

/// \brief Equality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator==(const FNumber& lhs, T rhs) {
  return mpfr_equal_p(lhs.mpfvalue(),detail::MpfFrom(rhs));
}

/// \brief Equality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator==(T lhs, const FNumber& rhs) {
  return mpfr_equal_p(rhs.mpfvalue(),detail::MpfFrom(lhs));
}

/// \brief Inequality operator
inline bool operator!=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_lessgreater_p(lhs.mpfvalue(),rhs.mpfvalue());
}

/// \brief Inequality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator!=(const FNumber& lhs, T rhs) {
  return mpfr_lessgreater_p(lhs.mpfvalue(),detail::MpfFrom(rhs));
}

/// \brief Inequality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator!=(T lhs, const FNumber& rhs) {
  return mpfr_lessgreater_p(rhs.mpfvalue(),detail::MpfFrom(lhs));
}

/// \brief Less than comparison
inline bool operator<(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_less_p(lhs.mpfvalue(),rhs.mpfvalue());
}

/// \brief Less than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<(const FNumber& lhs, T rhs) {
  return mpfr_less_p(lhs.mpfvalue(),detail::MpfFrom(rhs));
}

/// \brief Less than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<(T lhs, const FNumber& rhs) {
  return mpfr_less_p(detail::MpfFrom(lhs),rhs.mpfvalue());
}

/// \brief Less or equal comparison
inline bool operator<=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_lessequal_p(lhs.mpfvalue(),rhs.mpfvalue());
}

/// \brief Less or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<=(const FNumber& lhs, T rhs) {
  return mpfr_less_p(lhs.mpfvalue(),detail::MpfFrom(rhs));
}

/// \brief Less or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator<=(T lhs, const FNumber& rhs) {
  return mpfr_lessequal_p(detail::MpfFrom(lhs),rhs.mpfvalue());
}

/// \brief Greater than comparison
inline bool operator>(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_greater_p(lhs.mpfvalue(),rhs.mpfvalue());
}

/// \brief Greater than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>(const FNumber& lhs, T rhs) {
  return mpfr_greater_p(lhs.mpfvalue(),detail::MpfFrom(rhs));
}

/// \brief Greater than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>(T lhs, const FNumber& rhs) {
  return mpfr_greater_p(detail::MpfFrom(lhs),rhs.mpfvalue());
}


/// \brief Greater or equal comparison
inline bool operator>=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_greaterequal_p(lhs.mpfvalue(),rhs.mpfvalue());
}

/// \brief Greater or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>=(const FNumber& lhs, T rhs) {
  return mpfr_greaterequal_p(lhs.mpfvalue(),detail::MpfFrom(rhs));
}

/// \brief Greater or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedFloat< T >::value > >
inline bool operator>=(T lhs, const FNumber& rhs) {
  return mpfr_greaterequal_p(detail::MpfFrom(lhs),rhs.mpfvalue());
}
} // namespace core
} // namespace ikos