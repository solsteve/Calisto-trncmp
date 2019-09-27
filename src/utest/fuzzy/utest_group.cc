// ====================================================================== BEGIN FILE =====
// **                               U T E S T _ G R O U P                               **
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
/** @brief  Automated testing for fuzzy::Partition class methods.
 *  @file   utest_partition.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-16
 *
 *  Provides automated testing for the fuzzy::Group class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <fuzzy/Group.hh>
#include <VarReal.hh>
#include <Array.hh>
#include <FileTool.hh>
#include <gtest/gtest.h>

namespace {


// =======================================================================================
TEST( test_group_create, empty_one ) {
  // -------------------------------------------------------------------------------------
  fuzzy::Group G;
  EXPECT_EQ( 0, G.nIn() );
  EXPECT_EQ( 0, G.nOut() );
  EXPECT_EQ( 0, G.size() );
}

// =======================================================================================
TEST( test_group_create, n_empty ) {
  // -------------------------------------------------------------------------------------
  fuzzy::Group G(4);
  EXPECT_EQ( 4, G.nIn() );
  EXPECT_EQ( 0, G.nOut() );
  EXPECT_EQ( 0, G.size() );
}

// =======================================================================================
TEST( test_group_create, n_part ) {
  // -------------------------------------------------------------------------------------
  fuzzy::Partition** P;

  P = new fuzzy::Partition*[3];
  P[0] = new fuzzy::Partition(4);
  P[1] = new fuzzy::Partition(2);
  P[2] = new fuzzy::Partition(3);

  fuzzy::Group G(3,P);
  
  EXPECT_EQ( 3, G.nIn() );
  EXPECT_EQ( 9, G.nOut() );
  EXPECT_EQ( 9, G.size() );
}


// =======================================================================================
TEST( test_group_create, n_varreal ) {
  // -------------------------------------------------------------------------------------
  real8_t ctr[] = { 1, 2, 3, 
                    7, 8, 9, 10, 11, 12, 
                    -1, 1, 
                    4, 5, 6 };
  
  int32_t nc[] = { 3, 6, 2, 3 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  VarReal V(nr, nc, ctr);
  
  fuzzy::Group G( V );
  
  EXPECT_EQ(  4, G.nIn()  );
  EXPECT_EQ( 14, G.nOut() );
  EXPECT_EQ( 14, G.size() );
}


// =======================================================================================
TEST( test_group_storage, load_save ) {
  // -------------------------------------------------------------------------------------
  real8_t ctr[] = { 1.0, 2.0, 3.0, 
                    7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 
                    -1.0, 1.0, 
                    4.0, 5.0, 6.0 };
  
   real8_t test[] = { 11.01, 12.02, 13.03, 
                      21.04, 22.05, 23.06, 24.07, 25.08, 26.09, 
                      31.10, 32.11, 
                      41.12, 42.13, 43.14 };
  
  int32_t nc[] = { 3, 6, 2, 3 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  VarReal V1(nr, nc, ctr);
  VarReal V2(nr, nc, test);
  
  fuzzy::Group G( V1 );
  fuzzy::Group H( V2 );

  real8_t* g_buf = G.create_buffer();
  real8_t* x_buf = G.create_buffer();
  real8_t* h_buf = H.create_buffer();

  int32_t k = G.size();

  for ( int32_t i=0; i<k; i++ ) {
    g_buf[i] = 1.0;
    h_buf[i] = 1.0;
    x_buf[i] = 1.0;
    EXPECT_DOUBLE_EQ( g_buf[i], h_buf[i] );
  }

  G.store( g_buf );
  H.store( h_buf );
  
  int32_t idx = 0;
  int32_t np  = G.nIn();
  for ( int32_t i=0; i<np; i++ ) {
    int32_t m = G.get(i).nOut();
    for ( int32_t j=0; j<m; j++ ) {
      EXPECT_NE( g_buf[idx], h_buf[idx] );
      idx++;
    }
  }

  G.load( h_buf );
  G.store( x_buf );

  for ( int32_t i=0; i<k; i++ ) {
    EXPECT_DOUBLE_EQ( h_buf[i], x_buf[i] );
  }

  delete[] g_buf;
  delete[] h_buf;
}

// =======================================================================================
TEST( test_group_storage, read_write ) {
  // -------------------------------------------------------------------------------------
  real8_t ctr[] = { 1.0, 2.0, 3.0, 
                    7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 
                    -1.0, 1.0, 
                    4.0, 5.0, 6.0 };
  
  
  int32_t nc[] = { 3, 6, 2, 3 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  VarReal V(nr, nc, ctr);
  
  fuzzy::Group G( V );

  std::ofstream outf = FileTool::openWrite( "/tmp/group.ftest" );
  G.write( outf );
  outf.close();

  fuzzy::Group H;

  std::ifstream inf = FileTool::openRead( "/tmp/group.ftest" );
  H.read( inf );
  inf.close();

    int32_t k = G.size();
  real8_t* g_buf = G.create_buffer();
  real8_t* h_buf = H.create_buffer();
  G.store( g_buf );
  H.store( h_buf );

  for ( int32_t i=0; i<k; i++ ) {
    EXPECT_DOUBLE_EQ( ctr[i],   g_buf[i] );
    EXPECT_DOUBLE_EQ( ctr[i],   h_buf[i] );
  }

  delete[] g_buf;
  delete[] h_buf;
}


// =======================================================================================
TEST( test_group_execution, fuzzy ) {
  // -------------------------------------------------------------------------------------
  real8_t ctr[] = { 1.0, 2.0, 3.0, 
                    7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 
                    -1.0, 1.0, 
                    4.0, 5.0, 6.0 };

  int32_t nc[] = { 3, 6, 2, 3 };
  int32_t nr = sizeof(nc) / sizeof(nc[0]);

  VarReal V(nr, nc, ctr);
  
  fuzzy::Group G( V );

  int32_t n_in  = G.nIn();
  int32_t n_out = G.nOut();

  real8_t input[n_in];
  real8_t delta[n_in];
  real8_t mu[n_out];
  real8_t coa[n_in];

  real8_t min_x[n_in] = { 0.0,  6.0, -2.0, 3.0 };
  real8_t max_x[n_in] = { 4.0, 13.0,  2.0, 7.0 };

  int32_t n_sample = 40;

  for ( int32_t i=0; i<n_in; i++ ) {
    delta[i] = ( max_x[i] - min_x[i] ) / (real8_t)(n_sample - 1);
    input[i] = min_x[i];
  }
  
  for ( int32_t j=0; j<n_sample; j++ ) {

    G.fuzzify( mu, input );
    G.defuzzify( coa, mu );

    int32_t idx = 0;
    for ( int32_t i=0; i<n_in; i++ ) {
      fuzzy::Partition& P = G.get(i);

      int32_t no = P.nOut();
      real8_t mini_mu[no];

      P.mu( mini_mu, input[i] );
      for ( int32_t k=0; k<no; k++ ) {
        EXPECT_DOUBLE_EQ( mini_mu[k], mu[idx] );
        idx += 1;
      }
      real8_t y = P.coa( mini_mu );

      EXPECT_DOUBLE_EQ( y, coa[i] );
      input[i] += delta[i];
    }
  }

}

} // end namespace


// =======================================================================================
// **                               U T E S T _ G R O U P                               **
// ======================================================================== END FILE =====
