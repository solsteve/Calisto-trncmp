// ====================================================================== BEGIN FILE =====
// **                                   R U N S T A T                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2015, 2019, Stephen W. Soliday                                     **
// **                            stephen.soliday@trncmp.org                             **
// **                            http://research.trncmp.org                             **
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
/** @brief  Running Statistics.
 *  @file   RunStat.hh
 *  @author Stephen W. Soliday
 *  @date   2015-01-26  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the interface for a running statistics.
 */
// =======================================================================================


#include <RunStat.hh>


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
RunStat::RunStat  ( std::string nm )
    : name(nm), min_val(0.0), max_val(0.0), mean_val(0.0), mean_val_sq(0.0),
      is_first(true), num_samp(0), min_idx(0), max_idx(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
RunStat::~RunStat ( void ) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Reset.
 *
 *  Clear the values and start over.
 *  @note this will not take effect until the first update after calling a rest.
 */
// ---------------------------------------------------------------------------------------
void RunStat::reset( void ) {
  // -------------------------------------------------------------------------------------
  is_first = true;
}


// =======================================================================================
/** @brief Variance.
 *  @return mean variance of the sampled values.
 */
// ---------------------------------------------------------------------------------------
real8_t RunStat::var( void ) {
  // -------------------------------------------------------------------------------------
  return mean_val_sq - (mean_val*mean_val);
}


// =======================================================================================
/** @brief Report.
 *  @param[in] os optional reference to an output stream (default: stdout)
 */
// ---------------------------------------------------------------------------------------
void RunStat::report( std::ostream& os ) {
  // -------------------------------------------------------------------------------------
  os << "Type: " << name << " Samples: " << count() << "\n"
     << "  mean      " << mean()  << "\n"
     << "  std dev   " << stdev() << "\n"
     << "  min       " << minv()  << "\n"
     << "  max       " << maxv()  << "\n"
     << "  min index " << mini()  << "\n"
     << "  max index " << maxi()  << "\n"
     << "\n";
}


// =======================================================================================
// **                                   R U N S T A T                                   **
// ======================================================================== END FILE =====
