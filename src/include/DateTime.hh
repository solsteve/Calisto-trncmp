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
 *  @file   DateTime.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the interface for a class to maintain date and time functions.
 */
// =======================================================================================


#ifndef __HH_DATETIME_TRNCMP
#define __HH_DATETIME_TRNCMP

#include <DateComponents.hh>
#include <TimeComponents.hh>


// =======================================================================================
class DateTime {
  // -------------------------------------------------------------------------------------
 protected:

  DateComponents date_comp;
  TimeComponents time_comp;
  
 public:
  DateTime ( void );
  DateTime ( const DateComponents& DC, const TimeComponents& TC );

  DateTime ( const int32_t yr,   const int32_t mo=0, const int32_t da=0,
             const int32_t hr=0, const int32_t mn=0, const real8_t sc=D_ZERO, int32_t ut=0 );

  DateTime&       operator=  ( const DateTime& ) = default;

  int             compare    ( DateTime& dt );
  bool            equals     ( DateTime& dt );

  void            set        ( const int32_t yr,   const int32_t mo=0, const int32_t da=0,
                               const int32_t hr=0, const int32_t mn=0, const real8_t sc=D_ZERO,
                               const int32_t ut=0 );
  
  DateComponents  getDate    ( void );
  TimeComponents  getTime    ( void );

  std::string     toString   ( void ) const;
  static DateTime fromString ( std::string str );
  
}; // end class DateTime


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  DateTime::DateTime( void ) : date_comp(), time_comp() {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
inline  DateTime::DateTime( const DateComponents& DC, const TimeComponents& TC ) :
    date_comp(DC), time_comp(TC) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] yr year.         (required)
 *  @param[in] mo month.        (defualt: 0)
 *  @param[in] da day of month. (defualt: 0)
 *  @param[in] hr hour.         (defualt: 0)
 *  @param[in] mn minute.       (defualt: 0)
 *  @param[in] sc second.       (defualt: 0.000)
 *
 *  Construct a new DateTime instance from a calendar date.
 */
// ---------------------------------------------------------------------------------------
inline  DateTime::DateTime ( const int32_t yr, const int32_t mo, const int32_t da,
                             const int32_t hr, const int32_t mn, const real8_t sc,
                             const int32_t ut ) :
    date_comp(yr,mo,da), time_comp(hr,mn,sc,ut)  {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  void DateTime::set( const int32_t yr, const int32_t mo, const int32_t da,
                            const int32_t hr, const int32_t mn, const real8_t sc,
                            const int32_t ut ) {
  // -------------------------------------------------------------------------------------
  date_comp.set(yr,mo,da);
  time_comp.set(hr,mn,sc,ut);
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  DateComponents DateTime::getDate( void ) {
  // -------------------------------------------------------------------------------------
  return date_comp;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  TimeComponents DateTime::getTime( void ) {
  // -------------------------------------------------------------------------------------
  return time_comp;
}


#endif


// =======================================================================================
// **                                  D A T E T I M E                                  **
// ======================================================================== END FILE =====
