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
 *  Provides the methods for a three element vector.
 */
// =======================================================================================

#include <Vector3D.hh>
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
real8_t* Vector3D::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  this->x[0] = src[0];
  this->x[1] = src[1];
  this->x[2] = src[2];
  return (src+3);
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
  real8_t* Vector3D::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  dst[0] = this->x[0];
  dst[1] = this->x[1];
  dst[2] = this->x[2];
  return (dst+3);
}


// =======================================================================================
/** @brief Index operator.
 *  @param i index.
 *  @return reference to the ith position in this vector.
 *
 *  x[0]=0, x[1]=1, x[2]=2
 */
// ---------------------------------------------------------------------------------------
real8_t& Vector3D::at( const size_t i ) {
  // -------------------------------------------------------------------------------------
  if ( i==0 ) { return this->x[0]; }
  if ( i==1 ) { return this->x[1]; }
  if ( i==2 ) { return this->x[2]; }
  char buf[64];
  snprintf( buf, 63, "out of range: %lu expected (0, 1 or 2)", i );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Index[0] operator.
 *  @param i index[0].
 *  @return reference to the ith position in this vector.
 *
 *  x=0, x[1]=1, x[2]=2
 */
// ---------------------------------------------------------------------------------------
real8_t& Vector3D::operator[]( const size_t i ) {
  // -------------------------------------------------------------------------------------
  if ( i==0 ) { return this->x[0]; }
  if ( i==1 ) { return this->x[1]; }
  if ( i==2 ) { return this->x[2]; }
  char buf[64];
  snprintf( buf, 63, "out of range: %lu ex[0]pected (0, 1 or 2)", i );
  throw( new std::invalid_argument(buf) );
}


// =======================================================================================
/** @brief Normalize.
 *  @return new vector.
 *
 *  Return a Vector3D that is the normalization of this Vector3D.
 */
// ---------------------------------------------------------------------------------------
Vector3D Vector3D::normalize( void ) const {
  // -------------------------------------------------------------------------------------
  real8_t s = norm();
  if ( D_ZERO < s ) {
    return Vector3D( x[0]/s, x[1]/s, x[2]/s );
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
 *  Format a Vector3D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Vector3D& v, std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  real8_t buf[3];
  v.store( buf );
  return toString( buf, 3, sfmt, sdel );
}


// =======================================================================================
/** @brief toString.
 *  @param[in] v    pointer to a vector.
 *  @param[in] sfmt edit descriptor.
 *  @param[in] sdel column delimiter.
 *  @return string representation of the vector.
 *
 *  Format a Vector3D for printing and return an appropriate string.
 */
// ---------------------------------------------------------------------------------------
std::string toString( Vector3D* v, std::string sfmt, std::string sdel ) {
  // -------------------------------------------------------------------------------------
  real8_t buf[3];
  v->store( buf );
  return toString( buf, 3, sfmt, sdel );
}


// =======================================================================================
/** @brief Equals.
 *  @param[in] A reference to first  Vector3D.
 *  @param[in] B reference to second Vector3D.
 */
// ---------------------------------------------------------------------------------------
bool equals( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  if ( A.x[0] < B.x[0] ) { return false; }
  if ( A.x[0] > B.x[0] ) { return false; }
  if ( A.x[1] < B.x[1] ) { return false; }
  if ( A.x[1] > B.x[1] ) { return false; }
  if ( A.x[2] < B.x[2] ) { return false; }
  if ( A.x[2] > B.x[2] ) { return false; }
  return true;
}

// =======================================================================================
/** @brief Distance.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return L1 distance.
 */
// ---------------------------------------------------------------------------------------
real8_t dist1( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  real8_t dz = A.x[2] - B.x[2];
  return Abs(dx) + Abs(dy) + Abs(dz);
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
real8_t dist( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  real8_t dz = A.x[2] - B.x[2];
  return sqrt( (dx*dx) + (dy*dy) + (dz*dz) );
}


// =======================================================================================
/** @brief Distance.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return Square of the Euclidian distance.
 */
// ---------------------------------------------------------------------------------------
real8_t distsq( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  real8_t dx = A.x[0] - B.x[0];
  real8_t dy = A.x[1] - B.x[1];
  real8_t dz = A.x[2] - B.x[2];
  return (dx*dx) + (dy*dy) + (dz*dz);
}


// =======================================================================================
/** @brief Angle.
 *  @param[in] A reference to the first  Vector3D.
 *  @param[in] B reference to the second Vector3D.
 *  @return Angle in radians.
 *
 *  ArcTan2( norm(cross(a,b), dot(a,b)) )
 *  ArcCos( dot(a,b) / norm(a) / norm(b) )
 *  ArcSin( norm(cross((a,b)) / norm(a) / norm(b) )
 */
// ---------------------------------------------------------------------------------------
real8_t angle( const Vector3D& A, const Vector3D& B ) {
  // -------------------------------------------------------------------------------------
  const real8_t np = A.norm() * B.norm();

  if ( D_ZERO < np ) {
    real8_t dt = dot( A, B );
    real8_t th = np * 0.9999;
    if ( (dt < -th) || (dt > th) ) {
      Vector3D C = cross(A,B);
      if ( dt < D_ZERO ) {
	return D_PI - asin( C.norm() / np );
      }
      return asin( C.norm() / np );
    }
    return acos( dt / np );
  }

  throw( new std::domain_error( "zero norm vector" ) );  
}


// =======================================================================================
// **                                  V E C T O R 3 D                                  **
// ======================================================================== END FILE =====
