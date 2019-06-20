// ====================================================================== BEGIN FILE =====
// **                          E N T R O P Y _ X O R S H I F T                          **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library. (formerly SolLib)              **
// **                                                                                   **
// **  Copyright (c) 2019, Stephen W. Soliday                                           **
// **                      stephen.soliday@trncmp.org                                   **
// **                      http://research.trncmp.org                                   **
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
/** @brief  Entropy XORShift Class.
 *  @file   Entropy_XORShift.cc
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-18
 *
 *  Provides the methods for an XOR Shift Pseudo Random Number Generator.
 */
// =======================================================================================


#include <Entropy_XORShift.hh>

// =======================================================================================
/** @brief Build Instance.
 *  @return pointer to a new Entropy Engine.
 */
// ---------------------------------------------------------------------------------------
Entropy_XORShift* Entropy_XORShift::Builder::build( void ) {
  // -------------------------------------------------------------------------------------
  return new Entropy_XORShift();
}


// =======================================================================================
/** @brief Constructor.
 */
// ---------------------------------------------------------------------------------------
Entropy_XORShift::Entropy_XORShift( void ) : Entropy(), buffer(0), SB(0), SW(0), SD(0), SQ(0) {
  // -------------------------------------------------------------------------------------

  size_t p8  = 0;
  size_t p16 = p8  + 4*sizeof(u_int8_t);
  size_t p32 = p16 + 4*sizeof(u_int16_t);
  size_t p64 = p32 + 4*sizeof(u_int32_t);
  size_t n   = p64 + 4*sizeof(u_int64_t);

  if ( n == seed_size() ) {

    p8  /= sizeof(u_int32_t);
    p16 /= sizeof(u_int32_t);
    p32 /= sizeof(u_int32_t);
    p64 /= sizeof(u_int32_t);
    n   /= sizeof(u_int32_t);
    
    buffer = new u_int32_t[n];

    SB = reinterpret_cast<u_int8_t*>(  (buffer+p8) );
    SW = reinterpret_cast<u_int16_t*>( (buffer+p16) );
    SD = reinterpret_cast<u_int32_t*>( (buffer+p32) );
    SQ = reinterpret_cast<u_int64_t*>( (buffer+p64) );
  } else {
    std::cerr << "Seed init " << n << " is not equal to " << seed_size() << "\n";
  }
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
Entropy_XORShift::~Entropy_XORShift( void ) {
  // -------------------------------------------------------------------------------------
  SB = static_cast<u_int8_t*>(0);
  SW = static_cast<u_int16_t*>(0);
  SD = static_cast<u_int32_t*>(0);
  SQ = static_cast<u_int64_t*>(0);
  delete buffer;
  buffer = static_cast<u_int32_t*>(0);
}


// =======================================================================================
/** @brief Set Seed.
 *  @param[in] S pointer to a source of seed material.
 *  @param[in] n number of bytes of seed matter.
 *
 *  Set the underlying state of this generator from the seed matter.
 */
// ---------------------------------------------------------------------------------------
void Entropy_XORShift::seed_set( void* S, size_t n ) {
  // -------------------------------------------------------------------------------------
  const size_t ns = seed_size();
    
  if ( n == ns ) {
    copy( buffer, reinterpret_cast<u_int32_t*>(S), ns/sizeof(u_int32_t) );
  } else {
    seed_map( reinterpret_cast<u_int8_t*>(buffer), ns,
              reinterpret_cast<void*>(S), n );
  }
}


// =======================================================================================
/** @brief
 */
// ---------------------------------------------------------------------------------------
size_t Entropy_XORShift::seed_size( void ) {
  // -------------------------------------------------------------------------------------
  return
      (4*sizeof(u_int8_t))  +
      (4*sizeof(u_int16_t)) +
      (4*sizeof(u_int32_t)) +
      (4*sizeof(u_int64_t));
}


// =======================================================================================
/** @brief Get Integer.
 *  @return 8 bit unsigned integer.
 *
 *  Return a uniformly distributed 8 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
u_int8_t Entropy_XORShift::U8( void ) {
  // -------------------------------------------------------------------------------------
  const u_int8_t t = SB[0] ^ (u_int8_t)(SB[0] << 4);
  SB[0] = SB[1];
  SB[1] = SB[2];
  SB[2] = SB[3];
  SB[3] = SB[2] ^ t ^ (u_int8_t)( SB[2] >> 1 ) ^ (u_int8_t)( t << 1 );
  return SB[3];
}


// =======================================================================================
/** @brief Get Integer.
 *  @return 16 bit unsigned integer.
 *
 *  Return a uniformly distributed 16 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
u_int16_t Entropy_XORShift::U16( void ) {
  // -------------------------------------------------------------------------------------
  uint16_t t = SW[0] ^ (u_int16_t)(SW[0]<<5); 
  SW[0] = SW[1]; 
  SW[1] = SW[2]; 
  SW[2] = SW[3]; 
  SW[3] = SW[3] ^ (u_int16_t)(SW[3]>>1) ^ (t ^ (u_int16_t)(t>>3));
  return SW[3];
}


// =======================================================================================
/** @brief Get Integer.
 *  @return 32 bit unsigned integer.
 *
 *  Return a uniformly distributed 32 bit unsigned integer.
 */
// ---------------------------------------------------------------------------------------
u_int32_t Entropy_XORShift::U32( void ) {
  // -------------------------------------------------------------------------------------
  uint32_t t = SD[0] ^ (SD[0] << 11);   
  SD[0] = SD[1];
  SD[1] = SD[2];
  SD[2] = SD[3];
  SD[3] = SD[3] ^ (SD[3] >> 19) ^ (t ^ (t >> 8));
  return SD[3];
}


// =======================================================================================
static inline uint64_t rotl(const uint64_t x, int k) {
  // -------------------------------------------------------------------------------------
	return (x << k) | (x >> (64 - k));
}

// =======================================================================================
/** @brief Get Integer.
 *  @return 64 bit unsigned integer.
 *
 *  Return a uniformly distributed 64 bit unsigned integer.  xoshiro256**
 */
// ---------------------------------------------------------------------------------------
u_int64_t Entropy_XORShift::U64( void ) {
  // -------------------------------------------------------------------------------------
  const uint64_t result_starstar = rotl(SQ[1] * 5, 7) * 9;
  
  const uint64_t t = SQ[1] << 17;
  
  SQ[2] ^= SQ[0];
  SQ[3] ^= SQ[1];
  SQ[1] ^= SQ[2];
  SQ[0] ^= SQ[3];
  
  SQ[2] ^= t;
  
  SQ[3] = rotl(SQ[3], 45);

  return result_starstar;
}

// const uint64_t result_starstar = rotl(SQ[1] * 5, 7) * 9;
// const uint64_t t = SQ[1] << 11;
// SQ[2] ^= SQ[0];
// SQ[5] ^= SQ[1];
// SQ[1] ^= SQ[2];
// SQ[7] ^= SQ[3];
// SQ[3] ^= SQ[4];
// SQ[4] ^= SQ[5];
// SQ[0] ^= SQ[6];
// SQ[6] ^= SQ[7];
// SQ[6] ^= t;
// SQ[7] = rotl(SQ[7], 21);
// return result_starstar;


// =======================================================================================
/** @brief Get Real.
 *  @return 32 bit real.
 *
 *  Return a uniformly distributed 32 bit real.
 */
// ---------------------------------------------------------------------------------------
real4_t Entropy_XORShift::R32( void ) {
  // -------------------------------------------------------------------------------------
  const union {
    u_int32_t I;
    real4_t   F;
  } M = { .I = 0x3F800000U | (U32() >> 9) };
  
  return M.F - 1.0e0f;  
}


// =======================================================================================
/** @brief Get Real.
 *  @return 64 bit real.
 *
 *  Return a uniformly distributed 64 bit real.
 */
// ---------------------------------------------------------------------------------------
real8_t Entropy_XORShift::R64( void ) {
  // -------------------------------------------------------------------------------------
  const union {
    u_int64_t I;
    real8_t   D;
  } M = { .I = 0x3FF0000000000000UL | (U64() >> 12) };
  
  return M.D - 1.0e0;
}


// =======================================================================================
// **                          E N T R O P Y _ X O R S H I F T                          **
// ======================================================================== END FILE =====
