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


#include <TimeComponents.hh>
#include <ISO8601.hh>


/** Constant for commonly used hour 00:00:00. */
TimeComponents TimeComponents::H00(0, 0, D_ZERO);

/** Constant for commonly used hour 12:00:00. */
TimeComponents TimeComponents::H12(12, 0, D_ZERO);




// =======================================================================================
void TimeComponents::validate( void ) {
  // -------------------------------------------------------------------------------------
  if (    23 < hour   ) { throw std::invalid_argument( "Hour is to large" );   }
  if (     0 > hour   ) { throw std::invalid_argument( "Hour is to small" );   }
  
  if (    59 < minute ) { throw std::invalid_argument( "Minute is to large" ); }
  if (     0 > minute ) { throw std::invalid_argument( "Minute is to small" ); }
  
  if (  61.0 < second ) { throw std::invalid_argument( "Second is to large" ); }
  if (   0.0 > second ) { throw std::invalid_argument( "Second is to small" ); }
  
  if (  1439 < minFromUTC ) { throw std::invalid_argument( "UTC Offset is to large" ); }
  if ( -1439 > minFromUTC ) { throw std::invalid_argument( "UTC Offset is to small" ); }  
}


// =======================================================================================
/** @brief Constructor
 */
// ---------------------------------------------------------------------------------------
TimeComponents::TimeComponents( void ) :
    hour(0), minute(0), second(D_ZERO), minFromUTC(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor
 *  @param[in] _second_in_day seconds from midnight.
 *  @param[in] _utc           UTC offset in minutes. (default = 0)
 */
// ---------------------------------------------------------------------------------------
TimeComponents::TimeComponents( const real8_t _second_in_day,
                                const int32_t _utc ) :
    hour(0), minute(0), second(D_ZERO), minFromUTC(_utc) {
  // -------------------------------------------------------------------------------------
  HMSfromSeconds( &hour, &minute, &second, _second_in_day );
  validate();
}


// =======================================================================================
/** @brief Constructor
 *  @param[in] _hours  hours from midnight.
 *  @param[in] _minute minutes.
 *  @param[in] _second seconds.
 *  @param[in] _utc    UTC offset in minutes. (default = 0)
 */
// ---------------------------------------------------------------------------------------
TimeComponents::TimeComponents( const int32_t _hour,
                                const int32_t _minute,
                                const real8_t _second,
                                const int32_t _utc ) :
    hour(_hour), minute(_minute), second(_second), minFromUTC(_utc) {
  // -------------------------------------------------------------------------------------
  validate();
}


// =======================================================================================
/** @brief Constructor
 *  @param[in] TC reference to a TimeComponents used as a source.
 */
// ---------------------------------------------------------------------------------------
TimeComponents::TimeComponents( const TimeComponents& TC ) :
    hour(TC.hour), minute(TC.minute), second(TC.second), minFromUTC(TC.minFromUTC) {
  // -------------------------------------------------------------------------------------
  validate();
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] TC reference to a TimeComponents used as a source.
 */
// ---------------------------------------------------------------------------------------
void TimeComponents::copy( const TimeComponents& TC ) {
  // -------------------------------------------------------------------------------------
  this->hour       = TC.hour;
  this->minute     = TC.minute;
  this->second     = TC.second;
  this->minFromUTC = TC.minFromUTC;
  validate();
}


// =======================================================================================
/** @brief Equals.
 */
// ---------------------------------------------------------------------------------------
bool TimeComponents::equals( TimeComponents& that ) {
  // -------------------------------------------------------------------------------------
  if ( this->hour       != that.hour )       { return false; }
  if ( this->minute     != that.minute )     { return false; }
  if ( this->minFromUTC != that.minFromUTC ) { return false; }

  // compliant with IEEE 754
  if ( notEqual( this->second, that.second, 1.0e-11 ) ) {
  //  fprintf( stderr,
  //           "TimeComponents::equals ******** %23.16e\n ********",
  //          this->second - that.second );
    return false;
  }

  return true;
}

// =======================================================================================
/** @brief Compare
 *  @param[in] that Reference to another TimeCompomnents class.
 *  @return -1 if this DateComponents is less than that.
 *           0 if this DateComponents is equal to  that.
 *          +1 if this DateComponents is greater than that.
 */
// ---------------------------------------------------------------------------------------
int TimeComponents::compare( TimeComponents& that ) {
  // -------------------------------------------------------------------------------------
  const real8_t lhs = this->getSecondsInUTCDay();
  const real8_t rhs = that.getSecondsInUTCDay();

  return (lhs<rhs) ? (-1) : ((lhs>rhs) ? (+1) : (0));
}


// =======================================================================================
/** @brief Constructor
 *  @param[in] _hours  hours from midnight.
 *  @param[in] _minute minutes.
 *  @param[in] _second seconds.               (default = 0)
 *  @param[in] _utc    UTC offset in minutes. (default = 0)
 */
// ---------------------------------------------------------------------------------------
void TimeComponents::set( const int32_t _hour,   const int32_t _minute,
                          const real8_t _second, const int32_t _utc ) {
  // -------------------------------------------------------------------------------------
  this->hour       = _hour;
  this->minute     = _minute;
  this->second     = _second;
  this->minFromUTC = _utc;
  validate();
}


// =======================================================================================
/** @brief To String
 *  @return ISO 8601 formated string containing the time.
 */
// ---------------------------------------------------------------------------------------
std::string TimeComponents::toString( void ) {
  // -------------------------------------------------------------------------------------
  ISO8601 P;
  P.setTime( hour, minute, second, minFromUTC );
  return P.toString();
}


// =======================================================================================
/** @brief Parse a String
 *  @param[in] str ISO 8601 formated string containing the time.
 *  @return static instance of a TimeComponents class.
 */
// ---------------------------------------------------------------------------------------
TimeComponents TimeComponents::fromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  ISO8601 P( str );

  int32_t h = P.getHour();
  int32_t m = P.getMinute();
  real8_t s = P.getSecond();
  int32_t u = P.getOffset();

  return TimeComponents(h,m,s,u);
}


// =======================================================================================
// **                            T I M E C O M P O N E N T S                            **
// ======================================================================== END FILE =====
