// ====================================================================== BEGIN FILE =====
// **                                U T E S T _ C O S T                                **
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
 *  @file   utest_cost.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-19
 *
 *  Provides automated testing for the nns::cost methods.
 */
// =======================================================================================

#include <limits.h>
#include <nns/cost.hh>
#include <gtest/gtest.h>

namespace {


// =======================================================================================
TEST(test_nns_cost, mse ) {
  // -------------------------------------------------------------------------------------
  real8_t A[4] = { 1.2, -3.4, 6.7, -2.5 };
  real8_t B[4] = { 1.7, -3.5, 6.4, -2.3 };
  real8_t mse  = 0.04875;
  real8_t test_grad[4] = { 0.5,  -0.1,  -0.3, 0.2 };
  real8_t grad[4];

  nns::cost_function_t           C = nns::getCostFunction( "MSE" );
  nns::cost_function_gradient_t dC = nns::getCostFunctionGradient( "MSE" );

  real8_t test  =  C( A, B, 4 );
  dC( grad, A, B, 4 );

  EXPECT_DOUBLE_EQ( test, mse );
  for ( size_t i=0; i<4; i++ ) {
    EXPECT_NEAR( grad[i], test_grad[i], 1.0e-11 );
  }

  
  nns::cost_function_t           C2 = nns::getCostFunction( "heather" );
  nns::cost_function_gradient_t dC2 = nns::getCostFunctionGradient( "rebekah" );

  EXPECT_TRUE(  C2 == static_cast<nns::cost_function_t>(0) );
  EXPECT_TRUE( dC2 == static_cast<nns::cost_function_gradient_t>(0) );
      
}


// =======================================================================================
TEST(test_nns_cost, crossentropy ) {
  // -------------------------------------------------------------------------------------
  real8_t Y[4] = { 0.015, 0.015, 0.97, 0.97 };
  real8_t A[4] = { 0.01, 0.96, 0.01, 0.96 };
  real8_t ce   = -1.963415587733312;
  real8_t test_grad[4] = { -0.505050505050505, 24.60937499999998,
                           -96.96969696969695, -0.2604166666666667 };
  real8_t grad[4];

  nns::cost_function_t           C = nns::getCostFunction( "cross" );
  nns::cost_function_gradient_t dC = nns::getCostFunctionGradient( "CE" );

  real8_t test  =  C( Y, A, 4 );
  dC( grad, Y, A, 4 );

  EXPECT_DOUBLE_EQ( test, ce );
  for ( size_t i=0; i<4; i++ ) {
    EXPECT_NEAR( grad[i], test_grad[i], 1.0e-11 );
  }
}


} // end namespace


// =======================================================================================
// **                                U T E S T _ C O S T                                **
// ======================================================================== END FILE =====
