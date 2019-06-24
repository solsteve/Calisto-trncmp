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
 *  @file   copy_clone.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-23 Original release.
 *
 *  Provides the interface and templates for various copy and clone of
 *  single dimension arrays.
 */
// =======================================================================================


#ifndef __HH_COPYCLONE_TRNCMP
#define __HH_COPYCLONE_TRNCMP

#define NULLCHAR ((char)0)  ///< Null character for the end of a char string.

void copy  ( char* dst, const size_t doff,
             const char* src, const size_t soff, const size_t n=0 );

void copy  ( char* dst, const char* src, const size_t soff, const size_t n=0 );

void copy  ( char* dst, const size_t doff, const char* src, const size_t n=0 );

void copy  ( char* dst, const char* src, const size_t n=0 );

  
// =======================================================================================
/** @brief Copy.
 *  @param[out] dst  pointer to destination array.
 *  @param[in]  doff destination offset.
 *  @param[in]  src  pointer to source array.
 *  @param[in]  soff source offset.
 *  @param[in]  n    number of elements to copy.
 *
 *  Copy the source elements into the destination array.
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void copy( T* dst, const size_t doff, T* src, const size_t soff, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((T*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((T*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  T* S = (src+soff);
  T* D = (dst+doff);
  for ( size_t i=0; i<n; i++ ) {
    *D++ = *S++;
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
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void copy( T* dst, T* src, const size_t soff, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((T*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((T*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  T* S = (src+soff);
  T* D = dst;
  for ( size_t i=0; i<n; i++ ) {
    *D++ = *S++;
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
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void copy( T* dst, const size_t doff, T* src, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((T*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((T*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  T* S = src;
  T* D = (dst+doff);
  for ( size_t i=0; i<n; i++ ) {
    *D++ = *S++;
  }
}


// =======================================================================================
/** @brief Copy.
 *  @param[out] dst  pointer to destination array.
 *  @param[in]  src  pointer to source array.
 *  @param[in]  n    number of elements to copy.
 *
 *  Copy the source elements into the destination array.
 *  @note it is your responsibility to make sure that the destination is large enough.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void copy( T* dst, T* src, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((T*)0 == src) throw std::invalid_argument("source array pointer NULL");
  if ((T*)0 == dst) throw std::invalid_argument("destination array pointer NULL");
  T* S = src;
  T* D = dst;
  for ( size_t i=0; i<n; i++ ) {
    *D++ = *S++;
  }
}

char* clone( const char* src );


// =======================================================================================
/** @brief Clone.
 *  @param[in] src  pointer to source array.
 *  @param[in] soff source offset.
 *  @param[in] n    number of elements to copy.
 *  @return    pointer to newly allocated destination array.
 *
 *  Allocate a destination array and copy the source into it.
 *  @note it is your responsibility to delete the destination array.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T* clone( T* src, const size_t soff, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((T*)0 == src) throw std::invalid_argument("source array pointer NULL");
  T* dst = new T[n];
  T* S = (src+soff);
  T* D = dst;
  for ( size_t i=0; i<n; i++ ) {
    *D++ = *S++;
  }
  return dst;
}


// =======================================================================================
/** @brief Clone.
 *  @param[in] src  pointer to source array.
 *  @param[in] n    number of elements to copy.
 *  @return    pointer to newly allocated destination array.
 *
 *  Allocate a destination array and copy the source into it.
 *  @note it is your responsibility to delete the destination array.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T* clone( T* src, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((T*)0 == src) throw std::invalid_argument("source array pointer NULL");
  T* dst = new T[n];
  T* S = src;
  T* D = dst;
  for ( size_t i=0; i<n; i++ ) {
    *D++ = *S++;
  }
  return dst;
}


#endif


// =======================================================================================
// **                                C O P Y _ C L O N E                                **
// ======================================================================== END FILE =====
