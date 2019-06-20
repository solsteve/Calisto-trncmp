// ====================================================================== BEGIN FILE =====
// **                                 S T O P W A T C H                                 **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2014, 19  Stephen W. Soliday                                       **
// **                          stephen.soliday@trncmp.org                               **
// **                          http://research.trncmp.org                               **
// **                                                                                   **
// **  -------------------------------------------------------------------------------  **
// **                                                                                   **
// **  This file, and associated source code, is not free software; you may not         **
// **  redistribute it and/or modify it. This library is currently in an on going       **
// **  development phase by its author and has, as yet, not been publicly distributed.  **
// **  Development of this library has been at the sole cost in both time and funding   **
// **  by its author. Until such a public release is made the author retains ALL RIGHTS **
// **  to this software. It is expected that if and when this library is deemed         **
// **  releasable it will be released under the GNU Public license for non-commercial   **
// **  use or with a restricted rights for government use. At that time each source     **
// **  file will contain either/both the standard GPL statement/disclaimer, and/or the  **
// **  DFARS Restricted Rights Legend.                                                  **
// **                                                                                   **
// **  This library exists at the present time WITHOUT ANY WARRANTY; without even the   **
// **  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         **
// **  As you are not supposed to be in possession of this file if you use it,          **
// **  you use this code AT YOUR OWN RISK.                                              **
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


#ifndef __STOPWATCH_TRNCMP_HH
#define __STOPWATCH_TRNCMP_HH


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
