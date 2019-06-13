// ====================================================================== BEGIN FILE =====
// **                                C O P Y _ C L O N E                                **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019  Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
