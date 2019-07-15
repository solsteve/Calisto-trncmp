// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ L I N A L G 3 D                            **
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
/** @brief  Automated testing for LinAlg3  methods.
 *  @file   utest_linalg3d.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides automated testing for combination of Vector3D and Matrix3D class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <LinAlg3D.hh>
#include "gtest/gtest.h"

real8_t cov3[3][3] = {
   {  2.7855750860241834e+01, -1.2952444330788102e+00, -1.4541927550064198e+01 },
   { -1.2952444330788102e+00,  9.3231063639430634e+00,  2.3878308674408739e+00 },
   { -1.4541927550064198e+01,  2.3878308674408739e+00,  8.9086945406431184e+00 }
};


real8_t data3[][3] = {
   {  3.9014710770332033e+00,  9.8663740658657439e-01,  2.2777815363930229e-01 },
   {  2.2727748331479738e+00,  6.1482220233764151e+00, -2.0153295666955440e-01 },
   {  1.5316835216160982e+01,  3.5871982486098353e+00, -4.3710279427528054e+00 },
   {  7.4571595402075195e+00,  4.7634256760242364e+00, -1.2600548569287058e+00 },
   {  1.6528361794541006e+01,  5.0683440831234678e+00, -5.4374250345063277e+00 },
   {  2.2507623137987746e+01,  1.7280468574243626e+00, -1.0093282712979708e+01 },
   {  7.0123696496604015e+00,  3.2379025364766867e+00, -1.3290003146277742e+00 },
   { -1.8222002589529779e-01,  3.7356172401599834e+00,  1.8751812078728571e+00 },
   {  1.4798542096419842e+01,  2.2647983107611371e+00, -3.9937785023424883e+00 },
   {  3.3435226769296529e+00,  8.0162448574694540e+00,  1.8141864427283685e+00 },
   {  7.9467862023339544e+00,  2.3177463132965097e+00, -1.3455571008477143e+00 },
   {  3.2775249970914229e+00,  3.9766170569825223e+00,  1.1156002684454589e+00 },
   {  1.0518713817603793e+01,  4.7157286584276470e+00, -2.0125125009415132e+00 },
   {  5.9422261424042659e+00,  1.0431213040847661e+01,  1.7988984171153757e+00 },
   {  9.0326173727341885e+00,  7.8317446231797261e-02, -1.5185218670945635e+00 },
   {  6.7365967540514173e+00,  4.2631221235742772e-01, -3.2358343936567899e+00 },
   {  8.3814737057828097e+00,  4.9699126569922472e+00, -2.6823128051143552e+00 },
   {  1.6968596201392049e+01,  4.8489542591232606e+00, -5.6145494129651077e+00 },
   {  4.9768867980358182e+00,  1.8632482024892232e+00, -3.4517895110889429e-01 },
   {  8.7018172469647865e+00, -2.4165907480194126e-01, -3.8118659787492515e+00 },
   {  1.6809515600943651e+01, -1.4370159142408694e+00, -9.4874221483463561e+00 },
   {  1.7288565690934242e+01,  1.5232312152974441e+00, -6.6903760604169440e+00 },
   {  1.3549856255723144e+01, -2.6948051823551329e+00, -5.4722875445025991e+00 },
   {  7.7723182195245011e+00,  4.3006464093204135e+00, -9.3510205890626752e-01 },
   {  9.9283844323081993e+00,  5.9931018803762006e+00, -9.0612597517081839e-01 },
   { -6.1887332629061542e-01,  3.7150106366839569e-01,  2.7256275917572070e+00 },
   {  3.3654124292640430e+00,  3.2141500799670135e+00, -6.1087234631786158e-01 },
   {  4.6567831496750340e+00, -1.3369162318270269e+00, -7.7908268039586626e-01 },
   {  1.3347055408498184e+01,  5.5216354777440344e+00, -4.5291118769366250e+00 },
   {  1.3966377020095946e+01,  4.9910757524223461e+00, -4.1073225896688941e+00 },
   {  7.9134658276421777e-01, -7.1726095002812795e-01,  2.4085915800185393e+00 },
   {  9.6435865835350043e+00,  3.1125202127821155e-01, -2.5056132639206812e+00 },
   {  9.9390057591142646e+00,  2.9222643196333018e+00, -2.8046417110908601e+00 },
   {  3.6598300920064513e+00,  5.7087075534680043e+00,  2.4022063008819994e+00 },
   {  9.7531931080990830e+00,  1.0678964681979901e+01, -2.4592747491192055e+00 },
   {  8.8652134703598477e+00,  6.6094414882352366e+00, -1.5434712871601257e+00 },
   {  7.7578427551771316e+00,  6.9668126231742988e+00, -2.4796733355636844e+00 },
   {  6.7468515571312802e+00,  5.9911838104687787e+00, -1.5943006227202394e+00 },
   {  6.9186097984767070e+00,  5.0196154033267462e+00,  5.2066402864480199e-01 },
   {  6.6342893819277347e+00,  3.7777546633453256e+00, -2.1006303797364789e+00 }
};


size_t N_SAMP3 = sizeof(data3) / sizeof(data3[0]);

namespace {

// =======================================================================================
bool check(Vector3D& V, real8_t a[3] ) {
  // -------------------------------------------------------------------------------------
  real8_t sum =
      ((V.x[0]-a[0])*(V.x[0]-a[0])) +
      ((V.x[1]-a[1])*(V.x[1]-a[1])) +
      ((V.x[2]-a[2])*(V.x[2]-a[2]));

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
bool check( Matrix3D& M, real8_t a[3][3] ) {
  // -----------------------------------------------------------------------------------
  real8_t sum =
      ((M.q[0]-a[0][0])*(M.q[0]-a[0][0])) +
      ((M.q[1]-a[0][1])*(M.q[1]-a[0][1])) +
      ((M.q[2]-a[0][2])*(M.q[2]-a[0][2])) +
      ((M.q[3]-a[1][0])*(M.q[3]-a[1][0])) +
      ((M.q[4]-a[1][1])*(M.q[4]-a[1][1])) +
      ((M.q[5]-a[1][2])*(M.q[5]-a[1][2])) +
      ((M.q[6]-a[2][0])*(M.q[6]-a[2][0])) +
      ((M.q[7]-a[2][1])*(M.q[7]-a[2][1])) +
      ((M.q[8]-a[2][2])*(M.q[8]-a[2][2]));

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
  real8_t adat[3][3] = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
    {3.1, 3.2, 3.3},
  };

  {
    Matrix3D A( adat );
    Vector3D V = getRow( A, 3 );
    real8_t test[3] = { 1.1, 1.2, 1.3 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getRow( A, 0 );
    real8_t test[3] = { 1.1, 1.2, 1.3 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getRow( A, 1 );
    real8_t test[3] = { 2.1, 2.2, 2.3 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getRow( A, 2 );
    real8_t test[3] = { 3.1, 3.2, 3.3 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getColumn( A, 3 );
    real8_t test[3] = { 1.1, 2.1, 3.1 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getColumn( A, 0 );
    real8_t test[3] = { 1.1, 2.1, 3.1 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getColumn( A, 1 );
    real8_t test[3] = { 1.2, 2.2, 3.2 };
    EXPECT_TRUE( check( V, test ) );
  }
  
  {
    Matrix3D A( adat );
    Vector3D V = getColumn( A, 2 );
    real8_t test[3] = { 1.3, 2.3, 3.3 };
    EXPECT_TRUE( check( V, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V = getDiagonal( A );
    real8_t test[3] = { 1.1, 2.2, 3.3 };
    EXPECT_TRUE( check( V, test ) );
  }
  
}


// =======================================================================================
TEST(test_setRC_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t adat[3][3] = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
    {3.1, 3.2, 3.3}
  };
  real8_t vdat[3] = { 4.5, 6.7, 8.9 };

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {4.5, 6.7, 8.9},
      {2.1, 2.2, 2.3},
      {3.1, 3.2, 3.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 0 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {1.1, 1.2, 1.3},
      {4.5, 6.7, 8.9},
      {3.1, 3.2, 3.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 1 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {1.1, 1.2, 1.3},
      {2.1, 2.2, 2.3},
      {4.5, 6.7, 8.9}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 2 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {4.5, 6.7, 8.9},
      {2.1, 2.2, 2.3},
      {3.1, 3.2, 3.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    setRow( A, V, 3 );
    EXPECT_TRUE( check( A, test ) );
  }


  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {4.5, 1.2, 1.3},
      {6.7, 2.2, 2.3},
      {8.9, 3.2, 3.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 0 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {1.1, 4.5, 1.3},
      {2.1, 6.7, 2.3},
      {3.1, 8.9, 3.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 1 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {1.1, 1.2, 4.5},
      {2.1, 2.2, 6.7},
      {3.1, 3.2, 8.9}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 2 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {4.5, 1.2, 1.3},
      {6.7, 2.2, 2.3},
      {8.9, 3.2, 3.3}
    };
    EXPECT_TRUE( check( A, adat ) );
    setColumn( A, V, 3 );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    Matrix3D A( adat );
    Vector3D V( vdat );
    real8_t test[3][3] = {
      {4.5, 1.2, 1.3},
      {2.1, 6.7, 2.3},
      {3.1, 3.2, 8.9}
    };
    EXPECT_TRUE( check( A, adat ) );
    setDiagonal( A, V );
    EXPECT_TRUE( check( A, test ) );
  }

}

// =======================================================================================
TEST(test_diag_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t mdat[3][3] = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
    {3.1, 3.2, 3.3}
  };
  real8_t vdat[3] = { 4.5, 6.7, 8.9 };

  Matrix3D M(mdat);
  Vector3D V(vdat);

  {
    real8_t test[3][3] = {
      { 4.5,    D_ZERO, D_ZERO },
      { D_ZERO, 6.7,    D_ZERO },
      { D_ZERO, D_ZERO, 8.9    }
    };
    Matrix3D A = diagonal( V );
    EXPECT_TRUE( check( A, test ) );
  }

  {
    real8_t test[3] = { 1.1, 2.2, 3.3 };
    Vector3D A = diagonal( M );
    EXPECT_TRUE( check( A, test ) );
  }

  
}

// =======================================================================================
TEST(test_dot_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  real8_t mdat[3][3] = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
    {3.1, 3.2, 3.3}
  };
  real8_t vdat[3] = { 4.5, 6.7, 8.9 };

  {
    Matrix3D M( mdat );
    Vector3D V( vdat );
    real8_t test[3] = { 46.61, 48.62, 50.63 };
    Vector3D C = dot( V, M );
    EXPECT_TRUE( check( C, test ) );
  }

  {
    Matrix3D M( mdat );
    Vector3D V( vdat );
    real8_t test[3] = { 24.56, 44.66, 64.76 };
    Vector3D C = dot( M, V );
    EXPECT_TRUE( check( C, test ) );
  }

  {
    Matrix3D M( mdat );
    Vector3D V( vdat );
    real8_t test[3] = { 46.61, 48.62, 50.63 };
    Vector3D C;
    dot( C, V, M );
    EXPECT_TRUE( check( C, test ) );
  }

  {
    Matrix3D M( mdat );
    Vector3D V( vdat );
    real8_t test[3] = { 24.56, 44.66, 64.76 };
    Vector3D C;
    dot( C, M, V );
    EXPECT_TRUE( check( C, test ) );
  }

}


// =======================================================================================
TEST(test_cov_lin3, Positive) {
  // -------------------------------------------------------------------------------------
  {
    Matrix3D A(cov3);
    Matrix3D C;
    covariance( C, data3, N_SAMP3 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
  }

  {
    Matrix3D A(cov3);
    Vector3D* vdata = new Vector3D[N_SAMP3];
    for ( size_t i=0; i<N_SAMP3; i++ ) {
      vdata[i].copy( data3[i][0], data3[i][1], data3[i][2] );
    }
    Matrix3D C;
    covariance( C, data3, N_SAMP3 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
    delete[] vdata;
  }
  
  {
    Matrix3D A(cov3);
    Matrix3D C = covariance( data3, N_SAMP3 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
  }

  {
    Matrix3D A(cov3);
    Vector3D* vdata = new Vector3D[N_SAMP3];
    for ( size_t i=0; i<N_SAMP3; i++ ) {
      vdata[i].copy( data3[i][0], data3[i][1], data3[i][2] );
    }
    Matrix3D C = covariance( data3, N_SAMP3 );
    EXPECT_NEAR( 0.0e0, sumsq( A - C ), D_EPSILON );
    delete[] vdata;
  }
  
}

} // end namespace


// =======================================================================================
// **                            U T E S T _ L I N A L G 3 D                            **
// ======================================================================== END FILE =====
