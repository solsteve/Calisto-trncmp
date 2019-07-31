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
#include <gtest/gtest.h>

namespace {

// =======================================================================================
inline real8_t ELEM( size_t i, size_t j ) {
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
  size_t ns = 11;
  size_t nv = 7;
    
  Table T(ns,nv);

  for ( size_t s=0; s<ns; s++ ) {
    for ( size_t v=0; v<nv; v++ ) {
      T(s,v) = ELEM(s,v);
    }
  }

  Table K(T);
    
  for ( size_t v=0; v<nv; v++ ) {
    for ( size_t s=0; s<ns; s++ ) {
      EXPECT_DOUBLE_EQ( ELEM(s,v), K.at(s,v) );
    }
  }

  Table X(2,3);

  X = T;
    
  for ( size_t v=0; v<nv; v++ ) {
    for ( size_t s=0; s<ns; s++ ) {
      EXPECT_DOUBLE_EQ( ELEM(s,v), X(s,v) );
    }
  }

}

  
// =======================================================================================
TEST(test_table_creation, set ) {
  // -------------------------------------------------------------------------------------
  // Test: set()
  // -------------------------------------------------------------------------------------
  size_t ns = 13;
  size_t nv = 9;
    
  Table T(ns,nv);

  T.set(13.7);

  for ( size_t v=0; v<nv; v++ ) {
    for ( size_t s=0; s<ns; s++ ) {
      EXPECT_DOUBLE_EQ( 13.7, T(s,v) );
    }
  }

}


// =======================================================================================
TEST(test_table_pointer, row ) {
  // -------------------------------------------------------------------------------------
  // Test: row()
  // -------------------------------------------------------------------------------------
  size_t ns = 11;
  size_t nv = 7;
    
  Table T(ns,nv);

  for ( size_t s=0; s<ns; s++ ) {
    for ( size_t v=0; v<nv; v++ ) {
      T(s,v) = ELEM(s,v);
    }
  }

  real8_t R[nv];

  for ( size_t s=0; s<ns; s++ ) {
    T.row( R, s );
    for ( size_t v=0; v<nv; v++ ) {
      EXPECT_DOUBLE_EQ( ELEM(s,v), R[v] );
    }
  }

}


// =======================================================================================
TEST(test_table_pointer, column ) {
  // -------------------------------------------------------------------------------------
  // Test: col()
  // -------------------------------------------------------------------------------------
  size_t ns = 11;
  size_t nv = 7;
    
  Table T(ns,nv);

  for ( size_t s=0; s<ns; s++ ) {
    for ( size_t v=0; v<nv; v++ ) {
      T(s,v) = ELEM(s,v);
    }
  }

  for ( size_t v=0; v<nv; v++ ) {
    real8_t* C = T.col(v);
    for ( size_t s=0; s<ns; s++ ) {
      EXPECT_DOUBLE_EQ( ELEM(s,v), C[s] );
    }
  }
  
}

// =======================================================================================
TEST(test_table_file, read_write ) {
  // -------------------------------------------------------------------------------------
  // Test: read(), write()
  // -------------------------------------------------------------------------------------
  size_t ns = 11;
  size_t nv = 7;
    
  Table T(ns,nv);

  for ( size_t s=0; s<ns; s++ ) {
    for ( size_t v=0; v<nv; v++ ) {
      T(s,v) = ELEM(s,v);
    }
  }

  T.write_ascii( "/tmp/table_test.dat", "%5.2f" );

  Table X( "/tmp/table_test.dat" ); 

  for ( size_t s=0; s<ns; s++ ) {
    for ( size_t v=0; v<nv; v++ ) {
      EXPECT_DOUBLE_EQ( T(s,v), X(s,v) );
    }
  }

}


} // end namespace


// =======================================================================================
// **                               U T E S T _ T A B L E                               **
// ======================================================================== END FILE =====
