// ====================================================================== BEGIN FILE =====
// **                                U T E S T _ D A T E                                **
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
/** @brief  Automated testing for Date Components.
 *  @file   utest_date.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-21
 *
 *  Provides automated testing for Date Components.
 */
// =======================================================================================

#include <limits.h>
#include <gtest/gtest.h>
#include <TimeComponents.hh>
#include <DateComponents.hh>

namespace {

#define TESTDC( dc, y, m, d, dy, j2k ) \
  EXPECT_EQ( y,   dc.getYear() );      \
  EXPECT_EQ( m,   dc.getMonth() );     \
  EXPECT_EQ( d,   dc.getDay() );       \
  EXPECT_EQ( dy,  dc.getDayOfYear() ); \
  EXPECT_EQ( j2k, dc.getJ2000Day() )

#define TESTDC2( dc, y, m, d ) \
  EXPECT_EQ( y,   dc.getYear() );      \
  EXPECT_EQ( m,   dc.getMonth() );     \
  EXPECT_EQ( d,   dc.getDay() )

// =======================================================================================
TEST( test_date, construct ) {
  // -------------------------------------------------------------------------------------
  DateComponents D1;
  DateComponents D2(2019, 5, 26);
  DateComponents D3(2019, 169);
  DateComponents D4(6013);
  DateComponents D5(D3);
  
  EXPECT_EQ( 1, D1.getYear() );
  EXPECT_EQ( 1, D1.getMonth() );
  EXPECT_EQ( 1, D1.getDay() );

  TESTDC( D2, 2019, 5, 26, 146, 7085 );
  TESTDC( D3, 2019, 6, 18, 169, 7108 );
  TESTDC( D4, 2016, 6, 18, 170, 6013 );

  D1 = D2;
  TESTDC( D1, 2019, 5, 26, 146, 7085 );

  D5.copy( D2 );
  TESTDC( D5, 2019, 5, 26, 146, 7085 );
}

// =======================================================================================
TEST( test_date, validate ) {
  // -------------------------------------------------------------------------------------

  DateComponents DC;
  int test = 0;

  // ------------------------------------------------
  test = 0;
  try {
    DC.set(1, 1, 1);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "XXXX", e.what() );
    test = 2;
  }
  EXPECT_EQ( 1, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(1999, 9, 13);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "XXXX", e.what() );
    test = 2;
  }
  EXPECT_EQ( 1, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(9999, 12, 31);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "XXXX", e.what() );
    test = 2;
  }
  EXPECT_EQ( 1, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(10000, 12, 31);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Year is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(0, 1, 1);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Year is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
        
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(9999, 13, 31);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Month is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(1, 0, 1);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Month is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
        
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(9999, 12, 32);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Day is to large", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
  // ------------------------------------------------
  test = 0;
  try {
    DC.set(1, 1, 0);
    test = 1;
  } catch( std::invalid_argument& e ) {
    EXPECT_STREQ( "Day is to small", e.what() );
    test = 2;
  }
  EXPECT_EQ( 2, test );
    
}


// =======================================================================================
TEST( test_date, equals ) {
  // -------------------------------------------------------------------------------------
  DateComponents A(2016,6,18);
  DateComponents B(6013);

  TESTDC( A, 2016, 6, 18, 170, 6013 );
  TESTDC( B, 2016, 6, 18, 170, 6013 );

  EXPECT_TRUE( A.equals(B) );

  A.set(2017, 6, 18);
  EXPECT_FALSE( A.equals(B) );
  
  A.set(2016, 7, 18);
  EXPECT_FALSE( A.equals(B) );
  
  A.set(2016, 6, 17);
  EXPECT_FALSE( A.equals(B) );
  
}


// =======================================================================================
TEST( test_date, compare ) {
  // -------------------------------------------------------------------------------------
  {
    DateComponents A(2016, 6, 18);
    DateComponents B(2016, 6, 18);
    EXPECT_EQ( 0, A.compare(B) );
    EXPECT_EQ( 0, B.compare(A) );
  }

  {
    DateComponents A(2015, 6, 18);
    DateComponents B(2016, 6, 18);
    EXPECT_EQ( -1, A.compare(B) );
    EXPECT_EQ( +1, B.compare(A) );
  }

  {
    DateComponents A(2016, 5, 18);
    DateComponents B(2016, 6, 18);
    EXPECT_EQ( -1, A.compare(B) );
    EXPECT_EQ( +1, B.compare(A) );
  }

  {
    DateComponents A(2016, 6, 15);
    DateComponents B(2016, 6, 18);
    EXPECT_EQ( -1, A.compare(B) );
    EXPECT_EQ( +1, B.compare(A) );
  }
}


// =======================================================================================
TEST( test_date, parse ) {
  // -------------------------------------------------------------------------------------
  DateComponents D1 = DateComponents::fromString( "1999-09-13" );

  TESTDC( D1, 1999, 9, 13, 256, -110 );

  DateComponents D2( 1999, 9, 13 );

  std::string str = D2.toString();

  EXPECT_STREQ( "1999-09-13", str.c_str() );
}


typedef struct {
  int32_t JD;
  int32_t year;
  int32_t month;
  int32_t day;
} jd_test_s;


// =======================================================================================
TEST( test_date, JD ) {
  // -------------------------------------------------------------------------------------
  jd_test_s T[] = {
    { 2461186, 2026, 5, 26 },
    { 2458652, 2019, 6, 18 },
    { 2457557, 2016, 6, 18 },
    { 2451544, 2000, 1,  1 },
    { 2451434, 1999, 9, 13 },
    { 2448037, 1990, 5, 26 },
    { 2440587, 1970, 1,  1 },
    { 2438564, 1964, 6, 18 },
  };

  size_t n = sizeof(T) / sizeof(T[0]);

  DateComponents DC;

  for ( size_t i=0; i<n; i++ ) {
    int32_t j = T[i].JD;
    int32_t y = T[i].year;
    int32_t m = T[i].month;
    int32_t d = T[i].day;
    DC = DateComponents::fromJulianDate(j);
    TESTDC2( DC, y, m, d );
    int32_t tj = DC.toJulianDate();
    EXPECT_EQ( j, tj );
  }
  
}


} // end namespace


// =======================================================================================
// **                                U T E S T _ D A T E                                **
// ======================================================================== END FILE =====
