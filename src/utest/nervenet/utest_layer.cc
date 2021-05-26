// ====================================================================== BEGIN FILE =====
// **                               U T E S T _ L A Y E R                               **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2020-, Stephen W. Soliday                                          **
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
/** @brief  Automated testing for nns::layer methods.
 *  @file   utest_layer.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-25
 *
 *  Provides automated testing for the nns::layer methods.
 */
// =======================================================================================

#include <limits.h>
#include <nns/layer.hh>
#include <gtest/gtest.h>
#include <FileTool.hh>


namespace {


// =======================================================================================
TEST(test_nns_layer, construct ) {
  // -------------------------------------------------------------------------------------
  nns::Layer* L1 = nns::Layer::Builder().build();

  EXPECT_EQ( L1->size(),  0 );
  EXPECT_EQ( L1->size(0), 0 );
  EXPECT_EQ( L1->size(1), 0 );
  EXPECT_EQ( L1->size(2), 256 );

  nns::Layer* L2 = nns::Layer::Builder().IO(3,5).activate("sigmoid").build();

  EXPECT_EQ( L2->size(), 20 );
  EXPECT_EQ( L2->size(0), 3 );
  EXPECT_EQ( L2->size(1), 5 );
  EXPECT_EQ( L2->size(2), 256 );
  
  nns::Layer* L3 = nns::Layer::Builder().IO(8,10).batch(63).build();

  EXPECT_EQ( L3->size(),  90 );
  EXPECT_EQ( L3->size(0),  8 );
  EXPECT_EQ( L3->size(1), 10 );
  EXPECT_EQ( L3->size(2), 63 );

  delete L1;
  delete L2;
  delete L3;
}


// =======================================================================================
TEST(test_nns_layer, loadstore ) {
  // -------------------------------------------------------------------------------------
  const size_t nc = 3;
  const size_t nn = 5;

  nns::Layer* L1 = nns::Layer::Builder().IO(nc,nn).activate("sigmoid").build();
  nns::Layer* L2 = nns::Layer::Builder().IO(nc,nn).activate("sigmoid").build();
  L1->initialize( true );
  L2->initialize( true );

  size_t   nb = L1->size();
  real8_t* B1 = new real8_t[nb];
  real8_t* B2 = new real8_t[nb];
  
  L1->store(B1);
  L2->store(B2);

  for ( size_t i=0; i<nb; i++ ) {
    EXPECT_EQ( B1[i], B2[i] );
  }

  L1->initialize();
  L2->initialize();
  
  L1->store(B1);
  L2->store(B2);

  EXPECT_TRUE( 0.5 < MSE( B1, B2, nb ) );

  L2->load(B1);
  L2->store(B2);

  EXPECT_EQ( MSE( B1, B2, nb ), 0.0 );

  delete B1;
  delete B2;
  delete L1;
  delete L2;
}


// =======================================================================================
TEST(test_nns_layer, readwrite ) {
  // -------------------------------------------------------------------------------------

  nns::Layer*   L1  = nns::Layer::Builder().IO(3,5).activate("sigmoid").build();
  L1->initialize( true );
  std::ofstream fp1 = FileTool::openWrite( "/tmp/test.1.net" );
  L1->write( fp1 );
  fp1.close();

  
  std::ifstream fp2 = FileTool::openRead( "/tmp/test.1.net" );
  nns::Layer*   L2  = nns::Layer::Builder().build(fp2);
  fp2.close();

  std::ofstream fp3 = FileTool::openWrite( "/tmp/test.2.net" );
  L2->write( fp3 );
  fp3.close();

  delete L1;
  delete L2;
}


// =======================================================================================
TEST(test_nns_layer, forward ) {
  // -------------------------------------------------------------------------------------
  real8_t buf[25] = { -0.758, -4.002, -1.767, 2.014, 1.034, -0.754, -1.163, -0.671,
                      1.224, 6.652, 0.031, -0.486, 2.349, -2.055, -0.535, -1.897, 0.693,
                      -1.781, -1.558, 0.229, 1.299, -1.935, -1.738, -0.956, 0.026 };

  real8_t X[10][4] = {
    { -0.057, -1.086, -0.534, -0.34 },
    { 0.753, -0.1, -1.687, 0.364 },
    { -0.503, 2.364, -1.231, 1.351 },
    { -0.448, 1.259, -0.952, 1.408 },
    { -0.154, 0.725, 4.142, -0.532 },
    { 1.606, 0.975, -1.172, 2.739 },
    { -0.682, -2.837, -0.896, -2.319 },
    { 0.911, -1.526, 0.798, 2.797 },
    { -0.577, -1.264, 0.285, -0.648 },
    { 2.212, -2.117, -1.135, 2.126 }
  };

  real8_t Y[10][5] = {
    { 0.490511, 0.0534388, 0.229163, 0.679566, 0.978085 },
    { 0.00133692, 0.230374, 0.937156, 0.819747, 0.83726 },
    { 0.0179072, 0.996747, 0.999517, 0.0143637, 0.348789 },
    { 0.160945, 0.999194, 0.987981, 0.0663539, 0.71595 },
    { 0.998289, 0.615282, 0.00162874, 5.16995e-05, 0.0256646 },
    { 0.0002168, 0.999999, 0.923002, 0.483179, 0.0901739 },
    { 0.941693, 4.65618e-07, 0.0384305, 0.972023, 0.999763 },
    { 0.942236, 1, 0.000797999, 0.700432, 0.817311 },
    { 0.975603, 0.0392991, 0.0523165, 0.345676, 0.986914 },
    { 0.00258024, 0.999981, 0.00798756, 0.996535, 0.862767 }
  };

  nns::Layer* L1 = nns::Layer::Builder().IO(4,5).activate("sigmoid").build();

  //  L1->forward(X,10);

  real8_t** out = L1->output();

  for ( size_t i=0; i<10; i++ ) {
    for ( size_t j=0; j<5; j++ ) {
      fprintf( stdout, " %.6f", out[i][j] );
    }
    fprintf( stdout, "\n" );
  }
  fprintf( stdout, "\n" );


}

} // end namespace


// =======================================================================================
// **                            U T E S T _ A C T I V A T E                            **
// ======================================================================== END FILE =====
