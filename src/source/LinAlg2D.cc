// ====================================================================== BEGIN FILE =====
// **                                  L I N A L G 2 D                                  **
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
 *  @file   LinAlg2D.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-07
 *
 *  Provides the methods for linear algebra functions, with three element vectors and
 *  nine element matrices.
 */
// =======================================================================================

#include <LinAlg2D.hh>

// =======================================================================================
/** @brief Covariance.
 *  @param[out] M    reference to a covariance matrix.
 *  @param[in]  data pointer to an array of three element arrays.
 *  @param[in]  n    number of samples.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix2D& M, real8_t data[][2], size_t n ) {
  // -------------------------------------------------------------------------------------
  const real8_t fn   = (real8_t)n;
  const real8_t fnm1 = (real8_t)(n-1);
  
  real8_t tmu_x = D_ZERO;
  real8_t tmu_y = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    tmu_x += data[i][0];
    tmu_y += data[i][1];
  }
  
  const real8_t mu_x = tmu_x / fn;
  const real8_t mu_y = tmu_y / fn;
  
  // -------------------------------------------------------------------------------------

  real8_t xx = D_ZERO;
  real8_t xy = D_ZERO;
  real8_t yy = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    const real8_t dx = data[i][0] - mu_x;
    const real8_t dy = data[i][1] - mu_y;
    
    xx += (dx * dx);
    xy += (dx * dy);

    yy += (dy * dy);
  }

  // -------------------------------------------------------------------------------------

  M.q[0] = xx / fnm1;    M.q[1] = xy / fnm1;
  M.q[2] = xy / fnm1;    M.q[3] = yy / fnm1;
}


// =======================================================================================
/** @brief Covariance.
 *  @param[out] M    reference to a covariance matrix.
 *  @param[in]  data pointer to an array of Vector2D.
 *  @param[in]  n    number of samples.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
void covariance( Matrix2D& M, Vector2D *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  const real8_t fn   = (real8_t)n;
  const real8_t fnm1 = (real8_t)(n-1);

  real8_t tmu_x = D_ZERO;
  real8_t tmu_y = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    tmu_x += data[i].x[0];
    tmu_y += data[i].x[1];
  }
  
  const real8_t mu_x = tmu_x / fn;
  const real8_t mu_y = tmu_y / fn;
  
  // -------------------------------------------------------------------------------------

  real8_t xx = D_ZERO;
  real8_t xy = D_ZERO;
  real8_t yy = D_ZERO;

  for ( size_t i=0; i<n; i++ ) {
    const real8_t dx = data[i].x[0] - mu_x;
    const real8_t dy = data[i].x[1] - mu_y;
    
    xx += (dx * dx);
    xy += (dx * dy);

    yy += (dy * dy);
  }
  
  // -------------------------------------------------------------------------------------

  M.q[0] = xx / fnm1;    M.q[1] = xy / fnm1;
  M.q[2] = xy / fnm1;    M.q[3] = yy / fnm1;
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
const Matrix2D covariance( real8_t data[][2], size_t n ) {
  // -------------------------------------------------------------------------------------
  Matrix2D M;
  covariance( M, data, n );
  return M;
}


// =======================================================================================
/** @brief Covariance.
 *  @param[in]  data pointer to an array of Vector2D.
 *  @param[in]  n    number of samples.
 *  @return covariance matrix.
 *
 *  Calculate the covariance of the samples.
 */
// ---------------------------------------------------------------------------------------
const Matrix2D covariance( Vector2D *data, size_t n ) {
  // -------------------------------------------------------------------------------------
  Matrix2D M;
  covariance( M, data, n );
  return M;
}


// =======================================================================================
/** @brief First Axis Rotation.
 *  @param[in]  angle in radians.
 *  @return affine matrix.
 *
 *  Rotate points from positive X to positive Y.
 */
// ---------------------------------------------------------------------------------------
const Matrix2D ROT( const real8_t ang ) {
  // -------------------------------------------------------------------------------------
  real8_t s, c;
  sincos( ang, &s, &c );
  return Matrix2D( c, s, -s, c );
}




// =======================================================================================
/** @brief Eigen System.
 *  @param[out] eval reference to eigen values.
 *  @param[out] ev1  reference to first  eigen vector.
 *  @param[out] ev2  reference to second eigen vector.
 *  @param[in]  M    reference to input Matrix3D.
 *  @return true if an error occurs.
 */
// ---------------------------------------------------------------------------------------
bool eigen( Vector2D& eval, Vector2D& ev1, Vector2D& ev2, const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
  const real8_t a = M.q[0];
  const real8_t b = M.q[1];
  const real8_t c = M.q[3];
  const real8_t d = M.q[4];

  const real8_t T =  a + d;
  const real8_t D = (a * d) - (b * c);
  const real8_t R = (T * T) - (D_FOUR * D);
    
  if ( D_ZERO > R ) { return false; }

  const real8_t K = sqrt( R );

  const real8_t L0 = D_HALF * (T + K);
  const real8_t L1 = D_HALF * (T - K);

  const real8_t e  = L0 - d;
  const real8_t f  = L1 - d;
  const real8_t g  = e * f;

  real8_t v00 = D_ZERO;
  real8_t v01 = D_ZERO;
  real8_t v10 = D_ZERO;
  real8_t v11 = D_ZERO;
    
  if ( ( D_ZERO < g ) || ( D_ZERO > g ) ) {
    v00 = D_ONE; v01 = c / e;
    v10 = D_ONE; v11 = c / f;
  } else {
    if ( ( D_ZERO < b ) || ( D_ZERO > b ) ) {
      v00 = D_ONE; v01 = (L0 - a) / b;
      v10 = D_ONE; v11 = (L1 - a) / b;
    } else {
      v00 = D_ONE;  v01 = D_ZERO;
      v10 = D_ZERO; v11 = D_ONE;
    }
  }

  if ( L0 > L1 ) {
    eval.x[0] = L0;    ev1.x[0] = v00; ev1.x[1] = v01;
    eval.x[1] = L1;    ev2.x[0] = v10; ev2.x[1] = v11;
  } else {
    eval.x[0] = L1;    ev1.x[0] = v10; ev1.x[1] = v11;
    eval.x[1] = L0;    ev2.x[0] = v00; ev2.x[1] = v01;
  }

  return true;
}


// =======================================================================================
// **                                  L I N A L G 2 D                                  **
// ======================================================================== END FILE =====
