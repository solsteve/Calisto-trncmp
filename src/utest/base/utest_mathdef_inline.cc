// ====================================================================== BEGIN FILE =====
// **                      U T E S T _ M A T H D E F _ I N L I N E                      **
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
/** @brief  Automated testing for inline MathDef.
 *  @file   utest_mathdef_inline.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-22
 *
 *  Provides automated testing for inline auxiliary math definitions..
 */
// =======================================================================================


#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST(are_equalR8, Positive) {
  real8_t A = 60.0;
  real8_t B = 5.0;
  EXPECT_TRUE( areEqual(A/4.0, B*3.0) );
}


TEST(are_equalR8, Negative) {
  real8_t A = 60.0;
  real8_t B = 5.0;
  EXPECT_FALSE( areEqual(A/4.0, B*3.1) );
}


TEST(are_equalR4, Positive) {
  real4_t A = 60.0f;
  real4_t B = 5.0f;
  EXPECT_TRUE( areEqual(A/4.0f, B*3.0f) );
}


TEST(are_equalR4, Negative) {
  real4_t A = 60.0f;
  real4_t B = 5.0f;
  EXPECT_FALSE( areEqual(A/4.0f, B*3.1f) );
}


// ---------------------------------------------------------------------------------------


TEST(are_equalR8_tol, Positive) {
  real8_t A = 60.0;
  real8_t B = 60.1;
  real8_t T = 0.2;
  EXPECT_TRUE( areEqual(A, B, T) );
}


TEST(are_equalR8_tol, Negative) {
  real8_t A = 60.0;
  real8_t B = 60.1;
  real8_t T = 0.05;
  EXPECT_FALSE( areEqual(A, B, T) );
}


TEST(are_equalR4_tol, Positive) {
  real4_t A = 60.0f;
  real4_t B = 60.1f;
  real4_t T = 0.2f;
  EXPECT_TRUE( areEqual(A, B, T) );
}


TEST(are_equalR4_tol, Negative) {
  real4_t A = 60.0f;
  real4_t B = 60.1f;
  real4_t T = 0.05f;
  EXPECT_FALSE( areEqual(A, B, T) );
}


// =======================================================================================


TEST(not_equalR8, Negative) {
  real8_t A = 60.0;
  real8_t B = 5.0;
  EXPECT_FALSE( notEqual(A/4.0, B*3.0) );
}


TEST(not_equalR8, Positive) {
  real8_t A = 60.0;
  real8_t B = 5.0;
  EXPECT_TRUE( notEqual(A/4.0, B*3.1) );
}


TEST(not_equalR4, Negative) {
  real4_t A = 60.0f;
  real4_t B = 5.0f;
  EXPECT_FALSE( notEqual(A/4.0f, B*3.0f) );
}


TEST(not_equalR4, Positive) {
  real4_t A = 60.0f;
  real4_t B = 5.0f;
  EXPECT_TRUE( notEqual(A/4.0f, B*3.1f) );
}


// ---------------------------------------------------------------------------------------


TEST(not_equalR8_tol, Negative) {
  real8_t A = 60.0;
  real8_t B = 60.1;
  real8_t T = 0.2;
  EXPECT_FALSE( notEqual(A, B, T) );
}


TEST(not_equalR8_tol, Positive) {
  real8_t A = 60.0;
  real8_t B = 60.1;
  real8_t T = 0.05;
  EXPECT_TRUE( notEqual(A, B, T) );
}


TEST(not_equalR4_tol, Negative) {
  real4_t A = 60.0f;
  real4_t B = 60.1f;
  real4_t T = 0.2f;
  EXPECT_FALSE( notEqual(A, B, T) );
}


TEST(not_equalR4_tol, Positive) {
  real4_t A = 60.0f;
  real4_t B = 60.1f;
  real4_t T = 0.05f;
  EXPECT_TRUE( notEqual(A, B, T) );
}


// =======================================================================================


TEST(is_zeroR8, Positive) {
  real8_t A = 30.0;
  real8_t B = 30.0;
  EXPECT_TRUE( isZero(A-B) );
}


TEST(is_zeroR8, Negative) {
  real8_t A = 30.0;
  real8_t B = 30.1;
  EXPECT_FALSE( isZero(A-B) );
}


TEST(is_zeroR4, Positive) {
  real4_t A = 30.0f;
  real4_t B = 30.0f;
  EXPECT_TRUE( isZero(A-B) );
}


TEST(is_zeroR4, Negative) {
  real4_t A = 30.0f;
  real4_t B = 30.1f;
  EXPECT_FALSE( isZero(A-B) );
}


// ---------------------------------------------------------------------------------------


TEST(is_not_zeroR8, Negative) {
  real8_t A = 30.0;
  real8_t B = 30.0;
  EXPECT_FALSE( isNotZero(A-B) );
}


TEST(is_not_zeroR8, Positive) {
  real8_t A = 30.0;
  real8_t B = 30.1;
  EXPECT_TRUE( isNotZero(A-B) );
}


TEST(is_not_zeroR4, Negative) {
  real4_t A = 30.0f;
  real4_t B = 30.0f;
  EXPECT_FALSE( isNotZero(A-B) );
}


TEST(is_not_zeroR4, Positive) {
  real4_t A = 30.0f;
  real4_t B = 30.1f;
  EXPECT_TRUE( isNotZero(A-B) );
}


// =======================================================================================


TEST(is_zeroR8_tol, Positive) {
  real8_t A = 30.0;
  real8_t B = 30.0;
  real8_t T = 0.2;
  EXPECT_TRUE( isZero(A-B, T) );
}


TEST(is_zeroR8_tol, Negative) {
  real8_t A = 30.0;
  real8_t B = 30.1;
  real8_t T = 0.02;
  EXPECT_FALSE( isZero(A-B, T) );
}


TEST(is_zeroR4_tol, Positive) {
  real4_t A = 30.0f;
  real4_t B = 30.0f;
  real4_t T = 0.2f;
  EXPECT_TRUE( isZero(A-B, T) );
}


TEST(is_zeroR4_tol, Negative) {
  real4_t A = 30.0f;
  real4_t B = 30.1f;
  real4_t T = 0.02f;
  EXPECT_FALSE( isZero(A-B, T) );
}


// ---------------------------------------------------------------------------------------


TEST(is_not_zeroR8_tol, Negative) {
  real8_t A = 30.0;
  real8_t B = 30.0;
  real8_t T = 0.2;
  EXPECT_FALSE( isNotZero(A-B, T) );
}


TEST(is_not_zeroR8_tol, Positive) {
  real8_t A = 30.0;
  real8_t B = 30.1;
  real8_t T = 0.02;
  EXPECT_TRUE( isNotZero(A-B, T) );
}


TEST(is_not_zeroR4_tol, Negative) {
  real4_t A = 30.0f;
  real4_t B = 30.0f;
  real4_t T = 0.2f;
  EXPECT_FALSE( isNotZero(A-B, T) );
}


TEST(is_not_zeroR4_tol, Positive) {
  real4_t A = 30.0f;
  real4_t B = 30.1f;
  real4_t T = 0.02f;
  EXPECT_TRUE( isNotZero(A-B, T) );
}


// =======================================================================================


TEST(rootR8, Positive) {
  real8_t A = 3.7;
  real8_t B = A*A*A;
  EXPECT_DOUBLE_EQ( Root( B, 3.0 ), A );
}


TEST(rootR4, Positive) {
  real4_t A = 3.7f;
  real4_t B = A*A*A;
  EXPECT_FLOAT_EQ( Root( B, 3.0f ), A );
}


// ---------------------------------------------------------------------------------------


TEST(powerR8, Positive) {
  real8_t A = 3.7;
  real8_t B = A*A*A;
  EXPECT_DOUBLE_EQ( Power( A, 3.0 ), B );
}


TEST(powerR4, Positive) {
  real4_t A = 3.7f;
  real4_t B = A*A*A;
  EXPECT_FLOAT_EQ( Power( A, 3.0f ), B );
}


// =======================================================================================


TEST(deg2rad8, Positive) {
  real8_t D1 = 3.0e1;
  real8_t D2 = 4.5e1;
  real8_t R1 = D_PI/6.0;
  real8_t R2 = D_PI_4;

  EXPECT_DOUBLE_EQ( DEG2RAD(D1), R1 );
  EXPECT_DOUBLE_EQ( DEG2RAD(D2), R2 );

  EXPECT_DOUBLE_EQ( RAD2DEG(R1), D1 );
  EXPECT_DOUBLE_EQ( RAD2DEG(R2), D2 );
}


TEST(deg2rad4, Positive) {
  real4_t D1 = 3.0e1f;
  real4_t D2 = 4.5e1f;
  real4_t R1 = F_PI/6.0f;
  real4_t R2 = F_PI_4;

  EXPECT_FLOAT_EQ( DEG2RAD(D1), R1 );
  EXPECT_FLOAT_EQ( DEG2RAD(D2), R2 );

  EXPECT_FLOAT_EQ( RAD2DEG(R1), D1 );
  EXPECT_FLOAT_EQ( RAD2DEG(R2), D2 );
}


// ---------------------------------------------------------------------------------------


TEST(trig_d8, Positive) {
  real8_t a1 = 4.5e1;
  real8_t a2 = 3.0e1;
  
  real8_t s1 = D_HALF*D_SQRT2;
  real8_t c1 = D_HALF*D_SQRT2;
  real8_t t1 = D_ONE;

  real8_t s2 = D_HALF;
  real8_t c2 = D_HALF*D_SQRT3;
  real8_t t2 = D_SQRT3/D_THREE;

  EXPECT_DOUBLE_EQ( sin_deg(a1), s1 );
  EXPECT_DOUBLE_EQ( cos_deg(a1), c1 );
  EXPECT_DOUBLE_EQ( tan_deg(a1), t1 );
  
  EXPECT_DOUBLE_EQ( sin_deg(a2), s2 );
  EXPECT_DOUBLE_EQ( cos_deg(a2), c2 );
  EXPECT_DOUBLE_EQ( tan_deg(a2), t2 );

  EXPECT_DOUBLE_EQ( asin_deg(s1), a1 );
  EXPECT_DOUBLE_EQ( acos_deg(c1), a1 );
}


TEST(trig_d4, Positive) {
  real4_t a1 = 4.5e1f;
  real4_t a2 = 3.0e1f;
  
  real4_t s1 = F_HALF*F_SQRT2;
  real4_t c1 = F_HALF*F_SQRT2;
  real4_t t1 = F_ONE;

  real4_t s2 = F_HALF;
  real4_t c2 = F_HALF*F_SQRT3;
  real4_t t2 = F_SQRT3/F_THREE;

  EXPECT_FLOAT_EQ( sin_deg(a1),  s1 );
  EXPECT_FLOAT_EQ( cos_deg(a1),  c1 );
  EXPECT_FLOAT_EQ( tan_deg(a1),  t1 );
  
  EXPECT_FLOAT_EQ( sin_deg(a2),  s2 );
  EXPECT_FLOAT_EQ( cos_deg(a2),  c2 );
  EXPECT_FLOAT_EQ( tan_deg(a2),  t2 );

  EXPECT_FLOAT_EQ( asin_deg(s1), a1 );
  EXPECT_FLOAT_EQ( acos_deg(c1), a1 );
}


// ---------------------------------------------------------------------------------------


TEST(sincos_d8, Positive) {
  real8_t a1 = 4.5e1;
  real8_t a2 = 3.0e1;
  
  real8_t s1 = D_HALF*D_SQRT2;
  real8_t c1 = D_HALF*D_SQRT2;

  real8_t s2 = D_HALF;
  real8_t c2 = D_HALF*D_SQRT3;

  real8_t s, c;

  sincos_deg( a1, &s, &c );

  EXPECT_DOUBLE_EQ( s, s1 );
  EXPECT_DOUBLE_EQ( c, c1 );

  sincos_deg( a2, &s, &c );

  EXPECT_DOUBLE_EQ( s, s2 );
  EXPECT_DOUBLE_EQ( c, c2 );
}


TEST(sincos_d4, Positive) {
  real4_t a1 = 4.5e1f;
  real4_t a2 = 3.0e1f;
  
  real4_t s1 = F_HALF*F_SQRT2;
  real4_t c1 = F_HALF*F_SQRT2;

  real4_t s2 = F_HALF;
  real4_t c2 = F_HALF*F_SQRT3;

  real4_t s, c;

  sincos_deg( a1, &s, &c );

  EXPECT_FLOAT_EQ( s, s1 );
  EXPECT_FLOAT_EQ( c, c1 );

  sincos_deg( a2, &s, &c );

  EXPECT_FLOAT_EQ( s, s2 );
  EXPECT_FLOAT_EQ( c, c2 );
}


// =======================================================================================


TEST( angle_diff8, Positive ) {
  real8_t A[] = {  40.0, 100.0, 200.0, 300.0 };
  real8_t B[] = { 320.0,  80.0, 150.0, 240.0 };
  real8_t D[] = {  80.0,  20.0,  50.0,  60.0 };

  size_t n = sizeof(A)/sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test_p = AngleDiff( A[i], B[i] );
    real8_t test_n = AngleDiff( B[i], A[i] );
    EXPECT_DOUBLE_EQ(  D[i], test_p );
    EXPECT_DOUBLE_EQ( -D[i], test_n );
  }
}


TEST( angle_diff4, Positive ) {
  real4_t A[] = {  40.0f, 100.0f, 200.0f, 300.0f };
  real4_t B[] = { 320.0f,  80.0f, 150.0f, 240.0f };
  real4_t D[] = {  80.0f,  20.0f,  50.0f,  60.0f };

  size_t n = sizeof(A)/sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test_p = AngleDiff( A[i], B[i] );
    real4_t test_n = AngleDiff( B[i], A[i] );
    EXPECT_FLOAT_EQ(  D[i], test_p );
    EXPECT_FLOAT_EQ( -D[i], test_n );
  }
}


// ---------------------------------------------------------------------------------------


TEST( radian_diff8, Positive ) {
  real8_t A[] = {  1.0, 5.0, 9.0, 13.0 };
  real8_t B[] = { 15.0, 3.0, 7.0, 11.0 };
  real8_t D   = D_PI_4;
  real8_t k   = 1.25e-1 * D_PI;
  real8_t t   = 1.0e-8;

  size_t n = sizeof(A)/sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test_p = RadianDiff( k*A[i], k*B[i] );
    real8_t test_n = RadianDiff( k*B[i], k*A[i] );
    EXPECT_NEAR(  D, test_p, t );
    EXPECT_NEAR( -D, test_n, t );
  }
}


TEST( radian_diff4, Positive ) {
  real4_t A[] = {  1.0f, 5.0f, 9.0f, 13.0f };
  real4_t B[] = { 15.0f, 3.0f, 7.0f, 11.0f };
  real4_t D   = F_PI_4;
  real4_t k   = 1.25e-1f * F_PI;
  real4_t t   = 1.0e-6f;
  
  size_t n = sizeof(A)/sizeof(A[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test_p = RadianDiff( k*A[i], k*B[i] );
    real4_t test_n = RadianDiff( k*B[i], k*A[i] );
    EXPECT_NEAR(  D, test_p, t );
    EXPECT_NEAR( -D, test_n, t );
  }
}


// =======================================================================================


TEST( mag8, Positive ) {
  real8_t x2 = 3.0;
  real8_t y2 = 4.0;
  real8_t d2 = 5.0;

  real8_t x3 = 16.0;
  real8_t y3 = 12.0;
  real8_t z3 = 15.0;
  real8_t d3 = 25.0;

  real8_t xa = 4.0;
  real8_t xb = 7.0;
  real8_t ya = 2.0;
  real8_t yb = 6.0;
  real8_t dd = 5.0;

  EXPECT_DOUBLE_EQ( d2, Mag( x2, y2 ) );
  EXPECT_DOUBLE_EQ( d3, Mag( x3, y3, z3 ) );
  EXPECT_DOUBLE_EQ( dd, Mag( xa, ya, xb, yb ) );
}


TEST( mag4, Positive ) {
  real4_t x2 = 3.0f;
  real4_t y2 = 4.0f;
  real4_t d2 = 5.0f;

  real4_t x3 = 16.0f;
  real4_t y3 = 12.0f;
  real4_t z3 = 15.0f;
  real4_t d3 = 25.0f;

  real4_t xa = 4.0;
  real4_t xb = 7.0;
  real4_t ya = 2.0;
  real4_t yb = 6.0;
  real4_t dd = 5.0;

  EXPECT_FLOAT_EQ( d2, Mag( x2, y2 ) );
  EXPECT_FLOAT_EQ( d3, Mag( x3, y3, z3 ) );
  EXPECT_FLOAT_EQ( dd, Mag( xa, ya, xb, yb ) );
}


// =======================================================================================


TEST( dot_cross8, Positive ) {
  real8_t tol = 1.0e-10;

  real8_t Ax = 3.1;
  real8_t Ay = 2.7;
  real8_t Az = 4.9;

  real8_t Bx = 5.2;
  real8_t By = 6.3;
  real8_t Bz = 8.4;

  real8_t Cx, Cy, Cz;

  real8_t tCx = -8.19;
  real8_t tCy = -0.56;
  real8_t tCz =  5.49;

  real8_t D2 = 33.13;
  real8_t D3 = 74.29;

  Cross( &Cx, &Cy, &Cz, Ax, Ay, Az, Bx, By, Bz );

  EXPECT_NEAR( tCx, Cx, tol );
  EXPECT_NEAR( tCy, Cy, tol );
  EXPECT_NEAR( tCz, Cz, tol );
  EXPECT_NEAR( tCz, Cross( Ax, Ay, Bx, By ), tol );

  EXPECT_NEAR( D2, Dot( Ax, Ay, Bx, By ), tol );
  EXPECT_NEAR( D3, Dot( Ax, Ay, Az, Bx, By, Bz ), tol );
}


TEST( dot_cross4, Positive ) {
  real4_t tol = 8.0e-6f;

  real4_t Ax = 3.1f;
  real4_t Ay = 2.7f;
  real4_t Az = 4.9f;

  real4_t Bx = 5.2f;
  real4_t By = 6.3f;
  real4_t Bz = 8.4f;

  real4_t Cx, Cy, Cz;

  real4_t tCx = -8.19f;
  real4_t tCy = -0.56f;
  real4_t tCz =  5.49f;

  real4_t D2 = 33.13f;
  real4_t D3 = 74.29f;

  Cross( &Cx, &Cy, &Cz, Ax, Ay, Az, Bx, By, Bz );

  EXPECT_NEAR( tCx, Cx, tol );
  EXPECT_NEAR( tCy, Cy, tol );
  EXPECT_NEAR( tCz, Cz, tol );
  EXPECT_NEAR( tCz, Cross( Ax, Ay, Bx, By ), tol );

  EXPECT_NEAR( D2, Dot( Ax, Ay, Bx, By ), tol );
  EXPECT_NEAR( D3, Dot( Ax, Ay, Az, Bx, By, Bz ), tol );
}


// =======================================================================================


TEST( clamp8, Positive ) {
  real8_t X[] = { -1.0, -1.0e-8, -1.0e-10, -1.0e-12, 0.0, 1.0e-12, 1.0e-10, 1.0e-8, 1.0 };
  real8_t C[] = { -1.0, -1.0e-8, -1.0e-10, 0.0, 0.0, 0.0, 1.0e-10, 1.0e-8, 1.0 };
  size_t n = sizeof(X)/sizeof(X[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t cl = clamp( X[i], 0.9e-10 );
    EXPECT_DOUBLE_EQ( cl, C[i] );
  }
}


TEST( clamp4, Positive ) {
  real4_t X[] = { -1.0f, -1.0e-8f, -1.0e-10f, -1.0e-12f, 0.0f, 1.0e-12f, 1.0e-10f, 1.0e-8f, 1.0f };
  real4_t C[] = { -1.0f, -1.0e-8f, -1.0e-10f, 0.0f, 0.0f, 0.0f, 1.0e-10f, 1.0e-8f, 1.0f };
  size_t n = sizeof(X)/sizeof(X[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t cl = clamp( X[i], 0.9e-10f );
    EXPECT_FLOAT_EQ( cl, C[i] );
  }
}


// =======================================================================================


TEST( pow8, Positive ) {
  real8_t x1 = 3.1415;
  real8_t x2 = x1*x1;
  real8_t x3 = x1*x1*x1;
  real8_t x4 = x1*x1*x1*x1;
  real8_t x5 = x1*x1*x1*x1*x1;
  real8_t x6 = x1*x1*x1*x1*x1*x1;
  real8_t x7 = x1*x1*x1*x1*x1*x1*x1;
  real8_t x8 = x1*x1*x1*x1*x1*x1*x1*x1;
  real8_t x9 = x1*x1*x1*x1*x1*x1*x1*x1*x1;

  EXPECT_DOUBLE_EQ( x2, pow_2(x1) );
  EXPECT_DOUBLE_EQ( x3, pow_3(x1) );
  EXPECT_DOUBLE_EQ( x4, pow_4(x1) );
  EXPECT_DOUBLE_EQ( x5, pow_5(x1) );
  EXPECT_DOUBLE_EQ( x6, pow_6(x1) );
  EXPECT_DOUBLE_EQ( x7, pow_7(x1) );
  EXPECT_DOUBLE_EQ( x8, pow_8(x1) );
  EXPECT_DOUBLE_EQ( x9, pow_9(x1) );
}


TEST( pow4, Positive ) {
  real4_t x1 = 3.1415f;
  real4_t x2 = x1*x1;
  real4_t x3 = x1*x1*x1;
  real4_t x4 = x1*x1*x1*x1;
  real4_t x5 = x1*x1*x1*x1*x1;
  real4_t x6 = x1*x1*x1*x1*x1*x1;
  real4_t x7 = x1*x1*x1*x1*x1*x1*x1;
  real4_t x8 = x1*x1*x1*x1*x1*x1*x1*x1;
  real4_t x9 = x1*x1*x1*x1*x1*x1*x1*x1*x1;

  EXPECT_FLOAT_EQ( x2, pow_2(x1) );
  EXPECT_FLOAT_EQ( x3, pow_3(x1) );
  EXPECT_FLOAT_EQ( x4, pow_4(x1) );
  EXPECT_FLOAT_EQ( x5, pow_5(x1) );
  EXPECT_FLOAT_EQ( x6, pow_6(x1) );
  EXPECT_FLOAT_EQ( x7, pow_7(x1) );
  EXPECT_FLOAT_EQ( x8, pow_8(x1) );
  EXPECT_FLOAT_EQ( x9, pow_9(x1) );
}


// =======================================================================================


TEST( deg_mod8, Positive ) {
  real8_t original[] = { -400.0, -360.0, -180.0, 0.0, 180.0, 360.0, 400.0, 720.0, 800.0 };
  real8_t expected[] = {  320.0,    0.0,  180.0, 0.0, 180.0,   0.0,  40.0,   0.0,  80.0 };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = DegreeCorrect( original[i] );
    EXPECT_DOUBLE_EQ( expected[i], test );
  }
}


TEST( deg_mod4, Positive ) {
  real4_t original[] = { -400.0f, -360.0f, -180.0f, 0.0f, 180.0f, 360.0f, 400.0f, 720.0f, 800.0f };
  real4_t expected[] = {  320.0f,    0.0f,  180.0f, 0.0f, 180.0f,   0.0f,  40.0f,   0.0f,  80.0f };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = DegreeCorrect( original[i] );
    EXPECT_FLOAT_EQ( expected[i], test );
  }
}


// =======================================================================================


TEST( rad_mod8, Positive ) {
  real8_t original[] = { -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
  real8_t expected[] = {  1.0,  0.0,  1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = RadCorrect( D_PI * original[i] ) / D_PI;
    EXPECT_DOUBLE_EQ( expected[i], test );
  }
}


TEST( rad_mod4, Positive ) {
  real4_t original[] = { -3.0f, -2.0f, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
  real4_t expected[] = {  1.0f,  0.0f,  1.0f,  1.5f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = RadCorrect( F_PI * original[i] ) / F_PI;
    EXPECT_FLOAT_EQ( expected[i], test );
  }
}


// =======================================================================================


TEST( deg_pm_mod8, Positive ) {
  real8_t original[] = { -450.0, -360.0, -270.0, -180.0, -90.0, 0.0, 90.0,  180.0, 270.0, 360.0, 450.0,  540.0, 630.0, 720.0, 810.0 };
  real8_t expected[] = {  -90.0,    0.0,   90.0, -180.0, -90.0, 0.0, 90.0, -180.0, -90.0,   0.0,  90.0, -180.0, -90.0,   0.0,  90.0 };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = DegreeCorrectPM( original[i] );
    EXPECT_DOUBLE_EQ( expected[i], test );
  }
}


TEST( deg_pm_mod4, Positive ) {
  real4_t original[] = { -450.0f, -360.0f, -270.0f, -180.0f, -90.0f, 0.0f, 90.0f,  180.0f, 270.0f, 360.0f, 450.0f,  540.0f, 630.0f, 720.0f, 810.0f };
  real4_t expected[] = {  -90.0f,    0.0f,   90.0f, -180.0f, -90.0f, 0.0f, 90.0f, -180.0f, -90.0f,   0.0f,  90.0f, -180.0f, -90.0f,   0.0f,  90.0f };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = DegreeCorrectPM( original[i] );
    EXPECT_FLOAT_EQ( expected[i], test );
  }
}


// =======================================================================================


TEST( rad_pm_mod8, Positive ) {
  real8_t original[] = { -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0,  2.0,
                         3.0, 4.0, 5.0,  6.0,  7.0, 8.0, 9.0 };
  real8_t expected[] = { -1.0,  0.0,  1.0, -2.0, -1.0, 0.0, 1.0, -2.0,
                         -1.0, 0.0, 1.0, -2.0, -1.0, 0.0, 1.0 };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = RadCorrectPM( original[i] * D_PI_2 ) / D_PI_2;
    EXPECT_NEAR( expected[i], test, 1.0e-12 );
  }
}


TEST( rad_pm_mod4, Positive ) {
  real4_t original[] = { -5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f, 1.0f,  2.0f,  3.0f,
                         4.0f, 5.0f,  6.0f,  7.0f, 8.0f, 9.0f };
  real4_t expected[] = { -1.0f,  0.0f,  1.0f, -2.0f, -1.0f, 0.0f, 1.0f, -2.0f, -1.0f,
                         0.0f, 1.0f, -2.0f, -1.0f, 0.0f, 1.0f };

  size_t n = sizeof(original)/sizeof(original[0]);

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = RadCorrectPM( original[i] * F_PI_2 ) / F_PI_2;
    EXPECT_NEAR( expected[i], test, 1.0e-6f );
  }
}


// =======================================================================================


TEST( sum_to, Positive ) {
  int32_t a[] = { 1, 3, 7, 11, 23, 71, 83, 117 };
  int32_t b[] = { 1, 6, 28, 66, 276, 2556, 3486, 6903 };
  int32_t c[] = { 1, 14, 140, 506, 4324, 121836, 194054, 540735 };
  size_t  n   = sizeof(a)/sizeof(a[0]);

  for ( size_t i=0; i<n; i++ ) {
    EXPECT_EQ( b[i], nsum(a[i]) );
    EXPECT_EQ( c[i], n2sum(a[i]) );
  }
}


} // end namespace


// =======================================================================================
// **                      U T E S T _ M A T H D E F _ I N L I N E                      **
// ======================================================================== END FILE =====
