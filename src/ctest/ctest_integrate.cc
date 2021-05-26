// ====================================================================== BEGIN FILE =====
// **                          C T E S T _ I N T E G R A T E                           **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2020, Stephen W. Soliday                                           **
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
/** @brief  Test Multiple Integrators.
 *  @file   ctest_integrate.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Dec-25
 *
 *  Provides the interface for testing integrators.
 */
// =======================================================================================


#include <RK4.hh>
#include <StopWatch.hh>
#include <PSGraph.hh>


#define ITER  ((size_t)  28800)      ///< Number of Plot Iterations.
#define ISTEP ((size_t)  100)       ///< Number of Integration Steps per Plot.
#define MAXT  ((real8_t) 1728000.0)   ///< Time in seconds of plot.


// =======================================================================================
class AbstractIntegrator {
  // -------------------------------------------------------------------------------------
 protected:
  int32_t  dim;  ///< number of coupled first order equations.

 public:
  bool done;

  AbstractIntegrator  ( int32_t n ) : dim(n), done(false) {};
  virtual ~AbstractIntegrator ( void ) {};
  
  virtual real8_t integrate  ( real8_t *Q, real8_t t0, real8_t t1, int32_t step, real8_t *P ) = 0;
  virtual int  check( real8_t* Q, real8_t t, real8_t* P ) = 0;
  virtual void difeq( real8_t* Qd, real8_t* Q, real8_t t, real8_t* P ) = 0;
};


// =======================================================================================
class MidPointIntegrator : public AbstractIntegrator {
  // -------------------------------------------------------------------------------------
 protected:
  real8_t *A; ///< workspace
  real8_t *B; ///< workspace
  real8_t *W; ///< workspace
  
 public:
  MidPointIntegrator  ( int32_t n );
  virtual ~MidPointIntegrator ( void );

  virtual real8_t integrate  ( real8_t *Q, real8_t t0, real8_t t1, int32_t step, real8_t *P );
  virtual int  check( real8_t* Q, real8_t t, real8_t* P ) = 0;
  virtual void difeq( real8_t* Qd, real8_t* Q, real8_t t, real8_t* P ) = 0;
};


// =======================================================================================
// ---------------------------------------------------------------------------------------
MidPointIntegrator::MidPointIntegrator  ( int32_t n ) : AbstractIntegrator( n ) {
  // -------------------------------------------------------------------------------------
  A = new real8_t[n];
  B = new real8_t[n];
  W = new real8_t[n];
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
MidPointIntegrator::~MidPointIntegrator( void ) {
  // -------------------------------------------------------------------------------------
  delete[] A;
  delete[] B;
  delete[] W;
}


// =======================================================================================
/** @brief Numerical integration step.
 *  @param[in,out] Q    real vector containing the state.
 *  @param[in]     t0   initial time.
 *  @param[in]     t1   final time.
 *  @param[in]     step number of steps between current time t0 and final time t1.
 *  @param[in]     P    vector containing fixed parameters.
 *  @return new time (t1).
 *
 *  Provides the implementation for a numerical integrator with uniform step sizes.
 */
// ---------------------------------------------------------------------------------------
real8_t MidPointIntegrator::integrate( real8_t* Q, real8_t t0, real8_t t1,
                                     int32_t step, real8_t* P ) {
  // -------------------------------------------------------------------------------------
  const real8_t h  = (t1 - t0) / ((real8_t) step);
  const real8_t h2 = D_HALF * h;

  real8_t t = t0;
  for ( int32_t k=0; k<step; k++ ) {

    if (0 != check( Q, t, P )) { return t; }

    for ( int32_t j=0; j<dim; j++) { W[j] = Q[j];               } difeq(A, W, t,    P);
    for ( int32_t j=0; j<dim; j++) { W[j] = Q[j] + (A[j] * h2); } difeq(B, W, t+h2, P);
    
    for ( int32_t j=0; j<dim; j++) {
      Q[j] += h*B[j];
    }
    t += h;
  }

  return t;
}













// =======================================================================================
class Motion1 : public MidPointIntegrator {
  // -------------------------------------------------------------------------------------
 public:
  bool done;

  Motion1( void ) :  MidPointIntegrator(4), done(false) {};
  virtual ~Motion1( void ) { };

  virtual int  check (              real8_t* Q, real8_t t, real8_t* P );
  virtual void difeq ( real8_t* Qd, real8_t* Q, real8_t t, real8_t* P );
}; // end class Motion1


// =======================================================================================
/** @brief Check State.
 *  @param[in] Q current state vector.
 *  @return 0=continue, non-zero=stop
 */
// ---------------------------------------------------------------------------------------
int Motion1::check( real8_t* Q, real8_t, real8_t* P ) {
  // -------------------------------------------------------------------------------------
  const real8_t x   = Q[2];
  const real8_t y   = Q[3];
  const real8_t rad = P[1];              ///< eqrth radius

  if (((x*x) + (y*y)) > (rad*rad)) { return 0; }

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
void Motion1::difeq( real8_t* Qd, real8_t* Q, real8_t, real8_t* P ) {
  // -------------------------------------------------------------------------------------
  if (!done) {
    const real8_t vx = Q[0];
    const real8_t vy = Q[1];
    const real8_t x  = Q[2];
    const real8_t y  = Q[3];

    const real8_t r3_2 = exp( 1.5e0 * log( (x*x) + (y*y) ) );

    const real8_t mu = P[0];

    Qd[0] = -mu*x/r3_2;   ///< dVx/dt
    Qd[1] = -mu*y/r3_2;   ///< dVx/dt
    Qd[2] = vx;           ///< dX/dt
    Qd[3] = vy;           ///< dY/dt
    }
}














// =======================================================================================
class Motion : public RK4 {
  // -------------------------------------------------------------------------------------
 public:
  bool done;

  Motion( void ) :  RK4(4), done(false) {};
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
int Motion::check( real8_t* Q, real8_t, real8_t* P ) {
  // -------------------------------------------------------------------------------------
  const real8_t x   = Q[2];
  const real8_t y   = Q[3];
  const real8_t rad = P[1];              ///< eqrth radius

  if (((x*x) + (y*y)) > (rad*rad)) { return 0; }

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
    const real8_t vx = Q[0];
    const real8_t vy = Q[1];
    const real8_t x  = Q[2];
    const real8_t y  = Q[3];

    const real8_t r3_2 = exp( 1.5e0 * log( (x*x) + (y*y) ) );

    const real8_t mu = P[0];

    Qd[0] = -mu*x/r3_2;   ///< dVx/dt
    Qd[1] = -mu*y/r3_2;   ///< dVx/dt
    Qd[2] = vx;           ///< dX/dt
    Qd[3] = vy;           ///< dY/dt
    }
}

// =======================================================================================
inline real8_t euclid( real8_t x, real8_t y ) {
  return sqrt( x*x + y*y );
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
void drawPlanet( PSGraph::Draw* pd, real8_t radius ) {
  // -------------------------------------------------------------------------------------
  pd->saveColor();
  pd->setRGB( PSGraph::Color::blue );

  size_t  n = 200;
  real8_t dt = D_2PI / (real8_t)(n-1);

  real8_t t = D_ZERO;

  real8_t lastX = radius * cos( t );
  real8_t lastY = radius * sin( t );
  
  for ( size_t i=0; i<n; i++ ) {
    t += dt;
    real8_t X = radius * cos( t );
    real8_t Y = radius * sin( t );

    pd->drawLine( X, Y, lastX, lastY );

    lastX = X;
    lastY = Y;
  }

  pd->restoreColor();
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
int main( void ) {
  // -------------------------------------------------------------------------------------
  size_t i;
  real8_t param[2];
  real8_t state[4];
  real8_t t  = 0.0;
  real8_t dt = MAXT / ((real8_t) ITER);
  real8_t b;

  const real8_t GMe = 3.986004418e14;       ///< Geocentric gravitational constant (m^3/s^2)
  const real8_t Re  = 6378136.6;            ///< Earth equitorial radius (meters)
  const real8_t MX  = Re*2.0;               ///< Max boundary for plot
  

  param[0] = GMe;
  param[1] = Re;


  state[0] = 0.0e0;        ///< Vx    meters / second
  state[1] = 7.5e3;        ///< Vy    meters / second
  state[2] = 8.0e6;        ///< X     meters
  state[3] = 0.0e0;        ///< Y     meters

  real8_t lastX = state[2];
  real8_t lastY = state[3];

  // -------------------------------------------------------------------------------------
  PSGraph*       ps = new PSGraph(1);
  PSGraph::Draw* pd = new PSGraph::Draw( 7.5, 7.5, -MX, -MX, MX, MX );

  pd->drawBorder();

  drawPlanet( pd, Re );

  AbstractIntegrator*  model = new Motion1();

  StopWatch watch;

  watch.reset();
    
  for (i=0; i<ITER; i++) {

    t = model->integrate ( state,  t, t+dt, ISTEP, param );

    real8_t v = euclid( state[0], state[1] );
    real8_t r = euclid( state[2], state[3] );

    //fprintf( stdout,
    // 	     "%.2f %.3f %.3f %.3f %.3f\n",
    // 	     t, state[0], state[1], state[2], state[3]);

    pd->drawLine( state[2], state[3], lastX, lastY );
    lastX = state[2];
    lastY = state[3];
 
    if (model->done) { break; }
  }

  real8_t et = watch.check();

  std::cerr << "Run time = " << et << " seconds\n\n"; 

  delete model;

  ps->add( pd, 0, 1.75, 0.5 );

  ps->pswrite( "orbit.ps" );
  
  delete ps;

  delete pd;

  return 0;
}

// ==========================================================================================
// **                           C T E S T _ I N T E G R A T E                           **
// =========================================================================== END FILE =====
