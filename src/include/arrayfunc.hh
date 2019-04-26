// ====================================================================== BEGIN FILE =====
// **                                 A R R A Y F U N C                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2002, 2019  Stephen W. Soliday                                     **
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
/** @brief  Main header
 *  @file   arrayfunc.hh
 *  @author Stephen W. Soliday
 *  @date   2002-08-17 Original release.
 *  @date   2009-12-23 Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  This is a collection of array based functions.
 */
// =======================================================================================


#ifndef __HH_ARRAYFUNC_TRNCMP
#define __HH_ARRAYFUNC_TRNCMP


// =======================================================================================
/** @brief IEEE8 safe comparison.
 *  @param _x   first value.
 *  @param _y   second value.
 *  @param _act action.
 *
 *  Compare _x and _y. Only perform _act if _x and _y are equal in value
 */
// ---------------------------------------------------------------------------------------
#define IEEE8(_x, _y, _act) {                   \
    if (_x > _y) {                              \
      /* NOOP */                                \
    } else {                                    \
      if (_x < _y) {                            \
        /* NOOP */                              \
      } else {                                  \
        _act;                                   \
      }                                         \
    }                                           \
  }
// =======================================================================================


// =======================================================================================
/** @brief Zero.
 *  @param[in] ary    pointer to a 1-D array.
 *  @param[in] n      number of elements in the array.
 *  @param[in] setval optional set value (default: 0)
 *
 *  Set each element in the array.
 */
// ---------------------------------------------------------------------------------------
template< class T >
void zero( T* ary, size_t n, T setval = (T)0 ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<n; i++ ) {
    ary[i] = setval;
  }
}


// =======================================================================================
/** @brief Zero.
 *  @param[in] ary    pointer to a 2-D array.
 *  @param[in] nr     number of row elements in the array.
 *  @param[in] nc     number of column elements in the array.
 *  @param[in] setval optional set value (default: 0)
 *
 *  Set each element in the array.
 */
// ---------------------------------------------------------------------------------------
template< class T >
void zero( T** ary, size_t nr, size_t nc, T setval = (T)0 ) {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<nr; i++ ) {
    for ( size_t j=0; j<nc; j++ ) {
      ary[i][j] = setval;
    }
  }
}


// =======================================================================================
/** @brief Count.
 *  @param test value to find in the array.
 *  @param array the array to test.
 *  @param len the length of the array.
 *  @return true  if (test) is in (array), false if (test) is not a member of (array).
 * 
 *  Count the number of times (test) appears in (array).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
size_t count( const T test, const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");

  size_t c=0;
  for (size_t i=0; i<len; i++) IEEE8(test, array[i], c++; );
  return c;
}


// =======================================================================================
/** @brief Is in Array.
 *  @param test value to find in the array.
 *  @param array the array to test.
 *  @param len the length of the array.
 *  @return true if (test) is in (array), false if (test) is not a member of (array).
 * 
 *  is (test) in the set (array) of length (len).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
bool isIn( const T test, const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");

  for (size_t i=0; i<len; i++) IEEE8(test, array[i], return true; );
  return false;
}


// =======================================================================================
/** @brief Find position in array.
 *  @param test  value to find in the array.
 *  @param array the array to test.
 *  @param len   the length of the array.
 *  @return the index for (test) in (array). ERROR if (test) is not in (array) return -1.
 *
 *  find the index for (test) in the set (array) of length (len).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
ssize_t findIn( const T test, const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");

  for (size_t i=0; i<len; i++) IEEE8(test, array[i], return i; );
  return -1;
}


// =======================================================================================
/** @brief Find minimum.
 *  @param array the array to test.
 *  @param len the length of the array.
 *  @return the minimum value of elements in (array).
 *
 *  find the minimum value of elements in the set (array) of length (len).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
T Min( const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");

  T minV = array[0]; 
  for (size_t i=1; i<len; i++) {
    if (array[i] < minV) { minV = array[i]; }
  }
  return minV;
}


// =======================================================================================
/** @brief Find maximum.
 *  @param array the array to test.
 *  @param len the length of the array.
 *  @return the maximum value of elements in (array).
 *
 *  find the maximum value of elements in the set (array) of length (len).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
T Max( const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");
 
  T maxV = array[0]; 
  for (size_t i=1; i<len; i++) {
    if (array[i] > maxV) { maxV = array[i]; }
  }
  return maxV;
}


// =======================================================================================
/** @brief Find minimum.
 *  @param array the array to test.
 *  @param len the length of the array.
 *  @return the index for the minimum value of elements in (array).
 *
 *  find the index for the minimum value of elements in the set (array) of length (len).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
size_t MinIndex( const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");

  size_t minIdx = 0;
  T      minV   = array[0]; 
  for (size_t i=1; i<len; i++) {
    if (array[i] < minV) {
      minIdx = i;
      minV   = array[i];
    }
  }
  return minIdx;
}


// =======================================================================================
/** @brief Find maximum.
 *  @param array the array to test.
 *  @param len the length of the array.
 *  @return the index for the maximum value of elements in (array).
 *
 *  find the index for the maximum value of elements in the set (array) of length (len).
 *  This function throws a NullException if the pointer to the array is NULL.
 */
// ---------------------------------------------------------------------------------------
template < class T >
size_t MaxIndex( const T* array, const size_t len ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == array) throw std::invalid_argument("array pointer NULL");

  size_t maxIdx = 0;
  T      maxV   = array[0]; 
  for (size_t i=1; i<len; i++) {
    if (array[i] > maxV) {
      maxIdx = i;
      maxV   = array[i];
    }
  }
  return maxIdx;
}


// =======================================================================================
/** @brief Copy.
 *  @param dst destination vector.
 *  @param src source vector
 *  @param n length of the vector
 *  @return true=success, false=failure
 *
 *  Copy vector of real8_t.
 *  This function throws a NullException if the pointer to the dst is NULL.
 *  This function throws a NullException if the pointer to the src is NULL.
 *  This function throws an InvalidException src length is zero.
 */
// ---------------------------------------------------------------------------------------
template < class T >
void copy( T* dst, const T* src, const size_t n ) {
  // -------------------------------------------------------------------------------------
  if ((const T*)0 == dst) throw std::invalid_argument("destination pointer NULL");
  if ((const T*)0 == src) throw std::invalid_argument("source pointer NULL");
  if (0 == n)             throw std::invalid_argument("copying zero elements makes no sense");

  for (size_t i=0; i<n; i++) {
    dst[i] = src[i];
  }
}


#endif


// =======================================================================================
// **                                 A R R A Y F U N C                                 **
// ======================================================================== END FILE =====
