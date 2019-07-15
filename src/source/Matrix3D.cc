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

#define INIT_VAR(a) m{0,0,0}, q{ a,a,a,a,a,a,a,a,a }


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q     pointer to array containing data.
 *  @param[in] order enum for format of data.
 *
 *  order: ROW_MAJOR, COLUMN_MAJOR, UPPER_TRIANGLE, LOWER_TRIANGLE
 */
// ---------------------------------------------------------------------------------------
Matrix3D::Matrix3D( const real8_t* _q, matrix3d_format_e order ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  setRowPointer();
  this->load( _q, order );
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m reference to source Matrix3D.
 */
// ---------------------------------------------------------------------------------------
Matrix3D::Matrix3D( const Matrix3D& _m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  setRowPointer();
  this->copy(_m);
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] m pointer to source Matrix3D.
 */
// ---------------------------------------------------------------------------------------
Matrix3D::Matrix3D( const Matrix3D* _m ) : INIT_VAR(D_ZERO) {
  // -------------------------------------------------------------------------------------
  setRowPointer();
  this->copy(_m);
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Matrix3D::~Matrix3D( void ) {
  // -------------------------------------------------------------------------------------
  this->set(D_ZERO);
  m[0] = static_cast<real8_t*>(0);
  m[1] = static_cast<real8_t*>(0);
  m[2] = static_cast<real8_t*>(0);
  
}


// =======================================================================================
/** @brief Set.
 *  @param s scalar value (default: 0)
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::set( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  q[0] = s;    q[1] = s;    q[2] = s;
  q[3] = s;    q[4] = s;    q[5] = s;
  q[6] = s;    q[7] = s;    q[8] = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::copy( const Matrix3D& that ) {
  // -------------------------------------------------------------------------------------
  this->q[0] = that.q[0];    this->q[1] = that.q[1];    this->q[2] = that.q[2];
  this->q[3] = that.q[3];    this->q[4] = that.q[4];    this->q[5] = that.q[5];
  this->q[6] = that.q[6];    this->q[7] = that.q[7];    this->q[8] = that.q[8];
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
  q[0] = A[0][0];    q[1] = A[0][1];    q[2] = A[0][2];
  q[3] = A[1][0];    q[4] = A[1][1];    q[5] = A[1][2];
  q[6] = A[2][0];    q[7] = A[2][1];    q[8] = A[2][2];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three by three element destination array.
 */
// ---------------------------------------------------------------------------------------
void Matrix3D::toArray( real8_t A[3][3] ) {
  // -------------------------------------------------------------------------------------
  A[0][0] = q[0];    A[0][1] = q[1];    A[0][2] = q[2];
  A[1][0] = q[3];    A[1][1] = q[4];    A[1][2] = q[5];
  A[2][0] = q[6];    A[2][1] = q[7];    A[2][2] = q[8];
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
  real8_t* p = const_cast<real8_t*>(src);
  
  switch(order) {
    case ROW_MAJOR:
      q[0] = *p++;    q[1] = *p++;    q[2] = *p++;
      q[3] = *p++;    q[4] = *p++;    q[5] = *p++;
      q[6] = *p++;    q[7] = *p++;    q[8] = *p++;
      break;

    case COLUMN_MAJOR:
      q[0] = *p++;    q[3] = *p++;    q[6] = *p++;
      q[1] = *p++;    q[4] = *p++;    q[7] = *p++;
      q[2] = *p++;    q[5] = *p++;    q[8] = *p++;
      break;

    case UPPER_TRIANGLE:
      q[0] = *p++;    q[1] = *p++;    q[2] = *p++;
      /*       */     q[4] = *p++;    q[5] = *p++;
      /*                        */    q[8] = *p++;
      q[3] = q[1];
      q[6] = q[2];
      q[7] = q[5];
      break;

    case LOWER_TRIANGLE:
      q[0] = *p++;
      q[3] = *p++;    q[4] = *p++;
      q[6] = *p++;    q[7] = *p++;    q[8] = *p++;
      q[1] = q[3];
      q[2] = q[6];
      q[5] = q[7];
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
real8_t* Matrix3D::store( const real8_t* dst, matrix3d_format_e order ) {
  // -------------------------------------------------------------------------------------
  real8_t* p = const_cast<real8_t*>(dst);
  
  switch(order) {
    case ROW_MAJOR:
      *p++ = q[0];    *p++ = q[1];    *p++ = q[2];
      *p++ = q[3];    *p++ = q[4];    *p++ = q[5];
      *p++ = q[6];    *p++ = q[7];    *p++ = q[8];
      break;

    case COLUMN_MAJOR:
      *p++ = q[0];    *p++ = q[3];    *p++ = q[6];
      *p++ = q[1];    *p++ = q[4];    *p++ = q[7];
      *p++ = q[2];    *p++ = q[5];    *p++ = q[8];
      break;

    case UPPER_TRIANGLE:
      *p++ = q[0];    *p++ = q[1];    *p++ = q[2];
      /*        */    *p++ = q[4];    *p++ = q[5];
      /*                        */    *p++ = q[8];
      break;

    case LOWER_TRIANGLE:
      *p++ = q[0];
      *p++ = q[3];    *p++ = q[4];
      *p++ = q[6];    *p++ = q[7];    *p++ = q[8];
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
  
  return Matrix3D( A.q[0]*B.q[0] + A.q[1]*B.q[3] + A.q[2]*B.q[6],
                   A.q[0]*B.q[1] + A.q[1]*B.q[4] + A.q[2]*B.q[7],
                   A.q[0]*B.q[2] + A.q[1]*B.q[5] + A.q[2]*B.q[8],
                   
                   A.q[3]*B.q[0] + A.q[4]*B.q[3] + A.q[5]*B.q[6],
                   A.q[3]*B.q[1] + A.q[4]*B.q[4] + A.q[5]*B.q[7],
                   A.q[3]*B.q[2] + A.q[4]*B.q[5] + A.q[5]*B.q[8],
                   
                   A.q[6]*B.q[0] + A.q[7]*B.q[3] + A.q[8]*B.q[6],
                   A.q[6]*B.q[1] + A.q[7]*B.q[4] + A.q[8]*B.q[7],
                   A.q[6]*B.q[2] + A.q[7]*B.q[5] + A.q[8]*B.q[8] );
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
  
  return Matrix3D( ((q[4]*q[8]) - (q[7]*q[5])) / D,
                   ((q[7]*q[2]) - (q[1]*q[8])) / D,
                   ((q[1]*q[5]) - (q[4]*q[2])) / D,
                   
                   ((q[6]*q[5]) - (q[3]*q[8])) / D,
                   ((q[0]*q[8]) - (q[6]*q[2])) / D,
                   ((q[3]*q[2]) - (q[0]*q[5])) / D,
                   
                   ((q[3]*q[7]) - (q[6]*q[4])) / D,
                   ((q[6]*q[1]) - (q[0]*q[7])) / D,
                   ((q[0]*q[4]) - (q[3]*q[1])) / D );
}


// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t sum( const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  return
      M.q[0] + M.q[1] + M.q[2] +
      M.q[3] + M.q[4] + M.q[5] +
      M.q[6] + M.q[7] + M.q[8];
}

// =======================================================================================
/** @brief Sum Squared.
 *  @return sum of the squares of the elements.
 */
// ---------------------------------------------------------------------------------------
real8_t sumsq( const Matrix3D& M ) {
  // -------------------------------------------------------------------------------------
  return
      (M.q[0]*M.q[0]) + (M.q[1]*M.q[1]) + (M.q[2]*M.q[2]) + 
      (M.q[3]*M.q[3]) + (M.q[4]*M.q[4]) + (M.q[5]*M.q[5]) + 
      (M.q[6]*M.q[6]) + (M.q[7]*M.q[7]) + (M.q[8]*M.q[8]);
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
  real8_t d0 = (A.q[0] - B.q[0]);
  real8_t d1 = (A.q[1] - B.q[1]);
  real8_t d2 = (A.q[2] - B.q[2]);
  real8_t d3 = (A.q[3] - B.q[3]);
  real8_t d4 = (A.q[4] - B.q[4]);
  real8_t d5 = (A.q[5] - B.q[5]);
  real8_t d6 = (A.q[6] - B.q[6]);
  real8_t d7 = (A.q[7] - B.q[7]);
  real8_t d8 = (A.q[8] - B.q[8]);
  return
      (d0*d0)+(d1*d1)+(d2*d2)+
      (d3*d3)+(d4*d4)+(d5*d5)+
      (d6*d6)+(d7*d7)+(d8*d8);
}


// =======================================================================================
// **                                  M A T R I X 3 D                                  **
// ======================================================================== END FILE =====
