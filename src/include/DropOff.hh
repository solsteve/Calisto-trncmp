// ====================================================================== BEGIN FILE =====
// **                                   D R O P O F F                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2016-2019, Stephen W. Soliday                                      **
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
/** @brief  Drop Off Generator.
 *  @file   DropOff.hh
 *  @author Stephen W. Soliday
 *  @date   2016-Aug-09 Original release.
 *  @date   2019-Jun-27 CMake refactorization.
 *
 *  Provides the interface for a drop off generator.
 */
// =======================================================================================

#ifndef __HH_DROPOFF_TRNCMP
#define __HH_DROPOFF_TRNCMP

#include <trncmp.hh>

// =======================================================================================
class DropOff {
  // -------------------------------------------------------------------------------------
public:
  enum drop_type { LINEAR=0, EXPONENTIAL=1, GAUSSIAN=2 };
  
protected:
  size_t    index;
  real8_t   A;
  real8_t   B;
  drop_type d_type;
  
public:
  DropOff       ( real8_t Vo, real8_t Vf, size_t n, drop_type dt=LINEAR );
  ~DropOff      ( void );
  real8_t next  ( void );
  
  real8_t get   ( size_t n );
  void    reset ( void );
};

#endif

// =======================================================================================
// **                                   D R O P O F F                                   **
// ======================================================================== END FILE =====
