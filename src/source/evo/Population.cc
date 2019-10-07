// ====================================================================== BEGIN FILE =====
// **                           E V O : : P O P U L A T I O N                           **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1995-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  Callisto is free software: you can redistribute it and/or modify it under the    **
// **  terms of the GNU General Public License as published by the Free Software        **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  Callisto is distributed in the hope that it will be useful, but WITHOUT          **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  Callisto. If not, see <https://www.gnu.org/licenses/>.                           **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief Population.
 *  @file   evo/Population.cc
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-29 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-11 Ported to HPSP Java.
 *  @date   2019-Sep-27 CMake refactorization.
 *
 *  Provides the abstract interface for an encoding.
 */
// =======================================================================================


#include <evo/Population.hh>


namespace evo {

// =======================================================================================
  /** @brief Constructor.
   *  @param[in] mod pointer to a Model for memory allocation.
   */
// ---------------------------------------------------------------------------------------
Population::Member::Member( Model* mod ) : met(0), enc(0), age(0) {
  // -------------------------------------------------------------------------------------
  met = mod->alloc_metric();
  enc = mod->alloc_encoding();
  age = 0;
  met->zero();
}


// =======================================================================================
  /** @brief Destructor.
   */
// ---------------------------------------------------------------------------------------
Population::Member::~Member( void ) {
  // -------------------------------------------------------------------------------------
  delete met;
  delete enc;
}


// =======================================================================================
  /** @brief Copy.
   *  @param[in] src pointer to a source PopulationMember
   */
// ---------------------------------------------------------------------------------------
void Population::Member::copy( Member* src ) {
  // -------------------------------------------------------------------------------------
    met->copy( src->met );
    enc->copy(  src->enc );
    age = src->age;
}

}; // end namespace evo


// =======================================================================================
// **                           E V O : : P O P U L A T I O N                           **
// =========================================================================== END FILE ==
