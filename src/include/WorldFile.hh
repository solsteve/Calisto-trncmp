// ====================================================================== BEGIN FILE =====
// **                                 W O R L D F I L E                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2013-2019, Stephen W. Soliday                                      **
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
/** @brief  ESRI World File
 *  @file   WorldFile.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Aug-15.
 *
 *  Provides the interface for a class to maintain coordinate trainsforms.
 */
// =======================================================================================


#ifndef __HH_WORLDFILE_TRNCMP
#define __HH_WORLDFILE_TRNCMP

#include <trncmp.hh>


// =======================================================================================
class WorldFile {
  // -------------------------------------------------------------------------------------
 protected:
  real8_t data[3][2];

  void destroy( void );
  
 public:
  WorldFile ( void );
  WorldFile ( std::string fspc );
  ~WorldFile ( void );

  int read  ( std::string fspc );
  int write ( std::string fspc );

  void fromGDAL( real8_t g[6] );

  /** x-component  of pixel width  (x-scale) */
  real8_t A( void )      { return data[0][0]; };
  void    A( real8_t v ) {        data[0][0] = v; };
  
  /** y-component  of pixel width  (y-skew) */
  real8_t B( void )      { return data[1][0]; };
  void    B( real8_t v ) {        data[1][0] = v; };
  
  /** y-component  of pixel height (x-skew) */
  real8_t C( void )      { return data[2][0]; };
  void    C( real8_t v ) {        data[2][0] = v; };
  
  /** y-component  of pixel height (y-scale) */
  real8_t D( void )      { return data[0][1]; };
  void    D( real8_t v ) {        data[0][1] = v; };
  
  /** UTM Easting  of the center of the upper left pixel */
  real8_t E( void )      { return data[1][1]; };
  void    E( real8_t v ) {        data[1][1] = v; };
  
  /** UTM Northing of the center of the upper left pixel */
  real8_t F( void )      { return data[2][1]; };
  void    F( real8_t v ) {        data[2][1] = v; };
};

#endif


// =======================================================================================
// **                                 W O R L D F I L E                                 **
// ======================================================================== END FILE =====
