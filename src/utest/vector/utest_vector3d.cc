// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ V E C T O R 3 D                            **
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
/** @brief  Automated testing for Vector3D class and methods.
 *  @file   utest_vector3d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides automated testing for Vector3D class and methods.
 */
// =======================================================================================


#include <limits.h>
#include <Vector3D.hh>
#include "gtest/gtest.h"
#include <Dice.hh>


namespace {


  // =====================================================================================
  TEST(test_construct3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A;
      EXPECT_DOUBLE_EQ( 0.0, A.x );
      EXPECT_DOUBLE_EQ( 0.0, A.y );
      EXPECT_DOUBLE_EQ( 0.0, A.z );
    }

    {
      Vector3D A = { 1.2,3.4,5.6 };
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }

    {
      Vector3D A(1.2,3.4,5.6);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }

    {
      real8_t q[] = { 1.2,3.4,5.6 };
      Vector3D A(q);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }

    {
      real8_t q[] = { 1.2,3.4,5.6 };
      Vector3D T(q);
      Vector3D A(T);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }

    {
      real8_t q[] = { 1.2,3.4,5.6 };
      Vector3D* T = new Vector3D(q);
      Vector3D A(T);
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
      delete T;
    }
  }


  // =====================================================================================
  TEST(test_set3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A = { 1.2,3.4,5.6 };
      A.set();
    
      EXPECT_DOUBLE_EQ( 0.0, A.x );
      EXPECT_DOUBLE_EQ( 0.0, A.y );
      EXPECT_DOUBLE_EQ( 0.0, A.z );
    }

    {
      Vector3D A = { 1.2,3.4,5.6 };
      A.set(7.2);
    
      EXPECT_DOUBLE_EQ( 7.2, A.x );
      EXPECT_DOUBLE_EQ( 7.2, A.y );
      EXPECT_DOUBLE_EQ( 7.2, A.z );
    }
  }


  // =====================================================================================
  TEST(test_copy3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A = { 6.5, 4.3, 2.1 };
      Vector3D B = { 1.2, 3.4, 5.6 };

      A.copy( B );
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }
  
    {
      Vector3D A = { 6.5, 4.3, 2.1 };
      Vector3D T = { 1.2, 3.4, 5.6 };
      Vector3D* B = new Vector3D(T);
    
      A.copy( B );
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );

      delete B;
    }
  
    {
      Vector3D A = { 6.5, 4.3, 2.1 };

      A.copy( 1.2, 3.4, 5.6 );
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }
  
    {
      Vector3D A = { 6.5, 4.3, 2.1 };
      Vector3D B = { 1.2, 3.4, 5.6 };

      A = B;
    
      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }
  }


  // =====================================================================================
  TEST(test_access3, Positive) {
    // -----------------------------------------------------------------------------------
    Vector3D A;
    A[0] = 1.23;
    A[1] = 4.56;
    A[2] = 7.89;

    A.x += 3.1;
    A.y += 2.2;
    A.z += 1.3;

    real8_t a0 = A[0];
    real8_t a1 = A[1];
    real8_t a2 = A[2];

    EXPECT_DOUBLE_EQ( 4.33, a0 );
    EXPECT_DOUBLE_EQ( 6.76, a1 );
    EXPECT_DOUBLE_EQ( 9.19, a2 );
  }


  // =====================================================================================
  TEST(test_format3, Positive) {
    // -----------------------------------------------------------------------------------
    Vector3D A( 6.40, 1.28, 2.56 );

    std::string test = toString( A, "%3.2f", ";" );

    EXPECT_STREQ( "6.40;1.28;2.56", test.c_str() );
  }


  // =====================================================================================
  TEST(test_unary_scale3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A( 6.40, 1.28, 2.56 );
      A = 3.4;
      EXPECT_DOUBLE_EQ( 3.4, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 3.4, A.z );
    }

    {
      Vector3D A( 6.40, 1.28, 2.56 );
      A += 3.4;
      EXPECT_DOUBLE_EQ( 9.80, A.x );
      EXPECT_DOUBLE_EQ( 4.68, A.y );
      EXPECT_DOUBLE_EQ( 5.96, A.z );
    }

    {
      Vector3D A( 6.40, 1.28, 2.56 );
      A -= 3.1;
      EXPECT_DOUBLE_EQ(  3.30, A.x );
      EXPECT_DOUBLE_EQ( -1.82, A.y );
      EXPECT_DOUBLE_EQ( -0.54, A.z );
    }

    {
      Vector3D A( 6.40, 1.28, 2.56 );
      A *= 2.1;
      EXPECT_DOUBLE_EQ( 13.44, A.x );
      EXPECT_DOUBLE_EQ( 2.688, A.y );
      EXPECT_DOUBLE_EQ( 5.376, A.z );
    }

    {
      Vector3D A( 6.40, 1.28, 2.56 );
      A /= 2.0;
      EXPECT_DOUBLE_EQ( 3.20, A.x );
      EXPECT_DOUBLE_EQ( 0.64, A.y );
      EXPECT_DOUBLE_EQ( 1.28, A.z );
    }
  }


  // =====================================================================================
  TEST(test_unary_vector3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A( 1.2, 3.4, 5.6 );
      Vector3D B( 6.5, 4.3, 2.1 );

      A += B;

      EXPECT_DOUBLE_EQ( 7.7, A.x );
      EXPECT_DOUBLE_EQ( 7.7, A.y );
      EXPECT_DOUBLE_EQ( 7.7, A.z );
    }

    {
      Vector3D A( 1.2, 3.4, 5.6 );
      Vector3D B( 6.5, 4.3, 2.1 );

      A -= B;

      EXPECT_DOUBLE_EQ( -5.3, A.x );
      EXPECT_DOUBLE_EQ( -0.9, A.y );
      EXPECT_DOUBLE_EQ(  3.5, A.z );
    }

    {
      Vector3D A( 1.2, 3.4, 5.6 );
      Vector3D B( 6.5, 4.3, 2.1 );

      A *= B;

      EXPECT_DOUBLE_EQ(  7.80, A.x );
      EXPECT_DOUBLE_EQ( 14.62, A.y );
      EXPECT_DOUBLE_EQ( 11.76, A.z );
    }

    {
      Vector3D A( 3.96, 7.48, 6.16 );
      Vector3D B( 3.30, 2.20, 1.10 );

      A /= B;

      EXPECT_DOUBLE_EQ( 1.2, A.x );
      EXPECT_DOUBLE_EQ( 3.4, A.y );
      EXPECT_DOUBLE_EQ( 5.6, A.z );
    }
  }


  // =====================================================================================
  TEST(test_binary_add3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 1.2, 3.4, 5.6 );

      A = 3.1 + B;

      EXPECT_DOUBLE_EQ( 4.3, A.x );
      EXPECT_DOUBLE_EQ( 6.5, A.y );
      EXPECT_DOUBLE_EQ( 8.7, A.z );
    }

    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 1.2, 3.4, 5.6 );

      A = B + 3.1;

      EXPECT_DOUBLE_EQ( 4.3, A.x );
      EXPECT_DOUBLE_EQ( 6.5, A.y );
      EXPECT_DOUBLE_EQ( 8.7, A.z );
    }

    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );

      C = A + B;

      EXPECT_DOUBLE_EQ( 7.7, C.x );
      EXPECT_DOUBLE_EQ( 7.7, C.y );
      EXPECT_DOUBLE_EQ( 7.7, C.z );
    }
  
    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );
      Vector3D D( 1.1, 2.2, 3.3 );

      D = C + (A + B);

      EXPECT_DOUBLE_EQ( 8.8, D.x );
      EXPECT_DOUBLE_EQ( 9.9, D.y );
      EXPECT_DOUBLE_EQ( 11.0, D.z );
    } 
  }


  // =====================================================================================
  TEST(test_binary_sub3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 1.2, 3.4, 5.6 );

      A = 3.1 - B;

      EXPECT_DOUBLE_EQ(  1.90, A.x );
      EXPECT_DOUBLE_EQ( -0.30, A.y );
      EXPECT_DOUBLE_EQ( -2.50, A.z );
    }

    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 1.2, 3.4, 5.6 );

      A = B - 3.1;

      EXPECT_DOUBLE_EQ( -1.90, A.x );
      EXPECT_DOUBLE_EQ(  0.30, A.y );
      EXPECT_DOUBLE_EQ(  2.50, A.z );
    }

    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );

      C = A - B;

      EXPECT_DOUBLE_EQ(  5.3, C.x );
      EXPECT_DOUBLE_EQ(  0.9, C.y );
      EXPECT_DOUBLE_EQ( -3.5, C.z );
    }
  
    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );
      Vector3D D( 1.1, 2.2, 3.3 );

      D = C - (A - B);

      EXPECT_DOUBLE_EQ( -4.2, D.x );
      EXPECT_DOUBLE_EQ(  1.3, D.y );
      EXPECT_DOUBLE_EQ(  6.8, D.z );
    } 
  }


  // =====================================================================================
  TEST(test_binary_mul3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 1.2, 3.4, 5.6 );

      A = 3.1 * B;

      EXPECT_DOUBLE_EQ(  3.72, A.x );
      EXPECT_DOUBLE_EQ( 10.54, A.y );
      EXPECT_DOUBLE_EQ( 17.36, A.z );
    }

    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 1.2, 3.4, 5.6 );

      A = B * 3.1;

      EXPECT_DOUBLE_EQ(  3.72, A.x );
      EXPECT_DOUBLE_EQ( 10.54, A.y );
      EXPECT_DOUBLE_EQ( 17.36, A.z );
    }

    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );

      C = A * B;

      EXPECT_DOUBLE_EQ(  7.80, C.x );
      EXPECT_DOUBLE_EQ( 14.62, C.y );
      EXPECT_DOUBLE_EQ( 11.76, C.z );
    }
  
    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );
      Vector3D D( 1.1, 2.2, 3.3 );

      D = C * (A + B);

      EXPECT_DOUBLE_EQ(  8.47, D.x );
      EXPECT_DOUBLE_EQ( 16.94, D.y );
      EXPECT_DOUBLE_EQ( 25.41, D.z );
    } 
  }


  // =====================================================================================
  TEST(test_binary_div3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 2.0, 4.0, 8.0 );

      A = 6.4 / B;

      EXPECT_DOUBLE_EQ( 3.2, A.x );
      EXPECT_DOUBLE_EQ( 1.6, A.y );
      EXPECT_DOUBLE_EQ( 0.8, A.z );
    }

    {
      Vector3D A( 1.1, 2.2, 3.3 );
      Vector3D B( 6.82, 10.23, 13.64 );

      A = B / 3.1;

      EXPECT_DOUBLE_EQ( 2.2, A.x );
      EXPECT_DOUBLE_EQ( 3.3, A.y );
      EXPECT_DOUBLE_EQ( 4.4, A.z );
    }

    {
      Vector3D A( 6.6, 14.96, 18.48 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 1.1, 2.2, 3.3 );

      C = A / B;

      EXPECT_DOUBLE_EQ( 5.5, C.x );
      EXPECT_DOUBLE_EQ( 4.4, C.y );
      EXPECT_DOUBLE_EQ( 3.3, C.z );
    }
  
    {
      Vector3D A( 6.5, 4.3, 2.1 );
      Vector3D B( 1.2, 3.4, 5.6 );
      Vector3D C( 20.79, 23.87, 50.05 );
      Vector3D D( 1.1, 2.2, 3.3 );

      D = C / (A + B);

      EXPECT_DOUBLE_EQ( 2.7, D.x );
      EXPECT_DOUBLE_EQ( 3.1, D.y );
      EXPECT_DOUBLE_EQ( 6.5, D.z );
    } 
  }

  // =====================================================================================
  TEST(test_equals3, Positive) {
    // -----------------------------------------------------------------------------------
    {
      Vector3D  rA( 6.5, 4.3, 2.1 );
      Vector3D  rB( 1.2, 3.4, 5.6 );
      Vector3D* pA = &rA;
      Vector3D* pB = &rB;

      EXPECT_FALSE( equals( rA, rB ) );
      EXPECT_FALSE( equals( pA, pB ) );
    }

    {
      Vector3D  rB( 6.5, 4.3, 2.1 );
      Vector3D  rA( 6.5, 4.3, 2.1 );
      Vector3D* pB = &rA;
      Vector3D* pA = &rB;

      EXPECT_TRUE( equals( rA, rB ) );
      EXPECT_TRUE( equals( pA, pB ) );
    }
  }

  // =====================================================================================
  TEST(test_norm3, Positive) {
    // -----------------------------------------------------------------------------------
    Vector3D  A( -1.2,  3.4, -5.6 );

    EXPECT_DOUBLE_EQ( 10.20, A.norm1() );
    EXPECT_DOUBLE_EQ( sqrt(44.36), A.norm() );
    EXPECT_DOUBLE_EQ( 44.36, A.normsq() );

    Vector3D N = A.normalize();
    EXPECT_DOUBLE_EQ( D_ONE, N.norm() ); 
  }

  // =====================================================================================
  TEST(test_dot_cross3, Positive) {
    // -----------------------------------------------------------------------------------
    Vector3D  A( -1.2,  3.4, -5.6 );
    Vector3D  B(  6.5, -4.3,  7.8 );
    Vector3D  C(  2.44, -27.04, -16.94 );

    Vector3D  test = cross( A, B );

    EXPECT_DOUBLE_EQ( C.x, test.x );
    EXPECT_DOUBLE_EQ( C.y, test.y );
    EXPECT_DOUBLE_EQ( C.z, test.z );
    
    EXPECT_DOUBLE_EQ( -66.10, dot( A, B ) );
  }

  // =====================================================================================
  TEST(test_dist3, Positive) {
    // -----------------------------------------------------------------------------------
    Vector3D  A( -1.2,  3.4, -5.6 );
    Vector3D  B(  6.5, -5.4,  4.7);

    EXPECT_DOUBLE_EQ( 26.8, dist1( A, B ) );
    EXPECT_DOUBLE_EQ( sqrt(242.82), dist( A, B ) );
    EXPECT_DOUBLE_EQ( 242.82, distsq( A, B ) );
  }


  // =====================================================================================
  TEST(test_ang3, Positive) {
    // -----------------------------------------------------------------------------------
    real8_t TV[40][7] =
      {
       {  14.21,  -9.42,  72.72, -11.26,  75.68,  48.97, 1.1634370699920933 },
       {  36.30,  64.53,   1.38, -52.58,  78.23, -88.35, 1.2498944528452900 },
       {  98.70, -17.50, -19.65,  55.55, -98.88, -79.57, 0.9018227426657861 },
       {   9.03, -40.97,  82.36,  82.89, -55.28,  94.31, 0.5544593770317743 },
       { -76.00,  62.85, -57.37, -19.43, -22.40, -35.09, 1.1623357758074084 },
       {  -2.03,  91.44, -69.40, -28.13,  84.14,  78.82, 1.4026111716743486 },
       {  -2.55, -16.03,  65.80, -38.65,  72.63,  30.59, 1.4109043301608302 },
       { -81.28,  75.47,  88.02,  62.47,  -7.53, -36.81, 2.6077362165012681 },
       { -99.92, -34.53,  79.84,  23.73, -35.47, -79.99, 2.2486972010199882 },
       {   1.71, -97.64,   3.42,  67.60,  54.75, -31.23, 2.2030155038568879 },
       {  69.96, -68.05,  75.61,  -9.93,  86.28,  15.19, 2.0917439296682132 },
       { -13.64, -84.55, -65.71,  32.44,   2.45,  33.66, 2.1727578751133514 },
       {  95.90,  -9.19,   3.86,  -2.24, -57.02, -47.51, 1.5532223838101085 },
       {  93.01, -12.71, -16.54,  31.75, -71.06, -50.09, 1.0110160215994479 },
       { -66.20,  50.29,  -4.76, -50.37, -33.42,  68.94, 1.3962852953296010 },
       {   5.81, -84.45, -83.20,  96.74, -90.64,  74.05, 1.4564911845433257 },
       { -87.55,  82.53,  34.81,  75.91,  39.04, -17.20, 1.9485519961171980 },
       { -73.12,  14.95, -30.34, -49.87,  73.36,  39.07, 1.0977386290056481 },
       { -14.58, -27.12,  37.78,  18.58,  93.78,  -2.49, 2.2445841758290133 },
       { -47.58,  46.77, -98.84,  67.92,  41.15,  11.89, 1.8330182719681392 },
       {  76.71, -72.12,  68.03,   7.00,  64.61,  94.95, 1.4080683069952646 },
       { -16.79, -18.19, -36.84, -22.51,  82.70,  44.87, 2.2748161326747773 },
       { -66.68, -41.94,  -8.98,  67.65,  85.26,  41.89, 2.7270224331490636 },
       {   3.09, -65.30,  72.86,  -7.31,  -8.67, -26.71, 2.0872032144364967 },
       { -48.77,  35.34,  83.98,  94.86, -78.90,  22.10, 2.0143041190140516 },
       {  58.11,  83.20,  89.26,  32.88,  -7.91,  58.82, 0.7825147471539138 },
       {  87.34, -30.24,  60.96,   3.22,  -2.19, -44.28, 2.0690171468736871 },
       {  57.46, -96.39,  -6.79,  42.40,  73.21,  63.34, 2.0098406743780868 },
       {   8.86,  28.21, -11.82,  62.60, -78.22, -60.28, 1.8258723014774458 },
       {  76.00, -89.69, -33.16,  21.26,  33.89, -23.33, 1.6859926201596569 },
       {  21.00,  28.53,  81.91,  17.88, -88.46, -97.52, 2.5959730339721383 },
       { -49.11,  73.08,  54.86,   8.86,  40.21, -76.81, 1.7611222795256067 },
       {  73.63,  -4.75, -71.70,  14.20,  88.80, -23.52, 1.3268198638183153 },
       {  57.45, -77.82,  23.59,  97.88, -36.78, -20.34, 0.7153919187591896 },
       {  95.30, -32.17,  42.10,  24.49,  29.42,  64.77, 1.0454425583364324 },
       { -81.23, -23.01,  56.63, -33.85, -16.89, -62.32, 1.6235653515318758 },
       {   1.98, -67.64,  66.15,  94.46, -51.45, -39.73, 1.4748996339875908 },
       {  78.69,  61.05,  86.67, -13.64, -90.47,  90.93, 1.4953079598943164 },
       { -20.36, -98.45, -98.01,  67.88,  95.21, -84.14, 1.6951608187322940 },
       {  18.65, -37.60,  61.10,  29.57,  67.13, -31.70, 2.2916039155903638 },
      };

    size_t n = sizeof(TV)/sizeof(TV[0]);

    for ( size_t i=0; i<n; i++ ) {
      Vector3D A( TV[i][0], TV[i][1], TV[i][2] );
      Vector3D B( TV[i][3], TV[i][4], TV[i][5] );

      EXPECT_NEAR( TV[i][6], angle(A,B), 1.0e-12 );
    }
  }

  
} // end namespace


// =======================================================================================
// **                            U T E S T _ V E C T O R 3 D                            **
// ======================================================================== END FILE =====
