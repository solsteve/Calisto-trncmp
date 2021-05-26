// ====================================================================== BEGIN FILE =====
// **                                 S U M M A T I O N                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
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
/** @brief Mean Square Error.
 *  @param[in] X pointer to a list.
 *  @param[in] Y pointer to another list.
 *  @param[in] n number of elements in the list.
 *  @return mean of the squares of the elements of the list.
 *
 *  $mse = \frac{1}{n} SUM^n_{i=1} {\(X_i - Y_i\)}^2$
 */
// ---------------------------------------------------------------------------------------
template<class T>
real8_t MSE( T* X, T* Y, size_t n ) {
  // -------------------------------------------------------------------------------------
  T s = (T)0;
  for ( size_t i=0; i<n; i++ ) {
    T d = X[i] - Y[i];
    s += (d*d);
  }
  return static_cast<real8_t>(s) / static_cast<real8_t>(n);
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
