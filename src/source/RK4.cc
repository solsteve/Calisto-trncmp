// ====================================================================== BEGIN FILE =====
// **                                       R K 4                                       **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2006-2019, Stephen W. Soliday                                      **
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
/** @brief  Runge-Kutta.
 *  @file   RK4.cc
 *  @author Stephen W. Soliday
 *  @date   2006-Nov-24 Original release.
 *  @date   2010-Jan-15 Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  Provides the abstract methods for a Runge-Kutta 4th Order Numerical Integrator.
 */
// =======================================================================================


#include <RK4.hh>


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n number of coupled first-order differential equations.
 *
 *   Allocate work vectors for integration.
 */
// ---------------------------------------------------------------------------------------
RK4::RK4( int32_t n ) : dim(n), A(0), B(0), C(0), D(0), W(0) {
  // -------------------------------------------------------------------------------------
  A = new real8_t[dim];
  B = new real8_t[dim];
  C = new real8_t[dim];
  D = new real8_t[dim];
  W = new real8_t[dim];
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] RP reference to an RK4 to copy from.
 *
 *   Allocate work vectors for integration.
 */
// ---------------------------------------------------------------------------------------
RK4::RK4( const RK4& RP ) : dim(RP.dim), A(0), B(0), C(0), D(0), W(0) {
  // -------------------------------------------------------------------------------------
  A = new real8_t[dim];
  B = new real8_t[dim];
  C = new real8_t[dim];
  D = new real8_t[dim];
  W = new real8_t[dim];
  copy(RP);
}


// =======================================================================================
/** @brief Destructor.
 *
 *  Free work vectors for integration.
 */
// ---------------------------------------------------------------------------------------
RK4::~RK4( void ) {
  // -------------------------------------------------------------------------------------
  delete[] A;
  delete[] B;
  delete[] C;
  delete[] D;
  delete[] W;
}


// =======================================================================================
/** @brief Copy.
 *  @param RP reference to a \a RK4 to copy from.
 *
 *   Overload the equal sign and perform a deep copy.
 */
// ---------------------------------------------------------------------------------------
RK4& RK4::operator= ( const RK4& RP ) {
  // -------------------------------------------------------------------------------------
  copy(RP);
  return *this;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] RP reference to an RK4 to copy from.
 *
 *  Perform a deep copy.
 */
// ---------------------------------------------------------------------------------------
void RK4::copy( const RK4& that ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<dim; i++ ) {
    this->A[i] = that.A[i];
    this->B[i] = that.B[i];
    this->C[i] = that.C[i];
    this->D[i] = that.D[i];
    this->W[i] = that.W[i];
  }
}


// =======================================================================================
/** @brief Fourth order Runge-Kutta.
 *  @param[in,out] Q  real vector containing the state.
 *  @param[in]     t0 initial time.
 *  @param[in]     t1 final time.
 *  @param[in]     step number of steps between current time t0 and final time t1.
 *  @param P vector containing fixed parameters.
 *  @return new time (t1).
 *
 *  Provides the implementation for a fourth order Runge-Kutta numerical integrator with 
 *  uniform step sizes.
 */
// ---------------------------------------------------------------------------------------
real8_t RK4::integrate( real8_t* Q, real8_t t0, real8_t t1, int32_t step, real8_t* P ) {
  // -------------------------------------------------------------------------------------
  const real8_t h  = (t1 - t0) / ((real8_t) step);
  const real8_t h2 = D_HALF * h;

  real8_t t = t0;
  for ( int32_t k=0; k<step; k++ ) {

    if (0 != check( Q, t, P )) { return t; }

    for ( int32_t j=0; j<dim; j++) { W[j] = Q[j];               } difeq(A, W, t,    P);
    for ( int32_t j=0; j<dim; j++) { W[j] = Q[j] + (A[j] * h2); } difeq(B, W, t+h2, P);
    for ( int32_t j=0; j<dim; j++) { W[j] = Q[j] + (B[j] * h2); } difeq(C, W, t+h2, P);
    for ( int32_t j=0; j<dim; j++) { W[j] = Q[j] + (C[j] * h);  } difeq(D, W, t+h,  P);

    for ( int32_t j=0; j<dim; j++) {
      Q[j] += ( h*(A[j] + D_TWO*(B[j] + C[j]) + D[j]) / D_SIX );
    }

    t += h;
  }

  return t;
}


// =======================================================================================
// **                                       R K 4                                       **
// ======================================================================== END FILE =====
