// ====================================================================== BEGIN FILE =====
// **                                    T R N C M P                                    **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 1993, 02, 09, 19  Stephen W. Soliday                               **
// **                                  stephen.soliday@trncmp.org                       **
// **                                  http://research.trncmp.org                       **
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
/** @brief  Basic functions
 *  @file   trncmp.cc
 *  @author Stephen W. Soliday
 *  @date   1993-09-18  Original release.
 *  @date   2009-01-28  Major revision.
 *  @date   2019-Apr-11 CMake refactorization.
 *
 *  This is the minimum set of functions to be built.
 */
// =======================================================================================


#include <trncmp.hh>


// =======================================================================================
/** @brief Author
 *  @return name of the author
 *
 *  This function returns the name of the author
 */
// ---------------------------------------------------------------------------------------
const char* trncmpAuthor() {
  // -------------------------------------------------------------------------------------
  return "Stephen Soliday";
}


// =======================================================================================
/** @brief Version
 *  @return name the version number
 *
 *  This function returns the version number of this build
 */
// ---------------------------------------------------------------------------------------
const char* trncmpVersion() {
  // -------------------------------------------------------------------------------------
  return "3.0.1";
}


// ==========================================================================================
/** @brief Show Time.
 *  @param o     reference to a stream object.
 *  @param hours time expressed in hours.
 *
 *  Decompose hours into hours minutes and seconds appropriate for display.
 */
// ------------------------------------------------------------------------------------------
void ShowTime( std::ostream& o, real8_t hours ) {
  // ----------------------------------------------------------------------------------------
  real8_t x = hours;
  real8_t h = floor(x);
  
  x = (x - h)*60.0;
  real8_t m = floor(x);
  
  x = (x - m)*60.0;
  real8_t s = floor(x+0.5);
  
  o << h << ":"
    << m << ":"
    << s;
}


// =======================================================================================
// **                                    T R N C M P                                    **
// ======================================================================== END FILE =====
