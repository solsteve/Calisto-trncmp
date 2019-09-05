// ====================================================================== BEGIN FILE =====
// **                                  D A T E T I M E                                  **
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
/** @brief  Date and Time
 *  @file   DateTime.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the methods for a class to maintain date and time functions.
 */
// =======================================================================================


#include <DateTime.hh>
#include <ISO8601.hh>


// =======================================================================================
/** @brief Compare.
 *  @param[in] dt reference to another DateTime.
 *  @return -1 if dt is less than this,
 *           0 if dt and this are equal,
 *          +1 if dt is greater than this.
 *
 *  Compare another DateTime to this one.
 */
// ---------------------------------------------------------------------------------------
inline  int DateTime::compare( DateTime& dt ) {
  // -------------------------------------------------------------------------------------
  const int dc = date_comp.compare( dt.date_comp );
  if ( 0 > dc ) { return -1; }
  if ( 0 < dc ) { return +1; }
  
  const int tc = time_comp.compare( dt.time_comp );
  if ( 0 > tc ) { return -1; }
  if ( 0 < tc ) { return +1; }
  return 0;
}


// =======================================================================================
/** @brief Compare.
 *  @param[in] dt reference to another DateTime.
 *  @return true if all of the components are exactly equal.
 *
 *  Compare another DateTime to this one.
 */
// ---------------------------------------------------------------------------------------
inline  bool DateTime::equals( DateTime& dt ) {
  // -------------------------------------------------------------------------------------
  return
      date_comp.equals( dt.date_comp ) &&
      time_comp.equals( dt.time_comp );
}


// =======================================================================================
/** @brief To String.
 *  @return ISO8601 formated date & Time.
 */
// ---------------------------------------------------------------------------------------
std::string DateTime::toString( void ) const {
  // -------------------------------------------------------------------------------------
  ISO8601 P;

  P.setDate( date_comp.getYear(),
             date_comp.getMonth(),
             date_comp.getDay() );

  if ( isNotZero( time_comp.getSecondsInUTCDay() ) ) {
    P.setTime( time_comp.getHour(),
               time_comp.getMinute(),
               time_comp.getSecond(),
               time_comp.getMinutesFromUTC() );
  }
  
  return P.toString();
}


// =======================================================================================
/** @brief From String.
 *  @param[in] str
 *  @return ISO8601 formated date & time string.
 */
// ---------------------------------------------------------------------------------------
DateTime DateTime::fromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  ISO8601 P( str );

  int32_t yr = P.getYear();
  int32_t mo = P.getMonth();
  int32_t da = P.getDay();
  int32_t hr = P.getHour();
  int32_t mn = P.getMinute();
  real8_t sc = P.getSecond();
  int32_t ut = P.getOffset();

  return DateTime(yr,mo,da,hr,mn,sc,ut);
}


// =======================================================================================
// **                                  D A T E T I M E                                  **
// ======================================================================== END FILE =====
