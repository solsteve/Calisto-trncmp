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

#ifndef __TRNCMP_HH
#define __TRNCMP_HH

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
//#include <sys/types.h>
#include <typeinfo>
#include <cctype>

// ---------------------------------------------------------------------------------------

#define DEFAULT_OUTPUT_STREAM std::cout
#define DEFAULT_ERROR_STREAM  std::cerr

#define DEFAULT_OUTPUT_UNIT   stdout
#define DEFAULT_ERROR_UNIT    stderr

// ---------------------------------------------------------------------------------------

typedef u_int64_t   iden_t;

typedef float       real4_t;
typedef double      real8_t;
typedef long double real10_t;

// ---------------------------------------------------------------------------------------

#include <mathdef.hh>

// ---------------------------------------------------------------------------------------

typedef union __u_mask64 {
  u_int64_t qwrd;
  u_int32_t dwrd[2];
  u_int16_t word[4];
  u_int8_t  byte[8];
  int64_t   i64;
  int32_t   i32[2];
  int16_t   i16[4];
  int8_t    i8[8];
} u_mask64_t;

typedef union __u_mask32 {
  u_int32_t dwrd;
  u_int16_t word[2];
  u_int8_t  byte[4];
  int32_t   i32;
  int16_t   i16[2];
  int8_t    i8[4];
} u_mask32_t;

typedef union __u_mask16 {
  u_int16_t word;
  u_int8_t  byte[2];
  int16_t   i16;
  int8_t    i8[2];
} u_mask16_t;

// ---------------------------------------------------------------------------------------

typedef real8_t (* __R8_FUNC_R8 )   ( real8_t );
typedef real8_t (* __R8_FUNC_R8S )  ( real8_t, size_t );
typedef real8_t (* __R8_FUNC_RP8S ) ( real8_t*, size_t );
typedef size_t  (* __I4_FUNC_RP8S ) ( real8_t*, size_t );

// ---------------------------------------------------------------------------------------

#  ifdef    MAXPATH
#    define MAXPATHLEN MAXPATH
#    ifdef SHOWDIAG
#      warning "Using MAXPATH for MAXPATHLEN"
#    endif
#  endif

#  ifdef    MAX_PATH
#    define MAXPATHLEN MAX_PATH
#    ifdef SHOWDIAG
#      warning "Using MAX_PATH for MAXPATHLEN"
#    endif
#  endif

#  ifndef   MAXPATHLEN
#    define MAXPATHLEN 256
#    ifdef SHOWDIAG
#      warning "Using 256 for MAXPATHLEN"
#    endif
#  endif

// ---------------------------------------------------------------------------------------

const char* trncmpAuthor();
const char* trncmpVersion();

// ---------------------------------------------------------------------------------------

#define EMPTY_PROTOTYPE(_clname)                \
  _clname(const _clname&); \
  _clname& operator=(const _clname&)

#  ifdef   until
#    undef until
#  endif
#  define  until(_c) while(!(_c))

#define SHOW(a) std::cerr << #a << " = " << a << std::endl;

// ==========================================================================================
/** @brief C Format single variable.
 *  @param fmt c-style format (see: fprintf )
 *  @param value number to format.
 *  @return formatted value as char*
 *
 *  Convert the number (value) using fprintf c-style format specifier. Note this function is
 *  not thread safe. It is not intended for complex formating keep it under 63-characters.
 */
// ------------------------------------------------------------------------------------------
template< class T >
inline char* c_fmt( const char* fmt, T value ) {
  // ----------------------------------------------------------------------------------------
  static char buffer[64];
  sprintf( buffer, fmt, value );
  return buffer;
}

#endif

// =======================================================================================
// **                                    T R N C M P                                    **
// ======================================================================== END FILE =====
