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
 *  @file   Entropy.hh
 *  @author Stephen W. Soliday
 *  @date   2010-01-01  Original release.
 *  @date   2019-Jun-14 CMake refactorization.
 *
 *  Provides the abstract interface for entropy generation.
 */
// =======================================================================================


#ifndef __ENTROPY_TRNCMP_HH
#define __ENTROPY_TRNCMP_HH


#include <trncmp.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
class Entropy {
  // -------------------------------------------------------------------------------------
 protected:
  Entropy(void);

  void seed_map( u_int8_t* dst, size_t nd, void* vsrc, size_t ns );

 public:
  virtual ~Entropy (void);

  virtual void      seed_set  ( void* S, size_t n ) = 0;
  virtual size_t    seed_size ( void )              = 0;
  
  virtual u_int8_t  U8        ( void )              = 0;  ///<  8-bit  unsigned integer
  virtual u_int16_t U16       ( void )              = 0;  ///< 16-bit  unsigned integer
  virtual u_int32_t U32       ( void )              = 0;  ///< 32-bit  unsigned integer
  virtual u_int64_t U64       ( void )              = 0;  ///< 64-bit  unsigned integer
  virtual real4_t   R32       ( void )              = 0;  ///< 32-bit  floating point
  virtual real8_t   R64       ( void )              = 0;  ///< 64-bit  floating point

  static Entropy*   DEFAULT   ( void );

  void seed_set ( void );
}; // end class Entropy


#endif


// =======================================================================================
// **                                   E N T R O P Y                                   **
// ======================================================================== END FILE =====
