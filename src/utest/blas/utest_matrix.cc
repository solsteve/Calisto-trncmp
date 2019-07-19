// ====================================================================== BEGIN FILE =====
// **                              U T E S T _ M A T R I X                              **
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
/** @brief  Automated testing for Matrix class methods.
 *  @file   utest_matrix.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-16
 *
 *  Provides automated testing for the Matrix class and methods.
 */
// =======================================================================================


#include <limits.h>
#include <Matrix.hh>
#include <gtest/gtest.h>

namespace {
  
real8_t ColMajor[] = { 1.1, 2.1, 3.1,
                       1.2, 2.2, 3.2, 
                       1.3, 2.3, 3.3, 
                       1.4, 2.4, 3.4, 
                       1.5, 2.5, 3.5 };

real8_t RowMajor[] = { 1.1, 1.2, 1.3, 1.4, 1.5,
                       2.1, 2.2, 2.3, 2.4, 2.5,
                       3.1, 3.2, 3.3, 3.4, 3.5 };
  
real8_t Symetric[] = { 1.1, 2.1, 3.1, 4.1,
                       2.1, 2.2, 3.2, 4.2,
                       3.1, 3.2, 3.3, 4.3,
                       4.1, 4.2, 4.3, 4.4 };
		       
real8_t UpperTri[] = { 1.1, 2.1, 3.1, 4.1,
                       /**/ 2.2, 3.2, 4.2,
                       /*     */ 3.3, 4.3,
                       /*          */ 4.4 };
		       
real8_t LowerTri[] = { 1.1, /*          */
                       2.1, 2.2, /*     */ 
                       3.1, 3.2, 3.3, /**/
                       4.1, 4.2, 4.3, 4.4 };

real8_t DVec[]     = { 1.1, 2.2, 3.3, 4.4 };

real8_t Diagonal[] = { 1.1, 0.0, 0.0, 0.0,
                       0.0, 2.2, 0.0, 0.0,
                       0.0, 0.0, 3.3, 0.0,
                       0.0, 0.0, 0.0, 4.4 };

real8_t Identity[] = { 1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 1.0 };

// =====================================================================================
bool check( real8_t v, Matrix& M, real8_t eps = D_EPSILON ) {
  // -----------------------------------------------------------------------------------
  int32_t nr = size( M, 0 );
  int32_t nc = size( M, 1 );
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      real8_t dif = v - M(r,c);
      if ( dif < -eps ) { std::cout << dif << " < -" << eps << "\n"; return false; }
      if ( dif >  eps ) { std::cout << dif << "> " << eps << "\n"; return false; }
    }
  }
  return true;
}

  
// =====================================================================================
void load_index( Matrix& M ) {
  // -----------------------------------------------------------------------------------
  int32_t nr = size( M, 0 );
  int32_t nc = size( M, 1 );
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      real8_t x = (real8_t)(r+1) + ((real8_t)(c+1))/100.0;
      //fprintf( stdout, "%d %d %d %d %g\n", r, nr, c, nc, x );
      M.at(r,c) = x;
    }
  }
}


// =====================================================================================
TEST( test_matrix_construct, Positive ) {
  // -----------------------------------------------------------------------------------
  {
    Matrix A;
    EXPECT_EQ(0, size(A,0) );
    EXPECT_EQ(0, size(A,1) );
  }

  {
    Matrix A(4);
    EXPECT_EQ(4, size(A,0) );
    EXPECT_EQ(4, size(A,1) );
    EXPECT_TRUE( A.isSquare() );
  }

  {
    Matrix A(7,11);
    EXPECT_EQ(7, size(A,0) );
    EXPECT_EQ(11, size(A,1) );
    EXPECT_FALSE( A.isSquare() );
  }

  {
    Matrix A(7,11,9);
    EXPECT_EQ(7, size(A,0) );
    EXPECT_EQ(11, size(A,1) );
    EXPECT_EQ(7, *(A.M()) );
    EXPECT_EQ(11, *(A.N()) );
    EXPECT_EQ(9, *(A.LDA()) );
  }
}


// =====================================================================================
TEST( test_matrix_set, Positive ) {
  // -----------------------------------------------------------------------------------
  {
    Matrix A(2,3,true);
    //A.debug();
    EXPECT_TRUE( check(D_ZERO,A) );
    A.set( D_FOUR );
    //A.debug();
    EXPECT_TRUE( check(D_FOUR,A) );
  }

  {
    Matrix A(4,5,true);
    EXPECT_TRUE( check(D_ZERO,A) );
    A.set( D_FOUR );
    EXPECT_TRUE( check(D_FOUR,A) );
  }
    
  {
    Matrix A(4,5,7,true);
    EXPECT_TRUE( check(D_ZERO,A) );
    A.set( D_FOUR );
    EXPECT_TRUE( check(D_FOUR,A) );
  }   
}


// =====================================================================================
TEST( test_matrix_copy, Positive ) {
  // -----------------------------------------------------------------------------------
  {
    Matrix A(4,5,true);
    Matrix B(3,2,true);
    EXPECT_TRUE( check(D_ZERO,A) );
    EXPECT_TRUE( check(D_ZERO,B) );
    A.set( D_FOUR );
    B.set( D_TWO );
    EXPECT_FALSE( A.equals(B) );
    EXPECT_TRUE( check(D_FOUR,A) );
    EXPECT_TRUE( check(D_TWO,B) );
    EXPECT_EQ(4, size(A,0) );
    EXPECT_EQ(5, size(A,1) );
    EXPECT_EQ(3, size(B,0) );
    EXPECT_EQ(2, size(B,1) );
    B.copy(A);
    EXPECT_TRUE( check(D_FOUR,B) );
    EXPECT_EQ(4, size(B,0) );
    EXPECT_EQ(5, size(B,1) );
    EXPECT_TRUE( A.equals(B) );
  }
    
  {
    Matrix A(4,5,7);
    load_index(A);
    Matrix B(A);
    EXPECT_TRUE( A.equals(B) );
    Matrix C(A,true);
    EXPECT_TRUE( A.equals(C) );
    EXPECT_EQ( *(A.M()), *(B.M()) );
    EXPECT_EQ( *(A.M()), *(C.M()) );
    EXPECT_EQ( *(A.N()), *(B.N()) );
    EXPECT_EQ( *(A.N()), *(C.N()) );
    EXPECT_NE( *(A.LDA()), *(B.LDA()) );
    EXPECT_EQ( *(A.LDA()), *(C.LDA()) );
  }
    
}

// =====================================================================================
TEST( test_matrix_tostring, Print ) {
  // -----------------------------------------------------------------------------------
  Matrix A(4,5,7);
  load_index(A);
  std::string N = toNumpy( "A", A, "%g" );
  std::string O = toOctave( "A", A, "%g" );
  std::string S = toSage( "A", A, "%g" );
  const char* testN = "A=np.matrix( [[1.01,1.02,1.03,1.04,1.05],[2.01,2.02,2.03,2.04,2.05],[3.01,3.02,3.03,3.04,3.05],[4.01,4.02,4.03,4.04,4.05]])";

  const char* testO = "A = [1.01,1.02,1.03,1.04,1.05;2.01,2.02,2.03,2.04,2.05;3.01,3.02,3.03,3.04,3.05;4.01,4.02,4.03,4.04,4.05];";
      
  const char* testS = "A = Matrix(QQ,[[1.01,1.02,1.03,1.04,1.05],\n[2.01,2.02,2.03,2.04,2.05],\n[3.01,3.02,3.03,3.04,3.05],\n[4.01,4.02,4.03,4.04,4.05]])";
      
  EXPECT_STREQ( testN, N.c_str() );
  EXPECT_STREQ( testO, O.c_str() );
  EXPECT_STREQ( testS, S.c_str() );
}


// =====================================================================================
TEST( test_matrix_source, Col_Major_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T(5,3); T.column_major( ColMajor );
  Matrix A(5,3); A.column_major( ColMajor );
  EXPECT_TRUE( A.equals(T) );
}
    

// =====================================================================================
TEST( test_matrix_source, Row_Major_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T(3,5); T.column_major( ColMajor );
  Matrix A(3,5); A.row_major( RowMajor );
  EXPECT_TRUE( A.equals(T) );
}


// =====================================================================================
TEST( test_matrix_source, Upper_Triangle_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T(4); T.row_major( Symetric );
  Matrix A(4); A.upper_triangle( UpperTri );
  EXPECT_TRUE( A.equals(T) );
}


// =====================================================================================
TEST( test_matrix_source, Lower_Triangle_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T(4); T.row_major( Symetric );
  Matrix A(4); A.lower_triangle( LowerTri );
  EXPECT_TRUE( A.equals(T) );
}
    

// =====================================================================================
TEST( test_matrix_source, Diagonal_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T(4); T.row_major( Diagonal );
  Matrix A(4); A.diagonal( DVec );
  EXPECT_TRUE( A.equals(T) );
}


// =====================================================================================
TEST( test_matrix_source, Identity_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T(4); T.row_major( Identity );
  Matrix A(4); A.identity();
  EXPECT_TRUE( A.equals(T) );
}
    

} // end namespace


// =======================================================================================
// **                              U T E S T _ M A T R I X                              **
// ======================================================================== END FILE =====
