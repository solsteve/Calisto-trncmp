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
 *  @file   evo/Metric.cc
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-27 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-10 Ported to HPSP Java.
 *  @date   2019-Sep-26 CMake refactorization.
 *
 *  Provides the methods for a multi valued matric class.
 */
// =======================================================================================


#include <evo/Metric.hh>
#include <string.h>


namespace evo {


#define INIT_VAR(_a) buffer(_a), n_buf(_a), owns_buffer(false), data(_a), n_dat(_a)


// =======================================================================================
/** @brief Destroy.
 *
 *  Deallocate space if required. Place this Metric in the empty state.
 */
// ---------------------------------------------------------------------------------------
void Metric::destroy( void ) {
  // -------------------------------------------------------------------------------------
  data  = static_cast<real8_t*>(0);
  n_dat = 0;
  
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
 *  @param[in] src    pointer to a allocation for this metric.
 *  @param[in] offset offset into the allocated buf for this metric.
 *
 *  Create a metric object. Use the buffer if provided, otherwise
 *  make an allocation and take ownership.
 */
// ---------------------------------------------------------------------------------------
void Metric::resize( const int32_t nd, u_int8_t* src, const int32_t offset ) {
  // -------------------------------------------------------------------------------------
  if ( n_dat != nd ) {
    destroy();

    n_dat = nd;
    n_buf = nd * static_cast<int32_t>(sizeof(real8_t));
    
    if ( static_cast<u_int8_t*>(0) == src ) {
      buffer      = new u_int8_t[ n_buf ];
      owns_buffer = true;
    } else {
      buffer      = (src+offset);
      owns_buffer = false;
    }

    data = reinterpret_cast<real8_t*>(buffer);
  }
}








// =======================================================================================
/** @brief Constructor.
 *
 *  Create an empty Metric.
 */
// ---------------------------------------------------------------------------------------
Metric::Metric( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
}


// =======================================================================================
  /** @brief Constructor.
   *  @param[in] nd     number of data elements.
   *  @param[in] src    pointer to a allocation for this metric.
   *  @param[in] offset offset into the allocated buf for this metric.
   *
   *  Create a metric object. Use the buffer if provided, otherwise
   *  make an allocation and take ownership.
   */
// ---------------------------------------------------------------------------------------
  Metric::Metric( const int32_t nd, u_int8_t* src, const int32_t offset ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
    resize( nd, src, offset );
}


// =======================================================================================
  /** @brief Destructor.
   */
// ---------------------------------------------------------------------------------------
Metric::~Metric( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}








// =======================================================================================
  /** @brief Compare.
   *  @param[in] rhs pointer to the RHS Metric.
   *  @return integer less than, equal to, or greater than zero if this is found,
   *          respectively, to be less than, to match, or be greater than rhs.
   *
   *  Perform an element by element compare of the RHS Metric.
   *
   *  < 0   if   this[i] < rhs[i]
   *  = 0   if   this[i] = rhs[i]
   *  > 0   if   this[i] > rhs[i]
   */
// ---------------------------------------------------------------------------------------
  int Metric::compare( Metric* rhs ) const {
  // -------------------------------------------------------------------------------------
    const int n = static_cast<int>(this->n_dat);
    for ( int i=0; i<n; i++ ) {
      if ( this->data[i] < rhs->data[i] ) { return -(i+1); }
      if ( this->data[i] > rhs->data[i] ) { return   i+1;  }
    }
    return 0;
}


// =======================================================================================
  /** @brief Sum of squares.
   *  @return the sum of the squares.
   *
   *  Sum the squares of each element of the metric array.
   */
// ---------------------------------------------------------------------------------------
  real8_t Metric::sumsq( void ) const {
  // -------------------------------------------------------------------------------------
    real8_t sum = D_ZERO;

    for ( int32_t i=0; i<n_dat; i++ ) {
      const real8_t d = data[i];
      sum += ( d*d );
    }

    return sum;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] src pointer to the source metric.
 *
 *  Perform a deep copy of this object.
 */
// ---------------------------------------------------------------------------------------
  void Metric::copy( Metric* src ) {
  // -------------------------------------------------------------------------------------
    for ( int32_t i=0; i<n_dat; i++ ) {
      data[i] = src->data[i];
    }
}


// =======================================================================================
/** @brief Zero.
 *
 *  Zero all the elements of this Metric.
 */
// ---------------------------------------------------------------------------------------
  void Metric::zero( void ) {
  // -------------------------------------------------------------------------------------
    for ( int32_t i=0; i<n_dat; i++ ) {
      data[i] = D_ZERO;
    }
}


// =======================================================================================
  /** @brief Normalize.
   *  @return the scaling factor.
   *
   *  Normalize in place the elements of the Metric.
   */
// ---------------------------------------------------------------------------------------
  real8_t Metric::normalize( void ) {
  // -------------------------------------------------------------------------------------
    const real8_t div = sqrt( sumsq() );

    for ( int32_t i=0; i<n_dat; i++ ) {
      data[i] /= div;
    }

    return div;
}


// =======================================================================================
  /** @brief Load.
   *  @param[in] src pointer to a source of data.
   *  @return next unused address in the source.
   */
// ---------------------------------------------------------------------------------------
  u_int8_t* Metric::load( u_int8_t* src ) {
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
  u_int8_t* Metric::store( u_int8_t* dst ) {
  // -------------------------------------------------------------------------------------
    memcpy( static_cast<void*>(dst), static_cast<void*>(buffer), n_buf);
    return (dst+n_buf);
}


}; // end namespace evo


// =======================================================================================
// **                                  M A K E F I L E                                  **
// =========================================================================== END FILE ==
