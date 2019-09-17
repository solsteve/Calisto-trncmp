// ====================================================================== BEGIN FILE =====
// **                                F U Z Z Y : : S E T                                **
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
/** @brief  Fuzzy Set.
 *  @file   fuzzy/Set.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-06 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides an abstract interface for a fuzzy set.
 */
// =======================================================================================


#ifndef __HH_FUZZY_SET_TRNCMP
#define __HH_FUZZY_SET_TRNCMP


#include <trncmp.hh>


namespace fuzzy {


// =======================================================================================
class Set {
  // -------------------------------------------------------------------------------------
 protected:

  real8_t L;  ///< Left extreme of this fuzzy set.
  real8_t C;  ///< Point of maximum membership extreme of this fuzzy set.
  real8_t R;  ///< Right extreme of this fuzzy set.

 public:
  Set( void );
  virtual ~Set( void );

  virtual real8_t     getLeft   ( void ) const;
  virtual real8_t     getCenter ( void ) const;
  virtual real8_t     getRight  ( void ) const;

  virtual void        set       ( const real8_t a, const real8_t b,
                                  const real8_t c = D_ZERO )     = 0;
  virtual real8_t     mu        ( const real8_t x )              = 0;
  virtual real8_t     area      ( const real8_t deg )            = 0;
  virtual real8_t     coa       ( const real8_t deg )            = 0;
  virtual std::string toString  ( std::string fmt = "%g" )       = 0;
  virtual real8_t*    load      ( real8_t* src )                 = 0;
  virtual real8_t*    store     ( real8_t* dst )                 = 0;
}; // end class Set

// =======================================================================================
inline  real8_t Set::getLeft( void ) const {
  // -------------------------------------------------------------------------------------
  return L;
}


// =======================================================================================
  inline  real8_t Set::getCenter( void ) const {
  // -------------------------------------------------------------------------------------
  return C;
}


// =======================================================================================
  inline  real8_t Set::getRight( void ) const {
  // -------------------------------------------------------------------------------------
  return R;
}

}; // end namespace fuzzy


#endif 


// =======================================================================================
// **                                F U Z Z Y : : S E T                                **
// ======================================================================== END FILE =====
