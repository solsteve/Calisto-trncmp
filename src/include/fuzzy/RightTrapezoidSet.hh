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
 *  @file   fuzzy/RightTrapezoidSet.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-08 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the interface for a derived right trapezoid fuzzy set.
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


#ifndef __HH_FUZZY_RIGHTTRAPEZOIDSET_TRNCMP
#define __HH_FUZZY_RIGHTTRAPEZOIDSET_TRNCMP


#include <fuzzy/Set.hh>


namespace fuzzy {


// =======================================================================================
class RightTrapezoidSet : public Set {
  // -------------------------------------------------------------------------------------
 protected:

  real8_t W;  ///< Work variable.

 public:
  RightTrapezoidSet( void );
  RightTrapezoidSet( const real8_t a, const real8_t b );
  virtual ~RightTrapezoidSet( void );

  virtual void        set      ( const real8_t a, const real8_t b,
                                 const real8_t c = D_ZERO );

  virtual real8_t     getRight ( void ) const;

  virtual real8_t     mu       ( const real8_t x );
  virtual real8_t     area     ( const real8_t deg );
  virtual real8_t     coa      ( const real8_t deg );
  virtual std::string toString ( std::string fmt = "%g" );
  virtual real8_t*    load     ( real8_t* src );
  virtual real8_t*    store    ( real8_t* dst );
}; // end class RightTrapezoidSet


// =======================================================================================
inline  real8_t RightTrapezoidSet::getRight( void ) const {
  // -------------------------------------------------------------------------------------
  return D_HALF*(D_THREE*C-L);
}


}; // end namespace fuzzy


#endif 


// =======================================================================================
// **                  F U Z Z Y : : R I G H T T R A P E Z O I D S E T                  **
// ======================================================================== END FILE =====
