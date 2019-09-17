// ====================================================================== BEGIN FILE =====
// **                   F U Z Z Y : : L E F T T R A P E Z O I D S E T                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2014-2019, Stephen W. Soliday                                      **
// **                           stephen.soliday@trncmp.org                              **
// **                           http://research.trncmp.org                              **
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
/** @brief  Left Trapezoid Fuzzy Set.
 *  @file   fuzzy/LeftTrapezoidSet.cc
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-08 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the methods for a derived left trapezoid fuzzy set.
 *
 *  1 ____
 *       |\
 *       | \
 *       |  \    Left Trapezoid Set
 *       |   \
 *       |    \____
 *  0 ===|===========
 *       C     R
 */
// =======================================================================================


#include <fuzzy/LeftTrapezoidSet.hh>


namespace fuzzy {


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
LeftTrapezoidSet::LeftTrapezoidSet( void ) : W(D_ZERO) {
  // -------------------------------------------------------------------------------------
  set( D_ZERO, D_ONE );
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
LeftTrapezoidSet::LeftTrapezoidSet( const real8_t a, const real8_t b ) : W(D_ZERO) {
  // -------------------------------------------------------------------------------------
  set( a, b );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
LeftTrapezoidSet::~LeftTrapezoidSet( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Set.
 *  @param[in] a first parameter.
 *  @param[in] b second parameter.
 *  @param[in] c optional third parameter.
 */
// ---------------------------------------------------------------------------------------
void LeftTrapezoidSet::set( const real8_t a, const real8_t b, const real8_t ) {
  // -------------------------------------------------------------------------------------
  C = a;
  R = b;

  W = R - C;
}


// =======================================================================================
/** @brief Membership.
 *  @param[in] x crisp value.
 *  @return degree of membership.
 *
 *  Compute the degree of membership in this LeftTrapezoidSet based on a crisp value x.
 *  The domain is all real numbers. The range is 0 to 1 inclusive.
 */
// ---------------------------------------------------------------------------------------
real8_t LeftTrapezoidSet::mu( const real8_t x ) {
  // -------------------------------------------------------------------------------------
  if ( x > C ) {
    if ( x < R ) {
      return (R - x)/W;
    } else {
      return D_ZERO;
    }
  }

  return D_ONE;
}


// =======================================================================================
/** @brief Area.
 *  @param[in] d degree of membership.
 *  @return area.
 *
 *  Compute the area under the degree of membership for this LeftTrapezoidSet.
 *  The domain is 0 to 1 inclusive. The range is 0 to max area for this LeftTrapezoidSet.
 */
// ---------------------------------------------------------------------------------------
real8_t LeftTrapezoidSet::area( const real8_t degree ) {
  // -------------------------------------------------------------------------------------
    return D_HALF*W*degree*(D_THREE-degree);
}


// =======================================================================================
/** @brief Center of area.
 *  @param[in] d degree of membership.
 *  @return center of area.
 *
 *  Compute the center of area based on the degree of membership in this LeftTrapezoidSet. 
 *  The domain is 0 to 1 inclusive. The range is (left) to (right) inclusive.
 */
// ---------------------------------------------------------------------------------------
real8_t LeftTrapezoidSet::coa( const real8_t degree ) {
  // -------------------------------------------------------------------------------------
  return ( D_NINE*(D_THREE*C + R) - (1.2e1*R - D_FOUR*W*degree)*degree )
        / (1.2e1*(D_THREE - degree));
}


// =======================================================================================
/** @brief To String.
 *  @param[in] fmt edit descriptor.
 *  @return parameters of this LeftTrapezoidSet as a string.
 */
// ---------------------------------------------------------------------------------------
std::string LeftTrapezoidSet::toString( std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string rs = "L(";
  rs.append( c_fmt( fmt, C ) );
  rs.append( "," );
  rs.append( c_fmt( fmt, R ) );
  rs.append( ")" );
  return rs;
}


// =======================================================================================
/** @brief Load.
 *  @param[in] src pointer to a source array.
 *  @return pointer to the next available data element.
 *
 *  Load the parameters for this LeftTrapezoidSet from a source array.
 */
// ---------------------------------------------------------------------------------------
real8_t* LeftTrapezoidSet::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  set( src[0], src[1] );
  return (src+2);
}


// =======================================================================================
/** @brief Store.
 *  @param[out] dst pointer to a destination array.
 *  @return pointer to the next available data element.
 *
 *  Store the parameters for this LeftTrapezoidSet from a source array.
 */
// ---------------------------------------------------------------------------------------
real8_t* LeftTrapezoidSet::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  dst[0] = C;
  dst[1] = R;
  return (dst+2);
}


}; // end namespace fuzzy


// =======================================================================================
// **                   F U Z Z Y : : L E F T T R A P E Z O I D S E T                   **
// ======================================================================== END FILE =====
