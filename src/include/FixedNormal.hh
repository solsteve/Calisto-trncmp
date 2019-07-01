// ====================================================================== BEGIN FILE =====
// **                               F I X E D N O R M A L                               **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2018-2019, Stephen W. Soliday                                      **
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
/** @brief Fixed / Normal Generator.
 *  @file   FixedNormal.hh
 *  @author Stephen W. Soliday
 *  @date   2018-Jan-03 Original (Java) release.
 *  @date   2019-Jun-28 C++ port.
 *
 *  Provides the interface for generating either a fixed number or a normal distribution.
 */
// =======================================================================================


#ifndef __HH_FIXEDNORMAL_TRNCMP
#define __HH_FIXEDNORMAL_TRNCMP

#include <Dice.hh>
#include <TLogger.hh>

// =======================================================================================
// ---------------------------------------------------------------------------------------
class FixedNormal {                                                         // FixedNormal
  // -------------------------------------------------------------------------------------
 protected:
  
  EMPTY_PROTOTYPE( FixedNormal );
  TLOGGER_HEADER( logger );

  bool    fixed;               ///< Flag if true this class returns a fixed value.
  real8_t mean_value;          ///< Mean value,  when fixed==flase.
  real8_t std_dev;             ///< Standard deviation.
  real8_t min_value;           ///< Minimum value generated.
  real8_t max_value;           ///< Maximum value generate.
  Dice*   dd ;                 ///< Pointer to a Dice instance.

  void init( bool flag, real8_t mean,
             real8_t std=D_ZERO, real8_t minv=D_ZERO, real8_t maxv=D_ZERO );
  
 public:

  FixedNormal     ( real8_t x );
  FixedNormal     ( real8_t mean, real8_t std );
  FixedNormal     ( real8_t mean, real8_t std, real8_t minv, real8_t maxv );
  FixedNormal     ( real8_t* param, size_t n );
  FixedNormal     ( std::string param );

  ~FixedNormal    ( void );

  real8_t next    ( void );
  int32_t nextInt ( void );

  void report( std::ostream& ps = std::cout );
  
}; // end class FixedNormal


#endif


// =======================================================================================
// **                               F I X E D N O R M A L                               **
// ======================================================================== END FILE =====
