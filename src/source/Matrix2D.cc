// ====================================================================== BEGIN FILE =====
// **                                  M A T R I X 2 D                                  **
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
/** @brief  Three by three element matrix.
 *  @file   Matrix2D.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-06
 *
 *  Provides the methods for a three by three element matrix.
 */
// =======================================================================================

#include <Matrix2D.hh>

#define INIT_VAR(a) a00(a), a01(a), a10(a), a11(a)


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q     pointer to array containing data.
 *  @param[in] order enum for format of data.
 *
 *  order: ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE
 */
// ---------------------------------------------------------------------------------------
Matrix2D::Matrix2D( const real8_t* q, matrix2d_format_e order ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  this->load( q, order );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m reference to source Matrix2D.
 */
// ---------------------------------------------------------------------------------------
Matrix2D::Matrix2D( const Matrix2D& m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  this->copy(m);
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m pointer to source Matrix2D.
 */
// ---------------------------------------------------------------------------------------
Matrix2D::Matrix2D( const Matrix2D* m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  this->copy(m);
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Matrix2D::~Matrix2D( void ) {
  // -------------------------------------------------------------------------------------
  this->set(0.0e0);
}


// =======================================================================================
/** @brief Set.
 *  @param s scalar value (default: 0)
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::set( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  a00 = s;    a01 = s;
  a10 = s;    a11 = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::copy( const Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  this->a00 = that.a00;    this->a01 = that.a01;
  this->a10 = that.a10;    this->a11 = that.a11;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v pointer to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::copy( const Matrix2D* that ) {
  // -------------------------------------------------------------------------------------
  this->copy( *that );
}


// =======================================================================================
/** @brief From Array.
 *  @param[in] A reference to a three by three element source array.
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::fromArray( const real8_t A[2][2] ) {
  // -------------------------------------------------------------------------------------
  a00 = A[0][0];    a01 = A[0][1];
  a10 = A[1][0];    a11 = A[1][1];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three by three element destination array.
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::toArray( real8_t A[2][2] ) {
  // -------------------------------------------------------------------------------------
  A[0][0] = a00;    A[0][1] = a01;
  A[1][0] = a10;    A[1][1] = a11;
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
real8_t* Matrix2D::load( const real8_t* src, matrix2d_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* q = const_cast<real8_t*>(src);
  
  switch(order) {
    case ROW_MAJOR:
      a00 = *q++;    a01 = *q++;
      a10 = *q++;    a11 = *q++;
      break;

    case COLUMN_MAJOR:
      a00 = *q++;    a10 = *q++;
      a01 = *q++;    a11 = *q++;
      break;

    case UPPER_TRIANGLE:
      a00 = *q++;    a01 = *q++;
      /*      */     a11 = *q++;
      a10 = a01;
      break;

    case LOWER_TRIANGLE:
      a00 = *q++;
      a10 = *q++;    a11 = *q++;
      a01 = a10;
      break;
  }
  
  return q;
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
real8_t* Matrix2D::store( const real8_t* dst, matrix2d_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* q = const_cast<real8_t*>(dst);
  
  switch(order) {
    case ROW_MAJOR:
      *q++ = a00;    *q++ = a01;
      *q++ = a10;    *q++ = a11;
      break;

    case COLUMN_MAJOR:
      *q++ = a00;    *q++ = a10;
      *q++ = a01;    *q++ = a11;
      break;

    case UPPER_TRIANGLE:
      *q++ = a00;    *q++ = a01;
      /*      */     *q++ = a11;
      break;

    case LOWER_TRIANGLE:
      *q++ = a00;
      *q++ = a10;    *q++ = a11;
      break;
  }
  
  return q;
}


// =======================================================================================
/** @brief toString.
 *  @param[in] M    reference to a matrix.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] cdel column delimiter.
 *  @param[in] rdel row delimiter.
 *  @return string representation of the matrix.
 *
 *  Format a Matrix2D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Matrix2D& M, std::string sfmt, std::string cdel, std::string rdel ) {
  // -------------------------------------------------------------------------------------
  real8_t buffer[9];
  real8_t *Q[3] = { (buffer+0), (buffer+3) };
  M.store( buffer, ROW_MAJOR );
  return toString( Q, 2, 2, sfmt, cdel, rdel );
}
  

// =======================================================================================
/** @brief Index operator.
 *  @param r row    index.
 *  @param c column index.
 *  @return reference to the (r,c) position in this Matrix.
 */
// ---------------------------------------------------------------------------------------
real8_t& Matrix2D::at( const size_t r, const size_t c ) {
  // -------------------------------------------------------------------------------------
  char buf[64];

  if ( r==0 ) {
    if ( c==0 ) { return this->a00; }
    if ( c==1 ) { return this->a01; }
    snprintf( buf, 63, "column out of range: %lu expected (0 or 1)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  if ( r==1 ) {
    if ( c==0 ) { return this->a10; }
    if ( c==1 ) { return this->a11; }
    snprintf( buf, 63, "column out of range: %lu expected (0 or 1)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  snprintf( buf, 63, "row out of range: %lu expected (0 or 1)", r );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Index operator.
 *  @param r row    index.
 *  @param c column index.
 *  @return reference to the (r,c) position in this Matrix.
 */
// ---------------------------------------------------------------------------------------
real8_t& Matrix2D::operator()( const size_t r, const size_t c ) {
  // -------------------------------------------------------------------------------------
  char buf[64];

  if ( r==0 ) {
    if ( c==0 ) { return this->a00; }
    if ( c==1 ) { return this->a01; }
    snprintf( buf, 63, "column out of range: %lu expected (0 or 1)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  if ( r==1 ) {
    if ( c==0 ) { return this->a10; }
    if ( c==1 ) { return this->a11; }
    snprintf( buf, 63, "column out of range: %lu expected (0 or 1)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  snprintf( buf, 63, "row out of range: %lu expected (0 or 1)", r );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A pointer to the first  Matrix2D.
 *  @param[in] B pointer to the second Matrix2D.
 *  @return dot product of two matrices.
 *
 *  Dot product of a Matrix2D onto a Matrix2D.
 */
// ---------------------------------------------------------------------------------------
const Matrix2D dot( const Matrix2D& A, const Matrix2D& B ) {
  // -------------------------------------------------------------------------------------
  
  return Matrix2D( (A.a00*B.a00) + (A.a01*B.a10),
                   (A.a00*B.a01) + (A.a01*B.a11),
                   (A.a10*B.a00) + (A.a11*B.a10),
                   (A.a10*B.a01) + (A.a11*B.a11) );
}


// =======================================================================================
/** @brief Inverse.
 */
// ---------------------------------------------------------------------------------------
const Matrix2D Matrix2D::inverse( void ) {
  // -------------------------------------------------------------------------------------
  real8_t D = det();

  if ( isZero(D) ) {
    throw( new std::domain_error( "Singular Matrix" ) );
  }
  
  return Matrix2D(  a11 / D, -a01 / D,
                   -a10 / D,  a00 / D );
}


// =======================================================================================
// **                                  M A T R I X 2 D                                  **
// ======================================================================== END FILE =====
