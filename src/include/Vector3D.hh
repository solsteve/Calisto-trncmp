// ====================================================================== BEGIN FILE =====
// **                                  V E C T O R 3 D                                  **
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
/** @brief  Three element vector.
 *  @file   Vector3D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides the interface for a three element vector.
 */
// =======================================================================================

#ifndef __HH_VECTOR3D_TRNCMP
#define __HH_VECTOR3D_TRNCMP


#include <array_print.hh>


// =======================================================================================
class Vector3D {
  // -------------------------------------------------------------------------------------
 public:
  real8_t x[3];  ///< Abscissa, Ordinate andHeight.

  constexpr Vector3D( void );
  constexpr Vector3D( const real8_t _x, const real8_t _y, const real8_t _z );
  constexpr Vector3D( const real8_t*  q );
  constexpr Vector3D( const Vector3D& v );
  constexpr Vector3D( const Vector3D* v );

  ~Vector3D( void );

  Vector3D& operator=( const Vector3D& ) = default;

  void set( const real8_t s = D_ZERO );

  void copy ( const Vector3D& that );
  void copy ( const Vector3D* that );
  void copy ( const real8_t _x, const real8_t _y, const real8_t _z );

  void fromArray ( const real8_t A[3] );
  void toArray   ( real8_t A[3] );

  real8_t* load  ( real8_t* src );
  real8_t* store ( real8_t* dst );

  real8_t& at ( const size_t i );
  real8_t& operator[] ( const size_t i );

  void swap( Vector3D& that );

  // ----- scalar operations ------------------------------
  
  Vector3D& operator=  ( const real8_t s );
  Vector3D& operator+= ( const real8_t s );
  Vector3D& operator-= ( const real8_t s );
  Vector3D& operator*= ( const real8_t s );
  Vector3D& operator/= ( const real8_t s );

  // ----- vector operations ------------------------------
  
  Vector3D& operator+=  ( const Vector3D& v );
  Vector3D& operator-=  ( const Vector3D& v );
  Vector3D& operator*=  ( const Vector3D& v );
  Vector3D& operator/=  ( const Vector3D& v );

  real8_t  norm1  ( void ) const;
  real8_t  norm   ( void ) const;
  real8_t  normsq ( void ) const;

  Vector3D normalize( void ) const;

}; // end class Vector3D

std::string toString( Vector3D& v,
                      std::string sfmt = DEFAULT_PRINT_FORMAT,
                      std::string sdel = DEFAULT_PRINT_DELIM );
  
std::string toString( Vector3D* v,
                      std::string sfmt = DEFAULT_PRINT_FORMAT,
                      std::string sdel = DEFAULT_PRINT_DELIM );

bool    equals ( const Vector3D& A, const Vector3D& B );
bool    equals ( const Vector3D* A, const Vector3D* B );

real8_t dist1  ( const Vector3D& A, const Vector3D& B );
real8_t dist   ( const Vector3D& A, const Vector3D& B );
real8_t distsq ( const Vector3D& A, const Vector3D& B );

real8_t angle  ( const Vector3D& A, const Vector3D& B );

real8_t sum    ( const Vector3D& A );
real8_t sumsq  ( const Vector3D& A );
real8_t sumsq  ( const Vector3D& A, const Vector3D& B );

const Vector3D operator+( const real8_t&  s, const Vector3D& v );
const Vector3D operator+( const Vector3D& v, const real8_t&  s );
const Vector3D operator+( const Vector3D& A, const Vector3D& B );

const Vector3D operator-( const real8_t&  s, const Vector3D& v );
const Vector3D operator-( const Vector3D& v, const real8_t&  s );
const Vector3D operator-( const Vector3D& A, const Vector3D& B );

const Vector3D operator*( const real8_t&  s, const Vector3D& v );
const Vector3D operator*( const Vector3D& v, const real8_t&  s );
const Vector3D operator*( const Vector3D& A, const Vector3D& B );

const Vector3D operator/( const real8_t&  s, const Vector3D& v );
const Vector3D operator/( const Vector3D& v, const real8_t&  s );
const Vector3D operator/( const Vector3D& A, const Vector3D& B );

real8_t dot( const Vector3D& A, const Vector3D& B );
real8_t dot( const Vector3D* A, const Vector3D* B );

const Vector3D cross( const Vector3D& A, const Vector3D& B );
const Vector3D cross( const Vector3D* A, const Vector3D* B );


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return reference to the ith position in this vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t& Vector3D::at( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return x[i];
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return reference to the ith position in this vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t& Vector3D::operator[]( const size_t i ) {
  // -------------------------------------------------------------------------------------
  return x[i];
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] A pointer to first  Vector3D.
 *  @param[in] B pointer to second Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  bool equals( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return equals( *A, *B );
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Default constructor, all zeros.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( void ) : x{D_ZERO,D_ZERO,D_ZERO} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] _x abscissa value.
 *  @param[in] _y ordinate value.
 *  @param[in] _z height   value.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const real8_t _x, const real8_t _y, const real8_t _z ) :
x{_x,_y,_z} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q pointer to an array containing the three values.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const real8_t* q ) : x{q[0],q[1],q[2]} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v reference to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const Vector3D& v ) : x{v.x[0],v.x[1],v.x[2]} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v pointer to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const Vector3D* v ) : x{v->x[0],v->x[1],v->x[2]} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D::~Vector3D( void ) {
  // -------------------------------------------------------------------------------------
}



// =======================================================================================
/** @brief Set.
 *  @param s scalar value (default: 0)
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::set( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = s;
  this->x[1] = s;
  this->x[2] = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::copy ( const Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = that.x[0];
  this->x[1] = that.x[1];
  this->x[2] = that.x[2];
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v pointer to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::copy ( const Vector3D* that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = that->x[0];
  this->x[1] = that->x[1];
  this->x[2] = that->x[2];
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] _x abscissa value.
 *  @param[in] _y ordinate value.
 *  @param[in] _z height   value.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::copy ( const real8_t _x, const real8_t _y, const real8_t _z ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = _x;
  this->x[1] = _y;
  this->x[2] = _z;
}


// =======================================================================================
/** @brief From Array.
 *  @param[in] A reference to a three element source array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::fromArray ( const real8_t A[3] ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = A[0];
  this->x[1] = A[1];
  this->x[2] = A[2];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three element destination array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::toArray ( real8_t A[3] ) {
  // -------------------------------------------------------------------------------------
  A[0] = this->x[0];
  A[1] = this->x[1];
  A[2] = this->x[2];
}








// =======================================================================================
/** @brief Assignment.
 *  @param[in] s scalar value.
 *  @return reference to this Vector3D.
 *
 *  Set all three elements to the value of the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator=  ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = s;
  this->x[1] = s;
  this->x[2] = s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar addition.
 *  @param[in] s scalar value.
 *  @return reference to this Vector3D.
 *
 *  Add the scalar to all three elements of this Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator+= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x[0] += s;
  this->x[1] += s;
  this->x[2] += s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar subtraction.
 *  @param[in] s scalar value.
 *  @return reference to this Vector3D.
 *
 *  Subtract the scalar from all three elements of this Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator-= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x[0] -= s;
  this->x[1] -= s;
  this->x[2] -= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar multiplication.
 *  @param[in] s scalar value.
 *  @return reference to this Vector3D.
 *
 *  Multiply all three elements of this Vector3D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator*= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x[0] *= s;
  this->x[1] *= s;
  this->x[2] *= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar division.
 *  @param[in] s scalar value.
 *  @return reference to this Vector3D.
 *
 *  Divide all three elements of this Vector3D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator/= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x[0] /= s;
  this->x[1] /= s;
  this->x[2] /= s;
  return *this;
}








// =======================================================================================
/** @brief Inplace vector addition.
 *  @param[in] that reference to a Vector3D.
 *  @return reference to this Vector3D.
 *
 *  Element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator+= ( const Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] += that.x[0];
  this->x[1] += that.x[1];
  this->x[2] += that.x[2];
  return *this;
}


// =======================================================================================
/** @brief Inplace vector subtraction.
 *  @param[in] that reference to a Vector3D.
 *  @return reference to this Vector3D.
 *
 *  Element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator-= ( const Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] -= that.x[0];
  this->x[1] -= that.x[1];
  this->x[2] -= that.x[2];
  return *this;
}


// =======================================================================================
/** @brief Inplace vector multiplication.
 *  @param[in] that reference to a Vector3D.
 *  @return reference to this Vector3D.
 *
 *  Element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator*= ( const Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] *= that.x[0];
  this->x[1] *= that.x[1];
  this->x[2] *= that.x[2];
  return *this;
}


// =======================================================================================
/** @brief Inplace vector division.
 *  @param[in] that reference to a Vector3D.
 *  @return reference to this Vector3D.
 *
 *  Element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  Vector3D& Vector3D::operator/= ( const Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] /= that.x[0];
  this->x[1] /= that.x[1];
  this->x[2] /= that.x[2];
  return *this;
}


// =======================================================================================
/** @brief Swap.
 *  @param[inout] that reference to a vector.
 *
 *  Swap the contents of this with that.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::swap( Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  std::swap( this->x[0], that.x[0] );
  std::swap( this->x[1], that.x[1] );
  std::swap( this->x[2], that.x[2] );
}







// =======================================================================================
/** @brief Addition.
 *  @param s scalar value.
 *  @param v reference Vector3D.
 *  @return new vector.
 *
 *  Add a scalar value to each element of a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator+( const real8_t& s, const Vector3D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( v.x[0]+s, v.x[1]+s, v.x[2]+s );
}


// =======================================================================================
/** @brief Addition.
 *  @param v reference Vector3D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Add a scalar value to each element of a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator+( const Vector3D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( v.x[0]+s, v.x[1]+s, v.x[2]+s );
}


// =======================================================================================
/** @brief Addition.
 *  @param A reference Vector3D.
 *  @param B reference Vector3D.
 *  @return new vector.
 *
 *  Add two Vectors in element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator+( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( A.x[0]+B.x[0], A.x[1]+B.x[1], A.x[2]+B.x[2] );
}








// =======================================================================================
/** @brief Subtraction.
 *  @param s scalar value.
 *  @param v reference Vector3D.
 *  @return new vector.
 *
 *  Subtract each element of a Vector3D from the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator-( const real8_t& s, const Vector3D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( s-v.x[0], s-v.x[1], s-v.x[2] );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param v reference Vector3D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Subtract the same scalar value from each element of a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator-( const Vector3D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( v.x[0]-s, v.x[1]-s, v.x[2]-s );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param A reference Vector3D.
 *  @param B reference Vector3D.
 *  @return new vector.
 *
 *  Subtract two Vectors in element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator-( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( A.x[0]-B.x[0], A.x[1]-B.x[1], A.x[2]-B.x[2] );
}






// =======================================================================================
/** @brief Multiplication.
 *  @param s scalar value.
 *  @param v reference Vector3D.
 *  @return new vector.
 *
 *  Multiply each element of a Vector3D with the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator*( const real8_t& s, const Vector3D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( s*v.x[0], s*v.x[1], s*v.x[2] );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param v reference Vector3D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Multiply the same scalar value with each element of a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator*( const Vector3D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( v.x[0]*s, v.x[1]*s, v.x[2]*s );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param A reference Vector3D.
 *  @param B reference Vector3D.
 *  @return new vector.
 *
 *  Multiply two Vectors in element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator*( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( A.x[0]*B.x[0], A.x[1]*B.x[1], A.x[2]*B.x[2] );
}





// =======================================================================================
/** @brief Division.
 *  @param s scalar value.
 *  @param v reference Vector3D.
 *  @return new vector.
 *
 *  Divide the same scalar value by each element of a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator/( const real8_t& s, const Vector3D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( s/v.x[0], s/v.x[1], s/v.x[2] );
}


// =======================================================================================
/** @brief Division.
 *  @param v reference Vector3D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Divide the same scalar value by each element of a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator/( const Vector3D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( v.x[0]/s, v.x[1]/s, v.x[2]/s );
}


// =======================================================================================
/** @brief Division.
 *  @param A reference Vector3D.
 *  @param B reference Vector3D.
 *  @return new vector.
 *
 *  Divide two Vectors in element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D operator/( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( A.x[0]/B.x[0], A.x[1]/B.x[1], A.x[2]/B.x[2] );
}








// =======================================================================================
/** @brief Norm.
 *  @return L1 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline   real8_t Vector3D::norm1( void ) const {
  // -------------------------------------------------------------------------------------
  return Abs(x[0]) + Abs(x[1]) + Abs(x[2]);
}


// =======================================================================================
/** @brief Norm.
 *  @return L2 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline   real8_t Vector3D::norm( void ) const {
  // -------------------------------------------------------------------------------------
  return sqrt( (x[0]*x[0]) + (x[1]*x[1]) + (x[2]*x[2]) );
}


// =======================================================================================
/** @brief Norm Squared.
 *  @return square of the Euclidean norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline   real8_t Vector3D::normsq( void ) const {
  // -------------------------------------------------------------------------------------
  return (x[0]*x[0]) + (x[1]*x[1]) + (x[2]*x[2]);
}













// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return dot product of two vectors.
 *
 *  Dot product of a Vector3D onto a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dot( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  return ( A.x[0]*B.x[0] ) + ( A.x[1]*B.x[1] ) + ( A.x[2]*B.x[2] );
}


// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A pointer to the first  Vector3D.
 *  @param[in] B pointer to the second Vector3D.
 *  @return dot product of two vectors.
 *
 *  Dot product of a Vector3D onto a Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dot( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return dot( *A, *B );
}


// =======================================================================================
/** @brief Cross Product.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return cross product of two vectors.
 *
 *  Cross Vector3D A to Vector3D B.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D cross( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector3D( (A.x[1]*B.x[2]) - (A.x[2]*B.x[1]),
                   (A.x[2]*B.x[0]) - (A.x[0]*B.x[2]),
                   (A.x[0]*B.x[1]) - (A.x[1]*B.x[0]) );
}


// =======================================================================================
/** @brief Cross Product.
 *  @param[in] A pointer to the first  Vector3D.
 *  @param[in] B pointer to the second Vector3D.
 *  @return cross product of two vectors.
 *
 *  Cross Vector3D A to Vector3D B.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector3D cross( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return cross( *A, *B );
}

// =======================================================================================
/** @brief Distance.
 *  @param[in] A pointer to the first  Vector3D.
 *  @param[in] B pointer to the second Vector3D.
 *  @return L1 distance.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dist1( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return dist1( *A, *B );
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A pointer to the first  Vector3D.
 *  @param[in] B pointer to the second Vector3D.
 *  @return Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dist( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return dist( *A, *B );
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A pointer to the first  Vector3D.
 *  @param[in] B pointer to the second Vector3D.
 *  @return Square of the Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t distsq( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return distsq( *A, *B );
}


// =======================================================================================
/** @brief Angle.
 *  @param[in] A pointer to the first  Vector3D.
 *  @param[in] B pointer to the second Vector3D.
 *  @return Angle in radians.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t angle( const Vector3D* A, const Vector3D* B ) {
  // -------------------------------------------------------------------------------------
  return angle( *A, *B );
}


// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sum( const Vector3D& A ) {
  // -------------------------------------------------------------------------------------
  return A.x[0] + A.x[1] + A.x[2];
}

// =======================================================================================
/** @brief Sum Squared.
 *  @return sum of the squares of the elements.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sumsq( const Vector3D& A ) {
  // -------------------------------------------------------------------------------------
  return (A.x[0]*A.x[0]) + (A.x[1]*A.x[1]) + (A.x[2]*A.x[2]);
}


// =======================================================================================
/** @brief Sum Square.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return Sum of the square differences of the elements.
 *  @nodet this is an alias of distsq
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sumsq( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  real8_t dz = A.x[2] - B.x[2];
  return (dx*dx) + (dy*dy) + (dz*dz);
}


#endif


// =======================================================================================
// **                                  V E C T O R 3 D                                  **
// ======================================================================== END FILE =====
