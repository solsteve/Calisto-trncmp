// ====================================================================== BEGIN FILE =====
// **                             N N S : : A C T I V A T E                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2020, Stephen W. Soliday                                      **
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
/** @brief  Neural Network Activation Functions.
 *  @file   activate.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-18.
 *
 *  Provides the interface for various neural network activation functions.
 */
// =======================================================================================


#ifndef __HH_NNS_ACTIVATE_TRNCMP
#define __HH_NNS_ACTIVATE_TRNCMP

#include <trncmp.hh>

namespace nns {

typedef void (*activate_t)          (real8_t*, real8_t*, const size_t);
typedef void (*activate_gradient_t) (real8_t*, real8_t*, real8_t*, const size_t);

activate_t            getActivation         ( std::string name );
activate_gradient_t   getActivationGradient ( std::string name );

}; // end namespace nns


#endif

// =======================================================================================
// **                             N N S : : A C T I V A T E                             **
// ======================================================================== END FILE =====
