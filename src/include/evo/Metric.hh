// ====================================================================== BEGIN FILE =====
// **                               E V O : : M E T R I C                               **
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
/** @brief  Multi Valued Metric.
 *  @file   evo/Metric.hh
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-27 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-10 Ported to HPSP Java.
 *  @date   2019-Sep-26 CMake refactorization.
 *
 *  Provides an interface for a multi valued matric class.
 */
// =======================================================================================


#ifndef __HH_EVO_METRIC_TRNCMP
#define __HH_EVO_METRIC_TRNCMP


#include <trncmp.hh>


namespace evo {

// =======================================================================================
class Metric {
  // -------------------------------------------------------------------------------------
 protected:
  u_int8_t* buffer;       ///< pointer to the metrics buffer.
  int32_t   n_buf;        ///< number of bytes in the buffer.
  bool      owns_buffer;  ///< true if this metric owns the allocation.
    
  real8_t*  data;         ///< recast buffer as real8_t*
  int32_t   n_dat;        ///< number of real8_t data elements.

  EMPTY_PROTOTYPE( Metric );

  void destroy( void );
  
 public:
  Metric  ( void );
  Metric  ( const int32_t nd,
            u_int8_t* src=static_cast<u_int8_t*>(0),
            const int32_t offset=0 );
  
  ~Metric ( void );

  void           resize        ( const int32_t nd,
                                 u_int8_t* src=static_cast<u_int8_t*>(0),
                                 const int32_t offset=0 );
    
  int32_t        size          ( void ) const;
  int32_t        count         ( void ) const;

  u_int8_t*      create_buffer ( void );
  u_int8_t*      get_buffer    ( void );
  real8_t*       get_data      ( void );
  real8_t        get           ( const int32_t idx ) const;
  void           set           ( const int32_t idx, const real8_t value );

  int            compare       ( Metric* rhs ) const;
  
  real8_t        sumsq         ( void ) const;
  real8_t        mse           ( void ) const;

  void           copy          ( Metric* src );
  void           zero          ( void );
  real8_t        normalize     ( void );

  u_int8_t*      load          ( u_int8_t* src );
  u_int8_t*      store         ( u_int8_t* dst );
  
  static int32_t size          ( const int32_t n_elm );
}; // end class Metric


// =======================================================================================
/** @brief Size.
 *  @param[in] n_elm number of elements.
 *  @return number bytes required for n_elm elements.
 *
 *  Static function returns the BYTE storage requirment for n_elm elements.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Metric::size( const int32_t n_elm ) {
  // -------------------------------------------------------------------------------------
  return n_elm * static_cast<int32_t>(sizeof( real8_t ));
}


// =======================================================================================
/** @brief Size.
 *  @return number bytes required for this Metric.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Metric::size( void ) const {
  // -------------------------------------------------------------------------------------
  return n_buf;
}


// =======================================================================================
/** @brief Count.
 *  @return number of real elements in this metric.
 */
// ---------------------------------------------------------------------------------------
inline  int32_t Metric::count( void ) const {
  // -------------------------------------------------------------------------------------
  return n_dat;
}


// =======================================================================================
/** @brief Create Buffer.
 *  @return pointer to new storage for this metric.
 */
// ---------------------------------------------------------------------------------------
inline  u_int8_t* Metric::create_buffer( void ) {
  // -------------------------------------------------------------------------------------
  return new u_int8_t[n_buf];
}


// =======================================================================================
/** @brief Get Buffer.
 *  @return pointer to the storage for this metric.
 */
// ---------------------------------------------------------------------------------------
inline  u_int8_t* Metric::get_buffer( void ) {
  // -------------------------------------------------------------------------------------
  return buffer;
}


// =======================================================================================
/** @brief Get Data.
 *  @return pointer to the data for this metric.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t* Metric::get_data( void ) {
  // -------------------------------------------------------------------------------------
  return data;
}


// =======================================================================================
/** @brief Get.
 *  @param[in] idx index of the Metric data element.
 *  @return value of the indexed element.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Metric::get( const int32_t idx ) const {
  // -------------------------------------------------------------------------------------
  return data[idx];
}


// =======================================================================================
/** @brief Set.
 *  @param[in] idx   index of the Metric data element.
 *  @param[in] value value to set the indexed element.
 */
// ---------------------------------------------------------------------------------------
inline  void Metric::set( const int32_t idx, const real8_t value ) {
  // -------------------------------------------------------------------------------------
  data[idx] = value;
}


// =======================================================================================
  /** @brief Mean square.
   *  @return the mean square.
   *
   *  Compute the mean of the squares of the elements of the Metric.
   */
// ---------------------------------------------------------------------------------------
inline  real8_t Metric::mse( void ) const {
  // -------------------------------------------------------------------------------------
    return sumsq() / static_cast<real8_t>(n_dat);
}


}; // end namespace evo


#endif


// =======================================================================================
// **                                  M A K E F I L E                                  **
// =========================================================================== END FILE ==
