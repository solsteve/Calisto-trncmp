// ====================================================================== BEGIN FILE =====
// **                                   E N T R O P Y                                   **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2010, 2019, Stephen W. Soliday                                     **
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
