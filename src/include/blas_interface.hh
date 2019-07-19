// ====================================================================== BEGIN FILE =====
// **                            B L A S _ I N T E R F A C E                            **
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
/** @brief  External BLAS interface to FORTRAN procedures.
 *  @file   blas_interface.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-14
 *
 *  Provides C++ interface to FORTRAN Basic Linerar Algebra Subprograms (BLAS) procedures.
 
 @BOOK{laug,
      AUTHOR = {Anderson, E. and Bai, Z. and Bischof, C. and
                Blackford, S. and Demmel, J. and Dongarra, J. and
                Du Croz, J. and Greenbaum, A. and Hammarling, S. and
                McKenney, A. and Sorensen, D.},
      TITLE = {{LAPACK} Users' Guide},
      EDITION = {Third},
      PUBLISHER = {Society for Industrial and Applied Mathematics},
      YEAR = {1999},
      ADDRESS = {Philadelphia, PA},
      ISBN = {0-89871-447-8 (paperback)} }

 */
// =======================================================================================


#ifndef __HH_BLAS_INTERFACE_TRNCMP
#define __HH_BLAS_INTERFACE_TRNCMP


#include <trncmp.hh>


// =======================================================================================
extern "C" {
  // -------------------------------------------------------------------------------------

  // =====================================================================================
  // **  L E V E L   1   *   V E C T O R    O P E R A T I O N S                         **
  // =====================================================================================
  
  // -------------------------------------------------------------------------------------
  //          dy := dx
  // -------------------------------------------------------------------------------------
  extern void dcopy_( const int32_t* n,
		      const real8_t* dx,
		      const int32_t* incx,
		      const real8_t* dy,
		      const int32_t* incy );

  // -------------------------------------------------------------------------------------
  //          dy <==> dx
  // -------------------------------------------------------------------------------------
  extern void dswap_( const int32_t* n,
		      const real8_t* dx,
		      const int32_t* incx,
		      const real8_t* dy,
		      const int32_t* incy );

  // -------------------------------------------------------------------------------------
  //          x := da*x
  // -------------------------------------------------------------------------------------
  extern void dscal_( const int32_t* n,
		      const real8_t* da,
		      const real8_t* dx,
		      const int32_t* incx );

  // =====================================================================================
  // **  L E V E L   2   *   V E C T O R  / M A T R I X    O P E R A T I O N S          **
  // =====================================================================================
  
  // -------------------------------------------------------------------------------------
  //          y := alpha*op(A)*x + beta*y     op = N,T,C
  // -------------------------------------------------------------------------------------
  extern void dgemv_( const char*    trans,
		      const int32_t* m,
		      const int32_t* n,
		      const real8_t* alpha,
		      const real8_t* A,
		      const int32_t* lda,
		      const real8_t* x,
		      const int32_t* incx,
		      const real8_t* beta,
		      const real8_t* y,
		      const int32_t* incy );

  // =====================================================================================
  // **  L E V E L   2   *   M A T R I X  / M A T R I X    O P E R A T I O N S          **
  // =====================================================================================
  
  // -------------------------------------------------------------------------------------
  //          C := alpha*op( A )*op( B ) + beta*C
  // -------------------------------------------------------------------------------------
  extern void dgemm_( const char*    transa,
		      const char*    transb,
		      const int32_t* m,
		      const int32_t* n,
		      const int32_t* k,
		      const real8_t* alpha,
		      const real8_t* A,
		      const int32_t* lda,
		      const real8_t* B,
		      const int32_t* ldb,
		      const real8_t* beta,
		      const real8_t* C,
		      const int32_t* ldc );

} // end extern "C"


#endif


// =======================================================================================
// **                            B L A S _ I N T E R F A C E                            **
// ======================================================================== END FILE =====
