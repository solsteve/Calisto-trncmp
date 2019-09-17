// ====================================================================== BEGIN FILE =====
// **                                U T E S T _ F S E T                                **
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
/** @brief  Automated testing for fuzzy::Set class methods.
 *  @file   utest_fset.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-15
 *
 *  Provides automated testing for the fuzzy::Set class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <fuzzy/LeftTrapezoidSet.hh>
#include <fuzzy/TriangleSet.hh>
#include <fuzzy/RightTrapezoidSet.hh>
#include <gtest/gtest.h>

namespace {


// =======================================================================================
TEST(test_fset_create, empty ) {
  // -------------------------------------------------------------------------------------
  fuzzy::LeftTrapezoidSet L0;

  EXPECT_DOUBLE_EQ( -D_HALF, L0.getLeft() );
  EXPECT_DOUBLE_EQ(  D_ZERO, L0.getCenter() );
  EXPECT_DOUBLE_EQ(  D_ONE,  L0.getRight() );

  fuzzy::TriangleSet T0;

  EXPECT_DOUBLE_EQ( -D_ONE,  T0.getLeft() );
  EXPECT_DOUBLE_EQ(  D_ZERO, T0.getCenter() );
  EXPECT_DOUBLE_EQ(  D_ONE,  T0.getRight() );

  fuzzy::RightTrapezoidSet R0;

  EXPECT_DOUBLE_EQ( -D_ONE,  R0.getLeft() );
  EXPECT_DOUBLE_EQ(  D_ZERO, R0.getCenter() );
  EXPECT_DOUBLE_EQ(  D_HALF, R0.getRight() );
}


// =======================================================================================
TEST(test_fset_create, init ) {
  // -------------------------------------------------------------------------------------
  fuzzy::LeftTrapezoidSet L( 3.0, 5.0 );

  EXPECT_DOUBLE_EQ( 2.0, L.getLeft() );
  EXPECT_DOUBLE_EQ( 3.0, L.getCenter() );
  EXPECT_DOUBLE_EQ( 5.0, L.getRight() );

  fuzzy::TriangleSet T( 4.0, 6.0, 9.0 );

  EXPECT_DOUBLE_EQ( 4.0, T.getLeft() );
  EXPECT_DOUBLE_EQ( 6.0, T.getCenter() );
  EXPECT_DOUBLE_EQ( 9.0, T.getRight() );

  fuzzy::RightTrapezoidSet R( 8.0, 12.0 );

  EXPECT_DOUBLE_EQ( 8.0,  R.getLeft() );
  EXPECT_DOUBLE_EQ( 12.0, R.getCenter() );
  EXPECT_DOUBLE_EQ( 14.0, R.getRight() );
}


// =======================================================================================
TEST(test_fset_mu, left_trap ) {
  // -------------------------------------------------------------------------------------

  real8_t X[] = { 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00 };
  real8_t M[] = { 1.00, 1.00, 0.75, 0.50, 0.25, 0.00, 0.00 };

  int32_t n = sizeof(X) / sizeof(X[0]);

  fuzzy::LeftTrapezoidSet L( X[1], X[n-2] );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( M[i], L.mu(X[i]) );
  }
}


// =======================================================================================
TEST(test_fset_mu, triangle ) {
  // -------------------------------------------------------------------------------------

  real8_t X[] = { 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 8.00, 10.00, 12.00, 14.00, 16.00 };
  real8_t M[] = { 0.00, 0.00, 0.25, 0.50, 0.75, 1.00, 0.75,  0.50,  0.25,  0.00,  0.00 };

  int32_t n = sizeof(X) / sizeof(X[0]);

  fuzzy::TriangleSet T( 2.0, 6.0, 14.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( M[i], T.mu(X[i]) );
  }
}

  // =======================================================================================
TEST(test_fset_mu, right_trap ) {
  // -------------------------------------------------------------------------------------

  real8_t X[] = { 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00 };
  real8_t M[] = { 0.00, 0.00, 0.25, 0.50, 0.75, 1.00, 1.00 };

  int32_t n = sizeof(X) / sizeof(X[0]);

  fuzzy::RightTrapezoidSet R( X[1], X[n-2] );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( M[i], R.mu(X[i]) );
  }
}

// =======================================================================================
TEST(test_fset_area, left_trap ) {
  // -------------------------------------------------------------------------------------

  real8_t D[] = { 1.000, 0.750, 0.500, 0.250, 0.000 };
  real8_t A[] = { 4.000, 3.375, 2.500, 1.375, 0.000 };

  int32_t n = sizeof(D) / sizeof(D[0]);

  fuzzy::LeftTrapezoidSet L( 5.0, 9.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( A[i], L.area(D[i]) );
  }
}


// =======================================================================================
TEST(test_fset_area, triangle ) {
  // -------------------------------------------------------------------------------------

  real8_t D[] = { 1.000, 0.750, 0.500, 0.250, 0.000 };
  real8_t A[] = { 6.000, 5.625, 4.500, 2.625, 0.000 };

  int32_t n = sizeof(D) / sizeof(D[0]);

  fuzzy::TriangleSet T( 3.0, 11.0, 15.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( A[i], T.area(D[i]) );
  }
}


// =======================================================================================
TEST(test_fset_area, right_trap ) {
  // -------------------------------------------------------------------------------------

  real8_t D[] = { 1.00, 0.75, 0.50, 0.25, 0.00 };
  real8_t A[] = { 8.00, 6.75, 5.00, 2.75, 0.00 };

  int32_t n = sizeof(D) / sizeof(D[0]);

  fuzzy::RightTrapezoidSet R( 7.0, 15.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( A[i], R.area(D[i]) );
  }
}


// =======================================================================================
TEST(test_fset_coa, left_trap ) {
  // -------------------------------------------------------------------------------------

  real8_t D[]  = {  1.000, 0.750,  0.500,  0.250, 0.000 };
  real8_t Cn[] = { 13.000, 7.000, 38.000, 91.000, 3.000 };
  real8_t Cd[] = {  6.000, 3.000, 15.000, 33.000, 1.000 };

  int32_t n = sizeof(D) / sizeof(D[0]);

  fuzzy::LeftTrapezoidSet L( 2.0, 6.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( Cn[i]/Cd[i], L.coa(D[i]) );
  }
}


// =======================================================================================
TEST(test_fset_coa, triangle ) {
  // -------------------------------------------------------------------------------------

  real8_t D[]  = {  1.000,  0.750,  0.500,   0.250, 0.000 };
  real8_t Cn[] = { 17.000, 57.000, 52.000, 247.000, 6.000 };
  real8_t Cd[] = {  3.000, 10.000,  9.000,  42.000, 1.000 };

  int32_t n = sizeof(D) / sizeof(D[0]);

  fuzzy::TriangleSet T( 3.0, 5.0, 9.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( Cn[i]/Cd[i], T.coa(D[i]) );
  }
}


// =======================================================================================
TEST(test_fset_coa, right_trap ) {
  // -------------------------------------------------------------------------------------

  real8_t D[]  = {  1.000,  0.750,  0.500,   0.250, 0.000 };
  real8_t Cn[] = { 41.000, 20.000, 97.000, 206.000, 6.000 };
  real8_t Cd[] = {  6.000,  3.000, 15.000,  33.000, 1.000 };

  int32_t n = sizeof(D) / sizeof(D[0]);

  fuzzy::RightTrapezoidSet R( 3.0, 7.0 );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( Cn[i]/Cd[i], R.coa(D[i]) );
  }
}

// =======================================================================================
TEST(test_fset_storage, load_store ) {
  // -------------------------------------------------------------------------------------
  fuzzy::LeftTrapezoidSet  L1( 7.0, 11.0 );
  fuzzy::TriangleSet       T1( 7.0, 11.0, 15.0 );
  fuzzy::RightTrapezoidSet R1( 11.0, 15.0 );
  real8_t check[] = {  7.0, 11.0, 7.0, 11.0, 15.0, 11.0, 15.0 };
  real8_t buffer[10];

  for ( int32_t i=0; i<10; i++ ) {
    buffer[i] = (real8_t)i;
  }
  
  real8_t* P = buffer;
  
  P = L1.store( P );
  P = T1.store( P );
  P = R1.store( P );

  EXPECT_DOUBLE_EQ( 7.0, *P );

  for ( int32_t i=0; i<7; i++ ) {
    EXPECT_DOUBLE_EQ( check[i], buffer[i] );
  }

}

} // end namespace


// =======================================================================================
// **                                U T E S T _ F S E T                                **
// ======================================================================== END FILE =====
