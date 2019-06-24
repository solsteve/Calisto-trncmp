// ====================================================================== BEGIN FILE =====
// **                           U T E S T _ S U M M A T I O N                           **
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
/** @brief  Automated testing for summation.
 *  @file   utest_summation.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Apr-26
 *
 *  Provides automated testing for summation.
 */
// =======================================================================================


#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {


// =======================================================================================

TEST( test_sum8, Positive ) {
  const size_t N = 100;
  real8_t cons[N];
  real8_t even[N];
  real8_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (real8_t)(i);
    even[k] = (real8_t)(2*i);
    odd[k]  = (real8_t)(2*i + 1);
  }

  real8_t tc = (real8_t)(N*(N+1)/2);
  real8_t te = (real8_t)(N*(N+1));
  real8_t to = (real8_t)(N*(N+2));

  EXPECT_DOUBLE_EQ( tc, sum( cons, N ) );
  EXPECT_DOUBLE_EQ( te, sum( even, N ) );
  EXPECT_DOUBLE_EQ( to, sum( odd,  N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sum4, Positive ) {
  const size_t N = 100;
  real4_t cons[N];
  real4_t even[N];
  real4_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (real4_t)(i);
    even[k] = (real4_t)(2*i);
    odd[k]  = (real4_t)(2*i + 1);
  }

  real4_t tc = (real4_t)(N*(N+1)/2);
  real4_t te = (real4_t)(N*(N+1));
  real4_t to = (real4_t)(N*(N+2));

  EXPECT_FLOAT_EQ( tc, sum( cons, N ) );
  EXPECT_FLOAT_EQ( te, sum( even, N ) );
  EXPECT_FLOAT_EQ( to, sum( odd,  N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sum32, Positive ) {
  const size_t N = 100;
  int32_t cons[N];
  int32_t even[N];
  int32_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (int32_t)(i);
    even[k] = (int32_t)(2*i);
    odd[k]  = (int32_t)(2*i + 1);
  }

  int32_t tc = (int32_t)(N*(N+1)/2);
  int32_t te = (int32_t)(N*(N+1));
  int32_t to = (int32_t)(N*(N+2));

  EXPECT_EQ( tc, sum( cons, N ) );
  EXPECT_EQ( te, sum( even, N ) );
  EXPECT_EQ( to, sum( odd,  N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sum64, Positive ) {
  const size_t N = 100;
  int64_t cons[N];
  int64_t even[N];
  int64_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (int64_t)(i);
    even[k] = (int64_t)(2*i);
    odd[k]  = (int64_t)(2*i + 1);
  }

  int64_t tc = (int64_t)(N*(N+1)/2);
  int64_t te = (int64_t)(N*(N+1));
  int64_t to = (int64_t)(N*(N+2));

  EXPECT_EQ( tc, sum( cons, N ) );
  EXPECT_EQ( te, sum( even, N ) );
  EXPECT_EQ( to, sum( odd,  N ) );
}


// =======================================================================================


TEST( test_sumsq8, Positive ) {
  const size_t N = 100;
  real8_t cons[N];
  real8_t even[N];
  real8_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (real8_t)(i);
    even[k] = (real8_t)(2*i);
    odd[k]  = (real8_t)(2*i + 1);
  }

  real8_t tc = (real8_t)(N*(N+1)*(2*N+1)/6);
  real8_t te = (real8_t)(2*N*(N+1)*(2*N+1)/3);
  real8_t to = (real8_t)(N*(4*N*(N + 3) + 11)/3);

  EXPECT_DOUBLE_EQ( tc, sumsq( cons, N ) );
  EXPECT_DOUBLE_EQ( te, sumsq( even, N ) );
  EXPECT_DOUBLE_EQ( to, sumsq( odd,  N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sumsq4, Positive ) {
  const size_t N = 100;
  real4_t cons[N];
  real4_t even[N];
  real4_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (real4_t)(i);
    even[k] = (real4_t)(2*i);
    odd[k]  = (real4_t)(2*i + 1);
  }

  real4_t tc = (real4_t)(N*(N+1)*(2*N+1)/6);
  real4_t te = (real4_t)(2*N*(N+1)*(2*N+1)/3);
  real4_t to = (real4_t)(N*(4*N*(N + 3) + 11)/3);

  EXPECT_FLOAT_EQ( tc, sumsq( cons, N ) );
  EXPECT_FLOAT_EQ( te, sumsq( even, N ) );
  EXPECT_FLOAT_EQ( to, sumsq( odd,  N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sumsq32, Positive ) {
  const size_t N = 100;
  int32_t cons[N];
  int32_t even[N];
  int32_t odd[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    cons[k] = (int32_t)(i);
    even[k] = (int32_t)(2*i);
    odd[k]  = (int32_t)(2*i + 1);
  }

  int32_t tc = (int32_t)(N*(N+1)*(2*N+1)/6);
  int32_t te = (int32_t)(2*N*(N+1)*(2*N+1)/3);
  int32_t to = (int32_t)(N*(4*N*(N + 3) + 11)/3);

  EXPECT_EQ( tc, sumsq( cons, N ) );
  EXPECT_EQ( te, sumsq( even, N ) );
  EXPECT_EQ( to, sumsq( odd,  N ) );
}


// =======================================================================================


TEST( test_wsum8, Positive ) {
  const size_t N = 100;
  real8_t W1[N];
  real8_t X1[N];
  real8_t W2[N];
  real8_t X2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    W1[k] = (real8_t)(3*i-1);
    X1[k] = (real8_t)(2*i+5);
    W2[k] = (real8_t)(2*i+7);
    X2[k] = (real8_t)(5*i-3);
  }

  real8_t t1 = (real8_t)(N*(N*(4*N+19) + 5)/2);
  real8_t t2 = (real8_t)(N*(N*(20*N+117)-29)/6);

  EXPECT_DOUBLE_EQ( t1, wsum( W1, X1, N ) );
  EXPECT_DOUBLE_EQ( t2, wsum( W2, X2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_wsum4, Positive ) {
  const size_t N = 100;
  real4_t W1[N];
  real4_t X1[N];
  real4_t W2[N];
  real4_t X2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    W1[k] = (real4_t)(3*i-1);
    X1[k] = (real4_t)(2*i+5);
    W2[k] = (real4_t)(2*i+7);
    X2[k] = (real4_t)(5*i-3);
  }

  real4_t t1 = (real4_t)(N*(N*(4*N+19) + 5)/2);
  real4_t t2 = (real4_t)(N*(N*(20*N+117)-29)/6);

  EXPECT_FLOAT_EQ( t1, wsum( W1, X1, N ) );
  EXPECT_FLOAT_EQ( t2, wsum( W2, X2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_wsum32, Positive ) {
  const size_t N = 100;
  int32_t W1[N];
  int32_t X1[N];
  int32_t W2[N];
  int32_t X2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    W1[k] = (int32_t)(3*i-1);
    X1[k] = (int32_t)(2*i+5);
    W2[k] = (int32_t)(2*i+7);
    X2[k] = (int32_t)(5*i-3);
  }

  int32_t t1 = (int32_t)(N*(N*(4*N+19) + 5)/2);
  int32_t t2 = (int32_t)(N*(N*(20*N+117)-29)/6);

  EXPECT_EQ( t1, wsum( W1, X1, N ) );
  EXPECT_EQ( t2, wsum( W2, X2, N ) );
}


// =======================================================================================


TEST( test_sumdif8, Positive ) {
  const size_t N = 100;
  real8_t X1[N];
  real8_t X2[N];
  real8_t Y1[N];
  real8_t Y2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    X1[k] = (real8_t)(3*i-1);
    Y1[k] = (real8_t)(2*i+5);
    X2[k] = (real8_t)(5*i-3);
    Y2[k] = (real8_t)(2*i+7);
  }

  real8_t t1 = (real8_t)(N*(N-11)/2);
  real8_t t2 = (real8_t)(N*(3*N-17)/2);

  EXPECT_DOUBLE_EQ( t1, sumDiff( X1, Y1, N ) );
  EXPECT_DOUBLE_EQ( t2, sumDiff( X2, Y2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sumdif4, Positive ) {
  const size_t N = 100;
  real4_t X1[N];
  real4_t X2[N];
  real4_t Y1[N];
  real4_t Y2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    X1[k] = (real4_t)(3*i-1);
    Y1[k] = (real4_t)(2*i+5);
    X2[k] = (real4_t)(5*i-3);
    Y2[k] = (real4_t)(2*i+7);
  }

  real4_t t1 = (real4_t)(N*(N-11)/2);
  real4_t t2 = (real4_t)(N*(3*N-17)/2);

  EXPECT_FLOAT_EQ( t1, sumDiff( X1, Y1, N ) );
  EXPECT_FLOAT_EQ( t2, sumDiff( X2, Y2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sumdif32, Positive ) {
  const size_t N = 100;
  int32_t X1[N];
  int32_t X2[N];
  int32_t Y1[N];
  int32_t Y2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    X1[k] = (int32_t)(3*i-1);
    Y1[k] = (int32_t)(2*i+5);
    X2[k] = (int32_t)(5*i-3);
    Y2[k] = (int32_t)(2*i+7);
  }

  int32_t t1 = (int32_t)(N*(N-11)/2);
  int32_t t2 = (int32_t)(N*(3*N-17)/2);

  EXPECT_EQ( t1, sumDiff( X1, Y1, N ) );
  EXPECT_EQ( t2, sumDiff( X2, Y2, N ) );
}


// =======================================================================================


TEST( test_sumsqdif8, Positive ) {
  const size_t N = 100;
  real8_t X1[N];
  real8_t Y1[N];
  real8_t X2[N];
  real8_t Y2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    X1[k] = (real8_t)(2*i+5);
    Y1[k] = (real8_t)(3*i-1);
    X2[k] = (real8_t)(2*i+7);
    Y2[k] = (real8_t)(5*i-3);
  }

  real8_t t1 = (real8_t)(N*(N*(2*N-33)+181)/6);
  real8_t t2 = (real8_t)(N*(N*(6*N-51)+143)/2);

  EXPECT_DOUBLE_EQ( t1, sumsqDiff( X1, Y1, N ) );
  EXPECT_DOUBLE_EQ( t2, sumsqDiff( X2, Y2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sumsqdif4, Positive ) {
  const size_t N = 100;
  real4_t X1[N];
  real4_t Y1[N];
  real4_t X2[N];
  real4_t Y2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    X1[k] = (real4_t)(2*i+5);
    Y1[k] = (real4_t)(3*i-1);
    X2[k] = (real4_t)(2*i+7);
    Y2[k] = (real4_t)(5*i-3);
  }

  real4_t t1 = (real4_t)(N*(N*(2*N-33)+181)/6);
  real4_t t2 = (real4_t)(N*(N*(6*N-51)+143)/2);

  EXPECT_DOUBLE_EQ( t1, sumsqDiff( X1, Y1, N ) );
  EXPECT_DOUBLE_EQ( t2, sumsqDiff( X2, Y2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_sumsqdif32, Positive ) {
  const size_t N = 100;
  int32_t X1[N];
  int32_t Y1[N];
  int32_t X2[N];
  int32_t Y2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    X1[k] = (int32_t)(2*i+5);
    Y1[k] = (int32_t)(3*i-1);
    X2[k] = (int32_t)(2*i+7);
    Y2[k] = (int32_t)(5*i-3);
  }

  int32_t t1 = (int32_t)(N*(N*(2*N-33)+181)/6);
  int32_t t2 = (int32_t)(N*(N*(6*N-51)+143)/2);

  EXPECT_DOUBLE_EQ( t1, sumsqDiff( X1, Y1, N ) );
  EXPECT_DOUBLE_EQ( t2, sumsqDiff( X2, Y2, N ) );
}


// =======================================================================================


TEST( test_com8, Positive ) {
  const size_t N = 100;
  real8_t W1[N];
  real8_t X1[N];
  real8_t W2[N];
  real8_t X2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    W1[k] = (real8_t)(2*i+5);
    X1[k] = (real8_t)(3*i-1);
    W2[k] = (real8_t)(2*i+7);
    X2[k] = (real8_t)(5*i-3);
  }

  real8_t t1 = ((real8_t)(N*(4*N+19) + 5)) / ((real8_t)(2*(N+6)));
  real8_t t2 = ((real8_t)(N*(20*N+117) - 29)) / ((real8_t)(6*(N+8)));

  EXPECT_DOUBLE_EQ( t1, centerOfMass( W1, X1, N ) );
  EXPECT_DOUBLE_EQ( t2, centerOfMass( W2, X2, N ) );
}


// ---------------------------------------------------------------------------------------


TEST( test_com4, Positive ) {
  const size_t N = 100;
  real4_t W1[N];
  real4_t X1[N];
  real4_t W2[N];
  real4_t X2[N];

  for ( size_t k=0; k<N; k++ ) {
    size_t i = k+1;
    W1[k] = (real4_t)(2*i+5);
    X1[k] = (real4_t)(3*i-1);
    W2[k] = (real4_t)(2*i+7);
    X2[k] = (real4_t)(5*i-3);
  }

  real4_t t1 = ((real4_t)(N*(4*N+19) + 5)) / ((real4_t)(2*(N+6)));
  real4_t t2 = ((real4_t)(N*(20*N+117) - 29)) / ((real4_t)(6*(N+8)));

  EXPECT_DOUBLE_EQ( t1, centerOfMass( W1, X1, N ) );
  EXPECT_DOUBLE_EQ( t2, centerOfMass( W2, X2, N ) );
}

TEST( test_rad_com8, Positive ) {
  real8_t W[] = {  3.0,  6.0,  9.0,  8.0 };
  real8_t X[] = { 28.0, 26.0, 20.0, 19.0 };

  for ( size_t i=0; i<4; i++ ) {
    X[i] = X[i] * D_2PI / 24.0;
  }

  real8_t test   = centerOfMass( W, X, 4 );
  //real8_t rtest  = centerOfMassRad( W, X, 4 );
  //real8_t target = 22.0 * D_2PI / 24.0;

  EXPECT_DOUBLE_EQ( 22.0,  test * 24.0 / D_2PI );
  //EXPECT_DOUBLE_EQ( target , rtest );
}

} // end namespace


// =======================================================================================
// **                           U T E S T _ S U M M A T I O N                           **
// ======================================================================== END FILE =====
