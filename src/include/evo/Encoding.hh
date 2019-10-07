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
/** @brief Real Encoding.
 *  @file   evo/Encoding.hh
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-29 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-11 Ported to HPSP Java.
 *  @date   2019-Sep-27 CMake refactorization.
 *
 *  Provides the abstract interface for an encoding.
 */
// =======================================================================================


#ifndef __HH_EVO_ENCODING_TRNCMP
#define __HH_EVO_ENCODING_TRNCMP


#include <trncmp.hh>


namespace evo {

// =======================================================================================
class Encoding {
  // -------------------------------------------------------------------------------------
 protected:
  u_int8_t* buffer;       ///< pointer to the Encodings buffer.
  int32_t   n_buf;        ///< number of bytes in the buffer.
  bool      owns_buffer;  ///< true if this Encoding owns the allocation.
    
  EMPTY_PROTOTYPE( Encoding );

  void destroy_buffer( void );
  void resize_buffer ( const int32_t nb, u_int8_t* src, const int32_t offset );

 public:

  /** This constant is used with noise and mutation. It represents the number of standard
   *  deviations that are covered by the range of parameter values when 'scale' is set
   *  to 1. Example: if the mean is -1.0 and the scale is 1.0 then the opposite end
   *  parameter 1.0 is N_SIGMA_SCALE * sigma away.
   */
  static const real8_t N_SIGMA_SCALE;
  
  Encoding  ( void );

  
  virtual        ~Encoding      ( void );
  virtual int32_t count         ( void )          const = 0;
  virtual int     compare       ( Encoding* rhs ) const = 0;
  virtual void    copy          ( Encoding* src )       = 0;
  virtual void    zero          ( void )                = 0;

  virtual void    randomize     ( void )                = 0;
  virtual void    bracket       ( Encoding* src = static_cast<Encoding*>(0) ) = 0;
  virtual void    noise         ( const real8_t scale,
                                  Encoding* src = static_cast<Encoding*>(0) ) = 0;
  
  virtual void    crossover     ( Encoding* ac2,  Encoding* ap1,  Encoding* ap2 )           = 0;
  virtual void    mutate        ( Encoding* src,  const real8_t perc, const real8_t scale ) = 0;
  

  int32_t         size          ( void ) const;

  u_int8_t*       create_buffer ( void );
  u_int8_t*       get_buffer    ( void );
  u_int8_t*       load          ( u_int8_t* src );
  u_int8_t*       store         ( u_int8_t* dst );
  
}; // end class Encoding


// =======================================================================================
/** @brief Size.
 *  @return number bytes required for this Encoding.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Encoding::size( void ) const {
  // -------------------------------------------------------------------------------------
  return n_buf;
}


// =======================================================================================
/** @brief Create Buffer.
 *  @return pointer to new storage for this Encoding.
 */
// ---------------------------------------------------------------------------------------
inline  u_int8_t* Encoding::create_buffer( void ) {
  // -------------------------------------------------------------------------------------
  return new u_int8_t[n_buf];
}


// =======================================================================================
/** @brief Get Buffer.
 *  @return pointer to the storage for this Encoding.
 */
// ---------------------------------------------------------------------------------------
inline  u_int8_t* Encoding::get_buffer( void ) {
  // -------------------------------------------------------------------------------------
  return buffer;
}


}; // end namespace evo


#endif


// =======================================================================================
// **                             E V O : : E N C O D I N G                             **
// =========================================================================== END FILE ==
