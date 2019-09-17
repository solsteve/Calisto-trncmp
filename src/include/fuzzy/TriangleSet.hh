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
 *  @file   fuzzy/TriangleSet.hh
 *  @author Stephen W. Soliday
 *  @date   2014-Jun-27 Original C++ release.
 *  @date   2018-Aug-08 Ported to Java.
 *  @date   2019-Sep-12 CMake refactorization.
 *
 *  Provides the interface for a derived triangle fuzzy set.
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


#ifndef __HH_FUZZY_TRIANGLESET_TRNCMP
#define __HH_FUZZY_TRIANGLESET_TRNCMP


#include <fuzzy/Set.hh>


namespace fuzzy {


// =======================================================================================
class TriangleSet : public Set {
  // -------------------------------------------------------------------------------------
 protected:

  real8_t LD, RD, W;  ///< Work variables.

 public:
  TriangleSet( void );
  TriangleSet( const real8_t a, const real8_t b, const real8_t c );
  virtual ~TriangleSet( void );

  virtual void        set      ( const real8_t a, const real8_t b, const real8_t c );
  virtual real8_t     mu       ( const real8_t x );
  virtual real8_t     area     ( const real8_t degree );
  virtual real8_t     coa      ( const real8_t degree );
  virtual std::string toString ( std::string fmt = "%g" );
  virtual real8_t*    load     ( real8_t* src );
  virtual real8_t*    store    ( real8_t* dst );
}; // end class TriangleSet


}; // end namespace fuzzy


#endif 


// =======================================================================================
// **                        F U Z Z Y : : T R I A N G L E S E T                        **
// ======================================================================== END FILE =====
