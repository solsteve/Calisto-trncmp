// ====================================================================== BEGIN FILE =====
// **                                   V A R R E A L                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
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
//
/** @brief  Variable row length array.
 *  @file   VarReal.cc
 *  @author Stephen W. Soliday
 *  @date   2015-Feb-09 Original release.
 *  @date   2019-Sep-01 CMake refactorization.
 *
 *  Provides the methods for a templated 2-D array with variable row length.
 */
// =======================================================================================


#include <VarReal.hh>

#define INIT_VAR(_a)  n_buf(_a), n_row(_a), n_col(_a), data(_a), rowptr(_a)


// =======================================================================================
/** @brief Destroy.
 *
 *  Remove internal allocation.
 */
// ---------------------------------------------------------------------------------------
void VarReal::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) != data ) {
    for ( int32_t r=0; r<n_row; r++ ) {
      rowptr[r] = static_cast<real8_t*>(0);
      n_col[r]  = 0;
    }
    delete[] rowptr;
    delete[] n_col;
    delete[] data;
    data   = static_cast<real8_t*>(0);
    rowptr = static_cast<real8_t**>(0);
    n_col  = static_cast<int32_t*>(0);
    n_buf  = 0;
    n_row  = 0;
  }
}


// =======================================================================================
/** @brief resize.
 *  @param[in] nr number of rows.
 *  @param[in] nc number of columns.
 */
// ---------------------------------------------------------------------------------------
void VarReal::resize( const int32_t nr, const int32_t* nc ) {
  // -------------------------------------------------------------------------------------
  destroy();

  n_row = nr;
  n_buf = 0;
  n_col = new int32_t[n_row];
  for ( int32_t r=0; r<n_row; r++) {
    n_col[r] = nc[r];
    n_buf   += nc[r];
  }

  data   = new real8_t[ n_buf ];
  rowptr = new real8_t*[ n_row ];

  real8_t* ptr = data;

  for ( int32_t r=0; r<n_row; r++ ) {
    rowptr[r] = ptr;
    ptr       = ( ptr + n_col[r] );
  }
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
VarReal::VarReal( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nr  number of rows.
 *  @param[in] nc  number of columns.
 */
// ---------------------------------------------------------------------------------------
VarReal::VarReal( const int32_t nr, const int32_t* nc ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  resize( nr, nc );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nr  number of rows.
 *  @param[in] nc  number of columns.
 *  @param[in] src optional pointer to a data source.
 */
// ---------------------------------------------------------------------------------------
VarReal::VarReal( const int32_t nr, const int32_t* nc, real8_t* src ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  resize( nr, nc );
  load( src );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
VarReal::~VarReal( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Size.
 *  @return total number of elements.
 */
// ---------------------------------------------------------------------------------------
int32_t VarReal::size( void ) const {
  // -------------------------------------------------------------------------------------
  return n_buf;
}


// =======================================================================================
/** @brief Number of rows.
 *  @return total number of rows.
 */
// ---------------------------------------------------------------------------------------
int32_t VarReal::nRow( void ) const {
  // -------------------------------------------------------------------------------------
  return n_row;
}


// =======================================================================================
/** @brief Number of coluns.
 *  @return total number of columns in a given row.
 */
// ---------------------------------------------------------------------------------------
int32_t VarReal::nCol( const int32_t r ) const {
  // -------------------------------------------------------------------------------------
  return (0 == n_row) ? (0) : (n_col[r]);
}


// =======================================================================================
/** @brief Get.
 *  @param[in] r row index.
 *  @param[in] c column index.
 *  @return value of the element indexed by (r,c)
 */
// ---------------------------------------------------------------------------------------
real8_t VarReal::get( const int32_t r, const int32_t c ) const {
  // -------------------------------------------------------------------------------------
  return (rowptr[r])[c];
}


// =======================================================================================
/** @brief Set.
 *  @param[in] r   row    index.
 *  @param[in] c   column index.
 *  @param[in] val value
 */
// ---------------------------------------------------------------------------------------
void VarReal::set( const int32_t r, const int32_t c, const real8_t val ) {
  // -------------------------------------------------------------------------------------
  (rowptr[r])[c] = val;
}


// =======================================================================================
/** @brief Reference.
 *  @param[in] r row index.
 *  @param[in] c column index.
 *  @return reference to the element indexed by (r,c)
 */
// ---------------------------------------------------------------------------------------
real8_t& VarReal::operator()( const int32_t r, const int32_t c ) {
  // -------------------------------------------------------------------------------------
  return (rowptr[r])[c];
}


// =======================================================================================
/** @brief Get Row.
 *  @param[in] r row index.
 *  @return pointer to begining of row.
 */
// ---------------------------------------------------------------------------------------
real8_t* VarReal::operator()( const int32_t r ) {
  // -------------------------------------------------------------------------------------
  return rowptr[r];
}


// =======================================================================================
/** @brief Store.
 *  @param[in] src pointer to an array of type T.
 *  @return return a pointer to the next available element of src.
 *
 *  Store the contents of this VarArray into a buffer provided by src. This copy is
 *  performed in row order.
 */
// ---------------------------------------------------------------------------------------
real8_t* VarReal::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n_buf; i++ ) {
    data[i] = src[i];
  }
  return (src+n_buf);
}


// =======================================================================================
/** @brief Store.
 *  @param[in] src pointer to an array of type T.
 *  @return return a pointer to the next available element of src.
 *
 *  Store the contents of this VarArray into a buffer provided by src. This copy is
 *  performed in row order.
 */
// ---------------------------------------------------------------------------------------
real8_t* VarReal::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n_buf; i++ ) {
    dst[i] = data[i];
  }
  return (dst+n_buf);
}

// =======================================================================================
// **                                   V A R R E A L                                   **
// ======================================================================== END FILE =====
