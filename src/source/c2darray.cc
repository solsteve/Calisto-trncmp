// ====================================================================== BEGIN FILE =====
// **                                  C 2 D A R R A Y                                  **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2002-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
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

#include <c2darray.hh>

namespace C2DArray {

// =======================================================================================
/** @brief construct 2D array.
 *  @param n_row number of rows.
 *  @param n_col number of cols.
 *  @return pointer to a row address array.
 *
 *  Construct the allocation for a two dimensional array.
 */
// ---------------------------------------------------------------------------------------
real8_t** build( const size_t n_row, const size_t n_col ) {
  // -------------------------------------------------------------------------------------
  real8_t*  buffer = new real8_t[ n_col * n_row ];
  real8_t** row    = new real8_t*[ n_row ];
  real8_t*  ptr    = buffer;
  for ( size_t i=0; i<n_row; i++ ) {
    row[i] = ptr;
    ptr += n_col;
  }
  return row;
}


// =======================================================================================
/** @brief destruct.
 *  @param array pointer to a 2D array.
 *
 *  Deallocate a 2D array.
 */
// ---------------------------------------------------------------------------------------
void del( real8_t** array ) {
  // -------------------------------------------------------------------------------------
  real8_t* buffer = array[0];
  array[0] = (real8_t*)0;
  delete array;
  delete buffer;
}


// =======================================================================================
/** @brief Reshape.
 *  @param n_row  number of rows.
 *  @param n_col  number of cols.
 *  @param vector pointer to a one dimensional array.
 *  @return pointer to a two dimensional array copy of vector.
 *
 *  Use the pointer to vector as a source.
 */
// ---------------------------------------------------------------------------------------
real8_t** reshape( const size_t n_row, const size_t n_col, real8_t* vector ) {
  // -------------------------------------------------------------------------------------
  real8_t** temp = build( n_row, n_col );
  size_t n = n_row * n_col;
  real8_t* buffer = temp[0];
  for ( size_t i=0; i<n; i++ ) {
    buffer[i] = vector[i];
  }
}


// =======================================================================================
/** @brief Reshape.
 *  @param n_row  number of rows.
 *  @param n_col  number of cols.
 *  @param array pointer to an array of arrays.
 *  @return pointer to a two dimensional array copy of vector.
 *
 *  Use the pointer to the array of arrays.
 */
// ---------------------------------------------------------------------------------------
real8_t** reshape( const size_t n_row, const size_t n_col, real8_t* array[] ) {
  // -------------------------------------------------------------------------------------
  real8_t** temp = build( n_row, n_col );
  for ( size_t r=0; r<n_row; r++ ) {
    for ( size_t c=0; c<n_col; c++ ) {
      (temp[r])[c] = (array[r])[c];
    }
  }
}


}; // end namespace C2DArray

// =======================================================================================
// **                                 A R R A Y F U N C                                 **
// ======================================================================== END FILE =====
