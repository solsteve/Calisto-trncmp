// ====================================================================== BEGIN FILE =====
// **                                C O P Y _ C L O N E                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  Copy & Clone
 *  @file   copy_clone.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-23 Original release.
 *
 *  Provides the methods for various copy and clone single dimension arrays.
 */
// =======================================================================================


#include <trncmp.hh>
#include <string.h>


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
  if (static_cast<const char*>(0) == src) throw std::invalid_argument("source array pointer NULL");
  if (static_cast<char*>(0) == dst) throw std::invalid_argument("destination array pointer NULL");
  
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
  if (static_cast<const char*>(0) == src) throw std::invalid_argument("source array pointer NULL");
  if (static_cast<char*>(0) == dst) throw std::invalid_argument("destination array pointer NULL");
  
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
  if (static_cast<const char*>(0) == src) throw std::invalid_argument("source array pointer NULL");
  if (static_cast<char*>(0) == dst) throw std::invalid_argument("destination array pointer NULL");
  
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
  if (static_cast<const char*>(0) == src) throw std::invalid_argument("source array pointer NULL");
  if (static_cast<char*>(0) == dst) throw std::invalid_argument("destination array pointer NULL");
  
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
/** @brief Clone.
 *  @param[in] src  pointer to source character array.
 *  @return    pointer to newly allocated destination character array.
 *
 *  Allocate a destination array and copy the source into it.
 *  @note it is your responsibility to delete the destination array.
 */
// ---------------------------------------------------------------------------------------
char* clone( const char* src ) {
  // -------------------------------------------------------------------------------------
  size_t n = strlen(src);
  char* dst = new char[n+1];
  for ( size_t i=0; i<n; i++ ) {
    dst[i] = src[i];
  }
  dst[n] = (char)0;
  return dst;
}





// =======================================================================================
// **                                C O P Y _ C L O N E                                **
// ======================================================================== END FILE =====
