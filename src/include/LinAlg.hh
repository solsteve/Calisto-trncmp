// ====================================================================== BEGIN FILE =====
// **                                    L I N A L G                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief  Linear algebra functions.
 *  @file   LinAlg.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-23
 *
 *  Provides the interface for linear algebra functions.
 */
// =======================================================================================

#ifndef __HH_LINALG_TRNCMP
#define __HH_LINALG_TRNCMP

#include <Vector.hh>
#include <Matrix.hh>

void    getRow  ( Vector& v, Matrix& M, int32_t ridx );
void    setRow  ( Matrix& M, Vector& v, int32_t ridx );

void    getCol  ( Vector& v, Matrix& M, int32_t cidx );
void    setCol  ( Matrix& M, Vector& v, int32_t cidx );

void    getDiag ( Vector& v, Matrix& M );
void    setDiag ( Matrix& M, Vector& v );

void    dot     ( Vector& a, Vector& v, Matrix& M );
void    dot     ( Vector& a, Matrix& M, Vector& v );

void    dotAdd  ( Vector& a, Vector& v, Matrix& M, Vector& b );
void    dotAdd  ( Vector& a, Matrix& M, Vector& v, Vector& b );

void    outer   ( Matrix& M, Vector& col, Vector& row );

real8_t vMv     ( Vector& a, Matrix& M );
real8_t vMv     ( Vector& row, Matrix& M,  Vector& col );
real8_t vMv     ( Vector& a, Vector& mu, Matrix& S );

#endif


// =======================================================================================
// **                                    L I N A L G                                    **
// ======================================================================== END FILE =====
