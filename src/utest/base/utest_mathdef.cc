// ====================================================================== BEGIN FILE =====
// **                             U T E S T _ M A T H D E F                             **
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
/** @brief  Automated testing for MathDef.
 *  @file   utest_mathdef.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-23
 *
 *  Provides automated testing for auxiliary math definitions.
 */
// =======================================================================================


#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST( swap, Positive ) {
  real8_t A8  = 3.1;
  real8_t B8  = 2.7;
  real4_t A4  = 6.2f;
  real4_t B4  = 5.3f;
  int32_t A32 = 123456L;
  int32_t B32 = 654321L;

  {
    real8_t a = A8;
    real8_t b = B8;
    std::swap( a, b );
    EXPECT_DOUBLE_EQ( a, B8 );
    EXPECT_DOUBLE_EQ( b, A8 );
  }

  {
    real4_t a = A4;
    real4_t b = B4;
    std::swap( a, b );
    EXPECT_FLOAT_EQ( a, B4 );
    EXPECT_FLOAT_EQ( b, A4 );
  }

  {
    int32_t a = A32;
    int32_t b = B32;
    std::swap( a, b );
    EXPECT_EQ( a, B32 );
    EXPECT_EQ( b, A32 );
  }


}










  

// =======================================================================================


TEST( pf_mod8, Positive ) {
  real8_t original[] = { -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0,
                         4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0 };
  real8_t expected[] = {  3.0,  4.0,  0.0,  1.0,  2.0,  3.0,  4.0, 0.0, 1.0, 2.0, 3.0,
                          4.0, 0.0, 1.0, 2.0, 3.0, 4.0,  0.0,  1.0,  2.0,  3.0,  4.0 };

  size_t n = sizeof(original)/sizeof(original[0]);

  const real8_t M = 5.0;

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = PFmod( original[i], M );
    EXPECT_DOUBLE_EQ( expected[i], test );
  }
}


TEST( pf_mod4, Positive ) {
  real4_t original[] = { -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f,
                         3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f,
                         13.0f, 14.0f };
  real4_t expected[] = {  3.0f,  4.0f,  0.0f,  1.0f,  2.0f,  3.0f,  4.0f, 0.0f, 1.0f,
                          2.0f, 3.0f, 4.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f,  0.0f,  1.0f,
                          2.0f,  3.0f,  4.0f };

  size_t n = sizeof(original)/sizeof(original[0]);

  const real4_t M = 5.0f;

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = PFmod( original[i], M );
    EXPECT_FLOAT_EQ( expected[i], test );
  }
}


// =======================================================================================


TEST( linear8, Positive ) {
  real8_t slope =  3.4;
  real8_t inter = -1.1;

  real8_t x1    = -5.3;
  real8_t x2    =  4.2;
  
  real8_t y1    = -19.12;
  real8_t y2    =  13.18;

  EXPECT_DOUBLE_EQ( y1, linear( slope, inter, x1 ) );
  EXPECT_DOUBLE_EQ( y2, linear( slope, inter, x2 ) );

  real8_t m = 0.0;
  real8_t b = 0.0;

  EXPECT_FALSE( linear( &m, &b, x1, y1, x2, y2 ) );
      
  EXPECT_DOUBLE_EQ( slope, m );
  EXPECT_DOUBLE_EQ( inter, b );
}


TEST( linear8, Negative ) {
  real8_t x1    =   2.34;
  real8_t x2    =   2.34;
  
  real8_t y1    = -19.12;
  real8_t y2    =  13.18;

  real8_t m = 10.0;
  real8_t b = 10.0;

  EXPECT_TRUE( linear( &m, &b, x1, y1, x2, y2 ) );
      
  EXPECT_DOUBLE_EQ( MAX_POS_DOUBLE, m );
  EXPECT_DOUBLE_EQ( D_ZERO,         b );
}


// ---------------------------------------------------------------------------------------


TEST( linear4, Positive ) {
  real4_t slope =  3.4f;
  real4_t inter = -1.1f;

  real4_t x1    = -5.3f;
  real4_t x2    =  4.2f;
  
  real4_t y1    = -19.12f;
  real4_t y2    =  13.18f;

  EXPECT_FLOAT_EQ( y1, linear( slope, inter, x1 ) );
  EXPECT_FLOAT_EQ( y2, linear( slope, inter, x2 ) );

  real4_t m = 10.0f;
  real4_t b = 10.0f;

  EXPECT_FALSE( linear( &m, &b, x1, y1, x2, y2 ) );
      
  EXPECT_FLOAT_EQ( slope, m );
  EXPECT_FLOAT_EQ( inter, b );
}


TEST( linear4, Negative ) {
  real4_t x1    =   2.34f;
  real4_t x2    =   2.34f;
  
  real4_t y1    = -19.12f;
  real4_t y2    =  13.18f;

  real4_t m = 10.0f;
  real4_t b = 10.0f;

  EXPECT_TRUE( linear( &m, &b, x1, y1, x2, y2 ) );
      
  EXPECT_FLOAT_EQ( MAX_POS_FLOAT, m );
  EXPECT_FLOAT_EQ( F_ZERO,        b );
}


// =======================================================================================


TEST( LLS8, Positive ) {
  real8_t N[] = { -1.824, 0.799, -0.564, 0.172, -0.890, 1.321, -0.401, 0.310, -1.531 };
  real8_t X[] = { -4.0,  -3.0,   -2.0,  -1.0,    0.0,   1.0,    2.0,   3.0,    4.0 };
  size_t  n   = sizeof(X) / sizeof(X[0]);
  real8_t Y[n];

  real8_t m =  3.2;
  real8_t b = -1.1;

  for ( size_t i=0; i<n; i++ ) {
    Y[i] = (m*X[i] + b) + (N[i] / 1000.0);
  }

  real8_t tm = 0.0;
  real8_t tb = 0.0;

  EXPECT_FALSE( linear( &tm, &tb, X, Y, n ) );
  
  EXPECT_NEAR( m, tm, 0.00002 );
  EXPECT_NEAR( b, tb, 0.0003 );
}


TEST( LLS4, Positive ) {
  real4_t N[] = { -1.824f, 0.799f, -0.564f, 0.172f, -0.890f, 1.321f, -0.401f, 0.310f, -1.531f };
  real4_t X[] = { -4.0f,  -3.0f,   -2.0f,  -1.0f,    0.0f,   1.0f,    2.0f,   3.0f,    4.0f };
  size_t  n   = sizeof(X) / sizeof(X[0]);
  real4_t Y[n];

  real4_t m =  3.2f;
  real4_t b = -1.1f;

  for ( size_t i=0; i<n; i++ ) {
    Y[i] = (m*X[i] + b) + (N[i] / 1000.0f);
  }

  real4_t tm = 0.0f;
  real4_t tb = 0.0f;

  EXPECT_FALSE( linear( &tm, &tb, X, Y, n ) );
  
  EXPECT_NEAR( m, tm, 0.00002f );
  EXPECT_NEAR( b, tb, 0.0003f );
}


// =======================================================================================


TEST( arctan8, Positive ) {
  real8_t X[] = { -1.0, -1.0, -1.0,  0.0, 0.0, 0.0,  1.0, 1.0, 1.0 };
  real8_t Y[] = { -1.0,  0.0,  1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 1.0 };
  real8_t T[] = {  5.0,  4.0,  3.0,  6.0, 0.0, 2.0,  7.0, 0.0, 1.0 };

  size_t n = sizeof(T) / sizeof(T[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = T[i] * D_PI_4;
    real8_t at   = ArcTan( Y[i], X[i] );

    EXPECT_DOUBLE_EQ( test, at );
  }
}


TEST( arctan4, Positive ) {
  real4_t X[] = { -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f };
  real4_t Y[] = { -1.0f,  0.0f,  1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f };
  real4_t T[] = {  5.0f,  4.0f,  3.0f,  6.0f, 0.0f, 2.0f,  7.0f, 0.0f, 1.0f };

  size_t n = sizeof(T) / sizeof(T[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = T[i] * F_PI_4;
    real4_t at   = ArcTan( Y[i], X[i] );

    EXPECT_FLOAT_EQ( test, at );
  }
}


// =======================================================================================


TEST( arctanpm8, Positive ) {
  real8_t X[] = { -1.0, -1.0, -1.0,  0.0, 0.0, 0.0,  1.0, 1.0, 1.0 };
  real8_t Y[] = { -1.0,  0.0,  1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 1.0 };
  real8_t T[] = { -3.0,  4.0,  3.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0 };

  size_t n = sizeof(T) / sizeof(T[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = T[i] * D_PI_4;
    real8_t at   = ArcTanPM( Y[i], X[i] );

    EXPECT_DOUBLE_EQ( test, at );
  }
}


// =======================================================================================


TEST( arctanpm4, Positive ) {
  real4_t X[] = { -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f };
  real4_t Y[] = { -1.0f,  0.0f,  1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f };
  real4_t T[] = { -3.0f,  4.0f,  3.0f, -2.0f, 0.0f, 2.0f, -1.0f, 0.0f, 1.0f };

  size_t n = sizeof(T) / sizeof(T[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = T[i] * F_PI_4;
    real4_t at   = ArcTanPM( Y[i], X[i] );

    EXPECT_FLOAT_EQ( test, at );
  }
}


// =======================================================================================


TEST( angle8, Positive ) {
  real8_t Rad2 = 0.47947961942355338;
  real8_t Rad3 = 0.83993274038914389;
  
  real8_t Ax = 3.2;
  real8_t Ay = 1.7;
  real8_t Az = 9.2;
  real8_t Bx = 4.2;
  real8_t By = 6.1;
  real8_t Bz = 3.2;

  EXPECT_DOUBLE_EQ( Rad2, Angle( Ax, Ay, Bx, By ) );
  EXPECT_DOUBLE_EQ( Rad3, Angle( Ax, Ay, Az, Bx, By, Bz ) );
}


TEST( angle4, Positive ) {
  real4_t Rad2 = 0.47947975993156433f;
  real4_t Rad3 = 0.83993270540069198f;
                
  real4_t Ax = 3.2f;
  real4_t Ay = 1.7f;
  real4_t Az = 9.2f;
  real4_t Bx = 4.2f;
  real4_t By = 6.1f;
  real4_t Bz = 3.2f;

  EXPECT_FLOAT_EQ( Rad2, Angle( Ax, Ay, Bx, By ) );
  EXPECT_NEAR( Rad3, Angle( Ax, Ay, Az, Bx, By, Bz ), 3.0e-8f );
}


// =======================================================================================


TEST( param8, Positive ) {
  real8_t A1 = 25.0;
  real8_t B1 = 45.0;
  real8_t  t = 0.25;
  real8_t C1 = 30.0;

  real8_t An[] = { 25.0, 30.0, 35.0 };
  real8_t Bn[] = { 45.0, 50.0, 55.0 };
  real8_t Cn[] = { 30.0, 35.0, 40.0 };
  
  size_t n = sizeof(An)/sizeof(An[0]);

  real8_t Tn[n];

  EXPECT_DOUBLE_EQ(  C1, parametric( A1, B1, t ) );

  parametric( Tn, An, Bn, n, t );
  
  for ( size_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( Cn[i], Tn[i] );
  }
}


TEST( param4, Positive ) {
  real4_t tol = 1.0e-8f;

  real4_t A1 = 25.0f;
  real4_t B1 = 45.0f;
  real4_t  t = 0.25f;
  real4_t C1 = 30.0f;

  real4_t An[] = { 25.0f, 30.0f, 35.0f };
  real4_t Bn[] = { 45.0f, 50.0f, 55.0f };
  real4_t Cn[] = { 30.0f, 35.0f, 40.0f };
  
  size_t n = sizeof(An)/sizeof(An[0]);

  real4_t Tn[n];

  EXPECT_NEAR(  C1, parametric( A1, B1, t ), tol );

  parametric( Tn, An, Bn, n, t );
  
  for ( size_t i=0; i<n; i++ ) {
    EXPECT_NEAR( Cn[i], Tn[i], tol );
  }
}


// =======================================================================================


TEST( test_gcd64, Positive ) {
  int64_t A[] = { 2063, 883, 1423, 2713, 3137 };
  int64_t B[] = { 1667, 733, 1823, 3061, 1091 };
  int64_t G[] = { 2399, 607, 2243, 1567, 1487 };

  size_t n = sizeof(A) / sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    int64_t u = A[i] * G[i];
    int64_t v = B[i] * G[i];
    EXPECT_EQ( G[i], gcd( u, v ) );
  }
}


TEST( test_gcd32, Positive ) {
  int32_t A[] = { 2063, 883, 1423, 2713, 3137 };
  int32_t B[] = { 1667, 733, 1823, 3061, 1091 };
  int32_t G[] = { 2399, 607, 2243, 1567, 1487 };

  size_t n = sizeof(A) / sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    int32_t u = A[i] * G[i];
    int32_t v = B[i] * G[i];
    EXPECT_EQ( G[i], gcd( u, v ) );
  }
}

TEST( test_lcm64, Positive ) {
  int64_t A[] = { 1762, 4817, 9957, 4012, 9943, 9724,
                  3636, 6454, 8075, 3442 };
  int64_t B[] = { 1755, 5339, 6263, 1809, 8545, 4084,
                  9733, 9585, 6438, 7250 };
  int64_t T[] = { 3092310, 25717963, 62360691, 7257708,
                  84962935, 9928204, 35389188, 61861590,
                  51986850, 12477250 };
  size_t n = sizeof(A) / sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    int64_t u = A[i];
    int64_t v = B[i];
    EXPECT_EQ( T[i], lcm( u, v ) );
  }
}

TEST( test_lcm32, Positive ) {
  int32_t A[] = { 9650, 9226, 3957, 1358, 3179,
                  7691, 4007, 4326, 5831, 7524 };
  int32_t B[] = { 5791, 4777, 4644, 5186, 1484,
                  6201, 9034, 4025, 5062, 8398 };
  int32_t T[] = { 55883150, 44072602, 6125436, 3521294,
                  4717636, 47691891, 36199238, 2487450,
                  29516522, 1662804 };
  size_t n = sizeof(A) / sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    int32_t u = A[i];
    int32_t v = B[i];
    EXPECT_EQ( T[i], lcm( u, v ) );
  }
}

TEST( test_lcm16, Positive ) {
  int16_t A[] = { 10, 26, 21, 9, 28, 9, 41, 25, 16, 4 };
  int16_t B[] = { 35, 27, 3, 50, 18, 12, 4, 26, 32, 22 };
  int16_t T[] = { 70, 702, 21, 450, 252, 36, 164, 650, 32, 44 };
  
  size_t n = sizeof(A) / sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    int16_t u = A[i];
    int16_t v = B[i];
    EXPECT_EQ( T[i], lcm( u, v ) );
  }
}



} // end namespace



// =======================================================================================
// **                             U T E S T _ M A T H D E F                             **
// ======================================================================== END FILE =====
