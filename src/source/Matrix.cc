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
 *  @file   Matrix.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-15
 *
 *  Provides the methods for a BLAS and LAPACK Compatable Matrix.
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


#include <Matrix.hh>

#define INIT_VARS(a) data(a), nrow(a), ncol(a), lda(a), nbuf(0)

TLOGGER_REFERENCE( Matrix, logger );


// =======================================================================================
// ---------------------------------------------------------------------------------------
static std::string MAT_FORM( Matrix::matrix_format_e fmt ) {
  // -------------------------------------------------------------------------------------
  switch( fmt ) {
  case Matrix::ROW_MAJOR:       return "ROW_MAJOR";
  case Matrix::COLUMN_MAJOR:    return "COLUMN_MAJOR";
  case Matrix::UPPER_TRIANGLE:  return "UPPER_TRIANGLE";
  case Matrix::LOWER_TRIANGLE:  return "LOWER_TRIANGLE";
  case Matrix::DIAGONAL:        return "DIAGONAL";
  case Matrix::IDENTITY:        return "IDENTITY";
  default:
    break;
  }
  return "UNKNOWN";
}


void Matrix::debug( void ) {
  fprintf( stdout, "[%d,%d | %d (%d)]", nrow, ncol, lda, nbuf );
  for ( int32_t i=0; i<nbuf; i++ ) {
    fprintf( stdout, " %g", data[i] );
  }
  fprintf( stdout, "\n" );
}

// =======================================================================================
/** @brief Destroy.
 *
 *  Delete allocation.
 */
// ---------------------------------------------------------------------------------------
void Matrix::destroy( void ) {
  // -------------------------------------------------------------------------------------
  if ( static_cast<real8_t*>(0) != data ) {
    delete[] data;
  } 
  data = static_cast<real8_t*>(0);
  nrow = 0;
  ncol = 0;
  lda  = 0;
}

// =======================================================================================
/** @brief Resize.
 *  @param[in] nr number of rows.
 *  @param[in] nc number of columns.
 *  @param[in] ld leading dimension.
 *
 *  Reallocate if necessary.
 */
// ---------------------------------------------------------------------------------------
void Matrix::resize( const int32_t nr, const int32_t nc, const int32_t ld ) {
  // -------------------------------------------------------------------------------------
  int32_t new_nbuf = ld*nc;
  
  if ( new_nbuf > nbuf ) {
    destroy();
    //fprintf( stdout, "allocate(%d)[%d,%d|%d]\n", new_nbuf, nr, nc, ld );
    data = new real8_t[ new_nbuf ];
    nbuf = new_nbuf;
  }
  nrow = nr;
  ncol = nc;
  lda  = ld;
}


// =======================================================================================
/** @brief Set.
 *  @param[in] v value (default 0.0).
 *
 *  Set all elements of this Matrix to the value v.
 */
// ---------------------------------------------------------------------------------------
void Matrix::set( const real8_t v ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      //std::cout << r << "|" << c << "|" << v << "\n";
      this->at(r,c) = v;
    }
  }
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] M reference to a source Matrix.
 *  @param[in] clone allocate the same unused memory as the source. (Default: false)
 *
 *  Copy all of the elements of the source M. Resize if necessary this Matrix.
 *  Optionally include the sources empty space in this allocation.
 *  @note contents of the empty space is not copied.
 */
// ---------------------------------------------------------------------------------------
void Matrix::copy( Matrix& M, const bool clone ) {
  // -------------------------------------------------------------------------------------
  if ( clone ) {
    resize( M.nrow, M.ncol, M.lda );
  } else {
    resize( M.nrow, M.ncol, M.nrow );
  }

  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      this->at(r,c) = M.at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] M reference to another Matrix.
 *  @return true if Matrices are element by element equal.
 */
// ---------------------------------------------------------------------------------------
bool Matrix::equals( Matrix& M ) {
  // -------------------------------------------------------------------------------------
  if ( nrow != M.nrow ) { return false; }
  if ( ncol != M.ncol ) { return false; }
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      const real8_t a = at(r,c);
      const real8_t b = M.at(r,c);
      if ( a < b ) { return false; }
      if ( a > b ) { return false; }
    }
  }
  return true;
}








// =======================================================================================
/** @brief Constructor.
 *
 *  Construct an empty Matrix of zero order.
 */
// ---------------------------------------------------------------------------------------
Matrix::Matrix( void ) : INIT_VARS(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] n    order of the square Matrix.
 *  @param[in] init if true all elements are initialized to zero. (default: true)
 *
 *  Construct an empty n by n Matrix, optionaly not initializing the elements.
 */
// ---------------------------------------------------------------------------------------
Matrix::Matrix( const int32_t n, bool init ) : INIT_VARS(0) {
  // -------------------------------------------------------------------------------------
  resize(n,n,n);
  if ( init ) {
    set( D_ZERO );
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nr   number of rows.
 *  @param[in] nc   number of columns.
 *  @param[in] init if true all elements are initialized to zero. (default: true)
 *
 *  Construct an empty nr by nc Matrix, optionaly not initializing the elements.
 */
// ---------------------------------------------------------------------------------------
Matrix::Matrix( const int32_t nr, const int32_t nc, bool init ) : INIT_VARS(0) {
  // -------------------------------------------------------------------------------------
  resize(nr,nc,nr);
  if ( init ) {
    set( D_ZERO );
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nr   number of rows.
 *  @param[in] nc   number of columns.
 *  @param[in] ld   leading dimension.
 *  @param[in] init if true all elements are initialized to zero. (default: true)
 *
 *  Construct an empty nr by nc Matrix, optionaly not initializing the elements.
 */
// ---------------------------------------------------------------------------------------
Matrix::Matrix( const int32_t nr, const int32_t nc,
		const int32_t ld, bool init ) : INIT_VARS(0) {
  // -------------------------------------------------------------------------------------
  resize(nr,nc,ld);
  if ( init ) {
    set( D_ZERO );
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] M     reference to a source Matrix.
 *  @param[in] clone if true all free space will be reallocated (default: false)
 *
 *  Construct a copy of the source Matrix.
 */
// ---------------------------------------------------------------------------------------
Matrix::Matrix( Matrix& M, const bool clone ) : INIT_VARS(0) {
  // -------------------------------------------------------------------------------------
  copy( M, clone );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Matrix::~Matrix( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}








// =======================================================================================
/** @brief Set Matrix.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
void Matrix::column_major( const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  load( src, COLUMN_MAJOR );
}


// =======================================================================================
/** @brief Set Matrix.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
void Matrix::row_major( const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  load( src, ROW_MAJOR );
}


// =======================================================================================
/** @brief Set Diagonal.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
void Matrix::diagonal( const real8_t* src ) {
  // -------------------------------------------------------------------------------------
  load( src, DIAGONAL );
}


// =======================================================================================
/** @brief Set Upper Triangle.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
void Matrix::upper_triangle( const real8_t* src ) {
  // -------------------------------------------------------------------------------------
    load( src, UPPER_TRIANGLE );
}


// =======================================================================================
/** @brief Set Lower Triangle.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix and load the elements with data from src in .
 *  @note it is up to the programmer to make sure src points to enough space to read from.
 */
// ---------------------------------------------------------------------------------------
void Matrix::lower_triangle( const real8_t* src ) {
  // -------------------------------------------------------------------------------------
    load( src, LOWER_TRIANGLE );
}


// =======================================================================================
/** @brief Set Identity.
 *  @param[in] src pointer to a source of data.
 *
 *  Construct a Matrix with one's onm the diagonal and zero everywhere else.
 */
// ---------------------------------------------------------------------------------------
void Matrix::identity( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t r=0; r<nrow; r++ ) {
    for ( int32_t c=0; c<ncol; c++ ) {
      at(r,c) = ((r==c) ? (D_ONE) : (D_ZERO));
    }
  }
}








// =======================================================================================
/** @brief Load.
 *  @param src pointer to a source array.
 *  @return pointer next available element in the source array.
 *
 *  Load the three elements of this array from the next three positions in the source
 *  array and return the fourth position.
 */
// ---------------------------------------------------------------------------------------
real8_t* Matrix::load( const real8_t* src, matrix_format_e order ) {
  // -------------------------------------------------------------------------------------

  real8_t* p = const_cast<real8_t*>(src);
  
  switch(order) {
  case COLUMN_MAJOR: { // ----------------------------------------------------------------
    for ( int32_t c=0; c<ncol; c++ ) {
      for ( int32_t r=0; r<nrow; r++ ) {
	this->at(r,c) = *p++;
      }
    }
  } break;

  case ROW_MAJOR: { // -------------------------------------------------------------------
    for ( int32_t r=0; r<nrow; r++ ) {
      for ( int32_t c=0; c<ncol; c++ ) {
	this->at(r,c) = *p++;
      }
    }
  } break;

  case DIAGONAL: { // --------------------------------------------------------------------
    for ( int32_t r=0; r<nrow; r++ ) {
      for ( int32_t c=0; c<ncol; c++ ) {
	if ( r == c ) {
	  this->at(r,c) = *p++;
	} else {
	  this->at(r,c) = D_ZERO;
	}
      }
    }
  } break;

  case UPPER_TRIANGLE: { // --------------------------------------------------------------
    if ( isSquare() ) {
      for ( int32_t r=0; r<nrow; r++ ) {
	for ( int32_t c=r; c<ncol; c++ ) {
	  real8_t x = *p++;
	  this->at(r,c) = x;
	  if ( r != c ) {
	    this->at(c,r) = x;
	  }
	}
      }
    } else {
      logger->warn( LOCATION,
		    "UPPER_TRIANGLE: Matrix is not square(%d,%d)",
		    nrow, ncol );
    }
  } break;

  case LOWER_TRIANGLE: { // --------------------------------------------------------------
    if ( isSquare() ) {
      for ( int32_t r=0; r<nrow; r++ ) {
	for ( int32_t c=0; c<=r; c++ ) {
	  real8_t x = *p++;
	  this->at(r,c) = x;
	  if ( r != c ) {
	    this->at(c,r) = x;
	  }
	}
      }
    } else {
      logger->warn( LOCATION,
		    "LOWER_TRIANGLE: Matrix is not square(%d,%d)",
		    nrow, ncol );
    }
  } break;

  case IDENTITY:
  default: { // --------------------------------------------------------------------------
    std::cerr << "This Should not be possible\n";
    throw 1;
  }
  }
  
  return p;
}


// =======================================================================================
/** @brief Store.
 *  @param dst pointer to a destination array.
 *  @return pointer next available element in the destination array.
 *
 *  Store the three elements of this array into the next three positions in the
 *  destination array and return the fourth position.
 */
// ---------------------------------------------------------------------------------------
real8_t* Matrix::store( const real8_t* dst, matrix_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* p = const_cast<real8_t*>(dst);
  
  switch(order) {
  case COLUMN_MAJOR: { // ----------------------------------------------------------------
    for ( int32_t c=0; c<ncol; c++ ) {
      for ( int32_t r=0; r<nrow; r++ ) {
	*p++ = this->at(r,c);
      }
    }
  } break;

  case ROW_MAJOR: { // -------------------------------------------------------------------
    for ( int32_t r=0; r<nrow; r++ ) {
      for ( int32_t c=0; c<ncol; c++ ) {
	*p++ = this->at(r,c);
      }
    }
  } break;

  case DIAGONAL: { // --------------------------------------------------------------------
    int32_t n = Min( nrow, ncol );
    for ( int32_t i=0; i<n; i++ ) {
      *p++ = this->at(i,i);
    }
  } break;

  case UPPER_TRIANGLE: { // --------------------------------------------------------------
    if ( isSquare() ) {
      for ( int32_t r=0; r<nrow; r++ ) {
	for ( int32_t c=r; c<ncol; c++ ) {
	  *p++ = this->at(r,c);
	}
      }
    } else {
      logger->warn( LOCATION,
		    "UPPER_TRIANGLE: Matrix is not square(%d,%d)",
		    nrow, ncol );
    }
  } break;

  case LOWER_TRIANGLE: { // --------------------------------------------------------------
    if ( isSquare() ) {
      for ( int32_t r=0; r<nrow; r++ ) {
	for ( int32_t c=0; c<=r; c++ ) {
	  *p++ = this->at(r,c);
	}
      }
    } else {
      logger->warn( LOCATION,
		    "LOWER_TRIANGLE: Matrix is not square(%d,%d)",
		    nrow, ncol );
    }
  } break;

  case IDENTITY:
  default: { // --------------------------------------------------------------------------
    std::cerr << "This Should not be possible\n";
    throw 1;
  }
  }

  return p;
}



// =======================================================================================
/** @brief To String.
 *  @param[in] M    reference to a Matrix.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] cdel column delimeter.
 *  @param[in] rdel row delimeter.
 *
 *  Format a Matrix for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Matrix& M,
		      std::string sfmt, std::string cdel, std::string rdel ) {
  // -------------------------------------------------------------------------------------
  std::string tstr;
  char buffer[64];

  std::string df      = cdel + sfmt;
  const char* fmt     = sfmt.c_str();
  const char* col_del = df.c_str();

  int32_t nr = size(M,0);
  int32_t nc = size(M,1);
  for ( int32_t r=0; r<nr; r++ ) {
    snprintf( buffer, 64, fmt, M(r,0) );
    if ( 0 == r ) {
      tstr = buffer;
    } else {
      tstr.append( buffer );
    }
    for ( int32_t c=1; c<nc; c++ ) {
      snprintf( buffer, 64, col_del, M(r,c) );
      tstr.append( buffer );
    }
    if ( r < (nr-1)) {
      tstr.append( rdel );
    }
  }

  return tstr;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
std::string toString( std::string prefix, Matrix& M, std::string suffix,
		      std::string sfmt, std::string cdel, std::string rdel ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = prefix;
  tstr.append(toString(M, sfmt, cdel, rdel));
  tstr.append(suffix);
  return tstr;
}




// =======================================================================================
// **                                    M A T R I X                                    **
// ======================================================================== END FILE =====

