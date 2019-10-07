// ====================================================================== BEGIN FILE =====
// **                             U T E S T _ T O O L K I T                             **
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
/** @brief  Automated testing for evo::ToolKit class methods.
 *  @file   utest_toolkit.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-28
 *
 *  Provides automated testing for the evo::ToolKit class and methods.
 */
// =======================================================================================

#include <limits.h>
#include <evo/ToolKit.hh>
#include <gtest/gtest.h>
#include <Statistics.hh>

namespace {

// =======================================================================================
TEST( test_toolkit_parametric, real ) {
  // -------------------------------------------------------------------------------------

  const real8_t F = 2.250;
  const real8_t L = 3.550;
  //                       0       1      2      3      4      5      6      7      8
  const real8_t T[] = { -0.500, -0.250, 0.000, 0.250, 0.500, 0.750, 1.000, 1.250, 1.500 };
  const real8_t A[] = {  1.600,  1.925, 2.250, 2.575, 2.900, 3.225, 3.550, 3.875, 4.200 };

  const int32_t n = sizeof(T) / sizeof(T[0]);

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_DOUBLE_EQ(  A[i],  evo::ToolKit::parametric( F, L, T[i] ) );
  }

}


// =======================================================================================
TEST( test_toolkit_parametric, integer ) {
  // -------------------------------------------------------------------------------------

  const int32_t F = 8;
  const int32_t L = 20;
  //                       0       1      2      3      4      5      6      7      8
  const real8_t T[] = { -0.500, -0.250, 0.000, 0.250, 0.500, 0.750, 1.000, 1.250, 1.500 };
  const int32_t A[] = {    2,      5,     8,     11,    14,    17,    20,    23,    26  };

  const int32_t n = sizeof(T) / sizeof(T[0]);

  for ( int32_t i=0; i<n; i++ ) {
    EXPECT_EQ(  A[i],  evo::ToolKit::parametric( F, L, T[i] ) );
  }

}


// =======================================================================================
TEST( test_toolkit_randomize, real ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 100000;
  const real8_t F   = -2.0;
  const real8_t L   =  4.0;
  const real8_t M   = D_HALF*(F+L);
  const real8_t eta = 0.008;

  real8_t* a = new real8_t[n];

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->randomize( a, n, F, L);

  Statistics::single S;
  S.compile( a, n );

  S.report( std::cout );

  EXPECT_NEAR( F, S.minv(), eta );
  EXPECT_NEAR( L, S.maxv(), eta );
  EXPECT_NEAR( M, S.mean(), eta );
      
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_randomize, integer ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 1000000;
  const int32_t F   = -5;
  const int32_t L   = 15;

  const real8_t expected_min  = static_cast<real8_t>(F);
  const real8_t expected_max  = static_cast<real8_t>(L);
  const real8_t expected_mean = D_HALF * (expected_max + expected_min + 1);

  int32_t* a = new int32_t[n];

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->randomize( a, n, F, L );

  Statistics::running S;
  S.reset();
  S.batch( a, n );
  
  S.report( std::cout );

  EXPECT_DOUBLE_EQ( expected_min,  S.minv() );
  EXPECT_DOUBLE_EQ( expected_max,  S.maxv() );
  EXPECT_NEAR( expected_mean, S.mean(), 0.05 );
      
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_randomize, indexed ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 10000;
  const int32_t F   = 0;
  const int32_t L   = n;

  const real8_t expected_min  = static_cast<real8_t>(F);
  const real8_t expected_max  = static_cast<real8_t>(L-1);
  const real8_t expected_mean = D_HALF * (expected_max + expected_min);

  int32_t* a = new int32_t[n];

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->randomize( a, n );

  Statistics::running S;
  S.reset();
  S.batch( a, n );
  
  S.report( std::cout );

  //EXPECT_DOUBLE_EQ( expected_min,  S.minv() );
  //EXPECT_DOUBLE_EQ( expected_max,  S.maxv() );
  //EXPECT_NEAR( expected_mean, S.mean(), 0.1 );

  std::cerr << "    ****************\n"
            << "   *              **\n"
            << "  **************** *\n"
            << "  *              * *\n"
            << "  *  NOT TESTED  * *\n"
            << "  *              **\n"
            << "  ****************\n\n";
      
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_bracket, real ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 10000;
  const real8_t L   = -5.0;
  const real8_t H   =  5.0;

  real8_t* a = new real8_t[n];

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->bracket( a, n, L, H );

  int32_t upper  = 0;
  int32_t lower  = 0;
  int32_t inside = 0;
  for ( int32_t i=0; i<n; i++ ) {
    if ( H > a[i] ) {
      if ( L < a[i] ) {
        inside += 1;
      } else {
        lower +=1;
      }
    } else {
      upper +=1;
    }
  }

  EXPECT_EQ( n, lower+upper );
  EXPECT_EQ( 0, inside );

  real8_t x = Abs( static_cast<real8_t>(lower - upper) ) / static_cast<real8_t>(n);

  EXPECT_NEAR( 0.0, x, 0.1 );
  
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_bracket, real_bias ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 33333;
  const int32_t n1  = 22222;
  const real8_t L   = D_ONE;
  const real8_t H   = D_FOUR;

  real8_t* a = new real8_t[n];
  real8_t* b = new real8_t[n];

  for ( int32_t i=0; i<n; i++ ) {
    b[i] = ( n<n1 ) ? (D_TWO) : (D_THREE);
  }

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->bracket( a, n, L, H, b );

  int32_t upper  = 0;
  int32_t lower  = 0;
  int32_t inside = 0;
  for ( int32_t i=0; i<n; i++ ) {
    if ( H > a[i] ) {
      if ( L < a[i] ) {
        inside += 1;
      } else {
        lower +=1;
      }
    } else {
      upper +=1;
    }
  }

  EXPECT_EQ( n, lower+upper );
  EXPECT_EQ( 0, inside );

  real8_t x = Abs( static_cast<real8_t>(lower - 2*upper) ) / static_cast<real8_t>(n);

  EXPECT_NEAR( 0.0, x, 0.1 );
  
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_bracket, integer ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 10000;
  const int32_t L   = -3;
  const int32_t H   =  7;

  int32_t* a = new int32_t[n];

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->bracket( a, n, L, H );

  int32_t upper  = 0;
  int32_t lower  = 0;
  int32_t inside = 0;
  for ( int32_t i=0; i<n; i++ ) {
    if ( H > a[i] ) {
      if ( L < a[i] ) {
        inside += 1;
      } else {
        lower +=1;
      }
    } else {
      upper +=1;
    }
  }

  EXPECT_EQ( n, lower+upper );
  EXPECT_EQ( 0, inside );

  real8_t x = Abs( static_cast<real8_t>(lower - upper) ) / static_cast<real8_t>(n);

  EXPECT_NEAR( 0.0, x, 0.1 );
  
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_bracket, integer_bias ) {
  // -------------------------------------------------------------------------------------
  const int32_t n   = 33333;
  const int32_t n1  = 22222;
  const int32_t L   = 1;
  const int32_t H   = 4;

  int32_t* a = new int32_t[n];
  int32_t* b = new int32_t[n];

  for ( int32_t i=0; i<n; i++ ) {
    b[i] = ( n<n1 ) ? (2) : (3);
  }

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->bracket( a, n, L, H, b );

  int32_t upper  = 0;
  int32_t lower  = 0;
  int32_t inside = 0;
  for ( int32_t i=0; i<n; i++ ) {
    if ( H > a[i] ) {
      if ( L < a[i] ) {
        inside += 1;
      } else {
        lower +=1;
      }
    } else {
      upper +=1;
    }
  }

  EXPECT_EQ( n, lower+upper );
  EXPECT_EQ( 0, inside );

  real8_t x = Abs( static_cast<real8_t>(lower - 2*upper) ) / static_cast<real8_t>(n);

  EXPECT_NEAR( 0.0, x, 0.1 );
  
  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_noise, real ) {
  // -------------------------------------------------------------------------------------
  const int32_t n  = 20000;
  const int32_t n1 = 10000;
  const real8_t L  = -6.0;
  const real8_t H  =  12.0;
  const real8_t sigma = 2.0;
  const real8_t ac    = 0.0;
  const real8_t bc    = 5.0;

  real8_t* a = new real8_t[n];

  for ( int32_t i=0; i<n; i++ ) {
    a[i] = (i<n1) ? (ac) : (bc);
  }

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->noise( a, n, sigma, L, H );

  Statistics::single A,B;

  A.compile( a, n1 );
  B.compile( (a+n1), n1 );

  EXPECT_NEAR( L,  A.minv(), 0.1 );
  EXPECT_NEAR( ac, A.mean(), 0.1 );
  EXPECT_NEAR( bc, B.mean(), 0.1 );
  EXPECT_NEAR( H,  B.maxv(), 0.1 );

  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_noise, real_bias ) {
  // -------------------------------------------------------------------------------------
  const int32_t n  = 20000;
  const int32_t n1 = 10000;
  const real8_t L  = -6.0;
  const real8_t H  =  12.0;
  const real8_t sigma = 2.0;
  const real8_t ac    = 0.0;
  const real8_t bc    = 5.0;

  real8_t* a = new real8_t[n];
  real8_t* b = new real8_t[n];

  for ( int32_t i=0; i<n; i++ ) {
    a[i] = 7.3;
    b[i] = (i<n1) ? (ac) : (bc);
  }

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->noise( a, n, sigma, L, H, b );

  Statistics::single A,B;

  A.compile( a, n1 );
  B.compile( (a+n1), n1 );

  EXPECT_NEAR( L,  A.minv(), 0.1 );
  EXPECT_NEAR( ac, A.mean(), 0.1 );
  EXPECT_NEAR( bc, B.mean(), 0.1 );
  EXPECT_NEAR( H,  B.maxv(), 0.1 );

  delete[] a;
  delete[] b;
}


// =======================================================================================
TEST( test_toolkit_noise, integer ) {
  // -------------------------------------------------------------------------------------
  const int32_t n  = 20000;
  const int32_t n1 = 10000;
  const int32_t L  = -6;
  const int32_t H  =  12;
  const real8_t sigma = 2.0;
  const real8_t ac    = 0.0;
  const real8_t bc    = 5.0;

  int32_t* a = new int32_t[n];

  for ( int32_t i=0; i<n; i++ ) {
    a[i] = (i<n1) ? (ac) : (bc);
  }

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->noise( a, n, sigma, L, H );

  Statistics::running A,B;

  A.reset();
  B.reset();
  
  for ( int32_t i=0; i<n; i++ ) {
    if ( i < n1 ) {
      A.update( a[i] );
    } else {
      B.update( a[i] );
    }
  }
  
  EXPECT_NEAR( L,  A.minv(), 0.1 );
  EXPECT_NEAR( ac, A.mean(), 0.1 );
  EXPECT_NEAR( bc, B.mean(), 0.1 );
  EXPECT_NEAR( H,  B.maxv(), 0.1 );

  delete[] a;
}


// =======================================================================================
TEST( test_toolkit_noise, integer_bias ) {
  // -------------------------------------------------------------------------------------
  const int32_t n  = 20000;
  const int32_t n1 = 10000;
  const int32_t L  = -6;
  const int32_t H  =  12;
  const real8_t sigma = 2.0;
  const real8_t ac    = 0.0;
  const real8_t bc    = 5.0;

  int32_t* a = new int32_t[n];
  int32_t* b = new int32_t[n];

  for ( int32_t i=0; i<n; i++ ) {
    a[i] = 7;
    b[i] = (i<n1) ? (ac) : (bc);
  }

  evo::ToolKit* tk = evo::ToolKit::getInstance( Dice::TestDice() );

  tk->noise( a, n, sigma, L, H, b );

  Statistics::running A,B;

  A.reset();
  B.reset();
  
  for ( int32_t i=0; i<n; i++ ) {
    if ( i < n1 ) {
      A.update( a[i] );
    } else {
      B.update( a[i] );
    }
  }
  
  EXPECT_NEAR( L,  A.minv(), 0.1 );
  EXPECT_NEAR( ac, A.mean(), 0.1 );
  EXPECT_NEAR( bc, B.mean(), 0.1 );
  EXPECT_NEAR( H,  B.maxv(), 0.1 );

  delete[] a;
  delete[] b;
}


} // end namespace


// =======================================================================================
// **                             U T E S T _ T O O L K I T                             **
// ======================================================================== END FILE =====
