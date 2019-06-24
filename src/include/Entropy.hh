// ====================================================================== BEGIN FILE =====
// **                                   E N T R O P Y                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2010-2019, Stephen W. Soliday                                      **
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
/** @brief  Entropy Base Class.
 *  @file   Entropy.hh
 *  @author Stephen W. Soliday
 *  @date   2010-01-01  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the abstract interface for entropy generation.
 */
// =======================================================================================


#ifndef __HH_ENTROPY_TRNCMP
#define __HH_ENTROPY_TRNCMP


#include <trncmp.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
class Entropy {
  // -------------------------------------------------------------------------------------
 protected:
  Entropy(void);

  void seed_map( u_int8_t* dst, size_t nd, void* vsrc, size_t ns );

 public:
  virtual ~Entropy (void);

  virtual void      seed_set  ( void* S, size_t n ) = 0;
  virtual size_t    seed_size ( void )              = 0;
  
  virtual u_int8_t  U8        ( void )              = 0;  ///<  8-bit  unsigned integer
  virtual u_int16_t U16       ( void )              = 0;  ///< 16-bit  unsigned integer
  virtual u_int32_t U32       ( void )              = 0;  ///< 32-bit  unsigned integer
  virtual u_int64_t U64       ( void )              = 0;  ///< 64-bit  unsigned integer
  virtual real4_t   R32       ( void )              = 0;  ///< 32-bit  floating point
  virtual real8_t   R64       ( void )              = 0;  ///< 64-bit  floating point

  static Entropy*   DEFAULT   ( void );

  void seed_set ( void );
}; // end class Entropy


#endif


// =======================================================================================
// **                                   E N T R O P Y                                   **
// ======================================================================== END FILE =====
