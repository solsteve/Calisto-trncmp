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

  {
    Matrix A(4,5,7);
    load_index(A);
    Matrix B;

    B = A;

    EXPECT_TRUE( A.equals(B) );
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
  const char* testN = "A=np.matrix( [[1.01,1.02,1.03,1.04,1.05],"
      "[2.01,2.02,2.03,2.04,2.05],[3.01,3.02,3.03,3.04,3.05],[4.01,4.02,4.03,4.04,4.05]])";

  const char* testO = "A = [1.01,1.02,1.03,1.04,1.05;2.01,2.02,"
      "2.03,2.04,2.05;3.01,3.02,3.03,3.04,3.05;4.01,4.02,4.03,4.04,4.05];";
      
  const char* testS = "A = Matrix(QQ,[[1.01,1.02,1.03,1.04,1.05],\n"
      "[2.01,2.02,2.03,2.04,2.05],\n[3.01,3.02,3.03,3.04,3.05],\n[4.01,4.02,4.03,4.04,4.05]])";
      
  EXPECT_STREQ( testN, N.c_str() );
  EXPECT_STREQ( testO, O.c_str() );
  EXPECT_STREQ( testS, S.c_str() );
}


// =====================================================================================
TEST( test_matrix_source, Col_Major_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::column_major( 5,3,ColMajor );
  Matrix A = Matrix::column_major( 5,3,ColMajor );
  EXPECT_TRUE( A.equals(T) );
}
    

// =====================================================================================
TEST( test_matrix_source, Row_Major_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::column_major( 3,5,ColMajor );
  Matrix A = Matrix::row_major( 3,5,RowMajor );
  EXPECT_TRUE( A.equals(T) );
}


// =====================================================================================
TEST( test_matrix_source, Upper_Triangle_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::row_major( 4, Symetric );
  Matrix A = Matrix::upper_triangle( 4, UpperTri );
  EXPECT_TRUE( A.equals(T) );
}


// =====================================================================================
TEST( test_matrix_source, Lower_Triangle_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::row_major( 4, 4, Symetric );
  Matrix A = Matrix::lower_triangle( 4, LowerTri );
  EXPECT_TRUE( A.equals(T) );
}
    

// =====================================================================================
TEST( test_matrix_source, Diagonal_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::row_major( 4, 4,Diagonal );
  Matrix A = Matrix::diagonal( 4, DVec );
  EXPECT_TRUE( A.equals(T) );
}


// =====================================================================================
TEST( test_matrix_source, Identity_Test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::row_major( 4, 4, Identity );
  Matrix A = Matrix::identity(4);
  EXPECT_TRUE( A.equals(T) );
}
    

// =====================================================================================
TEST( test_matrix_static, zero_test ) {
  // -----------------------------------------------------------------------------------
  Matrix T = Matrix::zero(4);
  Matrix B(4);  B.set();
  EXPECT_TRUE( B.equals(T) );
}

// =======================================================================================
TEST(test_matrix_element, add) {
  // -------------------------------------------------------------------------------------
    
  real8_t A[] = { -1.24, -4.71,  9.19, -1.91,
                  -8.16, -8.84,  3.55, -2.09,
                  -3.27, -1.08, -5.65,  8.04 };

  real8_t B[] = { -6.65, -1.38,  6.21,  1.73,
                  0.34, -9.32, -2.22, -9.97,
                  -4.35,  3.42,  3.60,  7.06 };

  real8_t C[] = { -7.89, -6.09, 15.40, -0.18,
                  -7.82, -18.16,  1.33, -12.06,
                  -7.62,  2.34, -2.05, 15.10 };

  real8_t S0[] = { -8.70, -12.17,  1.73, -9.37,
                   -15.62, -16.30, -3.91, -9.55,
                   -10.73, -8.54, -13.11,  0.58 };

  real8_t S1[] = { -14.11, -8.84, -1.25, -5.73,
                   -7.12, -16.78, -9.68, -17.43,
                   -11.81, -4.04, -3.86, -0.40 };

  real8_t S2[] = { -14.11, -8.84, -1.25, -5.73,
                   -7.12, -16.78, -9.68, -17.43,
                   -11.81, -4.04, -3.86, -0.40 };

  {
    Matrix  X = Matrix::row_major(3,4,A);
    Matrix  S = Matrix::row_major(3,4,S0);
    real8_t s = -7.46;
    X.add(s);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix Z = Matrix::row_major(3,4,C);
    X.add(Y);
    EXPECT_TRUE( X.equals(Z, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix S = Matrix::row_major(3,4,S1);
    real8_t s = -7.46;
    X.add(Y,s);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix S = Matrix::row_major(3,4,S1);
    real8_t s = -7.46;
    X.add(s,Y);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix Z = Matrix::row_major(3,4,C);
    Matrix T(2);
    T.add(X,Y);
    EXPECT_TRUE( T.equals(Z, 1.0e-14) );
  }

}







// =======================================================================================
TEST(test_matrix_element, sub) {
  // -------------------------------------------------------------------------------------
    
  real8_t A[] = { -2.53,  4.88,  6.77,  2.67,  4.85,
                  -3.01, -5.83,  3.33,  3.84, -0.14 };

  real8_t B[] = {  3.42, -4.57,  9.72, -2.64,  0.09,
                   -4.74, -1.17, -6.59, -6.96,  8.02 };

  real8_t C[] = { -5.95,  9.45, -2.95,  5.31,  4.76,
                  1.73, -4.66,  9.92, 10.80, -8.16 };

  real8_t S0[] = { -11.44, -4.03, -2.14, -6.24, -4.06,
                   -11.92, -14.74, -5.58, -5.07, -9.05 };

  real8_t S1[] = { -5.49, -13.48,  0.81, -11.55, -8.82,
                   -13.65, -10.08, -15.50, -15.87, -0.89 };

  real8_t S2[] = {  5.49, 13.48, -0.81, 11.55,  8.82,
                    13.65, 10.08, 15.50, 15.87,  0.89 };

  {
    Matrix  X = Matrix::row_major(2,5,A);
    Matrix  S = Matrix::row_major(2,5,S0);
    real8_t s = 8.91;
    X.sub(s);
    EXPECT_TRUE( X.equals(S, 1.0e-15) );
  }

  {
    Matrix X = Matrix::row_major(2,5,A);
    Matrix Y = Matrix::row_major(2,5,B);
    Matrix Z = Matrix::row_major(2,5,C);
    X.sub(Y);
    EXPECT_TRUE( X.equals(Z, 1.0e-15) );
  }

  {
    Matrix X = Matrix::row_major(2,5,A);
    Matrix Y = Matrix::row_major(2,5,B);
    Matrix S = Matrix::row_major(2,5,S1);
    real8_t s = 8.91;
    X.sub(Y,s);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(2,5,A);
    Matrix Y = Matrix::row_major(2,5,B);
    Matrix S = Matrix::row_major(2,5,S2);
    real8_t s = 8.91;
    X.sub(s,Y);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(2,5,A);
    Matrix Y = Matrix::row_major(2,5,B);
    Matrix Z = Matrix::row_major(2,5,C);
    Matrix T(2);
    T.sub(X,Y);
    EXPECT_TRUE( T.equals(Z, 1.0e-15) );
  }

}


// =======================================================================================
TEST(test_matrix_element, mul) {
  // -------------------------------------------------------------------------------------
    
  real8_t A[] = { -0.02, 7.97, 0.02, 3.7, -2.32, 7.75,
                  6.38, -0.11, 8.41, -4.33, 5.39, 0.15,
                  9.27, -9.81, -7.66, 3.53, -1.72, -6.31 };

  real8_t B[] = { -5.43, -5.25, -7.95, -6.52, -2.36, 9.92,
                  -4.8, -2.18, -7.06, 5.41, 7.92, 4.23,
                  5.8, -9.14, 2.18, 0.52, 3.07, -9.79 };

  real8_t C[] = { 0.1086, -41.8425, -0.159, -24.124, 5.4752, 76.88,
                  -30.624, 0.2398, -59.3746, -23.4253, 42.6888, 0.6345,
                  53.766, 89.6634, -16.6988, 1.8356, -5.2804, 61.7749 };

  real8_t S0[] = { -0.0558, 22.2363, 0.0558, 10.323, -6.4728, 21.6225,
                   17.8002, -0.3069, 23.4639, -12.0807, 15.0381, 0.4185,
                   25.8633, -27.3699, -21.3714, 9.8487, -4.7988, -17.6049 };

  real8_t S1[] = { -15.1497, -14.6475, -22.1805, -18.1908, -6.5844, 27.6768,
                   -13.392, -6.0822, -19.6974, 15.0939, 22.0968, 11.8017,
                   16.182, -25.5006, 6.0822, 1.4508, 8.5653, -27.3141 };

  real8_t S2[] = { -15.1497, -14.6475, -22.1805, -18.1908, -6.5844, 27.6768,
                   -13.392, -6.0822, -19.6974, 15.0939, 22.0968, 11.8017,
                   16.182, -25.5006, 6.0822, 1.4508, 8.5653, -27.3141 };

  {
    Matrix  X = Matrix::row_major(3,6,A);
    Matrix  S = Matrix::row_major(3,6,S0);
    real8_t s = 2.79;
    X.mul(s);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,6,A);
    Matrix Y = Matrix::row_major(3,6,B);
    Matrix Z = Matrix::row_major(3,6,C);
    X.mul(Y);
    EXPECT_TRUE( X.equals(Z, 1.0e-13) );
  }

  {
    Matrix X = Matrix::row_major(3,6,A);
    Matrix Y = Matrix::row_major(3,6,B);
    Matrix S = Matrix::row_major(3,6,S1);
    real8_t s = 2.79;
    X.mul(Y,s);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,6,A);
    Matrix Y = Matrix::row_major(3,6,B);
    Matrix S = Matrix::row_major(3,6,S2);
    real8_t s = 2.79;
    X.mul(s,Y);
    EXPECT_TRUE( X.equals(S, 1.0e-14) );
  }

  {
    Matrix X = Matrix::row_major(3,6,A);
    Matrix Y = Matrix::row_major(3,6,B);
    Matrix Z = Matrix::row_major(3,6,C);
    Matrix T(2);
    T.mul(X,Y);
    EXPECT_TRUE( T.equals(Z, 1.0e-13) );
  }

}



// =======================================================================================
TEST(test_matrix_element, div) {
  // -------------------------------------------------------------------------------------
    
  real8_t A[] = { -8.54, -6.57, -0.53, 7.23,
                  -2.71, -4.77, 0.4, -0.49,
                  -2.17, 8.68, -7.97, -6.24 };

  real8_t B[] = { -6.65, -4.06, -8.21, -3.42,
                  -7.48, 8.35, 0.79, 4.89,
                  8.84, 4.09, 4.07, 2.09 };

  real8_t C[] = {  1.284210526316e+00,  1.618226600985e+00,
                   6.455542021924e-02, -2.114035087719e+00,
                   3.622994652406e-01, -5.712574850299e-01,
                   5.063291139241e-01, -1.002044989775e-01,
                   -2.454751131222e-01,  2.122249388753e+00,
                   -1.958230958231e+00, -2.985645933014e+00 };

  real8_t S0[] = { -1.578558225508e+00, -1.214417744917e+00,
                   -9.796672828096e-02,  1.336414048059e+00,
                   -5.009242144177e-01, -8.817005545287e-01,
                   7.393715341959e-02, -9.057301293900e-02,
                   -4.011090573013e-01,  1.604436229205e+00,
                   -1.473197781885e+00, -1.153419593346e+00 };

  real8_t S1[] = { -1.229205175601e+00, -7.504621072089e-01,
                   -1.517560073937e+00, -6.321626617375e-01,
                   -1.382624768946e+00,  1.543438077634e+00,
                   1.460258780037e-01,  9.038817005545e-01,
                   1.634011090573e+00,  7.560073937153e-01,
                   7.523105360444e-01,  3.863216266174e-01 };

  real8_t S2[] = { -8.135338345865e-01, -1.332512315271e+00,
                   -6.589524969549e-01, -1.581871345029e+00,
                   -7.232620320856e-01,  6.479041916168e-01,
                   6.848101265823e+00,  1.106339468303e+00,
                   6.119909502262e-01,  1.322738386308e+00,
                   1.329238329238e+00,  2.588516746411e+00 };

  {
    Matrix  X = Matrix::row_major(3,4,A);
    Matrix  S = Matrix::row_major(3,4,S0);
    real8_t s = 5.41;
    X.div(s);
    EXPECT_TRUE( X.equals(S, 1.0e-12) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix Z = Matrix::row_major(3,4,C);
    X.div(Y);
    EXPECT_TRUE( X.equals(Z, 1.0e-12) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix S = Matrix::row_major(3,4,S1);
    real8_t s = 5.41;
    X.div(Y,s);
    EXPECT_TRUE( X.equals(S, 1.0e-12) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix S = Matrix::row_major(3,4,S2);
    real8_t s = 5.41;
    X.div(s,Y);
    EXPECT_TRUE( X.equals(S, 1.0e-12) );
  }

  {
    Matrix X = Matrix::row_major(3,4,A);
    Matrix Y = Matrix::row_major(3,4,B);
    Matrix Z = Matrix::row_major(3,4,C);
    Matrix T(2);
    T.div(X,Y);
    EXPECT_TRUE( T.equals(Z, 1.0e-12) );
  }

}

// =======================================================================================
TEST(test_matrix_sum, sum) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { -5.19, 4.93, 9.4, -6.78, -3.67, -4.44,
                     -7.45, 3.41, -2.93, -0.85, 1.5, 6.11,
                     -0.83, -2, 4.64, -3.36, -0.31, -2.36 };

  Matrix  A = Matrix::row_major(3,6,adat);
  EXPECT_NEAR( -10.18, A.sum(), 1.0e-14 );
}

// =======================================================================================
TEST(test_matrix_sum, square) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { -3.79, 7.51, -8.48, -4.27, -4.36,
                     -6.67, -8.46, -2.48, 8.44, 5.05,
                     -8.42, -5.2, -1.42, -7.94, -1.61,
                     -9.42, -8.8, -3.46, -3.98, -1.86 };

  Matrix  A = Matrix::row_major(4,5,adat);
  EXPECT_NEAR( 761.9006, A.sumsq(), 1.0e-12 );
}

// =======================================================================================
TEST(test_matrix_sum, diff) {
  // -------------------------------------------------------------------------------------
   real8_t adat[] = { -6.33, -7.37, -5.05, -5.28, 9.55,
                   0.56, 2.75, -0.84, -7.52, -4.01,
                   1.79, -7.57, 0, 6.32, -1.3,
                   1.01, 5.82, -0.1, -8.45, -7.66 };

    real8_t bdat[] = { 3.01, 6.52, 9.42, 8.64, 9.4,
                   1.18, -4.97, -0.46, 3.86, 8.62,
                   6.86, 5.64, 7.01, 3.06, -4.96,
                   -0.7, 4.61, 5.8, -9.35, 7.91 };

  Matrix  A = Matrix::row_major(4,5,adat);
  Matrix  B = Matrix::row_major(4,5,bdat);
  EXPECT_NEAR( 1588.2914, A.sumsq(B), 1.0e-12 );
}

// =======================================================================================
TEST(test_matrix_linalg, dot) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { -8.83, -0.93, -4.11, 0.71, -6.46,
                     9.97, -1.36, -4.26, -3.94, -0.20,
                     -8.93, -5.40, -4.31, 9.49, -8.19,
                     4.19, -3.81, -9.93, 0.14, -3.97 };

  real8_t bdat[] = { 0.30, 7.91, -4.80, -7.02, 8.06, 2.91,
                     1.22, -2.16, 2.71, -4.59, -7.96, -9.99,
                     -5.14, 9.41, 1.80, -3.75, 1.00, -1.91,
                     6.57, 0.58, 6.56, 8.47, -6.06, 1.11,
                     -4.67, -3.92, 0.53, 5.05, 9.57, 5.45 };

  real8_t cdat[] = { 52.1747, -80.7766, 33.6995, 55.0585, -134.0018, -42.9734,
                     -1.7236, 40.2125, -85.1620, -82.1538, 108.8862, 45.2723,
                     113.4830, -61.9204, 78.3857, 142.6579, -169.1895, 2.0902,
                     67.1087, -36.4252, -49.4968, 6.4489, 15.3277, 47.7400 };

  Matrix  A = Matrix::row_major(4,5,adat);
  Matrix  B = Matrix::row_major(5,6,bdat);
  Matrix  C = Matrix::row_major(4,6,cdat);
  Matrix  T(2);

  T.dot(A,B);

  EXPECT_TRUE( T.equals(C, 1.0e-13) );
}


// =======================================================================================
TEST(test_matrix_linalg, trans) {
  // -------------------------------------------------------------------------------------
  Matrix X = Matrix::row_major(3,5,RowMajor);
  Matrix T = Matrix::column_major(5,3,RowMajor);
  Matrix A(2);
  A.T(X);
  EXPECT_TRUE( A.equals(T) );
}


// =======================================================================================
TEST(test_matrix_linalg, inverse) {
  // -------------------------------------------------------------------------------------
  real8_t adat[] = { 7.30, -5.61, -4.86, -1.00, -7.58,
                     -8.60, 3.49, -3.61, -0.58, 7.07,
                     1.82, -0.16, 0.04, -7.92, -7.87,
                     5.66, -4.78, 7.07, -9.38, 5.72,
                     0.70, -7.05, 9.24, -2.96, 8.23 };

  real8_t bdat[] = {  4.038769272033290204e-03, -6.404971115705972162e-02,
                      -9.362276471842786996e-02,  1.182244819789350920e-01,
                      -1.129538112139867601e-01,
                      -1.054409544416902156e-01, -5.188546364586762993e-02,
                      -3.028958619248770315e-02,  8.421494832369230688e-02,
                      -1.400365436741343450e-01,
                      -9.157091721962687392e-02, -8.760879342226650379e-02,
                      3.881679503394249581e-02, -3.387327778842666448e-02,
                      5.158322513214828875e-02,
                      -6.976403160458548303e-03, -5.385323727221966172e-02,
                      -6.320480542014032810e-02, -5.465470754104554546e-02,
                      1.738327582461646204e-02,
                      9.632959228439350735e-03,  3.999294629435570098e-02,
                      -8.429636178753134590e-02,  8.045800738035768784e-02,
                      -4.050601079380825031e-02 };

  Matrix  A1 = Matrix::row_major(5,5,adat);
  Matrix  A2 = Matrix::row_major(5,5,adat);
  Matrix  B  = Matrix::row_major(5,5,bdat);
  real8_t d  = -6.858754678514717671e+04;
  Matrix C(2);
  Matrix E(2);

  real8_t D = C.inverse(A1);
  EXPECT_TRUE( C.equals(B) );
  EXPECT_NEAR( d, D, 1.0e-10 );
  E.dot( A2, B );
  EXPECT_NEAR( D_FIVE, E.sum(), 1.0e-10 );
}


} // end namespace


// =======================================================================================
// **                              U T E S T _ M A T R I X                              **
// ======================================================================== END FILE =====
