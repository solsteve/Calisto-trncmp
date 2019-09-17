// ====================================================================== BEGIN FILE =====
// **                                F U Z Z Y : : S E T                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2014-2019, Stephen W. Soliday                                      **
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
/** @brief  Fuzzy Set.
 *  @file   fuzzy/Set.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-06 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the methods for a fuzzy set.
 */
// =======================================================================================


#include <fuzzy/Set.hh>


namespace fuzzy {


// =======================================================================================
// ---------------------------------------------------------------------------------------
Set::Set( void ) : L(D_ZERO), C(D_ZERO), R(D_ZERO) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
Set::~Set( void ) {
  // -------------------------------------------------------------------------------------
}


}; // end namespace fuzzy


// =======================================================================================
// **                                F U Z Z Y : : S E T                                **
// ======================================================================== END FILE =====
