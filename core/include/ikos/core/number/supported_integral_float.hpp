//
// Created by zou on 11/15/23.
//

#pragma once

#include <type_traits>

namespace ikos {
namespace core {

/// \brief Checks whether T is a supported integral type.
///
/// Supported integral types are:
///   * int, unsigned int
///   * long, unsigned long
///   * long long, unsigned long long
template < typename T >
struct IsSupportedIntegralFloat : public std::false_type {};

template <>
struct IsSupportedIntegralFloat< int > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< unsigned int > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< long > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< unsigned long > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< long long > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< unsigned long long > : public std::true_type {};

/// \brief Checks whether T is a supported floating point type.
///
/// Supported floating point types are:
///   * float, double
///   * long double, and so on
/// \todo(zoush99)
///   * I still need to add the 80 bits after that. By zoush99

template <>
struct IsSupportedIntegralFloat< float > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< double > : public std::true_type {};

template <>
struct IsSupportedIntegralFloat< long double > : public std::true_type {};

} // end namespace core
} // end namespace ikos
