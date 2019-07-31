// ====================================================================== BEGIN FILE =====
// **                          E N T R O P Y _ X O R S H I F T                          **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2019-, Stephen W. Soliday                                          **
// **                       stephen.soliday@trncmp.org                                  **
// **                       http://research.trncmp.org                                  **
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
/** @brief  Entropy XORShift Class.
 *  @file   Entropy_XORShift.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Jun-18
 *
 *  Provides the interface for an XOR Shift Pseudo Random Number Generator.
 */
// =======================================================================================


#ifndef __HH_ENTROPY_XORSHIFT_TRNCMP
#define __HH_ENTROPY_XORSHIFT_TRNCMP


#include <Entropy.hh>


// =======================================================================================
// ---------------------------------------------------------------------------------------
class Entropy_XORShift : public Entropy {                              // Entropy_XORShift
  // -------------------------------------------------------------------------------------
 protected:
  EMPTY_PROTOTYPE( Entropy_XORShift );
  
  Entropy_XORShift(void);

  u_int32_t* buffer; ///< State buffer
  size_t     nbuf;
  
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

  virtual void      seed_show ( std::ostream& os = std::cerr );

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
// **                          E N T R O P Y _ X O R S H I F T                          **
// ======================================================================== END FILE =====
