// ====================================================================== BEGIN FILE =====
// **                            T I M E C O M P O N E N T S                            **
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
/** @brief  Time Components
 *  @file   TimeComponents.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the interface for a class to maintain date functions.
 *
 *  @note Parts of this are borrowed heavily from OreKit 9.3.1
 *        Copyright 2002-2019 CS Systèmes d'Information
 *        Licensed to CS Systèmes d'Information (CS) under one or more
 *        contributor license agreements.
 */
// =======================================================================================


#ifndef __HH_TIMECOMP_TRNCMP
#define __HH_TIMECOMP_TRNCMP


#include <trncmp.hh>


// =======================================================================================
class TimeComponents {
  // -------------------------------------------------------------------------------------
 public:
  /** Constant for commonly used hour 00:00:00. */
  static  TimeComponents H00;
  
  /** Constant for commonly used hour 12:00:00. */
  static  TimeComponents H12;

 protected:
   int32_t hour;       ///< Hour number.
   int32_t minute;     ///< Minute number.
   real8_t second;     ///< Seconds.
   int32_t minFromUTC; ///< UTC offset in minutes.

  void validate( void );


 public:
  TimeComponents ( void );

  TimeComponents ( const real8_t _second,
                   const int32_t _utc=0);

  TimeComponents ( const int32_t _hour,
                   const int32_t _minute,
                   const real8_t _second,
                   const int32_t _utc=0);

  TimeComponents( const TimeComponents& TC );

 TimeComponents& operator=  ( const TimeComponents& TC ) = default;
  void            copy      ( const TimeComponents& TC );
  bool            equals    ( TimeComponents& TC );
  int             compare   ( TimeComponents& TC );

  void set ( const int32_t hr, const  int32_t mn,
             const real8_t sc=D_ZERO, int32_t ut=0 );

  int32_t getHour              ( void ) const;
  int32_t getMinute            ( void ) const;
  real8_t getSecond            ( void ) const;
  int32_t getMinutesFromUTC    ( void ) const;
  real8_t getSecondsInLocalDay ( void ) const;
  real8_t getSecondsInUTCDay   ( void ) const;


  std::string           toString   ( void );
  static TimeComponents fromString ( std::string str );


}; // end class TimeComponents


// =======================================================================================
/** @brief Get Hours.
 *  @return hours.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t TimeComponents::getHour( void ) const {
  // -------------------------------------------------------------------------------------
  return hour;
}


// =======================================================================================
/** @brief Get minutes.
 *  @return minutes.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t TimeComponents::getMinute( void ) const {
  // -------------------------------------------------------------------------------------
  return minute;
}


// =======================================================================================
/** @brief Get Seconds.
 *  @return seconds.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t TimeComponents::getSecond( void ) const {
  // -------------------------------------------------------------------------------------
  return second;
}


// =======================================================================================
/** @brief Get get minutes from UTC.
 *  @return get minutes from UTC.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t TimeComponents::getMinutesFromUTC( void ) const {
  // -------------------------------------------------------------------------------------
  return minFromUTC;
}


// =======================================================================================
/** @brief Get seconds in local day.
 *  @return seconds in local day.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t TimeComponents::getSecondsInLocalDay( void ) const {
  // -------------------------------------------------------------------------------------
  return second + (real8_t)(60*minute + 3600*hour);
}


// =======================================================================================
/** @brief Get seconds in UTC day.
 *  @return seconds in UTC day.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t TimeComponents::getSecondsInUTCDay( void ) const {
  // -------------------------------------------------------------------------------------
  return second + (real8_t)(60*(minute+minFromUTC) + 3600*hour);
}


#endif


// =======================================================================================
// **                            T I M E C O M P O N E N T S                            **
// ======================================================================== END FILE =====
