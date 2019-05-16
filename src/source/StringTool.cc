// ====================================================================== BEGIN FILE =====
// **                                S T R I N G T O O L                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2013, 2019  Stephen W. Soliday                                     **
// **                            stephen.soliday@trncmp.org                             **
// **                            http://research.trncmp.org                             **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This file, and associated source code, is not free software; you may not         **
// **  redistribute it and/or modify it. This library is currently in an on going       **
// **  development phase by its author and has, as yet, not been publicly distributed.  **
// **  Development of this library has been at the sole cost in both time and funding   **
// **  by its author. Until such a public release is made the author retains ALL RIGHTS **
// **  to this software. It is expected that if and when this library is deemed         **
// **  releasable it will be released under the GNU Public license for non-commercial   **
// **  use or with a restricted rights for government use. At that time each source     **
// **  file will contain either/both the standard GPL statement/disclaimer, and/or the  **
// **  DFARS Restricted Rights Legend.                                                  **
// **                                                                                   **
// **  This library exists at the present time WITHOUT ANY WARRANTY; without even the   **
// **  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         **
// **  As you are not supposed to be in possession of this file if you use it,          **
// **  you use this code AT YOUR OWN RISK.                                              **
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
// **                                S T R I N G T O O L                                **
// ======================================================================== END FILE =====
