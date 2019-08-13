// ====================================================================== BEGIN FILE =====
// **                                     T A B L E                                     **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1993-2019, Stephen W. Soliday                                      **
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
/** @brief  Table (2D Array)
 *  @file   Table.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-26 CMake refactorization.
 *
 *  Provides the interface for a 2D Table
 *  @see Statistics, Covariance, and PCA
 */
// =======================================================================================

#ifndef __HH_TABLE_TRNCMP
#define __HH_TABLE_TRNCMP

#include <TLogger.hh>

// =======================================================================================
class Table {
  // -------------------------------------------------------------------------------------
 protected:
  real8_t* data;    ///< pointer to the table data
  int32_t  nsamp;   ///< number of samples
  int32_t  nvar;    ///< number of variables
  int32_t  nalloc;  /// < max allocation (@see: Resize)

  TLOGGER_HEADER( logger );

  void destroy( void );
  
  // -------------------------------------------------------------------------------------
 public:
  Table   ( void );
  Table   ( const int32_t ns, const int32_t nv );
  Table   ( const Table& tab );
  Table   ( const std::string fspc );
  ~Table  ( void );

  void     resize       ( const int32_t ns, const int32_t nv );
  void     set          ( const real8_t value = D_ZERO );
  void     copy         ( const Table& tab );

  int32_t  size         ( const int dim=0 ) const;

  real8_t& at           ( const int32_t sidx, const int32_t vidx );
  real8_t  get          ( const int32_t sidx, const int32_t vidx ) const;
  real8_t& operator()   ( const int32_t sidx, const int32_t vidx );
  Table&   operator=    ( const Table& tab );

  void     row          ( real8_t* row, const int32_t sidx );
  real8_t* col          ( const int32_t vidx );

  bool     read_ascii   ( std::istream& inf );
  bool     write_ascii  ( std::ostream& outf, const std::string sfmt="%23.16e" );
  bool     write_ascii  ( std::ostream& outf, const int32_t start, const int32_t finis,
                          const std::string sfmt="%23.16e" );
  
  bool     read_ascii   ( const std::string fspc );
  bool     write_ascii  ( const std::string fspc, const std::string sfmt="%23.16e" );
  
  int      sum          ( real8_t* s, const int32_t n, const int axis=0 ) const;
  int      mean         ( real8_t* s, const int32_t n, const int axis=0 ) const;
  
}; // end class Table

int32_t size( const Table& tab, const int dim=0 );

// =======================================================================================
/** @brief Access.
 *  @param[in] sidx index for the sample (row)
 *  @param[in] vidx index of variable    (col)
 *  @return reference to the element varaible v in sample s.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Table::get( const int32_t sidx, const int32_t vidx ) const {
  // -------------------------------------------------------------------------------------
  return data[sidx + vidx*nsamp];
}


// =======================================================================================
/** @brief Access.
 *  @param[in] sidx index for the sample (row)
 *  @param[in] vidx index of variable    (col)
 *  @return reference to the element varaible v in sample s.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t& Table::at( const int32_t sidx, const int32_t vidx ) {
  // -------------------------------------------------------------------------------------
  return data[sidx + vidx*nsamp];
}


// =======================================================================================
/** @brief Access.
 *  @param[in] sidx index for the sample (row)
 *  @param[in] vidx index of variable    (col)
 *  @return reference to the element varaible v in sample s.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t& Table::operator()( const int32_t sidx, const int32_t vidx ) {
  // -------------------------------------------------------------------------------------
  return data[sidx + vidx*nsamp];
}


// =======================================================================================
/** @brief Size.
 *  @param[in] dim dimension to return 0=number of samples, 1=number of variables.
 *  @return number of samples if dim==0, otherwise, number of variables.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Table::size( const int dim ) const {
  // -------------------------------------------------------------------------------------
  return ( (0==dim) ? (nsamp) : (nvar) );
}


// =======================================================================================
/** @brief Column.
 *  @param[in] vidx vaiable index (column)
 *  @return pointer to the start of the column.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Table::col( const int32_t vidx ) {
  // -------------------------------------------------------------------------------------
  return (data + vidx*nsamp);
}

// =======================================================================================
/** @brief Copy.
 *  @param[in] tab reference to a source Table.
 *
 *  Copy the contents of the source Table tab into this Table.
 */
// ---------------------------------------------------------------------------------------
inline  Table& Table::operator=( const Table& tab ) {
  // -------------------------------------------------------------------------------------
  copy( tab );
  return *this;
}


// =======================================================================================
/** @brief Size.
 *  @param[in] tab reference to a tble.
 *  @param[in] dim dimension to return 0=number of samples, 1=number of variables.
 *  @return number of samples if dim==0, otherwise, number of variables.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t size( const Table& tab, const int dim ) {
  // -------------------------------------------------------------------------------------
  return tab.size( dim );
}


#endif


// =======================================================================================
// **                                     T A B L E                                     **
// ======================================================================== END FILE =====
