// ====================================================================== BEGIN FILE =====
// **                                  V E C T O R 2 D                                  **
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
/** @brief  Two element vector.
 *  @file   Vector2D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides the interface for a two element vector.
 */
// =======================================================================================

#ifndef __HH_VECTOR2D_TRNCMP
#define __HH_VECTOR2D_TRNCMP


#include <array_print.hh>


// =======================================================================================
class Vector2D {
  // -------------------------------------------------------------------------------------
public:
  real8_t x;  ///< Abscissa.
  real8_t y;  ///< Ordinate.

  constexpr Vector2D( void );
  constexpr Vector2D( const real8_t _x, const real8_t _y );
  constexpr Vector2D( const real8_t*  q );
  constexpr Vector2D( const Vector2D& v );
  constexpr Vector2D( const Vector2D* v );

  ~Vector2D( void );

  void set( const real8_t s = D_ZERO );

  void copy ( const Vector2D& that );
  void copy ( const Vector2D* that );
  void copy ( const real8_t _x, const real8_t _y );

  void fromArray ( const real8_t A[2] );
  void toArray   ( real8_t A[2] );

  real8_t* load  ( real8_t* src );
  real8_t* store ( real8_t* dst );

  real8_t& at         ( const size_t i );
  real8_t& operator[] ( const size_t i );

  Vector2D& operator=( const Vector2D& ) = default;

  // ----- scalar operations ------------------------------
  
  Vector2D& operator=  ( const real8_t s );
  Vector2D& operator+= ( const real8_t s );
  Vector2D& operator-= ( const real8_t s );
  Vector2D& operator*= ( const real8_t s );
  Vector2D& operator/= ( const real8_t s );

  Vector2D& operator+=  ( const Vector2D& v );
  Vector2D& operator-=  ( const Vector2D& v );
  Vector2D& operator*=  ( const Vector2D& v );
  Vector2D& operator/=  ( const Vector2D& v );

  real8_t  norm1  ( void ) const;
  real8_t  norm   ( void ) const;
  real8_t  normsq ( void ) const;
  real8_t  sum    ( void ) const;

  Vector2D normalize( void ) const;

}; // end class Vector2D

std::string toString( Vector2D& v,
                      std::string sfmt = DEFAULT_PRINT_FORMAT,
                      std::string sdel = DEFAULT_PRINT_DELIM );
  
std::string toString( Vector2D* v,
                      std::string sfmt = DEFAULT_PRINT_FORMAT,
                      std::string sdel = DEFAULT_PRINT_DELIM );
  

bool    equals ( const Vector2D& A, const Vector2D& B );

real8_t dist1  ( const Vector2D& A, const Vector2D& B );
real8_t dist   ( const Vector2D& A, const Vector2D& B );
real8_t distsq ( const Vector2D& A, const Vector2D& B );

real8_t angle  ( const Vector2D& A, const Vector2D& B );

const Vector2D operator+( const real8_t&  s, const Vector2D& v );
const Vector2D operator+( const Vector2D& v, const real8_t&  s );
const Vector2D operator+( const Vector2D& A, const Vector2D& B );

const Vector2D operator-( const real8_t&  s, const Vector2D& v );
const Vector2D operator-( const Vector2D& v, const real8_t&  s );
const Vector2D operator-( const Vector2D& A, const Vector2D& B );

const Vector2D operator*( const real8_t&  s, const Vector2D& v );
const Vector2D operator*( const Vector2D& v, const real8_t&  s );
const Vector2D operator*( const Vector2D& A, const Vector2D& B );

const Vector2D operator/( const real8_t&  s, const Vector2D& v );
const Vector2D operator/( const Vector2D& v, const real8_t&  s );
const Vector2D operator/( const Vector2D& A, const Vector2D& B );

  real8_t dot( const Vector2D& A, const Vector2D& B );
  real8_t dot( const Vector2D* A, const Vector2D* B );

  real8_t cross( const Vector2D& A, const Vector2D& B );
  real8_t cross( const Vector2D* A, const Vector2D* B );

// =======================================================================================
/** @brief Equals.
 *  @param[in] A pointer to first  Vector2D.
 *  @param[in] B pointer to second Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  bool equals( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return equals( *A, *B );
}


// =======================================================================================
/** @brief Constructor.
 *
 *  Default constructor, all zeros.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( void ) : x(D_ZERO), y(D_ZERO) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] _x abscissa value.
 *  @param[in] _y ordinate value.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const real8_t _x, const real8_t _y ) :
  x(_x), y(_y) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q pointer to an array containing the three values.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const real8_t* q ) : x(q[0]), y(q[1]) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v reference to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const Vector2D& v ) : x(v.x), y(v.y) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v pointer to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const Vector2D* v ) : x(v->x), y(v->y) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D::~Vector2D( void ) {
  // -------------------------------------------------------------------------------------
}








// =======================================================================================
/** @brief Set.
 *  @param s scalar value (default: 0)
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::set( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x = s;
  this->y = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::copy ( const Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  this->x = that.x;
  this->y = that.y;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v pointer to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::copy ( const Vector2D* that ) {
  // -------------------------------------------------------------------------------------
  this->x = that->x;
  this->y = that->y;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] _x abscissa value.
 *  @param[in] _y ordinate value.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::copy ( const real8_t _x, const real8_t _y ) {
  // -------------------------------------------------------------------------------------
  this->x = _x;
  this->y = _y;
}


// =======================================================================================
/** @brief From Array.
 *  @param[in] A reference to a three element source array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::fromArray ( const real8_t A[2] ) {
  // -------------------------------------------------------------------------------------
  this->x = A[0];
  this->y = A[1];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three element destination array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::toArray ( real8_t A[2] ) {
  // -------------------------------------------------------------------------------------
  A[0] = this->x;
  A[1] = this->y;
}








// =======================================================================================
/** @brief Assignment.
 *  @param[in] s scalar value.
 *  @return reference to this Vector2D.
 *
 *  Set all three elements to the value of the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x = s;
  this->y = s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar addition.
 *  @param[in] s scalar value.
 *  @return reference to this Vector2D.
 *
 *  Add the scalar to all three elements of this Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator+= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x += s;
  this->y += s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar subtraction.
 *  @param[in] s scalar value.
 *  @return reference to this Vector2D.
 *
 *  Subtract the scalar from all three elements of this Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator-= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x -= s;
  this->y -= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar multiplication.
 *  @param[in] s scalar value.
 *  @return reference to this Vector2D.
 *
 *  Multiply all three elements of this Vector2D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator*= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x *= s;
  this->y *= s;
  return *this;
}


// =======================================================================================
/** @brief Inplace scalar division.
 *  @param[in] s scalar value.
 *  @return reference to this Vector2D.
 *
 *  Divide all three elements of this Vector2D by the scalar.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator/= ( const real8_t s ) {
  // -------------------------------------------------------------------------------------
  this->x /= s;
  this->y /= s;
  return *this;
}








// =======================================================================================
/** @brief Inplace vector addition.
 *  @param[in] that reference to a Vector2D.
 *  @return reference to this Vector2D.
 *
 *  Element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator+= ( const Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  this->x += that.x;
  this->y += that.y;
  return *this;
}


// =======================================================================================
/** @brief Inplace vector subtraction.
 *  @param[in] that reference to a Vector2D.
 *  @return reference to this Vector2D.
 *
 *  Element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator-= ( const Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  this->x -= that.x;
  this->y -= that.y;
  return *this;
}


// =======================================================================================
/** @brief Inplace vector multiplication.
 *  @param[in] that reference to a Vector2D.
 *  @return reference to this Vector2D.
 *
 *  Element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator*= ( const Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  this->x *= that.x;
  this->y *= that.y;
  return *this;
}


// =======================================================================================
/** @brief Inplace vector division.
 *  @param[in] that reference to a Vector2D.
 *  @return reference to this Vector2D.
 *
 *  Element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  Vector2D& Vector2D::operator/= ( const Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  this->x /= that.x;
  this->y /= that.y;
  return *this;
}








// =======================================================================================
/** @brief Addition.
 *  @param s scalar value.
 *  @param v reference Vector2D.
 *  @return new vector.
 *
 *  Add a scalar value to each element of a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator+( const real8_t& s, const Vector2D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( v.x+s, v.y+s );
}


// =======================================================================================
/** @brief Addition.
 *  @param v reference Vector2D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Add a scalar value to each element of a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator+( const Vector2D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( v.x+s, v.y+s );
}


// =======================================================================================
/** @brief Addition.
 *  @param A reference Vector2D.
 *  @param B reference Vector2D.
 *  @return new vector.
 *
 *  Add two Vectors in element wise addition.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator+( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( A.x+B.x, A.y+B.y );
}








// =======================================================================================
/** @brief Subtraction.
 *  @param s scalar value.
 *  @param v reference Vector2D.
 *  @return new vector.
 *
 *  Subtract each element of a Vector2D from the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator-( const real8_t& s, const Vector2D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( s-v.x, s-v.y );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param v reference Vector2D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Subtract the same scalar value from each element of a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator-( const Vector2D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( v.x-s, v.y-s );
}


// =======================================================================================
/** @brief Subtraction.
 *  @param A reference Vector2D.
 *  @param B reference Vector2D.
 *  @return new vector.
 *
 *  Subtract two Vectors in element wise subtraction.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator-( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( A.x-B.x, A.y-B.y );
}






// =======================================================================================
/** @brief Multiplication.
 *  @param s scalar value.
 *  @param v reference Vector2D.
 *  @return new vector.
 *
 *  Multiply each element of a Vector2D with the same scalar value.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator*( const real8_t& s, const Vector2D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( s*v.x, s*v.y );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param v reference Vector2D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Multiply the same scalar value with each element of a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator*( const Vector2D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( v.x*s, v.y*s );
}


// =======================================================================================
/** @brief Multiplication.
 *  @param A reference Vector2D.
 *  @param B reference Vector2D.
 *  @return new vector.
 *
 *  Multiply two Vectors in element wise multiplication.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator*( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( A.x*B.x, A.y*B.y );
}





// =======================================================================================
/** @brief Division.
 *  @param s scalar value.
 *  @param v reference Vector2D.
 *  @return new vector.
 *
 *  Divide the same scalar value by each element of a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator/( const real8_t& s, const Vector2D& v ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( s/v.x, s/v.y );
}


// =======================================================================================
/** @brief Division.
 *  @param v reference Vector2D.
 *  @param s scalar value.
 *  @return new vector.
 *
 *  Divide the same scalar value by each element of a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator/( const Vector2D& v, const real8_t& s ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( v.x/s, v.y/s );
}


// =======================================================================================
/** @brief Division.
 *  @param A reference Vector2D.
 *  @param B reference Vector2D.
 *  @return new vector.
 *
 *  Divide two Vectors in element wise division.
 */
// ---------------------------------------------------------------------------------------
inline  const Vector2D operator/( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  return Vector2D( A.x/B.x, A.y/B.y );
}








// =======================================================================================
/** @brief Norm.
 *  @return L1 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::norm1( void ) const {
  // -------------------------------------------------------------------------------------
  return Abs(x) + Abs(y);
}


// =======================================================================================
/** @brief Norm.
 *  @return L2 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::norm( void ) const {
  // -------------------------------------------------------------------------------------
  return sqrt( (x*x) + (y*y) );
}


// =======================================================================================
/** @brief Norm Squared.
 *  @return square of the Euclidean norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::normsq( void ) const {
  // -------------------------------------------------------------------------------------
  return (x*x) + (y*y);
}

// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::sum( void ) const {
  // -------------------------------------------------------------------------------------
  return x+y;
}




// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return dot product of two vectors.
 *
 *  Dot product of a Vector2D onto a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dot( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  return ( A.x*B.x ) + ( A.y*B.y );
}


// =======================================================================================
/** @brief Dot Product.
 *  @param[in] A pointer to the first  Vector2D.
 *  @param[in] B pointer to the second Vector2D.
 *  @return dot product of two vectors.
 *
 *  Dot product of a Vector2D onto a Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dot( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return dot( *A, *B );
}


// =======================================================================================
/** @brief Cross Product.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return cross product of two vectors.
 *
 *  Cross Vector2D A to Vector2D B.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t cross( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  return (A.x*B.y) - (A.y*B.x);
}


// =======================================================================================
/** @brief Cross Product.
 *  @param[in] A pointer to the first  Vector2D.
 *  @param[in] B pointer to the second Vector2D.
 *  @return cross product of two vectors.
 *
 *  Cross Vector2D A to Vector2D B.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t cross( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return cross( *A, *B );
}






// =======================================================================================
/** @brief Distance.
 *  @param[in] A pointer to the first  Vector2D.
 *  @param[in] B pointer to the second Vector2D.
 *  @return L1 distance.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dist1( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return dist1( *A, *B );
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A pointer to the first  Vector2D.
 *  @param[in] B pointer to the second Vector2D.
 *  @return Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t dist( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return dist( *A, *B );
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A pointer to the first  Vector2D.
 *  @param[in] B pointer to the second Vector2D.
 *  @return Square of the Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t distsq( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return distsq( *A, *B );
}


// =======================================================================================
/** @brief Angle.
 *  @param[in] A pointer to the first  Vector2D.
 *  @param[in] B pointer to the second Vector2D.
 *  @return Angle in radians.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t angle( const Vector2D* A, const Vector2D* B ) {
  // -------------------------------------------------------------------------------------
  return angle( *A, *B );
}


#endif


// =======================================================================================
// **                                  V E C T O R 2 D                                  **
// ======================================================================== END FILE =====
