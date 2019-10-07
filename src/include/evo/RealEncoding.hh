// ====================================================================== BEGIN FILE =====
// **                         E V O : : R E A L E N C O D I N G                         **
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
 *  @file   evo/RealEncoding.hh
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-29 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-11 Ported to HPSP Java.
 *  @date   2019-Sep-27 CMake refactorization.
 *
 *  Provides the interface for an encoding that is a list of double precision 
 */
// =======================================================================================


#ifndef __HH_EVO_REALENCODING_TRNCMP
#define __HH_EVO_REALENCODING_TRNCMP


#include <evo/Encoding.hh>
#include <evo/ToolKit.hh>
#include <Dice.hh>



namespace evo {

// =======================================================================================
class RealEncoding : public Encoding {
  // -------------------------------------------------------------------------------------
 protected:
  Dice*     dd;
  ToolKit*  tk;
  real8_t*  data;         ///< recast buffer as real8_t*
  int32_t   n_dat;        ///< number of real8_t data elements.
  real8_t   min_value;    ///< minimum value for encoding
  real8_t   zero_value;   ///< zero    value for encoding
  real8_t   max_value;    ///< maximum value for encoding
  bool      is_concave;   ///< is the solution space a concave set. @todo Check this

  EMPTY_PROTOTYPE( RealEncoding );

  void destroy( void );
  
 public:
  RealEncoding  ( void );
  RealEncoding  ( const int32_t nd,
                  const real8_t mnv, const real8_t mxv,
                  u_int8_t* src=static_cast<u_int8_t*>(0),
                  const int32_t offset=0 );
  
  virtual        ~RealEncoding  ( void );
  virtual int32_t count         ( void ) const;
  virtual int     compare       ( Encoding* rhs ) const;
  virtual void    copy          ( Encoding* src );
  virtual void    zero          ( void );

  virtual void    randomize     ( void );
  virtual void    bracket       ( Encoding* src = static_cast<Encoding*>(0) );
  virtual void    noise         ( const real8_t scale,
                                  Encoding* src = static_cast<Encoding*>(0) );
  
  virtual void    crossover     ( Encoding* ac2,  Encoding* ap1,  Encoding* ap2 );
  virtual void    mutate        ( Encoding* src,  const real8_t perc, const real8_t scale );

  void            resize        ( const int32_t nd,
                                  u_int8_t* src=static_cast<u_int8_t*>(0),
                                  const int32_t offset=0 );
    
  real8_t*        get_data      ( void );
  real8_t         get           ( const int32_t idx ) const;
  void            set           ( const int32_t idx, const real8_t value );


}; // end class RealEncoding


// =======================================================================================
/** @brief Count.
 *  @return number of real elements in this RealEncoding.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t RealEncoding::count( void ) const {
  // -------------------------------------------------------------------------------------
  return n_dat;
}


// =======================================================================================
/** @brief Get Data.
 *  @return pointer to the data for this RealEncoding.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* RealEncoding::get_data( void ) {
  // -------------------------------------------------------------------------------------
  return data;
}


// =======================================================================================
/** @brief Get.
 *  @param[in] idx index of the RealEncoding data element.
 *  @return value of the indexed element.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t RealEncoding::get( const int32_t idx ) const {
  // -------------------------------------------------------------------------------------
  return data[idx];
}


// =======================================================================================
/** @brief Set.
 *  @param[in] idx   index of the RealEncoding data element.
 *  @param[in] value value to set the indexed element.
 */
// ---------------------------------------------------------------------------------------
inline  void RealEncoding::set( const int32_t idx, const real8_t value ) {
  // -------------------------------------------------------------------------------------
  data[idx] = value;
}


}; // end namespace evo


#endif


// =======================================================================================
// **                         E V O : : R E A L E N C O D I N G                         **
// =========================================================================== END FILE ==
