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
 *  @file   RK4.hh
 *  @author Stephen W. Soliday
 *  @date   2006-Nov-24 Original release.
 *  @date   2010-Jan-15 Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  Provides the abstract interface for a Runge-Kutta 4th Order Numerical Integrator.
 */
// =======================================================================================

#ifndef __HH_RK4_TRNCMP
#define __HH_RK4_TRNCMP

#include <trncmp.hh>

// =======================================================================================
class RK4 {
  // -------------------------------------------------------------------------------------
 protected:
  int32_t  dim;  ///< number of coupled first order equations.
  real8_t* A;    ///< stage one   state vector.
  real8_t* B;    ///< stage two   state vector.
  real8_t* C;    ///< stage three state vector.
  real8_t* D;    ///< stage four  state vector.
  real8_t* W;    ///< DIFEQ input vector.

 public:
  RK4                ( int32_t n );
  RK4                ( const RK4& RP );
  virtual ~RK4       ( void );

  RK4&    operator=  ( const RK4& RP );
  void    copy       ( const RK4& RP );

  real8_t integrate  ( real8_t *Q, real8_t t0, real8_t t1, int32_t step, real8_t *P );

  // =====================================================================================
  /** @brief Check State.
   *  @param[in] Q current state vector.
   *  @param[in] t current time.
   *  @param[in] P parameter vector.
   *  @return 0=continue, non-zero=stop
   */
  // -------------------------------------------------------------------------------------
  virtual int check( real8_t* Q, real8_t t, real8_t* P ) = 0;
  // -------------------------------------------------------------------------------------

  
  // =====================================================================================
  /** @brief Differential equations.
   *  @param[out] Qd first time derivative of the current state vector.
   *  @param[in]  Q  current state vector.
   *  @param[in]  t  current time.
   *  @param[in]  P  parameter vector.
   */
  // -------------------------------------------------------------------------------------
  virtual void difeq( real8_t* Qd, real8_t* Q, real8_t t, real8_t* P ) = 0;
  // -------------------------------------------------------------------------------------


}; // end class RK4

#endif


// =======================================================================================
// **                                       R K 4                                       **
// ======================================================================== END FILE =====
