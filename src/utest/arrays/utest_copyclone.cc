// ====================================================================== BEGIN FILE =====
// **                           U T E S T _ C O P Y C L O N E                           **
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
/** @brief  Automated testing for copy and clone.
 *  @file   utest_copyclone.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-23
 *
 *  Provides automated testing for copy and clone.
 */
// =======================================================================================


#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {

TEST( test_cc_char, Positive ) {
  const char *original = "heather";
  char* test = clone( original );
  EXPECT_STREQ( original, test );
  delete test;

  test = clone( "Rebekah" );
  EXPECT_STREQ( "Rebekah", test );
  delete test;
}

// =======================================================================================

TEST( test_cc_oo, Positive ) {

  const int32_t M = 100000;
  const int32_t N = 1000;
  const int32_t K = 500;
  const int32_t S = 100;
  const int32_t D = 200;
  
  int32_t* A = new int32_t[ N ];
  int32_t* B = new int32_t[ N ];

  A[0] = 1;
  A[1] = 1;
  B[0] = 7;
  B[1] = 11;

  for ( int32_t i=2; i<N; i++ ) {
    A[i] = (A[i-1] + A[i-2]) % M;
    B[i] = (B[i-1] + B[i-2]) % M;
  }

  int32_t count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  copy( B, D, A, S, K );

  count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  count = 0;
  for ( int32_t i=0; i<K; i++ ) {
    if ( A[i+S] == B[i+D] ) { count++; }
  }
  EXPECT_EQ( K, count );
    
  delete B;
  delete A;
}

// ---------------------------------------------------------------------------------------

TEST( test_cc_xo, Positive ) {

  const int32_t M = 100000;
  const int32_t N = 1000;
  const int32_t K = 500;
  const int32_t S = 100;
  
  int32_t* A = new int32_t[ N ];
  int32_t* B = new int32_t[ N ];

  A[0] = 1;
  A[1] = 1;
  B[0] = 7;
  B[1] = 11;

  for ( int32_t i=2; i<N; i++ ) {
    A[i] = (A[i-1] + A[i-2]) % M;
    B[i] = (B[i-1] + B[i-2]) % M;
  }

  int32_t count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  copy( B, A, S, K );

  count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  count = 0;
  for ( int32_t i=0; i<K; i++ ) {
    if ( A[i+S] == B[i] ) { count++; }
  }
  EXPECT_EQ( K, count );
    
  delete B;
  delete A;
}

// ---------------------------------------------------------------------------------------

TEST( test_cc_ox, Positive ) {

  const int32_t M = 100000;
  const int32_t N = 1000;
  const int32_t K = 500;
  const int32_t D = 200;
  
  int32_t* A = new int32_t[ N ];
  int32_t* B = new int32_t[ N ];

  A[0] = 1;
  A[1] = 1;
  B[0] = 7;
  B[1] = 11;

  for ( int32_t i=2; i<N; i++ ) {
    A[i] = (A[i-1] + A[i-2]) % M;
    B[i] = (B[i-1] + B[i-2]) % M;
  }

  int32_t count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  copy( B, D, A, K );

  count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  count = 0;
  for ( int32_t i=0; i<K; i++ ) {
    if ( A[i] == B[i+D] ) { count++; }
  }
  EXPECT_EQ( K, count );
    
  delete B;
  delete A;
}

// ---------------------------------------------------------------------------------------

TEST( test_cc_xx, Positive ) {

  const int32_t M = 100000;
  const int32_t N = 1000;
  
  int32_t* A = new int32_t[ N ];
  int32_t* B = new int32_t[ N ];

  A[0] = 1;
  A[1] = 1;
  B[0] = 7;
  B[1] = 11;

  for ( int32_t i=2; i<N; i++ ) {
    A[i] = (A[i-1] + A[i-2]) % M;
    B[i] = (B[i-1] + B[i-2]) % M;
  }

  int32_t count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_NE( N, count );
  
  copy( B, A, N );

  count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  EXPECT_EQ( N, count );
    
  delete B;
  delete A;
}

// =======================================================================================

TEST( test_cl_o, Positive ) {

  const int32_t M = 100000;
  const int32_t N = 1000;
  const int32_t K = 500;
  const int32_t S = 100;
  
  int32_t* A = new int32_t[ N ];

  A[0] = 1;
  A[1] = 1;

  for ( int32_t i=2; i<N; i++ ) {
    A[i] = (A[i-1] + A[i-2]) % M;
  }

  int32_t* B = clone( A, S, K );

  int32_t count = 0;
  for ( int32_t i=0; i<K; i++ ) {
    if ( A[i+S] == B[i] ) { count++; }
  }
  
  EXPECT_EQ( K, count );
    
  delete B;
  delete A;
}

// ---------------------------------------------------------------------------------------

TEST( test_cl, Positive ) {

  const int32_t M = 100000;
  const int32_t N = 1000;
  
  int32_t* A = new int32_t[ N ];

  A[0] = 1;
  A[1] = 1;

  for ( int32_t i=2; i<N; i++ ) {
    A[i] = (A[i-1] + A[i-2]) % M;
  }

  int32_t* B = clone( A, N );

  int32_t count = 0;
  for ( int32_t i=0; i<N; i++ ) {
    if ( A[i] == B[i] ) { count++; }
  }
  
  EXPECT_EQ( N, count );
    
  delete B;
  delete A;
}



} // end namespace


// =======================================================================================
// **                           U T E S T _ C O P Y C L O N E                           **
// ======================================================================== END FILE =====
