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
 *  @file   summation.cc
 *  @author Stephen W. Soliday
 *  @date   2015-12-24 Original FORTRAN release.
 *  @date   2019-Apr-11 C++ Port.
 *
 *  Provides the methods for various summation functions on single dimesional arrays.
 */
// =======================================================================================


#include <trncmp.hh>


// =======================================================================================
/** @brief Radial Center of mass.
 *  @param[in] mag array of vector magnitudes
 *  @param[in] rad array of vector directions
 *  @param[in] n   number of array elements
 *  @return    direction of the weighted average vector [0,2Pi)
 *
 *  Find the two dimensional weighted average [0,2Pi)
 */
// ---------------------------------------------------------------------------------------
real8_t centerOfMassRad( const real8_t* mag, const real8_t* rad, const size_t n ) {
  // -------------------------------------------------------------------------------------
  real8_t MXSum = D_ZERO;
  real8_t MYSum = D_ZERO;
  real8_t MSum  = D_ZERO;

  for (size_t i=0; i<n; i++) { MSum  +=  mag[i]; }

  if (isZero(MSum)) { return D_ZERO; }

  for (size_t i=0; i<n; i++) {
    MXSum += (mag[i] * cos(rad[i]));
    MYSum += (mag[i] * sin(rad[i]));
  }

  return ArcTan( (MYSum / MSum), (MXSum / MSum) );
}


// =======================================================================================
/** @brief Radial Center of mass.
 *  @param[in] mag array of vector magnitudes
 *  @param[in] rad array of vector directions
 *  @param[in] n   number of array elements
 *  @return    direction of the weighted average vector (-Pi,+Pi]
 *
 *  Find the two dimensional weighted average (-Pi,+Pi]
 */
// ---------------------------------------------------------------------------------------
real8_t centerOfMassRadPM( const real8_t* mag, const real8_t* rad, const size_t n ) {
  // -------------------------------------------------------------------------------------
  real8_t MXSum = D_ZERO;
  real8_t MYSum = D_ZERO;
  real8_t MSum  = D_ZERO;

  for (size_t i=0; i<n; i++) { MSum  +=  mag[i]; }

  if (isZero(MSum)) { return D_ZERO; }

  for (size_t i=0; i<n; i++) {
    MXSum += (mag[i] * cos(rad[i]));
    MYSum += (mag[i] * sin(rad[i]));
  }

  return ArcTanPM( (MYSum / MSum), (MXSum / MSum) );  
}


// =======================================================================================
/** @brief Radial Center of mass.
 *  @param[in] mag array of vector magnitudes
 *  @param[in] rad array of vector directions
 *  @param[in] n   number of array elements
 *  @return    direction of the weighted average vector [0,2Pi)
 *
 *  Find the two dimensional weighted average [0,2Pi)
 */
// ---------------------------------------------------------------------------------------
real4_t centerOfMassRad( const real4_t* mag, const real4_t* rad, const size_t n ) {
  // -------------------------------------------------------------------------------------
  real4_t MXSum = F_ZERO;
  real4_t MYSum = F_ZERO;
  real4_t MSum  = F_ZERO;

  for (size_t i=0; i<n; i++) { MSum  +=  mag[i]; }

  if (isZero(MSum)) { return F_ZERO; }

  for (size_t i=0; i<n; i++) {
    MXSum += (mag[i] * cosf(rad[i]));
    MYSum += (mag[i] * sinf(rad[i]));
  }

  return ArcTan( (MYSum / MSum), (MXSum / MSum) );
}


// =======================================================================================
/** @brief Radial Center of mass.
 *  @param[in] mag array of vector magnitudes
 *  @param[in] rad array of vector directions
 *  @param[in] n   number of array elements
 *  @return    direction of the weighted average vector (-Pi,+Pi]
 *
 *  Find the two dimensional weighted average (-Pi,+Pi]
 */
// ---------------------------------------------------------------------------------------
real4_t centerOfMassRadPM( const real4_t* mag, const real4_t* rad, const size_t n ) {
  // -------------------------------------------------------------------------------------
  real4_t MXSum = F_ZERO;
  real4_t MYSum = F_ZERO;
  real4_t MSum  = F_ZERO;

  for (size_t i=0; i<n; i++) { MSum  +=  mag[i]; }

  if (isZero(MSum)) { return F_ZERO; }

  for (size_t i=0; i<n; i++) {
    MXSum += (mag[i] * cosf(rad[i]));
    MYSum += (mag[i] * sinf(rad[i]));
  }

  return ArcTanPM( (MYSum / MSum), (MXSum / MSum) );  
}


// =======================================================================================
// **                                 S U M M A T I O N                                 **
// ======================================================================== END FILE =====
