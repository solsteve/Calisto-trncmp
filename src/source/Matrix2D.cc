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

#define INIT_VAR(a) m{0,0}, q{a,a,a,a}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q     pointer to array containing data.
 *  @param[in] order enum for format of data.
 *
 *  order: ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE
 */
// ---------------------------------------------------------------------------------------
Matrix2D::Matrix2D( const real8_t* _q, matrix2d_format_e order ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  setRowPointer();
  this->load( _q, order );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m reference to source Matrix2D.
 */
// ---------------------------------------------------------------------------------------
Matrix2D::Matrix2D( const Matrix2D& _m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  setRowPointer();
  this->copy(_m);
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m pointer to source Matrix2D.
 */
// ---------------------------------------------------------------------------------------
Matrix2D::Matrix2D( const Matrix2D* _m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  setRowPointer();
  this->copy(_m);
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
  q[0] = s;    q[1] = s;
  q[2] = s;    q[3] = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::copy( const Matrix2D& that ) {
  // -------------------------------------------------------------------------------------
  this->q[0] = that.q[0];    this->q[1] = that.q[1];
  this->q[2] = that.q[2];    this->q[3] = that.q[3];
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] that reference to another Matrix2D.
 *  @return true if Matrices are element by element equal.
 */
// ---------------------------------------------------------------------------------------
bool Matrix2D::equals( const Matrix2D& that, const real8_t eps ) const {
  // -------------------------------------------------------------------------------------
  for ( size_t i=0; i<4; i++ ) {
    const real8_t dif = this->q[i] - that.q[i];
    if ( dif < -eps ) { return false; }
    if ( dif >  eps ) { return false; }
  }
  return true;
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
  q[0] = A[0][0];    q[1] = A[0][1];
  q[2] = A[1][0];    q[3] = A[1][1];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three by three element destination array.
 */
// ---------------------------------------------------------------------------------------
void Matrix2D::toArray( real8_t A[2][2] ) {
  // -------------------------------------------------------------------------------------
  A[0][0] = q[0];    A[0][1] = q[1];
  A[1][0] = q[2];    A[1][1] = q[3];
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
  real8_t* p = const_cast<real8_t*>(src);
  
  switch(order) {
    case ROW_MAJOR:
      q[0] = *p++;    q[1] = *p++;
      q[2] = *p++;    q[3] = *p++;
      break;

    case COLUMN_MAJOR:
      q[0] = *p++;    q[2] = *p++;
      q[1] = *p++;    q[3] = *p++;
      break;

    case UPPER_TRIANGLE:
      q[0] = *p++;    q[1] = *p++;
      /*        */    q[3] = *p++;
      q[2] = q[1];
      break;

    case LOWER_TRIANGLE:
      q[0] = *p++;
      q[2] = *p++;    q[3] = *p++;
      q[1] = q[2];
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
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
real8_t* Matrix2D::store( real8_t* dst, matrix2d_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* p = dst;
  
  switch(order) {
    case ROW_MAJOR:
      *p++ = q[0];    *p++ = q[1];
      *p++ = q[2];    *p++ = q[3];
      break;

    case COLUMN_MAJOR:
      *p++ = q[0];    *p++ = q[2];
      *p++ = q[1];    *p++ = q[3];
      break;

    case UPPER_TRIANGLE:
      *p++ = q[0];    *p++ = q[1];
      /*       */     *p++ = q[3];
      break;

    case LOWER_TRIANGLE:
      *p++ = q[0];
      *p++ = q[2];    *p++ = q[3];
      break;

    default:
      std::cerr << "This Should not be possible\n";
      throw 1;
  }
  
  return p;
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
  real8_t *Q[2] = { (buffer+0), (buffer+3) };
  M.store( buffer, ROW_MAJOR );
  return toString( Q, 2, 2, sfmt, cdel, rdel );
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
  
  return Matrix2D( (A.q[0]*B.q[0]) + (A.q[1]*B.q[2]),
                   (A.q[0]*B.q[1]) + (A.q[1]*B.q[3]),
                   (A.q[2]*B.q[0]) + (A.q[3]*B.q[2]),
                   (A.q[2]*B.q[1]) + (A.q[3]*B.q[3]) );
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
  
  return Matrix2D(  q[3] / D, -q[1] / D,
                   -q[2] / D,  q[0] / D );
}


// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t sum( const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
  return
      M.q[0] + M.q[1] +
      M.q[2] + M.q[3];
}

// =======================================================================================
/** @brief Sum Squared.
 *  @return sum of the squares of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t sumsq( const Matrix2D& M ) {
  // -------------------------------------------------------------------------------------
  return
      (M.q[0]*M.q[0]) + (M.q[1]*M.q[1]) + 
      (M.q[2]*M.q[2]) + (M.q[3]*M.q[3]);
}


// =======================================================================================
/** @brief Sum Square.
 *  @param[in] A reference to the first  Matrix2D.
 *  @param[in] B reference to the second Matrix2D.
 *  @return Sum of the square differences of the elements.
 *  @nodet this is an alias of distsq
 */
// ---------------------------------------------------------------------------------------
real8_t sumsq( const Matrix2D& A, const Matrix2D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t d0 = (A.q[0] - B.q[0]);
  real8_t d1 = (A.q[1] - B.q[1]);
  real8_t d2 = (A.q[2] - B.q[2]);
  real8_t d3 = (A.q[3] - B.q[3]);
  return (d0*d0)+(d1*d1)+(d2*d2)+(d3*d3);
}


// =======================================================================================
// **                                  M A T R I X 2 D                                  **
// ======================================================================== END FILE =====
