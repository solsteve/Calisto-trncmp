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
  real8_t x[2];  ///< Abscissa and Ordinate.

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

  void     swap       ( Vector2D& M );

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

real8_t sum    ( const Vector2D& A );
real8_t sumsq  ( const Vector2D& A );
real8_t sumsq  ( const Vector2D& A, const Vector2D& B );

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
inline  constexpr Vector2D::Vector2D( void ) : x{D_ZERO,D_ZERO} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] _x abscissa value.
 *  @param[in] _y ordinate value.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const real8_t _x, const real8_t _y ) :
  x{_x,_y} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] q pointer to an array containing the three values.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const real8_t* q ) : x{q[0],q[1]} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v reference to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const Vector2D& v ) : x{v.x[0],v.x[1]} {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] v pointer to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  constexpr Vector2D::Vector2D( const Vector2D* v ) : x{v->x[0],v->x[1]} {
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
  this->x[0] = s;
  this->x[1] = s;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v reference to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::copy ( const Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = that.x[0];
  this->x[1] = that.x[1];
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] v pointer to a source Vector2D.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::copy ( const Vector2D* that ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = that->x[0];
  this->x[1] = that->x[1];
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] _x abscissa value.
 *  @param[in] _y ordinate value.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::copy ( const real8_t _x, const real8_t _y ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = _x;
  this->x[1] = _y;
}


// =======================================================================================
/** @brief From Array.
 *  @param[in] A reference to a three element source array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::fromArray ( const real8_t A[2] ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = A[0];
  this->x[1] = A[1];
}


// =======================================================================================
/** @brief To Array.
 *  @param[in] A reference to a three element destination array.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::toArray ( real8_t A[2] ) {
  // -------------------------------------------------------------------------------------
  A[0] = this->x[0];
  A[1] = this->x[1];
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
  this->x[0] = s;
  this->x[1] = s;
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
  this->x[0] += s;
  this->x[1] += s;
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
  this->x[0] -= s;
  this->x[1] -= s;
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
  this->x[0] *= s;
  this->x[1] *= s;
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
  this->x[0] /= s;
  this->x[1] /= s;
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
  this->x[0] += that.x[0];
  this->x[1] += that.x[1];
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
  this->x[0] -= that.x[0];
  this->x[1] -= that.x[1];
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
  this->x[0] *= that.x[0];
  this->x[1] *= that.x[1];
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
  this->x[0] /= that.x[0];
  this->x[1] /= that.x[1];
  return *this;
}

// =======================================================================================
/** @brief Swap.
 *  @param[inout] that reference to a vector.
 *
 *  Swap the contents of this with that.
 */
// ---------------------------------------------------------------------------------------
inline  void Vector2D::swap( Vector2D& that ) {
  // -------------------------------------------------------------------------------------
  ::swap( this->x[0], that.x[0] );
  ::swap( this->x[1], that.x[1] );
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
  return Vector2D( v.x[0]+s, v.x[1]+s );
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
  return Vector2D( v.x[0]+s, v.x[1]+s );
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
  return Vector2D( A.x[0]+B.x[0], A.x[1]+B.x[1] );
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
  return Vector2D( s-v.x[0], s-v.x[1] );
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
  return Vector2D( v.x[0]-s, v.x[1]-s );
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
  return Vector2D( A.x[0]-B.x[0], A.x[1]-B.x[1] );
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
  return Vector2D( s*v.x[0], s*v.x[1] );
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
  return Vector2D( v.x[0]*s, v.x[1]*s );
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
  return Vector2D( A.x[0]*B.x[0], A.x[1]*B.x[1] );
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
  return Vector2D( s/v.x[0], s/v.x[1] );
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
  return Vector2D( v.x[0]/s, v.x[1]/s );
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
  return Vector2D( A.x[0]/B.x[0], A.x[1]/B.x[1] );
}








// =======================================================================================
/** @brief Norm.
 *  @return L1 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::norm1( void ) const {
  // -------------------------------------------------------------------------------------
  return Abs(x[0]) + Abs(x[1]);
}


// =======================================================================================
/** @brief Norm.
 *  @return L2 norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::norm( void ) const {
  // -------------------------------------------------------------------------------------
  return sqrt( (x[0]*x[0]) + (x[1]*x[1]) );
}


// =======================================================================================
/** @brief Norm Squared.
 *  @return square of the Euclidean norm for the vector.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Vector2D::normsq( void ) const {
  // -------------------------------------------------------------------------------------
  return (x[0]*x[0]) + (x[1]*x[1]);
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
  return ( A.x[0]*B.x[0] ) + ( A.x[1]*B.x[1] );
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
  return (A.x[0]*B.x[1]) - (A.x[1]*B.x[0]);
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


// =======================================================================================
/** @brief Sum.
 *  @return sum of the elements.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sum( const Vector2D& A ) {
  // -------------------------------------------------------------------------------------
  return A.x[0] + A.x[1];
}

// =======================================================================================
/** @brief Sum Squared.
 *  @return sum of the squares of the elements.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sumsq( const Vector2D& A ) {
  // -------------------------------------------------------------------------------------
  return (A.x[0]*A.x[0]) + (A.x[1]*A.x[1]);
}


// =======================================================================================
/** @brief Sum Square.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return Sum of the square differences of the elements.
 *  @nodet this is an alias of distsq
 */
// ---------------------------------------------------------------------------------------
inline  real8_t sumsq( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  return (dx*dx) + (dy*dy);
}


#endif


// =======================================================================================
// **                                  V E C T O R 2 D                                  **
// ======================================================================== END FILE =====
