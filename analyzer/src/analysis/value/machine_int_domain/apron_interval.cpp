/*******************************************************************************
 *
 * \file
 * \brief Implement make_(top|bottom)_machine_int_apron_interval
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

#ifdef HAS_APRON
#include <ikos/core/domain/machine_int/numeric_domain_adapter.hpp>
#include <ikos/core/domain/numeric/apron.hpp>
#endif

#include <ikos/analyzer/analysis/value/machine_int_domain.hpp>
#include <ikos/analyzer/exception.hpp>

namespace ikos {
namespace analyzer {
namespace value {

#ifdef HAS_APRON
namespace {

//using RuntimeNumericDomain = core::numeric::
//    ApronDomain< core::numeric::apron::Interval, ZNumber, Variable* >;
// By zoush99
using RuntimeNumericDomain = core::numeric::
    ApronDomain< core::numeric::apron::Interval, FNumber, Variable* >;
using RuntimeMachineIntDomain =
    core::machine_int::NumericDomainAdapter< Variable*, RuntimeNumericDomain >;

} // end anonymous namespace
#endif

MachineIntAbstractDomain make_top_machine_int_apron_interval() {
#ifdef HAS_APRON
  return MachineIntAbstractDomain(
      RuntimeMachineIntDomain(RuntimeNumericDomain::top()));
#else
  throw LogicError("ikos was compiled without apron support");
#endif
}

MachineIntAbstractDomain make_bottom_machine_int_apron_interval() {
#ifdef HAS_APRON
  return MachineIntAbstractDomain(
      RuntimeMachineIntDomain(RuntimeNumericDomain::bottom()));
#else
  throw LogicError("ikos was compiled without apron support");
#endif
}

} // end namespace value
} // end namespace analyzer
} // end namespace ikos
