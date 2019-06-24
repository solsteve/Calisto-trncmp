// ====================================================================== BEGIN FILE =====
// **                           U T E S T _ A R R A Y F U N C                           **
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
/** @brief  Automated testing for array functions.
 *  @file   utest_arrayfunc.cc
 *  @author Stephen W. Soliday
 *  @date   2019-May-08
 *
 *  Provides automated testing for array functions.
 */
// =======================================================================================


#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {


#define LOOP_TEST( _a, _n, _v ) {               \
    for ( size_t _i=0; _i<_n; _i++ ) {          \
      EXPECT_EQ( _v, _a[_i] );                  \
    }                                           \
  }


#define DLOOP_TEST( _a, _n, _v ) {              \
    for ( size_t _i=0; _i<_n; _i++ ) {          \
      EXPECT_DOUBLE_EQ( _v, _a[_i] );           \
    }                                           \
  }


#define FLOOP_TEST( _a, _n, _v ) {              \
    for ( size_t _i=0; _i<_n; _i++ ) {          \
      EXPECT_FLOAT_EQ( _v, _a[_i] );            \
    }                                           \
  }


#define LOOP_2D_TEST( _a, _nr, _nc, _v ) {      \
    for ( size_t _i=0; _i<_nr; _i++ ) {         \
      for ( size_t _j=0; _j<_nc; _j++ ) {       \
        EXPECT_EQ( _v, _a[_i][_j] );            \
      }                                         \
    }                                           \
  }


#define DLOOP_2D_TEST( _a, _nr, _nc, _v ) {     \
    for ( size_t _i=0; _i<_nr; _i++ ) {         \
      for ( size_t _j=0; _j<_nc; _j++ ) {       \
        EXPECT_DOUBLE_EQ( _v, _a[_i][_j] );     \
      }                                         \
    }                                           \
  }


#define FLOOP_2D_TEST( _a, _nr, _nc, _v ) {     \
    for ( size_t _i=0; _i<_nr; _i++ ) {         \
      for ( size_t _j=0; _j<_nc; _j++ ) {       \
        EXPECT_FLOAT_EQ( _v, _a[_i][_j] );      \
      }                                         \
    }                                           \
  }


template<class T>
T** make_array( size_t nr, size_t nc, T initval ) {
  T** temp = new T*[nr];
  for ( size_t i=0; i<nr; i++ ) {
    temp[i] = new T[nc];
    for ( size_t j=0; j<nc; j++ ) {
      temp[i][j] = initval;
    }
  }
  return temp;
}


template<class T>
void free_array( T** ary, size_t nr ) {
  for ( size_t i=0; i<nr; i++ ) {
    delete ary[i];
  }
  delete ary;
}


// =======================================================================================

TEST(test_zero1D, Positive) {
  const size_t N = 20;
  
  real8_t   R8[N];
  real4_t   R4[N];
  int32_t   I32[N];
  int16_t   I16[N];
  int8_t    I8[N];
  u_int32_t U32[N];
  u_int16_t U16[N];
  u_int8_t  U8[N];

  zero(R8,  N, (real8_t  )3);
  zero(R4,  N, (real4_t  )3);
  zero(I32, N, (int32_t  )3);
  zero(I16, N, (int16_t  )3);
  zero(I8,  N, (int8_t   )3);
  zero(U32, N, (u_int32_t)3);
  zero(U16, N, (u_int16_t)3);
  zero(U8,  N, (u_int8_t )3);

  DLOOP_TEST(R8, N, (real8_t)3);
  FLOOP_TEST(R4, N, (real4_t)3);

  LOOP_TEST(I32, N, (int32_t)3);
  LOOP_TEST(I16, N, (int16_t)3);
  LOOP_TEST(I8,  N, (int8_t)3);

  LOOP_TEST(U32, N, (u_int32_t)3);
  LOOP_TEST(U16, N, (u_int16_t)3);
  LOOP_TEST(U8,  N, (u_int8_t)3);

  zero(R8,  N);
  zero(R4,  N);
  zero(I32, N);
  zero(I16, N);
  zero(I8,  N);
  zero(U32, N);
  zero(U16, N);
  zero(U8,  N);

  DLOOP_TEST(R8, N, (real8_t)0);
  FLOOP_TEST(R4, N, (real4_t)0);

  LOOP_TEST(I32, N, (int32_t)0);
  LOOP_TEST(I16, N, (int16_t)0);
  LOOP_TEST(I8,  N, (int8_t)0);

  LOOP_TEST(U32, N, (u_int32_t)0);
  LOOP_TEST(U16, N, (u_int16_t)0);
  LOOP_TEST(U8,  N, (u_int8_t)0);
}


// =======================================================================================


TEST(test_zero2D, Positive) {
  const size_t NR = 17;
  const size_t NC = 23;

  real8_t   ** R8 = make_array( NR, NC, (real8_t)3 );
  real4_t   ** R4 = make_array( NR, NC, (real4_t)3 );
  int32_t   ** I4 = make_array( NR, NC, (int32_t)3 );
  int16_t   ** I2 = make_array( NR, NC, (int16_t)3 );
  int8_t    ** I1 = make_array( NR, NC, (int8_t)3 );
  u_int32_t ** U4 = make_array( NR, NC, (u_int32_t)3 );
  u_int16_t ** U2 = make_array( NR, NC, (u_int16_t)3 );
  u_int8_t  ** U1 = make_array( NR, NC, (u_int8_t)3 );

  DLOOP_2D_TEST( R8, NR, NC, (real8_t)3 );
  FLOOP_2D_TEST( R4, NR, NC, (real4_t)3 );
  LOOP_2D_TEST(  I4, NR, NC, (int32_t)3 );
  LOOP_2D_TEST(  I2, NR, NC, (int16_t)3 );
  LOOP_2D_TEST(  I1, NR, NC, (int8_t)3 );
  LOOP_2D_TEST(  U4, NR, NC, (u_int32_t)3 );
  LOOP_2D_TEST(  U2, NR, NC, (u_int16_t)3 );
  LOOP_2D_TEST(  U1, NR, NC, (u_int8_t)3 );

  zero( R8, NR, NC );
  zero( R4, NR, NC );
  zero( I4, NR, NC );
  zero( I2, NR, NC );
  zero( I1, NR, NC );
  zero( U4, NR, NC );
  zero( U2, NR, NC );
  zero( U1, NR, NC );

  DLOOP_2D_TEST( R8, NR, NC, (real8_t)0 );
  FLOOP_2D_TEST( R4, NR, NC, (real4_t)0 );
  LOOP_2D_TEST(  I4, NR, NC, (int32_t)0 );
  LOOP_2D_TEST(  I2, NR, NC, (int16_t)0 );
  LOOP_2D_TEST(  I1, NR, NC, (int8_t)0 );
  LOOP_2D_TEST(  U4, NR, NC, (u_int32_t)0 );
  LOOP_2D_TEST(  U2, NR, NC, (u_int16_t)0 );
  LOOP_2D_TEST(  U1, NR, NC, (u_int8_t)0 );
  
      
  free_array( R8, NR );
  free_array( R4, NR );
  free_array( I4, NR );
  free_array( I2, NR );
  free_array( I1, NR );
  free_array( U4, NR );
  free_array( U2, NR );
  free_array( U1, NR );
}


// =======================================================================================


TEST( test_count, Positive ) {
  real8_t R[] = { 1.1, 2.2, 1.1, 3.3, 4.4, 1.1, 1.1 };
  int32_t A[] = { 1,2,3,4,3,4,5,6,3,7,8 };

  size_t n = sizeof(R)/sizeof(R[0]);
  size_t c = count( 1.1, R, n );
  EXPECT_EQ( 4, c );

  n = sizeof(A)/sizeof(A[0]);
  c = count( 3, A, n );
  EXPECT_EQ( 3, c );
}


// =======================================================================================


TEST( test_isin, Positive ) {
  real8_t R[] = { 1.1, 2.2, 1.1, 3.3, 4.4, 1.1, 1.1 };
  int32_t A[] = { 1,2,3,4,3,4,5,6,3,7,8 };

  size_t n = sizeof(R)/sizeof(R[0]);
  EXPECT_TRUE(  isIn( 1.1, R, n ) );

  n = sizeof(A)/sizeof(A[0]);
  EXPECT_TRUE(  isIn( 3, A, n ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_isin, Negative ) {
  real8_t R[] = { 1.1, 2.2, 1.1, 3.3, 4.4, 1.1, 1.1 };
  int32_t A[] = { 1,2,3,4,3,4,5,6,3,7,8 };

  size_t n = sizeof(R)/sizeof(R[0]);
  EXPECT_FALSE( isIn( 2.3, R, n ) );

  n = sizeof(A)/sizeof(A[0]);
  EXPECT_FALSE( isIn( 9, A, n ) );
}


// =======================================================================================


TEST( test_findin, Positive ) {
  real8_t R[] = { 6.91, 3.49, 2.42, 3.75, 6.78, 2.34, 8.19, 1.75, 8.56 };
  int32_t A[] = { 6, 3, 4, 8, 1, 5, 9, 7, 2 };
  size_t n = sizeof(R)/sizeof(R[0]);
  EXPECT_EQ( 3, findIn( 3.75, R, n ) );

  n = sizeof(A)/sizeof(A[0]);
  EXPECT_EQ( 6, findIn( 9, A, n ) );
}


TEST( test_findin, Negative ) {
  real8_t R[] = { 6.91, 3.49, 2.42, 3.75, 6.78, 2.34, 8.19, 1.75, 8.56 };
  int32_t A[] = { 6, 3, 4, 8, 1, 5, 9, 7, 2 };
  size_t n = sizeof(R)/sizeof(R[0]);
  EXPECT_EQ( -1, findIn( 1.11, R, n ) );

  n = sizeof(A)/sizeof(A[0]);
  EXPECT_EQ( -1, findIn( 10, A, n ) );
}


// =======================================================================================


TEST( test_minmax, Positive ) {
  real8_t R[] = { 6.91, 3.49, 2.42, 3.75, 6.78, 2.34, 8.19, 1.75, 8.56 };
  int32_t A[] = { 6, 3, 4, 8, 1, 5, 9, 7, 2 };
  size_t n = sizeof(R)/sizeof(R[0]);
  EXPECT_DOUBLE_EQ( 1.75, Min( R, n ) );
  EXPECT_DOUBLE_EQ( 8.56, Max( R, n ) );

  n = sizeof(A)/sizeof(A[0]);
  EXPECT_EQ( 1, Min( A, n ) );
  EXPECT_EQ( 9, Max( A, n ) );

  real8_t* X = (real8_t*)0;
  try {
    real8_t dummy = Min( X, n );
    std::cout << dummy << std:: endl;
  } catch( std::invalid_argument& e ) {
    std::cout << "Correct exception caught" << std:: endl;
  }
}


// =======================================================================================


TEST( test_minmax_index, Positive ) {
  real8_t R[] = { 6.91, 3.49, 2.42, 3.75, 6.78, 2.34, 8.19, 1.75, 8.56 };
  int32_t A[] = { 6, 3, 4, 8, 1, 5, 9, 7, 2 };
  size_t n = sizeof(R)/sizeof(R[0]);
  EXPECT_EQ( 7, MinLoc( R, n ) );
  EXPECT_EQ( 8, MaxLoc( R, n ) );

  n = sizeof(A)/sizeof(A[0]);
  EXPECT_EQ( 4, MinLoc( A, n ) );
  EXPECT_EQ( 6, MaxLoc( A, n ) );

  real8_t* X = (real8_t*)0;
  try {
    size_t dummy = MinLoc( X, n );
    std::cout << dummy << std:: endl;
  } catch( std::invalid_argument& e ) {
    std::cout << "Correct exception caught" << std:: endl;
  }
}


} // end namespace


// =======================================================================================
// **                           U T E S T _ A R R A Y F U N C                           **
// ======================================================================== END FILE =====
