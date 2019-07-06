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
  real8_t x;  ///< Abscissa.
  real8_t y;  ///< Ordinate.
  real8_t z;  ///< Height.

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
  real8_t  sum    ( void ) const;

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
inline  constexpr Vector3D::Vector3D( void ) : x(D_ZERO), y(D_ZERO), z(D_ZERO) {
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
x(_x), y(_y), z(_z) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q pointer to an array containing the three values.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const real8_t* q ) : x(q[0]), y(q[1]), z(q[2]) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v reference to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const Vector3D& v ) : x(v.x), y(v.y), z(v.z) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v pointer to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector3D::Vector3D( const Vector3D* v ) : x(v->x), y(v->y), z(v->z) {
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
  this->x = s;
  this->y = s;
  this->z = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::copy ( const Vector3D& that ) {
  // -------------------------------------------------------------------------------------
  this->x = that.x;
  this->y = that.y;
  this->z = that.z;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v pointer to a source Vector3D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::copy ( const Vector3D* that ) {
  // -------------------------------------------------------------------------------------
  this->x = that->x;
  this->y = that->y;
  this->z = that->z;
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
  this->x = _x;
  this->y = _y;
  this->z = _z;
}


// =======================================================================================
/** @brief From Array.
 *  @param[in] A reference to a three element source array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::fromArray ( const real8_t A[3] ) {
  // -------------------------------------------------------------------------------------
  this->x = A[0];
  this->y = A[1];
  this->z = A[2];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three element destination array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector3D::toArray ( real8_t A[3] ) {
  // -------------------------------------------------------------------------------------
  A[0] = this->x;
  A[1] = this->y;
  A[2] = this->z;
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
  this->x = s;
  this->y = s;
  this->z = s;
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
  this->x += s;
  this->y += s;
  this->z += s;
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
  this->x -= s;
  this->y -= s;
  this->z -= s;
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
  this->x *= s;
  this->y *= s;
  this->z *= s;
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
  this->x /= s;
  this->y /= s;
  this->z /= s;
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
  this->x += that.x;
  this->y += that.y;
  this->z += that.z;
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
  this->x -= that.x;
  this->y -= that.y;
  this->z -= that.z;
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
  this->x *= that.x;
  this->y *= that.y;
  this->z *= that.z;
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
  this->x /= that.x;
  this->y /= that.y;
  this->z /= that.z;
  return *this;
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
  return Vector3D( v.x+s, v.y+s, v.z+s );
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
  return Vector3D( v.x+s, v.y+s, v.z+s );
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
  return Vector3D( A.x+B.x, A.y+B.y, A.z+B.z );
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
  return Vector3D( s-v.x, s-v.y, s-v.z );
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
  return Vector3D( v.x-s, v.y-s, v.z-s );
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
  return Vector3D( A.x-B.x, A.y-B.y, A.z-B.z );
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
  return Vector3D( s*v.x, s*v.y, s*v.z );
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
  return Vector3D( v.x*s, v.y*s, v.z*s );
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
  return Vector3D( A.x*B.x, A.y*B.y, A.z*B.z );
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
  return Vector3D( s/v.x, s/v.y, s/v.z );
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
  return Vector3D( v.x/s, v.y/s, v.z/s );
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
  return Vector3D( A.x/B.x, A.y/B.y, A.z/B.z );
}








// =======================================================================================
/** @brief Norm.
 *  @return L1 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline   real8_t Vector3D::norm1( void ) const {
  // -------------------------------------------------------------------------------------
  return Abs(x) + Abs(y) + Abs(z);
}


// =======================================================================================
/** @brief Norm.
 *  @return L2 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline   real8_t Vector3D::norm( void ) const {
  // -------------------------------------------------------------------------------------
  return sqrt( (x*x) + (y*y) + (z*z) );
}


// =======================================================================================
/** @brief Norm Squared.
 *  @return square of the Euclidean norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline   real8_t Vector3D::normsq( void ) const {
  // -------------------------------------------------------------------------------------
  return (x*x) + (y*y) + (z*z);
}


// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector3D::sum( void ) const {
  // -------------------------------------------------------------------------------------
  return x+y+z;
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
  return ( A.x*B.x ) + ( A.y*B.y ) + ( A.z*B.z );
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
  return Vector3D( (A.y*B.z) - (A.z*B.y),
                   (A.z*B.x) - (A.x*B.z),
                   (A.x*B.y) - (A.y*B.x) );
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


#endif


// =======================================================================================
// **                                  V E C T O R 3 D                                  **
// ======================================================================== END FILE =====
