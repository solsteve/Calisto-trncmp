// ====================================================================== BEGIN FILE =====
// **                                 C T E S T _ R K 4                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  Test RK4 Abstract Class.
 *  @file   ctest_rk4.hh
 *  @author Stephen W. Soliday
 *  @date   2009-Dec-21 Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for precision time keeping.
 */
// =======================================================================================


#include <RK4.hh>
#include <StopWatch.hh>


#define C     ((real8_t) 2.99792458e+8)   ///< Speed of light.
#define ITER  ((size_t)  10000)           ///< Number of Plot Iterations.
#define ISTEP ((size_t)  6000)            ///< Number of Integration Steps per Plot.
#define MAXT  ((real8_t) 36500.0)         ///< Time in days of plot.


// =======================================================================================
class Motion : public RK4 {
  // -------------------------------------------------------------------------------------
 public:
  bool done;

  Motion( void ) :  RK4(2), done(false) {};
  virtual ~Motion( void ) { };

  virtual void difeq ( real8_t* Qd, real8_t* Q, real8_t t, real8_t* P );
  virtual int  check (              real8_t* Q, real8_t t, real8_t* P );
}; // end class Motion


// =======================================================================================
/** @brief Check State.
 *  @param[in] Q current state vector.
 *  @return 0=continue, non-zero=stop
 */
// ---------------------------------------------------------------------------------------
int Motion::check( real8_t* Q, real8_t, real8_t* ) {
  // -------------------------------------------------------------------------------------
  if (Q[0] < C) { return 0; }

  done = true;

  return 1;
}
  
// =======================================================================================
/** @brief Differential equations.
 *  @param[out] Qd first time derivative of the current state vector.
 *  @param[in]  Q  current state vector.
 *  @param[in]  t  current time.
 *  @param[in]  P  parameter vector.
 */
// ---------------------------------------------------------------------------------------
void Motion::difeq( real8_t* Qd, real8_t* Q, real8_t, real8_t* P ) {
  // -------------------------------------------------------------------------------------
  if (!done) {
    const real8_t v = Q[0];
    //    real8_t x = Q[1];

    const real8_t F = P[0];
    const real8_t m = P[1];

    const real8_t v2 = v*v;
    const real8_t c2 = C*C;
    const real8_t c3 = C*C*C;

    const real8_t temp = c2 - v2;

    Qd[0] = (F*Power(temp,2.5)) / (c3*m*(c2+2.0e0*v2));
    Qd[1] = v;

    P[2] = Qd[0];
    P[3] = sqrt(1.0 - v2/c2);
  }
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  size_t i;
  real8_t param[8];
  real8_t state[2];
  real8_t t  = 0.0;
  real8_t tt = 0.0;
  real8_t dt = (MAXT * 86400.0) / ((real8_t) ITER);
  real8_t b;

  param[0] = 98100.0;
  param[1] = 10000.0;

  state[0] = 0.0e0;
  state[1] = 0.0e0;

  Motion* model = new Motion();

  StopWatch watch;

  watch.reset();
    
  for (i=0; i<ITER; i++) {

    t = model->integrate ( state,  t, t+dt, ISTEP, param );

    b = state[0]/C;

    tt += dt*sqrt(1.0-b*b);

    fprintf( stdout,
     	     "%12.4e%12.4e%12.4e%12.4e%12.4e%12.4e%12.4e%12.4e%12.4e\n",
     	     t,tt,b,state[0],state[1],param[0],param[1],param[2],param[3] );

    // fprintf( stdout,
    // 	     "%9.3f, %9.3f, %8.5f, %8.5f, %8.5f, %10.3e\n",
    // 	     t/86400.0, tt/86400.0,
    // 	     (tt/t),
    // 	     param[2] / 9.81,
    // 	     b,
    // 	     state[1] );
 
    if (state[1] > 1.9867533e16) { break; }

    if (model->done) { break; }
  }

  real8_t et = watch.check();

  fprintf( stdout,
           "%9.3f, %9.3f, %8.5f, %8.5f, %8.5f, %10.3e\n",
           t/86400.0, tt/86400.0,
           (tt/t),
           param[2] / 9.81,
           b,
           state[1] );

  std::cout << "Run time = " << et << " seconds" << std::endl << std::endl; 


  delete model;

  return 0;
}

// ==========================================================================================
// **                                 C T E S T _ R K 4                                 **
// =========================================================================== END FILE =====
