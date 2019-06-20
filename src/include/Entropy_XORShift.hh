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
 *  @file   Entropy_XORShift.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-18
 *
 *  Provides the interface for an XOR Shift Pseudo Random Number Generator.
 */
// =======================================================================================


#ifndef __ENTROPY_XORSHIFT_TRNCMP_HH
#define __ENTROPY_XORSHIFT_TRNCMP_HH


#include <Entropy.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
class Entropy_XORShift : public Entropy {                              // Entropy_XORShift
  // -------------------------------------------------------------------------------------
 protected:
  EMPTY_PROTOTYPE( Entropy_XORShift );
  
  Entropy_XORShift(void);

  u_int32_t* buffer; ///< State buffer
  
  u_int8_t*  SB;     ///< BYTE state array
  u_int16_t* SW;     ///< WORD state array
  u_int32_t* SD;     ///< DWRD state array
  u_int64_t* SQ;     ///< QWRD state array

 public:

  // =====================================================================================
  // -------------------------------------------------------------------------------------
  class Builder {                                             // Entropy_XORShift::Builder
    // -----------------------------------------------------------------------------------
   public:
    Builder  ( void ) {};
    ~Builder ( void ) {};
    
    Entropy_XORShift* build( void );
  }; // end class Entropy_XORShift::Builder

  virtual ~Entropy_XORShift (void);

  virtual void      seed_set  ( void* S, size_t n );
  virtual size_t    seed_size ( void );
  
  virtual u_int8_t  U8        ( void );
  virtual u_int16_t U16       ( void );
  virtual u_int32_t U32       ( void );
  virtual u_int64_t U64       ( void );
  virtual real4_t   R32       ( void );
  virtual real8_t   R64       ( void );
}; // end class Entropy_XORShift


#endif


// =======================================================================================
// **                               E N T R O P Y _ L C G                               **
// ======================================================================== END FILE =====
