// ====================================================================== BEGIN FILE =====
// **                  F U Z Z Y : : R I G H T T R A P E Z O I D S E T                  **
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
/** @brief  Right Trapezoid Fuzzy Set.
 *  @file   fuzzy/RightTrapezoidSet.cc
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-08 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the methods for a derived right trapezoid fuzzy set.
 *
 *  1            ____
 *              /|
 *             / |
 *            /  |   Right Trapezoid Set
 *           /   |
 *      ____/    |
 *  0 ===========|====
 *          L    C
 */
// =======================================================================================


#include <fuzzy/RightTrapezoidSet.hh>


namespace fuzzy {


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
RightTrapezoidSet::RightTrapezoidSet( void ) : W(D_ZERO) {
  // -------------------------------------------------------------------------------------
  set( -D_ONE, D_ZERO );
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
RightTrapezoidSet::RightTrapezoidSet( const real8_t a, const real8_t b ) : W(D_ZERO) {
  // -------------------------------------------------------------------------------------
  set( a, b );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
RightTrapezoidSet::~RightTrapezoidSet( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Set.
 *  @param[in] a first parameter.
 *  @param[in] b second parameter.
 *  @param[in] c optional third parameter.
 */
// ---------------------------------------------------------------------------------------
void RightTrapezoidSet::set( const real8_t a, const real8_t b, const real8_t ) {
  // -------------------------------------------------------------------------------------
  L = a;
  C = b;

  W = C - L;
}


// =======================================================================================
/** @brief Membership.
 *  @param[in] x crisp value.
 *  @return degree of membership.
 *
 *  Compute the degree of membership in this RightTrapezoidSet based on a crisp value x.
 *  The domain is all real numbers. The range is 0 to 1 inclusive.
 */
// ---------------------------------------------------------------------------------------
real8_t RightTrapezoidSet::mu( const real8_t x ) {
  // -------------------------------------------------------------------------------------
    if ( x < C ) {
      if ( x > L ) {
        return (x - L)/W;
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
 *  Compute the area under the degree of membership for this RightTrapezoidSet.
 *  The domain is 0 to 1 inclusive. The range is 0 to max area for this RightTrapezoidSet.
 */
// ---------------------------------------------------------------------------------------
real8_t RightTrapezoidSet::area( const real8_t degree ) {
  // -------------------------------------------------------------------------------------
  return D_HALF*(D_THREE - degree)*W*degree;
}


// =======================================================================================
/** @brief Center of area.
 *  @param[in] d degree of membership.
 *  @return center of area.
 *
 *  Compute the center of area based on the degree of membership in this RightTrapezoidSet. 
 *  The domain is 0 to 1 inclusive. The range is (left) to (right) inclusive.
 */
// ---------------------------------------------------------------------------------------
real8_t RightTrapezoidSet::coa( const real8_t degree ) {
  // -------------------------------------------------------------------------------------
  return ( D_NINE*(D_THREE*C + L) - (D_FOUR*W*degree + 1.2e1*L)*degree )
        / (1.2e1*(D_THREE - degree));
}


// =======================================================================================
/** @brief To String.
 *  @param[in] fmt edit descriptor.
 *  @return parameters of this RightTrapezoidSet as a string.
 */
// ---------------------------------------------------------------------------------------
std::string RightTrapezoidSet::toString( std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string rs = "R(";
  rs.append( c_fmt( fmt, L ) );
  rs.append( "," );
  rs.append( c_fmt( fmt, C ) );
  rs.append( ")" );
  return rs;
}


// =======================================================================================
/** @brief Load.
 *  @param[in] src pointer to a source array.
 *  @return pointer to the next available data element.
 *
 *  Load the parameters for this RightTrapezoidSet from a source array.
 */
// ---------------------------------------------------------------------------------------
real8_t* RightTrapezoidSet::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  set( src[0], src[1] );
  return (src+2);
}


// =======================================================================================
/** @brief Store.
 *  @param[out] dst pointer to a destination array.
 *  @return pointer to the next available data element.
 *
 *  Store the parameters for this RightTrapezoidSet from a source array.
 */
// ---------------------------------------------------------------------------------------
real8_t* RightTrapezoidSet::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  dst[0] = L;
  dst[1] = C;
  return (dst+2);
}


}; // end namespace fuzzy


// =======================================================================================
// **                  F U Z Z Y : : R I G H T T R A P E Z O I D S E T                  **
// ======================================================================== END FILE =====
