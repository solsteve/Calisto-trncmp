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
 *  @file   fuzzy/LeftTrapezoidSet.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-08 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the interface for a derived left trapezoid fuzzy set.
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


#ifndef __HH_FUZZY_LEFTTRAPEZOIDSET_TRNCMP
#define __HH_FUZZY_LEFTTRAPEZOIDSET_TRNCMP


#include <fuzzy/Set.hh>


namespace fuzzy {


// =======================================================================================
class LeftTrapezoidSet : public Set {
  // -------------------------------------------------------------------------------------
 protected:

  real8_t W;  ///< Work variable.

 public:
  LeftTrapezoidSet( void );
  LeftTrapezoidSet( const real8_t a, const real8_t b );
  virtual ~LeftTrapezoidSet( void );

  virtual void        set      ( const real8_t a, const real8_t b,
                                 const real8_t c = D_ZERO );
  
  virtual real8_t     getLeft  ( void ) const;

  virtual real8_t     mu       ( const real8_t x );
  virtual real8_t     area     ( const real8_t degree );
  virtual real8_t     coa      ( const real8_t degree );
  virtual std::string toString ( std::string fmt = "%g" );
  virtual real8_t*    load     ( real8_t* src );
  virtual real8_t*    store    ( real8_t* dst );
}; // end class LeftTrapezoidSet


// =======================================================================================
inline  real8_t LeftTrapezoidSet::getLeft( void ) const {
  // -------------------------------------------------------------------------------------
  return D_HALF*(D_THREE*C - R);
}


}; // end namespace fuzzy


#endif 


// =======================================================================================
// **                   F U Z Z Y : : L E F T T R A P E Z O I D S E T                   **
// ======================================================================== END FILE =====
