// ====================================================================== BEGIN FILE =====
// **                                C T E S T _ B P N N                                **
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
/** @brief  Test LAPACK/BLAS ROUTINES
 *  @file   ctest_bpn.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-29 CMake refactorization.
 *
 *  Provides the test of BLAS interface.
 */
// =======================================================================================

#include <Dice.hh>
#include <StopWatch.hh>
#include <LinAlg.hh>
#include <FileTool.hh>
#include <BPNN.hh>
#include <Exemplar.hh>

static u_int32_t SEED_MATTER[] = { 0x29341EA3, 0x9257677C, 0xCC98B1D1, 0x7C5EB68C,
                                   0x13ED5BC5, 0x3C91F88F, 0xE1A42570, 0x24CA88CD,
                                   0xAE36E97A, 0x59BADCBB, 0x4B9ED120, 0x952318E6,
                                   0xDD62B887, 0xCFC13ED9, 0x0F6A241B, 0x43970DA6,
                                   0xDF52E725, 0x4F6FE0ED, 0xCF9D4A7B, 0xA8742AE2,
                                   0x3B0590CF, 0xE20ACC41, 0x10A25D9B, 0xD59349FF,
                                   0x10BEE39E, 0x33CE2526, 0xD8029C5B, 0xFC6D3D65,
                                   0xD08E3996, 0x6FCFC48D, 0x2FD4F96B, 0x1AAEC36F };



real8_t raw_test[] =  {
  5.9, 3.0, 4.2, 1.5,  0.1, 0.9, 0.1,
  6.9, 3.1, 5.4, 2.1,  0.1, 0.1, 0.9,
  5.1, 3.3, 1.7, 0.5,  0.9, 0.1, 0.1,
  6.0, 3.4, 4.5, 1.6,  0.1, 0.9, 0.1,
  5.5, 2.5, 4.0, 1.3,  0.1, 0.9, 0.1,
  6.2, 2.9, 4.3, 1.3,  0.1, 0.9, 0.1,
  5.5, 4.2, 1.4, 0.2,  0.9, 0.1, 0.1,
  6.3, 2.8, 5.1, 1.5,  0.1, 0.1, 0.9,
  5.6, 3.0, 4.1, 1.3,  0.1, 0.9, 0.1,
  6.7, 2.5, 5.8, 1.8,  0.1, 0.1, 0.9,
  7.1, 3.0, 5.9, 2.1,  0.1, 0.1, 0.9,
  4.3, 3.0, 1.1, 0.1,  0.9, 0.1, 0.1,
  5.6, 2.8, 4.9, 2.0,  0.1, 0.1, 0.9,
  5.5, 2.3, 4.0, 1.3,  0.1, 0.9, 0.1,
  6.0, 2.2, 4.0, 1.0,  0.1, 0.9, 0.1,
  5.1, 3.5, 1.4, 0.2,  0.9, 0.1, 0.1,
  5.7, 2.6, 3.5, 1.0,  0.1, 0.9, 0.1,
  4.8, 3.4, 1.9, 0.2,  0.9, 0.1, 0.1,
  5.1, 3.4, 1.5, 0.2,  0.9, 0.1, 0.1,
  5.7, 2.5, 5.0, 2.0,  0.1, 0.1, 0.9,
  5.4, 3.4, 1.7, 0.2,  0.9, 0.1, 0.1,
  5.6, 3.0, 4.5, 1.5,  0.1, 0.9, 0.1,
  6.3, 2.9, 5.6, 1.8,  0.1, 0.1, 0.9,
  6.3, 2.5, 4.9, 1.5,  0.1, 0.9, 0.1,
  5.8, 2.7, 3.9, 1.2,  0.1, 0.9, 0.1,
  6.1, 3.0, 4.6, 1.4,  0.1, 0.9, 0.1,
  5.2, 4.1, 1.5, 0.1,  0.9, 0.1, 0.1,
  6.7, 3.1, 4.7, 1.5,  0.1, 0.9, 0.1,
  6.7, 3.3, 5.7, 2.5,  0.1, 0.1, 0.9,
  6.4, 2.9, 4.3, 1.3,  0.0, 1.0, 0.0 };

int32_t n_test = (int32_t)(sizeof(raw_test) / sizeof(raw_test[0]) / 7);
  
real8_t raw_train[] = {
  6.4, 2.8, 5.6, 2.2,  0.1, 0.1, 0.9,
  5.0, 2.3, 3.3, 1.0,  0.1, 0.9, 0.1,
  4.9, 2.5, 4.5, 1.7,  0.1, 0.1, 0.9,
  4.9, 3.1, 1.5, 0.1,  0.9, 0.1, 0.1,
  5.7, 3.8, 1.7, 0.3,  0.9, 0.1, 0.1,
  4.4, 3.2, 1.3, 0.2,  0.9, 0.1, 0.1,
  5.4, 3.4, 1.5, 0.4,  0.9, 0.1, 0.1,
  6.9, 3.1, 5.1, 2.3,  0.1, 0.1, 0.9,
  6.7, 3.1, 4.4, 1.4,  0.1, 0.9, 0.1,
  5.1, 3.7, 1.5, 0.4,  0.9, 0.1, 0.1,
  5.2, 2.7, 3.9, 1.4,  0.1, 0.9, 0.1,
  6.9, 3.1, 4.9, 1.5,  0.1, 0.9, 0.1,
  5.8, 4.0, 1.2, 0.2,  0.9, 0.1, 0.1,
  5.4, 3.9, 1.7, 0.4,  0.9, 0.1, 0.1,
  7.7, 3.8, 6.7, 2.2,  0.1, 0.1, 0.9,
  6.3, 3.3, 4.7, 1.6,  0.1, 0.9, 0.1,
  6.8, 3.2, 5.9, 2.3,  0.1, 0.1, 0.9,
  7.6, 3.0, 6.6, 2.1,  0.1, 0.1, 0.9,
  6.4, 3.2, 5.3, 2.3,  0.1, 0.1, 0.9,
  5.7, 4.4, 1.5, 0.4,  0.9, 0.1, 0.1,
  6.7, 3.3, 5.7, 2.1,  0.1, 0.1, 0.9,
  6.4, 2.8, 5.6, 2.1,  0.1, 0.1, 0.9,
  5.4, 3.9, 1.3, 0.4,  0.9, 0.1, 0.1,
  6.1, 2.6, 5.6, 1.4,  0.1, 0.1, 0.9,
  7.2, 3.0, 5.8, 1.6,  0.1, 0.1, 0.9,
  5.2, 3.5, 1.5, 0.2,  0.9, 0.1, 0.1,
  5.8, 2.6, 4.0, 1.2,  0.1, 0.9, 0.1,
  5.9, 3.0, 5.1, 1.8,  0.1, 0.1, 0.9,
  5.4, 3.0, 4.5, 1.5,  0.1, 0.9, 0.1,
  6.7, 3.0, 5.0, 1.7,  0.1, 0.9, 0.1,
  6.3, 2.3, 4.4, 1.3,  0.1, 0.9, 0.1,
  5.1, 2.5, 3.0, 1.1,  0.1, 0.9, 0.1,
  6.4, 3.2, 4.5, 1.5,  0.1, 0.9, 0.1,
  6.8, 3.0, 5.5, 2.1,  0.1, 0.1, 0.9,
  6.2, 2.8, 4.8, 1.8,  0.1, 0.1, 0.9,
  6.9, 3.2, 5.7, 2.3,  0.1, 0.1, 0.9,
  6.5, 3.2, 5.1, 2.0,  0.1, 0.1, 0.9,
  5.8, 2.8, 5.1, 2.4,  0.1, 0.1, 0.9,
  5.1, 3.8, 1.5, 0.3,  0.9, 0.1, 0.1,
  4.8, 3.0, 1.4, 0.3,  0.9, 0.1, 0.1,
  7.9, 3.8, 6.4, 2.0,  0.1, 0.1, 0.9,
  5.8, 2.7, 5.1, 1.9,  0.1, 0.1, 0.9,
  6.7, 3.0, 5.2, 2.3,  0.1, 0.1, 0.9,
  5.1, 3.8, 1.9, 0.4,  0.9, 0.1, 0.1,
  4.7, 3.2, 1.6, 0.2,  0.9, 0.1, 0.1,
  6.0, 2.2, 5.0, 1.5,  0.1, 0.1, 0.9,
  4.8, 3.4, 1.6, 0.2,  0.9, 0.1, 0.1,
  7.7, 2.6, 6.9, 2.3,  0.1, 0.1, 0.9,
  4.6, 3.6, 1.0, 0.2,  0.9, 0.1, 0.1,
  7.2, 3.2, 6.0, 1.8,  0.1, 0.1, 0.9,
  5.0, 3.3, 1.4, 0.2,  0.9, 0.1, 0.1,
  6.6, 3.0, 4.4, 1.4,  0.1, 0.9, 0.1,
  6.1, 2.8, 4.0, 1.3,  0.1, 0.9, 0.1,
  5.0, 3.2, 1.2, 0.2,  0.9, 0.1, 0.1,
  7.0, 3.2, 4.7, 1.4,  0.1, 0.9, 0.1,
  6.0, 3.0, 4.8, 1.8,  0.1, 0.1, 0.9,
  7.4, 2.8, 6.1, 1.9,  0.1, 0.1, 0.9,
  5.8, 2.7, 5.1, 1.9,  0.1, 0.1, 0.9,
  6.2, 3.4, 5.4, 2.3,  0.1, 0.1, 0.9,
  5.0, 2.0, 3.5, 1.0,  0.1, 0.9, 0.1,
  5.6, 2.5, 3.9, 1.1,  0.1, 0.9, 0.1,
  6.7, 3.1, 5.6, 2.4,  0.1, 0.1, 0.9,
  6.3, 2.5, 5.0, 1.9,  0.1, 0.1, 0.9,
  6.4, 3.1, 5.5, 1.8,  0.1, 0.1, 0.9,
  6.2, 2.2, 4.5, 1.5,  0.1, 0.9, 0.1,
  7.3, 2.9, 6.3, 1.8,  0.1, 0.1, 0.9,
  4.4, 3.0, 1.3, 0.2,  0.9, 0.1, 0.1,
  7.2, 3.6, 6.1, 2.5,  0.1, 0.1, 0.9,
  6.5, 3.0, 5.5, 1.8,  0.1, 0.1, 0.9,
  5.0, 3.4, 1.5, 0.2,  0.9, 0.1, 0.1,
  4.7, 3.2, 1.3, 0.2,  0.9, 0.1, 0.1,
  6.6, 2.9, 4.6, 1.3,  0.1, 0.9, 0.1,
  5.5, 3.5, 1.3, 0.2,  0.9, 0.1, 0.1,
  7.7, 3.0, 6.1, 2.3,  0.1, 0.1, 0.9,
  6.1, 3.0, 4.9, 1.8,  0.1, 0.1, 0.9,
  4.9, 3.1, 1.5, 0.1,  0.9, 0.1, 0.1,
  5.5, 2.4, 3.8, 1.1,  0.1, 0.9, 0.1,
  5.7, 2.9, 4.2, 1.3,  0.1, 0.9, 0.1,
  6.0, 2.9, 4.5, 1.5,  0.1, 0.9, 0.1,
  6.4, 2.7, 5.3, 1.9,  0.1, 0.1, 0.9,
  5.4, 3.7, 1.5, 0.2,  0.9, 0.1, 0.1,
  6.1, 2.9, 4.7, 1.4,  0.1, 0.9, 0.1,
  6.5, 2.8, 4.6, 1.5,  0.1, 0.9, 0.1,
  5.6, 2.7, 4.2, 1.3,  0.1, 0.9, 0.1,
  6.3, 3.4, 5.6, 2.4,  0.1, 0.1, 0.9,
  4.9, 3.1, 1.5, 0.1,  0.9, 0.1, 0.1,
  6.8, 2.8, 4.8, 1.4,  0.1, 0.9, 0.1,
  5.7, 2.8, 4.5, 1.3,  0.1, 0.9, 0.1,
  6.0, 2.7, 5.1, 1.6,  0.1, 0.9, 0.1,
  5.0, 3.5, 1.3, 0.3,  0.9, 0.1, 0.1,
  6.5, 3.0, 5.2, 2.0,  0.1, 0.1, 0.9,
  6.1, 2.8, 4.7, 1.2,  0.1, 0.9, 0.1,
  5.1, 3.5, 1.4, 0.3,  0.9, 0.1, 0.1,
  4.6, 3.1, 1.5, 0.2,  0.9, 0.1, 0.1,
  6.5, 3.0, 5.8, 2.2,  0.1, 0.1, 0.9,
  4.6, 3.4, 1.4, 0.3,  0.9, 0.1, 0.1,
  4.6, 3.2, 1.4, 0.2,  0.9, 0.1, 0.1,
  7.7, 2.8, 6.7, 2.0,  0.1, 0.1, 0.9,
  5.9, 3.2, 4.8, 1.8,  0.1, 0.9, 0.1,
  5.1, 3.8, 1.6, 0.2,  0.9, 0.1, 0.1,
  4.9, 3.0, 1.4, 0.2,  0.9, 0.1, 0.1,
  4.9, 2.4, 3.3, 1.0,  0.1, 0.9, 0.1,
  4.5, 2.3, 1.3, 0.3,  0.9, 0.1, 0.1,
  5.8, 2.7, 4.1, 1.0,  0.1, 0.9, 0.1,
  5.0, 3.4, 1.6, 0.4,  0.9, 0.1, 0.1,
  5.2, 3.4, 1.4, 0.2,  0.9, 0.1, 0.1,
  5.3, 3.7, 1.5, 0.2,  0.9, 0.1, 0.1,
  5.0, 3.6, 1.4, 0.2,  0.9, 0.1, 0.1,
  5.6, 2.9, 3.6, 1.3,  0.1, 0.9, 0.1,
  4.8, 3.1, 1.6, 0.2,  0.9, 0.1, 0.1,
  6.3, 2.7, 4.9, 1.8,  0.1, 0.1, 0.9,
  5.7, 2.8, 4.1, 1.3,  0.1, 0.9, 0.1,
  5.0, 3.0, 1.6, 0.2,  0.9, 0.1, 0.1,
  6.3, 3.3, 6.0, 2.5,  0.1, 0.1, 0.9,
  5.0, 3.5, 1.6, 0.6,  0.9, 0.1, 0.1,
  5.5, 2.6, 4.4, 1.2,  0.1, 0.9, 0.1,
  5.7, 3.0, 4.2, 1.2,  0.1, 0.9, 0.1,
  4.4, 2.9, 1.4, 0.2,  0.9, 0.1, 0.1,
  4.8, 3.0, 1.4, 0.1,  0.9, 0.1, 0.1,
  5.5, 2.4, 3.7, 1.0,  0.0, 1.0, 0.0 };

int32_t n_train = (int32_t)(sizeof(raw_train) / sizeof(raw_train[0]) / 7);




// =======================================================================================
void BuildTable( Table& X, Table& Y, real8_t data[],
                 int32_t ns, int32_t nIn, int32_t nOut ) {
  // -------------------------------------------------------------------------------------
  int32_t idx = 0;
  X.resize( ns, nIn );
  Y.resize( ns, nOut );
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<nIn; c++ ) {
      X.set( r, c, data[idx] ); idx++;
    }
    for ( int32_t c=0; c<nOut; c++ ) {
      Y.set( r, c, data[idx] ); idx++;
    }
  }  
}




// =======================================================================================
void BuildTable( Matrix& X, Matrix& Y, real8_t data[],
                 int32_t ns, int32_t nIn, int32_t nOut ) {
  // -------------------------------------------------------------------------------------
  int32_t idx = 0;
  X.resize( ns, nIn );
  Y.resize( ns, nOut );
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<nIn; c++ ) {
      X.set( r, c, data[idx] ); idx++;
    }
    for ( int32_t c=0; c<nOut; c++ ) {
      Y.set( r, c, data[idx] ); idx++;
    }
  }
}


// =======================================================================================
void BuildTable( Exemplar& E, real8_t data[],
                 int32_t ns, int32_t nIn, int32_t nOut ) {
  // -------------------------------------------------------------------------------------
  int32_t idx = 0;
  E.resize( ns, nIn, nOut );
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<nIn; c++ ) {
      E.setIn( r, c, data[idx] ); idx++;
    }
    for ( int32_t c=0; c<nOut; c++ ) {
      E.setOut( r, c, data[idx] ); idx++;
    }
  }
}


// =======================================================================================
void randomWeight( Matrix& W, int32_t nr, int32_t nc, Dice* dd ) {
  // -------------------------------------------------------------------------------------
  W.resize(nr,nc);
  real8_t scl = D_ONE / (real8_t) nc;
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      W.set( r, c, dd->normal() * scl );
    }
  }
}


// =======================================================================================
void randomBias( Vector& b, int32_t n, Dice* dd ) {
  // -------------------------------------------------------------------------------------
  b.resize(n);
  real8_t scl = D_ONE / (real8_t) n;
  for ( int32_t i=0; i<n; i++ ) {
    b.set( i, dd->normal() * scl );
  }
}

inline real8_t ACT    ( const real8_t x ) { return D_ONE / (D_ONE + exp(-x)); }
inline real8_t INVACT ( const real8_t a ) { return a*(D_ONE - a); }


// =======================================================================================
void activate( Matrix& a, Matrix& z ) {
  // -------------------------------------------------------------------------------------
  const int32_t nr = size( a, 0 );
  const int32_t nc = size( a, 1 );
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      a.set( r, c, ACT( z.get( r, c ) ) );
    }
  }
}

// =======================================================================================
void activate( Vector& a, Vector& z ) {
  // -------------------------------------------------------------------------------------
  const int32_t n = size( a );
  for ( int32_t i=0; i<n; i++ ) {
    a.set( i, ACT( z.get( i ) ) );
  }
}

// =======================================================================================
void add( Matrix& z, Vector& b ) {
  // -------------------------------------------------------------------------------------
  const int32_t nr = size( z, 0 );
  const int32_t nc = size( z, 1 );
  if ( nc != size( b ) ) {
    throw new std::length_error( "Add Bias: number of col do not match" );
  }
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      z.set( r, c, z.get( r, c ) + b.get( c ) );
    }
  }
}

// =======================================================================================
void forward( Matrix& a, Matrix& z, Matrix& W, Vector& b, Matrix& x ) {
  // -------------------------------------------------------------------------------------
  z.dot( x, W );
  add( z, b );
  activate( a, z );
}

// =======================================================================================
void forward( Vector& a, Vector& z, Matrix& W, Vector& b, Vector& x ) {
  // -------------------------------------------------------------------------------------
  dot( z, x, W );
  z.add( b );
  activate( a, z );
}


// =======================================================================================
void backward( Matrix& dW, Vector& db, Vector& dm,
               Matrix&  W, Vector& d,  Vector& a, Vector& am, Vector& E ) {
  // -------------------------------------------------------------------------------------
  int32_t n = size( E );
  for ( int32_t i=0; i<n; i++ ) {
    E.set( i, d.get( i ) * INVACT( a.get( i ) ) );
  }

  dot(dm,W,E);
  outer( dW, am, E );
  db.copy(E);
}



// =======================================================================================
void forward4( Vector& a, Vector& z, Matrix& W, Vector& b, Vector& x ) {
  // -------------------------------------------------------------------------------------
  const int32_t n     = size( a );
  const char*   TRANS = "TRANS";
  const real8_t ONE   = D_ONE;

  dcopy_( &n, b.X(), b.INCX(), z.X(), z.INCX() );

  dgemv_( TRANS, W.M(), W.N(),
          &ONE, W.A(), W.LDA(),
          x.X(), x.INCX(),
          &ONE, z.X(), z.INCX() );

  for ( int32_t i=0; i<n; i++ ) {
    a.set( i, ACT( z.get( i ) ) );
  }
}

// =======================================================================================
void backward4( Matrix& dW, Vector& db, Vector& dm,
                Matrix&  W, Vector& d,  Vector& a, Vector& am, Vector& E ) {
  // -------------------------------------------------------------------------------------
  int32_t n = size( E );
  for ( int32_t i=0; i<n; i++ ) {
    E.set( i, d.get( i ) * INVACT( a.get( i ) ) );
  }

  const char*   NOTRA = "NONE";
  //const char*   TRANS = "TRANS";
  const int32_t IONE  = 1;
  const real8_t ONE   = D_ONE;
  const real8_t ZERO  = D_ZERO;

  //dot(dm,W,E);
  dgemv_( NOTRA, W.M(), W.N(),
          &ONE, W.A(), W.LDA(),
          E.X(), E.INCX(),
          &ZERO, dm.X(), dm.INCX() );

  //outer( dW, am, E );
  dgemm_( NOTRA, NOTRA, dW.M(), dW.N(), &IONE,
          &ONE, am.X(), am.N(),
          E.X(), &IONE, &ZERO,
          dW.A(), dW.LDA() );

  //db.copy(E);
  dcopy_( &n, E.X(), E.INCX(), db.X(), db.INCX() );
}
















// =======================================================================================
void backward( Matrix& dW, Vector& db, Matrix& dm,
               Matrix&  W, Matrix& d,  Matrix& a, Matrix& am, Matrix& E ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = size( E, 0 );
  int32_t nc = size( E, 1 );
  for ( int32_t c=0; c<nc; c++ ) {
    for ( int32_t r=0; r<nr; r++ ) {
      E.set( r, c, d.get( r, c ) * INVACT( a.get( r, c ) ) );
    }
  }

  dm.dot(E,false,W,true);
  dW.dot( am, true, E, false );

  for ( int32_t c=0; c<nc; c++ ) {
    db.set( c, D_ZERO );
    for ( int32_t r=0; r<nr; r++ ) {
      db.set( c, db.get( c ) + E.get( r, c ) );
    }
  }
}


// =======================================================================================
void forwardXXX( Matrix& a, Matrix& z, Matrix& W, Vector& b, Matrix& x ) {
  // -------------------------------------------------------------------------------------
  const int32_t ni = size( W, 0 );
  const int32_t no = size( W, 1 );
  const int32_t ns = size( x, 0 );

  if ( no != size( b ) ) {
    throw new std::length_error( "NN Fwd: bias wrong length" );
  }
  
  if ( ni != size( x, 1 ) ) {
    throw new std::length_error( "NN Fwd: input wrong length" );
  }
  
  if ( no != size( z, 1 ) ) {
    throw new std::length_error( "NN Fwd: Z wrong width" );
  }
  
  if ( no != size( a, 1 ) ) {
    throw new std::length_error( "NN Fwd: A wrong width" );
  }
  
  if ( ns != size( z, 0 ) ) {
    throw new std::length_error( "NN Fwd: Z wrong length" );
  }
  
  if ( ns != size( a, 0 ) ) {
    throw new std::length_error( "NN Fwd: A wrong length" );
  }

  
  for ( int32_t r=0; r<ns; r++ ) {
    for ( int32_t c=0; c<no; c++ ) {
      real8_t sum = b.get(c);
      for ( int32_t k=0; k<ni; k++ ) {
        sum += ( x.get(r,k) * W.get(k,c) );
      }
      z.set( r, c, sum );
      a.set( r, c, ACT(sum) );
    }
  }

}


// =======================================================================================
void display( Matrix& a, Matrix& b ) {
  // -------------------------------------------------------------------------------------
  const int32_t nr = size( a, 0 );
  const int32_t nc = size( a, 1 );
  real8_t mse = D_ZERO;
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      fprintf( stdout, "%7.3f ", a.get(r,c) );
    }
    fprintf( stdout, "  " );
    for ( int32_t c=0; c<nc; c++ ) {
      fprintf( stdout, " %7.3f", b.get(r,c) );
      real8_t d = a.get(r,c) - b.get(r,c);
      mse += (d*d);
    }
    fprintf( stdout, "\n" );
  }
  fprintf( stdout, "\nMSE = %g\n\n", a.sumsq(b) );
}

// =======================================================================================
void load( Vector& v, Table& tab,  int32_t sidx ) {
  // -------------------------------------------------------------------------------------
  const int32_t n = size( v );
  for ( int32_t i=0; i<n; i++ ) {
    v.set( tab.get( sidx, i ) );
  }
}


// =======================================================================================
void load( real8_t*v, const int32_t n, Table& tab,  int32_t sidx ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n; i++ ) {
    v[i] = tab.get( sidx, i );
  }
}



// =======================================================================================
void TEST04( void ) {
  // -------------------------------------------------------------------------------------
  std::cout << "\nVector (BLAS) Implementation\n";
  Dice* dd = Dice::getInstance();
  //dd->seed_set( reinterpret_cast<void*>(SEED_MATTER),  dd->seed_size() );
  dd->seed_set(  );

  Table train_in;
  Table train_out;
  Table test_in;
  Table test_out;

  int32_t nIn  = 4;
  int32_t nH1  = 10;
  int32_t nH2  = 6;
  int32_t nOut = 3;
  
  BuildTable( test_in,  test_out,  raw_test,  n_test,  nIn, nOut );
  BuildTable( train_in, train_out, raw_train, n_train, nIn, nOut );

  Matrix W1;  randomWeight( W1, nIn, nH1,  dd );
  Matrix W2;  randomWeight( W2, nH1, nH2,  dd );
  Matrix W3;  randomWeight( W3, nH2, nOut, dd );

  Vector b1;  randomBias( b1, nH1,  dd );
  Vector b2;  randomBias( b2, nH2,  dd );
  Vector b3;  randomBias( b3, nOut, dd );

  // -------------------------------------------------------------------------------------

  int32_t epochs = 3000;
  real8_t eta    = 0.08;

  real8_t* Train_err = new real8_t[ epochs ];
  real8_t* Test_err  = new real8_t[ epochs ];
  int32_t* Match_err = new int32_t[ epochs ];

  Vector a0( nIn  );
  Vector a1( nH1  );
  Vector a2( nH2  );
  Vector a3( nOut );
  Vector z1( nH1  );
  Vector z2( nH2  );
  Vector z3( nOut );

  Matrix dW1( nIn, nH1  );
  Matrix dW2( nH1, nH2  );
  Matrix dW3( nH2, nOut );

  Matrix tdW1( nIn, nH1  );
  Matrix tdW2( nH1, nH2  );
  Matrix tdW3( nH2, nOut );

  Vector db1( nH1  );
  Vector db2( nH2  );
  Vector db3( nOut );

  Vector tdb1( nH1  );
  Vector tdb2( nH2  );
  Vector tdb3( nOut );

  Vector d0( nIn  );
  Vector d1( nH1  );
  Vector d2( nH2  );
  Vector d3( nOut );
  
  Vector E1( nH1  );
  Vector E2( nH2  );
  Vector E3( nOut );

  Vector T( nOut );
  
  StopWatch SW;
  SW.reset();

  real8_t* train_error = new real8_t[epochs];
  real8_t* test_error  = new real8_t[epochs];
  
  for ( int32_t gen=0; gen<epochs; gen++ ) {

    // ----- forward pass ----------------------------------------------------------------

    tdW1.set();  tdb1.set();
    tdW2.set();  tdb2.set();
    tdW3.set();  tdb3.set();
    
    for ( int32_t i=0; i<n_train; i++ ) {
      //train_in.row( a0.X(), i );
      //train_out.row( T.X(), i );
      load( a0, train_in,  i );
      load( T,  train_out, i );

      forward4( a1, z1, W1, b1, a0 );
      forward4( a2, z2, W2, b2, a1 );
      forward4( a3, z3, W3, b3, a2 );

      d3.sub( a3, T );
      train_error[gen] = d3.sumsq() / (real8_t)n_train;
    
      backward4( tdW3, tdb3, d2, W3, d3, a3, a2, E3 );
      backward4( tdW2, tdb2, d1, W2, d2, a2, a1, E2 );
      backward4( tdW1, tdb1, d0, W1, d1, a1, a0, E1 );

      dW1.add( tdW1 );  db1.add( tdb1 );
      dW2.add( tdW2 );  db2.add( tdb2 );
      dW3.add( tdW3 );  db3.add( tdb3 );
    }


    dW1.mul( eta );  db1.mul( eta );
    dW2.mul( eta );  db2.mul( eta );
    dW3.mul( eta );  db3.mul( eta );
    
    W1.sub( dW1 );   b1.sub( db1 );
    W2.sub( dW2 );   b2.sub( db2 );
    W3.sub( dW3 );   b3.sub( db3 );
  }
  
  std::cout << SW.check() << " seconds\n";

  std::ofstream fp = FileTool::openWrite( "/tmp/mseB.dat" );
  for ( int32_t gen=0; gen<epochs; gen++ ) {
    fp << gen << " " << train_error[gen] << "\n";
  }
  fp.close();
  
  // -------------------------------------------------------------------------------------

  delete[] test_error;
  delete[] train_error;
  delete[] Train_err;
  delete[] Test_err;
  delete[] Match_err;
}



// =======================================================================================
void TEST03( void ) {
  // -------------------------------------------------------------------------------------
  std::cout << "\nVector Implementation\n";
  Dice* dd = Dice::getInstance();
  //dd->seed_set( reinterpret_cast<void*>(SEED_MATTER),  dd->seed_size() );
  dd->seed_set(  );

  Table train_in;
  Table train_out;
  Table test_in;
  Table test_out;

  int32_t nIn  = 4;
  int32_t nH1  = 10;
  int32_t nH2  = 6;
  int32_t nOut = 3;
  
  BuildTable( test_in,  test_out,  raw_test,  n_test,  nIn, nOut );
  BuildTable( train_in, train_out, raw_train, n_train, nIn, nOut );

  Matrix W1;  randomWeight( W1, nIn, nH1,  dd );
  Matrix W2;  randomWeight( W2, nH1, nH2,  dd );
  Matrix W3;  randomWeight( W3, nH2, nOut, dd );

  Vector b1;  randomBias( b1, nH1,  dd );
  Vector b2;  randomBias( b2, nH2,  dd );
  Vector b3;  randomBias( b3, nOut, dd );

  // -------------------------------------------------------------------------------------

  int32_t epochs = 3000;
  real8_t eta    = 0.08;

  real8_t* Train_err = new real8_t[ epochs ];
  real8_t* Test_err  = new real8_t[ epochs ];
  int32_t* Match_err = new int32_t[ epochs ];

  Vector a0( nIn  );
  Vector a1( nH1  );
  Vector a2( nH2  );
  Vector a3( nOut );
  Vector z1( nH1  );
  Vector z2( nH2  );
  Vector z3( nOut );

  Matrix dW1( nIn, nH1  );
  Matrix dW2( nH1, nH2  );
  Matrix dW3( nH2, nOut );

  Matrix tdW1( nIn, nH1  );
  Matrix tdW2( nH1, nH2  );
  Matrix tdW3( nH2, nOut );

  Vector db1( nH1  );
  Vector db2( nH2  );
  Vector db3( nOut );

  Vector tdb1( nH1  );
  Vector tdb2( nH2  );
  Vector tdb3( nOut );

  Vector d0( nIn  );
  Vector d1( nH1  );
  Vector d2( nH2  );
  Vector d3( nOut );
  
  Vector E1( nH1  );
  Vector E2( nH2  );
  Vector E3( nOut );

  Vector T( nOut );
  
  StopWatch SW;
  SW.reset();

  real8_t* train_error = new real8_t[epochs];
  real8_t* test_error  = new real8_t[epochs];
  
  for ( int32_t gen=0; gen<epochs; gen++ ) {

    // ----- forward pass ----------------------------------------------------------------

    tdW1.set();  tdb1.set();
    tdW2.set();  tdb2.set();
    tdW3.set();  tdb3.set();
    
    for ( int32_t i=0; i<n_train; i++ ) {
      //train_in.row( a0.X(), i );
      //train_out.row( T.X(), i );
      load( a0, train_in,  i );
      load( T,  train_out, i );

      forward( a1, z1, W1, b1, a0 );
      forward( a2, z2, W2, b2, a1 );
      forward( a3, z3, W3, b3, a2 );

      d3.sub( a3, T );
      train_error[gen] = d3.sumsq() / (real8_t)n_train;
    
      backward( tdW3, tdb3, d2, W3, d3, a3, a2, E3 );
      backward( tdW2, tdb2, d1, W2, d2, a2, a1, E2 );
      backward( tdW1, tdb1, d0, W1, d1, a1, a0, E1 );

      dW1.add( tdW1 );  db1.add( tdb1 );
      dW2.add( tdW2 );  db2.add( tdb2 );
      dW3.add( tdW3 );  db3.add( tdb3 );
    }


    dW1.mul( eta );  db1.mul( eta );
    dW2.mul( eta );  db2.mul( eta );
    dW3.mul( eta );  db3.mul( eta );
    
    W1.sub( dW1 );   b1.sub( db1 );
    W2.sub( dW2 );   b2.sub( db2 );
    W3.sub( dW3 );   b3.sub( db3 );
  }
  
  std::cout << SW.check() << " seconds\n";

  std::ofstream fp = FileTool::openWrite( "/tmp/mseV.dat" );
  for ( int32_t gen=0; gen<epochs; gen++ ) {
    fp << gen << " " << train_error[gen] << "\n";
  }
  fp.close();
  
  // -------------------------------------------------------------------------------------

  delete[] test_error;
  delete[] train_error;
  delete[] Train_err;
  delete[] Test_err;
  delete[] Match_err;
}



// =======================================================================================
void TEST01( void ) {
  // -------------------------------------------------------------------------------------
  std::cout << "\nMatrix Implementation\n";
  Dice* dd = Dice::getInstance();
  //dd->seed_set( reinterpret_cast<void*>(SEED_MATTER),  dd->seed_size() );
  dd->seed_set(  );

  Matrix train_in;
  Matrix train_out;
  Matrix test_in;
  Matrix test_out;

  int32_t nIn  = 4;
  int32_t nH1  = 10;
  int32_t nH2  = 6;
  int32_t nOut = 3;
  
  BuildTable( test_in,  test_out,  raw_test,  n_test,  nIn, nOut );
  BuildTable( train_in, train_out, raw_train, n_train, nIn, nOut );

  Matrix W1;  randomWeight( W1, nIn, nH1,  dd );
  Matrix W2;  randomWeight( W2, nH1, nH2,  dd );
  Matrix W3;  randomWeight( W3, nH2, nOut, dd );

  Vector b1;  randomBias( b1, nH1,  dd );
  Vector b2;  randomBias( b2, nH2,  dd );
  Vector b3;  randomBias( b3, nOut, dd );

  // -------------------------------------------------------------------------------------

  int32_t epochs = 3000;
  real8_t eta    = 0.08;

  real8_t* Train_err = new real8_t[ epochs ];
  real8_t* Test_err  = new real8_t[ epochs ];
  int32_t* Match_err = new int32_t[ epochs ];

  Matrix a0( n_train, nIn  );
  Matrix a1( n_train, nH1  );
  Matrix a2( n_train, nH2  );
  Matrix a3( n_train, nOut );
  Matrix z1( n_train, nH1  );
  Matrix z2( n_train, nH2  );
  Matrix z3( n_train, nOut );

  Matrix dW1( nIn, nH1  );
  Matrix dW2( nH1, nH2  );
  Matrix dW3( nH2, nOut );

  Vector db1( nH1  );
  Vector db2( nH2  );
  Vector db3( nOut );

  Matrix d0(n_train, nIn);
  Matrix d1(n_train, nH1);
  Matrix d2(n_train, nH2);
  Matrix d3(n_train, nOut);
  
  Matrix E1(n_train, nH1);
  Matrix E2(n_train, nH2);
  Matrix E3(n_train, nOut);
  
  StopWatch SW;
  SW.reset();

  real8_t* train_error = new real8_t[epochs];
  real8_t* test_error  = new real8_t[epochs];
  
  for ( int32_t gen=0; gen<epochs; gen++ ) {

    // ----- forward pass ----------------------------------------------------------------

    a0.copy( train_in );

    forward( a1, z1, W1, b1, a0 );
    forward( a2, z2, W2, b2, a1 );
    forward( a3, z3, W3, b3, a2 );

    d3.sub( a3, train_out );

    train_error[gen] = d3.sumsq() / (real8_t)n_train;
    backward( dW3, db3, d2, W3, d3, a3, a2, E3 );
    backward( dW2, db2, d1, W2, d2, a2, a1, E2 );
    backward( dW1, db1, d0, W1, d1, a1, a0, E1 );

    dW1.mul( eta );  db1.mul( eta );
    dW2.mul( eta );  db2.mul( eta );
    dW3.mul( eta );  db3.mul( eta );

    W1.sub( dW1 );   b1.sub( db1 );
    W2.sub( dW2 );   b2.sub( db2 );
    W3.sub( dW3 );   b3.sub( db3 );

    
  }
  
  std::cout << SW.check() << " seconds\n";

  std::ofstream fp = FileTool::openWrite( "/tmp/mseM.dat" );
  for ( int32_t gen=0; gen<epochs; gen++ ) {
    fp << gen << " " << train_error[gen] << "\n";
  }
  fp.close();
  
  // -------------------------------------------------------------------------------------

  delete[] test_error;
  delete[] train_error;
  delete[] Train_err;
  delete[] Test_err;
  delete[] Match_err;
}


// =======================================================================================
void TEST02( void ) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { -4.94, -8.78, -5.01, -7.47, -4.94,
                     -1.95, -6.63,  6.79,  7.02, -3.88,
                     -2.48, -2.19,  0.19, -4.04, -8.69 };

  real8_t bdat[] = {  0.63, -0.68,  7.66,  9.59,
                      -6.12,  3.00, -3.47, -9.39,
                      4.49, -1.71,  8.24, -7.70,
                      -3.84,  6.75, -0.91,  9.77,
                      5.54, -7.35, -1.11, -9.84 };

  real8_t cdat[] = {   29.4437,  -28.5272,  -36.3751,   49.2743,
                       21.3822,   45.7281,   61.9373,   98.0368,
                       -19.9355,   31.3930,    3.4904,   41.3567 };


  Matrix A = Matrix::row_major(3,5,adat);
  Matrix B = Matrix::row_major(5,4,bdat);
  Matrix C = Matrix::row_major(3,4,cdat);
  Matrix T;
  T.dot(A,B);
  real8_t s = T.sumsq( C );
  std::cout << s << std::endl;
}

// =======================================================================================
void TEST05( void ) {
  // -------------------------------------------------------------------------------------
  BPNN A( 3, 5, 2 );
  BPNN B;

  A.debug();

  A.write( "/tmp/bpnn1.cfg", "%7.2f");
  B.read( "/tmp/bpnn1.cfg" );
  B.write( "/tmp/bpnn2.cfg", "%7.2f" );
}



real8_t oneHot( real8_t* A, real8_t* B, int32_t n ) {
  const size_t sn = (size_t)n;
  size_t ia = MaxLoc( A, sn );
  size_t ib = MaxLoc( B, sn );
  return ( ia == ib ) ? D_ZERO : D_ONE;
}



// =======================================================================================
void TEST06( void ) {
  // -------------------------------------------------------------------------------------
  std::cout << "\nClass Implementation\n";
  Dice* dd = Dice::getInstance();
  //dd->seed_set( reinterpret_cast<void*>(SEED_MATTER),  dd->seed_size() );
  dd->seed_set(  );

  Table train_in;
  Table train_out;
  Table test_in;
  Table test_out;

  int32_t nIn  = 4;
  int32_t nH[] = { 6, 3 };
  int32_t nL   = sizeof(nH) / sizeof(nH[0]);
  int32_t nOut = nH[nL-1];
  
  BuildTable( test_in,  test_out,  raw_test,  n_test,  nIn, nOut );
  BuildTable( train_in, train_out, raw_train, n_train, nIn, nOut );

  BPNN net( nIn, nH, nL );
  net.randomize( dd );
  net.write( "/tmp/iris.net", "%9.6f" );
  
  // -------------------------------------------------------------------------------------

  int32_t epochs = 100000;
  real8_t eta    = 0.05;

  StopWatch SW;
  SW.reset();

  real8_t* train_error = new real8_t[epochs];
  real8_t* test_error  = new real8_t[epochs];

  real8_t* input   = new real8_t[ nIn ];
  real8_t* output  = new real8_t[ nOut ];
  real8_t* testout = new real8_t[ nOut ];

  int32_t n_batch = n_train / 1;
  int32_t* index = new int32_t[ n_train ];
  
  net.reset();
  for ( int32_t gen=0; gen<epochs; gen++ ) {

    dd->random_index( index, n_train );

    real8_t mse = D_ZERO;
    
    for ( int32_t m=0; m<n_batch; m++ ) {
      load( input,   nIn,  train_in,  index[m] );
      load( testout, nOut, train_out, index[m] );

      // ----- forward pass ----------------------------------------------------------------
      mse += net.train( input, output, testout );
      //display( input, nIn, output, nOut, testout, nOut );
    }
      
    train_error[gen] = mse / (real8_t)n_batch;

    net.update(eta);

    
    // ----- test ----------------------------------------------------------------------
    mse = D_ZERO;
    for ( int32_t m=0; m<n_test; m++ ) {
      load( input,   nIn,  test_in,  m );
      load( testout, nOut, test_out, m );

      net.execute( input, output );
      //mse += sumsqDiff( output, testout, nOut );
      mse += oneHot( output, testout, nOut );
    }

    test_error[gen] = mse; // / (real8_t)n_test;
  }
  
  std::cout << SW.check() << " seconds\n";

  std::ofstream fp = FileTool::openWrite( "/tmp/train.dat" );
  for ( int32_t gen=0; gen<epochs; gen++ ) {
    fp << gen << " " << train_error[gen] << "\n";
  }
  fp.close();
  
  fp = FileTool::openWrite( "/tmp/test.dat" );
  for ( int32_t gen=0; gen<epochs; gen++ ) {
    fp << gen << " " << test_error[gen] << "\n";
  }
  fp.close();
  
  // -------------------------------------------------------------------------------------

  delete[] testout;
  delete[] output;
  delete[] input;
  delete[] test_error;
  delete[] train_error;
}

// =======================================================================================
void TEST07( void ) {
  // -------------------------------------------------------------------------------------
  Exemplar E_train, E_test;
  
  int32_t nIn  = 4;
  int32_t nOut = 3;
  
  BuildTable( E_test,  raw_test,  n_test,  nIn, nOut );
  BuildTable( E_train, raw_train, n_train, nIn, nOut );

  E_test.setFormat( "%3.1f" );
  E_train.setFormat( "%3.1f" );
  
  E_test.write(  "iris_test.exm" );
  E_train.write( "iris_train.exm" );
}

// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  //  TEST01();
  //  TEST03();
  //  TEST04();
  //  TEST05();
  TEST06();
  
  return 0;
}

// =======================================================================================
// **                                C T E S T _ B P N N                                **
// ======================================================================== END FILE =====
