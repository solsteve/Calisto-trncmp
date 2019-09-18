// ====================================================================== BEGIN FILE =====
// **                               U T E S T _ A R R A Y                               **
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
/** @brief  Automated testing for Array class methods.
 *  @file   utest_array.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-10
 *
 *  Provides automated testing for the Array class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <VarReal.hh>
#include <gtest/gtest.h>

namespace {

// =======================================================================================
inline real8_t ELEM( int32_t i, int32_t j ) {
  // -------------------------------------------------------------------------------------
  return ((real8_t)(i+1)) + (((real8_t)(j+1))/100.0);
}


// =======================================================================================
TEST( test_varreal_creation, empty ) {
  // -------------------------------------------------------------------------------------
  VarReal V;
  EXPECT_EQ( 0, V.size()  );
  EXPECT_EQ( 0, V.nRow()  );
  EXPECT_EQ( 0, V.nCol(2) );
}

// =======================================================================================
TEST( test_varreal_creation, unfilled ) {
  // -------------------------------------------------------------------------------------
  int32_t nc[] = { 3, 5, 2, 4 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  int32_t nb = 0;
  for ( int32_t i=0; i<nr; i++ ) {
    nb += nc[i];
  }
  
  VarReal V(nr, nc);
  EXPECT_EQ( nb, V.size() );
  EXPECT_EQ( nr, V.nRow() );
  for ( int32_t i=0; i<nr; i++ ) {
    EXPECT_EQ( nc[i], V.nCol(i) );
  }
}

// =======================================================================================
TEST( test_varreal_creation, sourced ) {
  // -------------------------------------------------------------------------------------
  real8_t src[] = { 1.01, 1.02, 1.03, 
                    2.01, 2.02, 2.03, 2.04, 2.05, 
                    3.01, 3.02, 
                    4.01, 4.02, 4.03, 4.04 };
  
  int32_t nc[] = { 3, 5, 2, 4 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  VarReal V(nr, nc, src);
  
  int32_t nb = 0;
  for ( int32_t i=0; i<nr; i++ ) {
    nb += nc[i];
  }
  
  EXPECT_EQ( nb, V.size() );
  EXPECT_EQ( nr, V.nRow() );
  
  for ( int32_t i=0; i<nr; i++ ) {
    EXPECT_EQ( nc[i], V.nCol(i) );
  }

  for ( int32_t i=0; i<nr; i++ ) {
    int32_t n_c = V.nCol(i);
    for ( int32_t j=0; j<n_c; j++ ) {
      EXPECT_DOUBLE_EQ( ELEM(i,j), V(i,j) );
    }
    real8_t* R = V(i);
    for ( int32_t j=0; j<n_c; j++ ) {
      EXPECT_DOUBLE_EQ( ELEM(i,j), R[j] );
    }
  }

  V.set( 1, 2, 7.7 );
  EXPECT_DOUBLE_EQ( 7.7, V.get(1,2) );
  
  V( 1, 2 ) = 9.9;
  EXPECT_DOUBLE_EQ( 9.9, V(1,2) );
  
}

// =======================================================================================
TEST( test_varreal_storage, load_store ) {
  // -------------------------------------------------------------------------------------
  int32_t nc[] = { 3, 5, 2, 4 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  VarReal V( nr, nc );

  for ( int32_t i=0; i<nr; i++ ) {
     int32_t n_c = V.nCol(i);   
    for ( int32_t j=0; j<n_c; j++ ) {
      V(i,j) = ELEM( i, j );
    }
  }

  int32_t nb = V.size();

  real8_t buffer[ nb + 2 ];
  buffer[nb]   = 314.159;
  buffer[nb+1] = 271.828;

  real8_t* P = V.store( buffer );

  EXPECT_DOUBLE_EQ( 314.159, P[0] );
  EXPECT_DOUBLE_EQ( 271.828, P[1] );

}





} // end namespace


// =======================================================================================
// **                               U T E S T _ A R R A Y                               **
// ======================================================================== END FILE =====
