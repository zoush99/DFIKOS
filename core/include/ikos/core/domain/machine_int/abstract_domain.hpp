/*******************************************************************************
 *
 * \file
 * \brief Generic API for machine integer abstract domains
 *
 * Author: Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2018-2019 United States Government as represented by the
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

#include <ikos/core/domain/abstract_domain.hpp>
#include <ikos/core/domain/machine_int/operator.hpp>
#include <ikos/core/linear_expression.hpp>
#include <ikos/core/number/machine_int.hpp>
#include <ikos/core/semantic/machine_int/variable.hpp>
#include <ikos/core/semantic/variable.hpp>
#include <ikos/core/value/machine_int/congruence.hpp>
#include <ikos/core/value/machine_int/interval.hpp>
#include <ikos/core/value/machine_int/interval_congruence.hpp>

namespace ikos {
namespace core {
namespace machine_int {

/// \brief Base class for machine integer abstract domains
template < typename VariableRef, typename Derived >
class AbstractDomain : public core::AbstractDomain< Derived > {
public:
  static_assert(
      core::IsVariable< VariableRef >::value,
      "VariableRef does not meet the requirements for variable types");
  static_assert(machine_int::IsVariable< VariableRef >::value,
                "VariableRef must implement machine_int::VariableTraits");

public:
  using LinearExpressionT = LinearExpression< MachineInt, VariableRef >;
  using LinearExpressionF=LinearExpression<FNumber,VariableRef>;  // By zoush99

public:
  /// \brief Perform the widening of two abstract values with a threshold
  virtual void widen_threshold_with(const Derived& other,
                                    const MachineInt& threshold) = 0;

  /// \brief Perform the widening of two abstract values with a threshold
  virtual void widen_threshold_with(const Derived& other,
                                    const FNumber& threshold) = 0;

  /// \brief Perform the widening of two abstract values with a threshold
  virtual Derived widening_threshold(const Derived& other,
                                     const MachineInt& threshold) const {
    Derived tmp(static_cast< const Derived& >(*this));
    tmp.widen_threshold_with(other, threshold);
    return tmp;
  }

  /// \brief Perform the widening of two abstract values with a threshold
  virtual Derived widening_threshold(const Derived& other,
                                     const FNumber& threshold) const {
    Derived tmp(static_cast< const Derived& >(*this));
    tmp.widen_threshold_with(other, threshold);
    return tmp;
  }

  /// \brief Perform the narrowing of two abstract values with a threshold
  virtual void narrow_threshold_with(const Derived& other,
                                     const MachineInt& threshold) = 0;

  /// \brief Perform the narrowing of two abstract values with a threshold
  virtual void narrow_threshold_with(const Derived& other,
                                     const FNumber& threshold) = 0;

  /// \brief Perform the narrowing of two abstract values with a threshold
  virtual Derived narrowing_threshold(const Derived& other,
                                      const MachineInt& threshold) const {
    Derived tmp(static_cast< const Derived& >(*this));
    tmp.narrow_threshold_with(other, threshold);
    return tmp;
  }

  /// \brief Perform the narrowing of two abstract values with a threshold
  virtual Derived narrowing_threshold(const Derived& other,
                                      const FNumber& threshold) const {
    Derived tmp(static_cast< const Derived& >(*this));
    tmp.narrow_threshold_with(other, threshold);
    return tmp;
  }

  /// \brief Assign `x = n`
  virtual void assign(VariableRef x, const MachineInt& n) = 0;

  /// \brief Assign `x = n`
  virtual void assign(VariableRef x, const FNumber& n) = 0;

  /// \brief Assign `x = y`
  virtual void assign(VariableRef x, VariableRef y) = 0;

  /// \brief Assign `x = e`
  ///
  /// Note that it wraps on integer overflow.
  /// Note that it will automatically cast variables to the type of `x`.
  virtual void assign(VariableRef x, const LinearExpressionT& e) = 0;

  /// \brief Assign `x = e`. By zoush99
  virtual void assign(VariableRef x, const LinearExpressionF& e)=0;

  /// \brief Apply `x = op y`
  virtual void apply(UnaryOperator op, VariableRef x, VariableRef y) = 0;

  /// \brief Apply `x = y op z`
  virtual void apply(BinaryOperator op,
                     VariableRef x,
                     VariableRef y,
                     VariableRef z) = 0;

  /// \brief Apply `x = y op z`
  virtual void apply(BinaryOperator op,
                     VariableRef x,
                     VariableRef y,
                     const MachineInt& z) = 0;

  /// \brief Apply `x = y op z`
  virtual void apply(BinaryOperator op,
                     VariableRef x,
                     VariableRef y,
                     const FNumber& z) = 0;

  /// \brief Apply `x = y op z`
  virtual void apply(BinaryOperator op,
                     VariableRef x,
                     const MachineInt& y,
                     VariableRef z) = 0;

  /// \brief Apply `x = y op z`
  virtual void apply(BinaryOperator op,
                     VariableRef x,
                     const FNumber& y,
                     VariableRef z) = 0;

  // \brief Add the constraint `x pred y`
  virtual void add(Predicate pred, VariableRef x, VariableRef y) = 0;

  // \brief Add the constraint `x pred y`
  virtual void add(Predicate pred, VariableRef x, const MachineInt& y) = 0;

  // \brief Add the constraint `x pred y`
  virtual void add(Predicate pred, VariableRef x, const FNumber& y) = 0;

  // \brief Add the constraint `x pred y`
  virtual void add(Predicate pred, const MachineInt& x, VariableRef y) {
    switch (pred) {
      case Predicate::EQ: {
        this->add(Predicate::EQ, y, x);
      } break;
      case Predicate::NE: {
        this->add(Predicate::NE, y, x);
      } break;
      case Predicate::GT: {
        this->add(Predicate::LT, y, x);
      } break;
      case Predicate::GE: {
        this->add(Predicate::LE, y, x);
      } break;
      case Predicate::LT: {
        this->add(Predicate::GT, y, x);
      } break;
      case Predicate::LE: {
        this->add(Predicate::GE, y, x);
      } break;
    }
  }

  // \brief Add the constraint `x pred y`
  virtual void add(Predicate pred, const FNumber& x, VariableRef y) {
    switch (pred) {
      case Predicate::EQ: {
        this->add(Predicate::EQ, y, x);
      } break;
      case Predicate::NE: {
        this->add(Predicate::NE, y, x);
      } break;
      case Predicate::GT: {
        this->add(Predicate::LT, y, x);
      } break;
      case Predicate::GE: {
        this->add(Predicate::LE, y, x);
      } break;
      case Predicate::LT: {
        this->add(Predicate::GT, y, x);
      } break;
      case Predicate::LE: {
        this->add(Predicate::GE, y, x);
      } break;
    }
  }

  /// \brief Set the interval value of a variable
  virtual void set(VariableRef x, const Interval& value) = 0;

  /// \brief Set the congruence value of a variable
  virtual void set(VariableRef x, const Congruence& value) = 0;

  /// \brief Set the interval-congruence value of a variable
  virtual void set(VariableRef x, const IntervalCongruence& value) = 0;

  /// \brief Refine the value of a variable with an interval
  virtual void refine(VariableRef x, const Interval& value) = 0;

  /// \brief Refine the value of a variable with a congruence
  virtual void refine(VariableRef x, const Congruence& value) = 0;

  /// \brief Refine the value of a variable with an interval-congruence
  virtual void refine(VariableRef x, const IntervalCongruence& value) = 0;

  /// \brief Forget a variable
  virtual void forget(VariableRef x) = 0;

  /// \brief Projection to an interval
  ///
  /// Return an overapproximation of the value of `x` as an interval
  virtual Interval to_interval(VariableRef x) const = 0;

  /// \brief Projection to an interval
  ///
  /// Return an overapproximation of the linear expression `e` as an interval
  ///
  /// Note that it wraps on integer overflow.
  /// Note that it will automatically cast variables to the type of
  /// `e.constant()`.
  virtual Interval to_interval(const LinearExpressionT& e) const = 0;

  /// \brief Projection to an interval. By zoush99
  virtual Interval to_interval(const LinearExpressionF& e) const = 0;

  /// \brief Projection to a congruence
  ///
  /// Return an overapproximation of the value of `x` as a congruence
  virtual Congruence to_congruence(VariableRef x) const = 0;

  /// \brief Projection to a congruence
  ///
  /// Return an overapproximation of the linear expression `e` as a congruence
  ///
  /// Note that it wraps on integer overflow.
  /// Note that it will automatically cast variables to the type of
  /// `e.constant()`.
  virtual Congruence to_congruence(const LinearExpressionT& e) const = 0;

  /// \brief Projection to an interval-congruence
  ///
  /// Return an overapproximation of the value of `x` as an interval-congruence
  virtual IntervalCongruence to_interval_congruence(VariableRef x) const = 0;

  /// \brief Projection to an interval-congruence
  ///
  /// Return an overapproximation of the linear expression `e` as an
  /// interval-congruence
  ///
  /// Note that it wraps on integer overflow.
  /// Note that it will automatically cast variables to the type of
  /// `e.constant()`.
  virtual IntervalCongruence to_interval_congruence(
      const LinearExpressionT& e) const = 0;

  /// \name Non-negative loop counter abstract domain methods
  /// @{

  /// \brief Mark the variable `x` as a non-negative loop counter
  virtual void counter_mark(VariableRef /*x*/) {}

  /// \brief Mark the variable `x` as a normal variable, without losing
  /// information
  virtual void counter_unmark(VariableRef /*x*/) {}

  /// \brief Initialize a non-negative loop counter: `x = c`
  ///
  /// Precondition: `c >= 0`
  virtual void counter_init(VariableRef x, const MachineInt& c) {
    this->assign(x, c);
  }

  /// \brief Increment a non-negative loop counter counter: `x += k`
  ///
  /// Precondition: `k >= 0`
  virtual void counter_incr(VariableRef x, const MachineInt& k) {
    this->apply(BinaryOperator::Add, x, x, k);
  }

  /// \brief Forget a non-negative loop counter
  virtual void counter_forget(VariableRef x) { this->forget(x); }

  /// @}

}; // end class AbstractDomain

/// \brief Check if a type is a machine integer abstract domain
template < typename T, typename VariableRef >
struct IsAbstractDomain
    : std::is_base_of< machine_int::AbstractDomain< VariableRef, T >, T > {};

} // end namespace machine_int
} // end namespace core
} // end namespace ikos
