// ====================================================================== BEGIN FILE =====
// **                              A B S O L U T E D A T E                              **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2013-2019, Stephen W. Soliday                                      **
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
/** @brief  Absolute Date
 *  @file   AbsoluteDate.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the methods for a class to maintain date and time functions.
 */
// =======================================================================================


#include <AbsoluteDate.hh>

// =======================================================================================
// ---------------------------------------------------------------------------------------
  void AbsoluteDate::set( const int32_t yr, const int32_t mo, const int32_t da,
                      const int32_t hr, const int32_t mn, const real8_t sc,
                      const int32_t ut ) {
  // -------------------------------------------------------------------------------------
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  real8_t AbsoluteDate::getJD( void ) const {
  // -------------------------------------------------------------------------------------
    return epoch.span / 8.64e4;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  int32_t AbsoluteDate::getYear( void ) const {
  // -------------------------------------------------------------------------------------
    return 0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  int32_t AbsoluteDate::getMonth( void ) const {
  // -------------------------------------------------------------------------------------
    return 0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  int32_t AbsoluteDate::getDay( void ) const {
  // -------------------------------------------------------------------------------------
    return 0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  int32_t AbsoluteDate::getDayOfYear( void ) const {
  // -------------------------------------------------------------------------------------
    return 0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  int32_t AbsoluteDate::getHour( void ) const {
  // -------------------------------------------------------------------------------------
    return 0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  int32_t AbsoluteDate::getMinute( void ) const {
  // -------------------------------------------------------------------------------------
    return 0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  real8_t AbsoluteDate::getSecond( void ) const {
  // -------------------------------------------------------------------------------------
    return 0.0;
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  void AbsoluteDate::fromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  }


// =======================================================================================
// ---------------------------------------------------------------------------------------
  std::string AbsoluteDate::toString( void ) const {
  // -------------------------------------------------------------------------------------
    return "1970-01-01T00:00:00Z";
  }

// =======================================================================================
// **                              A B S O L U T E D A T E                              **
// ======================================================================== END FILE =====