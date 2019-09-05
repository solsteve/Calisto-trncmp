// ====================================================================== BEGIN FILE =====
// **                                     O R R E Y                                     **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  Model of the Solar System.
 *  @file   Orrey.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-14.
 *
 *  Provides a Model of the Solar System. All coordinates will Heliocentric.
 */
// =======================================================================================

#ifndef __HH_ORREY_TRNCMP
#define __HH_ORREY_TRNCMP

#include <trncmp.hh>

typedef enum { SUN, MERCURY, VENUS, EARTH, MARS, JUPITER,
               SATURN, URANUS, NEPTUNE, PLUTO } planet_e;

  // =======================================================================================
class Orrey {
  // -------------------------------------------------------------------------------------
 public:
  
  Orrey( void );
  ~Orrey( void );

  int      state  ( planet_e planet, real8_t* state );
  real8_t  mu     ( planet_e planet );
  real8_t  radius ( planet_e planet );
  
}; // end class Orrey


#endif


// =======================================================================================
// **                                     O R R E Y                                     **
// ======================================================================== END FILE =====
