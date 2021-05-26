// ====================================================================== BEGIN FILE =====
// **                          U T E S T _ 2 D A L L O C A T E                          **
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
/** @brief  Automated testing for nns::2D allocation methods.
 *  @file   utest_alloc.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-19
 *
 *  Provides automated testing for 2D alloc methods. (found in nns/Layer)
 */
// =======================================================================================

#include <limits.h>
#include <nns/layer.hh>
#include <gtest/gtest.h>

namespace {


// =======================================================================================
TEST(test_nns_alloc, twoD ) {
  // -------------------------------------------------------------------------------------

//  const size_t nr = 5;
//  const size_t nc = 7;
//  const size_t nu = nr*nc;

  
//  real8_t* test = new real8_t[ nu ];
  
//  real8_t** array = nns::new_2D( nr, nc );

//  size_t idx = 0;
//  for ( size_t r=0; r<nr; r++ ) {
//    for ( size_t c=0; c<nc; c++ ) {
//      real8_t x = static_cast<real8_t>(r+1) + (static_cast<real8_t>(c+1)/100.0);
//      test[ idx++ ] = x;
//      array[r][c] = x;
//    }
//  }

//  for ( size_t i=0; i<nu; i++) {
//    EXPECT_DOUBLE_EQ( test[i], array[0][i] );
//  }

}
      

} // end namespace


// =======================================================================================
// **                          U T E S T _ 2 D A L L O C A T E                          **
// ======================================================================== END FILE =====
