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
#include <Array.hh>
#include <gtest/gtest.h>

namespace {

// =======================================================================================
inline int32_t IELEM( int32_t i, int32_t j ) {
  // -------------------------------------------------------------------------------------
  return 1000*(i+1) + (j+1);
}


// =======================================================================================
inline real8_t RELEM( int32_t i, int32_t j ) {
  // -------------------------------------------------------------------------------------
  return ((real8_t)(i+1)) + (((real8_t)(j+1))/100.0);
}


// =======================================================================================
TEST(test_array_creation, empty ) {
  // -------------------------------------------------------------------------------------
  // Test: size(), Array.size()
  // -------------------------------------------------------------------------------------
  Array<int32_t> IT;
  EXPECT_EQ( 0, size(IT,0) );
  EXPECT_EQ( 0, size(IT,1) );
  Array<real8_t> RT;
  EXPECT_EQ( 0, size(RT,0) );
  EXPECT_EQ( 0, size(RT,1) );
}


// =======================================================================================
TEST(test_array_creation, setsize ) {
  // -------------------------------------------------------------------------------------
  // Test: Array(nr,nc)
  // -------------------------------------------------------------------------------------
  Array<int32_t> IT(17,34);
  EXPECT_EQ( 17, size(IT,0) );
  EXPECT_EQ( 34, size(IT,1) );
}


// =======================================================================================
TEST(test_array_creation, initalize ) {
  // -------------------------------------------------------------------------------------
  // Test: Array(nr,nc)
  // -------------------------------------------------------------------------------------

  int32_t data[] = { 1, 2,  3,  4,
                     5, 6,  7,  8,
                     9, 10, 11, 12 };

  int32_t nr = 3;
  int32_t nc = 4;
    
  Array<int32_t> IT(nr, nc, data);
  EXPECT_EQ( nr, size(IT,0) );
  EXPECT_EQ( nc, size(IT,1) );

  int32_t idx = 0;
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_EQ( data[idx], IT(r,c) );
      idx++;
    }
  }
}


// =======================================================================================
TEST(test_array_creation, sized ) {
  // -------------------------------------------------------------------------------------
  // Test: resize()
  // -------------------------------------------------------------------------------------
  Array<int> T(17,5);
  EXPECT_EQ( 17, size(T,0) );
  EXPECT_EQ(  5, size(T,1) );
  T.resize(5,17);
  EXPECT_EQ(  5, size(T,0) );
  EXPECT_EQ( 17, size(T,1) );
  T.resize(23,19);
  EXPECT_EQ( 23, size(T,0) );
  EXPECT_EQ( 19, size(T,1) );
}


// =======================================================================================
TEST(test_array_copy, real ) {
  // -------------------------------------------------------------------------------------
  // Test: Array(src), operator(), at(), copy(), operator=
  // -------------------------------------------------------------------------------------
  int32_t nr = 11;
  int32_t nc = 7;

  Array<real8_t> T(nr,nc);

  for ( int32_t s=0; s<nr; s++ ) {
    for ( int32_t v=0; v<nc; v++ ) {
      T(s,v) = RELEM(s,v);
    }
  }

  Array<real8_t> K(T);
    
  for ( int32_t v=0; v<nc; v++ ) {
    for ( int32_t s=0; s<nr; s++ ) {
      EXPECT_DOUBLE_EQ( RELEM(s,v), K.get(s,v) );
    }
  }

  Array<real8_t> X(2,3);

  X = T;
    
  for ( int32_t v=0; v<nc; v++ ) {
    for ( int32_t s=0; s<nr; s++ ) {
      EXPECT_DOUBLE_EQ( RELEM(s,v), X(s,v) );
    }
  }

}

// =======================================================================================
TEST(test_array_copy, integer ) {
  // -------------------------------------------------------------------------------------
  // Test: operator(), at(), copy(), operator=
  // -------------------------------------------------------------------------------------
  int32_t nr = 11;
  int32_t nc = 7;
    
  Array<int32_t> T(nr,nc);

  for ( int32_t s=0; s<nr; s++ ) {
    for ( int32_t v=0; v<nc; v++ ) {
      T(s,v) = IELEM(s,v);
    }
  }

  Array<int32_t> K(T);
    
  for ( int32_t v=0; v<nc; v++ ) {
    for ( int32_t s=0; s<nr; s++ ) {
      EXPECT_EQ( IELEM(s,v), K.get(s,v) );
    }
  }

  Array<int32_t> X(2,3);

  X = T;
    
  for ( int32_t v=0; v<nc; v++ ) {
    for ( int32_t s=0; s<nr; s++ ) {
      EXPECT_EQ( IELEM(s,v), X(s,v) );
    }
  }

}


// =======================================================================================
TEST(test_array_access, set ) {
  // -------------------------------------------------------------------------------------
  // Test: set()
  // -------------------------------------------------------------------------------------
  int32_t nr = 13;
  int32_t nc = 9;
    
  {
    Array<real8_t> T(nr,nc);

    T.set(13.7);

    for ( int32_t v=0; v<nc; v++ ) {
      for ( int32_t s=0; s<nr; s++ ) {
	EXPECT_DOUBLE_EQ( 13.7, T(s,v) );
      }
    }
  }

  {
    Array<int32_t> T(nr,nc);

    for ( int32_t s=0; s<nr; s++ ) {
      for ( int32_t v=0; v<nc; v++ ) {
	T.set( s, v, IELEM(s,v) );
      }
    }

    Array<int32_t> K(T);
    
    for ( int32_t v=0; v<nc; v++ ) {
      for ( int32_t s=0; s<nr; s++ ) {
	EXPECT_EQ( IELEM(s,v), K.get(s,v) );
      }
    }
  }

}


// =======================================================================================
TEST(test_array_access, get ) {
  // -------------------------------------------------------------------------------------
  // Test: get()
  // -------------------------------------------------------------------------------------
  int32_t nr = 13;
  int32_t nc = 9;
    
  Array<int32_t> T(nr,nc);
  
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      T.set( r, c, IELEM(r,c) );
    }
  }
  
  Array<int32_t> K(T);
  
  for ( int32_t c=0; c<nc; c++ ) {
    for ( int32_t r=0; r<nr; r++ ) {
      EXPECT_EQ( IELEM(r,c), K.get(r,c) );
    }
  }

  for ( int32_t c=0; c<nc; c++ ) {
    for ( int32_t r=0; r<nr; r++ ) {
      EXPECT_EQ( IELEM(r,c), K(r,c) );
    }
  }

  for ( int32_t r=0; r<nr; r++ ) {
    int32_t* P = K.get(r);
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_EQ( IELEM(r,c), P[c] );
    }
  }

  for ( int32_t r=0; r<nr; r++ ) {
    int32_t* P = K(r);
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_EQ( IELEM(r,c), P[c] );
    }
  }


}


// =======================================================================================
TEST(test_array_transfer, load_store ) {
  // -------------------------------------------------------------------------------------
  // Test: get()
  // -------------------------------------------------------------------------------------

  const int32_t nr = 23;
  const int32_t nc = 37;

  const int32_t nb = nr * nc;

  real8_t* buffer = new real8_t[ nb ];

  Array<real8_t> A( nr, nc );
  Array<real8_t> B( nr, nc );


  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      A(r,c) = RELEM(r,c);
    }
  }
  
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_DOUBLE_EQ( RELEM(r,c), A(r, c) );
    }
  }
  
  B.set();
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_DOUBLE_EQ( D_ZERO, B(r, c) );
    }
  }

  A.store( buffer );

  int32_t idx = 0;
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_DOUBLE_EQ( RELEM(r,c), buffer[idx] );
      idx++;
    }
  }
  
  B.load( buffer );

  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      EXPECT_DOUBLE_EQ( RELEM(r,c), B(r, c) );
    }
  }
  
  delete[] buffer;
}


} // end namespace


// =======================================================================================
// **                               U T E S T _ A R R A Y                               **
// ======================================================================== END FILE =====
