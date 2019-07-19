// ====================================================================== BEGIN FILE =====
// **                                    M A T R I X                                    **
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
/** @brief  BLAS & LAPACK Compatable Matrix.
 *  @file   Matrix.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-15
 *  Provides the interface for a BLAS and LAPACK Compatable Matrix.
 *
 *  \verbatim
 *  Given:
 *     m   = 4
 *     n   = 3
 *     lda = 6
 *  
 *  The following Matrix
 *     1.1, 1.2, 1.3
 *     2.1, 2.2, 2.3
 *     3.1, 3.2, 3.3
 *     4.1, 4.2, 4.3
 *     xxx, xxx, xxx
 *     xxx, xxx, xxx
 *  would be stored in memory as:
 *     1.1 | 2.1 | 3.1 | 4.1 | xxx | xxx | 1.2 | 2.2 | 3.2 | 4.2 | xxx | xxx | ...
 *    ... 1.3 | 2.3 | 3.3 | 4.3 | xxx | xxx |
 *  \endverbatim
 *
 * This represents FORTRAN's column-major layout. This is for full compatability with
 * LAPACK.
 */
// =======================================================================================

#ifndef __HH_MATRIX_TRNCMP
#define __HH_MATRIX_TRNCMP


#include <blas_interface.hh>
#include <array_print.hh>
#include <TLogger.hh>

// =======================================================================================
class Matrix {
  // -------------------------------------------------------------------------------------
 protected:

  TLOGGER_HEADER(logger); ///< reference to logger instance

  real8_t* data; ///< Storage buffer
  int32_t  nrow; ///< Number or rows        (visible).
  int32_t  ncol; ///< Number of columns     (actual).
  int32_t  lda;  ///< Number of stored rows (actual).
  int32_t  nbuf; ///< Allocated space;

  void destroy ( void );
  void resize  ( const int32_t nr, const int32_t nc, const int32_t ld );

  // -------------------------------------------------------------------------------------
 public:

  typedef enum {ROW_MAJOR, COLUMN_MAJOR,
                UPPER_TRIANGLE, LOWER_TRIANGLE,
                DIAGONAL, IDENTITY } matrix_format_e;

  Matrix  ( void );
  Matrix  ( const int32_t n,                                      bool init=false );
  Matrix  ( const int32_t nr, const int32_t nc,                   bool init=false );
  Matrix  ( const int32_t nr, const int32_t nc, const int32_t ld, bool init=false );
  Matrix  ( Matrix& M, const bool clone=false );

  ~Matrix ( void );

  void     set            ( const real8_t v=D_ZERO );
  bool     equals         ( Matrix& M );
  void     copy           ( Matrix& M, const bool clone=false );

  void     row_major      ( const real8_t* src );
  void     column_major   ( const real8_t* src );
  void     diagonal       ( const real8_t* src );
  void     upper_triangle ( const real8_t* src );
  void     lower_triangle ( const real8_t* src );
  void     identity       ( void );

  real8_t* load           ( const real8_t* src, matrix_format_e fmt = COLUMN_MAJOR );
  real8_t* store          ( const real8_t* dst, matrix_format_e fmt = COLUMN_MAJOR );

  real8_t& at             ( const int32_t r, const int32_t c );
  real8_t& operator()     ( const int32_t r, const int32_t c );
  void     operator=      ( const Matrix& M );
  
  int32_t  size           ( const int dim=0 );
  bool     isSquare       ( void );

  void     debug          ( void );

  // ----- for BLAS & LAPACK FORTRAN interface -------------------------------------------
 public:
  /** @brief Data Buffer. @return pointer to data buffer. */
  real8_t* A   (void) { return data;  };

  /** @brief Number of Rows. @return pointer to number of rows. */
  int32_t* M   (void) { return &nrow; };

  /** @brief Number of Columns. @return pointer to number of columns */
  int32_t* N   (void) { return &ncol; };

  /** @brief Leading Dimension. @return pointer to the leading dimension. */
  int32_t* LDA (void) { return &lda;  };

}; // end class Matrix

// =======================================================================================

int32_t       size     ( Matrix& M, int dim=0 );

std::string   toString ( Matrix& M,
			 std::string sfmt = DEFAULT_PRINT_FORMAT,
			 std::string cdel = DEFAULT_PRINT_COL_DELIM,
			 std::string rdel = DEFAULT_PRINT_ROW_DELIM );

std::string   toString ( std::string prefix, Matrix& M, std::string suffix,
			 std::string sfmt = DEFAULT_PRINT_FORMAT,
			 std::string cdel = DEFAULT_PRINT_COL_DELIM,
			 std::string rdel = DEFAULT_PRINT_ROW_DELIM );


// =======================================================================================
/** @brief Access.
 *  @param[in] r row    index.
 *  @param[in] c column index.
 *  @return reference to the element at (r,c).
 *
 *  Access the element at (r,c).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t&  Matrix::at( const int32_t r, const int32_t c ) {
  // -------------------------------------------------------------------------------------
  return *(data + r + c*lda);
}


// =======================================================================================
/** @brief Access.
 *  @param[in] r row    index.
 *  @param[in] c column index.
 *  @return reference to the element at (r,c).
 *
 *  Access the element at (r,c).
 */
// ---------------------------------------------------------------------------------------
inline  real8_t&  Matrix::operator() ( const int32_t r, const int32_t c ) {
  // -------------------------------------------------------------------------------------
  return *(data + r + c*lda);
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
inline  bool Matrix::isSquare( void ) {
  // -------------------------------------------------------------------------------------
  return ( nrow==ncol);
}

// =======================================================================================
/** @brief Size.
 *  @param[in] dim dimension (default:0)
 *  @return number of rows dim=0, or number of columns dim=1
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Matrix::size( const int dim ) {
  // -------------------------------------------------------------------------------------
  return ((0 == (dim%2)) ? (nrow) : (ncol));
}


// =======================================================================================
/** @brief Size.
 *  @param[in] M   reference to a Matrix.
 *  @param[in] dim dimension (default:0)
 *  @return number of rows dim=0, or number of columns dim=1
 */
// ---------------------------------------------------------------------------------------
inline  int32_t size( Matrix& M, const int dim ) {
  // -------------------------------------------------------------------------------------
  return M.size(dim);
}


// =======================================================================================
/** @brief To String.
 *  @param[in] lab  label.
 *  @param[in] M    reference to a Matrix.
 *  @param[in] sfmt printf style format.
 *
 *  Format this Matrix for printing so that is is compatable with Numpy.
 */
// ---------------------------------------------------------------------------------------
inline  std::string toNumpy( std::string lab, Matrix& M,
                             std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string prefix = lab + "=np.matrix( [[";
  return toString( prefix,M,"]])",sfmt,",","],[" );
}


// =======================================================================================
/** @brief To String.
 *  @param[in] lab  label.
 *  @param[in] M    reference to a Matrix.
 *  @param[in] sfmt printf style format.
 *
 *  Format this Matrix for printing so that is is compatable with Octave/Matlab.
 */
// ---------------------------------------------------------------------------------------
inline  std::string toOctave( std::string lab, Matrix& M,
                              std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string prefix = lab + " = [";
  return toString( prefix,M,"];",sfmt,",",";" );
}


// =======================================================================================
/** @brief To String.
 *  @param[in] lab  label.
 *  @param[in] M    reference to a Matrix.
 *  @param[in] sfmt printf style format.
 *
 *  Format this Matrix for printing so that is is compatable with Sage.
 */
// ---------------------------------------------------------------------------------------
inline  std::string toSage( std::string lab, Matrix& M,
                            std::string sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string prefix = lab + " = Matrix(QQ,[[";
  return toString( prefix,M,"]])",sfmt,",","],\n[" );
}




#endif

// =======================================================================================
// **                                    M A T R I X                                    **
// ======================================================================== END FILE =====

