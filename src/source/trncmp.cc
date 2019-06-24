// ====================================================================== BEGIN FILE =====
// **                                    T R N C M P                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1993-2019, Stephen W. Soliday                                      **
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
/** @brief  Basic functions
 *  @file   trncmp.cc
 *  @author Stephen W. Soliday
 *  @date   1993-09-18  Original release.
 *  @date   2009-01-28  Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
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
const char* trncmpAuthor() {
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
const char* trncmpVersion() {
  // -------------------------------------------------------------------------------------
  return "3.0.1";
}


// ==========================================================================================
/** @brief Show Time.
 *  @param o     reference to a stream object.
 *  @param hours time expressed in hours.
 *
 *  Decompose hours into hours minutes and seconds appropriate for display.
 */
// ------------------------------------------------------------------------------------------
void ShowTime( std::ostream& o, real8_t hours ) {
  // ----------------------------------------------------------------------------------------
  real8_t x = hours;
  real8_t h = floor(x);
  
  x = (x - h)*60.0;
  real8_t m = floor(x);
  
  x = (x - m)*60.0;
  real8_t s = floor(x+0.5);
  
  o << h << ":"
    << m << ":"
    << s;
}


// =======================================================================================
// **                                    T R N C M P                                    **
// ======================================================================== END FILE =====
