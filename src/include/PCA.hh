// ====================================================================== BEGIN FILE =====
// **                                       P C A                                       **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2018-19, Stephen W. Soliday                                        **
// **                         stephen.soliday@trncmp.org                                **
// **                         http://research.trncmp.org                                **
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
/** @brief  Principle Component Analysis.
 *  @file   PCA.hh
 *  @author Stephen W. Soliday
 *  @date   2018-Apr-20 Original release.
 *  @date   2019-Aug-06 Port from Java to C++.
 *  Provides the interface for performing Principle Component Analysis.
 */
// =======================================================================================


#ifndef __HH_PCA_TRNCMP
#define __HH_PCA_TRNCMP

#include <trncmp.hh>

// =======================================================================================
class PCA {
  // -------------------------------------------------------------------------------------
 protected:

  Vector* mu;
  Vector* variance;
  Matrix* covariance;
  Matrix* fwdTransform;
  Matrix* rvsTransform;
  


}; // end class PCA

#endif

// =======================================================================================
// **                                       P C A                                       **
// ======================================================================== END FILE =====

