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
#include <ikos/core/number/machine_int.hpp>
#include <ikos/core/number/supported_integral_float.hpp>
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
  /// \brief Create a FNumber from a string representation
  ///
  /// Interpret the null-terminated string `str` in the given base.
  ///
  /// If the string contains unsuitable characters for the given base, throw
  /// an exception NumberError.
  ///
  /// The base may vary from 2 to 36.
  static FNumber from_string(const char* str, int base = 10) {
    try {
      mpfr_t _strF;
      mpfr_init2(_strF, Fpre::dou); // 53 bits
      mpfr_set_str(_strF, str, base, MPFR_RNDN);
      FNumber F(_strF, MPFR_RNDN);
      F._prec = Fpre::dou;
      F._rnd = MPFR_RNDN;
      mpfr_clear(_strF);
      return F;
    } catch (std::invalid_argument&) {
      std::ostringstream buf;
      buf << "FNumber: invalid conversion from string '" << str << "'";
      throw NumberError(buf.str());
    }
  }

  /// \brief Create a FNumber from a string representation
  ///
  /// Interpret the null-terminated string `str` in the given base.
  ///
  /// If the string contains unsuitable characters for the given base, throw
  /// an exception NumberError.
  ///
  /// The base may vary from 2 to 36.
  static FNumber from_string(const std::string& str, int base = 10) {
    try {
      mpfr_t _strF;
      mpfr_init2(_strF, Fpre::dou); // 53 bits
      mpfr_set_str(_strF, str.c_str(), base, MPFR_RNDN);
      FNumber F(_strF, MPFR_RNDN);
      F._prec = Fpre::dou;
      F._rnd = MPFR_RNDN;
      mpfr_clear(_strF);
      return F;
    } catch (std::invalid_argument&) {
      std::ostringstream buf;
      buf << "FNumber: invalid conversion from string '" << str << "'";
      throw NumberError(buf.str());
    }
  }

  /// \brief Transform a FNumber to a string representation
  ///
  /// The base may vary from 2 to 36.
  std::string to_string(int base = 10) const {
    int size = mpfr_snprintf(nullptr, 0, "%.*Rg", base, this->_n);
    char* buffer = new char[size + 1];
    mpfr_snprintf(buffer,
                  size + 1,
                  "%.*Rg",
                  base,
                  this->_n); // %e, %f, %.10Rf et al.
    std::string result(buffer);
    delete[] buffer;
    return result;
  }

  /// \name Constructors
  /// @{

  /// \brief Default: double, nearest, 1.0
  FNumber() {
    mpfr_init2(this->_n, Fpre::dou);
    mpfr_set_d(this->_n, 1.0, MPFR_RNDN);
    this->_prec = Fpre::dou;
    this->_rnd = MPFR_RNDN;
  }

  /// \brief Copy constructor
  FNumber(const FNumber& f) {
    mpfr_init2(this->_n, f._prec);
    mpfr_set(this->_n, f._n, f._rnd);
    this->_prec = f._prec;
    this->_rnd = f._rnd;
  }

  /// \brief Move constructor
  FNumber(FNumber&& f) {
    if (this != &f) {
      mpfr_swap(this->_n, f._n);
      this->_prec = f._prec;
      this->_rnd = f._rnd;
      // Getting rid of pointing relationships
      mpfr_init2(f._n, Fpre::fl);
      f._prec = 0;
      f._rnd = MPFR_RNDN;
    }
  }

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
             class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
  explicit FNumber(T n) {
    if (std::is_same< T, float >::value) { // float type
      mpfr_init2(this->_n, Fpre::fl);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::fl;
    } else if (std::is_same< T, double >::value) { // double type
      mpfr_init2(this->_n, Fpre::dou);
      mpfr_set_d(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::dou;
    } else if (std::is_same< T, long double >::value) { // long double type
      mpfr_init2(this->_n, Fpre::ld);
      mpfr_set_ld(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::ld;
    } else if (std::is_same< T, int >::value) { // int type -> float
      mpfr_init2(this->_n, Fpre::fl);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::fl;
    } else if (std::is_same< T, long int >::value) { // long int -> double
      mpfr_init2(this->_n, Fpre::dou);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::dou;
    } else if (std::is_same< T, long long int >::value) { // long long int ->
                                                          // long double
      mpfr_init2(this->_n, Fpre::ld);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::ld;
    } else {
      ikos_unreachable("unreachable");
    }
    this->_rnd = MPFR_RNDN;
  }

  /// \brief Create a FNumber from a ZNumber. By zoush99
  FNumber(ZNumber& z){
    mpfr_init2(this->_n, Fpre::dou);
    mpfr_set_z(this->_n,z._n.get_mpz_t(),MPFR_RNDN);
    this->_prec=Fpre::dou;
    this->_rnd = MPFR_RNDN;
  }

  /// \brief Destructor
  ~FNumber() { mpfr_clear(this->_n); }

  /// \brief Display the information of FNumber
  void display() const {
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
  FNumber& operator=(FNumber&& f) {
    if (this != &f) {
      // Move the resource from f to this object
      mpfr_swap(this->_n, f._n);

      // Transfer other necessary members
      this->_prec = f._prec;
      this->_rnd = f._rnd;

      // Reset the original object to a valid but unspecified state
      mpfr_init2(f._n, Fpre::fl); // Ensure the original object doesn't own the
                                  // resource anymore
      f._prec = 0;                // Reset other members as needed
      f._rnd = MPFR_RNDN;
    }
    return *this;
  }

  /// \brief Assignments for floating point types
  template < typename T,
             class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
  FNumber& operator=(T n) {
    if (std::is_same< T, float >::value) { // float type
      mpfr_init2(this->_n, Fpre::fl);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::fl;
    } else if (std::is_same< T, double >::value) { // double type
      mpfr_init2(this->_n, Fpre::dou);
      mpfr_set_d(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::dou;
    } else if (std::is_same< T, long double >::value) { // long double type
      mpfr_init2(this->_n, Fpre::ld);
      mpfr_set_ld(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::ld;
    } else if (std::is_same< T, int >::value) { // int type -> float
      mpfr_init2(this->_n, Fpre::fl);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::fl;
    } else if (std::is_same< T, long int >::value) { // long int -> double
      mpfr_init2(this->_n, Fpre::dou);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::dou;
    } else if (std::is_same< T, long long int >::value) { // long long int ->
                                                          // long double
      mpfr_init2(this->_n, Fpre::ld);
      mpfr_set_flt(this->_n, n, MPFR_RNDN);
      this->_prec = Fpre::ld;
    } else {
      ikos_unreachable("unreachable");
    }
    this->_rnd = MPFR_RNDN;
    return *this;
  }

  /// \brief Unary minus
  /// Modified!
  const FNumber operator-() const {
    FNumber _f(*this);
    mpfr_neg(_f._n, this->_n, MPFR_RNDN);
    return _f;
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
             class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
  FNumber& operator+=(T x) {
    FNumber _f(x);
    *this += _f;
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
             class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
  FNumber& operator-=(T x) {
    FNumber _f(x);
    *this -= _f;
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
             class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
  FNumber& operator*=(T x) {
    FNumber _f(x);
    *this *= _f;
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
             class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
  FNumber& operator/=(T x) {
    ikos_assert_msg(x != 0, "division by zero");
    FNumber _f(x);
    *this /= _f;
    return *this;
  }

  /// @}
  /// {@
  /// \brief The information about class FNumber

  /// \brief whether equals to 0
  bool is_zero() const {
    if (!mpfr_cmp_d(this->_n, 0))
      return true;
    else
      return false;
  }

  /// \brief return 0
  static FNumber zero() {
    FNumber _f(0);
    return _f;
  }

  /// \brief Get the internal value of FNumber
  const mpfr_t& FNvalue() const { return this->_n; }

  /// \brief Get the precision of FNumber
  const mpfr_prec_t& FNprec() const { return this->_prec; }

  /// \brief Get the round mode of FNumber
  const mpfr_rnd_t& FNrnd() const { return this->_rnd; }

  /// \brief Change the infomation of FNumber
  void setFN(mpfr_t m, mpfr_prec_t p, mpfr_rnd_t r) {
    mpfr_set_prec(this->_n, p);
    mpfr_set(this->_n, m, MPFR_RNDN);
    this->_prec = p;
    this->_rnd = r;
  }

  /// @}
  /// {@
  /// \brief Addition of unary arithmetic operations
  /// \todo(zoush99)

  /// \brief Absolute value
  FNumber& absolute() {
    mpfr_t _m;
    mpfr_init2(_m, this->_prec);
    mpfr_abs(_m, this->_n, MPFR_RNDN);
    this->setFN(_m, this->_prec, MPFR_RNDN);
    mpfr_clear(_m);
    return *this;
  }

  /// \brief Switching from high precision to low precision
  //  FNumber& trunc(int prec) const{
  //      ikos_assert(this->_prec>prec);
  //  }

  /// \brief Switching from low precision to high precision
  //  FNumber& ext(int prec) const{
  //      ikos_assert(this->_prec<prec);
  //  }

  /// \brief Change the floating point sign
  FNumber& signcast() {
    FNumber F(this->_n, MPFR_RNDN);
    F = -F;
    this->setFN(F._n, this->_prec, MPFR_RNDN);
    return *this;
  }

  //  FNumber& cast();

  /// \brief Transform FNumber to integer
  // T: (int, long int et al.), F: FNumber
  template < typename T,
             class = std::enable_if_t< IsSupportedIntegral< T >::value > >
  T toInteger() const {
    switch (this->_prec) {
      case Fpre::fl: // float -> int
        return (
            static_cast< int >(mpfr_get_flt(this->_n, MPFR_RNDN))); // Truncate
      case Fpre::dou: // double -> int
        return (static_cast< int >(mpfr_get_d(this->_n, MPFR_RNDN)));
      case Fpre::ld: // long double -> long int
        return (static_cast< long int >(mpfr_get_ld(this->_n, MPFR_RNDN)));
      default:
        ikos_unreachable("unreachable");
    }
  }

  /// \brief Transform FNumber to ZNumber
  ZNumber to_z_number() const {
    mpz_t _Ztemp;
    mpfr_get_z(_Ztemp, this->_n, MPFR_RNDN);
    mpz_class _Zclass(_Ztemp);
    ZNumber _ZNum(_Zclass);
    return _ZNum;
  }

  /// \brief Transform ZNumber to FNumber
  FNumber from_z_number(ZNumber& z) const{
    mpfr_t _f;
    mpfr_init2(_f,Fpre::dou);
    mpfr_set_z(_f,z._n.get_mpz_t(),MPFR_RNDN);
    FNumber _FNum(_f,MPFR_RNDN);
    mpfr_clear(_f);
    return _FNum;
  }
  /// @}

  friend FNumber mod(const FNumber&, const FNumber&);

  friend FNumber gcd(const FNumber&, const FNumber&);

  friend FNumber lcm(const FNumber&, const FNumber&);

  /// \todo bugs here!!!
  friend void gcd_extended(
      const FNumber&, const FNumber&, FNumber&, FNumber&, FNumber&);

  //  friend std::istream& operator>>(std::istream& i, FNumber& n);

  //  friend std::istream& operator>>(std::istream& i, ZNumber& n);

  friend class QNumber;
  friend class ZNumber;
}; // end class FNumber

/// {@
/// \brief Transform between floating point and integer. By zoush99

/// @}
/// \brief Addition
inline FNumber operator+(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.FNprec() == rhs.FNprec()) { // left=right
    FNumber _tempF(lhs);
    _tempF += rhs;
    return _tempF;
  } else if (lhs.FNprec() < rhs.FNprec()) { // left<right
    FNumber _tempF(rhs);
    _tempF += lhs;
    return _tempF;
  } else { // left>right
    FNumber _tempF(lhs);
    _tempF += rhs;
    return _tempF;
  }
}

/// \brief Addition with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator+(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF = _tempF + rhs;
  return _tempF;
}

/// \brief Addition with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator+(const FNumber& lhs, T rhs) {
  FNumber _tempF(rhs);
  _tempF = _tempF + lhs;
  return _tempF;
}

/// \brief Subtraction
inline FNumber operator-(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.FNprec() == rhs.FNprec()) { // left=right
    FNumber _tempF(lhs);
    _tempF -= rhs;
    return _tempF;
  } else if (lhs.FNprec() < rhs.FNprec()) { // left<right
    FNumber _tempF(lhs);
    _tempF -= rhs;
    return _tempF;
  } else { // left>right
    FNumber _tempF(lhs);
    _tempF -= rhs;
    return _tempF;
  }
}

/// \brief Subtraction with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator-(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF = _tempF - rhs;
  return _tempF;
}

/// \brief Subtraction with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator-(const FNumber& lhs, T rhs) {
  FNumber _tempF(rhs);
  _tempF = lhs - _tempF;
  return _tempF;
}

/// \brief Multiplication
inline FNumber operator*(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.FNprec() == rhs.FNprec()) { // left=right
    FNumber _tempF(lhs);
    _tempF *= rhs;
    return _tempF;
  } else if (lhs.FNprec() < rhs.FNprec()) { // left<right
    FNumber _tempF(rhs);
    _tempF *= lhs;
    return _tempF;
  } else { // left>right
    FNumber _tempF(lhs);
    _tempF *= rhs;
    return _tempF;
  }
}

/// \brief Multiplication with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator*(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF = _tempF * rhs;
  return _tempF;
}

/// \brief Multiplication with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator*(const FNumber& lhs, T rhs) {
  FNumber _tempF(rhs);
  _tempF = _tempF * lhs;
  return _tempF;
}

/// \brief Division
inline FNumber operator/(const FNumber& lhs, const FNumber& rhs) {
  ikos_assert_msg(!mpfr_zero_p(rhs.FNvalue()), "division by zero");
  if (lhs.FNprec() == rhs.FNprec()) { // left=right
    FNumber _tempF(lhs);
    _tempF /= rhs;
    return _tempF;
  } else if (lhs.FNprec() < rhs.FNprec()) { // left<right
    FNumber _tempF(lhs);
    _tempF /= rhs;
    return _tempF;
  } else { // left>right
    FNumber _tempF(lhs);
    _tempF /= rhs;
    return _tempF;
  }
}

/// \brief Division with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator/(T lhs, const FNumber& rhs) {
  FNumber _tempF(lhs);
  _tempF = _tempF / rhs;
  return _tempF;
}

/// \brief Division with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber operator/(const FNumber& lhs, T rhs) {
  FNumber _tempF(rhs);
  _tempF = lhs / _tempF;
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
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator==(const FNumber& lhs, T rhs) {
  FNumber _rhsFN(rhs);
  return mpfr_equal_p(lhs.FNvalue(), _rhsFN.FNvalue());
}

/// \brief Equality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator==(T lhs, const FNumber& rhs) {
  FNumber _lhsFN(lhs);
  return mpfr_equal_p(rhs.FNvalue(), _lhsFN.FNvalue());
}

/// \brief Inequality operator
inline bool operator!=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_lessgreater_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Inequality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator!=(const FNumber& lhs, T rhs) {
  FNumber _rhsFN(rhs);
  return mpfr_lessgreater_p(lhs.FNvalue(), _rhsFN.FNvalue());
}

/// \brief Inequality operator with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator!=(T lhs, const FNumber& rhs) {
  FNumber _lhsFN(lhs);
  return mpfr_lessgreater_p(rhs.FNvalue(), _lhsFN.FNvalue());
}

/// \brief Less than comparison
inline bool operator<(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_less_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Less than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator<(const FNumber& lhs, T rhs) {
  FNumber _rhsFN(rhs);
  return mpfr_less_p(lhs.FNvalue(), _rhsFN.FNvalue());
}

/// \brief Less than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator<(T lhs, const FNumber& rhs) {
  FNumber _lhsFN(lhs);
  return mpfr_less_p(_lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Less or equal comparison
inline bool operator<=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_lessequal_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Less or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator<=(const FNumber& lhs, T rhs) {
  FNumber _rhsFN(rhs);
  return mpfr_less_p(lhs.FNvalue(), _rhsFN.FNvalue());
}

/// \brief Less or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator<=(T lhs, const FNumber& rhs) {
  FNumber _lhsFN(lhs);
  return mpfr_lessequal_p(_lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Greater than comparison
inline bool operator>(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_greater_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Greater than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator>(const FNumber& lhs, T rhs) {
  FNumber _rhsFN(rhs);
  return mpfr_greater_p(lhs.FNvalue(), _rhsFN.FNvalue());
}

/// \brief Greater than comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator>(T lhs, const FNumber& rhs) {
  FNumber _lhsFN(lhs);
  return mpfr_greater_p(_lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Greater or equal comparison
inline bool operator>=(const FNumber& lhs, const FNumber& rhs) {
  return mpfr_greaterequal_p(lhs.FNvalue(), rhs.FNvalue());
}

/// \brief Greater or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator>=(const FNumber& lhs, T rhs) {
  FNumber _rhsFN(rhs);
  return mpfr_greaterequal_p(lhs.FNvalue(), _rhsFN.FNvalue());
}

/// \brief Greater or equal comparison with floating point types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline bool operator>=(T lhs, const FNumber& rhs) {
  FNumber _lhsFN(lhs);
  return mpfr_greaterequal_p(_lhsFN.FNvalue(), rhs.FNvalue());
}

/// \brief Return the smaller of the given numbers
inline const FNumber& min(const FNumber& a, const FNumber& b) {
  return (a < b) ? a : b;
}

/// \brief Return the smaller of the given numbers
inline const FNumber& min(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c) {
  return min(min(a, b), c);
}

/// \brief Return the smaller of the given numbers
inline const FNumber& min(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c,
                          const FNumber& d) {
  return min(min(min(a, b), c), d);
}

/// \brief Return the greater of the given numbers
inline const FNumber& max(const FNumber& a, const FNumber& b) {
  return (a < b) ? b : a;
}

/// \brief Return the greater of the given numbers
inline const FNumber& max(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c) {
  return max(max(a, b), c);
}

/// \brief Return the greater of the given numbers
inline const FNumber& max(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c,
                          const FNumber& d) {
  return max(max(max(a, b), c), d);
}

/// \brief Integer floating point number
inline FNumber mod(const FNumber& lhs, const FNumber& rhs) {
  ZNumber z(mod(lhs.to_z_number(), rhs.to_z_number()));
  FNumber f(z.to< int >());
  return f;
}

/// \brief Absolute value
inline FNumber abs(const FNumber& n) {
  mpfr_t _m;
  mpfr_init2(_m, n.FNprec());
  mpfr_abs(_m, n.FNvalue(), MPFR_RNDN);
  FNumber m(_m, MPFR_RNDN);
  mpfr_clear(_m);
  return m;
}

/// \brief Return the greatest common divisor of the given numbers
///
/// The result is always positive even if one or both input operands are
/// negative. Except if both inputs are zero; then this function defines
/// `gcd(0, 0) = 0`.
inline FNumber gcd(const FNumber& lhs, const FNumber& rhs) {
  ZNumber z(gcd(lhs.to_z_number(), rhs.to_z_number()));
  FNumber f(z.to< int >());
  return f;
}

/// \brief Return the greatest common divisor of the given numbers
inline FNumber gcd(const FNumber& a, const FNumber& b, const FNumber& c) {
  return gcd(gcd(a, b), c);
}

/// \brief Return the least common multiple of the given numbers
inline FNumber lcm(const FNumber& lhs, const FNumber& rhs) {
  ZNumber z(lcm(lhs.to_z_number(), rhs.to_z_number()));
  FNumber f(z.to< int >());
  return f;
}

/// \todo bugs here!!!
/// \brief Run Euclid's algorithm
///
/// Compute `g = gcd(a, b)` and `u`, `v` such that `g = a*u + b*v`
//
/// The value in `g` is always positive, even if one or both of `a` and `b` are
/// negative (or zero if both inputs are zero).
// inline void gcd_extended(
//     const FNumber& a, const FNumber& b, FNumber& g, FNumber& u, FNumber& v) {
//   const ZNumber A = a.toZNumber();
//   const ZNumber B = b.toZNumber();
//   mpz_gcdext(g.toZNumber().mpz().get_mpz_t(),
//              u.toZNumber().mpz().get_mpz_t(),
//              v.toZNumber().mpz().get_mpz_t(),
//              A.mpz().get_mpz_t(),
//              B.mpz().get_mpz_t());
// }

/// @}
/// \name Mathematical function
/// @{
// All by zoush99

/// \brief Return the logarithm of the given number. log2(antilogarithm)
inline FNumber log2(const FNumber& antilogarithm) {
  mpfr_t n;
  mpfr_init2(n, antilogarithm.FNprec());
  mpfr_log2(n, antilogarithm.FNvalue(), MPFR_RNDN);
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n); // clear temporary variables. By zoush99
  return f;
}

/// \brief Return the natural logarithm of the given number. ln(antilogarithm)
inline FNumber ln(const FNumber& antilogarithm) {
  mpfr_t n;
  mpfr_init2(n, antilogarithm.FNprec());
  mpfr_log(n, antilogarithm.FNvalue(), MPFR_RNDN);
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n); // clear temporary variables. By zoush99
  return f;
}

/// \brief Return the logarithm of the given number. log10(antilogarithm)
inline FNumber log10(const FNumber& antilogarithm) {
  mpfr_t n;
  mpfr_init2(n, antilogarithm.FNprec());
  mpfr_log10(n, antilogarithm.FNvalue(), MPFR_RNDN);
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the exponential of the given number. 2(exponent)
inline FNumber exp2(const FNumber& exponent) {
  mpfr_t n;
  mpfr_init2(n, exponent.FNprec()); // default
  mpfr_exp2(n, exponent.FNvalue(), MPFR_RNDN);
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the exponential of the given number. e(exponent)
inline FNumber exp(const FNumber& exponent) {
  mpfr_t n;
  mpfr_init2(n, exponent.FNprec());
  mpfr_exp(n, exponent.FNvalue(), MPFR_RNDN);
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the exponential of the given number. 10(exponent)
inline FNumber exp10(const FNumber& exponent) {
  mpfr_t n;
  mpfr_init2(n, exponent.FNprec());
  mpfr_exp10(n, exponent.FNvalue(), MPFR_RNDN);
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \todo bugs here!!!
/// \brief Return the power of the given number. base**(exponent)
inline FNumber pow(const FNumber& base, const FNumber& exponent) {
  mpfr_t n;
  mpfr_init2(n, exponent.FNprec());
  mpfr_pow(n,
           base.FNvalue(),
           exponent.FNvalue(),
           MPFR_RNDN); // Result difference between mpfr_powr? By zoush99
  FNumber f(n, MPFR_RNDN);
  mpfr_clear(n);
  return f;
}

/// \brief Return the sin of the given curve number. sin(n): sin(pi/3)
inline FNumber sin(const FNumber& f) {
  mpfr_t n;
  mpfr_init2(n, f.FNprec());
  mpfr_sin(n, f.FNvalue(), MPFR_RNDN);
  FNumber e(n, MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brief Return the cos of the given curve number. cos(n): cos(pi/3)
inline FNumber cos(const FNumber& f) {
  mpfr_t n;
  mpfr_init2(n, f.FNprec());
  mpfr_cos(n, f.FNvalue(), MPFR_RNDN);
  FNumber e(n, MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brief Return the tan of the given curve number. tan(n): tan(pi/3)
inline FNumber tan(const FNumber& f) {
  mpfr_t n;
  mpfr_init2(n, f.FNprec());
  mpfr_tan(n, f.FNvalue(), MPFR_RNDN);
  FNumber e(n, MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brirf Return the sin of the given degree number. sin(n): sin(120)
inline FNumber sinu(const FNumber& f) {
  mpfr_t n;
  mpfr_init2(n, f.FNprec());
  mpfr_sinu(n, f.FNvalue(), 360, MPFR_RNDN);
  FNumber e(n, MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brirf Return the cos of the given degree number. cos(n): cos(120)
inline FNumber cosu(const FNumber& f) {
  mpfr_t n;
  mpfr_init2(n, f.FNprec());
  mpfr_cosu(n, f.FNvalue(), 360, MPFR_RNDN);
  FNumber e(n, MPFR_RNDN);
  mpfr_clear(n);
  return e;
}

/// \brirf Return the tan of the given degree number. tan(n): tan(120)
inline FNumber tanu(const FNumber& f) {
  mpfr_t n;
  mpfr_init2(n, f.FNprec());
  mpfr_tanu(n, f.FNvalue(), 360, MPFR_RNDN);
  FNumber e(n, MPFR_RNDN);
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
           class = std::enable_if_t< IsSupportedIntegralFloat< T >::value > >
inline FNumber retPi() {
  T f = 1;
  FNumber Pi(f);
  mpfr_t n;
  mpfr_init2(n, Pi.FNprec());
  mpfr_const_pi(n, MPFR_RNDN);
  Pi.setFN(n, Pi.FNprec(), MPFR_RNDN);
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

/// \brief Read a FNumber from a stream, in base 10
inline std::istream& operator>>(std::istream& i, FNumber& n) {
  double _d = mpfr_get_d(n.FNvalue(), MPFR_RNDN);
  i >> _d;
  return i;
}

/// @}
} // namespace core
} // namespace ikos