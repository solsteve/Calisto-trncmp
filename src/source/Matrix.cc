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
 *  
 *  The following Matrix
 *     1.1, 1.2, 1.3
 *     2.1, 2.2, 2.3
 *     3.1, 3.2, 3.3
 *     4.1, 4.2, 4.3
 *  would be stored in memory as:
 *     1.1 | 2.1 | 3.1 | 4.1 | 1.2 | 2.2 | 3.2 | 4.2 | 1.3 | 2.3 | 3.3 | 4.3
 *  \endverbatim
 *
 * This represents FORTRAN's column-major layout. This is for easy compatability with
 * LAPACK.
 */
// =======================================================================================


#include <Matrix.hh>

#define INIT_VARS(a) data(a), nrow(a), ncol(a), nbuf(0)

TLOGGER_INSTANCE( logger );

real8_t det2x2( const Matrix& M );
real8_t det3x3( const Matrix& M );
real8_t detNxN( const Matrix& M );

real8_t inv2x2( Matrix& A, const Matrix& M );
real8_t inv3x3( Matrix& A, const Matrix& M );
real8_t invNxN( Matrix& A, const Matrix& M );


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


// =======================================================================================
// ---------------------------------------------------------------------------------------
void Matrix::debug( void ) {
  // -------------------------------------------------------------------------------------
  fprintf( stdout, "[%d,%d (%d)]", nrow, ncol, nbuf );
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
    //logger->info( "x----- Matrix::destroy(dealloc) -----x" );
    delete[] data;
  }// else {
  //logger->info( "x----- Matrix::destroy(no dealloc) -----x" );
  //}
  data = static_cast<real8_t*>(0);
  nrow = 0;
  ncol = 0;
  nbuf = 0;
}


// =======================================================================================
/** @brief Resize.
 *  @param[in] n order of the square matrix.
 *
 *  Reallocate if necessary.
 */
// ---------------------------------------------------------------------------------------
void Matrix::resize( const int32_t n ) {
  // -------------------------------------------------------------------------------------
  int32_t new_nbuf = n*n;
  
  if ( new_nbuf > nbuf ) {
    destroy();
    data = new real8_t[ new_nbuf ];
    nbuf = new_nbuf;
  }
  nrow = n;
  ncol = n;
}


// =======================================================================================
/** @brief Resize.
 *  @param[in] nr number of rows.
 *  @param[in] nc number of columns.
 *
 *  Reallocate if necessary.
 */
// ---------------------------------------------------------------------------------------
void Matrix::resize( const int32_t nr, const int32_t nc ) {
  // -------------------------------------------------------------------------------------

  int32_t new_nbuf = nr*nc;
  
  if ( new_nbuf > nbuf ) {
    destroy();
    data = new real8_t[ new_nbuf ];
    nbuf = new_nbuf;
  }

  nrow = nr;
  ncol = nc;
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
 *
 *  Copy all of the elements of the source M. Resize if necessary this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::copy( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  //logger->info( "v----- Matrix::copy -----v" );
  resize( M.nrow, M.ncol );

  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      this->at(r,c) = const_cast<Matrix&>(M).at(r,c);
    }
  }
  //logger->info( "^----- Matrix::copy -----^" );
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] M reference to another Matrix.
 *  @return true if Matrices are element by element equal.
 */
// ---------------------------------------------------------------------------------------
bool Matrix::equals( const Matrix& M, const real8_t eps ) {
  // -------------------------------------------------------------------------------------
  if ( nrow != M.nrow ) { fprintf(stdout,"Matrix::equals  %d != %d\n", nrow, M.nrow); return false; }
  if ( ncol != M.ncol ) { fprintf(stdout,"Matrix::equals  %d != %d\n", ncol, M.ncol); return false; }
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      const real8_t dif = at(r,c) - const_cast<Matrix&>(M).at(r,c);
      if ( dif < -eps ) { fprintf(stdout,"Matrix::equals  %g < %g\n", dif, -eps); return false;}
      if ( dif >  eps ) { fprintf(stdout,"Matrix::equals  %g > %g\n", dif,  eps); return false;}
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
  //logger->info( "x----- Matrix::Matrix(void) -----x" );
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
  resize(n);
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
  resize(nr,nc);
  if ( init ) {
    set( D_ZERO );
  }
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] M     reference to a source Matrix.
 *
 *  Construct a copy of the source Matrix.
 */
// ---------------------------------------------------------------------------------------
Matrix::Matrix( const Matrix& M ) : INIT_VARS(0) {
  // -------------------------------------------------------------------------------------
  //logger->info( "v----- Matrix::Matrix(M) -----v" );
  copy( M );
  //logger->info( "^----- Matrix::Matrix(M) -----^" );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Matrix::~Matrix( void ) {
  // -------------------------------------------------------------------------------------
  //logger->info( "v----- Matrix::~Matrix -----v" );
  destroy();
  //logger->info( "^----- Matrix::~Matrix -----^" );
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
std::string toString( const Matrix&      M,
		      const std::string& sfmt,
		      const std::string& cdel,
		      const std::string& rdel ) {
  // -------------------------------------------------------------------------------------
  std::string tstr;
  char buffer[64];

  std::string df      = cdel + sfmt;
  const char* fmt     = sfmt.c_str();
  const char* col_del = df.c_str();

  int32_t nr = size(M,0);
  int32_t nc = size(M,1);
  for ( int32_t r=0; r<nr; r++ ) {
    snprintf( buffer, 64, fmt, const_cast<Matrix&>(M).at(r,0) );
    if ( 0 == r ) {
      tstr = buffer;
    } else {
      tstr.append( buffer );
    }
    for ( int32_t c=1; c<nc; c++ ) {
      snprintf( buffer, 64, col_del, const_cast<Matrix&>(M).at(r,c) );
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
std::string toString( const std::string& prefix,
		      const Matrix&      M,
		      const std::string& suffix,
		      const std::string& sfmt,
		      const std::string& cdel,
		      const std::string& rdel ) {
  // -------------------------------------------------------------------------------------
  std::string tstr = prefix;
  tstr.append(toString(M, sfmt, cdel, rdel));
  tstr.append(suffix);
  return tstr;
}









// =======================================================================================
/** @brief Transpose.
 *  @param[in] M reference to a source Matrix.
 *
 *  Rebuild this Matrix from the transpose of M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::T( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  int32_t nr = const_cast<Matrix&>(M).size(1);
  int32_t nc = const_cast<Matrix&>(M).size(0);
  resize( nr, nc );
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(M).at(c,r);
    }
  }
}



// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 *
 *  Sum of the elemets of this Matrix.
 */
// ---------------------------------------------------------------------------------------
 real8_t  Matrix::sum( void )  {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      sum += at(r,c);
    }
  }
  return sum;
}




// =======================================================================================
/** @brief Sum Square.
 *  @return sum of the squares of the elements.
 *
 *  Sum the squares of all elements of this Matrix.
 */
// ---------------------------------------------------------------------------------------
 real8_t  Matrix::sumsq( void ) {
  // -------------------------------------------------------------------------------------
  real8_t sum = D_ZERO;
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      real8_t x = at(r,c);
      sum += (x*x);
    }
  }
  return sum;
}


// =======================================================================================
/** @brief Sum Square Difference.
 *  @param[in] that reference to the second Matrix.
 *  @return sum of the square difference of the elements.
 *
 *  Sum of the squares of the differences of the elements of this and that Matrices.
 *  @note: this procedure will not fail is dimensions do not match. The minimum
 *  intersection will be 
 */
// ---------------------------------------------------------------------------------------
 real8_t  Matrix::sumsq( const Matrix& that ) {
  // -------------------------------------------------------------------------------------
  int32_t nr  = Min( nrow, const_cast<Matrix&>(that).size(0) );
  int32_t nc  = Min( ncol, const_cast<Matrix&>(that).size(1) );
  real8_t sum = D_ZERO;
  for ( int32_t c=0; c<nc; c++ ) {
    for ( int32_t r=0; r<nr; r++ ) {
      real8_t x = at(r,c) - const_cast<Matrix&>(that).at(r,c);
      sum += (x*x);
    }
  }
  return sum;
}


// =======================================================================================
/** @brief Inner Product.
 *  @param[in] lhs reference to the left  hand Matrix.
 *  @param[in] rhs reference to the right hand Matrix.
 *
 *  Set this 
 */
// ---------------------------------------------------------------------------------------
void Matrix::dot( const Matrix& lhs, const Matrix& rhs ) {
  // -------------------------------------------------------------------------------------
  int32_t m    = const_cast<Matrix&>(lhs).size(0);
  int32_t n    = const_cast<Matrix&>(rhs).size(1);
  int32_t k    = const_cast<Matrix&>(lhs).size(1);
  real8_t one  = D_ONE;
  real8_t zero = D_ZERO;

  resize( m, n );
  
  dgemm_( "NO", "NO", &m, &n, &k,
          &one, const_cast<Matrix&>(lhs).A(), const_cast<Matrix&>(lhs).LDA(),
          const_cast<Matrix&>(rhs).A(), const_cast<Matrix&>(rhs).LDA(),
          &zero, data, &nrow );
}








// =======================================================================================
/** @brief Addition.
 *  @param[in] s scalar value.
 *
 *  Add a scalar to each element of this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::add( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) += s;
    }
  }
}


// =======================================================================================
/** @brief Addition.
 *  @param[in] M reference to another Matrix.
 *
 *  Add each element of M to each element of this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::add( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  if ( nrow != M.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( ncol != M.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) += const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Addition.
 *  @param[in] s scalar value.
 *  @param[in] M reference to another Matrix.
 *
 *  Replace each element of this Matrix with the sum of s and each element of M.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::add( const real8_t s, const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = s + const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Addition.
 *  @param[in] M reference to another Matrix.
 *  @param[in] s scalar value.
 *
 *  Replace each element of this Matrix with the sum of each element of M and s.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::add( const Matrix& M, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(M).at(r,c) + s;
    }
  }
}


// =======================================================================================
/** @brief Addition.
 *  @param[in] lhs reference to the left  hand Matrix.
 *  @param[in] rhs reference to the right hand Matrix.
 *
 *  Replace each element of this Matrix with the sum of the elements of lhs and rhs.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::add( const Matrix& lhs, const Matrix& rhs ) {
  // -------------------------------------------------------------------------------------
  if ( lhs.nrow != rhs.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( lhs.ncol != rhs.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  resize(lhs.nrow,lhs.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(lhs).at(r,c) + const_cast<Matrix&>(rhs).at(r,c);
    }
  }
}








// =======================================================================================
/** @brief Subtraction.
 *  @param[in] s scalar value.
 *
 *  Subtract a scalar from each element of this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::sub( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) -= s;
    }
  }
}


// =======================================================================================
/** @brief Subtraction.
 *  @param[in] M reference to another Matrix.
 *
 *  Subtract each element of M from each element of this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::sub( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  if ( nrow != M.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( ncol != M.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) -= const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Subtraction.
 *  @param[in] s scalar value.
 *  @param[in] M reference to another Matrix.
 *
 *  Replace each element of this Matrix with the difference of s and each element of M.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::sub( const real8_t s, const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = s - const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Subtraction.
 *  @param[in] M reference to another Matrix.
 *  @param[in] s scalar value.
 *
 *  Replace each element of this Matrix with the difference of each element of M and s.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::sub( const Matrix& M, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(M).at(r,c) - s;
    }
  }
}


// =======================================================================================
/** @brief Subtraction.
 *  @param[in] lhs reference to the left  hand Matrix.
 *  @param[in] rhs reference to the right hand Matrix.
 *
 *  Replace each element of this Matrix with the difference of the elements of lhs and rhs.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::sub( const Matrix& lhs, const Matrix& rhs ) {
  // -------------------------------------------------------------------------------------
  if ( lhs.nrow != rhs.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( lhs.ncol != rhs.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  resize(lhs.nrow,lhs.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(lhs).at(r,c) - const_cast<Matrix&>(rhs).at(r,c);
    }
  }
}








// =======================================================================================
/** @brief Multiplication.
 *  @param[in] s scalar value.
 *
 *  Multiply a scalar with each element of this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::mul( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) *= s;
    }
  }
}


// =======================================================================================
/** @brief Multiplication.
 *  @param[in] M reference to another Matrix.
 *
 *  Multiply each element of M with each element of this Matrix.
 */
// ---------------------------------------------------------------------------------------
void Matrix::mul( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  if ( nrow != M.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( ncol != M.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) *= const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Multiplication.
 *  @param[in] s scalar value.
 *  @param[in] M reference to another Matrix.
 *
 *  Replace each element of this Matrix with the product of s and each element of M.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::mul( const real8_t s, const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = s * const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Multiplication.
 *  @param[in] M reference to another Matrix.
 *  @param[in] s scalar value.
 *
 *  Replace each element of this Matrix with the product of each element of M and s.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::mul( const Matrix& M, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(M).at(r,c) * s;
    }
  }
}


// =======================================================================================
/** @brief Multiplication.
 *  @param[in] lhs reference to the left  hand Matrix.
 *  @param[in] rhs reference to the right hand Matrix.
 *
 *  Replace each element of this Matrix with the product of the elements of lhs and rhs.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::mul( const Matrix& lhs, const Matrix& rhs ) {
  // -------------------------------------------------------------------------------------
  if ( lhs.nrow != rhs.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( lhs.ncol != rhs.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  resize(lhs.nrow,lhs.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(lhs).at(r,c) * const_cast<Matrix&>(rhs).at(r,c);
    }
  }
}








// =======================================================================================
/** @brief Division.
 *  @param[in] s scalar value.
 *
 *  Divide each element of this Matrix by s.
 */
// ---------------------------------------------------------------------------------------
void Matrix::div( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) /= s;
    }
  }
}


// =======================================================================================
/** @brief Division.
 *  @param[in] M reference to another Matrix.
 *
 *  Divide each element of this Matrix by each element of M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::div( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  if ( nrow != M.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( ncol != M.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) /= const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Division.
 *  @param[in] s scalar value.
 *  @param[in] M reference to another Matrix.
 *
 *  Replace each element of this Matrix with the division of s by each element of M.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::div( const real8_t s, const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = s / const_cast<Matrix&>(M).at(r,c);
    }
  }
}


// =======================================================================================
/** @brief Division.
 *  @param[in] M reference to another Matrix.
 *  @param[in] s scalar value.
 *
 *  Replace each element of this Matrix with the division of each element of M by s.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::div( const Matrix& M, const real8_t s ) {
  // -------------------------------------------------------------------------------------
  resize(M.nrow,M.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(M).at(r,c) / s;
    }
  }
}


// =======================================================================================
/** @brief Division.
 *  @param[in] lhs reference to the left  hand Matrix.
 *  @param[in] rhs reference to the right hand Matrix.
 *
 *  Replace each element of this Matrix with the division of the elements of lhs by
 *  the coresponding elements rhs.
 *  Resize this Matrix to fit M.
 */
// ---------------------------------------------------------------------------------------
void Matrix::div( const Matrix& lhs, const Matrix& rhs ) {
  // -------------------------------------------------------------------------------------
  if ( lhs.nrow != rhs.nrow ) { throw new std::length_error( "number of rows do not match" ); }
  if ( lhs.ncol != rhs.ncol ) { throw new std::length_error( "number of columns do not match" ); }
  resize(lhs.nrow,lhs.ncol);
  for ( int32_t c=0; c<ncol; c++ ) {
    for ( int32_t r=0; r<nrow; r++ ) {
      at(r,c) = const_cast<Matrix&>(lhs).at(r,c) / const_cast<Matrix&>(rhs).at(r,c);
    }
  }
}








// =======================================================================================
/** @brief Determinant.
 *  @param[in] CM reference to a Matrix;
 *  @return determinant of the Matrix CM.
 *
 *  Calculate the determinant of a 2x2 Matrix directly.
 */
// ---------------------------------------------------------------------------------------
real8_t det2x2( const Matrix& CM ) {
  // -------------------------------------------------------------------------------------
  Matrix& M = const_cast<Matrix&>(CM);
  
    real8_t* q = M.A();
    return (q[0] * q[3]) - (q[1] * q[2]);
}

// =======================================================================================
/** @brief Determinant.
 *  @param[in] CM reference to a Matrix;
 *  @return determinant of the Matrix CM.
 *
 *  Calculate the determinant of a 2x2 Matrix directly.
 */
// ---------------------------------------------------------------------------------------
real8_t det3x3( const Matrix& CM ) {
  // -------------------------------------------------------------------------------------
  Matrix& M = const_cast<Matrix&>(CM);
  
    real8_t* q = M.A();
    return 
      q[0]*(q[4]*q[8] - q[5]*q[7]) +
      q[1]*(q[5]*q[6] - q[3]*q[8]) +
      q[2]*(q[3]*q[7] - q[4]*q[6]);
}

// =======================================================================================
/** @brief Determinant.
 *  @param[in] CM reference to a Matrix;
 *  @return determinant of the Matrix CM.
 *
 *  Use LAPACK call to DGETRF to approximate the determinant of the NxN Matrix CM.
 *  DGETRF performs the LU decomposition of the input Matrix. The determinant is the
 *  product of the diagonal elements of the decomposed upper triangular Matrix.
 */
// ---------------------------------------------------------------------------------------
real8_t detNxN( const Matrix& CM ) {
  // -------------------------------------------------------------------------------------
  Matrix M(CM); // create a temporary copy of the matrix. This operation is destructive.
  int32_t n    = size(M,0);
  int32_t info = 0;
  real8_t d    = D_ZERO;
  int32_t ipiv[n];

  dgetrf_( M.M(), M.N(), M.A(), M.LDA(), ipiv, &info );

  if ( info > 0 ) {
    logger->warn( "DGETRF: The matrix is singular because U(%d,%d)", info, info );
  } else {
    d = D_ONE;
    for ( int32_t i=0; i<n; i++ ) {
      d = ((ipiv[i] == (i+1)) ? d : -d) * M.at(i,i);
    }
  }

  return d;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t inv2x2( Matrix& A, const Matrix& CM ) {
  // -------------------------------------------------------------------------------------
  Matrix&  M = const_cast<Matrix&>(CM);
  real8_t  D = det2x2(CM);
  real8_t* a = A.A();
  
    real8_t* q = M.A();
    a[0] =  q[3]/D;         a[2] = -q[2]/D;
    a[1] = -q[1]/D;         a[3] =  q[0]/D;
  
  return D;
}

// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t inv3x3( Matrix& A, const Matrix& CM ) {
  // -------------------------------------------------------------------------------------
  Matrix&  M = const_cast<Matrix&>(CM);
  real8_t  D = det3x3(CM);
  real8_t* a = A.A();

    real8_t* q = M.A();
    a[0] = (q[4]*q[8] - q[7]*q[5])/D;
    a[1] = (q[7]*q[2] - q[1]*q[8])/D;
    a[2] = (q[1]*q[5] - q[4]*q[2])/D;

    a[3] = (q[6]*q[5] - q[3]*q[8])/D;
    a[4] = (q[0]*q[8] - q[6]*q[2])/D;
    a[5] = (q[3]*q[2] - q[0]*q[5])/D;

    a[6] = (q[3]*q[7] - q[6]*q[4])/D;
    a[7] = (q[6]*q[1] - q[0]*q[7])/D;
    a[8] = (q[0]*q[4] - q[3]*q[1])/D;

  return D;
}


// =======================================================================================
// ---------------------------------------------------------------------------------------
real8_t invNxN( Matrix& A, const Matrix& CM ) {
  // -------------------------------------------------------------------------------------
  A.copy(CM);
  int32_t n    = size(A,0);
  int32_t info = 0;
  int32_t ipiv[n+1];

  dgetrf_( A.M(), A.N(), A.A(), A.LDA(), ipiv, &info );

  if ( info > 0 ) {
    logger->warn("DGETRF: The matrix is singular because U(%d,%d)", info, info );
    return D_ZERO;
  }

  // -------------------------------------------------------------------------------------
  
  real8_t d = D_ONE;

  for ( int32_t i=0; i<n; i++ ) {
    d = ((ipiv[i] == (i+1)) ? d : -d) * A.at(i,i);
  }
  
  // -------------------------------------------------------------------------------------

  int32_t lwork = -1;
  real8_t param = 0.0;

  dgetri_( A.M(), A.A(), A.LDA(), ipiv, &param, &lwork, &info );
  if ( 0 != info ) {
    logger->error( "DGETRF: Query failed: %d", info );
    return D_ZERO;
  }

  lwork = (int32_t)param;
  real8_t work[lwork];
  
  // -------------------------------------------------------------------------------------

  info = 0;
  dgetri_( A.M(), A.A(), A.LDA(), ipiv, work, &lwork, &info );

  if ( info > 0 ) {
    logger->warn("DGETRF: The matrix is singular because U(%d,%d)", info, info );
    return D_ZERO;
  }

  return d;
}








// =======================================================================================
/** @brief Determinant.
 *  @return determinant of this matrix.
 *
 *  @note Matrices of order 0,1,2, or 3 are returned directly.
 *        Orders 4 and above are approximated using LAPACK call to DGETRF.
 */
// ---------------------------------------------------------------------------------------
real8_t  Matrix::det( void ) {
  // -------------------------------------------------------------------------------------
  int32_t n = nrow;
  
  if ( n != ncol ) {
    logger->error("Matrix is not square row=%d col=%d", nrow, ncol);
    return D_ZERO;
  }

  real8_t d = D_ZERO;
  switch(n) {
  case 0:                       break;
  case 1:  d = *data;           break;
  case 2:  d = det2x2( *this ); break;
  case 3:  d = det3x3( *this ); break;
  default: d = detNxN( *this ); break;
  }
  
  return d;
}


// =======================================================================================
/** @brief Inverse.
 *  @param[in] M reference to a Matrix.
 *  @return determinant of the matrix.
 *
 *  On exit this Matrix will be replaced by the inverse of Matrix M.
 */
// ---------------------------------------------------------------------------------------
real8_t  Matrix::inverse( const Matrix& M ) {
  // -------------------------------------------------------------------------------------
  int32_t n  = ::size(M,0);
  int32_t nc = ::size(M,1);
  
  if ( n != nc ) {
    logger->error("Matrix is not square row=%d col=%d", n, nc);
    return D_ZERO;
  }

  real8_t d = D_ZERO;
  
  switch(n) {
  case 0:
    break;
  case 1:
    d     = *data;
    *data = D_ONE / d;
    break;
  case 2:
    resize(2);
    d = inv2x2( *this, M );
    break;
  case 3:
    resize(3);
    d = inv3x3( *this, M );
    break;
  default:
    resize(n);
    d = invNxN( *this, M );
    break;
  }
  
  return d;
}


// =======================================================================================
// **                                    M A T R I X                                    **
// ======================================================================== END FILE =====
