// ====================================================================== BEGIN FILE =====
// **                                C T E S T _ B L A S                                **
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
/** @brief  Test LAPACK/BLAS ROUTINES
 *  @file   ctest_blas.hh
 *  @author Stephen W. Soliday
 *  @date   2014-01-27  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for precision time keeping.
 */
// =======================================================================================

#include <Matrix.hh>
#include <Dice.hh>
#include <StopWatch.hh>

static u_int32_t SEED_MATTER[] = { 0x29341EA3, 0x9257677C, 0xCC98B1D1, 0x7C5EB68C,
                                   0x13ED5BC5, 0x3C91F88F, 0xE1A42570, 0x24CA88CD,
                                   0xAE36E97A, 0x59BADCBB, 0x4B9ED120, 0x952318E6,
                                   0xDD62B887, 0xCFC13ED9, 0x0F6A241B, 0x43970DA6,
                                   0xDF52E725, 0x4F6FE0ED, 0xCF9D4A7B, 0xA8742AE2,
                                   0x3B0590CF, 0xE20ACC41, 0x10A25D9B, 0xD59349FF,
                                   0x10BEE39E, 0x33CE2526, 0xD8029C5B, 0xFC6D3D65,
                                   0xD08E3996, 0x6FCFC48D, 0x2FD4F96B, 0x1AAEC36F };

// =======================================================================================
void TEST_REINDEX_ROW( const int32_t nsamp, Matrix& M, int32_t* sidx, Matrix& S ) {
  // -------------------------------------------------------------------------------------
  try {
    for ( int32_t i=0; i<nsamp; i++ ) {
      M.reindex_rows( S, sidx );
    }      
  } catch( std::length_error& e ) {
    std::cerr << e.what() << "\n";
  }
}

// =======================================================================================
void TEST_REINDEX_COL( const int32_t nsamp, Matrix& M, int32_t* sidx, Matrix& S ) {
  // -------------------------------------------------------------------------------------
  try {
    for ( int32_t i=0; i<nsamp; i++ ) {
      M.reindex_columns( S, sidx );
    }      
  } catch( std::length_error& e ) {
    std::cerr << e.what() << "\n";
  }
}

// =======================================================================================
void TEST_SWP_ROW_NOBLAS( const int32_t nsamp, Matrix& M, int32_t* sidx ) {
  // -------------------------------------------------------------------------------------
  try {
    const int32_t n = size( M, 1 );
    for ( int32_t i=0; i<nsamp; i++ ) {
      for ( int32_t j=0; j<n; j++ ) {
        M.swap_row_noblas( j, sidx[j] );
      }
    }      
  } catch( std::length_error& e ) {
    std::cerr << e.what() << "\n";
  }
}

// =======================================================================================
void TEST_SWP_ROW_BLAS( const int32_t nsamp, Matrix& M, int32_t* sidx ) {
  // -------------------------------------------------------------------------------------
  try {
    const int32_t n = size( M, 1 );
    for ( int32_t i=0; i<nsamp; i++ ) {
      for ( int32_t j=0; j<n; j++ ) {
        M.swap_row_blas( j, sidx[j] );
      }
    }      
  } catch( std::length_error& e ) {
    std::cerr << e.what() << "\n";
  }
}

// =======================================================================================
void TEST_SWP_COL_NOBLAS( const int32_t nsamp, Matrix& M, int32_t* sidx ) {
  // -------------------------------------------------------------------------------------
  try {
    const int32_t n = size( M, 1 );
    for ( int32_t i=0; i<nsamp; i++ ) {
      for ( int32_t j=0; j<n; j++ ) {
        M.swap_column_noblas( j, sidx[j] );
      }
    }      
  } catch( std::length_error& e ) {
    std::cerr << e.what() << "\n";
  }
}

// =======================================================================================
void TEST_SWP_COL_BLAS( const int32_t nsamp, Matrix& M, int32_t* sidx ) {
  // -------------------------------------------------------------------------------------
  try {
    const int32_t n = size( M, 1 );
    for ( int32_t i=0; i<nsamp; i++ ) {
      for ( int32_t j=0; j<n; j++ ) {
        M.swap_column_blas( j, sidx[j] );
      }
    }
  } catch( std::length_error& e ) {
    std::cerr << e.what() << "\n";
  }
}

// =======================================================================================
void TEST01( int32_t nrow, int32_t ncol, int32_t nsamp ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();

  StopWatch SW;

  const int32_t NS = nsamp;
  const int32_t NR = nrow;
  const int32_t NC = ncol;

  Matrix data(NR,NC);
  int32_t* rswp = new int32_t[NR];
  int32_t* cswp = new int32_t[NC];

  for ( int32_t i=0; i<NR; i++ ) {
    rswp[i] = i;
  }
  dd->shuffle( rswp, NR );

  for ( int32_t i=0; i<NC; i++ ) {
    cswp[i] = i;
  }
  dd->shuffle( cswp, NC );

  for ( int32_t c=0; c<NC; c++ ) {
    for ( int32_t r=0; r<NR; r++ ) {
      data(r,c) = D_TWO*dd->uniform() - D_ONE;
    }
  }

  SW.reset();
  TEST_SWP_COL_NOBLAS( NS, data, cswp );
  real8_t swp_col_nb = 1.0e-6 * ((real8_t)(NS*NC)) / SW.check() ;

  SW.reset();
  TEST_SWP_COL_BLAS( NS, data, cswp );
  real8_t swp_col =  1.0e-6 * ((real8_t)(NS*NC)) / SW.check();

  SW.reset();
  TEST_SWP_ROW_NOBLAS( NS, data, cswp );
  real8_t swp_row_nb = 1.0e-6 * ((real8_t)(NS*NC)) / SW.check();

  SW.reset();
  TEST_SWP_ROW_BLAS( NS, data, cswp );
  real8_t swp_row = 1.0e-6 * ((real8_t)(NS*NC)) / SW.check();

  Matrix S(data);
  SW.reset();
  TEST_REINDEX_ROW( NS, data, cswp, S );
  real8_t reindex_row = 1.0e-6 * ((real8_t)(NS*NC)) / SW.check();

  Matrix R(data);
  SW.reset();
  TEST_REINDEX_COL( NS, data, cswp, R );
  real8_t reindex_col = 1.0e-6 * ((real8_t)(NS*NC)) / SW.check();

  fprintf( stdout,
           "%4d %4d    %10.6f %10.6f %10.6f    %10.6f %10.6f %10.6f\n",
           nrow, ncol,
           swp_col, swp_col_nb, reindex_col,
           swp_row, swp_row_nb, reindex_row );
  
  delete[] cswp;
  delete[] rswp;
}


// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  Dice* dd = Dice::getInstance();
  dd->seed_set( reinterpret_cast<void*>(SEED_MATTER), dd->seed_size() );

  std::cerr << "\n\n"
            << "  Order             Swap Columns                        Swap Rows\n"
            << "nrow ncol    blas     no  blas    reindex       blas     no  blas   reindex\n"
            << "---- ----  ---------- ---------- ----------  ---------- ---------- ----------\n";

  for ( int32_t i=2; i<100; i++ ) {
    TEST01( i, i, 100000 );
  }
  
  std::cerr << "\n\n";

  return 0;
}


// =======================================================================================
// **                                C T E S T _ B L A S                                **
// ======================================================================== END FILE =====
