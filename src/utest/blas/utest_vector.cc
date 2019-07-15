// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ L I N A L G 2 D                            **
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
/** @brief  Automated testing for LinAlg2 methods.
 *  @file   utest_linalg2d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides automated testing for combination of Vector2D and Matrix2D class and methods.
 */
// =======================================================================================


#include <limits.h>
#include <Vector.hh>
#include <gtest/gtest.h>

namespace {

// =======================================================================================
void check( real8_t* A, real8_t* T, int32_t n, real8_t ep=D_EPSILON ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_NEAR( A[i], T[i], ep );
  }
}


// =======================================================================================
void check( Vector& V, real8_t* T, real8_t ep=D_EPSILON ) {
  // -------------------------------------------------------------------------------------
  int32_t n = size(V);
  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_NEAR( V(i), T[i], ep );
  }
}


// =======================================================================================
TEST(test_vector_create, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t data[] = { 2.0, 3.0, 5.0, 6.0, 7.0, 9.0, 1.0 };
  const int32_t NN = sizeof(data)/sizeof(data[0]);
  
  { // ----- test: size constructor, load & store ------------------------
    real8_t test[NN];
    Vector V(7,4);
    V.load( data );
    V.store( test );
    check( data, test, NN );
  }
  
  { // ----- test: copy constructor --------------------------------------
    real8_t test[NN];
    Vector V(data,NN);
    Vector Z(V);
    Z.store( test );
    check( data, test, NN );
  }
  
}

// =======================================================================================
TEST(test_vector_copy, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t data[] = { 2.0, 3.0, -3.2, 5.0, 6.0, -7.5, 9.0, 1.0 };
  const int32_t NN = sizeof(data)/sizeof(data[0]);
  
  { // ----- test: copy --------------------------------------------------
    Vector V(data,NN);
    Vector Z;
    Z.copy(V);
    check( Z, data );
  }

  { // ----- test: copy --------------------------------------------------
    Vector V(data,NN);
    Vector Z;
    Z = V;
    check( Z, data );
  }

}

// =======================================================================================
TEST(test_vector_string, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t data[] = { 3.1, 4.1, 5.9 };
  const int32_t NN = sizeof(data)/sizeof(data[0]);

  { // ----- test: print --------------------------------------------------
    Vector V(data,NN);
    std::string str = toString( V, "%.2f", ";" );
    EXPECT_STREQ( "3.10;4.10;5.90", str.c_str() );
  }

  { // ----- test: print --------------------------------------------------
    Vector V(data,NN);
    std::string str = toString( "a=[", V, "];", "%.2f", "," );
    EXPECT_STREQ( "a=[3.10,4.10,5.90];", str.c_str() );
  }

}

// =======================================================================================
TEST(test_vector_swap, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, 4.1, 5.9 };
  real8_t bdat[] = { 2.8, 7.1, 8.3 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  { // ----- test: print --------------------------------------------------
    Vector A(adat,NN);
    Vector B(bdat,NN);

    check(A,adat);
    check(B,bdat);

    A.swap( B );

    check(A,bdat);
    check(B,adat);
  }

    
}

// =======================================================================================
TEST(test_vector_scale, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8, 9.7, 9.2 };
  real8_t bdat[] = { 6.2, 8.2, 11.8, 5.2, 10.6, 11.6, 19.4, 18.4  };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  { // ----- test: print --------------------------------------------------
    Vector A(adat,NN);

    check(A,adat);

    A.mul( 2.0 );

    check(A,bdat);
  }

  { // ----- test: print --------------------------------------------------
    Vector A(bdat,NN);

    check(A,bdat);

    A.div( 2.0 );

    check(A,adat);
  }

    
}

// =======================================================================================
TEST(test_vector_add, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  real8_t cdat[] = { 1.1, 2.2 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  real8_t test1[] = { 4.3, -2.9, -4.7, 3.8, -4.1, 7.0, 10.9, -8.0 };
  real8_t test2[] = { 5.8, -2.3, -8.7, 0.8, -2.5, 1.3, 18.7, -4.7 };
  real8_t test3[] = { 4.8, 3.9, -0.7, 0.3, 4.9, -2.4, 11.1, 6.6 };
  real8_t test4[] = { 6.2, 5.3, 0.7, 1.7, 6.3, -1.0, 12.5, 8.0 };

  {
    Vector A( adat, NN );
    check( A, adat );

    A.add( 1.2 );
    check( A, test1, 1.0e-14 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.add( B );
    check( A, test2, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    Vector C( cdat, 2 );
    check( A, adat );
    check( B, bdat );

    C.add( A, B );
    check( C, test2, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.add( 2.1, B );
    check( A, test3, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.add( B, 3.5 );
    check( A, test4, 1.0e-15 );
  }

}



// =======================================================================================
TEST(test_vector_sub, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  real8_t cdat[] = { 1.1, 2.2 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  real8_t test1[] = { 1.9, -5.3, -7.1, 1.4, -6.5, 4.6, 8.5, -10.4 };
  real8_t test2[] = { 0.4, -5.9, -3.1, 4.4, -8.1, 10.3, 0.7, -13.7 };
  real8_t test3[] = { -0.6, 0.3, 4.9, 3.9, -0.7, 6.6, -6.9, -2.4 };
  real8_t test4[] = { -0.8, -1.7, -6.3, -5.3, -0.7, -8.0, 5.5, 1.0 };

  {
    Vector A( adat, NN );
    check( A, adat );

    A.sub( 1.2 );
    check( A, test1, 1.0e-14 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.sub( B );
    check( A, test2, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    Vector C( cdat, 2 );
    check( A, adat );
    check( B, bdat );

    C.sub( A, B );
    check( C, test2, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.sub( 2.1, B );
    check( A, test3, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.sub( B, 3.5 );
    check( A, test4, 1.0e-15 );
  }

}



// =======================================================================================
TEST(test_vector_mul, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  real8_t cdat[] = { 1.1, 2.2 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  real8_t test1[] = { 3.72, -4.92, -7.08, 3.12, -6.36, 6.96, 11.64, -11.04 };
  real8_t test2[] = { 8.37, -7.38, 16.52, -4.68, -14.84, -26.10, 87.30, -41.40 };
  real8_t test3[] = { 5.67, 3.78, -5.88, -3.78, 5.88, -9.45, 18.90, 9.45 };
  real8_t test4[] = { 9.45, 6.30, -9.80, -6.30, 9.80, -15.75, 31.50, 15.75 };

  {
    Vector A( adat, NN );
    check( A, adat );

    A.mul( 1.2 );
    check( A, test1, 1.0e-14 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.mul( B );
    check( A, test2, 1.0e-14 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    Vector C( cdat, 2 );
    check( A, adat );
    check( B, bdat );

    C.mul( A, B );
    check( C, test2, 1.0e-14 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.mul( 2.1, B );
    check( A, test3, 1.0e-14 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.mul( B, 3.5 );
    check( A, test4, 1.0e-14 );
  }

}

// =======================================================================================
TEST(test_vector_div, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  real8_t cdat[] = { 1.1, 2.2 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  real8_t test1[] = {  2.583333333333333e+00, -3.416666666666667e+00, -4.916666666666667e+00,
                       2.166666666666667e+00, -4.416666666666667e+00,  4.833333333333333e+00,
                       8.083333333333334e+00, -7.666666666666666e+00 };
  real8_t test2[] = {  1.148148148148148e+00, -2.277777777777778e+00,  2.107142857142857e+00,
                       -1.444444444444444e+00, -1.892857142857143e+00, -1.288888888888889e+00,
                       1.077777777777778e+00, -2.044444444444444e+00 };
  real8_t test3[] = {  7.777777777777778e-01,  1.166666666666667e+00, -7.500000000000001e-01,
                       -1.166666666666667e+00,  7.500000000000001e-01, -4.666666666666667e-01,
                       2.333333333333333e-01,  4.666666666666667e-01 };
  real8_t test4[] = {  7.714285714285715e-01,  5.142857142857143e-01, -7.999999999999999e-01,
                       -5.142857142857143e-01,  7.999999999999999e-01, -1.285714285714286e+00,
                       2.571428571428572e+00,  1.285714285714286e+00 };

  {
    Vector A( adat, NN );
    check( A, adat );

    A.div( 1.2 );
    check( A, test1, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.div( B );
    check( A, test2, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    Vector C( cdat, 2 );
    check( A, adat );
    check( B, bdat );

    C.div( A, B );
    check( C, test2, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.div( 2.1, B );
    check( A, test3, 1.0e-15 );
  }

  {
    Vector A( adat, NN );
    Vector B( bdat, NN );
    check( A, adat );
    check( B, bdat );

    A.div( B, 3.5 );
    check( A, test4, 1.0e-15 );
  }

}


// =======================================================================================
TEST(test_vector_dot, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);
    Vector A( adat, NN );
    Vector B( bdat, NN );
    EXPECT_NEAR( 17.79, A.dot( B ), 1.0e-14 );  
}





// =======================================================================================
TEST(test_vector_norm, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);
    Vector A( adat, NN );

    EXPECT_DOUBLE_EQ( 45.7,         A.norm1()  );
    EXPECT_DOUBLE_EQ( sqrt(308.45), A.norm()   );
    EXPECT_DOUBLE_EQ( 308.45,       A.normsq() );
}


// =======================================================================================
TEST(test_vector_sum, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);
    Vector A( adat, NN );
    Vector B( bdat, NN );

    EXPECT_DOUBLE_EQ( -3.3,   A.sum()  );
    EXPECT_DOUBLE_EQ( 308.45, A.sumsq()   );
    EXPECT_DOUBLE_EQ( 423.82, A.sumsq(B) );
}


// =======================================================================================
TEST(test_vector_dist, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);
    Vector A( adat, NN );
    Vector B( bdat, NN );

    EXPECT_DOUBLE_EQ( 46.6,         A.dist1(B)  );
    EXPECT_DOUBLE_EQ( sqrt(423.82), A.dist(B)   );
    EXPECT_DOUBLE_EQ( 423.82,       A.distsq(B) );
}

// =======================================================================================
TEST(test_vector_normalize, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 3.1, -4.1, -5.9,  2.6, -5.3,  5.8, 9.7, -9.2 };
  real8_t bdat[] = { 2.7,  1.8, -2.8, -1.8,  2.8, -4.5, 9.0,  4.5 };
  const int32_t NN = sizeof(adat)/sizeof(adat[0]);

  {
  Vector A( adat, NN );
  check( A, adat );

  A.normalize();

  EXPECT_DOUBLE_EQ( D_ONE, A.dot( A ) );
  }

  {
  Vector A( adat, NN );
  Vector B( bdat, NN );
  check( A, adat );
  check( B, bdat );

  A.normalize(B);

  EXPECT_DOUBLE_EQ( D_ONE, A.dot( A ) );
  }

}


} // end namespace


// =======================================================================================
// **                              U T E S T _ V E C T O R                              **
// ======================================================================== END FILE =====
