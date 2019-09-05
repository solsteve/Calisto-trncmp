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
 *  @file   ISO8601.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15
 *
 *  Provides the methods for an ISO8601 Parser and formater.
 */
// =======================================================================================


#include <ISO8601.hh>

#define INIT_VAR(a)                                              \
  year(a), month(a), day(a), hour(a), minute(a), second(D_ZERO), \
    offset(a), has_date(false), has_time(false)

// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
ISO8601::ISO8601( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] str string to parse.
 */
// ---------------------------------------------------------------------------------------
ISO8601::ISO8601( std::string str ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  fromString( str );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
ISO8601::~ISO8601( void ) {
  // -------------------------------------------------------------------------------------
  clear();
}


// =======================================================================================
/** @brief Clear.
 */
// ---------------------------------------------------------------------------------------
void ISO8601::clear( void ) {
  // -------------------------------------------------------------------------------------
  year     = 0;
  month    = 0;
  day      = 0;
  hour     = 0;
  minute   = 0;
  second   = D_ZERO;
  offset   = 0;
  has_date = false;
  has_time = false;
}


// =======================================================================================
void ISO8601::validate_time( void ) {
  // -------------------------------------------------------------------------------------
  if (    23 < hour   ) { throw std::invalid_argument( "Hour is to large" );   }
  if (     0 > hour   ) { throw std::invalid_argument( "Hour is to small" );   }
  
  if (    59 < minute ) { throw std::invalid_argument( "Minute is to large" ); }
  if (     0 > minute ) { throw std::invalid_argument( "Minute is to small" ); }
  
  if (  61.0 < second ) { throw std::invalid_argument( "Second is to large" ); }
  if (   0.0 > second ) { throw std::invalid_argument( "Second is to small" ); }
  
  if (  1440 < offset ) { throw std::invalid_argument( "Offset is to large" ); }
  if ( -1440 > offset ) { throw std::invalid_argument( "Offset is to small" ); }  
}


// =======================================================================================
void ISO8601::validate_date( void ) {
  // -------------------------------------------------------------------------------------
  if ( 9999 < year  ) { throw std::invalid_argument( "Year is to large" );  }
  if (    1 > year  ) { throw std::invalid_argument( "Year is to small" );  }
  
  if (   12 < month ) { throw std::invalid_argument( "Month is to large" ); }
  if (    1 > month ) { throw std::invalid_argument( "Month is to small" ); }
  
  if (   31 < day   ) { throw std::invalid_argument( "Day is to large" );   }
  if (    1 > day   ) { throw std::invalid_argument( "Day is to small" );   }
}


// =======================================================================================
void ISO8601::validate( void ) {
  // -------------------------------------------------------------------------------------
  validate_time();
  validate_date();
}


// =======================================================================================
/** @brief Set Date.
 *  @param[in] y year.
 *  @param[in] m month. (default: 0)
 *  @param[in] d day.   (default: 0)
 */
// ---------------------------------------------------------------------------------------
void ISO8601::setDate( const int32_t y, const int32_t m, const int32_t d ) {
  // -------------------------------------------------------------------------------------
  year     = y;
  month    = m;
  day      = d;
  validate_date();
  has_date = true;
}


// =======================================================================================
/** @brief Set Time.
 *  @param[in] h hour.
 *  @param[in] m minute.     (default: 0)
 *  @param[in] s second.     (default: 0)
 *  @param[in] o UTC offset. (default: 0)
 */
// ---------------------------------------------------------------------------------------
void ISO8601::setTime( const int32_t h, const int32_t m, const real8_t s, const int32_t o ) {
  // -------------------------------------------------------------------------------------
  hour     = h;
  minute   = m;
  second   = s;
  offset   = o;
  validate_time();
  has_time = true;
}


// =======================================================================================
/** @brief Parse String.
 *  @param[in] str ISO8601 formated date and/or time.
 */
// ---------------------------------------------------------------------------------------
void ISO8601::fromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  clear();

  StringTool::Splitter SP( str, 'T' );
  size_t n = SP.size();

  if ( 1 == n ) {
    std::string s1 = SP.at(0);
    dateFromString( s1 );
  } else {
    std::string s1 = SP.at(0);
    std::string s2 = SP.at(1);
    if ( 0 < s1.size() ) { dateFromString( s1 ); }
    if ( 0 < s2.size() ) { timeFromString( s2 ); }
  }

}


// =======================================================================================
/** @brief Parse Date String.
 *  @param[in] str ISO8601 formated date.
 */
// ---------------------------------------------------------------------------------------
void ISO8601::dateFromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  std::regex  e ("^(\\d\\d\\d\\d)\\-?(\\d\\d)\\-?(\\d\\d)?$");
  std::cmatch cm;

  std::regex_match ( str.c_str(), cm, e );

  has_date = false;
  if ( "" == cm[1] ) { year  = 1; } else { year   = StringTool::asInt32( cm[1] ); has_date = true; }
  if ( "" == cm[2] ) { month = 1; } else { month  = StringTool::asInt32( cm[2] ); has_date = true; }
  if ( "" == cm[3] ) { day   = 1; } else { day    = StringTool::asInt32( cm[3] ); has_date = true; }
  if ( has_date ) { validate_date(); }
}


// =======================================================================================
/** @brief Parse Time String.
 *  @param[in] str ISO8601 formated time.
 */
// ---------------------------------------------------------------------------------------
void ISO8601::timeFromString( std::string str ) {
  // -------------------------------------------------------------------------------------
  std::regex  e ("^[T]*(\\d\\d):?(\\d\\d):?(\\d\\d(?:[.,]\\d+)?)?(?:Z|([-+]\\d\\d):?(\\d\\d)?)?$");
  std::cmatch cm;

  std::regex_match ( str.c_str(), cm, e );

  has_time = false;
  if ( "" != cm[1] ) { hour   = StringTool::asInt32( cm[1] ); has_time = true; }
  if ( "" != cm[2] ) { minute = StringTool::asInt32( cm[2] ); has_time = true; }
  if ( "" != cm[3] ) { second = StringTool::asReal8( cm[3] ); has_time = true; }
  int32_t oh = 0;
  int32_t om = 0;
  if ( "" != cm[4] ) { oh = StringTool::asInt32( cm[4] ); has_time = true; }
  if ( "" != cm[5] ) { om = StringTool::asInt32( cm[5] ); has_time = true; }
  offset = (60*oh) + ((0>oh) ? (-om) : (om));
  if ( has_time ) { validate_time(); }
}









// =======================================================================================
/** @brief To String.
 *  @return ISO8601 formated date and/or time
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::toString( bool basic ) {
  // -------------------------------------------------------------------------------------
  std::string str;
  if ( has_date ) {
    str = dateToString(basic);
  }
  
  if ( has_time ) {
    str.append(timeToString(basic));
  }

  return str;
}





// =======================================================================================
/** @brief To String.
 *  @return ISO8601 formated date and/or time
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::timeToString( bool basic ) {
  // -------------------------------------------------------------------------------------
  if ( basic ) {
    return time_to_string_basic();
  }
  return time_to_string_extended();
}


// =======================================================================================
/** @brief To String.
 *  @return ISO8601 formated date and/or time
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::dateToString( bool basic ) {
  // -------------------------------------------------------------------------------------
  if ( basic ) {
    return date_to_string_basic();
  }
  return date_to_string_extended();
}


// =======================================================================================
/** @brief Date to String.
 *  @return ISO8601 basic formated date.
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::date_to_string_basic( void ) {
  // -------------------------------------------------------------------------------------
  char buffer[32];
  snprintf( buffer, 31, "%04d%02d%02d", year, month, day );
  return std::string( buffer );
}


// =======================================================================================
/** @brief Date to String.
 *  @return ISO8601 extended formated date.
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::date_to_string_extended( void ) {
  // -------------------------------------------------------------------------------------
  char buffer[32];
  snprintf( buffer, 31, "%04d-%02d-%02d", year, month, day );
  return std::string( buffer );
}


// =======================================================================================
/** @brief Time to String.
 *  @return ISO8601 basic formated time.
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::time_to_string_basic( void ) {
  // -------------------------------------------------------------------------------------
  char buffer1[32];
  char buffer2[32];
  int32_t ip = (int32_t) floor(second);
  int32_t fp = (int32_t) ((second - ip)*1.0e5);
  if ( 0 == fp ) {
    snprintf( buffer1, 31, "T%02d%02d%02d", hour, minute, ip );
  } else {
    snprintf( buffer1, 31, "T%02d%02d%08.5f", hour, minute, second );
  }

  std::string str( buffer1 );

  if ( 0 == offset ) {  // ----- No UTC Offset --------------------------------
    buffer2[0] = 'Z';
    buffer2[1] = static_cast<char>(0);
  } else {
    int32_t h = 0;
    int32_t m = 0;
    if ( 0 < offset ) { // ----- Positive UTC Offset --------------------------
      HMfromMinutes( &h, &m, offset );
      snprintf( buffer2, 31, "+%02d%02d", h, m );
    } else {            // ----- Negative UTC Offset --------------------------
      HMfromMinutes( &h, &m, -offset );
      snprintf( buffer2, 31, "-%02d%02d", h, m );
    }
  }

  str.append( buffer2 );
  
  return std::string(str);  
}


// =======================================================================================
/** @brief Time to String.
 *  @return ISO8601 extended formated time.
 */
// ---------------------------------------------------------------------------------------
std::string ISO8601::time_to_string_extended( void ) {
  // -------------------------------------------------------------------------------------
  char buffer1[32];
  char buffer2[32];
  int32_t ip = (int32_t) floor(second);
  int32_t fp = (int32_t) ((second - ip)*1.0e5);
  if ( 0 == fp ) {
    snprintf( buffer1, 31, "T%02d:%02d:%02d", hour, minute, ip );
  } else {
    snprintf( buffer1, 31, "T%02d:%02d:%08.5f", hour, minute, second );
  }

  std::string str( buffer1 );
  
  if ( 0 == offset ) {  // ----- No UTC Offset --------------------------------
    buffer2[0] = 'Z';
    buffer2[1] = static_cast<char>(0);
  } else {
    int32_t h = 0;
    int32_t m = 0;
    if ( 0 < offset ) { // ----- Positive UTC Offset --------------------------
      HMfromMinutes( &h, &m, offset );
      snprintf( buffer2, 13, "+%02d:%02d", h, m );
    } else {            // ----- Negative UTC Offset --------------------------
      HMfromMinutes( &h, &m, -offset );
      snprintf( buffer2, 13, "-%02d:%02d", h, m );
    }
  }
  
  str.append( buffer2 );
  
  return std::string(str);  
}


// =======================================================================================
// **                                   I S O 8 6 0 1                                   **
// ======================================================================== END FILE =====

