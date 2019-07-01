// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ V E C T O R 2 D                            **
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
/** @brief  Automated testing for Vector2D class and methods.
 *  @file   utest_vector2d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides automated testing for Vector2D class and methods.
 */
// =======================================================================================


#include <limits.h>
#include "Vector2D.hh"
#include "gtest/gtest.h"
#include <Dice.hh>


namespace {


  // =====================================================================================
  TEST(test_construct2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A;
      EXPECT_DOUBLE_EQ( 0.0, A.x );
      EXPECT_DOUBLE_EQ( 0.0, A.y );
    }

    {
      Vector2D A = { 1.2, 3.4 };
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }

    {
      Vector2D A(1.2, 3.4);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }

    {
      real8_t q[] = { 1.2, 3.4 };
      Vector2D A(q);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }

    {
      real8_t q[] = { 1.2, 3.4 };
      Vector2D T(q);
      Vector2D A(T);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }

    {
      real8_t q[] = { 1.2, 3.4 };
      Vector2D* T = new Vector2D(q);
      Vector2D A(T);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      delete T;
    }
  }


  // =====================================================================================
  TEST(test_set2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A = { 1.2, 3.4 };
      A.set();
    
      EXPECT_DOUBLE_EQ( 0.0, A.x );
      EXPECT_DOUBLE_EQ( 0.0, A.y );
    }

    {
      Vector2D A = { 1.2, 3.4 };
      A.set(7.2);
    
      EXPECT_DOUBLE_EQ( 7.2, A.x );
      EXPECT_DOUBLE_EQ( 7.2, A.y );
    }
  }


  // =====================================================================================
  TEST(test_copy2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A = { 6.5, 4.3 };
      Vector2D B = { 1.2, 3.4 };

      A.copy( B );
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }
  
    {
      Vector2D A = { 6.5, 4.3 };
      Vector2D T = { 1.2, 3.4 };
      Vector2D* B = new Vector2D(T);
    
      A.copy( B );
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );

      delete B;
    }
  
    {
      Vector2D A = { 6.5, 4.3 };

      A.copy( 1.2, 3.4 );
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }
  
    {
      Vector2D A = { 6.5, 4.3 };
      Vector2D B = { 1.2, 3.4 };

      A = B;
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }
  }


  // =====================================================================================
  TEST(test_access2, Positive) {
    // -----------------------------------------------------------------------------------
    Vector2D A;
    A[0] = 1.23;
    A[1] = 4.56;

    A.x += 3.1;
    A.y += 2.2;

    real8_t a0 = A[0];
    real8_t a1 = A[1];

    EXPECT_DOUBLE_EQ( 4.33, a0 );
    EXPECT_DOUBLE_EQ( 6.76, a1 );
  }


  // =====================================================================================
  TEST(test_format2, Positive) {
    // -----------------------------------------------------------------------------------
    Vector2D A( 6.40, 1.28 );

    std::string test = toString( A, "%3.2f", ";" );

    EXPECT_STREQ( "6.40;1.28", test.c_str() );
  }


  // =====================================================================================
  TEST(test_unary_scale2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A( 6.40, 1.28 );
      A = 3.4;
      EXPECT_DOUBLE_EQ( 3.4, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }

    {
      Vector2D A( 6.40, 1.28 );
      A += 3.4;
      EXPECT_DOUBLE_EQ( 9.80, A.x );
      EXPECT_DOUBLE_EQ( 4.68, A.y );
    }

    {
      Vector2D A( 6.40, 1.28 );
      A -= 3.1;
      EXPECT_DOUBLE_EQ(  3.30, A.x );
      EXPECT_DOUBLE_EQ( -1.82, A.y );
    }

    {
      Vector2D A( 6.40, 1.28 );
      A *= 2.1;
      EXPECT_DOUBLE_EQ( 13.44, A.x );
      EXPECT_DOUBLE_EQ( 2.688, A.y );
    }

    {
      Vector2D A( 6.40, 1.28 );
      A /= 2.0;
      EXPECT_DOUBLE_EQ( 3.20, A.x );
      EXPECT_DOUBLE_EQ( 0.64, A.y );
    }
  }


  // =====================================================================================
  TEST(test_unary_vector2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A( 1.2, 3.4 );
      Vector2D B( 6.5, 4.3 );

      A += B;

      EXPECT_DOUBLE_EQ( 7.7, A.x );
      EXPECT_DOUBLE_EQ( 7.7, A.y );
    }

    {
      Vector2D A( 1.2, 3.4 );
      Vector2D B( 6.5, 4.3 );

      A -= B;

      EXPECT_DOUBLE_EQ( -5.3, A.x );
      EXPECT_DOUBLE_EQ( -0.9, A.y );
    }

    {
      Vector2D A( 1.2, 3.4 );
      Vector2D B( 6.5, 4.3 );

      A *= B;

      EXPECT_DOUBLE_EQ(  7.80, A.x );
      EXPECT_DOUBLE_EQ( 14.62, A.y );
    }

    {
      Vector2D A( 3.96, 7.48 );
      Vector2D B( 3.30, 2.20 );

      A /= B;

      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
    }
  }


  // =====================================================================================
  TEST(test_binary_add2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 1.2, 3.4 );

      A = 3.1 + B;

      EXPECT_DOUBLE_EQ( 4.3, A.x );
      EXPECT_DOUBLE_EQ( 6.5, A.y );
    }

    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 1.2, 3.4 );

      A = B + 3.1;

      EXPECT_DOUBLE_EQ( 4.3, A.x );
      EXPECT_DOUBLE_EQ( 6.5, A.y );
    }

    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );

      C = A + B;

      EXPECT_DOUBLE_EQ( 7.7, C.x );
      EXPECT_DOUBLE_EQ( 7.7, C.y );
    }
  
    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );
      Vector2D D( 1.1, 2.2 );

      D = C + (A + B);

      EXPECT_DOUBLE_EQ( 8.8, D.x );
      EXPECT_DOUBLE_EQ( 9.9, D.y );
    } 
  }


  // =====================================================================================
  TEST(test_binary_sub2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 1.2, 3.4 );

      A = 3.1 - B;

      EXPECT_DOUBLE_EQ(  1.90, A.x );
      EXPECT_DOUBLE_EQ( -0.30, A.y );
    }

    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 1.2, 3.4 );

      A = B - 3.1;

      EXPECT_DOUBLE_EQ( -1.90, A.x );
      EXPECT_DOUBLE_EQ(  0.30, A.y );
    }

    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );

      C = A - B;

      EXPECT_DOUBLE_EQ(  5.3, C.x );
      EXPECT_DOUBLE_EQ(  0.9, C.y );
    }
  
    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );
      Vector2D D( 1.1, 2.2 );

      D = C - (A - B);

      EXPECT_DOUBLE_EQ( -4.2, D.x );
      EXPECT_DOUBLE_EQ(  1.3, D.y );
    } 
  }


  // =====================================================================================
  TEST(test_binary_mul2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 1.2, 3.4 );

      A = 3.1 * B;

      EXPECT_DOUBLE_EQ(  3.72, A.x );
      EXPECT_DOUBLE_EQ( 10.54, A.y );
    }

    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 1.2, 3.4 );

      A = B * 3.1;

      EXPECT_DOUBLE_EQ(  3.72, A.x );
      EXPECT_DOUBLE_EQ( 10.54, A.y );
    }

    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );

      C = A * B;

      EXPECT_DOUBLE_EQ(  7.80, C.x );
      EXPECT_DOUBLE_EQ( 14.62, C.y );
    }
  
    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );
      Vector2D D( 1.1, 2.2 );

      D = C * (A + B);

      EXPECT_DOUBLE_EQ(  8.47, D.x );
      EXPECT_DOUBLE_EQ( 16.94, D.y );
    } 
  }


  // =====================================================================================
  TEST(test_binary_div2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 2.0, 4.0 );

      A = 6.4 / B;

      EXPECT_DOUBLE_EQ( 3.2, A.x );
      EXPECT_DOUBLE_EQ( 1.6, A.y );
    }

    {
      Vector2D A( 1.1, 2.2 );
      Vector2D B( 6.82, 10.23 );

      A = B / 3.1;

      EXPECT_DOUBLE_EQ( 2.2, A.x );
      EXPECT_DOUBLE_EQ( 3.3, A.y );
    }

    {
      Vector2D A( 6.6, 14.96 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 1.1, 2.2 );

      C = A / B;

      EXPECT_DOUBLE_EQ( 5.5, C.x );
      EXPECT_DOUBLE_EQ( 4.4, C.y );
    }
  
    {
      Vector2D A( 6.5, 4.3 );
      Vector2D B( 1.2, 3.4 );
      Vector2D C( 20.79, 23.87 );
      Vector2D D( 1.1, 2.2 );

      D = C / (A + B);

      EXPECT_DOUBLE_EQ( 2.7, D.x );
      EXPECT_DOUBLE_EQ( 3.1, D.y );
    } 
  }

  // =====================================================================================
  TEST(test_equals2, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector2D  rA( 6.5, 4.3 );
      Vector2D  rB( 1.2, 3.4 );
      Vector2D* pA = &rA;
      Vector2D* pB = &rB;

      EXPECT_FALSE( equals( rA, rB ) );
      EXPECT_FALSE( equals( pA, pB ) );
    }

    {
      Vector2D  rB( 6.5, 4.3 );
      Vector2D  rA( 6.5, 4.3 );
      Vector2D* pB = &rA;
      Vector2D* pA = &rB;

      EXPECT_TRUE( equals( rA, rB ) );
      EXPECT_TRUE( equals( pA, pB ) );
    }
  }

  // =====================================================================================
  TEST(test_norm3, Positive) {
    // -----------------------------------------------------------------------------------
    Vector2D  A( -1.2,  3.4 );

    EXPECT_DOUBLE_EQ( 4.6, A.norm1() );
    EXPECT_DOUBLE_EQ( sqrt(13.0), A.norm() );
    EXPECT_DOUBLE_EQ( 13.0, A.normsq() );
    
    Vector2D N = A.normalize();
    EXPECT_DOUBLE_EQ( D_ONE, N.norm() ); 
  }

  // =====================================================================================
  TEST(test_dot_cross2, Positive) {
    // -----------------------------------------------------------------------------------
    Vector2D  A( -1.2,  3.4 );
    Vector2D  B(  6.5, -4.3 );

    EXPECT_DOUBLE_EQ( -22.42, dot( A, B ) );
    EXPECT_DOUBLE_EQ( -16.94, cross( A, B ) );
  }


  // =====================================================================================
  TEST(test_dist2, Positive) {
    // -----------------------------------------------------------------------------------
    Vector2D  A( -1.2,  3.4 );
    Vector2D  B(  6.5, -5.4 );

    EXPECT_DOUBLE_EQ( 16.5, dist1( A, B ) );
    EXPECT_DOUBLE_EQ( sqrt(136.73), dist( A, B ) );
    EXPECT_DOUBLE_EQ( 136.73, distsq( A, B ) );
  }
  

  // =====================================================================================
  TEST(test_ang3, Positive) {
    // -----------------------------------------------------------------------------------
    real8_t TV[40][5] =
      {
       {  47.32, -77.20,  -8.65, -55.58, 0.7042825784517708 },
       { -14.60, -59.75,  62.97, -34.65, 1.3074073333788001 },
       {  61.97,  15.85, -13.51,   6.26, 2.4572830485561457 },
       { -97.86, -54.15, -49.31, -45.20, 0.2365330366249846 },
       { -97.45,  50.62, -36.28, -58.79, 1.4969725860528249 },
       { -99.02,  74.32,   7.22,  91.72, 1.0054956761230027 },
       { -78.74,  86.45,  22.58, -51.58, 2.8154683392784108 },
       { -20.31, -73.64,  66.80, -10.62, 1.6822446994452420 },
       {   3.04,  14.90,  29.77, -35.99, 2.2492357831159602 },
       {  57.73,  65.29,  28.51, -55.75, 1.9448525862372426 },
       { -81.06,  74.65, -26.06, -95.26, 2.0480179014864026 },
       {  59.13, -62.68,  70.46,  48.06, 1.4131374973037225 },
       {   2.20,  30.81, -86.93, -23.56, 1.9067454900115164 },
       { -18.09, -48.42,  40.61, -72.59, 0.8676124658729776 },
       { -76.41,  22.60,  84.99,  34.53, 2.4681074444295032 },
       {  77.72,  89.46,  -1.32, -70.94, 2.4449082352148075 },
       { -18.45, -20.96, -62.87,  30.07, 1.2951297375311701 },
       {  61.69, -32.29, -92.96,  22.79, 2.8997997242115749 },
       { -39.47,  38.52,  65.25,  12.02, 2.1862027254555843 },
       { -24.24,  39.23,  33.00,  36.22, 1.2923867219721306 },
       {  60.66, -93.45, -62.96, -93.10, 1.1703705535200624 },
       { -97.24,  48.15,  30.48, -42.98, 2.6474216340358891 },
       {  -5.74, -39.21, -92.32,  35.57, 1.7931992344737993 },
       {   4.56,  24.33, -39.42, -92.65, 2.9245956112910738 },
       { -68.42,  32.01, -72.46, -61.46, 1.1410384248702272 },
       { -51.79, -85.15,  77.24, -61.81, 1.4423555831078820 },
       {  44.16, -87.61, -96.69, -34.01, 1.6994538415788261 },
       {  13.48, -68.35, -29.66,  38.14, 2.6753433383817842 },
       {  28.72,  -3.80,  80.35, -61.32, 0.5203233010232680 },
       { -49.12, -31.83,  79.23, -67.08, 1.8640758382219402 },
       { -29.13,  11.41,  92.57,  70.69, 2.1160957882277911 },
       {  87.48,  73.58,  24.25, -53.70, 1.8459351057312436 },
       {  28.91, -10.86,  15.36, -97.10, 1.0545697301103758 },
       {  69.43, -13.57,  79.92, -51.47, 0.3791437079123604 },
       { -23.82,  70.85, -93.17,  -8.87, 1.3413813292948413 },
       { -36.07, -55.28,  72.82,  55.22, 2.7977216313202367 },
       {  41.29,  88.94,  34.61, -23.66, 1.7358052862027062 },
       {  89.81,  82.48,  87.20,  27.12, 0.4413531551072871 },
       {  30.78,  52.42,  45.67,  -2.63, 1.0973797910773553 },
       { -57.12, -23.90, -44.57,  11.62, 0.6513181621520460 },
      };

    size_t n = sizeof(TV)/sizeof(TV[0]);

    for ( size_t i=0; i<n; i++ ) {
      Vector2D A( TV[i][0], TV[i][1] );
      Vector2D B( TV[i][2], TV[i][3] );

      EXPECT_NEAR( TV[i][4], angle(A,B), 1.0e-12 );
    }
  }
  
    
} // end namespace


// =======================================================================================
// **                            U T E S T _ V E C T O R 2 D                            **
// ======================================================================== END FILE =====
