// ====================================================================== BEGIN FILE =====
// **                                    T R N C M P                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 1993, 02, 09, 19  Stephen W. Soliday                               **
// **                                  stephen.soliday@trncmp.org                       **
// **                                  http://research.trncmp.org                       **
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
/** @brief  Main header
 *  @file   trncmp.hh
 *  @author Stephen W. Soliday
 *  @date   1993-09-18  Original release.
 *  @date   2009-01-28  Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  This is the main header that all applications should call.
 */
// =======================================================================================

// READ THIS:: https://www.youtube.com/watch?v=bXkWuUe9V2I&feature=youtu.be

#ifndef __TRNCMP_HH
#define __TRNCMP_HH

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
//#include <sys/types.h>
#include <typeinfo>
#include <cctype>
#include <string>
#include <stdexcept>


// ---------------------------------------------------------------------------------------


#define DEFAULT_OUTPUT_STREAM std::cout ///< Default output ostream
#define DEFAULT_ERROR_STREAM  std::cerr ///< Default error  ostream

#define DEFAULT_OUTPUT_UNIT   stdout    ///< Default output FILE pointer
#define DEFAULT_ERROR_UNIT    stderr    ///< Default error  FILE pointer


// ---------------------------------------------------------------------------------------


typedef u_int64_t   iden_t;     ///< use for unique identification.

typedef float       real4_t;    ///< alias for float
typedef double      real8_t;    ///< alias for double
typedef long double real10_t;   ///< alias for long double


// ---------------------------------------------------------------------------------------


#include <mathdef.hh>
#include <arrayfunc.hh>
#include <summation.hh>
#include <copy_clone.hh>


// ---------------------------------------------------------------------------------------


/** @brief 64 bit mask */
typedef union __u_mask64 {
  u_int64_t qwrd;      ///< One   Quad   Word  Unsigned
  u_int32_t dwrd[2];   ///< Two   Double Words Unsigned
  u_int16_t word[4];   ///< Four  Single Words Unsigned
  u_int8_t  byte[8];   ///< Eight Half   Words Unsigned
  int64_t   i64;       ///< One   Quad   Word 
  int32_t   i32[2];    ///< Two   Double Words
  int16_t   i16[4];    ///< Four  Single Words
  int8_t    i8[8];     ///< Eight Half   Words
} u_mask64_t;


/** @brief 32 bit mask */
typedef union __u_mask32 {
  u_int32_t dwrd;      ///< One  Double Word  Unsigned
  u_int16_t word[2];   ///< Two  Single Words Unsigned
  u_int8_t  byte[4];   ///< Four Half   Words Unsigned
  int32_t   i32;       ///< One  Double Word
  int16_t   i16[2];    ///< Two  Single Words
  int8_t    i8[4];     ///< Four Half   Words
} u_mask32_t;


/** @brief 16 bit mask */
typedef union __u_mask16 {
  u_int16_t word;      ///< One Single Word  Unsigned
  u_int8_t  byte[2];   ///< Two Half   Words Unsigned
  int16_t   i16;       ///< One Single Word
  int8_t    i8[2];     ///< Two Half   Words
} u_mask16_t;


// ---------------------------------------------------------------------------------------

/** function pointer real8_t foo( real8_t ) */
typedef real8_t (* __R8_FUNC_R8 ) ( real8_t );

/** function pointer real8_t foo( real8_t, size_t ) */
typedef real8_t (* __R8_FUNC_R8S ) ( real8_t, size_t );  

/** function pointer real8_t foo( real8_t*, size_t ) */
typedef real8_t (* __R8_FUNC_RP8S ) ( real8_t*, size_t ); 

/** function pointer size_t foo( real8_t*, size_t ) */
typedef size_t  (* __I4_FUNC_RP8S ) ( real8_t*, size_t ); 

// ---------------------------------------------------------------------------------------

#  ifdef    MAXPATH
#    define MAXPATHLEN MAXPATH ///< Maximum length for a file path
#    ifdef SHOWDIAG
#      warning "Using MAXPATH for MAXPATHLEN"
#    endif
#  endif

#  ifdef    MAX_PATH
#    define MAXPATHLEN MAX_PATH ///< Maximum length for a file path
#    ifdef SHOWDIAG
#      warning "Using MAX_PATH for MAXPATHLEN"
#    endif
#  endif

#  ifndef   MAXPATHLEN
#    define MAXPATHLEN 256 ///< Maximum length for a file path
#    ifdef SHOWDIAG
#      warning "Using 256 for MAXPATHLEN"
#    endif
#  endif

// ---------------------------------------------------------------------------------------


const char* trncmpAuthor();
const char* trncmpVersion();
void ShowTime( std::ostream& o, real8_t hours );


// ---------------------------------------------------------------------------------------

/** @brief Generate an empty prototype.
 *  @param _clname class name.
 */
#define EMPTY_PROTOTYPE(_clname)                \
  _clname(const _clname&);                      \
  _clname& operator=(const _clname&)

#  ifdef   until
#    undef until
#  endif
#  define  until(_c) while(!(_c)) ///< create a do-until loop

/** Show a variable for documentation */
#define SHOW(a) std::cerr << #a << " = " << a << std::endl;


// =======================================================================================
/** @brief C Format single variable.
 *  @param fmt c-style format (see: fprintf )
 *  @param value number to format.
 *  @return formatted value as std::string
 *
 *  Convert the number (value) using fprintf c-style format specifier.
 *  @note this function is not thread safe. It is not intended for complex formating
 *        keep it under 63-characters.
 */
// ---------------------------------------------------------------------------------------
template< class T >
std::string c_fmt( std::string fmt, T value ) {
  // -------------------------------------------------------------------------------------
  char buffer[64];
  snprintf( buffer, 64, fmt.c_str(), value );
  return std::string(buffer);
}

template<class A, class B>
std::string EXPECTED( std::string l, A e, B g ) {
  std::string msg( l );
    msg.append( ": expected [" );
    msg.append( e );
    msg.append( "] got [" );
    msg.append( g );
    msg.append( "]" );
    return msg;
}


#endif


// =======================================================================================
// **                                    T R N C M P                                    **
// ======================================================================== END FILE =====
