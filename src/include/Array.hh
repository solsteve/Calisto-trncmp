// ====================================================================== BEGIN FILE =====
// **                                     A R R A Y                                     **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2010-2019, Stephen W. Soliday                                      **
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
/** @brief  Back Propagation Neural Network.
 *  @file   BPN.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-01.
 *
 *  Provides the interface for a vector implementation of a BLAS enabled
 *  back-propagation neural network.
 */
// =======================================================================================


#ifndef __HH_ARRAY_TRNCMP
#define __HH_ARRAY_TRNCMP

#include <trncmp.hh>

// =======================================================================================
template<class T>
class Array {
  // -------------------------------------------------------------------------------------
 protected:
  int32_t n_row;
  int32_t n_col;
  int32_t n_dat;
  T*      data;

  void destroy ( void );
  
 public:
  Array  ( void );
  Array  ( const int32_t nr, const int32_t nc, T* src = static_cast<T*>(0) );
  Array  ( const Array<T>& src );
  ~Array ( void );

  int32_t size       ( const int dim = 0 ) const;
  void    resize     ( const int32_t nr, const int32_t nc );

  Array<T>&  operator=  ( const Array<T>& src );
  void    copy       ( const Array<T>& src );

  T       get        ( const int32_t ir, const int32_t ic ) const;
  T*      get        ( const int32_t ir ) const;

  void    set        ( const T val = static_cast<T>(0) );
  void    set        ( const int32_t ir, const int32_t ic, const T val );

  T&      operator() ( const size_t ir, const size_t ic );
  T*      operator() ( const size_t ir ) const;

  T*      load       ( T* src );
  T*      store      ( T* dst );

}; // end class Array

// =======================================================================================
/** @brief Size
 *  @param[in] ary reference to an Array.
 *  @param[in] dim dimension to return ( default: number of rows )
 *  @return number of rows, if dim==0, else number of columns.
 */
// ---------------------------------------------------------------------------------------
template<class T>
int32_t size( const Array<T>& ary, const int dim = 0 ) {
  // -------------------------------------------------------------------------------------
  return ary.size(dim);
}

// =======================================================================================
/** @brief Destroy.
 *
 *  Remove internal allocation.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Array<T>::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<T*>(0) != data ) {
    delete[] data;
  }
  n_row = 0;
  n_col = 0;
  n_dat = 0;
  data  = static_cast<T*>(0);
}


// =======================================================================================
/** @brief resize.
 *  @param[in] nr number of rows.
 *  @param[in] nc number of columns.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Array<T>::resize( const int32_t nr, const int32_t nc ) {
  // -------------------------------------------------------------------------------------
  const int32_t n = nr*nc;
  if ( n != n_dat ) {
    destroy();
    data = new T[ n ];
    n_dat = n;
  }
  n_row = nr;
  n_col = nc;
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
template<class T>
Array<T>::Array( void )
    : n_row(0), n_col(0), n_dat(0), data(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nr  number of rows.
 *  @param[in] nc  number of columns.
 *  @param[in] src optional pointer to a data source.
 */
// ---------------------------------------------------------------------------------------
template<class T>
Array<T>::Array( const int32_t nr, const int32_t nc, T* src )
    : n_row(0), n_col(0), n_dat(0), data(0) {
  // -------------------------------------------------------------------------------------
  resize( nr, nc );
  if ( static_cast<T*>(0) != src ) {
    load( src );
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] src reference to a source Array.
 */
// ---------------------------------------------------------------------------------------
template<class T>
Array<T>::Array( const Array<T>& src ) : n_row(0), n_col(0), n_dat(0), data(0) {
  // -------------------------------------------------------------------------------------
  copy( src );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
template<class T>
Array<T>::~Array( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}


// =======================================================================================
/** @brief Size
 *  @param[in] dim dimension to return ( default: number of rows )
 *  @return number of rows, if dim==0, else number of columns.
 */
// ---------------------------------------------------------------------------------------
template<class T>
int32_t Array<T>::size( const int dim ) const {
  // -------------------------------------------------------------------------------------
  if ( 0 == dim ) {
    return n_row;
  }
  return n_col;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] reference to a source Array.
 *  @return reference to this Array.
 *
 *  Copy the contents of src.
 */
// ---------------------------------------------------------------------------------------
template<class T>
Array<T>& Array<T>::operator=( const Array<T>& src ) {
  // -------------------------------------------------------------------------------------
  copy( src );
  return *this;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] reference to a source Array.
 *
 *  Copy the contents of src.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Array<T>::copy( const Array<T>& src ) {
  // -------------------------------------------------------------------------------------
  resize( src.n_row, src.n_col );
  for ( int32_t i=0; i<n_dat; i++ ) {
    *(data+i) = *(src.data+i);
  }
}


// =======================================================================================
/** @brief Get.
 *  @param[in] ir row    index.
 *  @param[in] ic column index.
 *  @return value of the element indexed by ir and ic.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T Array<T>::get( const int32_t ir, const int32_t ic ) const {
  // -------------------------------------------------------------------------------------
  return *(data+ic+(ir*n_col));
}


// =======================================================================================
/** @brief Get.
 *  @param[in] ir row index.
 *  @return pointer to the row indexed by ir.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T* Array<T>::get( const int32_t ir ) const {
  // -------------------------------------------------------------------------------------
  return (data+(ir*n_col));
}


// =======================================================================================
/** @brief Set.
 *  @param[in] val value to set (default: zero).
 *
 *  Set all elements of this Array to the value of val.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Array<T>::set( const T val ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n_dat; i++ ) {
    *(data+i) = val;
  }
}


// =======================================================================================
/** @brief Set.
 *  @param[in] ir row    index.
 *  @param[in] ic column index.
 *  @param[in] val value to set.
 *
 *  Set the element indexed by ir and ic to the value of val.
 */
// ---------------------------------------------------------------------------------------
template<class T>
void Array<T>::set( const int32_t ir, const int32_t ic, const T val ) {
  // -------------------------------------------------------------------------------------
  *(data+ic+(ir*n_col)) = val;
}


// =======================================================================================
/** @brief Get.
 *  @param[in] ir row    index.
 *  @param[in] ic column index.
 *  @return refernce to the element indexed by ir and ic.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T& Array<T>::operator()( const size_t ir, const size_t ic ) {
  // -------------------------------------------------------------------------------------
  return *(data+ic+(ir*n_col));
}


// =======================================================================================
/** @brief Get.
 *  @param[in] ir row index.
 *  @return pointer to the row indexed by ir.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T* Array<T>::operator()( const size_t ir ) const {
  // -------------------------------------------------------------------------------------
  return (data+(ir*n_col));
}

// =======================================================================================
/** @brief Store.
 *  @param[in] src pointer to an array of type T.
 *  @return return a pointer to the next available element of src.
 *
 *  Store the contents of this Array into a buffer provided by src. This copy is
 *  performed in row order.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T* Array<T>::load( T* src ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n_dat; i++ ) {
    *(data+i) = *(src+i);
  }
  return (src+n_dat);
}


// =======================================================================================
/** @brief Store.
 *  @param[in] src pointer to an array of type T.
 *  @return return a pointer to the next available element of dst.
 *
 *  Store the contents of this Array into a buffer provided by dst. This copy is
 *  performed in row order.
 */
// ---------------------------------------------------------------------------------------
template<class T>
T* Array<T>::store( T* dst ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n_dat; i++ ) {
    *(dst+i) = *(data+i);
  }
  return (dst+n_dat);
}


#endif

// =======================================================================================
// **                                     A R R A Y                                     **
// ======================================================================== END FILE =====
