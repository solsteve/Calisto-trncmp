// ====================================================================== BEGIN FILE =====
// **                                   M A T H D E F                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 1991, 09, 19  Stephen W. Soliday                                   **
// **                              stephen.soliday@trncmp.org                           **
// **                              http://research.trncmp.org                           **
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
/** @brief  Extended math functions
 *  @file   mathdef.cc
 *  @author Stephen W. Soliday
 *  @date   1991-01-12  Original release.
 *  @date   2009-02-01  Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  Provides basic constants and math utilities.
 */
// =======================================================================================

#include <trncmp.hh>

// =======================================================================================
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x1    first  x coordinate.
 *  @param[in]  y1    first  y coordinate.
 *  @param[in]  x2    second x coordinate.
 *  @param[in]  y2    second y coordinate.
 *  @return true if singular.
 *
 *  Find the slope and intercept for the linear y = m x + b.
 */
// ---------------------------------------------------------------------------------------
bool linear( real8_t& slope, real8_t& inter,
                    const real8_t x1, const real8_t y1,
                    const real8_t x2, const real8_t y2 ) {
  // -------------------------------------------------------------------------------------
  real8_t d = x2-x1;
  if ( isZero(d) ) {
    slope = MAX_POS_DOUBLE;
    inter = D_ZERO;
    return true;
  }
  slope = ( y2 - y1 ) / d;
  inter = ( x2*y1 - x1*y2 ) / d;
  return false;
}

// =======================================================================================
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x1    first  x coordinate.
 *  @param[in]  y1    first  y coordinate.
 *  @param[in]  x2    second x coordinate.
 *  @param[in]  y2    second y coordinate.
 *  @return true if singular.
 *
 *  Find the slope and intercept for the linear y = m x + b.
 */
// ---------------------------------------------------------------------------------------
bool linear( real4_t& slope, real4_t& inter,
                    const real4_t x1, const real4_t y1,
                    const real4_t x2, const real4_t y2 ) {
  // -------------------------------------------------------------------------------------
  real4_t d = x2-x1;
  if ( isZero(d) ) {
    slope = MAX_POS_FLOAT;
    inter = F_ZERO;
    return true;
  }
  slope = ( y2 - y1 ) / d;
  inter = ( x2*y1 - x1*y2 ) / d;
  return false;
}

// =======================================================================================
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x     pointer to array of x coordinates.
 *  @param[in]  y     pointer to array of y coordinates.
 *  @param[in]  n     number of coordinates.
 *  @return true if singular.
 *
 *  Solve least squares for slope and intercept.
 */
// ---------------------------------------------------------------------------------------
bool linear( real8_t& slope, real8_t& inter,
             real8_t* x, real8_t* y, const size_t n ) {
  // -------------------------------------------------------------------------------------
  
  real8_t X  = x[0];
  real8_t Y  = y[0];
  real8_t X2 = x[0]*x[0];
  real8_t XY = x[0]*y[0];
  real8_t N  = (real8_t) n;

  for ( size_t i=1; i<n; i++ ) {
    X  += x[i];
    Y  += y[i];
    X2 += x[i]*x[i];
    XY += x[i]*y[i];
  }

  real8_t det = N*X2 - X*X;
  if ( isZero(det) ) {
    slope = MAX_POS_DOUBLE;
    inter = D_ZERO;
    return true;
  }

  slope = (N*XY - X*Y)  / det;
  inter = (X2*Y - X*XY) / det;

  return true;
}

// =======================================================================================
/** @brief Linear.
 *  @param[out] slope slope.
 *  @param[out] inter y intercept.
 *  @param[in]  x     pointer to array of x coordinates.
 *  @param[in]  y     pointer to array of y coordinates.
 *  @param[in]  n     number of coordinates.
 *  @return true if singular.
 *
 *  Solve least squares for slope and intercept.
 */
// ---------------------------------------------------------------------------------------
bool linear( real4_t& slope, real4_t& inter,
             real4_t* x, real4_t* y, const size_t n ) {
  // -------------------------------------------------------------------------------------
  
  real4_t X  = x[0];
  real4_t Y  = y[0];
  real4_t X2 = x[0]*x[0];
  real4_t XY = x[0]*y[0];
  real4_t N  = (real4_t) n;

  for ( size_t i=1; i<n; i++ ) {
    X  += x[i];
    Y  += y[i];
    X2 += x[i]*x[i];
    XY += x[i]*y[i];
  }

  real4_t det = N*X2 - X*X;
  if ( isZero(det) ) {
    slope = MAX_POS_FLOAT;
    inter = F_ZERO;
    return true;
  }

  slope = (N*XY - X*Y)  / det;
  inter = (X2*Y - X*XY) / det;

  return true;
}



/*
void    urandom           ( void* buffer, size_t n );
real8_t ArcTan            ( const real8_t y, const real8_t x );
real8_t ArcTanPM          ( const real8_t y, const real8_t x );
real8_t RadCorrect        ( const real8_t r );
real8_t RadCorrectPM      ( const real8_t r );
real8_t centerOfMass      ( const real8_t* M,   const real8_t* X,   const size_t n );
real8_t centerOfMassRad   ( const real8_t* mag, const real8_t* rad, const size_t n );
real8_t centerOfMassRadPM ( const real8_t* mag, const real8_t* rad, const size_t n );
real8_t normalize         (       real8_t* vec,                     const size_t n );
real8_t SumSquareDiff     ( const real8_t* A,   const size_t n );
real8_t SumSquareDiff     ( const real8_t* A,   const real8_t* B,   const size_t n );
int32_t SumSquareDiff     ( const int32_t* A,   const int32_t* B,   const size_t n );
real8_t EuclideanDistance ( const real8_t* A,   const real8_t* B,   const size_t n );
real8_t MeanSquareError   ( const real8_t* A,   const real8_t* B,   const size_t n );
*/












// =======================================================================================
// ---------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------

// =======================================================================================
// **                                   M A T H D E F                                   **
// ======================================================================== END FILE =====
