// ====================================================================== BEGIN FILE =====
// **                                S T R I N G T O O L                                **
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
/** @brief  String Tool.
 *  @file   StringTool.cc
 *  @author Stephen W. Soliday
 *  @date   2013-Aug-18 Original release.
 *  @date   2019-May-06 CMake refactorization.
 *
 *  Provides the methods for a set of string manipulation tools.
 */
// =======================================================================================


#include <StringTool.hh>
#include <string.h>


const size_t StringTool::NOT_FOUND = std::string::npos;

// =======================================================================================
/** @brief Convert to string.
 *  @param val Boolean value.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the boolean value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const bool val ) {
  // -------------------------------------------------------------------------------------
  return std::string( (val) ? (".true.") : (".false.") );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %f.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const real8_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %f.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const real4_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %lld.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int64_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %ld.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int32_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %hd.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int16_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %hhd.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int8_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %llu.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int64_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %lu.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int32_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %hu.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int16_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}


// =======================================================================================
/** @brief Convert to string.
 *  @param val Numerical value.
 *  @param fmt The format used is the same as that used with printf. Default is %hhu.
 *  @return string representation of val.
 *
 *  Returns a string with the representation of the numerical value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int8_t val, const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( fmt, val );
}









// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %f.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const std::string* lst, const size_t n ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( lst[0] );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( lst[i] );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %f.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const real8_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %f.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const real4_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %lld.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int64_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %ld.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int32_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %hd.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int16_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %hhd.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const int8_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %llu.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int64_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %lu.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int32_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %hu.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int16_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @param fmt The format used is the same as that used with printf. Default is %hhu.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the numerical list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toString( const u_int8_t* lst, const size_t n,
                                  const std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], fmt ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], fmt ) );
  }

  temp.append( " ]" );

  return temp;
}








// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param val unsigned integer.
 *  @return hexadecimal string representation of val.
 *
 *  Returns a hexadecimal string with the representation of the unsigned integer.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int64_t val ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( "%016llx", val );
}


// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param val unsigned integer.
 *  @return hexadecimal string representation of val.
 *
 *  Returns a hexadecimal string with the representation of the unsigned integer.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int32_t val ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( "%08lx", val );
}


// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param val unsigned integer.
 *  @return hexadecimal string representation of val.
 *
 *  Returns a hexadecimal string with the representation of the unsigned integer.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int16_t val ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( "%04hx", val );
}


// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param val unsigned integer.
 *  @return hexadecimal string representation of val.
 *
 *  Returns a hexadecimal string with the representation of the unsigned integer.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int8_t val ) {
  // -------------------------------------------------------------------------------------
  return c_fmt( "%02hhx", val );
}




// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the hexadecimal list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int64_t* lst, const size_t n ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], "%016llx" ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], "%016llx" ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the hexadecimal list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int32_t* lst, const size_t n ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], "%08lx" ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], "%08lx" ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the hexadecimal list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int16_t* lst, const size_t n ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], "%04x" ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], "%04x" ) );
  }

  temp.append( " ]" );

  return temp;
}


// =======================================================================================
/** @brief Convert to hexadecimal string.
 *  @param lst pointer to an array.
 *  @param n   length of the array.
 *  @return string representation of list.
 *
 *  Returns a string with the representation of the hexadecimal list.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::toHex( const u_int8_t* lst, const size_t n ) {
  // -------------------------------------------------------------------------------------
  std::string temp("[ ");

  temp.append( StringTool::toString( lst[0], "%02x" ) );

  for (size_t i=1; i<n; i++) {
    temp.append( ", " );
    temp.append( StringTool::toString( lst[i], "%02x" ) );
  }

  temp.append( " ]" );

  return temp;
}








// =======================================================================================
/** @brief Convert to logical.
 *  @param S reference to std::string object.
 *  @return parsed logical value.
 *
 *  Parse a string for a logical value.
 */
// ---------------------------------------------------------------------------------------
bool StringTool::asBool( std::string S ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == S.compare( ".true."  ) ) { return true;  }
  if ( 0 == S.compare( ".false." ) ) { return false; }

  if ( 0 == S.compare( ".TRUE."  ) ) { return true;  }
  if ( 0 == S.compare( ".FALSE." ) ) { return false; }

  if ( 0 == S.compare( "true"  ) )  { return true;  }
  if ( 0 == S.compare( "false" ) )  { return false; }

  if ( 0 == S.compare( "True"  ) )  { return true;  }
  if ( 0 == S.compare( "False" ) )  { return false; }

  if ( 0 == S.compare( "TRUE"  ) )  { return true;  }
  if ( 0 == S.compare( "FALSE" ) )  { return false; }

  if ( 0 == S.compare( "yes"  ) )  { return true;  }
  if ( 0 == S.compare( "no" ) )  { return false; }

  if ( 0 == S.compare( "Yes"  ) )  { return true;  }
  if ( 0 == S.compare( "No" ) )  { return false; }

  if ( 0 == S.compare( "YES"  ) )  { return true;  }
  if ( 0 == S.compare( "NO" ) )  { return false; }

  if ( 0 == S.compare( "@true"  ) )  { return true;  }
  if ( 0 == S.compare( "@false" ) )  { return false; }

  if ( 0 == S.compare( "@TRUE"  ) )  { return true;  }
  if ( 0 == S.compare( "@FALSE" ) )  { return false; }

  throw ( std::invalid_argument( EXPECTED( "parse_bool", "true/false", S ) ) );
  
  return false;
}


// =======================================================================================
/** @brief Convert to an 8 byte real.
 *  @param S reference to std::string object.
 *  @return parsed 8 byte real value.
 *
 *  Parse a string as an 8 byte real value.
 */
// ---------------------------------------------------------------------------------------
real8_t StringTool::asReal8( const std::string S ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return std::stod( S );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "floating point", S ) ) );
  }
  return 0.0; 
}


// =======================================================================================
/** @brief Convert to a 4 byte real.
 *  @param S reference to std::string object.
 *  @return parsed 4 byte real value.
 *
 *  Parse a string as a 4 byte real value.
 */
// ---------------------------------------------------------------------------------------
real4_t StringTool::asReal4( const std::string S ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return std::stof( S );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "floating point", S ) ) );
  }
  return 0.0; 
}


// =======================================================================================
/** @brief Convert to a 64 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 64 bit integer value.
 *
 *  Parse a string as an 64 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
int64_t StringTool::asInt64( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return std::stol( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "64 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to a 32 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 32 bit integer value.
 *
 *  Parse a string as a 32 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
int32_t StringTool::asInt32( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return std::stoi( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "32 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to a 16 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 16 bit integer value.
 *
 *  Parse a string as a 16 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
int16_t StringTool::asInt16( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return (int16_t) std::stoi( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "16 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to an 8 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 8 bit integer value.
 *
 *  Parse a string as an 8 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
int8_t StringTool::asInt8( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return (int8_t) std::stoi( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "8 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to an unsigned 64 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 64 bit unsigned integer value.
 *
 *  Parse a string as an unsigned 64 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
u_int64_t StringTool::asUInt64( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return std::stoul( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "unsigned 64 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to an unsigned 32 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 32 bit unsigned integer value.
 *
 *  Parse a string as an unsigned 32 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
u_int32_t StringTool::asUInt32( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return (u_int32_t) std::stoul( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "unsigned 32 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to an unsigned 16 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 16 bit unsigned integer value.
 *
 *  Parse a string as an unsigned 16 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
u_int16_t StringTool::asUInt16( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return (u_int16_t) std::stoul( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "unsigned 16 bit integer", S ) ) );
  }
  return 0; 
}


// =======================================================================================
/** @brief Convert to an unsigned 8 bit integer.
 *  @param S    reference to std::string object.
 *  @param base numeric base (default: 10)
 *  @return parsed 8 bit unsigned integer value.
 *
 *  Parse a string as an unsigned 8 bit integer value, in the given base.
 */
// ---------------------------------------------------------------------------------------
u_int8_t StringTool::asUInt8( const std::string S, int base ) noexcept(false) {
  // -------------------------------------------------------------------------------------
  try {
    return (u_int8_t) std::stoul( S, static_cast<size_t*>(0), base );
  } catch ( std::invalid_argument& e ) {
    throw( std::invalid_argument( EXPECTED( e.what(), "unsigned 8 bit integer", S ) ) );
  }
  return 0; 
}








// =======================================================================================
/** @brief Trim White Space.
 *  @param str input string.
 *  @return string with leading and trailing white space removed.
 *
 *  Copy the input string removing the leading and trailing white space.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::trim( const std::string str ) {
  // -------------------------------------------------------------------------------------
  size_t pos1 = str.find_first_not_of(" \t");
  if ( std::string::npos == pos1 ) { return ""; }

  size_t pos2 = str.find_last_not_of(" \t\n");

  size_t A = (pos1 == std::string::npos) ? 0 : pos1;
  size_t B = (pos2 == std::string::npos) ? (str.length() - 1) : (pos2 - pos1 + 1);

  return str.substr(A, B);
}


// =======================================================================================
/** @brief Contained by.
 *  @param test input string.
 *  @param lhs  string containing the left  hand side delimeter(s).
 *  @param rhs  string containing the right hand side delimeter(s).
 *  @return substring contained between the left and right delimeter.
 *
 *  Match left and right delimeters and extract a copy of the substring contained
 *  between them.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::containedBy( const std::string test,
                                     const std::string lhs, const std::string rhs ) {
  // -------------------------------------------------------------------------------------
  size_t lpos = test.find_first_of( lhs );

  if ( std::string::npos == lpos ) { return ""; }

  size_t rpos = test.find_first_of( rhs, lpos+1 );

  if ( std::string::npos == rpos ) { return ""; }

  return test.substr( lpos+1, rpos-lpos-1 );
}








// =======================================================================================
/** @brief Constructor.
 *  @param str reference to a source string.
 *  @param del token delimeter.
 *
 *  Divide a source string into tokens.
 */
// ---------------------------------------------------------------------------------------
StringTool::Splitter::Splitter( const std::string& str, const char del ) : vector() {
  // -------------------------------------------------------------------------------------
  std::istringstream buf(str);
  for (std::string token; getline(buf, token, del); ) {
    vector.push_back(StringTool::trim(token));
  }
}







// =======================================================================================
/** @brief As String List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @return array of std::string.
 *
 *  Split the parameter string and create an array of std::string.
 */
// ---------------------------------------------------------------------------------------
std::string* StringTool::asStringList( size_t& n, const std::string S ) {
  // -------------------------------------------------------------------------------------
  std::string L = "[{(";
  std::string R = ")}]";
  StringTool::Splitter SP( StringTool::containedBy(S,L,R), ',' );
  n = SP.size();
  
  std::string* list = new std::string[n];

  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::trim( SP[i] );
  }

  return list;
}


// =======================================================================================
/** @brief As boolean List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of boolean.
 *
 *  Split the parameter string and create an array of boolean.
 */
// ---------------------------------------------------------------------------------------
bool* StringTool::asBoolList( size_t& n, const std::string S ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  bool* list = new bool[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asBool( slist[i] );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As Real8 List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @return array of Real8.
 *
 *  Split the parameter string and create an array of Real8.
 */
// ---------------------------------------------------------------------------------------
real8_t* StringTool::asReal8List( size_t& n, const std::string S ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  real8_t* list = new real8_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asReal8( slist[i] );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As  List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of .
 *
 *  Split the parameter string and create an array of .
 */
// ---------------------------------------------------------------------------------------
real4_t* StringTool::asReal4List( size_t& n, const std::string S ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  real4_t* list = new real4_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asReal4( slist[i] );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 64 bit signed integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 64 bit signed integer.
 *
 *  Split the parameter string and create an array of 64 bit signed integer.
 */
// ---------------------------------------------------------------------------------------
int64_t* StringTool::asInt64List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  int64_t* list = new int64_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asInt64( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 32 bit signed integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 32 bit signed integer.
 *
 *  Split the parameter string and create an array of 32 bit signed integer.
 */
// ---------------------------------------------------------------------------------------
int32_t* StringTool::asInt32List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  int32_t* list = new int32_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asInt32( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 16 bit signed integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 16 bit signed integer.
 *
 *  Split the parameter string and create an array of 16 bit signed integer.
 */
// ---------------------------------------------------------------------------------------
int16_t* StringTool::asInt16List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  int16_t* list = new int16_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asInt16( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 8 bit signed integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 8 bit signed integer.
 *
 *  Split the parameter string and create an array of 8 bit signed integer.
 */
// ---------------------------------------------------------------------------------------
int8_t* StringTool::asInt8List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  int8_t* list = new int8_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asInt8( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 64 bit unsigned integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 64 bit unsigned integer.
 *
 *  Split the parameter string and create an array of 64 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
u_int64_t* StringTool::asUInt64List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  u_int64_t* list = new u_int64_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asUInt64( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 32 bit unsigned integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 32 bit unsigned integer.
 *
 *  Split the parameter string and create an array of 32 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
u_int32_t* StringTool::asUInt32List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  u_int32_t* list = new u_int32_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asUInt32( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 16 bit unsigned integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 16 bit unsigned integer.
 *
 *  Split the parameter string and create an array of 16 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
u_int16_t* StringTool::asUInt16List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  u_int16_t* list = new u_int16_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asUInt16( slist[i], base );
  }

  delete[] slist;
  
  return list;
}


// =======================================================================================
/** @brief As 8 bit unsigned integer List.
 *  @param[out] n    number of elements.
 *  @param[in]  S    parameter string.
 *  @param[in]  base numeric base.
 *  @return array of 8 bit unsigned integer.
 *
 *  Split the parameter string and create an array of 8 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
    u_int8_t* StringTool::asUInt8List( size_t& n, const std::string S, int base ) {
  // -------------------------------------------------------------------------------------
  std::string* slist = StringTool::asStringList( n, S );
  
  u_int8_t* list = new u_int8_t[n];
  
  for ( size_t i=0; i<n; i++ ) {
    list[i] = StringTool::asUInt8( slist[i], base );
  }

  delete[] slist;
  
  return list;
}



// =======================================================================================
/** @brief Input.
 *  @param[in] prompt prompt to display.
 *  @param[in] def    default value.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return user input
 *
 *  Display a prompt and request user input. If user hits enter without supplying a value
 *  then the default value from the argument list is returned.
 */
// ---------------------------------------------------------------------------------------
int32_t StringTool::input( std::string prompt, int32_t def, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  os << prompt << " [" << def << "]: ";
  char line[64];
  std::cin.getline(line,63);
  size_t n = strlen(line);
  if ( 0 < n ) {
    return StringTool::asInt32( line );
  }
  return def;
}


// =======================================================================================
/** @brief Input.
 *  @param[in] prompt prompt to display.
 *  @param[in] def    default value.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return user input
 *
 *  Display a prompt and request user input. If user hits enter without supplying a value
 *  then the default value from the argument list is returned.
 */
// ---------------------------------------------------------------------------------------
real8_t StringTool::input( std::string prompt, real8_t def, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  os << prompt << " [" << def << "]: ";
  char line[64];
  std::cin.getline(line,63);
  size_t n = strlen(line);
  if ( 0 < n ) {
    return StringTool::asReal8( line );
  }
  return def;
}


// =======================================================================================
/** @brief Input.
 *  @param[in] prompt prompt to display.
 *  @param[in] def    default value.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return user input
 *
 *  Display a prompt and request user input. If user hits enter without supplying a value
 *  then the default value from the argument list is returned.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::input( std::string prompt, std::string def, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  os << prompt << " [" << def << "]: ";
  char line[64];
  std::cin.getline(line,63);
  size_t n = strlen(line);
  if ( 0 < n ) {
    return line;
  }
  return def;
}


// =======================================================================================
/** @brief Input.
 *  @param[in] prompt prompt to display.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return user input
 *
 *  Display a prompt and request user input. If user hits enter without supplying a value
 *  then the prompt will be repeated, until the user supply's a value.
 */
// ---------------------------------------------------------------------------------------
int32_t StringTool::inputI32( std::string prompt, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  char line[64];
  do {
    os << prompt << ": ";
    std::cin.getline(line,63);
  } while( 0 == strlen(line) );
  return StringTool::asInt32( line );
}


// =======================================================================================
/** @brief Input.
 *  @param[in] prompt prompt to display.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return user input
 *
 *  Display a prompt and request user input. If user hits enter without supplying a value
 *  then the prompt will be repeated, until the user supply's a value.
 */
// ---------------------------------------------------------------------------------------
real8_t StringTool::inputR8( std::string prompt, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  char line[64];
  do {
    os << prompt << ": ";
    std::cin.getline(line,63);
  } while( 0 == strlen(line) );
  return StringTool::asReal8( line );
}


// =======================================================================================
/** @brief Input.
 *  @param[in] prompt prompt to display.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return user input
 *
 *  Display a prompt and request user input. If user hits enter without supplying a value
 *  then the prompt will be repeated, until the user supply's a value.
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::inputStr( std::string prompt, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  char line[64];
  do {
    os << prompt << ": ";
    std::cin.getline(line,63);
  } while( 0 == strlen(line) );
  return line;
}


// =======================================================================================
/** @brief Yes No.
 *  @param[in] prompt prompt to display.
 *  @param[in] def    default value.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return true==yes, false==no
 *
 *  Display a prompt and request user input. If the user supply's an empty string
 *  the default will be returned. If the user does not supply Yes, No, True, or False
 *  the prompt will be repeated.
 *  @note only the first letter is tested caseless.
 */
// ---------------------------------------------------------------------------------------
bool StringTool::YesNo( std::string prompt, bool def, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  char line[64];
  bool rv = false;
  while (true) {
    os << prompt << "[" << ((def)?("Y/n"):("y/N")) << "]: ";
    std::cin.getline(line,63);
    if ( 0 == strlen(line) ) { rv=def; break; }
    char test = line[0];
    if ( 'Y' == test ) { rv = true;  break; }
    if ( 'y' == test ) { rv = true;  break; }
    if ( 'T' == test ) { rv = true;  break; }
    if ( 't' == test ) { rv = true;  break; }
    if ( 'N' == test ) { rv = false; break; }
    if ( 'n' == test ) { rv = false; break; }
    if ( 'F' == test ) { rv = false; break; }
    if ( 'f' == test ) { rv = false; break; }
  }
  return rv;
}

// =======================================================================================
/** @brief Yes No.
 *  @param[in] prompt prompt to display.
 *  @param[in] def    default value.
 *  @param[in[ os     output stream for prompt (default: stdin)
 *  @return true==yes, false==no
 *
 *  Display a prompt and request user input. If the user supply's an empty string
 *  the default will be returned. If the user does not supply Yes, No, True, or False
 *  the prompt will be repeated.
 *  @note only the first letter is tested caseless.
 */
// ---------------------------------------------------------------------------------------
bool StringTool::YesNo( std::string prompt, std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  char line[64];
  bool rv = false;
  while (true) {
    os << prompt << "(y/n): ";
    std::cin.getline(line,63);
    if ( 0 < strlen(line) ) {
      char test = line[0];
      if ( 'Y' == test ) { rv = true;  break; }
      if ( 'y' == test ) { rv = true;  break; }
      if ( 'T' == test ) { rv = true;  break; }
      if ( 't' == test ) { rv = true;  break; }
      if ( 'N' == test ) { rv = false; break; }
      if ( 'n' == test ) { rv = false; break; }
      if ( 'F' == test ) { rv = false; break; }
      if ( 'f' == test ) { rv = false; break; }
    }
  }
  return rv;
}

// =======================================================================================
/** @brief Yes No.
 *  @param[in] test test.
 *  @return "Yes" if test==true, else "No"
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::asYesNo( bool test ) {
  // -------------------------------------------------------------------------------------
  return (test) ? "Yes" : "No";
}

// =======================================================================================
/** @brief Yes No.
 *  @param[in] test test.
 *  @return "No" if test==0, else "Yes"
 */
// ---------------------------------------------------------------------------------------
std::string StringTool::asYesNo( int test ) {
  // -------------------------------------------------------------------------------------
  return (0==test) ? "No" : "Yes";
}



// =======================================================================================
// **                                S T R I N G T O O L                                **
// ======================================================================== END FILE =====
