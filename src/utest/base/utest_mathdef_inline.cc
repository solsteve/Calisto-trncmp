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

TEST( pf_mod8, Positive ) {

  real8_t original[] = { -6.0, -1.0, 0.0, 3.0, 7.0 };
  real8_t expected[] = {  2.0,  3.0, 0.0, 3.0, 3.0 };

  size_t n = sizeof(original)/sizeof(original[0]);

  const real8_t M = 4.0;

  for ( size_t i=0; i<n; i++ ) {
    real8_t test = PFmod( original[i], M );
    EXPECT_DOUBLE_EQ( expected[i], test );
  }
}

TEST( pf_mod4, Positive ) {

  real4_t original[] = { -6.0f, -1.0f, 0.0f, 3.0f, 7.0f };
  real4_t expected[] = {  2.0f,  3.0f, 0.0f, 3.0f, 3.0f };

  size_t n = sizeof(original)/sizeof(original[0]);

  const real4_t M = 4.0f;

  for ( size_t i=0; i<n; i++ ) {
    real4_t test = PFmod( original[i], M );
    EXPECT_FLOAT_EQ( expected[i], test );
  }
}

// ---------------------------------------------------------------------------------------

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

TEST( mag8, Positive ) {

  real8_t A1 = 3.0;
  real8_t B1 = 4.0;
  real8_t C1 = 5.0;

  real8_t A2 = 17.0;
  real8_t A3 = 20.0;

  real8_t B2 = 11.0;
  real8_t B3 = 15.0;

  
  EXPECT_DOUBLE_EQ( C1, Mag( A1, B1 ) );
  EXPECT_DOUBLE_EQ( C1, Mag( A3, B3, A2, B2 ) );
}

TEST( mag4, Positive ) {

  real4_t tol = 1.0e-8f;

  real4_t A1 = 3.0f;
  real4_t B1 = 4.0f;
  real4_t C1 = 5.0f;

  real4_t A2 = 17.0f;
  real4_t A3 = 20.0f;

  real4_t B2 = 11.0f;
  real4_t B3 = 15.0f;

  
  EXPECT_NEAR( C1, Mag( A1, B1 ), tol );
  EXPECT_NEAR( C1, Mag( A3, B3, A2, B2 ), tol );
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


} // end namespace

