// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ M A T R I X 2 D                            **
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
/** @brief  Automated testing for Matrix2D class and methods.
 *  @file   utest_matrix2d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides automated testing for Matrix2D class and methods.
 */
// =======================================================================================


#include <limits.h>
#include <Matrix2D.hh>
#include "gtest/gtest.h"
#include <Dice.hh>


namespace {


// =====================================================================================
void out( Matrix2D& M, real8_t a[2][2] ) {
  // -----------------------------------------------------------------------------------
  fprintf( stdout, "%18.14f %18.14f     %18.14f %18.14f\n",
           M.a00, M.a01,    a[0][0], a[0][1] );
  fprintf( stdout, "%18.14f %18.14f     %18.14f %18.14f\n",
           M.a10, M.a11,    a[1][0], a[1][1] );
}

// =====================================================================================
void out( Matrix2D& M, real8_t* a ) {
  // -----------------------------------------------------------------------------------
  fprintf( stdout, "%18.14f %18.14f     %18.14f %18.14f\n",
           M.a00, M.a01,    a[0], a[1] );
  fprintf( stdout, "%18.14f %18.14f     %18.14f %18.14f\n",
           M.a10, M.a11,    a[2], a[3] );
}

// =====================================================================================
bool check( Matrix2D& M, real8_t a[2][2] ) {
  // -----------------------------------------------------------------------------------
  real8_t sum =
      ((M.a00-a[0][0])*(M.a00-a[0][0])) +
      ((M.a01-a[0][1])*(M.a01-a[0][1])) +
      ((M.a10-a[1][0])*(M.a10-a[1][0])) +
      ((M.a11-a[1][1])*(M.a11-a[1][1]));

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
bool check( Matrix2D& M, real8_t* a ) {
  // -----------------------------------------------------------------------------------
  real8_t sum =
      ((M.a00-a[0])*(M.a00-a[0])) +
      ((M.a01-a[1])*(M.a01-a[1])) +
      ((M.a10-a[2])*(M.a10-a[2])) +
      ((M.a11-a[3])*(M.a11-a[3]));

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
TEST(test_construct3, Positive) {
  // -----------------------------------------------------------------------------------
  {
    real8_t data[] =
	{ 0.0, 0.0,
	  0.0, 0.0 };
    Matrix2D A;
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2,
	  2.1, 2.2 };
    Matrix2D A( 1.1, 1.2,
                2.1, 2.2 );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2,
	  2.1, 2.2 };
    Matrix2D A( data );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2,
	  2.1, 2.2, };
    Matrix2D A( { 1.1, 1.2,
                  2.1, 2.2 } );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 0.0, 0.0,
	  0.0, 0.0 };
    Matrix2D Z = Matrix2D::Zero();
    Matrix2D A;
    A = Z;
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.0, 0.0,
	  0.0, 1.0 };
    Matrix2D I = Matrix2D::Ident();
    Matrix2D A;
    A = I;
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t data[] =
	{ 1.1, 1.2,
	  2.1, 2.2 };
    Matrix2D A( data, ROW_MAJOR );
    EXPECT_TRUE( check( A, data ) );
  }

  {
    real8_t dataC[] =
	{ 1.1, 2.1,
	  1.2, 2.2 };
    real8_t dataR[] =
	{ 1.1, 1.2,
	  2.1, 2.2 };
    Matrix2D A( dataC, COLUMN_MAJOR );
    EXPECT_TRUE( check( A, dataR ) );
  }

  {
    real8_t dataU[] = {
      1.1, 1.2,
      /**/ 2.2 };
    real8_t dataR[] =
	{ 1.1, 1.2,
	  1.2, 2.2 };
    Matrix2D A( dataU, UPPER_TRIANGLE );
    EXPECT_TRUE( check( A, dataR ) );
  }

  {
    real8_t dataL[] = {
      1.1,
      2.1, 2.2 };
    real8_t dataR[] =
	{ 1.1, 2.1,
	  2.1, 2.2 };
    Matrix2D A( dataL, LOWER_TRIANGLE );
    EXPECT_TRUE( check( A, dataR ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1,
	  2.1, 2.2 };
    Matrix2D A( data, ROW_MAJOR );
    Matrix2D B( A );
    EXPECT_TRUE( check( A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1,
	  2.1, 2.2 };
    Matrix2D* A = new Matrix2D( data, ROW_MAJOR );
    Matrix2D B( A );
    EXPECT_TRUE( check( *A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
    delete A;
  }

}

// =====================================================================================
TEST(test_copyset3, Positive) {
  // -----------------------------------------------------------------------------------
  {
    real8_t data[] =
	{ 1.1, 2.1,
	  2.1, 2.2 };
    Matrix2D A( data, ROW_MAJOR );
    Matrix2D B;

    B = A;
    
    EXPECT_TRUE( check( A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1,
	  2.1, 2.2 };
    Matrix2D A( data, ROW_MAJOR );
    Matrix2D B;

    B.copy( A );
    
    EXPECT_TRUE( check( A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
  }

  {
    real8_t data[] =
	{ 1.1, 2.1,
	  2.1, 2.2 };
    Matrix2D* A = new Matrix2D( data, ROW_MAJOR );
    Matrix2D B;

    B.copy( A );
    
    EXPECT_TRUE( check( *A, data  ) );
    EXPECT_TRUE( check( B, data  ) );
    delete A;
  }
  
  {
    real8_t data[] =
	{ 0.0, 0.0, 0.0, 0.0 };
    Matrix2D A;

    A.set();
    
    EXPECT_TRUE( check( A, data  ) );
  }
  
  {
    real8_t data[] =
	{ 1.2, 1.2, 1.2, 1.2 };
    Matrix2D A;

    A.set( 1.2 );
    
    EXPECT_TRUE( check( A, data  ) );
  }
  
}

// =====================================================================================
TEST(test_loadstore, Positive) {
  // -----------------------------------------------------------------------------------
  {
    real8_t data[2][2] = { { 1.1, 2.1, },
                           { 2.1, 2.2 } };
    
    real8_t* buffer = new real8_t[4];
    real8_t  box[2][2];
    
    Matrix2D A( data );
    EXPECT_TRUE( check( A, data  ) );

    A.store( buffer );
    Matrix2D B;
    B.load( buffer );
    
    EXPECT_TRUE( check( B, data  ) );

    A.toArray( box );
    Matrix2D C;
    C.fromArray( box );

    EXPECT_TRUE( check( C, data  ) );
    
    delete buffer;
  }

}

// =====================================================================================
TEST(test_unary_scale3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };

  {
    Matrix2D A( adat );
    real8_t test[2][2] = {
      {11.8, 11.4},
      {10.5,  8.3}
    };
    A += 2.1;
    EXPECT_TRUE( check( A, test ) );
  }
  
  {
    Matrix2D A( adat );
    real8_t test[2][2] = {
      {7.6, 7.2},
      {6.3, 4.1}
    };
    A -= 2.1;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    real8_t test[2][2] = {
      {20.37, 19.53},
      {17.64, 13.02}
    };
    A *= 2.1;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    real8_t test[2][2] = {
      {4.85, 4.65},
      {4.20, 3.10}
    };
    A /= 2.0;
    EXPECT_TRUE( check( A, test ) );
  }
}

// =====================================================================================
TEST(test_unary_matrix3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };
  real8_t bdat[2][2] = {
    {1.9, 7.1},
    {3.9, 9.3}
  };

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    real8_t test[2][2] = {
      {11.6, 16.4},
      {12.3, 15.5}
    };
    A += B;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    real8_t test[2][2] = {
      {7.8,  2.2},
      {4.5, -3.1}
    };
    A -= B;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    real8_t test[2][2] = {
      {18.43, 66.03},
      {32.76, 57.66}
    };
    A *= B;
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    real8_t test[2][2] = {
      {5.10526316, 1.30985915},
      {2.15384615, 0.66666667}
    };
    A /= B;
    EXPECT_TRUE( check( A, test ) );
  }
}


// =====================================================================================
TEST(test_binary_add3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };
  
  real8_t bdat[2][2] = {
    {1.9, 7.1},
    {3.9, 9.3}
  };

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {11.8, 11.4},
      {10.5,  8.3}
    };
    B = 2.1 + A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {11.8, 11.4},
      {10.5,  8.3}
    };
    B = A + 2.1;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    Matrix2D C;
    real8_t test[2][2] = {
      {11.6, 16.4},
      {12.3, 15.5}
    };
    C = A + B;
    EXPECT_TRUE( check( C, test ) );
  }
}



// =====================================================================================
TEST(test_binary_sub3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };
  
  real8_t bdat[2][2] = {
    {1.9, 7.1},
    {3.9, 9.3}
  };

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {-7.6, -7.2},
      {-6.3, -4.1}
    };
    B = 2.1 - A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {7.6, 7.2},
      {6.3, 4.1}
    };
    B = A - 2.1;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    Matrix2D C;
    real8_t test[2][2] = {
      {7.8,  2.2},
      {4.5, -3.1}
    };
    C = A - B;
    EXPECT_TRUE( check( C, test ) );
  }
}

// =====================================================================================
TEST(test_binary_mul3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };
  
  real8_t bdat[2][2] = {
    {1.9, 7.1},
    {3.9, 9.3}
  };

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {20.37, 19.53},
      {17.64, 13.02}
    };
    B = 2.1 * A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {20.37, 19.53},
      {17.64, 13.02}
    };
    B = A * 2.1;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    Matrix2D C;
    real8_t test[2][2] = {
      {18.43, 66.03},
      {32.76, 57.66}
    };
    C = A * B;
    EXPECT_TRUE( check( C, test ) );
  }
}

// =====================================================================================
TEST(test_binary_div3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };
  
  real8_t bdat[2][2] = {
    {1.9, 7.1},
    {3.9, 9.3}
  };

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {0.20618557, 0.21505376},
      {0.23809524, 0.32258065}
    };
    B = 2.0 / A;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B;
    real8_t test[2][2] = {
      {4.85, 4.65},
      {4.20, 3.10}
    };
    B = A / 2.0;
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B( bdat );
    Matrix2D C;
    real8_t test[2][2] = {
      {5.10526316, 1.30985915},
      {2.15384615, 0.66666667}
    };
    C = A / B;
    EXPECT_TRUE( check( C, test ) );
  }
}

// =====================================================================================
TEST(test_inverse3, Positive) {
  // -----------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {9.7, 9.3},
    {8.4, 6.2}
  };

  {
    real8_t D = -17.98;
    
    Matrix2D A( adat );
    Matrix2D B = A.inverse();
    
    EXPECT_DOUBLE_EQ( D, A.det() );
    
    real8_t test[2][2] = {
      { -0.344827586206897,  0.517241379310345 },
      {  0.467185761957731, -0.539488320355951 }
    };
    
    EXPECT_TRUE( check( B, test ) );
  }

  {
    Matrix2D A( adat );
    Matrix2D B = A.T();
    real8_t test[2][2] = {
      {9.7, 8.4},
      {9.3, 6.2}
    };
    EXPECT_TRUE( check( B, test ) );
  }

}

} // end namespace


// =======================================================================================
// **                            U T E S T _ M A T R I X 3 D                            **
// ======================================================================== END FILE =====
