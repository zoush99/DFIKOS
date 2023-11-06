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

#include <boost/functional/hash.hpp>

#include <ikos/core/number/exception.hpp>
#include <ikos/core/number/supported_integral.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/support/assert.hpp>

namespace ikos {
namespace core {

/// \brief Checks wether T is a supported integral type or ZNumber
template < typename T >
struct IsSupportedIntegralOrZNumber : public IsSupportedIntegral< T > {};

template <>
struct IsSupportedIntegralOrZNumber< const ZNumber& > : public std::true_type {
};

namespace detail {
/// \brief helper that returns either an integral type or a mpz_class
template < typename T>
struct ZNumberAdapter:public MpzAdapter<T>{};

template<>
struct ZNumberAdapter<const ZNumber&>{
  const mpz_class& operator()(const ZNumber& n){return n.mpz();}
};

} // namespace detail

class  FNumber{
private:
  mpf_class _n;
};
} // namespace core
} // namespace ikos