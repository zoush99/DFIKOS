/*******************************************************************************
 *
 * \file
 * \brief Operators for numerical abstract domains
 *
 * Author: Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2011-2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
 * ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
 * ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
 * ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
 * THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
 * ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
 * RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
 * RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 * DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
 * IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 *
 * Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
 * AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
 * IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
 * USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
 * RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 * HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
 * AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
 * RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
 * UNILATERAL TERMINATION OF THIS AGREEMENT.
 *
 ******************************************************************************/

#pragma once

#include <type_traits>

#include <ikos/core/number/f_number.hpp> // By zoush99
#include <ikos/core/number/q_number.hpp>
#include <ikos/core/number/z_number.hpp>

// zoush99 has modified.

namespace ikos {
namespace core {
namespace numeric {

/// \brief Unary floating point operations
enum class UnaryOperator {
  // Truncation, Extension, Symbol Conversion, Type Conversion. By zoush99
  Trunc,
  Ext,
  SignCast, // Realization
  Cast,
  FtoInteger,
  ZtoInteger,
};

/// \brief Transform between floating point and integer. By zoush99
enum class Transf {
  FlToIn, // Floating point to integer
  InToFl, // Integer to floating point
};

/// \brief Binary arithmetic operations
enum class BinaryOperator {
  /// \brief Addition
  Add,

  /// \brief Substraction
  Sub,

  /// \brief Multiplication
  Mul,

  /// \brief Division
  ///
  /// On integers (Z), this is the integer division with rounding towards zero.
  /// On rationals (Q), this is the exact division.
  /// On floating point number(F), this is the float division with rounding
  /// towards nearest. By zoush99
  Div,

  /// \brief Remainder
  ///
  /// On integers (Z), this is the integer remainder, see operator% on ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  Rem,

  /// \brief Modulo
  ///
  /// On integers (Z), this is the integer modulo, see mod() on ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  Mod,

  /// \brief Left binary shift
  ///
  /// On integers (Z), this is the left binary shift, see operator<< on ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  Shl,

  /// \brief Right binary shift
  ///
  /// On integers (Z), this is the right binary shift, see operator>> on
  /// ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  Shr,

  /// \brief Bitwise AND
  ///
  /// On integers (Z), this is the bitwise AND, see operator& on ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  And,

  /// \brief Bitwise OR
  ///
  /// On integers (Z), this is the bitwise OR, see operator| on ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  Or,

  /// \brief Bitwise XOR
  ///
  /// On integers (Z), this is the bitwise XOR, see operator^ on ZNumber.
  /// This is undefined on rationals.
  /// This is undefined on floating points. By zoush99
  Xor,
};

/// \brief Predicate on floating point numbers. By zoush99
enum class Predicate {
  EQ,
  NE,
  GT,
  GE,
  LT,
  LE,
};

/// \todo(Addition of unary arithmetic operations) By zoush99
/// \brief Apply a floating point unary operator on the given operands
template < typename T >
T apply_unary_operator(UnaryOperator op, const T& operand) {
  switch (op) {
      //    case UnaryOperator::Trunc:
      //      return operand.trunc(result_bit_width);
      //    case UnaryOperator::Ext:
      //      return operand.ext(result_bit_width);
    case UnaryOperator::SignCast:
      return operand.signcast();
      //    case UnaryOperator::Cast:
      //      return operand.cast(result_bit_width, result_sign);
  }
}

/// \brief Apply a floating point transformation between different types
template <typename T,typename F>  // T: (FNumber, ZNumber), F: (int, long int et al.)
F apply_trans_to_integer(UnaryOperator op, const T& operand){
  switch (op) {
    case UnaryOperator::FtoInteger:             // FNumber
      return operand.template toInteger< F >(); // Member variable
    case UnaryOperator::ZtoInteger:               // ZNumber
      return operand.template to< F >();
    default:
      ikos_unreachable("unreachable");
  }
}

/// \brief Get a textual representation of the given binary operator
inline const char* bin_operator_text(BinaryOperator op) {
  switch (op) {
    case BinaryOperator::Add:
      return "+";
    case BinaryOperator::Sub:
      return "-";
    case BinaryOperator::Mul:
      return "*";
    case BinaryOperator::Div:
      return "/";
    case BinaryOperator::Rem:
      return "%";
    case BinaryOperator::Mod:
      return "mod";
    case BinaryOperator::Shl:
      return "<<";
    case BinaryOperator::Shr:
      return ">>";
    case BinaryOperator::And:
      return "&";
    case BinaryOperator::Or:
      return "|";
    case BinaryOperator::Xor:
      return "^";
    default:
      ikos_unreachable("unsupported operator");
  }
}

namespace detail {

template < typename T, typename = void >
struct ApplyBinOperator {};

} // end namespace detail

/// \brief Apply an arithmetic binary operator on the given operands
template < typename T >
inline T apply_bin_operator(BinaryOperator op, const T& lhs, const T& rhs) {
    return detail::ApplyBinOperator< T >()(op, lhs, rhs);
}

namespace detail {

/// \brief Implementation for abstract values on ZNumber
template < typename T >
struct ApplyBinOperator<
    T,
    std::enable_if_t< std::is_same< typename T::NumberT, ZNumber >::value > > {
  inline T operator()(BinaryOperator op, const T& lhs, const T& rhs) const {
    switch (op) {
      case BinaryOperator::Add:
        return lhs + rhs;
      case BinaryOperator::Sub:
        return lhs - rhs;
      case BinaryOperator::Mul:
        return lhs * rhs;
      case BinaryOperator::Div:
        return lhs / rhs;
      case BinaryOperator::Rem:
        return lhs % rhs;
      case BinaryOperator::Mod:
        return mod(lhs, rhs);
      case BinaryOperator::Shl:
        return lhs << rhs;
      case BinaryOperator::Shr:
        return lhs >> rhs;
      case BinaryOperator::And:
        return lhs & rhs;
      case BinaryOperator::Or:
        return lhs | rhs;
      case BinaryOperator::Xor:
        return lhs ^ rhs;
      default:
        ikos_unreachable("unsupported operator");
    }
  }
};

/// \brief Implementation for abstract values on QNumber
template < typename T >
struct ApplyBinOperator<
    T,
    std::enable_if_t< std::is_same< typename T::NumberT, QNumber >::value > > {
  inline T operator()(BinaryOperator op, const T& lhs, const T& rhs) const {
    switch (op) {
      case BinaryOperator::Add:
        return lhs + rhs;
      case BinaryOperator::Sub:
        return lhs - rhs;
      case BinaryOperator::Mul:
        return lhs * rhs;
      case BinaryOperator::Div:
        return lhs / rhs;
      default:
        ikos_unreachable("unsupported operator");
    }
  }
};

/// \brief Implementation for abstract values on FNumber
// By zoush99
template < typename T >
struct ApplyBinOperator<
    T,
    std::enable_if_t< std::is_same< typename T::NumberT, FNumber >::value > > {
  inline T operator()(BinaryOperator op, const T& lhs, const T& rhs) const {
    switch (op) {
      case BinaryOperator::Add:
        return lhs + rhs;
      case BinaryOperator::Sub:
        return lhs - rhs;
      case BinaryOperator::Mul:
        return lhs * rhs;
      case BinaryOperator::Div:
        return lhs / rhs;
      default:
        ikos_unreachable("unsupported operator");
    }
  }
};

} // end namespace detail

/// \brief Compare the given operands with the given predicate
template < typename T >
bool compare(Predicate pred, const T& lhs, const T& rhs) {
  switch (pred) {
    case Predicate::EQ:
      return lhs == rhs;
    case Predicate::NE:
      return lhs != rhs;
    case Predicate::GT:
      return lhs > rhs;
    case Predicate::GE:
      return lhs >= rhs;
    case Predicate::LT:
      return lhs < rhs;
    case Predicate::LE:
      return lhs <= rhs;
    default:
      ikos_unreachable("unreachable");
  }
}
} // end namespace numeric
} // end namespace core
} // end namespace ikos
