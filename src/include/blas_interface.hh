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
 */
// =======================================================================================


#ifndef __HH_BLAS_INTERFACE_TRNCMP
#define __HH_BLAS_INTERFACE_TRNCMP


#include <trncmp.hh>


// =======================================================================================
extern "C" {
  // -------------------------------------------------------------------------------------
  extern void dcopy_(
  const int32_t* n,
  const real8_t* dx,
  const int32_t* incx,
  const real8_t* dy,
  const int32_t* incy );

  // -------------------------------------------------------------------------------------
  extern void dswap_(
  const int32_t* n,
  const real8_t* dx,
  const int32_t* incx,
  const real8_t* dy,
  const int32_t* incy );

  // -------------------------------------------------------------------------------------
  extern void dscal_(
  const int32_t* n,
  const real8_t* da,
  const real8_t* dx,
  const int32_t* incx );
} // end extern C


#endif


// =======================================================================================
// **                            B L A S _ I N T E R F A C E                            **
// ======================================================================== END FILE =====
