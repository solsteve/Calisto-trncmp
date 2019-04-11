// ====================================================================== BEGIN FILE =====
// **                                    T R N C M P                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This program is free software: you can redistribute it and/or modify it under    **
// **  the terms of the GNU General Public License as published by the Free Software    **
// **  Foundation, either version 3 of the License, or (at your option)                 **
// **  any later version.                                                               **
// **                                                                                   **
// **  This program is distributed in the hope that it will be useful, but WITHOUT      **
// **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
// **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
// **                                                                                   **
// **  You should have received a copy of the GNU General Public License along with     **
// **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
// **                                                                                   **
// ----- Modification History ------------------------------------------------------------
//
/** @brief  Basic functions
 *  @file   trncmp.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-11
 *
 *  This is the minimum set of functions to be built.
 */
// =======================================================================================

#include <trncmp.hh>

// =======================================================================================
/** @brief Author
 *  @return name of the author
 *
 *  This function returns the name of the author
 */
// ---------------------------------------------------------------------------------------
const char* author() {
  // -------------------------------------------------------------------------------------
  return "Stephen Soliday";
}

// =======================================================================================
/** @brief Version
 *  @return name the version number
 *
 *  This function returns the version number of this build
 */
// ---------------------------------------------------------------------------------------
const char* version() {
  // -------------------------------------------------------------------------------------
  return "3.0.1";
}

// =======================================================================================
// **                                    T R N C M P                                    **
// ======================================================================== END FILE =====
