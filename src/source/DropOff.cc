// ====================================================================== BEGIN FILE =====
// **                                   D R O P O F F                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2016-2019, Stephen W. Soliday                                      **
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
/** @brief  Drop Off Generator.
 *  @file   DropOff.cc
 *  @author Stephen W. Soliday
 *  @date   2016-Aug-09 Original release.
 *  @date   2019-Jun-27 CMake refactorization.
 *
 *  Provides the methods for a drop off generator.
 */
// =======================================================================================


#include <DropOff.hh>


// =======================================================================================
/** @brief Constructor
 *  @param[in] Vo Starting value.
 *  @param[in] Vf Final value.
 *  @param[in] n  number of samples.
 *  @param[in] dt drop off type (default linear).
 *
 *  Set up a drop off function such that V=Vo @ 0 and V=Vf @ n-1
 */
// ---------------------------------------------------------------------------------------
DropOff::DropOff( real8_t Vo, real8_t Vf, size_t n, drop_type dt )
  : index(0), A(1.0), B(1.0), d_type( dt ) {
  // -------------------------------------------------------------------------------------
  switch(dt) {
  case LINEAR:      // ----- Linear drop off ---------------------------------------------
    A = (Vf - Vo) / ((real8_t) (n-1));
    B = Vo;
    break;

  case EXPONENTIAL: // ----- Exponential drop off ----------------------------------------
    A = Vo;
    B = log( Vf / Vo ) / (real8_t) (n-1);
    break;

  case GAUSSIAN:    // ----- Gaussian drop off -------------------------------------------
    A = Vo;
    B = log(Vf/Vo) / (real8_t) (n*(n-1) + 1);
    break;

  default:          // -------------------------------------------------------------------
    std::cerr << "DropOff::Dropoff(" << Vo << "," << Vf << "," << (int)dt << ") - failed\n";
    break;
  }
}


// =======================================================================================
/** @brief Destructor
 */
// ---------------------------------------------------------------------------------------
DropOff::~DropOff( void ) {
  // -------------------------------------------------------------------------------------
  A     = D_ZERO;
  B     = D_ZERO;
  index = 0;
}


// =======================================================================================
/** @brief Get.
 *  @return current value.
 *
 *  Get the current value and increment the index.
 */
// ---------------------------------------------------------------------------------------
real8_t DropOff::next( void ) {
  // -------------------------------------------------------------------------------------
  real8_t rv = 0.0;
  
  switch(d_type) {
  case LINEAR:      // ----- Linear drop off ---------------------------------------------
    rv = B + A * (real8_t) index;
    break;
    
  case EXPONENTIAL: // ----- Exponential drop off ----------------------------------------
    rv = A * exp( B * (real8_t) index );
    break;
    
  case GAUSSIAN:    // ----- Gaussian drop off -------------------------------------------
    rv  = A*exp(((real8_t)(index*index))*B);
    break;
    
  default:          // -------------------------------------------------------------------
    std::cerr << "DropOff::get(" << index << "," << (int)d_type << ") - failed\n";
    break;
  }
  index += 1;

  return rv;
}


// =======================================================================================
/** @brief Get.
 *  @param n new index.
 *  @return current value.
 *
 *  Set the index, return that value and then increment.
 *  Example:  get(5)  returns V(5) and then increments index to 6.
 */
// ---------------------------------------------------------------------------------------
real8_t DropOff::get( size_t n ) {
  // -------------------------------------------------------------------------------------
  index = n;
  return next();
}


// =======================================================================================
/** @brief Reset.
 *  Set the index to 0.
 */
// ---------------------------------------------------------------------------------------
void DropOff::reset( void ) {
  // -------------------------------------------------------------------------------------
  index=0;
}


// =======================================================================================
// **                                   D R O P O F F                                   **
// ======================================================================== END FILE =====
