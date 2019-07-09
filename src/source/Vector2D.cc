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
/** @brief  Three element vector.
 *  @file   Vector2D.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-28
 *
 *  Provides the methods for a three element vector.
 */
// =======================================================================================

#include <Vector2D.hh>
#include <stdexcept>

// =======================================================================================
/** @brief Load.
 *  @param src pointer to a source array.
 *  @return pointer next available element in the source array.
 *
 *  Load the three elements of this array from the next three positions in the source
 *  array and return the fourth position.
 */
// ---------------------------------------------------------------------------------------
real8_t* Vector2D::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = src[0];
  this->x[1] = src[1];
  return (src+2);
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
  real8_t* Vector2D::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  dst[0] = this->x[0];
  dst[1] = this->x[1];
  return (dst+2);
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return reference to the ith position in this vector.
 *
 *  x[0]=0, x[1]=1, z=2
 */
// ---------------------------------------------------------------------------------------
real8_t& Vector2D::at( const size_t i ) {
  // -------------------------------------------------------------------------------------
  if ( i==0 ) { return this->x[0]; }
  if ( i==1 ) { return this->x[1]; }
  char buf[64];
  snprintf( buf, 63, "out of range: %lu expected (0 or 1)", i );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return reference to the ith position in this vector.
 *
 *  x[0]=0, x[1]=1, z=2
 */
// ---------------------------------------------------------------------------------------
real8_t& Vector2D::operator[]( const size_t i ) {
  // -------------------------------------------------------------------------------------
  if ( i==0 ) { return this->x[0]; }
  if ( i==1 ) { return this->x[1]; }
  char buf[64];
  snprintf( buf, 63, "out of range: %lu expected (0 or 1)", i );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Normalize.
 *  @return new vector.
 *
 *  Return a Vector2D that is the normalization of this Vector2D.
 */
// ---------------------------------------------------------------------------------------
Vector2D Vector2D::normalize( void ) const {
  // -------------------------------------------------------------------------------------
  real8_t s = norm();
  if ( D_ZERO < s ) {
    return Vector2D( x[0]/s, x[1]/s );
  }
  throw( new std::domain_error( "Can not normalize a zero norm vector" ) );
}





// =======================================================================================
/** @brief toString.
 *  @param[in] v    reference to a vector.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] sdel column delimiter.
 *  @return string representation of the vector.
 *
 *  Format a Vector2D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Vector2D& v, std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  real8_t buf[2];
  v.store( buf );
  return toString( buf, 2, sfmt, sdel );
}


// =======================================================================================
/** @brief toString.
 *  @param[in] v    pointer to a vector.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] sdel column delimiter.
 *  @return string representation of the vector.
 *
 *  Format a Vector2D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Vector2D* v, std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  real8_t buf[2];
  v->store( buf );
  return toString( buf, 2, sfmt, sdel );
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] A reference to first  Vector2D.
 *  @param[in] B reference to second Vector2D.
 */
// ---------------------------------------------------------------------------------------
bool equals( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  if ( A.x[0] < B.x[0] ) { return false; }
  if ( A.x[0] > B.x[0] ) { return false; }
  if ( A.x[1] < B.x[1] ) { return false; }
  if ( A.x[1] > B.x[1] ) { return false; }
  return true;
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return L1 distance.
 */
// ---------------------------------------------------------------------------------------
real8_t dist1( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  return Abs(dx) + Abs(dy);
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
real8_t dist( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  return sqrt( (dx*dx) + (dy*dy) );
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return Square of the Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
real8_t distsq( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  return (dx*dx) + (dy*dy);
}


// =======================================================================================
/** @brief Angle.
 *  @param[in] A reference to the first  Vector2D.
 *  @param[in] B reference to the second Vector2D.
 *  @return Angle in radians.
 */
// ---------------------------------------------------------------------------------------
real8_t angle( const Vector2D& A, const Vector2D& B ) {
  // -------------------------------------------------------------------------------------
  const real8_t np = A.norm() * B.norm();

  if ( D_ZERO < np ) {
    real8_t dt = dot( A, B );
    real8_t th = np * 0.9999;
    if ( (dt < -th) || (dt > th) ) {
      real8_t C = cross(A,B);
      if ( dt < D_ZERO ) {
	return D_PI - asin( C / np );
      }
      return asin( C / np );
    }
    return acos( dt / np );
  }

  throw( new std::domain_error( "zero norm vector" ) );  
}


// =======================================================================================
// **                                  V E C T O R 2 D                                  **
// ======================================================================== END FILE =====
