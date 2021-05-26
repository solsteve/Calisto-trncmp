// ====================================================================== BEGIN FILE =====
// **                            U T E S T _ A C T I V A T E                            **
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
/** @brief  Automated testing for nns::cost methods.
 *  @file   utest_activate.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-19
 *
 *  Provides automated testing for the nns::cost methods.
 */
// =======================================================================================

#include <limits.h>
#include <nns/activate.hh>
#include <gtest/gtest.h>

namespace {


// =======================================================================================
TEST(test_nns_activate, linear ) {
  // -------------------------------------------------------------------------------------
  real8_t test_Z[3] = { 1.3, -2.4, 5.7 };
  real8_t test_d[3] = { 1.0e0, 1.0e0, 1.0e0 };
  real8_t a[3];
  real8_t d[3];

  nns::activate_t           F = nns::getActivation( "linear" );
  nns::activate_gradient_t dF = nns::getActivationGradient( "linear" );

  F( a, test_Z, 3 );
  dF( d, a, test_Z, 3 );

  for ( size_t i=0; i<3; i++ ) {
    EXPECT_DOUBLE_EQ( a[i], test_Z[i]  );
    EXPECT_DOUBLE_EQ( d[i], test_d[i] );
  }


  nns::activate_t           F2 = nns::getActivation( "heather" );
  nns::activate_gradient_t dF2 = nns::getActivationGradient( "rebekah" );

  EXPECT_TRUE(  F2 == static_cast<nns::activate_t>(0) );
  EXPECT_TRUE( dF2 == static_cast<nns::activate_gradient_t>(0) );
}


// =======================================================================================
TEST(test_nns_activate, sigmoid ) {
  // -------------------------------------------------------------------------------------
  real8_t test_Z[3] = { -3.2, 0.0, 4.7 };
  real8_t test_a[3] = { 0.039165722796764356, 0.5, 0.990986701347152 };
  real8_t test_d[3] = { 0.03763176895457137,  0.25, 0.008932059100242515 };
  real8_t a[3];
  real8_t d[3];

  nns::activate_t           F = nns::getActivation( "Sigmoid" );
  nns::activate_gradient_t dF = nns::getActivationGradient( "sig" );

  F( a, test_Z, 3 );
  dF( d, a, test_Z, 3 );

  for ( size_t i=0; i<3; i++ ) {
    EXPECT_DOUBLE_EQ( a[i], test_a[i]  );
    EXPECT_DOUBLE_EQ( d[i], test_d[i] );
  }

}


// =======================================================================================
TEST(test_nns_activate, hypertan ) {
  // -------------------------------------------------------------------------------------
  real8_t test_Z[3] = { -1.3, 0.0, 5.7 };
  real8_t test_a[3] = { -0.8617231593133063, 0.0e0, 0.9999776092809898 };
  real8_t test_d[3] = { 0.25743319670309406, 1.0e0, 4.4780936676147576e-05 };
  real8_t a[3];
  real8_t d[3];

  nns::activate_t           F = nns::getActivation( "TanH" );
  nns::activate_gradient_t dF = nns::getActivationGradient( "tan" );

  F( a, test_Z, 3 );
  dF( d, a, test_Z, 3 );

  for ( size_t i=0; i<3; i++ ) {
    EXPECT_DOUBLE_EQ( a[i], test_a[i]  );
    EXPECT_DOUBLE_EQ( d[i], test_d[i] );
  }

}


} // end namespace


// =======================================================================================
// **                            U T E S T _ A C T I V A T E                            **
// ======================================================================== END FILE =====
