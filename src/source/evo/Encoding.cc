// ====================================================================== BEGIN FILE =====
// **                             E V O : : E N C O D I N G                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 1995-2019, Stephen W. Soliday                                      **
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
/** @brief  Multi Valued Encoding.
 *  @file   evo/Encoding.cc
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-27 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-10 Ported to HPSP Java.
 *  @date   2019-Sep-26 CMake refactorization.
 *
 *  Provides the methods for the generic encoding.
 */
// =======================================================================================


#include <evo/Encoding.hh>
#include <string.h>


namespace evo {


#define INIT_VAR(_a) buffer(_a), n_buf(_a), owns_buffer(false)

  /** This constant is used with noise and mutation. It represents the number of standard
   *  deviations that are covered by the range of parameter values when 'scale' is set
   *  to 1. Example: if the mean is -1.0 and the scale is 1.0 then the opposite end
   *  parameter 1.0 is N_SIGMA_SCALE * sigma away.
   */
const real8_t Encoding::N_SIGMA_SCALE = D_FOUR;

// =======================================================================================
/** @brief Destroy.
 *
 *  Deallocate space if required. Place this Encoding in the empty state.
 */
// ---------------------------------------------------------------------------------------
void Encoding::destroy_buffer( void ) {
  // -------------------------------------------------------------------------------------
  if ( owns_buffer ) { // this will not be set to true unless the pointer is non-NULL
    delete[] buffer;
  }
  
  n_buf       = 0;
  buffer      = static_cast<u_int8_t*>(0);
  owns_buffer = false;
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nd     number of data elements.
 *  @param[in] src    pointer to a allocation for this Encoding.
 *  @param[in] offset offset into the allocated buf for this Encoding.
 *
 *  Create a Encoding object. Use the buffer if provided, otherwise
 *  make an allocation and take ownership.
 */
// ---------------------------------------------------------------------------------------
void Encoding::resize_buffer( const int32_t nb, u_int8_t* src, const int32_t offset ) {
  // -------------------------------------------------------------------------------------
  if ( n_buf != nb ) {
    destroy_buffer();

    n_buf = nb;
    
    if ( static_cast<u_int8_t*>(0) == src ) {
      buffer      = new u_int8_t[ n_buf ];
      owns_buffer = true;
    } else {
      buffer      = (src+offset);
      owns_buffer = false;
    }
  }
}








// =======================================================================================
/** @brief Constructor.
 *
 *  Create an empty Encoding.
 */
// ---------------------------------------------------------------------------------------
Encoding::Encoding( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
  /** @brief Destructor.
   */
// ---------------------------------------------------------------------------------------
Encoding::~Encoding( void ) {
  // -------------------------------------------------------------------------------------
  destroy_buffer();
}








// =======================================================================================
  /** @brief Load.
   *  @param[in] src pointer to a source of data.
   *  @return next unused address in the source.
   */
// ---------------------------------------------------------------------------------------
  u_int8_t* Encoding::load( u_int8_t* src ) {
  // -------------------------------------------------------------------------------------
    memcpy( static_cast<void*>(buffer), static_cast<void*>(src), n_buf);
    return (src+n_buf);
}


// =======================================================================================
  /** @brief Store.
   *  @param[in] dst pointer to a destination of data.
   *  @return next unused address in the destination.
   */
// ---------------------------------------------------------------------------------------
  u_int8_t* Encoding::store( u_int8_t* dst ) {
  // -------------------------------------------------------------------------------------
    memcpy( static_cast<void*>(dst), static_cast<void*>(buffer), n_buf);
    return (dst+n_buf);
}


}; // end namespace evo


// =======================================================================================
// **                             E V O : : E N C O D I N G                             **
// =========================================================================== END FILE ==
