// ====================================================================== BEGIN FILE =====
// **                                  C 2 D A R R A Y                                  **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2020, Stephen W. Soliday                                           **
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
/** @brief  Two dimensional array
 *  @file   c2darray.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Dec-24
 */
// =======================================================================================


#ifndef __HH_C2DARRAY_TRNCMP
#define __HH_C2DARRAY_TRNCMP

#include <trncmp.hh>

namespace C2DArray {
real8_t**  build    ( const size_t n_row, const size_t n_col );
void       del      ( real8_t** array );
real8_t**  reshape  ( const size_t n_row, const size_t n_col, real8_t* vector );
real8_t**  reshape  ( const size_t n_row, const size_t n_col, real8_t* array[] );
}; // end namespace C2DArray


#endif


// =======================================================================================
// **                                  C 2 D A R R A Y                                  **
// ======================================================================== END FILE =====
