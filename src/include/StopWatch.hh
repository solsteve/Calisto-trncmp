// ====================================================================== BEGIN FILE =====
// **                                 S T O P W A T C H                                 **
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
/** @brief  Stop Watch
 *  @file   StopWatch.hh
 *  @author Stephen W. Soliday
 *  @date   2014-01-27  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for precision time keeping.
 */
// =======================================================================================


#ifndef __HH_STOPWATCH_TRNCMP
#define __HH_STOPWATCH_TRNCMP


#include <trncmp.hh>
#include <time.h>


// =======================================================================================
/** @brief Stop Watch.
 */
// ---------------------------------------------------------------------------------------
class StopWatch {
  // -------------------------------------------------------------------------------------
private:
  clock_t start_time;  ///< Start time in CPU clock ticks

public:
  StopWatch     ( void ) : start_time(0) { };
  ~StopWatch    ( void ) {};

  void    reset ( void );
  real8_t check ( void );
  
}; // end class StopWatch


// ==========================================================================================
/** @brief Reset.
 *
 *  Start the timmer.
 */
// ------------------------------------------------------------------------------------------
inline  void StopWatch::reset( void ) {
  // ----------------------------------------------------------------------------------------
  start_time = clock();
}


// ==========================================================================================
/** @brief Elapse.
 *  @return Elapsed time in seconds.
 *
 *  Return the time that elapsed between reset and now.
 */
// ------------------------------------------------------------------------------------------
inline  real8_t StopWatch::check( void ) {
  // ----------------------------------------------------------------------------------------
  return (real8_t)(clock() - start_time) / (real8_t) CLOCKS_PER_SEC;
}


#endif 

  
// =======================================================================================
// **                                 S T O P W A T C H                                 **
// ======================================================================== END FILE =====
