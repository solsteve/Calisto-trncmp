// ====================================================================== BEGIN FILE =====
// **                          L A P A C K _ I N T E R F A C E                          **
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
/** @brief  External LAPACK interface to FORTRAN procedures.
 *  @file   lapack_interface.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-21
 *
 *  Provides C++ interface to FORTRAN Linerar Algebra Package (LAPACK) procedures.
 
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


#ifndef __HH_LAPACK_INTERFACE_TRNCMP
#define __HH_LAPACK_INTERFACE_TRNCMP


#include <trncmp.hh>


// =======================================================================================
extern "C" {
  // -------------------------------------------------------------------------------------

  // -------------------------------------------------------------------------------------
  // DGETRF - compute an LU factorization of a general M-by-N matrix A
  //          using partial pivoting with row interchanges
  // -------------------------------------------------------------------------------------
  extern void dgetrf_( const int32_t* m,
                       const int32_t* n,
                       const real8_t* A,
                       const int32_t* lda,
                       const int32_t* ipiv,
                       const int32_t* info );

  // -------------------------------------------------------------------------------------
  // DGETRI - compute the inverse of a matrix using the LU factorization computed by DGETRF
  // -------------------------------------------------------------------------------------

  extern void dgetri_( const int32_t* n,
                       const real8_t* A,
                       const int32_t* lda,
                       const int32_t* ipiv,
                       const real8_t* work,
                       const int32_t* lwork,
                       const int32_t* info );

  // -------------------------------------------------------------------------------------
  // DGESVD - compute the singular value decomposition of a general rectangular matrix.
  // -------------------------------------------------------------------------------------

  extern void dgesvd_( const char*    jobu,
                       const char*    jobvt,
                       const int32_t* m,
                       const int32_t* n,
                       const real8_t* A,
                       const int32_t* lda,
                       const real8_t* S,
                       const real8_t* U,
                       const int32_t* ldu,
                       const real8_t* Vt,
                       const int32_t* ldvt,
                       const real8_t* work,
                       const int32_t* lwork,
                       const int32_t* info );

  // -------------------------------------------------------------------------------------
  // DGESDD - compute the singular value decomposition of a general rectangular matrix.
  // -------------------------------------------------------------------------------------

  extern void dgesdd_( const char*    jobz,
                       const int32_t* m,
                       const int32_t* n,
                       const real8_t* A,
                       const int32_t* lda,
                       const real8_t* S,
                       const real8_t* U,
                       const int32_t* ldu,
                       const real8_t* Vt,
                       const int32_t* ldvt,
                       const real8_t* work,
                       const int32_t* lwork,
                       const int32_t* iwork,
                       const int32_t* info );

  // -------------------------------------------------------------------------------------
  // ILAENV - called from the LAPACK routines to choose problem-dependent parameters
  //          for the local environment
  // -------------------------------------------------------------------------------------
  
  extern int32_t ilaenv_( const int32_t* ispec,
                          const char*    name,
                          const char*    opts,
                          const int32_t* n1,
                          const int32_t* n2,
                          const int32_t* n3,
                          const int32_t* n4 );

  // -------------------------------------------------------------------------------------
  // DGEEV - compute for an N-by-N real nonsymmetric matrix A, the eigenvalues and,
  //         optionally, the left and/or right eigenvectors
  // -------------------------------------------------------------------------------------
  extern int dgeev_( const char    *jobvl,
                     const char    *jobvr,
                     const int32_t *n,
		     const real8_t *a,
                     const int32_t *lda,
                     const real8_t *wr,
                     const real8_t *wi,
		     const real8_t *vl,
                     const int32_t *ldvl,
                     const real8_t *vr,
                     const int32_t *ldvr,
		     const real8_t *work,
                     const int32_t *lwork,
                     const int32_t *info );

  // -------------------------------------------------------------------------------------
  // DSYEV - compute all eigenvalues and, optionally, eigenvectors of a real
  //         symmetric matrix A
  // -------------------------------------------------------------------------------------
  extern int dsyev_( const char    *jobz,
                     const char    *uplo,
                     const int32_t *n,
		     const real8_t *a,
                     const int32_t *lda,
                     const real8_t *w,
		     const real8_t *work,
                     const int32_t *lwork,
                     const int32_t *info );
  
} // end extern "C"


#endif


// =======================================================================================
// **                          L A P A C K _ I N T E R F A C E                          **
// ======================================================================== END FILE =====
