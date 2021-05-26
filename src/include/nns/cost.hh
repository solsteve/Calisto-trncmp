// ====================================================================== BEGIN FILE =====
// **                                 N N S : : C O S T                                 **
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
/** @brief  Neural Network Cost Functions.
 *  @file   cost.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-18.
 *
 *  Provides the interface for various neural network cost functions.
 */
// =======================================================================================


#ifndef __HH_NNS_COST_TRNCMP
#define __HH_NNS_COST_TRNCMP


#include <trncmp.hh>


namespace nns {


typedef real8_t (*cost_function_t)          (real8_t*,real8_t*,size_t);
typedef void    (*cost_function_gradient_t) (real8_t*,real8_t*,real8_t*,size_t);


cost_function_t          getCostFunction          ( std::string name );
cost_function_gradient_t getCostFunctionGradient  ( std::string name );


}; // end namespace nns


#endif

// =======================================================================================
// **                                 N N S : : C O S T                                 **
// ======================================================================== END FILE =====
