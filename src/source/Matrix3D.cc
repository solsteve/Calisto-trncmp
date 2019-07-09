// ====================================================================== BEGIN FILE =====
// **                                  M A T R I X 3 D                                  **
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
 *  @file   Matrix3D.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jul-04
 *
 *  Provides the methods for a three by three element matrix.
 */
// =======================================================================================

#include <Matrix3D.hh>

#define INIT_VAR(a) a00(a), a01(a), a02(a), a10(a), a11(a), a12(a), a20(a), a21(a), a22(a)


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q     pointer to array containing data.
 *  @param[in] order enum for format of data.
 *
 *  order: ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE
 */
// ---------------------------------------------------------------------------------------
Matrix3D::Matrix3D( const real8_t* q, matrix3d_format_e order ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  this->load( q, order );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m reference to source Matrix3D.
 */
// ---------------------------------------------------------------------------------------
Matrix3D::Matrix3D( const Matrix3D& m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  this->copy(m);
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m pointer to source Matrix3D.
 */
// ---------------------------------------------------------------------------------------
Matrix3D::Matrix3D( const Matrix3D* m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  this->copy(m);
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Matrix3D::~Matrix3D( void ) {
  // -------------------------------------------------------------------------------------
  this->set(0.0e0);
}


// =======================================================================================
/** @brief Set.
 *  @param s scalar value (default: 0)
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::set( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  a00 = s;    a01 = s;    a02 = s;
  a10 = s;    a11 = s;    a12 = s;
  a20 = s;    a21 = s;    a22 = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::copy( const Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  this->a00 = that.a00;    this->a01 = that.a01;    this->a02 = that.a02;
  this->a10 = that.a10;    this->a11 = that.a11;    this->a12 = that.a12;
  this->a20 = that.a20;    this->a21 = that.a21;    this->a22 = that.a22;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v pointer to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::copy( const Matrix3D* that ) {
  // -------------------------------------------------------------------------------------
  this->copy( *that );
}


// =======================================================================================
/** @brief From Array.
 *  @param[in] A reference to a three by three element source array.
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::fromArray( const real8_t A[3][3] ) {
  // -------------------------------------------------------------------------------------
  a00 = A[0][0];    a01 = A[0][1];    a02 = A[0][2];
  a10 = A[1][0];    a11 = A[1][1];    a12 = A[1][2];
  a20 = A[2][0];    a21 = A[2][1];    a22 = A[2][2];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three by three element destination array.
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::toArray( real8_t A[3][3] ) {
  // -------------------------------------------------------------------------------------
  A[0][0] = a00;    A[0][1] = a01;    A[0][2] = a02;
  A[1][0] = a10;    A[1][1] = a11;    A[1][2] = a12;
  A[2][0] = a20;    A[2][1] = a21;    A[2][2] = a22;
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
real8_t* Matrix3D::load( const real8_t* src, matrix3d_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* q = const_cast<real8_t*>(src);
  
  switch(order) {
    case ROW_MAJOR:
      a00 = *q++;    a01 = *q++;    a02 = *q++;
      a10 = *q++;    a11 = *q++;    a12 = *q++;
      a20 = *q++;    a21 = *q++;    a22 = *q++;
      break;

    case COLUMN_MAJOR:
      a00 = *q++;    a10 = *q++;    a20 = *q++;
      a01 = *q++;    a11 = *q++;    a21 = *q++;
      a02 = *q++;    a12 = *q++;    a22 = *q++;
      break;

    case UPPER_TRIANGLE:
      a00 = *q++;    a01 = *q++;    a02 = *q++;
      /*      */     a11 = *q++;    a12 = *q++;
      /*                      */    a22 = *q++;
      a10 = a01;
      a20 = a02;
      a21 = a12;
      break;

    case LOWER_TRIANGLE:
      a00 = *q++;
      a10 = *q++;    a11 = *q++;
      a20 = *q++;    a21 = *q++;    a22 = *q++;
      a01 = a10;
      a02 = a20;
      a12 = a21;
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
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
real8_t* Matrix3D::store( const real8_t* dst, matrix3d_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* q = const_cast<real8_t*>(dst);
  
  switch(order) {
    case ROW_MAJOR:
      *q++ = a00;    *q++ = a01;    *q++ = a02;
      *q++ = a10;    *q++ = a11;    *q++ = a12;
      *q++ = a20;    *q++ = a21;    *q++ = a22;
      break;

    case COLUMN_MAJOR:
      *q++ = a00;    *q++ = a10;    *q++ = a20;
      *q++ = a01;    *q++ = a11;    *q++ = a21;
      *q++ = a02;    *q++ = a12;    *q++ = a22;
      break;

    case UPPER_TRIANGLE:
      *q++ = a00;    *q++ = a01;    *q++ = a02;
      /*      */     *q++ = a11;    *q++ = a12;
      /*                      */    *q++ = a22;
      break;

    case LOWER_TRIANGLE:
      *q++ = a00;
      *q++ = a10;    *q++ = a11;
      *q++ = a20;    *q++ = a21;    *q++ = a22;
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
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
 *  Format a Matrix3D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Matrix3D& M, std::string sfmt, std::string cdel, std::string rdel ) {
  // -------------------------------------------------------------------------------------
  real8_t buffer[9];
  real8_t *Q[3] = { (buffer+0), (buffer+3), (buffer+6) };
  M.store( buffer, ROW_MAJOR );
  return toString( Q, 3, 3, sfmt, cdel, rdel );
}
  

// =======================================================================================
/** @brief Index operator.
 *  @param r row    index.
 *  @param c column index.
 *  @return reference to the (r,c) position in this Matrix.
 */
// ---------------------------------------------------------------------------------------
real8_t& Matrix3D::at( const size_t r, const size_t c ) {
  // -------------------------------------------------------------------------------------
  char buf[64];

  if ( r==0 ) {
    if ( c==0 ) { return this->a00; }
    if ( c==1 ) { return this->a01; }
    if ( c==2 ) { return this->a02; }
    snprintf( buf, 63, "column out of range: %lu expected (0, 1 or 2)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  if ( r==1 ) {
    if ( c==0 ) { return this->a10; }
    if ( c==1 ) { return this->a11; }
    if ( c==2 ) { return this->a12; }
    snprintf( buf, 63, "column out of range: %lu expected (0, 1 or 2)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  if ( r==2 ) {
    if ( c==0 ) { return this->a20; }
    if ( c==1 ) { return this->a21; }
    if ( c==2 ) { return this->a22; }
    snprintf( buf, 63, "column out of range: %lu expected (0, 1 or 2)", c );
    throw( new std::invalid_argument(buf) );
  }

  snprintf( buf, 63, "row out of range: %lu expected (0, 1 or 2)", r );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Index operator.
 *  @param r row    index.
 *  @param c column index.
 *  @return reference to the (r,c) position in this Matrix.
 */
// ---------------------------------------------------------------------------------------
real8_t& Matrix3D::operator()( const size_t r, const size_t c ) {
  // -------------------------------------------------------------------------------------
  char buf[64];

  if ( r==0 ) {
    if ( c==0 ) { return this->a00; }
    if ( c==1 ) { return this->a01; }
    if ( c==2 ) { return this->a02; }
    snprintf( buf, 63, "column out of range: %lu expected (0, 1 or 2)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  if ( r==1 ) {
    if ( c==0 ) { return this->a10; }
    if ( c==1 ) { return this->a11; }
    if ( c==2 ) { return this->a12; }
    snprintf( buf, 63, "column out of range: %lu expected (0, 1 or 2)", c );
    throw( new std::invalid_argument(buf) );
  }
  
  if ( r==2 ) {
    if ( c==0 ) { return this->a20; }
    if ( c==1 ) { return this->a21; }
    if ( c==2 ) { return this->a22; }
    snprintf( buf, 63, "column out of range: %lu expected (0, 1 or 2)", c );
    throw( new std::invalid_argument(buf) );
  }

  snprintf( buf, 63, "row out of range: %lu expected (0, 1 or 2)", r );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A pointer to the first  Matrix3D.
 *  @param[in] B pointer to the second Matrix3D.
 *  @return dot product of two matrices.
 *
 *  Dot product of a Matrix3D onto a Matrix3D.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D dot( const Matrix3D& A, const Matrix3D& B ) {
  // -------------------------------------------------------------------------------------
  
  return Matrix3D( A.a00*B.a00 + A.a01*B.a10 + A.a02*B.a20,
                   A.a00*B.a01 + A.a01*B.a11 + A.a02*B.a21,
                   A.a00*B.a02 + A.a01*B.a12 + A.a02*B.a22,
                   
                   A.a10*B.a00 + A.a11*B.a10 + A.a12*B.a20,
                   A.a10*B.a01 + A.a11*B.a11 + A.a12*B.a21,
                   A.a10*B.a02 + A.a11*B.a12 + A.a12*B.a22,
                   
                   A.a20*B.a00 + A.a21*B.a10 + A.a22*B.a20,
                   A.a20*B.a01 + A.a21*B.a11 + A.a22*B.a21,
                   A.a20*B.a02 + A.a21*B.a12 + A.a22*B.a22 );
}


// =======================================================================================
/** @brief Inverse.
 */
// ---------------------------------------------------------------------------------------
const Matrix3D Matrix3D::inverse( void ) {
  // -------------------------------------------------------------------------------------
  real8_t D = det();

  if ( isZero(D) ) {
    throw( new std::domain_error( "Singular Matrix" ) );
  }
  
  return Matrix3D( ((a11*a22) - (a21*a12)) / D,
                   ((a21*a02) - (a01*a22)) / D,
                   ((a01*a12) - (a11*a02)) / D,
                   
                   ((a20*a12) - (a10*a22)) / D,
                   ((a00*a22) - (a20*a02)) / D,
                   ((a10*a02) - (a00*a12)) / D,
                   
                   ((a10*a21) - (a20*a11)) / D,
                   ((a20*a01) - (a00*a21)) / D,
                   ((a00*a11) - (a10*a01)) / D );
}


// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t sum( const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  return
      M.a00 + M.a01 + M.a02 +
      M.a10 + M.a11 + M.a12 +
      M.a20 + M.a21 + M.a22;
}

// =======================================================================================
/** @brief Sum Squared.
 *  @return sum of the squares of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t sumsq( const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  return
      (M.a00*M.a00) + (M.a01*M.a01) + (M.a02*M.a02) + 
      (M.a10*M.a10) + (M.a11*M.a11) + (M.a12*M.a12) + 
      (M.a20*M.a20) + (M.a21*M.a21) + (M.a22*M.a22);
}


// =======================================================================================
/** @brief Sum Square.
 *  @param[in] A reference to the first  Matrix3D.
 *  @param[in] B reference to the second Matrix3D.
 *  @return Sum of the square differences of the elements.
 *  @nodet this is an alias of distsq
 */
// ---------------------------------------------------------------------------------------
real8_t sumsq( const Matrix3D& A, const Matrix3D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t d0 = (A.a00 - B.a00);
  real8_t d1 = (A.a01 - B.a01);
  real8_t d2 = (A.a02 - B.a02);
  real8_t d3 = (A.a10 - B.a10);
  real8_t d4 = (A.a11 - B.a11);
  real8_t d5 = (A.a12 - B.a12);
  real8_t d6 = (A.a20 - B.a20);
  real8_t d7 = (A.a21 - B.a21);
  real8_t d8 = (A.a22 - B.a22);
  return
      (d0*d0)+(d1*d1)+(d2*d2)+
      (d3*d3)+(d4*d4)+(d5*d5)+
      (d6*d6)+(d7*d7)+(d8*d8);
}


// =======================================================================================
// **                                  M A T R I X 3 D                                  **
// ======================================================================== END FILE =====
