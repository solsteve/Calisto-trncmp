// ====================================================================== BEGIN FILE =====
// **                                   E N T R O P Y                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2010-2019, Stephen W. Soliday                                      **
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
/** @brief  Entropy Base Class.
 *  @file   Entropy.cc
 *  @author Stephen W. Soliday
 *  @date   2010-01-01  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the methods for entropy default generation.
 */
// =======================================================================================


#include <Entropy.hh>
#include <Entropy_XORShift.hh>


// =======================================================================================
/** @brief Base Constructor.
 */
// ---------------------------------------------------------------------------------------
Entropy::Entropy(void) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Base Destructor.
 */
// ---------------------------------------------------------------------------------------
Entropy::~Entropy(void){
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
/** @brief Get Default.
 *
 *  Instantiate a default engine.
 */
// ---------------------------------------------------------------------------------------
Entropy* Entropy::DEFAULT( void ) {
  // -------------------------------------------------------------------------------------
  Entropy_XORShift* P = (new Entropy_XORShift::Builder())->build();
  return dynamic_cast<Entropy*>(P);
}


// =======================================================================================
/** @brief Set Seed.
 *
 *  Use system methods (e.g. /dev/urandom) to set the initial seed.
 */
// ---------------------------------------------------------------------------------------
void Entropy::seed_set( void ) {
  // -------------------------------------------------------------------------------------
  size_t    n      = seed_size();
  u_int8_t* buffer = new u_int8_t[n];
  urandom(  reinterpret_cast<void*>(buffer), n );
  seed_set( reinterpret_cast<void*>(buffer), n );
  delete buffer;
}


// =======================================================================================
/** @brief Generate Seed Matter
 *  @param[out] dst  pointer to a destination buffer.
 *  @param[in]  nd   number of bytes in the destination.
 *  @param[in]  vsrc pointer to a source buffer.
 *  @param[in]  ns   number of bytes in the source.
 *
 *  @note this needs to be replaced with a true HASH.  
 */
// ---------------------------------------------------------------------------------------
void Entropy::seed_map( u_int8_t* dst, size_t nd, void* vsrc, size_t ns ) {
  // -------------------------------------------------------------------------------------

  u_int8_t* src = reinterpret_cast<u_int8_t*>(vsrc);
  
  if ( nd == ns ) { // ------ buffer are equal in length ---------------------------------
    for ( size_t i=0; i<nd; i++ ) {
      dst[i] = src[i];
    }
  } else {
    if ( nd < ns ) { // ----- desination buffer is shorter than the source ---------------
      for ( size_t i=0; i<nd; i++ ) {
        dst[i] = src[i];
      }
      for ( size_t i=nd; i<ns; i++ ) {
        dst[i%nd] ^= src[i];
      }
    } else { // ------------- desination buffer is longer than the source ----------------
      for ( size_t i=0; i<ns; i++ ) {
        dst[i] = src[i%ns];
      }
    }
  }
}

// =======================================================================================
// **                                   E N T R O P Y                                   **
// ======================================================================== END FILE =====
