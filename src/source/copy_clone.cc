// ====================================================================== BEGIN FILE =====
// **                                C O P Y _ C L O N E                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2015, 2019  Stephen W. Soliday                                     **
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
/** @brief  Copy & Clone
 *  @file   copy_clone.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-23 Original release.
 *
 *  Provides the methods for various copy and clone single dimension arrays.
 */
// =======================================================================================


#include <trncmp.hh>


// =======================================================================================
/** @brief Copy.
 *  @param[out] dst  pointer to destination array.
 *  @param[in]  doff destination offset.
 *  @param[in]  src  pointer to source array.
 *  @param[in]  soff source offset.
 *  @param[in]  n    number of elements to copy.
 *
 *  Copy the source elements into the destination array.
 *  If n==0 then copy upto and including the NULLCHAR.
 *  If n >0 copy n characters and then write a NULLCHAR to the destination.
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
void copy( char* dst, const size_t doff,
           const char* src, const size_t soff, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((const char*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((char*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  
  register char*  D   = (dst+doff);
  register size_t idx = soff;
  
  if ( 0==n ) {
    while( src[idx] ) { *D++ = src[idx++]; }
    *D = NULLCHAR;
  } else {
    for ( size_t i=0; i<n; i++ ) {
      *D++ = src[idx++];
    }
  }
}

// =======================================================================================
/** @brief Copy.
 *  @param[out] dst  pointer to destination array.
 *  @param[in]  src  pointer to source array.
 *  @param[in]  soff source offset.
 *  @param[in]  n    number of elements to copy.
 *
 *  Copy the source elements into the destination array.
 *  If n==0 then copy upto and including the NULLCHAR.
 *  If n >0 copy n characters and then write a NULLCHAR to the destination.
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
void copy( char* dst, const char* src, const size_t soff, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((const char*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((char*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  
  register char*  D   = dst;
  register size_t idx = soff;
  
  if ( 0==n ) {
    while( src[idx] ) { *D++ = src[idx++]; }
    *D = NULLCHAR;
  } else {
    for ( size_t i=0; i<n; i++ ) {
      *D++ = src[idx++];
    }
  }
}

// =======================================================================================
/** @brief Copy.
 *  @param[out] dst  pointer to destination array.
 *  @param[in]  doff destination offset.
 *  @param[in]  src  pointer to source array.
 *  @param[in]  n    number of elements to copy.
 *
 *  Copy the source elements into the destination array.
 *  If n==0 then copy upto and including the NULLCHAR.
 *  If n >0 copy n characters and then write a NULLCHAR to the destination.
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
void copy( char* dst, const size_t doff, const char* src, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((const char*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((char*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  
  register char*  D   = (dst+doff);
  register size_t idx = 0;
  
  if ( 0==n ) {
    while( src[idx] ) { *D++ = src[idx++]; }
    *D = NULLCHAR;
  } else {
    for ( size_t i=0; i<n; i++ ) {
      *D++ = src[idx++];
    }
  }
}

// =======================================================================================
/** @brief Copy.
 *  @param[out] dst  pointer to destination array.
 *  @param[in]  src  pointer to source array.
 *  @param[in]  n    number of elements to copy.
 *
 *  Copy the source elements into the destination array.
 *  If n==0 then copy upto and including the NULLCHAR.
 *  If n >0 copy n characters and then write a NULLCHAR to the destination.
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
void copy( char* dst, const char* src, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((const char*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((char*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  
  register char*  D   = dst;
  register size_t idx = 0;
  
  if ( 0==n ) {
    while( src[idx] ) { *D++ = src[idx++]; }
    *D = NULLCHAR;
  } else {
    for ( size_t i=0; i<n; i++ ) {
      *D++ = src[idx++];
    }
  }
}



// =======================================================================================
// **                                C O P Y _ C L O N E                                **
// ======================================================================== END FILE =====
