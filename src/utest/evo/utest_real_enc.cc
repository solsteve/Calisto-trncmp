// ====================================================================== BEGIN FILE =====
// **                        U T E S T _ R E A L E N C O D I N G                        **
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
/** @brief  Automated testing for evo::RealEncoding class methods.
 *  @file   utest_real_enc.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-26
 *
 *  Provides automated testing for the evo::RealEncoding class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <evo/RealEncoding.hh>
#include <gtest/gtest.h>

namespace {

static real8_t MDATA[] = { 1.1, 1.2, 1.3, 1.4,
                           2.1, 2.2, 2.3, 2.4,
                           3.1, 3.2, 3.3, 3.4 };
static const int32_t NM = 3;
static const int32_t ND = 4;

static u_int8_t* MBUFFER = reinterpret_cast<u_int8_t*>(MDATA);

// =======================================================================================
TEST( test_real_enc_create, empty ) {
  // -------------------------------------------------------------------------------------
  evo::RealEncoding M;
  EXPECT_EQ( 0, M.size() );
  EXPECT_EQ( 0, M.count() );
}


// =======================================================================================
TEST( test_real_enc_create, sourced ) {
  // -------------------------------------------------------------------------------------
  evo::RealEncoding M1( ND, -2.0, 2.0, MBUFFER, 0  );
  evo::RealEncoding M2( ND, -2.0, 2.0, MBUFFER, 4*sizeof(real8_t) );
  evo::RealEncoding M3( ND, -2.0, 2.0, MBUFFER, 8*sizeof(real8_t) );

  int32_t n = M1.count();
  
  EXPECT_EQ( ND*sizeof(real8_t), M1.size() );
  EXPECT_EQ( ND, M1.count() );
  EXPECT_EQ( ND*sizeof(real8_t), M2.size() );
  EXPECT_EQ( ND, M2.count() );
  EXPECT_EQ( ND*sizeof(real8_t), M3.size() );
  EXPECT_EQ( ND, M3.count() );

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ( (MDATA+0)[i], M1.get(i) );
    EXPECT_DOUBLE_EQ( (MDATA+4)[i], M2.get(i) );
    EXPECT_DOUBLE_EQ( (MDATA+8)[i], M3.get(i) );
  }
}


// =======================================================================================
TEST( test_real_enc_create, alloc ) {
  // -------------------------------------------------------------------------------------
  evo::RealEncoding M( 4, -2.0, 2.0 );
  
  EXPECT_EQ( 4*sizeof(real8_t), M.size() );
  EXPECT_EQ( 4, M.count() );

  M.set( 2, 123.456 );
  M.set( 1, 456.789 );

  EXPECT_DOUBLE_EQ( 456.789, M.get( 1 ) );
  EXPECT_DOUBLE_EQ( 123.456, M.get( 2 ) );
}


// =======================================================================================
TEST( test_real_enc_access, getset ) {
  // -------------------------------------------------------------------------------------
  evo::RealEncoding M( 4, -2.0, 4.0, MBUFFER );

  EXPECT_DOUBLE_EQ( 1.1, M.get( 0 ) );
  EXPECT_DOUBLE_EQ( 1.2, M.get( 1 ) );
  EXPECT_DOUBLE_EQ( 1.3, M.get( 2 ) );
  EXPECT_DOUBLE_EQ( 1.4, M.get( 3 ) );
  
  M.set( 0, 3.71 );
  M.set( 1, 3.72 );
  M.set( 2, 3.73 );
  M.set( 3, 3.74 );

  EXPECT_DOUBLE_EQ( 3.71, M.get( 0 ) );
  EXPECT_DOUBLE_EQ( 3.72, M.get( 1 ) );
  EXPECT_DOUBLE_EQ( 3.73, M.get( 2 ) );
  EXPECT_DOUBLE_EQ( 3.74, M.get( 3 ) );
}


// =======================================================================================
TEST( test_real_enc_storage, loadstore ) {
  // -------------------------------------------------------------------------------------
  real8_t D[] = { 1.2, 3.4, 5.6, 7.8 };
  evo::RealEncoding M1( 4, 0.0, 100.0, reinterpret_cast<u_int8_t*>(D) );
  evo::RealEncoding M2( 4, 0.0, 100.0 );

  u_int8_t* buf = M1.create_buffer();

  M2.zero();
  
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 0 ) );
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 1 ) );
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 2 ) );
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 3 ) );

  M1.store( buf );
  M2.load( buf );

  EXPECT_DOUBLE_EQ( 1.2, M2.get( 0 ) );
  EXPECT_DOUBLE_EQ( 3.4, M2.get( 1 ) );
  EXPECT_DOUBLE_EQ( 5.6, M2.get( 2 ) );
  EXPECT_DOUBLE_EQ( 7.8, M2.get( 3 ) );

  delete[] buf;
}


// =======================================================================================
TEST( test_real_enc_storage, copy ) {
  // -------------------------------------------------------------------------------------
  real8_t D[] = { 1.2, 3.4, 5.6, 7.8 };
  evo::RealEncoding M1( 4, 0.0, 100.0, reinterpret_cast<u_int8_t*>(D) );
  evo::RealEncoding M2( 4, 0.0, 100.0 );

  u_int8_t* buf = M1.create_buffer();

  M2.zero();
  
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 0 ) );
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 1 ) );
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 2 ) );
  EXPECT_DOUBLE_EQ( D_ZERO, M2.get( 3 ) );

  M2.copy( &M1 );

  EXPECT_DOUBLE_EQ( 1.2, M2.get( 0 ) );
  EXPECT_DOUBLE_EQ( 3.4, M2.get( 1 ) );
  EXPECT_DOUBLE_EQ( 5.6, M2.get( 2 ) );
  EXPECT_DOUBLE_EQ( 7.8, M2.get( 3 ) );

  real8_t* B = M2.get_data();

  EXPECT_DOUBLE_EQ( 1.2, B[0] );
  EXPECT_DOUBLE_EQ( 3.4, B[1] );
  EXPECT_DOUBLE_EQ( 5.6, B[2] );
  EXPECT_DOUBLE_EQ( 7.8, B[3] );
  
}


// =======================================================================================
TEST( test_real_enc_manipulate, compare ) {
  // -------------------------------------------------------------------------------------
  {
    real8_t L[] = { 1.2, 3.4, 5.6 };
    real8_t R[] = { 1.2, 3.4, 5.6 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( 0, ML.compare( &MR ) );
  }

  {
    real8_t L[] = { 1.1, 3.4, 5.6 };
    real8_t R[] = { 1.2, 3.4, 5.6 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( -1, ML.compare( &MR ) );
  }

  {
    real8_t L[] = { 1.2, 3.4, 5.6 };
    real8_t R[] = { 1.1, 3.4, 5.6 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( +1, ML.compare( &MR ) );
  }

  {
    real8_t L[] = { 1.2, 3.1, 5.6 };
    real8_t R[] = { 1.2, 3.4, 5.6 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( -2, ML.compare( &MR ) );
  }

  {
    real8_t L[] = { 1.2, 3.4, 5.6 };
    real8_t R[] = { 1.2, 3.1, 5.6 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( +2, ML.compare( &MR ) );
  }

  {
    real8_t L[] = { 1.2, 3.4, 5.1 };
    real8_t R[] = { 1.2, 3.4, 5.6 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( -3, ML.compare( &MR ) );
  }

  {
    real8_t L[] = { 1.2, 3.4, 5.6 };
    real8_t R[] = { 1.2, 3.4, 5.1 };
    evo::RealEncoding ML(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(L) );
    evo::RealEncoding MR(3, 0.0, 100.0,reinterpret_cast<u_int8_t*>(R) );
    EXPECT_EQ( +3, ML.compare( &MR ) );
  }
}



} // end namespace


// =======================================================================================
// **                              U T E S T _ M E T R I C                              **
// ======================================================================== END FILE =====
