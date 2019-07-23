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


#include <array_print.hh>
#include <blas_interface.hh>
#include <lapack_interface.hh>
#include <TLogger.hh>

// =======================================================================================
class Matrix {
  // -------------------------------------------------------------------------------------
 protected:

  real8_t* data; ///< Storage buffer
  int32_t  nrow; ///< Number or rows        (visible).
  int32_t  ncol; ///< Number of columns     (actual).
  int32_t  lda;  ///< Number of stored rows (actual).
  int32_t  nbuf; ///< Allocated space;

  void destroy ( void );
  void resize  ( const int32_t nr, const int32_t nc, const int32_t ld );

  // -------------------------------------------------------------------------------------
 public:
  void debug( void );

  typedef enum {ROW_MAJOR, COLUMN_MAJOR,
                UPPER_TRIANGLE, LOWER_TRIANGLE,
                DIAGONAL, IDENTITY } matrix_format_e;

  Matrix  ( void );
  Matrix  ( const int32_t n,                                      const bool init=false );
  Matrix  ( const int32_t nr, const int32_t nc,                   const bool init=false );
  Matrix  ( const int32_t nr, const int32_t nc, const int32_t ld, const bool init=false );
  Matrix  ( const Matrix& M,  const bool clone=false );

  static  Matrix zero           ( const int32_t n );
  static  Matrix identity       ( const int32_t n );
  static  Matrix diagonal       ( const int32_t n,                    const real8_t* src );
  static  Matrix row_major      ( const int32_t n,                    const real8_t* src );
  static  Matrix column_major   ( const int32_t n,                    const real8_t* src );
  static  Matrix upper_triangle ( const int32_t n,                    const real8_t* src );
  static  Matrix lower_triangle ( const int32_t n,                    const real8_t* src );

  static  Matrix zero           ( const int32_t nr, const int32_t nc );
  static  Matrix identity       ( const int32_t nr, const int32_t nc );
  static  Matrix diagonal       ( const int32_t nr, const int32_t nc, const real8_t* src );
  static  Matrix row_major      ( const int32_t nr, const int32_t nc, const real8_t* src );
  static  Matrix column_major   ( const int32_t nr, const int32_t nc, const real8_t* src );

  ~Matrix ( void );

  void resize  ( const int32_t n )                    { resize(n,n,n); }
  void resize  ( const int32_t nr, const int32_t nc ) { resize(nr,nc,nr); }

  void     set            ( const real8_t v=D_ZERO );
  bool     equals         ( const Matrix& M, const real8_t eps   = D_EPSILON );
  void     copy           ( const Matrix& M, const bool    clone = false );

  real8_t* load           ( const real8_t* src, matrix_format_e fmt = COLUMN_MAJOR );
  real8_t* store          ( const real8_t* dst, matrix_format_e fmt = COLUMN_MAJOR );

  real8_t& at             ( const int32_t r, const int32_t c );
  real8_t& operator()     ( const int32_t r, const int32_t c );
  Matrix&  operator=      ( const Matrix& rhs );

  int32_t  size           ( const int dim=0 );
  bool     isSquare       ( void );

  void     T              ( const Matrix& M );
  real8_t  det            ( void );
  real8_t  inverse        ( const Matrix& M );

  real8_t  sum            ( void );
  real8_t  sumsq          ( void );
  real8_t  sumsq          ( const Matrix& that );
  
  void     dot            ( const Matrix& lhs, const Matrix& rhs );
  
  // ----- inplace element operations -------------------------------------

  void     add            ( const real8_t s );
  void     add            ( const Matrix& M );
  void     add            ( const real8_t s,   const Matrix& M );
  void     add            ( const Matrix& M,   const real8_t s );
  void     add            ( const Matrix& lhs, const Matrix& rhs );

  void     sub            ( const real8_t s );
  void     sub            ( const Matrix& M );
  void     sub            ( const real8_t s,   const Matrix& M );
  void     sub            ( const Matrix& M,   const real8_t s );
  void     sub            ( const Matrix& lhs, const Matrix& rhs );

  void     mul            ( const real8_t s );
  void     mul            ( const Matrix& M );
  void     mul            ( const real8_t s,   const Matrix& M );
  void     mul            ( const Matrix& M,   const real8_t s );
  void     mul            ( const Matrix& lhs, const Matrix& rhs );

  void     div            ( const real8_t s );
  void     div            ( const Matrix& M );
  void     div            ( const real8_t s,   const Matrix& M );
  void     div            ( const Matrix& M,   const real8_t s );
  void     div            ( const Matrix& lhs, const Matrix& rhs );


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

int32_t size     ( const Matrix& M, int dim=0 );

std::string   toString ( const Matrix&      M,
			 const std::string& sfmt = DEFAULT_PRINT_FORMAT,
			 const std::string& cdel = DEFAULT_PRINT_COL_DELIM,
			 const std::string& rdel = DEFAULT_PRINT_ROW_DELIM );

std::string   toString ( const std::string& prefix,
			 const Matrix&      M,
			 const std::string& suffix,
			 const std::string& sfmt = DEFAULT_PRINT_FORMAT,
			 const std::string& cdel = DEFAULT_PRINT_COL_DELIM,
			 const std::string& rdel = DEFAULT_PRINT_ROW_DELIM );

/** TODO: Add more forward references */



// =======================================================================================
/** @brief Assignment.
 *  @param[in] rhs reference to a source Matrix.
 *  @return reference to this Matrix.
 *
 *  Copy all of the elements of the source rhs. Resize if necessary this Matrix.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix& Matrix::operator= ( const Matrix& rhs ) {
  // -------------------------------------------------------------------------------------
  //logger->info( "v----- Matrix::operator= -----v" );
  copy( rhs );
  //logger->info( "^----- Matrix::operator= -----^" );
  return *this;
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
inline  int32_t size( const Matrix& M, const int dim ) {
  // -------------------------------------------------------------------------------------
  return const_cast<Matrix&>(M).size(dim);
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
inline  std::string toNumpy( const std::string& lab, const Matrix& M,
                             const std::string& sfmt = DEFAULT_PRINT_FORMAT ) {
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
inline  std::string toOctave( const std::string& lab, const Matrix& M,
                              const std::string& sfmt = DEFAULT_PRINT_FORMAT ) {
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
inline  std::string toSage( const std::string& lab, const Matrix& M,
                            const std::string& sfmt = DEFAULT_PRINT_FORMAT ) {
  // -------------------------------------------------------------------------------------
  std::string prefix = lab + " = Matrix(QQ,[[";
  return toString( prefix,M,"]])",sfmt,",","],\n[" );
}








// =======================================================================================
/** @brief Zero.
 *  @param[in] n order of the square Matrix.
 *  @return instance of a Matrix.
 *
 *  Construct an n by n Matrix and fill with zeros.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::zero( const int32_t n ) {
  // -------------------------------------------------------------------------------------
  return Matrix(n,true);;
}


// =======================================================================================
/** @brief Identity.
 *  @param[in] n order of the square Matrix.
 *  @return instance of a Matrix.
 *
 *  Construct an n by n Matrix with one's on the diagonal and zero everywhere else.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::identity( const int32_t n ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(n,n,false);
  for ( int32_t r=0; r<n; r++ ) {
    for ( int32_t c=0; c<n; c++ ) {
      temp.at(r,c) = ((r==c) ? (D_ONE) : (D_ZERO));
    }
  }

  return temp;
}

// =======================================================================================
/** @brief Set Diagonal.
 *  @param[in] n   order of the square Matrix.
 *  @param[in] src pointer to a source of data.
 *  @return instance of a Matrix.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline Matrix Matrix::diagonal( const int32_t n, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(n, n, false );
  temp.load( src, DIAGONAL );
  return temp;
}


// =======================================================================================
/** @brief Set Matrix.
 *  @param[in] n   order of the square Matrix.
 *  @param[in] src pointer to a source of data.
 *  @return instance of a Matrix.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::column_major( const int32_t n, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(n, n, false );
  temp.load( src, COLUMN_MAJOR );
  return temp;
}

// =======================================================================================
/** @brief Set Matrix.
 *  @param[in] n   order of the square Matrix.
 *  @param[in] src pointer to a source of data.
 *  @return instance of a Matrix.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::row_major( const int32_t n, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(n, n, false );
  temp.load( src, ROW_MAJOR );
  return temp;
}


// =======================================================================================
/** @brief Set Upper Triangle.
 *  @param[in] n   order of the square Matrix.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline Matrix Matrix::upper_triangle( const int32_t n, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(n, n, false );
  temp.load( src, UPPER_TRIANGLE );
  return temp;
}


// =======================================================================================
/** @brief Set Lower Triangle.
 *  @param[in] n   order of the square Matrix.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline Matrix Matrix::lower_triangle( const int32_t n, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(n, n, false );
  temp.load( src, LOWER_TRIANGLE );
  return temp;
}










// =======================================================================================
/** @brief Zero.
 *  @param[in] nr number of rows.
 *  @param[in] nc number of columns.
 *  @return instance of a Matrix.
 *
 *  Construct an nr by nc Matrix and fill with zeros.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::zero( const int32_t nr, const int32_t nc ) {
  // -------------------------------------------------------------------------------------
  return Matrix(nr,nc,true);
}


// =======================================================================================
/** @brief Identity.
 *  @param[in] nr number of rows.
 *  @param[in] nc number of columns.
 *  @return instance of a Matrix.
 *
 *  Construct an nr by nc Matrix with one's on the diagonal and zero everywhere else.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::identity( const int32_t nr, const int32_t nc ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(nr,nc,false);
  for ( int32_t r=0; r<nr; r++ ) {
    for ( int32_t c=0; c<nc; c++ ) {
      temp.at(r,c) = ((r==c) ? (D_ONE) : (D_ZERO));
    }
  }

  return temp;
}


// =======================================================================================
/** @brief Set Diagonal.
 *  @param[in] nr  number of rows.
 *  @param[in] nc  number of columns.
 *  @param[in] src pointer to a source of data.
 *  @return instance of a Matrix.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::diagonal( const int32_t nr, const int32_t nc, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(nr, nc, false );
  temp.load( src, DIAGONAL );
  return temp;
}


// =======================================================================================
/** @brief Set Matrix.
 *  @param[in] nr  number of rows.
 *  @param[in] nc  number of columns.
 *  @param[in] src pointer to a source of data.
 *  @return instance of a Matrix.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::column_major( const int32_t nr, const int32_t nc, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(nr, nc, false );
  temp.load( src, COLUMN_MAJOR );
  return temp;
}

// =======================================================================================
/** @brief Set Matrix.
 *  @param[in] nr  number of rows.
 *  @param[in] nc  number of columns.
 *  @param[in] src pointer to a source of data.
 *  @return instance of a Matrix.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
inline  Matrix Matrix::row_major( const int32_t nr, const int32_t nc, const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  Matrix temp(nr, nc, false );
  temp.load( src, ROW_MAJOR );
  return temp;
}


#endif

// =======================================================================================
// **                                    M A T R I X                                    **
// ======================================================================== END FILE =====

