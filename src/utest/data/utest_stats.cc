// ====================================================================== BEGIN FILE =====
// **                               U T E S T _ S T A T S                               **
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
// **  Foundation, eithger version 3 of the License, or (at your option)                **
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
/** @brief  Automated testing for Statistics class methods.
 *  @file   utest_table.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-29
 *
 *  Provides automated testing for the Statistics class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <Statistics.hh>
#include <gtest/gtest.h>
#include <Dice.hh>

namespace {

  static u_int32_t SEED_MATTER[] = { 0x29341EA3, 0x9257677C, 0xCC98B1D1, 0x7C5EB68C,
				     0x13ED5BC5, 0x3C91F88F, 0xE1A42570, 0x24CA88CD,
				     0xAE36E97A, 0x59BADCBB, 0x4B9ED120, 0x952318E6,
				     0xDD62B887, 0xCFC13ED9, 0x0F6A241B, 0x43970DA6,
				     0xDF52E725, 0x4F6FE0ED, 0xCF9D4A7B, 0xA8742AE2,
				     0x3B0590CF, 0xE20ACC41, 0x10A25D9B, 0xD59349FF,
				     0x10BEE39E, 0x33CE2526, 0xD8029C5B, 0xFC6D3D65,
				     0xD08E3996, 0x6FCFC48D, 0x2FD4F96B, 0x1AAEC36F };

  static size_t SEED_MATTER_LEN = sizeof(SEED_MATTER)/sizeof(SEED_MATTER[0]);


// =======================================================================================
real8_t normal_MC( Dice* dd ) {
  // -------------------------------------------------------------------------------------
  real8_t x, y, t;
  do {
    y = dd->uniform();
    x = 1.2e1 * dd->uniform() - 6.0e0;
    t = exp( -5.0e-1 * x * x );
  } while( y > t );
  return x;
}


// =======================================================================================
TEST(test_statistics_histogram, construction ) {
  // -------------------------------------------------------------------------------------
  // Test: init, constrctor(x3), size
  // -------------------------------------------------------------------------------------
  real8_t ctrs[] = { 1.0, 3.0, 5.0, 7.0, 9.0 };
  size_t ns = sizeof(ctrs) / sizeof( ctrs[0] );

  Statistics::histogram H1(ns);
  Statistics::histogram H2(1.0, 9.0, ns);
  Statistics::histogram H3(ctrs, ns);

  EXPECT_EQ( ns, H1.size() );
  EXPECT_EQ( ns, H2.size() );
  EXPECT_EQ( ns, H3.size() );
    
  for ( size_t i=0; i<ns; i++ ) {
    EXPECT_DOUBLE_EQ( static_cast<real8_t>(i), H1.center(i) );
  }
    
  for ( size_t i=0; i<ns; i++ ) {
    EXPECT_DOUBLE_EQ( ctrs[i], H2.center(i) );
  }
    
  for ( size_t i=0; i<ns; i++ ) {
    EXPECT_DOUBLE_EQ( ctrs[i], H3.center(i) );
  }
    
}    

// =======================================================================================
TEST(test_statistics_histogram, add ) {
  // -------------------------------------------------------------------------------------
  // Test: add(x3), map, bin, count, max
  // -------------------------------------------------------------------------------------
  real8_t data[] = { 7.0, 5.8, 6.1, 8.9, 2.1, 3.9, 4.3, 0.8, 1.1, 4.5, 5.2, 7.9, 1.3 };
  size_t ns = sizeof(data) / sizeof( data[0] );

  size_t count[] = { 3, 2, 4, 3, 1 };
  size_t nc = sizeof(count) / sizeof( count[0] );
    
  Statistics::histogram H(1.0, 9.0, nc);

  H.reset();
  H.add( data, ns );

  EXPECT_EQ( ns, H.count() );
  EXPECT_EQ( 2,  H.max() );

  for ( size_t i=0; i<nc; i++ ) {
    EXPECT_EQ( count[i], H.bin(i) );
  }
    
}

#define  TEST_MEAN   3.0
#define  TEST_SIGMA  2.0
#define  TEST_VAR   (TEST_SIGMA*TEST_SIGMA)

// =======================================================================================
TEST(test_statistics_single, monte_carlo ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();
  dd->seed_set( reinterpret_cast<void*>(SEED_MATTER), dd->seed_size() );

  size_t   nsamp  = 1000000;
  real8_t* buffer = new real8_t[nsamp];

  Statistics::running R;

  real8_t minv = D_ZERO;
  real8_t maxv = D_ZERO;
  for ( size_t i=0; i<nsamp; i++ ) {
    real8_t x = TEST_MEAN + TEST_SIGMA*normal_MC( dd );
    buffer[i] = x;
    R.update(x);
    if ( x < minv ) { minv = x; }
    if ( x > maxv ) { maxv = x; }
  }

  Statistics::single S;

  S.compile( buffer, nsamp );
  S.extra(   buffer, nsamp );
  
  fprintf( stdout, "\nSampled %d normally distributed random numbers\n", nsamp );
  fprintf( stdout, "   Attribute  Expected   Single     Running\n" );
  fprintf( stdout, "   ---------  ---------  ---------  ---------\n" );
  fprintf( stdout, "   Min value  %9.6f  %9.6f  %9.6f\n", minv,      S.minv(), R.minv() );
  fprintf( stdout, "   Mean       %9.6f  %9.6f  %9.6f\n", TEST_MEAN, S.mean(), R.mean() );
  fprintf( stdout, "   Max value  %9.6f  %9.6f  %9.6f\n", maxv,      S.maxv(), R.maxv() );
  fprintf( stdout, "   Variance   %9.6f  %9.6f  %9.6f\n", TEST_VAR,  S.var(),  R.var()  );
  fprintf( stdout, "   Skew        0.000000  %9.6f\n",               S.skew() );
  fprintf( stdout, "   Kurt        0.000000  %9.6f\n\n",             S.kurt() );

  delete[] buffer;
}


// =======================================================================================
TEST(test_statistics_single, normal_Dice ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();
  dd->seed_set( reinterpret_cast<void*>(SEED_MATTER), dd->seed_size() );

  size_t   nsamp  = 1000000;
  real8_t* buffer = new real8_t[nsamp];

  Statistics::running R;

  real8_t minv = D_ZERO;
  real8_t maxv = D_ZERO;
  for ( size_t i=0; i<nsamp; i++ ) {
    real8_t x = TEST_MEAN + TEST_SIGMA*dd->normal();
    buffer[i] = x;
    R.update(x);
    if ( x < minv ) { minv = x; }
    if ( x > maxv ) { maxv = x; }
  }

  Statistics::single S;

  S.compile( buffer, nsamp );
  S.extra(   buffer, nsamp );
  
  fprintf( stdout, "\nSampled %d normally distributed random numbers\n", nsamp );
  fprintf( stdout, "   Attribute  Expected   Single     Running\n" );
  fprintf( stdout, "   ---------  ---------  ---------  ---------\n" );
  fprintf( stdout, "   Min value  %9.6f  %9.6f  %9.6f\n", minv,      S.minv(), R.minv() );
  fprintf( stdout, "   Mean       %9.6f  %9.6f  %9.6f\n", TEST_MEAN, S.mean(), R.mean() );
  fprintf( stdout, "   Max value  %9.6f  %9.6f  %9.6f\n", maxv,      S.maxv(), R.maxv() );
  fprintf( stdout, "   Variance   %9.6f  %9.6f  %9.6f\n", TEST_VAR,  S.var(),  R.var()  );
  fprintf( stdout, "   Skew        0.000000  %9.6f\n",               S.skew() );
  fprintf( stdout, "   Kurt        0.000000  %9.6f\n\n",             S.kurt() );

  delete[] buffer;
}



  
// =======================================================================================
TEST(test_statistics_multiple, normal_Dice ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();
  dd->seed_set( reinterpret_cast<void*>(SEED_MATTER), dd->seed_size() );

  real8_t MEAN[] = { 3.0, 7.0, -2.0, 1.0 };
  real8_t STDV[] = { 0.2, 1.5,  2.0, 3.0 };
  size_t  nvar = sizeof(MEAN)/sizeof(MEAN[0]);
  
  size_t  nsamp  = 1000000;
  Table   data( nsamp, nvar );

  real8_t minv[nvar];
  real8_t maxv[nvar];
  for ( size_t j=0; j<nvar; j++ ) {
    minv[j] =  1.0e10;
    maxv[j] = -1.0e10;
  }
  
  for ( size_t i=0; i<nsamp; i++ ) {
    for ( size_t j=0; j<nvar; j++ ) {
      real8_t x = MEAN[j] + STDV[j]*dd->normal();
      data(i,j) = x;
      if ( x < minv[j] ) { minv[j] = x; }
      if ( x > maxv[j] ) { maxv[j] = x; }
    }
  }

  Statistics::multi M(nvar);

  M.compile( data );
  M.extra(   data );
  
  fprintf( stdout, "\nSampled %d normally distributed vectors of %d variables\n", M.count(), M.nvar() );
  fprintf( stdout, "   Attribute  Expected   Single\n" );
  fprintf( stdout, "   ---------  ---------  ----------\n" );
  for ( size_t j=0; j<nvar; j++ ) {
    fprintf( stdout, "   Min value  %9.6f  %9.6f\n", minv[j], M.minv(j) );
    fprintf( stdout, "   Mean       %9.6f  %9.6f\n", MEAN[j], M.mean(j) );
    fprintf( stdout, "   Max value  %9.6f  %9.6f\n", maxv[j], M.maxv(j) );
    fprintf( stdout, "   Std. Dev.  %9.6f  %9.6f\n", STDV[j], M.std(j)  );
    fprintf( stdout, "   Skew        0.000000  %9.6f\n",      M.skew(j) );
    fprintf( stdout, "   Kurt        0.000000  %9.6f\n\n",    M.kurt(j) );
  }

  M.report( std::cout, "%10.6f" );
}



  
} // end namespace


// =======================================================================================
// **                               U T E S T _ S T A T S                               **
// ======================================================================== END FILE =====
