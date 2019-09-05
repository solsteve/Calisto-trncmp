// ====================================================================== BEGIN FILE =====
// **                                U T E S T _ T I M E                                **
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
// **  Foundation, eithger version 3 of the License, or (at your option)                **
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
/** @brief  Automated testing for Time Components.
 *  @file   utest_time.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-21
 *
 *  Provides automated testing for Time Components.
 */
// =======================================================================================

#include <limits.h>
#include <gtest/gtest.h>
#include <TimeComponents.hh>

namespace {

#define TESTTC( tc, h, m, s, u, ls, us )                        \
  EXPECT_EQ(   h,  tc.getHour() );                              \
  EXPECT_EQ(   m,  tc.getMinute() );                            \
  EXPECT_NEAR( s,  tc.getSecond(), 1.0e-11 );                   \
  EXPECT_EQ(   u,  tc.getMinutesFromUTC() );                    \
  EXPECT_NEAR( ls, tc.getSecondsInLocalDay(), 1.0e-11 );        \
  EXPECT_NEAR( us, tc.getSecondsInUTCDay(), 1.0e-11 )


// =======================================================================================
TEST( test_time, construct ) {
  // -------------------------------------------------------------------------------------
  TimeComponents T1;
  TimeComponents T2a(37.0);
  TimeComponents T2b(26741.9, 23);
  TimeComponents T3a(12,32,17.3);
  TimeComponents T3b(15,47,11.1,-239);
  TimeComponents T4(T3b);

  TESTTC( T1,   0,  0,  0.0,    0,  0.0,  0.0 );
  TESTTC( T2a,  0,  0, 37.0,    0, 37.0, 37.0 );
  TESTTC( T2b,  7, 25, 41.9,   23, 26741.9, 28121.9 );
  TESTTC( T3a, 12, 32, 17.3,    0, 45137.3, 45137.3 );
  TESTTC( T3b, 15, 47, 11.1, -239, 56831.1, 42491.1 );
  TESTTC( T4,  15, 47, 11.1, -239, 56831.1, 42491.1 );

  T1 = T2b;
  TESTTC( T1, 7, 25, 41.9, 23, 26741.9, 28121.9 );

  T2a.copy( T3a );
  TESTTC( T2a, 12, 32, 17.3, 0, 45137.3, 45137.3 );  
}

// =======================================================================================
TEST( test_time, validate ) {
  // -------------------------------------------------------------------------------------

  TimeComponents TC;
  int test = 0;

  // ------------------------------------------------
  test = 0;
  try {
    TC.set(0, 0, 0.0, -1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "XXXX", e.what() );
    test = 2;
  }
  EXPECT_EQ( 1, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(12, 30, 30.0, 0);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "XXXX", e.what() );
    test = 2;
  }
  EXPECT_EQ( 1, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(23, 59, 61.0, 1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "XXXX", e.what() );
    test = 2;
  }
  EXPECT_EQ( 1, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(24, 59, 61.0, 1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Hour is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(-1, 0, 0.0, -1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Hour is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(23, 60, 61.0, 1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Minute is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(0, -1, 0.0, -1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Minute is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(23, 59, 62.0, 1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Second is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(0, 0, -1.0, -1439);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Second is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(23, 59, 61.0, 1440);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "UTC Offset is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    TC.set(0, 0, 0.0, -1440);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "UTC Offset is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
}


// =======================================================================================
TEST( test_time, equals ) {
  // -------------------------------------------------------------------------------------
  TimeComponents A(15,47,11.1,-239);
  TimeComponents B(56831.1,-239);

  TESTTC( A, 15, 47, 11.1, -239, 56831.1, 42491.1 );
  TESTTC( B, 15, 47, 11.1, -239, 56831.1, 42491.1 );

  EXPECT_TRUE( A.equals(B) );

  A.set(14,47,11.1,-239);
  EXPECT_FALSE( A.equals(B) );
  
  A.set(15,42,11.1,-239);
  EXPECT_FALSE( A.equals(B) );
  
  A.set(15,47,11.2,-239);
  EXPECT_FALSE( A.equals(B) );
  
  A.set(15,47,11.0,-239);
  EXPECT_FALSE( A.equals(B) );
  
  A.set(15,47,11.1,-259);
  EXPECT_FALSE( A.equals(B) ); 
}


// =======================================================================================
TEST( test_time, compare ) {
  // -------------------------------------------------------------------------------------
  {
    TimeComponents A(14,47,11.1);
    TimeComponents B(14,47,11.1);
    EXPECT_EQ( 0, A.compare(B) );
    EXPECT_EQ( 0, B.compare(A) );
  }

  {
    TimeComponents A(14,47,11.1);
    TimeComponents B(15,47,11.1);
    EXPECT_EQ( -1, A.compare(B) );
    EXPECT_EQ( +1, B.compare(A) );
  }

  {
    TimeComponents A(15,46,11.1);
    TimeComponents B(15,47,11.1);
    EXPECT_EQ( -1, A.compare(B) );
    EXPECT_EQ( +1, B.compare(A) );
  }

  {
    TimeComponents A(15,47,11.0);
    TimeComponents B(15,47,11.1);
    EXPECT_EQ( -1, A.compare(B) );
    EXPECT_EQ( +1, B.compare(A) );
  }
}


// =======================================================================================
TEST( test_time, parse ) {
  // -------------------------------------------------------------------------------------
  TimeComponents T1 = TimeComponents::fromString( "T15:47:11.100-03:59" );

  TESTTC( T1, 15, 47, 11.1, -239, 56831.1, 42491.1 );

  TimeComponents T2( 15, 47, 11.1, -239 );

  std::string str = T2.toString();

  EXPECT_STREQ( "T15:47:11.10000-03:59", str.c_str() );
}


} // end namespace


// =======================================================================================
// **                                U T E S T _ T I M E                                **
// ======================================================================== END FILE =====
