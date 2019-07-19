// ====================================================================== BEGIN FILE =====
// **                              C T E S T _ L A P A C K                              **
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
 *  @file   StopWatch.hh
 *  @author Stephen W. Soliday
 *  @date   2014-01-27  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for precision time keeping.
 */
// =======================================================================================

#include <blas_interface.hh>
#include <array_print.hh>
#include <StopWatch.hh>

// =======================================================================================
void TEST01( void ) {
  // -------------------------------------------------------------------------------------
  char    trans = 'T';

  int32_t m     = 3;
  int32_t n     = 2;
  real8_t alpha = 3.1;
  real8_t A[]   = { 1.1, 1.2, 1.3,    1.4, 1.5,
		    2.1, 2.2, 2.3,    2.4, 2.5 };
  
  int32_t lda   = 5;
  real8_t x[]   = { 1.0, 9.0, 9.0, 2.0, 9.0, 9.0, 3.0 };
  int32_t incx  = 3;
  real8_t beta  = 0.0;
  real8_t y[]   = { 9.0, 8.0, 9.0, 8.0, 9.0, 8.0, 9.0 };
  int32_t incy  = 2;

  dgemv_( &trans, &m, &n, &alpha, A, &lda, x, &incx, &beta, y, &incy );

  std::cout << "Y = (" << toString(y,7) << ")\n";
}

// =======================================================================================
void TEST02( void ) {
  // -------------------------------------------------------------------------------------

  std::cout << "\n----- FORTRAN (Column Major) ----------------------------\n\n";
  char    transa = 'N';
  char    transb = 'N';

  int32_t m      = 4;
  int32_t n      = 2;
  int32_t k      = 3;
  
  real8_t alpha  = 3.1;
  
  real8_t fA[] = { 1.1, 2.1, 3.1, 4.1, 9995.1,
		   1.2, 2.2, 3.2, 4.2, 9995.2,
		   1.3, 2.3, 3.3, 4.3, 9995.3 };
  int32_t lda   = 5;
  
  real8_t fB[] = { 11.0, 21.0, 31.0, 99941.0, 99951.0, 99961.0,
		   12.0, 22.0, 32.0, 99942.0, 99952.0, 99962.0 };
  int32_t ldb   = 6;

  real8_t beta  = 0.0;

  real8_t fC[] = { 77.11, 77.21, 77.31, 77.41, -0.0051, -0.0061, -0.0071,
		   88.12, 88.22, 88.32, 88.42, -0.0052, -0.0062, -0.0072 };
  int32_t ldc   = 7;

  dgemm_( &transa, &transb, &m, &n, &k,
	  &alpha, fA, &lda,      fB, &ldb,
	  &beta,  fC, &ldc );

  std::cout << "C = (" << toString(fC,14) << ")\n";
}

// =======================================================================================
void TEST03( void ) {
  // -------------------------------------------------------------------------------------

  std::cout << "\n----- C/C++   (Row Major) -------------------------------\n\n";
  
  char    transa = 'N';
  char    transb = 'N';

  int32_t m      = 4;
  int32_t n      = 2;
  int32_t k      = 3;
  real8_t alpha  = 3.1;
  real8_t A[]    = { 1.1, 1.2, 1.3,    9991.4, 9991.5,
		     2.1, 2.2, 2.3,    9992.4, 9992.5,
		     3.1, 3.2, 3.3,    9993.4, 9993.5,
		     4.1, 4.2, 4.3,    9994.4, 9994.5 };
  int32_t lda   = 5;
  
  real8_t B[]   = { 11.0, 12.0,    99913.9, 99914.9, 99915.9, 99916.9,
		    21.0, 22.0,    99923.9, 99924.9, 99925.9, 99926.9,
		    31.0, 32.0,    99933.9, 99934.9, 99935.9, 99936.9 };
  int32_t ldb   = 6;
  
  real8_t beta  = 0.0;
  real8_t C[]   = { 77.11, 88.12,    -0.0013,
		    77.21, 88.22,    -0.0023,
		    77.31, 88.32,    -0.0033,
		    77.41, 88.42,    -0.0043 };
  int32_t ldc   = 3;
  
  dgemm_( &transa, &transb, &n, &m, &k,
	  &alpha, B, &ldb,      A, &lda,
	  &beta,  C, &ldc );

  std::cout << "C = (" << toString(C,12) << ")\n";
}


// =======================================================================================
real8_t TEST11( int32_t n, real8_t* A, int32_t incx, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    // v-------------------------------------v
    for ( int32_t i=0; i<n; i++ ) {
      sum += A[i*incx];
    }
    // ^-------------------------------------^
  }
  real8_t elap = SW.check();

  std::cout << "\nA[i*incx]\n";
  std::cout << SAMP << " samples of " << n << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(n*SAMP) / elap) << " add/s ]\n";

  return sum;
}


// =======================================================================================
real8_t TEST12( int32_t n, real8_t* A, int32_t incx, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    // v-------------------------------------v
    for ( int32_t i=0; i<n; i++ ) {
      sum += *(A+i*incx);
    }
    // ^-------------------------------------^
  }
  real8_t elap = SW.check();

  std::cout << "\n*(A+i*incx)\n";
  std::cout << SAMP << " samples of " << n << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(n*SAMP) / elap) << " add/s ]\n";

  return sum;
}


// =======================================================================================
real8_t TEST13( int32_t n, real8_t* A, int32_t incx, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    // v-------------------------------------v
    real8_t* P = A;
    for ( int32_t i=0; i<n; i++ ) {
      sum += *P;  P += incx;
    }
    // ^-------------------------------------^
  }
  real8_t elap = SW.check();

  std::cout << "*P;  P += incx\n\n";
  std::cout << SAMP << " samples of " << n << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(n*SAMP) / elap) << " add/s ]\n";

  return sum;
}


// =======================================================================================
real8_t TEST14( int32_t n, real8_t* A, int32_t incx, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    // v-------------------------------------v
    int32_t P = 0;
    for ( int32_t i=0; i<n; i++ ) {
      sum += A[P];  P += incx;
    }
    // ^-------------------------------------^
  }
  real8_t elap = SW.check();

  std::cout << "A[P];  P += incx\n\n";
  std::cout << SAMP << " samples of " << n << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(n*SAMP) / elap) << " add/s ]\n";

  return sum;
}


// =======================================================================================
void EXPECT( real8_t a, real8_t b ) {
  // -------------------------------------------------------------------------------------
  real8_t diff = a - b;
  std::cout << "Expected " << a << " got " << b << " error=" << diff << "\n\n";
}

// =======================================================================================
void TEST04( void ) {
  // -------------------------------------------------------------------------------------

  std::cout << "\n===== VECTOR ADDRESSING ================================\n\n";

  size_t    samp = 1000000;
  int32_t   n    = 10000;
  int32_t   incx = 7;

  int32_t   k = 1 + (n-1)*incx;
  int32_t   m = k + 4*incx;

  real8_t*  buffer = new real8_t[m];
  for ( int32_t i=0; i<m; i++ ) {
    buffer[i] = nan("trncmp");
  }

  real8_t* x = (buffer+2*incx);

  for ( int32_t i=0; i<k; i++ ) {
    x[i] = 1.0e8;
  }

  for ( int32_t i=0; i<n; i++ ) {
    x[i*incx] = (real8_t)i;
  }

  real8_t expected = ((real8_t)samp) * ((real8_t)(n*(n-1))) * 5.0e-1;
  
  // -------------------------------------------------------------------------------------
  
  EXPECT( expected, TEST11( n, x, incx, samp ) );
  EXPECT( expected, TEST12( n, x, incx, samp ) );
  EXPECT( expected, TEST13( n, x, incx, samp ) );
  EXPECT( expected, TEST14( n, x, incx, samp ) );
  
  // -------------------------------------------------------------------------------------

  delete[] buffer;
}

// =======================================================================================
real8_t TEST21( int32_t nr, int32_t nc, real8_t* A, int32_t lda, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    real8_t cr = D_ZERO;
    // v-------------------------------------v
    for (int32_t r=0; r<nr; r++) {
      for ( int32_t c=0; c<nc; c++ ) {
	cr += A[r*lda + c];
      }
    }
    // ^-------------------------------------^
    sum += (cr / (real8_t)SAMP);
  }
  real8_t elap = SW.check();

  std::cout << "A[r*lda + c] by row\n\n";
  std::cout << SAMP << " samples of " << (nr*nc) << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(nr*nc*SAMP) / elap) << " add/s ]\n";

  return sum;
}


// =======================================================================================
real8_t TEST22( int32_t nr, int32_t nc, real8_t* A, int32_t lda, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    real8_t cr = D_ZERO;
    // v-------------------------------------v
    for ( int32_t c=0; c<nc; c++ ) {
      for (int32_t r=0; r<nr; r++) {
	cr += A[r*lda + c];
      }
    }
    // ^-------------------------------------^
    sum += (cr / (real8_t)SAMP);
  }
  real8_t elap = SW.check();

  std::cout << "A[r*lda + c] by col\n\n";
  std::cout << SAMP << " samples of " << (nr*nc) << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(nr*nc*SAMP) / elap) << " add/s ]\n";

  return sum;
}


// =======================================================================================
real8_t TEST23( int32_t nr, int32_t nc, real8_t* A, int32_t lda, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    real8_t cr = D_ZERO;
    // v-------------------------------------v
    for (int32_t r=0; r<nr; r++) {
      for ( int32_t c=0; c<nc; c++ ) {
	cr += *(A + c + r*lda);
      }
    }
    // ^-------------------------------------^
    sum += (cr / (real8_t)SAMP);
  }
  real8_t elap = SW.check();

  std::cout << "*(A + c + r*lda) by row\n\n";
  std::cout << SAMP << " samples of " << (nr*nc) << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(nr*nc*SAMP) / elap) << " add/s ]\n";

  return sum;
}




// =======================================================================================
real8_t TEST24( int32_t nr, int32_t nc, real8_t* A, int32_t lda, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  for ( size_t s=0; s<SAMP; s++ ) {
    real8_t cr = D_ZERO;
    // v-------------------------------------v
    for ( int32_t c=0; c<nc; c++ ) {
      for (int32_t r=0; r<nr; r++) {
	cr += *(A + c + r*lda);
      }
    }
    // ^-------------------------------------^
    sum += (cr / (real8_t)SAMP);
  }
  real8_t elap = SW.check();

  std::cout << "*(A + c + r*lda) by col\n\n";
  std::cout << SAMP << " samples of " << (nr*nc) << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(nr*nc*SAMP) / elap) << " add/s ]\n";

  return sum;
}




// =======================================================================================
real8_t TEST25( int32_t nr, int32_t nc, real8_t* A, int32_t lda, size_t SAMP ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;

  StopWatch SW;
  SW.reset();
  int32_t em1 = lda - nc;
  for ( size_t s=0; s<SAMP; s++ ) {
    real8_t cr = D_ZERO;
    int32_t idx = 0;
    // v-------------------------------------v
    for (int32_t r=0; r<nr; r++) {
      for ( int32_t c=0; c<nc; c++ ) {
	cr += *(A + idx);
	idx += 1;
      }
      idx += em1;
    }
    // ^-------------------------------------^
    sum += (cr / (real8_t)SAMP);
  }
  real8_t elap = SW.check();

  std::cout << "indexed\n\n";
  std::cout << SAMP << " samples of " << (nr*nc) << " addresses in " << elap << " seconds. [ "
	    << ((real8_t)(nr*nc*SAMP) / elap) << " add/s ]\n";

  return sum;
}





// =======================================================================================
void TEST05( void ) {
  // -------------------------------------------------------------------------------------

  std::cout << "\n===== MATRIX ADDRESSING ================================\n\n";
  
  size_t    samp = 2000000;
  int32_t   m    = 60;   // ROWS
  int32_t   n    = 60;   // COLS
  int32_t   lda  = 120;   // MAXCOLS;

  int32_t   k = lda * m;

  real8_t*  A = new real8_t[k];

  int32_t idx = 0;
  for (int32_t r=0; r<m; r++) {
    for ( int32_t c=0; c<n; c++ ) {
      A[idx++] = (real8_t)r + ((real8_t)c) / 10000.0;
    }
    for ( int32_t c=n; c<lda; c++ ) {
      A[idx++] = nan("T");
    }
  }

  real8_t expected = D_ZERO;
  for (int32_t r=0; r<m; r++) {
    for ( int32_t c=0; c<n; c++ ) {
      real8_t x = A[r*lda + c];
      //std::cout << c_fmt( "%11.4f", x );
      expected += x;
    }
    //std::cout << "\n";
  }

  std::cout << "Expected sum = " << expected << "\n";
  
  // -------------------------------------------------------------------------------------

  EXPECT( expected, TEST21( m, n, A, lda, samp ) );
  EXPECT( expected, TEST22( m, n, A, lda, samp ) );
  EXPECT( expected, TEST23( m, n, A, lda, samp ) );
  EXPECT( expected, TEST24( m, n, A, lda, samp ) );
  EXPECT( expected, TEST25( m, n, A, lda, samp ) );
 
  // -------------------------------------------------------------------------------------
  
  delete[] A;
}
  
// =======================================================================================
int main( void ) {
  // -------------------------------------------------------------------------------------
  //TEST02();
  //TEST03();
  //TEST04();
  TEST05();
  return 0;
}




		      
		     
