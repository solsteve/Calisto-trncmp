// ====================================================================== BEGIN FILE =====
// **                                  L I N A L G 3 D                                  **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief  Linear algebra functions.
 *  @file   LinAlg3D.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides the methods for linear algebra functions, with three element vectors and
 *  nine element matrices.
 */
// =======================================================================================

#include <LinAlg3D.hh>

// =======================================================================================
/** @brief Covariance.
 *  @param[out] M    reference to a covariance matrix.
 *  @param[in]  data pointer to an array of three element arrays.
 *  @param[in]  n    number of samples.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix3D& M, real8_t data[][3], size_t n ) {
  // -------------------------------------------------------------------------------------
  const real8_t fn   = (real8_t)n;
  const real8_t fnm1 = (real8_t)(n-1);
  
  real8_t tmu_x = D_ZERO;
  real8_t tmu_y = D_ZERO;
  real8_t tmu_z = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    tmu_x += data[i][0];
    tmu_y += data[i][1];
    tmu_z += data[i][2];
  }
  
  const real8_t mu_x = tmu_x / fn;
  const real8_t mu_y = tmu_y / fn;
  const real8_t mu_z = tmu_z / fn;
  
  // -------------------------------------------------------------------------------------

  real8_t xx = D_ZERO;
  real8_t xy = D_ZERO;
  real8_t xz = D_ZERO;
  real8_t yy = D_ZERO;
  real8_t yz = D_ZERO;
  real8_t zz = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    const real8_t dx = data[i][0] - mu_x;
    const real8_t dy = data[i][1] - mu_y;
    const real8_t dz = data[i][2] - mu_z;
    
    xx += (dx * dx);
    xy += (dx * dy);
    xz += (dx * dz);

    yy += (dy * dy);
    yz += (dy * dz);

    zz += (dz * dz);
  }

  // -------------------------------------------------------------------------------------

  M.a00 = xx / fnm1;    M.a01 = xy / fnm1;    M.a02 = xz / fnm1;
  M.a10 = xy / fnm1;    M.a11 = yy / fnm1;    M.a12 = yz / fnm1;
  M.a20 = xz / fnm1;    M.a21 = yz / fnm1;    M.a22 = zz / fnm1;
}


// =======================================================================================
/** @brief Covariance.
 *  @param[out] M    reference to a covariance matrix.
 *  @param[in]  data pointer to an array of Vector3D.
 *  @param[in]  n    number of samples.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix3D& M, Vector3D *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  const real8_t fn = (real8_t)n;
  const real8_t fnm1 = (real8_t)(n-1);

  real8_t tmu_x = D_ZERO;
  real8_t tmu_y = D_ZERO;
  real8_t tmu_z = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    tmu_x += data[i].x[0];
    tmu_y += data[i].x[1];
    tmu_z += data[i].x[2];
  }
  
  const real8_t mu_x = tmu_x / fn;
  const real8_t mu_y = tmu_y / fn;
  const real8_t mu_z = tmu_z / fn;
  
  // -------------------------------------------------------------------------------------

  real8_t xx = D_ZERO;
  real8_t xy = D_ZERO;
  real8_t xz = D_ZERO;
  real8_t yy = D_ZERO;
  real8_t yz = D_ZERO;
  real8_t zz = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    const real8_t dx = data[i].x[0] - mu_x;
    const real8_t dy = data[i].x[1] - mu_y;
    const real8_t dz = data[i].x[2] - mu_z;
    
    xx += (dx * dx);
    xy += (dx * dy);
    xz += (dx * dz);

    yy += (dy * dy);
    yz += (dy * dz);

    zz += (dz * dz);
  }

  // -------------------------------------------------------------------------------------

  M.a00 = xx / fnm1;    M.a01 = xy / fnm1;    M.a02 = xy / fnm1;
  M.a10 = xy / fnm1;    M.a11 = yy / fnm1;    M.a12 = yz / fnm1;
  M.a20 = xz / fnm1;    M.a21 = yz / fnm1;    M.a22 = zz / fnm1;
}





// =======================================================================================
/** @brief Covariance.
 *  @param[in]  data pointer to an array of three element arrays.
 *  @param[in]  n    number of samples.
 *  @return covariance matrix.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D covariance( real8_t data[][3], size_t n ) {
  // -------------------------------------------------------------------------------------
  Matrix3D M;
  covariance( M, data, n );
  return M;
}


// =======================================================================================
/** @brief Covariance.
 *  @param[in]  data pointer to an array of Vector3D.
 *  @param[in]  n    number of samples.
 *  @return covariance matrix.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D covariance( Vector3D *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  Matrix3D M;
  covariance( M, data, n );
  return M;
}


// =======================================================================================
/** @brief First Axis Rotation.
 *  @param[in]  angle in radians.
 *  @return affine matrix.
 *
 *  Rotate points around the X-axis from positive Y to positive Z.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D ROT1( const real8_t ang ) {
  // -------------------------------------------------------------------------------------
  real8_t s, c;
  sincos( ang, &s, &c );
  return Matrix3D( D_ONE,  D_ZERO, D_ZERO,
                   D_ZERO,  c,     s,
                   D_ZERO, -s,     c );
}


// =======================================================================================
/** @brief Second Axis Rotation.
 *  @param[in] ang angle in radians.
 *  @return affine matrix.
 *
 *  Rotate points around the Y-axis from positive Z to positive X.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D ROT2( const real8_t ang ) {
  // -------------------------------------------------------------------------------------
  real8_t s, c;
  sincos( ang, &s, &c );
  return Matrix3D( c,      D_ZERO, -s,
                   D_ZERO, D_ONE,  D_ZERO,
                   s,      D_ZERO, c );
}


// =======================================================================================
/** @brief Third Axis Rotation.
 *  @param[in] ang angle in radians.
 *  @return affine matrix.
 *
 *  Rotate points around the Z-axis from positive X to positive Y.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D ROT3( const real8_t ang ) {
  // -------------------------------------------------------------------------------------
  real8_t s, c;
  sincos( ang, &s, &c );
  return Matrix3D(  c,     s,      D_ZERO,
                    -s,     c,      D_ZERO,
                    D_ZERO, D_ZERO, D_ONE );
}


// =======================================================================================
// **                                  L I N A L G 3 D                                  **
// ======================================================================== END FILE =====
