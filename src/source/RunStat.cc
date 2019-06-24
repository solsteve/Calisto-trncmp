// ====================================================================== BEGIN FILE =====
// **                                   R U N S T A T                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2015-2019, Stephen W. Soliday                                      **
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
