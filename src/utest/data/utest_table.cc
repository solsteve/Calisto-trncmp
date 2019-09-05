// ====================================================================== BEGIN FILE =====
// **                               U T E S T _ T A B L E                               **
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
/** @brief  Automated testing for Table class methods.
 *  @file   utest_table.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-26
 *
 *  Provides automated testing for the Table class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <Table.hh>
#include <Vector.hh>
#include <gtest/gtest.h>

namespace {

  // =======================================================================================
  inline real8_t ELEM( int32_t i, int32_t j ) {
    // -------------------------------------------------------------------------------------
    return ((real8_t)i) + (((real8_t)j)/100.0);
  }


  // =======================================================================================
  TEST(test_table_creation, empty ) {
    // -------------------------------------------------------------------------------------
    // Test: size(), Table.size()
    // -------------------------------------------------------------------------------------
    Table T;
    EXPECT_EQ( 0, size(T,0) );
    EXPECT_EQ( 0, size(T,1) );
  }


  // =======================================================================================
  TEST(test_table_creation, sized ) {
    // -------------------------------------------------------------------------------------
    // Test: resize()
    // -------------------------------------------------------------------------------------
    Table T(17,5);
    EXPECT_EQ( 17, size(T,0) );
    EXPECT_EQ(  5, size(T,1) );
  }


  // =======================================================================================
  TEST(test_table_creation, copy ) {
    // -------------------------------------------------------------------------------------
    // Test: operator(), at(), copy(), operator=
    // -------------------------------------------------------------------------------------
    int32_t ns = 11;
    int32_t nv = 7;
    
    Table T(ns,nv);

    for ( int32_t s=0; s<ns; s++ ) {
      for ( int32_t v=0; v<nv; v++ ) {
	T(s,v) = ELEM(s,v);
      }
    }

    Table K(T);
    
    for ( int32_t v=0; v<nv; v++ ) {
      for ( int32_t s=0; s<ns; s++ ) {
	EXPECT_DOUBLE_EQ( ELEM(s,v), K.at(s,v) );
      }
    }

    Table X(2,3);

    X = T;
    
    for ( int32_t v=0; v<nv; v++ ) {
      for ( int32_t s=0; s<ns; s++ ) {
	EXPECT_DOUBLE_EQ( ELEM(s,v), X(s,v) );
      }
    }

  }

  
  // =======================================================================================
  TEST(test_table_creation, set ) {
    // -------------------------------------------------------------------------------------
    // Test: set()
    // -------------------------------------------------------------------------------------
    int32_t ns = 13;
    int32_t nv = 9;
    
    Table T(ns,nv);

    T.set(13.7);

    for ( int32_t v=0; v<nv; v++ ) {
      for ( int32_t s=0; s<ns; s++ ) {
	EXPECT_DOUBLE_EQ( 13.7, T(s,v) );
      }
    }

  }


  // =======================================================================================
  TEST(test_table_pointer, row ) {
    // -------------------------------------------------------------------------------------
    // Test: row()
    // -------------------------------------------------------------------------------------
    int32_t ns = 11;
    int32_t nv = 7;
    
    Table T(ns,nv);

    for ( int32_t s=0; s<ns; s++ ) {
      for ( int32_t v=0; v<nv; v++ ) {
	T(s,v) = ELEM(s,v);
      }
    }

    real8_t R[nv];

    for ( int32_t s=0; s<ns; s++ ) {
      T.row( R, s );
      for ( int32_t v=0; v<nv; v++ ) {
	EXPECT_DOUBLE_EQ( ELEM(s,v), R[v] );
      }
    }

  }


  // =======================================================================================
  TEST(test_table_pointer, column ) {
    // -------------------------------------------------------------------------------------
    // Test: col()
    // -------------------------------------------------------------------------------------
    int32_t ns = 11;
    int32_t nv = 7;
    
    Table T(ns,nv);

    for ( int32_t s=0; s<ns; s++ ) {
      for ( int32_t v=0; v<nv; v++ ) {
	T(s,v) = ELEM(s,v);
      }
    }

    for ( int32_t v=0; v<nv; v++ ) {
      real8_t* C = T.col(v);
      for ( int32_t s=0; s<ns; s++ ) {
	EXPECT_DOUBLE_EQ( ELEM(s,v), C[s] );
      }
    }
  
  }

  // =======================================================================================
  TEST(test_table_file, read_write ) {
    // -------------------------------------------------------------------------------------
    // Test: read(), write()
    // -------------------------------------------------------------------------------------
    int32_t ns = 11;
    int32_t nv = 7;
    Table T(ns,nv);

    for ( int32_t s=0; s<ns; s++ ) {
      for ( int32_t v=0; v<nv; v++ ) {
	T(s,v) = ELEM(s,v);
      }
    }

    T.write_ascii( "/tmp/table_test.dat", "%5.2f" );

    Table X( "/tmp/table_test.dat" ); 

    for ( int32_t s=0; s<ns; s++ ) {
      for ( int32_t v=0; v<nv; v++ ) {
	EXPECT_DOUBLE_EQ( T(s,v), X(s,v) );
      }
    }
  }


  // =======================================================================================
  TEST(test_table_ops, sum_mean ) {
    // -------------------------------------------------------------------------------------
    int32_t nrow = 35;
    int32_t ncol = 23;

    real8_t nrF = static_cast<real8_t>(nrow);
    real8_t ncF = static_cast<real8_t>(ncol);
  
    Table T(nrow,ncol);
    real8_t count = D_ONE;
    for ( int32_t r=0; r<nrow; r++ ) {
      for ( int32_t c=0; c<ncol; c++ ) {
	T(r,c) = count;
	count += D_ONE;
      }
    }

    real8_t sumR[nrow];
    real8_t sumC[ncol];
    real8_t muR[nrow];
    real8_t muC[ncol];

    real8_t inc = ncF*ncF;

    sumR[0] = ncF*(ncF+D_ONE)*D_HALF;
    for ( int32_t r=1; r<nrow; r++) {
      sumR[r] = sumR[r-1] + inc;
    }

    inc = nrF;

    sumC[0] = (nrF*(ncF*(nrF - D_ONE) + D_TWO))*D_HALF;

    for ( int32_t c=1; c<ncol; c++) {
      sumC[c] = sumC[c-1] + inc;
    }

    for ( int32_t r=0; r<nrow; r++) {
      muR[r] = sumR[r] / ncF;
    }

    for ( int32_t c=0; c<ncol; c++) {
      muC[c] = sumC[c] / nrF;
    }
  
  
    real8_t R[nrow];
    real8_t C[ncol];

    T.sum( C, ncol, 0 );
    T.sum( R, nrow, 1 );
  
    for ( int32_t r=0; r<nrow; r++) {
      EXPECT_DOUBLE_EQ( sumR[r], R[r] );
    }

    for ( int32_t c=0; c<ncol; c++) {
      EXPECT_DOUBLE_EQ( sumC[c], C[c] );
    }


    T.mean( C, ncol, 0 );
    T.mean( R, nrow, 1 );
  
    for ( int32_t r=0; r<nrow; r++) {
      EXPECT_DOUBLE_EQ( muR[r], R[r] );
    }

    for ( int32_t c=0; c<ncol; c++) {
      EXPECT_DOUBLE_EQ( muC[c], C[c] );
    }

  }

} // end namespace


// =======================================================================================
// **                               U T E S T _ T A B L E                               **
// ======================================================================== END FILE =====
