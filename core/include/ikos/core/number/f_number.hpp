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

// GMP Only functions that return double types are defined. By zoush99
template <>
struct MpfTo< double > {
  double operator()(const mpf_class& n) {
    return static_cast< double >(n.get_d());
  }
};

} // end namespace detail

/// \brief Class for unlimited precision floating point number
class FNumber {
private:
  mpf_class _n; // Curious if it works like that? By zoush99

public:
  /// \brief Create a FNumber from a string representation
  static FNumber from_string(const char* str, int base = 10) {}

  /// \brief Create a FNumber from a string representation
  static FNumber from_string(const std::string& str, int base = 10) {}

  /// \name Constructors
  /// @{

  /// \brief Default constructor that creates a FNumber equals to 0
  FNumber() = default;

  /// \brief Copy constructor
  FNumber(const FNumber&) = default;

  /// \brief Move constructor
  FNumber(FNumber&&) = default;

  /// \brief Create a FNumber from a mpf_class
  explicit FNumber(const mpf_class& n) : _n(n) {}

  /// \brief Create a FNumber from a mpf_class
  explicit FNumber(mpf_class&& n) : _n(std::move(n)) {}

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
  FNumber& operator=(FNumber&&) noexcept=default;

  /// \brief Assignments for floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator=(T n) {
    this->_n = detail::MpfAdapter< T >()(n);
    return *this;
  }

  /// \brief Addition assignment
  FNumber& operator+=(const FNumber& x){
    this->_n+=x._n;
    return *this;
  }

  /// \brief Addition assignment with floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator+=(T x) {
    this->_n += detail::MpfAdapter< T >()(x);
    return *this;
  }

  /// \brief Subtraction assignment
  FNumber& operator-=(const FNumber& x) {
    this->_n -= x._n;
    return *this;
  }

  /// \brief Subtraction assignment with floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator-=(T x) {
    this->_n -= detail::MpfAdapter< T >()(x);
    return *this;
  }
}; // class FNumber
} // namespace core
} // namespace ikos