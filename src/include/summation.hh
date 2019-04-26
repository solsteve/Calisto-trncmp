// ====================================================================== BEGIN FILE =====
// **                                 S U M M A T I O N                                 **
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
/** @brief  Summation
 *  @file   summation.hh
 *  @author Stephen W. Soliday
 *  @date   2015-12-24 Original FORTRAN release.
 *  @date   2019-Apr-11 C++ Port.
 *
 *  Provides the interface for various summation functions on single dimesional arrays.
 */
// =======================================================================================


#ifndef __HH_SUMMATION_TRNCMP
#define __HH_SUMMATION_TRNCMP


// =======================================================================================t
/** @brief Sum.
 *  @param[in] X pointer to a list.
 *  @param[in] n number of elements in the list.
 *  @return sum of the elements of the list.
 *
 *  $sum = SUM^n_{i=1} X_i$
 */
// ---------------------------------------------------------------------------------------
template<class T>
T sum( T* X, size_t n ) {
  // -------------------------------------------------------------------------------------
  T s = (T)0;
  for ( size_t i=0; i<n; i++ ) {
    s += X[i];
  }
  return s;
}


// =======================================================================================t
/** @brief Sum of squares.
 *  @param[in] X pointer to a list.
 *  @param[in] n number of elements in the list.
 *  @return sum of the squares of the elements of the list.
 *
 *  $sum = SUM^n_{i=1} {\(X_i\)}^2$
 */
// ---------------------------------------------------------------------------------------
template<class T>
T sumsq( T* X, size_t n ) {
  // -------------------------------------------------------------------------------------
  T s = (T)0;
  for ( size_t i=0; i<n; i++ ) {
    s += (X[i]*X[i]);
  }
  return s;
}


// =======================================================================================t
/** @brief Sum.
 *  @param[in] W pointer to a list.
 *  @param[in] X pointer to a list.
 *  @param[in] n number of elements in the list.
 *  @return sum of the elements of the list.
 *
 *  $sum = SUM^n_{i=1} W_i cdot X_i$
 */
// ---------------------------------------------------------------------------------------
template<class T>
T wsum( T* W, T* X, size_t n ) {
  // -------------------------------------------------------------------------------------
  T s = (T)0;
  for ( size_t i=0; i<n; i++ ) {
    s += (W[i]*X[i]);
  }
  return s;
}


// =======================================================================================t
/** @brief Sum Difference.
 *  @param[in] L pointer to the left hand side list.
 *  @param[in] R pointer to the right hand side list.
 *  @param[in] n number of elements in the list.
 *  @return sum of the elements of the list.
 *
 *  $sum = SUM^n_{i=1} \(L_i - R_i\)$
 */
// ---------------------------------------------------------------------------------------
template<class T>
T sumDiff( T* L, T* R, size_t n ) {
  // -------------------------------------------------------------------------------------
  T s = (T)0;
  for ( size_t i=0; i<n; i++ ) {
    s = s + (L[i] - R[i]);
  }
  return s;
}


// =======================================================================================t
/** @brief Sum of squares of the differences.
 *  @param[in] X pointer to a list.
 *  @param[in] Y pointer to another list.
 *  @param[in] n number of elements in the list.
 *  @return sum of the squares of the elements of the list.
 *
 *  $sum = SUM^n_{i=1} {\(X_i - Y_i\)}^2$
 */
// ---------------------------------------------------------------------------------------
template<class T>
T sumsqDiff( T* X, T* Y, size_t n ) {
  // -------------------------------------------------------------------------------------
  T s = (T)0;
  for ( size_t i=0; i<n; i++ ) {
    T d = X[i] - Y[i];
    s += (d*d);
  }
  return s;
}


// =======================================================================================t
/** @brief Center of mass.
 *  @param W array of Masses    ( weights )
 *  @param X array of Positions ( values  )
 *  @param n number of array elements
 *  @return  the center of mass ( weighted average )
 *
 *  Determine the Center of Mass ( Weighted Average ) (-Inf,Inf)
 */
// ---------------------------------------------------------------------------------------
template<class T>
T centerOfMass( T* W, T* X, size_t n ) {
  // -------------------------------------------------------------------------------------
  return wsum( W, X, n ) / sum( W, n );
}


real8_t centerOfMassRad   ( const real8_t* mag, const real8_t* rad, const size_t n );
real8_t centerOfMassRadPM ( const real8_t* mag, const real8_t* rad, const size_t n );
real4_t centerOfMassRad   ( const real4_t* mag, const real4_t* rad, const size_t n );
real4_t centerOfMassRadPM ( const real4_t* mag, const real4_t* rad, const size_t n );


#endif


// =======================================================================================
// **                                 S U M M A T I O N                                 **
// ======================================================================== END FILE =====
