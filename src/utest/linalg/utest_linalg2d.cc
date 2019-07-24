// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ L I N A L G 2 D                            **
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
/** @brief  Automated testing for LinAlg2 methods.
 *  @file   utest_linalg2d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides automated testing for combination of Vector2D and Matrix2D class and methods.
 */
// =======================================================================================


#include <limits.h>
#include <LinAlg2D.hh>
#include "gtest/gtest.h"


real8_t cov2[2][2] = {
   {  5.0114993403723233e+01,  7.7824477842618016e+00 },
   {  7.7824477842618016e+00,  1.0072383793168383e+01 }
};


real8_t data2[][2] = {
   {  2.0021599185834706e+01,  7.6280043953843304e+00 },
   {  1.6475777814788966e+01,  1.5161316522968368e+01 },
   {  4.4770759383620966e+00,  7.0864730814916195e+00 },
   {  1.0750572065809166e+01,  5.9116578069679981e+00 },
   {  3.1332673036705736e+00,  8.7638298595203317e+00 },
   {  1.5322193717054899e+01,  7.8156047324936715e+00 },
   {  1.0971079545097298e+01,  5.2926540325857268e+00 },
   {  8.4319767368195322e+00,  8.0779894289756626e+00 },
   {  1.1754632940067124e+01,  4.1499420151847914e+00 },
   { -8.9948740825029361e-01,  3.0171467151149995e+00 },
   {  4.9297783842545009e+00,  5.2394175704079826e+00 },
   {  7.1112519960760361e+00,  1.1537230105337246e+01 },
   {  3.2553508875056885e+00,  6.0562747824038468e+00 },
   {  1.1107486195380142e+01,  3.3196990455897288e+00 },
   {  1.4489755272857676e+00,  6.9945143758665518e+00 },
   {  1.2274951694744333e+01,  3.7263315698329182e+00 },
   { -6.5861347419643632e+00,  4.4938930998747955e+00 },
   {  2.7139808923916261e-02, -3.3086800386671084e-01 },
   {  1.1899779166632340e+01,  5.0411158045112554e+00 },
   {  1.3797593436988802e+01,  1.0073053609901610e+01 },
   {  2.1150225141692452e+01,  1.0944175040291007e+01 },
   {  1.2066018532102479e+01,  3.7906914152970685e+00 },
   {  7.5047974826581418e+00,  3.6650481779468316e+00 },
   {  1.9954287233837363e+01,  3.7733381897969061e+00 },
   {  1.4323181301507047e+01,  1.0734615269699551e+01 },
   {  2.7759596287916413e+00,  9.7050084698168142e+00 },
   { -7.6669161494715192e+00,  4.3246393013284337e+00 },
   {  9.2517771225162591e+00,  3.2963988969772791e+00 },
   {  2.0841523485671800e+01,  6.5281637067623048e+00 },
   {  1.2991339353945101e+01,  8.4793039405607438e+00 },
   {  6.6067893766401342e+00, -4.5239988598711411e-01 },
   {  4.8416725974068102e+00,  6.3071221895008343e+00 },
   {  1.1807300634139589e+01,  8.4919990174391451e+00 },
   {  1.2562958764403184e+01,  6.7680057972437817e+00 },
   {  5.8454422030119675e+00,  6.3516053588636243e+00 },
   {  1.4380160682740440e+01,  6.3829716186719985e+00 },
   {  1.3132951392236798e+01,  8.5219353647219336e+00 },
   {  2.8549096116128645e+00,  6.8805922884243342e+00 },
   {  2.2352844221821258e+01,  8.7964056113847633e+00 },
   {  9.1754864670137408e+00,  1.1533279603662686e+01 }
};


size_t N_SAMP2 = sizeof(data2) / sizeof(data2[0]);

namespace {

// =======================================================================================
bool check(Vector2D& V, real8_t a[2] ) {
  // -------------------------------------------------------------------------------------
  real8_t sum =
      ((V.x[0]-a[0])*(V.x[0]-a[0])) +
      ((V.x[1]-a[1])*(V.x[1]-a[1]));

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
bool check( Matrix2D& M, real8_t a[2][2] ) {
  // -----------------------------------------------------------------------------------
  real8_t sum =
      ((M.q[0]-a[0][0])*(M.q[0]-a[0][0])) +
      ((M.q[1]-a[0][1])*(M.q[1]-a[0][1])) +
      ((M.q[2]-a[1][0])*(M.q[2]-a[1][0])) +
      ((M.q[3]-a[1][1])*(M.q[3]-a[1][1]));

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

// =======================================================================================
TEST(test_getRC_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {1.1, 1.2},
    {2.1, 2.2},
  };

  {
    Matrix2D A( adat );
    Vector2D V = getRow( A, 2 );
    real8_t test[2] = { 1.1, 1.2 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix2D A( adat );
    Vector2D V = getRow( A, 0 );
    real8_t test[2] = { 1.1, 1.2 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix2D A( adat );
    Vector2D V = getRow( A, 1 );
    real8_t test[2] = { 2.1, 2.2 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  
  {
    Matrix2D A( adat );
    Vector2D V = getColumn( A, 2 );
    real8_t test[2] = { 1.1, 2.1 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix2D A( adat );
    Vector2D V = getColumn( A, 0 );
    real8_t test[2] = { 1.1, 2.1 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix2D A( adat );
    Vector2D V = getColumn( A, 1 );
    real8_t test[2] = { 1.2, 2.2 };
    EXPECT_TRUE( check( V, test ) );
  }
  

  {
    Matrix2D A( adat );
    Vector2D V = getDiagonal( A );
    real8_t test[2] = { 1.1, 2.2 };
    EXPECT_TRUE( check( V, test ) );
  }
  
}


// =======================================================================================
TEST(test_setRC_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[2][2] = {
    {1.1, 1.2},
    {2.1, 2.2}
  };
  real8_t vdat[2] = { 4.5, 6.7 };

  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {4.5, 6.7},
      {2.1, 2.2}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 2 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {4.5, 6.7},
      {2.1, 2.2}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 0 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {1.1, 1.2},
      {4.5, 6.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 1 );
    EXPECT_TRUE( check( A, test ) );
  }




  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {4.5, 1.2},
      {6.7, 2.2}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 2 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {4.5, 1.2},
      {6.7, 2.2}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 0 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {1.1, 4.5},
      {2.1, 6.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 1 );
    EXPECT_TRUE( check( A, test ) );
  }


  {
    Matrix2D A( adat );
    Vector2D V( vdat );
    real8_t test[2][2] = {
      {4.5, 1.2},
      {2.1, 6.7}
    };
    EXPECT_TRUE( check( A, adat ) );
    setDiagonal( A, V );
    EXPECT_TRUE( check( A, test ) );
  }

}

// =======================================================================================
TEST(test_diag_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t mdat[2][2] = {
    {1.1, 1.2},
    {2.1, 2.2}
  };
  real8_t vdat[2] = { 4.5, 6.7 };

  Matrix2D M(mdat);
  Vector2D V(vdat);

  {
    real8_t test[2][2] = {
      { 4.5,    D_ZERO },
      { D_ZERO, 6.7    }
    };
    Matrix2D A = diagonal( V );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    real8_t test[2] = { 1.1, 2.2 };
    Vector2D A = diagonal( M );
    EXPECT_TRUE( check( A, test ) );
  }

  
}

// =======================================================================================
TEST(test_dot_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t mdat[2][2] = {
    {1.1, 1.2},
    {2.1, 2.2}
  };
  real8_t vdat[2] = { 4.5, 6.7 };

  {
    Matrix2D M( mdat );
    Vector2D V( vdat );
    real8_t test[2] = { 19.02, 20.14 };
    Vector2D C = dot( V, M );
    EXPECT_TRUE( check( C, test ) );
  }

  {
    Matrix2D M( mdat );
    Vector2D V( vdat );
    real8_t test[2] = { 12.99, 24.19 };
    Vector2D C = dot( M, V );
    EXPECT_TRUE( check( C, test ) );
  }

  {
    Matrix2D M( mdat );
    Vector2D V( vdat );
    real8_t test[2] = { 19.02, 20.14 };
    Vector2D C;
    dot( C, V, M );
    EXPECT_TRUE( check( C, test ) );
  }

  {
    Matrix2D M( mdat );
    Vector2D V( vdat );
    real8_t test[2] = { 12.99, 24.19 };
    Vector2D C;
    dot( C, M, V );
    EXPECT_TRUE( check( C, test ) );
  }

}


// =======================================================================================
TEST(test_cov_lin2, Positive) {
  // -------------------------------------------------------------------------------------
  {
    Matrix2D A(cov2);
    Matrix2D C;
    covariance( C, data2, N_SAMP2 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
  }

  {
    Matrix2D A(cov2);
    Vector2D* vdata = new Vector2D[N_SAMP2];
    for ( size_t i=0; i<N_SAMP2; i++ ) {
      vdata[i].copy( data2[i][0], data2[i][1] );
    }
    Matrix2D C;
    covariance( C, data2, N_SAMP2 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
    delete[] vdata;
  }
  
  {
    Matrix2D A(cov2);
    Matrix2D C = covariance( data2, N_SAMP2 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
  }

  {
    Matrix2D A(cov2);
    Vector2D* vdata = new Vector2D[N_SAMP2];
    for ( size_t i=0; i<N_SAMP2; i++ ) {
      vdata[i].copy( data2[i][0], data2[i][1] );
    }
    Matrix2D C = covariance( data2, N_SAMP2 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
    delete[] vdata;
  }
  
}





} // end namespace


// =======================================================================================
// **                            U T E S T _ L I N A L G 2 D                            **
// ======================================================================== END FILE =====
