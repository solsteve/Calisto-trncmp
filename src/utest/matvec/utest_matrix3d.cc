// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ M A T R I X 3 D                            **
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
/** @brief  Automated testing for Matrix3D class and methods.
 *  @file   utest_matrix3d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides automated testing for Matrix3D class and methods.
 */
// =======================================================================================


#include <limits.h>
#include <Matrix3D.hh>
#include "gtest/gtest.h"
#include <Dice.hh>


namespace {


/*
// =====================================================================================
void out( Matrix3D& M, real8_t a[3][3] ) {
// -----------------------------------------------------------------------------------
fprintf( stdout, "%18.14f %18.14f %18.14f     %18.14f %18.14f %18.14f\n",
M.a00, M.a01, M.a02,    a[0][0], a[0][1], a[0][2] );
fprintf( stdout, "%18.14f %18.14f %18.14f     %18.14f %18.14f %18.14f\n",
M.a10, M.a11, M.a12,    a[1][0], a[1][1], a[1][2] );
fprintf( stdout, "%18.14f %18.14f %18.14f     %18.14f %18.14f %18.14f\n\n",
M.a20, M.a21, M.a22,    a[2][0], a[2][1], a[2][2] );
}
*/

// =====================================================================================
bool check( Matrix3D& M, real8_t a[3][3] ) {
  // -----------------------------------------------------------------------------------
  real8_t sum =
      ((M.a00-a[0][0])*(M.a00-a[0][0])) +
      ((M.a01-a[0][1])*(M.a01-a[0][1])) +
      ((M.a02-a[0][2])*(M.a02-a[0][2])) +
      ((M.a10-a[1][0])*(M.a10-a[1][0])) +
      ((M.a11-a[1][1])*(M.a11-a[1][1])) +
      ((M.a12-a[1][2])*(M.a12-a[1][2])) +
      ((M.a20-a[2][0])*(M.a20-a[2][0])) +
      ((M.a21-a[2][1])*(M.a21-a[2][1])) +
      ((M.a22-a[2][2])*(M.a22-a[2][2]));

  if ( sum < -D_EPSILON ) {
    fprintf( stdout, "%19.12e < %19.12e\n", sum, -D_EPSILON );
    return false;
  }
  if ( sum >  D_EPSILON ) {
    fprintf( stdout, "%19.12e > %19.12e\n", sum,  D_EPSILON );
    return false;
  }

  return true;
}

// =====================================================================================
bool check( Matrix3D& M, real8_t* a ) {
  // -----------------------------------------------------------------------------------
  real8_t sum =
      ((M.a00-a[0])*(M.a00-a[0])) +
      ((M.a01-a[1])*(M.a01-a[1])) +
      ((M.a02-a[2])*(M.a02-a[2])) +
      ((M.a10-a[3])*(M.a10-a[3])) +
      ((M.a11-a[4])*(M.a11-a[4])) +
      ((M.a12-a[5])*(M.a12-a[5])) +
      ((M.a20-a[6])*(M.a20-a[6])) +
      ((M.a21-a[7])*(M.a21-a[7])) +
      ((M.a22-a[8])*(M.a22-a[8]));

  if ( sum < -D_EPSILON ) {
    fprintf( stdout, "%19.12e < %19.12e\n", sum, -D_EPSILON );
    return false;
  }
  if ( sum >  D_EPSILON ) {
    fprintf( stdout, "%19.12e > %19.12e\n", sum,  D_EPSILON );
    return false;
  }

  return true;
}



// =====================================================================================
TEST(test_construct_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  {
    real8_t data[] =
	{ 0.0, 0.0, 0.0,
	  0.0, 0.0, 0.0,
	  0.0, 0.0, 0.0 };
    Matrix3D A;
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2, 1.3,
	  2.1, 2.2, 2.3,
	  3.1, 3.2, 3.3 };
    Matrix3D A( 1.1, 1.2, 1.3,
                2.1, 2.2, 2.3,
                3.1, 3.2, 3.3 );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2, 1.3,
	  2.1, 2.2, 2.3,
	  3.1, 3.2, 3.3 };
    Matrix3D A( data );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2, 1.3,
	  2.1, 2.2, 2.3,
	  3.1, 3.2, 3.3 };
    Matrix3D A( { 1.1, 1.2, 1.3,
            2.1, 2.2, 2.3,
            3.1, 3.2, 3.3 } );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 0.0, 0.0, 0.0,
	  0.0, 0.0, 0.0,
	  0.0, 0.0, 0.0 };
    Matrix3D Z = Matrix3D::Zero();
    Matrix3D A;
    A = Z;
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.0, 0.0, 0.0,
	  0.0, 1.0, 0.0,
	  0.0, 0.0, 1.0 };
    Matrix3D I = Matrix3D::Ident();
    Matrix3D A;
    A = I;
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2, 1.3,
	  2.1, 2.2, 2.3,
	  3.1, 3.2, 3.3 };
    Matrix3D A( data, ROW_MAJOR );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t dataC[] =
	{ 1.1, 2.1, 3.1,
	  1.2, 2.2, 3.2,
	  1.3, 2.3, 3.3 };
    real8_t dataR[] =
	{ 1.1, 1.2, 1.3,
	  2.1, 2.2, 2.3,
	  3.1, 3.2, 3.3 };
    Matrix3D A( dataC, COLUMN_MAJOR );
    EXPECT_TRUE( check( A, dataR ) );
  }

  {
    real8_t dataU[] = {
      1.1, 1.2, 1.3,
      /**/ 2.2, 2.3,
      /*     */ 3.3 };
    real8_t dataR[] =
	{ 1.1, 1.2, 1.3,
	  1.2, 2.2, 2.3,
	  1.3, 2.3, 3.3 };
    Matrix3D A( dataU, UPPER_TRIANGLE );
    EXPECT_TRUE( check( A, dataR ) );
  }

  {
    real8_t dataL[] = {
      1.1,
      2.1, 2.2,
      3.1, 3.2, 3.3 };
    real8_t dataR[] =
	{ 1.1, 2.1, 3.1,
	  2.1, 2.2, 3.2,
	  3.1, 3.2, 3.3 };
    Matrix3D A( dataL, LOWER_TRIANGLE );
    EXPECT_TRUE( check( A, dataR ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1, 3.1,
	  2.1, 2.2, 3.2,
	  3.1, 3.2, 3.3 };
    Matrix3D A( data, ROW_MAJOR );
    Matrix3D B( A );
    EXPECT_TRUE( check( A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1, 3.1,
	  2.1, 2.2, 3.2,
	  3.1, 3.2, 3.3 };
    Matrix3D* A = new Matrix3D( data, ROW_MAJOR );
    Matrix3D B( A );
    EXPECT_TRUE( check( *A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
    delete A;
  }

}

// =====================================================================================
TEST(test_copyset_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  {
    real8_t data[] =
	{ 1.1, 2.1, 3.1,
	  2.1, 2.2, 3.2,
	  3.1, 3.2, 3.3 };
    Matrix3D A( data, ROW_MAJOR );
    Matrix3D B;

    B = A;
    
    EXPECT_TRUE( check( A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1, 3.1,
	  2.1, 2.2, 3.2,
	  3.1, 3.2, 3.3 };
    Matrix3D A( data, ROW_MAJOR );
    Matrix3D B;

    B.copy( A );
    
    EXPECT_TRUE( check( A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1, 3.1,
	  2.1, 2.2, 3.2,
	  3.1, 3.2, 3.3 };
    Matrix3D* A = new Matrix3D( data, ROW_MAJOR );
    Matrix3D B;

    B.copy( A );
    
    EXPECT_TRUE( check( *A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
    delete A;
  }
  
  {
    real8_t data[] =
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    Matrix3D A;

    A.set();
    
    EXPECT_TRUE( check( A, data  ) );
  }
  
  {
    real8_t data[] =
	{ 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2 };
    Matrix3D A;

    A.set( 1.2 );
    
    EXPECT_TRUE( check( A, data  ) );
  }
  
}

// =====================================================================================
TEST(test_loadstore_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  {
    real8_t data[3][3] = { { 1.1, 2.1, 3.1 },
                           { 2.1, 2.2, 3.2 },
                           { 3.1, 3.2, 3.3 } };
    
    real8_t* buffer = new real8_t[9];
    real8_t  box[3][3];
    
    Matrix3D A( data );
    EXPECT_TRUE( check( A, data  ) );

    A.store( buffer );
    Matrix3D B;
    B.load( buffer );
    
    EXPECT_TRUE( check( B, data  ) );

    A.toArray( box );
    Matrix3D C;
    C.fromArray( box );

    EXPECT_TRUE( check( C, data  ) );
    
    delete buffer;
  }

}

// =====================================================================================
TEST(test_unary_scale_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {11.8, 11.4, 4.4},
      {10.5,  8.3, 8.5},
      { 5.4, 10.4, 4.8}
    };
    A += 2.1;
    EXPECT_TRUE( check( A, test ) );
  }
  
  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {7.6, 7.2, 0.2},
      {6.3, 4.1, 4.3},
      {1.2, 6.2, 0.6}
    };
    A -= 2.1;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {20.37, 19.53,  4.83},
      {17.64, 13.02, 13.44},
      { 6.93, 17.43,  5.67}
    };
    A *= 2.1;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {4.85, 4.65, 1.15},
      {4.20, 3.10, 3.20},
      {1.65, 4.15, 1.35}
    };
    A /= 2.0;
    EXPECT_TRUE( check( A, test ) );
  }
}

// =====================================================================================
TEST(test_unary_matrix_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };
  real8_t bdat[3][3] = {
    {1.9, 7.1, 6.9},
    {3.9, 9.3, 7.5},
    {1.0, 5.8, 2.0}
  };

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    real8_t test[3][3] = {
      {11.6, 16.4,  9.2},
      {12.3, 15.5, 13.9},
      { 4.3, 14.1,  4.7}
    };
    A += B;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    real8_t test[3][3] = {
      {7.8,  2.2, -4.6},
      {4.5, -3.1, -1.1},
      {2.3,  2.5,  0.7}
    };
    A -= B;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    real8_t test[3][3] = {
      {18.43, 66.03, 15.87},
      {32.76, 57.66, 48.00},
      { 3.30, 48.14,  5.40}
    };
    A *= B;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    real8_t test[3][3] = {
      {5.10526316, 1.30985915, 0.33333333},
      {2.15384615, 0.66666667, 0.85333333},
      {3.3       , 1.43103448, 1.35      }
    };
    A /= B;
    EXPECT_TRUE( check( A, test ) );
  }
}


// =====================================================================================
TEST(test_binary_add_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };
  
  real8_t bdat[3][3] = {
    {1.9, 7.1, 6.9},
    {3.9, 9.3, 7.5},
    {1.0, 5.8, 2.0}
  };

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {11.8, 11.4, 4.4},
      {10.5,  8.3, 8.5},
      { 5.4, 10.4, 4.8}
    };
    B = 2.1 + A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {11.8, 11.4, 4.4},
      {10.5,  8.3, 8.5},
      { 5.4, 10.4, 4.8}
    };
    B = A + 2.1;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    Matrix3D C;
    real8_t test[3][3] = {
      {11.6, 16.4,  9.2},
      {12.3, 15.5, 13.9},
      { 4.3, 14.1,  4.7}
    };
    C = A + B;
    EXPECT_TRUE( check( C, test ) );
  }
}



// =====================================================================================
TEST(test_binary_sub_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };
  
  real8_t bdat[3][3] = {
    {1.9, 7.1, 6.9},
    {3.9, 9.3, 7.5},
    {1.0, 5.8, 2.0}
  };

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {-7.6, -7.2, -0.2},
      {-6.3, -4.1, -4.3},
      {-1.2, -6.2, -0.6}
    };
    B = 2.1 - A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {7.6, 7.2, 0.2},
      {6.3, 4.1, 4.3},
      {1.2, 6.2, 0.6}
    };
    B = A - 2.1;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    Matrix3D C;
    real8_t test[3][3] = {
      {7.8,  2.2, -4.6},
      {4.5, -3.1, -1.1},
      {2.3,  2.5,  0.7}
    };
    C = A - B;
    EXPECT_TRUE( check( C, test ) );
  }
}

// =====================================================================================
TEST(test_binary_mul_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };
  
  real8_t bdat[3][3] = {
    {1.9, 7.1, 6.9},
    {3.9, 9.3, 7.5},
    {1.0, 5.8, 2.0}
  };

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {20.37, 19.53,  4.83},
      {17.64, 13.02, 13.44},
      { 6.93, 17.43,  5.67}
    };
    B = 2.1 * A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {20.37, 19.53,  4.83},
      {17.64, 13.02, 13.44},
      { 6.93, 17.43,  5.67}
    };
    B = A * 2.1;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    Matrix3D C;
    real8_t test[3][3] = {
      {18.43, 66.03, 15.87},
      {32.76, 57.66, 48.00},
      { 3.30, 48.14,  5.40}
    };
    C = A * B;
    EXPECT_TRUE( check( C, test ) );
  }
}

// =====================================================================================
TEST(test_binary_div_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };
  
  real8_t bdat[3][3] = {
    {1.9, 7.1, 6.9},
    {3.9, 9.3, 7.5},
    {1.0, 5.8, 2.0}
  };

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {0.20618557, 0.21505376, 0.86956522},
      {0.23809524, 0.32258065, 0.31250000},
      {0.60606061, 0.24096386, 0.74074074}
    };
    B = 2.0 / A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B;
    real8_t test[3][3] = {
      {4.85, 4.65, 1.15},
      {4.20, 3.10, 3.20},
      {1.65, 4.15, 1.35}
    };
    B = A / 2.0;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    Matrix3D C;
    real8_t test[3][3] = {
      {5.10526316, 1.30985915, 0.33333333},
      {2.15384615, 0.66666667, 0.85333333},
      {3.30000000, 1.43103448, 1.35000000}
    };
    C = A / B;
    EXPECT_TRUE( check( C, test ) );
  }
}

// =====================================================================================
TEST(test_inverse_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };

  {
    real8_t D = -254.096;
    
    Matrix3D A( adat );
    Matrix3D B = A.inverse();
    
    EXPECT_DOUBLE_EQ( D, A.det() );
    
    real8_t test[3][3] = {
      {  0.143174233360620,    0.0236918330079970, -0.178121654807632 },
      {  0.00613941187582646, -0.0732006800579309,  0.168282853724577 },
      { -0.193863736540520,    0.196067627983124,   0.0707606573893332}
    };
    
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix3D A( adat );
    Matrix3D B = A.T();
    real8_t test[3][3] = {
      {9.7, 8.4, 3.3},
      {9.3, 6.2, 8.3},
      {2.3, 6.4, 2.7}
    };
    EXPECT_TRUE( check( B, test ) );
  }

}

// =====================================================================================
TEST(test_get_slice_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t data[3][3] = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
    {3.1, 3.2, 3.3}
  };

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getRow(test, 0);
    EXPECT_DOUBLE_EQ( 1.1, test[0] );
    EXPECT_DOUBLE_EQ( 1.2, test[1] );
    EXPECT_DOUBLE_EQ( 1.3, test[2] );
  }

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getRow(test, 1);
    EXPECT_DOUBLE_EQ( 2.1, test[0] );
    EXPECT_DOUBLE_EQ( 2.2, test[1] );
    EXPECT_DOUBLE_EQ( 2.3, test[2] );
  }

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getRow(test, 2);
    EXPECT_DOUBLE_EQ( 3.1, test[0] );
    EXPECT_DOUBLE_EQ( 3.2, test[1] );
    EXPECT_DOUBLE_EQ( 3.3, test[2] );
  }

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getColumn(test, 0);
    EXPECT_DOUBLE_EQ( 1.1, test[0] );
    EXPECT_DOUBLE_EQ( 2.1, test[1] );
    EXPECT_DOUBLE_EQ( 3.1, test[2] );
  }

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getColumn(test, 1);
    EXPECT_DOUBLE_EQ( 1.2, test[0] );
    EXPECT_DOUBLE_EQ( 2.2, test[1] );
    EXPECT_DOUBLE_EQ( 3.2, test[2] );
  }

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getColumn(test, 2);
    EXPECT_DOUBLE_EQ( 1.3, test[0] );
    EXPECT_DOUBLE_EQ( 2.3, test[1] );
    EXPECT_DOUBLE_EQ( 3.3, test[2] );
  }

  {
    Matrix3D A( data );
    real8_t test[3];
    A.getDiagonal(test);
    EXPECT_DOUBLE_EQ( 1.1, test[0] );
    EXPECT_DOUBLE_EQ( 2.2, test[1] );
    EXPECT_DOUBLE_EQ( 3.3, test[2] );
  }

  
}

// =====================================================================================
TEST(test_set_slice_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t data[3][3] = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
    {3.1, 3.2, 3.3}
  };

  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {4.4, 5.5, 6.6},
      {2.1, 2.2, 2.3},
      {3.1, 3.2, 3.3}
    };
    A.setRow( tset, 0 );
    EXPECT_TRUE( check( A, test ) );
  }
    
  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {1.1, 1.2, 1.3},
      {4.4, 5.5, 6.6},
      {3.1, 3.2, 3.3}
    };
    A.setRow( tset, 1 );
    EXPECT_TRUE( check( A, test ) );
  }
    
  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {1.1, 1.2, 1.3},
      {2.1, 2.2, 2.3},
      {4.4, 5.5, 6.6}
    };
    A.setRow( tset, 2 );
    EXPECT_TRUE( check( A, test ) );
  }
    
  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {4.4, 1.2, 1.3},
      {5.5, 2.2, 2.3},
      {6.6, 3.2, 3.3}
    };
    A.setColumn( tset, 0 );
    EXPECT_TRUE( check( A, test ) );
  }
    
  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {1.1, 4.4, 1.3},
      {2.1, 5.5, 2.3},
      {3.1, 6.6, 3.3}
    };
    A.setColumn( tset, 1 );
    EXPECT_TRUE( check( A, test ) );
  }
    
  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {1.1, 1.2, 4.4},
      {2.1, 2.2, 5.5},
      {3.1, 3.2, 6.6}
    };
    A.setColumn( tset, 2 );
    EXPECT_TRUE( check( A, test ) );
  }
    
  {
    Matrix3D A( data );
    real8_t tset[3] = {4.4, 5.5, 6.6};
    real8_t test[3][3] = {
      {4.4, 1.2, 1.3},
      {2.1, 5.5, 2.3},
      {3.1, 3.2, 6.6}
    };
    A.setDiagonal( tset );
    EXPECT_TRUE( check( A, test ) );
  }
    
}


// =====================================================================================
TEST(test_swap_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {9.7, 9.3, 2.3},
    {8.4, 6.2, 6.4},
    {3.3, 8.3, 2.7}
  };
  real8_t bdat[3][3] = {
    {6.9, 6.1, 5.3},
    {4.2, 5.3, 5.4},
    {8.8, 4.5, 7.4}
  };

  {
    Matrix3D A( adat );
    Matrix3D B( bdat );
    EXPECT_TRUE( check( A, adat ) );
    EXPECT_TRUE( check( B, bdat ) );
    A.swap( B );
    EXPECT_TRUE( check( A, bdat ) );
    EXPECT_TRUE( check( B, adat ) );
  }

  // =======================================================
  
  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {8.4, 6.2, 6.4},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(0,0);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {8.4, 6.2, 6.4},
      {9.7, 9.3, 2.3},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(0,1);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {3.3, 8.3, 2.7},
      {8.4, 6.2, 6.4},
      {9.7, 9.3, 2.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(0,2);
    EXPECT_TRUE( check( A, test ) );
  };

  // ------------------------------------------------

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {8.4, 6.2, 6.4},
      {9.7, 9.3, 2.3},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(1,0);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {8.4, 6.2, 6.4},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(1,1);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {3.3, 8.3, 2.7},
      {8.4, 6.2, 6.4}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(1,2);
    EXPECT_TRUE( check( A, test ) );
  };

  // ------------------------------------------------

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {3.3, 8.3, 2.7},
      {8.4, 6.2, 6.4},
      {9.7, 9.3, 2.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(2,0);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {3.3, 8.3, 2.7},
      {8.4, 6.2, 6.4}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(2,1);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {8.4, 6.2, 6.4},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_row(2,2);
    EXPECT_TRUE( check( A, test ) );
  };

  // =======================================================
  
  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {8.4, 6.2, 6.4},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(0,0);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.3, 9.7, 2.3},
      {6.2, 8.4, 6.4},
      {8.3, 3.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(0,1);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {2.3, 9.3, 9.7 },
      {6.4, 6.2, 8.4 },
      {2.7, 8.3, 3.3 }
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(0,2);
    EXPECT_TRUE( check( A, test ) );
  };

  // ------------------------------------------------

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.3, 9.7, 2.3},
      {6.2, 8.4, 6.4},
      {8.3, 3.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(1,0);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {8.4, 6.2, 6.4},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(1,1);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 2.3, 9.3},
      {8.4, 6.4, 6.2},
      {3.3, 2.7, 8.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(1,2);
    EXPECT_TRUE( check( A, test ) );
  };

  // ------------------------------------------------

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {2.3, 9.3, 9.7 },
      {6.4, 6.2, 8.4 },
      {2.7, 8.3, 3.3 }
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(2,0);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 2.3, 9.3},
      {8.4, 6.4, 6.2},
      {3.3, 2.7, 8.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(2,1);
    EXPECT_TRUE( check( A, test ) );
  };

  {
    Matrix3D A( adat );
    real8_t test[3][3] = {
      {9.7, 9.3, 2.3},
      {8.4, 6.2, 6.4},
      {3.3, 8.3, 2.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    A.swap_col(2,2);
    EXPECT_TRUE( check( A, test ) );
  };


}


// =====================================================================================
TEST(test_sum_mat3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[3][3] = {{6.4,1.3,2.1},{3.1,3.2,5.8},{4.4,6.1,6.4}};
  real8_t bdat[3][3] = {{6.5,4.7,2.1},{4.2,4.8,4.1},{9.8,2.7,5.1}};
  Matrix3D A( adat );
  Matrix3D B( bdat );

  EXPECT_DOUBLE_EQ( 38.80, sum(A) );
  EXPECT_DOUBLE_EQ( 198.08, sumsq(A) );
  EXPECT_DOUBLE_EQ( 60.64, sumsq(A,B) );
}

} // end namespace


// =======================================================================================
// **                            U T E S T _ M A T R I X 3 D                            **
// ======================================================================== END FILE =====
