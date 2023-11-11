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
#include <ikos/core/number/supported_float.hpp>

namespace ikos {
namespace core {

/// \brief Specified precision of a floating-point number. By zoush99
enum Fpre{
  ha=11,  //16 bits
  fl=24,  // 32 bits
  dou=53,  // 64 bits
  ld=113  // 128 bits
};

/// \brief Class for unlimited precision floating point number
class FNumber {
private:
  mpfr_t _n;  // It needs to be initialized. By zoush99
  mpfr_prec_t _prec;  // Precision of FNumber. unsigned integer
  mpfr_rnd_t _rnd;  // round mode of FNumber.

public:
  /// \name Constructors
  /// @{

  /// \brief Default: double, nearest, 1.0
  FNumber(){
    mpfr_init2(this->_n,53);
    mpfr_set_d(this->_n,1.0,MPFR_RNDN);
    this->_prec=53;
    this->_rnd=MPFR_RNDN;
  }

  /// \brief Copy constructor
  FNumber(const FNumber& f){
    mpfr_init2(this->_n,f._prec);
    mpfr_set(this->_n,f._n,f._rnd);
    this->_prec=f._prec;
    this->_rnd=f._rnd;
  }

//  /// \brief Move constructor
//  // I don't know how to construct
//  FNumber(const FNumber&& f){
//
//  }

  /// \brief Create a FNumber from a mpft_t
  explicit FNumber(const mpfr_t m,mpfr_rnd_t r){
    mpfr_init2(this->_n, mpfr_get_prec(m));
    mpfr_set(this->_n,m, r);
    this->_prec= mpfr_get_prec(m);
    this->_rnd=r;
  }

  /// \brief Create a FNumber from a floating point type
  ///
  /// I'm going to merge three functions into one,
  /// starting with determining the input data type. By zoush99
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  explicit FNumber(T n){
    if (std::is_same< T, float >::value){
      mpfr_init2(this->_n,24);
      mpfr_set_flt(this->_n,n,MPFR_RNDN);
      this->_prec=24;
    }else if(std::is_same< T, double >::
                   value){
      mpfr_init2(this->_n,53);
      mpfr_set_d(this->_n,n,MPFR_RNDN);
      this->_prec=53;
    }else{
      mpfr_init2(this->_n,113);
      mpfr_set_ld(this->_n,n,MPFR_RNDN);
      this->_prec=113;
    }
    this->_rnd=MPFR_RNDN;
  }

  /// \brief Destructor
  ~FNumber(){
    mpfr_clear(this->_n);
  }

  /// \brief Display the information of FNumber
  void display(){
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
  FNumber& operator=(const FNumber& f){
    mpfr_init2(this->_n,f._prec);
    mpfr_set(this->_n,f._n,f._rnd);
    this->_prec=f._prec;
    this->_rnd=f._rnd;
    return *this;
  }

  /// \brief Move assignment
  /// \todo(zoush99)

  /// \brief Assignments for floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedFloat< T >::value > >
  FNumber& operator=(T n) {
    if (std::is_same< T, float >::value){
      mpfr_init2(this->_n,24);
      mpfr_set_flt(this->_n,n,MPFR_RNDN);
      this->_prec=24;
    }else if(std::is_same< T, double >::
                   value){
      mpfr_init2(this->_n,53);
      mpfr_set_d(this->_n,n,MPFR_RNDN);
      this->_prec=53;
    }else{
      mpfr_init2(this->_n,113);
      mpfr_set_ld(this->_n,n,MPFR_RNDN);
      this->_prec=113;
    }
    this->_rnd=MPFR_RNDN;
    return *this;
  }

  /// \brief Addition assignment
  FNumber& operator+=(const FNumber& x) {
    mpfr_add(this->_n, this->_n, x._n, this->_rnd);
    return *this;
  }
}; // end class FNumber
} // end namespace ikos
} // end namespace core