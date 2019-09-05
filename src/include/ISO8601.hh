// ====================================================================== BEGIN FILE =====
// **                                   I S O 8 6 0 1                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2019, Stephen W. Soliday                                      **
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
/** @brief  ISO 8601 Date and Time parser.
 *  @file   ISO8601.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15
 *
 *  Provides the interface for an ISO8601 Parser and formater.
 */
// =======================================================================================


#ifndef __HH_ISO8601_TRNCMP
#define __HH_ISO8601_TRNCMP

#include <regex>
#include <StringTool.hh>

// =======================================================================================
class ISO8601 {
  // -------------------------------------------------------------------------------------
 protected:
  int32_t year;
  int32_t month;
  int32_t day;
  int32_t hour;
  int32_t minute;
  real8_t second;
  int32_t offset;
  bool    has_date;
  bool    has_time;

  void validate_time ( void );
  void validate_date ( void );
  void validate      ( void );

  std::string date_to_string_basic    ( void );
  std::string time_to_string_basic    ( void );
  std::string date_to_string_extended ( void );
  std::string time_to_string_extended ( void );

 public:
  
  ISO8601  ( void );
  ISO8601  ( std::string str );
  ~ISO8601 ( void );

  void    clear     ( void );

  int32_t getYear   ( void ) const;
  int32_t getMonth  ( void ) const;
  int32_t getDay    ( void ) const;
  int32_t getHour   ( void ) const;
  int32_t getMinute ( void ) const;
  real8_t getSecond ( void ) const;
  int32_t getOffset ( void ) const;

  bool    hasDate   ( void ) const;
  bool    hasTime   ( void ) const;

  void    setDate   ( const int32_t y, const int32_t m=0, const int32_t d=0 );
  void    setTime   ( const int32_t h, const int32_t m=0,
                      const real8_t s=D_ZERO, const int32_t o=0 );

  std::string toString       ( bool basic = false );
  void        fromString     ( std::string str );
  
  std::string dateToString   ( bool basic = false );
  std::string timeToString   ( bool basic = false );
  void        dateFromString ( std::string str );
  void        timeFromString ( std::string str );

}; // end class ISO8601



// =======================================================================================
/** @brief Get Year.
 *  @return year.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t ISO8601::getYear( void ) const {
  // -------------------------------------------------------------------------------------
  return year;
}


// =======================================================================================
/** @brief Get Month.
 *  @return month.
 */
// ---------------------------------------------------------------------------------------
  inline  int32_t ISO8601::getMonth( void ) const {
  // -------------------------------------------------------------------------------------
  return month;
}


// =======================================================================================
/** @brief Get Day.
 *  @return day.
 */
// ---------------------------------------------------------------------------------------
  inline  int32_t ISO8601::getDay( void ) const {
  // -------------------------------------------------------------------------------------
  return day;
}


// =======================================================================================
/** @brief Get Hour.
 *  @return hour.
 */
// ---------------------------------------------------------------------------------------
  inline  int32_t ISO8601::getHour( void ) const {
  // -------------------------------------------------------------------------------------
  return hour;
}


// =======================================================================================
/** @brief Get Minute.
 *  @return minute.
 */
// ---------------------------------------------------------------------------------------
  inline  int32_t ISO8601::getMinute( void ) const {
  // -------------------------------------------------------------------------------------
  return minute;
}


// =======================================================================================
/** @brief Get Second.
 *  @return second.
 */
// ---------------------------------------------------------------------------------------
  inline  real8_t ISO8601::getSecond( void ) const {
  // -------------------------------------------------------------------------------------
  return second;
}


// =======================================================================================
/** @brief Get UTC Offse.
 *  @return UTC offset.
 */
// ---------------------------------------------------------------------------------------
  inline  int32_t ISO8601::getOffset( void ) const {
  // -------------------------------------------------------------------------------------
  return offset;
}


// =======================================================================================
/** @brief Has Date.
 *  @return true if there is date data.
 */
// ---------------------------------------------------------------------------------------
  inline  bool ISO8601::hasDate( void ) const {
  // -------------------------------------------------------------------------------------
  return has_date;
}


// =======================================================================================
/** @brief Has Time.
 *  @return true if there is time data.
 */
// ---------------------------------------------------------------------------------------
  inline  bool ISO8601::hasTime( void ) const {
  // -------------------------------------------------------------------------------------
  return has_time;
}


#endif 


// =======================================================================================
// **                                   I S O 8 6 0 1                                   **
// ======================================================================== END FILE =====
