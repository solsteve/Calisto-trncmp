// ====================================================================== BEGIN FILE =====
// **                        F U Z Z Y : : T R I A N G L E S E T                        **
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
/** @brief  Triangle Fuzzy Set.
 *  @file   fuzzy/TriangleSet.cc
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-08 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the methods for a derived triangle fuzzy set.
 *  
 *  1
 *              /|\
 *             / | \
 *            /  |  \   Triangle Set
 *           /   |   \
 *      ____/    |    \____
 *  0 ===========|===========
 *         L     C     R
 */
// =======================================================================================


#include <fuzzy/TriangleSet.hh>


namespace fuzzy {


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
TriangleSet::TriangleSet( void ) : LD(D_ZERO), RD(D_ZERO), W(D_ZERO) {
  // -------------------------------------------------------------------------------------
  set( -D_ONE, D_ZERO, D_ONE );
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
TriangleSet::TriangleSet( const real8_t a, const real8_t b, const real8_t c ) :
    LD(D_ZERO), RD(D_ZERO), W(D_ZERO) {
  // -------------------------------------------------------------------------------------
  set( a, b, c );
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
TriangleSet::~TriangleSet( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Set.
 *  @param[in] a first parameter.
 *  @param[in] b second parameter.
 *  @param[in] c optional third parameter.
 */
// ---------------------------------------------------------------------------------------
void TriangleSet::set( const real8_t a, const real8_t b, const real8_t c ) {
  // -------------------------------------------------------------------------------------
  L = a;
  C = b;
  R = c;

  LD = C - L;
  RD = R - C;
  W  = R - L;
}


// =======================================================================================
/** @brief Membership.
 *  @param[in] x crisp value.
 *  @return degree of membership.
 *
 *  Compute the degree of membership in this TriangleSet based on a crisp value x.
 *  The domain is all real numbers. The range is 0 to 1 inclusive.
 */
// ---------------------------------------------------------------------------------------
real8_t TriangleSet::mu( const real8_t x ) {
  // -------------------------------------------------------------------------------------
    if ( x < C ) {
      if ( x > L ) {
        return (x - L)/LD;
      } else {
        return D_ZERO;
      }
    }
    if ( x > C ) {
      if ( x < R ) {
        return (R - x)/RD;
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
 *  Compute the area under the degree of membership for this TriangleSet.
 *  The domain is 0 to 1 inclusive. The range is 0 to max area for this TriangleSet.
 */
// ---------------------------------------------------------------------------------------
real8_t TriangleSet::area( const real8_t degree ) {
  // -------------------------------------------------------------------------------------
  return D_HALF*W*degree*(D_TWO-degree);
}


// =======================================================================================
/** @brief Center of area.
 *  @param[in] d degree of membership.
 *  @return center of area.
 *
 *  Compute the center of area based on the degree of membership in this TriangleSet. 
 *  The domain is 0 to 1 inclusive. The range is (left) to (right) inclusive.
 */
// ---------------------------------------------------------------------------------------
real8_t TriangleSet::coa( const real8_t degree ) {
  // -------------------------------------------------------------------------------------
  return (D_THREE*(L+R) - (D_THREE*(R-C+L) - (R-D_TWO*C+L)*degree)*degree )
        / (D_THREE*(D_TWO-degree));
}


// =======================================================================================
/** @brief To String.
 *  @param[in] fmt edit descriptor.
 *  @return parameters of this TriangleSet as a string.
 */
// ---------------------------------------------------------------------------------------
std::string TriangleSet::toString( std::string fmt ) {
  // -------------------------------------------------------------------------------------
  std::string rs = "T(";
  rs.append( c_fmt( fmt, L ) );
  rs.append( "," );
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
 *  Load the parameters for this TriangleSet from a source array.
 */
// ---------------------------------------------------------------------------------------
real8_t* TriangleSet::load( real8_t* src ) {
  // -------------------------------------------------------------------------------------
  set( src[0], src[1], src[2] );
  return (src+3);
}


// =======================================================================================
/** @brief Store.
 *  @param[out] dst pointer to a destination array.
 *  @return pointer to the next available data element.
 *
 *  Store the parameters for this TriangleSet from a source array.
 */
// ---------------------------------------------------------------------------------------
real8_t* TriangleSet::store( real8_t* dst ) {
  // -------------------------------------------------------------------------------------
  dst[0] = L;
  dst[1] = C;
  dst[2] = R;
  return (dst+3);
}


}; // end namespace fuzzy


// =======================================================================================
// **                        F U Z Z Y : : T R I A N G L E S E T                        **
// ======================================================================== END FILE =====
