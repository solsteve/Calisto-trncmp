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
/** @brief  Multi Valued RealEncoding.
 *  @file   evo/RealEncoding.cc
 *  @author Stephen W. Soliday
 *  @date   1995-Dec-27 Original C++ release (as FGA).
 *  @date   2016-Sep-01 Refactored for MPIch.
 *  @date   2018-Jul-10 Ported to HPSP Java.
 *  @date   2019-Sep-26 CMake refactorization.
 *
 *  Provides the methods for an encoding that is a list of double precision 
 */
// =======================================================================================


#include <evo/RealEncoding.hh>

namespace evo {


#define INIT_VAR(_a) dd(_a), tk(_a), data(_a), n_dat(_a), \
    min_value(_a), zero_value(_a), max_value(_a), is_concave(true)


// =======================================================================================
/** @brief Destroy.
 *
 *  Deallocate space if required. Place this RealEncoding in the empty state.
 */
// ---------------------------------------------------------------------------------------
void RealEncoding::destroy( void ) {
  // -------------------------------------------------------------------------------------
  destroy_buffer();
  data  = static_cast<real8_t*>(0);
  n_dat = 0;
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nd     number of data elements.
 *  @param[in] src    pointer to a allocation for this RealEncoding.
 *  @param[in] offset offset into the allocated buf for this RealEncoding.
 *
 *  Create a RealEncoding object. Use the buffer if provided, otherwise
 *  make an allocation and take ownership.
 */
// ---------------------------------------------------------------------------------------
void RealEncoding::resize( const int32_t nd, u_int8_t* src, const int32_t offset ) {
  // -------------------------------------------------------------------------------------
  if ( n_dat != nd ) {
    destroy();

    n_dat = nd;
    resize_buffer( nd * static_cast<int32_t>(sizeof(real8_t)),
                   src, offset );

    data = reinterpret_cast<real8_t*>(buffer);
  }
}








// =======================================================================================
/** @brief Constructor.
 *
 *  Create an empty RealEncoding.
 */
// ---------------------------------------------------------------------------------------
RealEncoding::RealEncoding( void ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  dd = Dice::getInstance();
  tk = ToolKit::getInstance(dd);
}


// =======================================================================================
/** @brief Constructor.
 *  @param[in] nd     number of data elements.
 *  @param[in] src    pointer to a allocation for this RealEncoding.
 *  @param[in] offset offset into the allocated buf for this RealEncoding.
 *
 *  Create a RealEncoding object. Use the buffer if provided, otherwise
 *  make an allocation and take ownership.
 */
// ---------------------------------------------------------------------------------------
RealEncoding::RealEncoding( const int32_t nd, const real8_t mnv, const real8_t mxv,
                            u_int8_t* src, const int32_t offset ) : INIT_VAR(0) {
  // -------------------------------------------------------------------------------------
  tk = ToolKit::getInstance();
  resize( nd, src, offset );
  min_value  = mnv;
  max_value  = mxv;
  zero_value = D_ZERO;
  if ( D_ZERO < min_value ) {
    zero_value = min_value;
  }
  if ( max_value < D_ZERO ) {
    zero_value = max_value;
  }
}


// =======================================================================================
/** @brief Destructor.
 */
// ---------------------------------------------------------------------------------------
RealEncoding::~RealEncoding( void ) {
  // -------------------------------------------------------------------------------------
  destroy();
}








// =======================================================================================
/** @brief Compare.
 *  @param[in] rhs pointer to the RHS RealEncoding.
 *  @return integer less than, equal to, or greater than zero if this is found,
 *          respectively, to be less than, to match, or be greater than rhs.
 *
 *  Perform an element by element compare of the RHS RealEncoding.
 *
 *  < 0   if   this[i] < rhs[i]
 *  = 0   if   this[i] = rhs[i]
 *  > 0   if   this[i] > rhs[i]
 */
// ---------------------------------------------------------------------------------------
int RealEncoding::compare( Encoding* e_rhs ) const {
  // -------------------------------------------------------------------------------------
  RealEncoding* rhs = dynamic_cast<RealEncoding*>(e_rhs);
  const int n = static_cast<int>(this->n_dat);
  for ( int i=0; i<n; i++ ) {
    if ( this->data[i] < rhs->data[i] ) { return -(i+1); }
    if ( this->data[i] > rhs->data[i] ) { return   i+1;  }
  }
  return 0;
}


// =======================================================================================
/** @brief Copy.
 *  @param[in] src pointer to the source RealEncoding.
 *
 *  Perform a deep copy of this object.
 */
// ---------------------------------------------------------------------------------------
void RealEncoding::copy( Encoding* e_src ) {
  // -------------------------------------------------------------------------------------
  RealEncoding* src = dynamic_cast<RealEncoding*>(e_src);
  for ( int32_t i=0; i<n_dat; i++ ) {
    data[i] = src->data[i];
  }
  min_value  = src->min_value;
  zero_value = src->zero_value;
  max_value  = src->max_value;
}


// =======================================================================================
/** @brief Zero.
 *
 *  Zero all the elements of this RealEncoding.
 */
// ---------------------------------------------------------------------------------------
void RealEncoding::zero( void ) {
  // -------------------------------------------------------------------------------------
  for ( int32_t i=0; i<n_dat; i++ ) {
    data[i] = zero_value;
  }
}








// =======================================================================================
  /** @brief Randomize.
   *
   *  Fill the Encoding with uniformly distributed random values.
   */
// ---------------------------------------------------------------------------------------
void RealEncoding::randomize( void ) {
  // -------------------------------------------------------------------------------------
  tk->randomize( data, n_dat, min_value, max_value );
}


// =======================================================================================
  /** @brief Bracket.
   *
   *  Fill the string with {min max} values, evenly distributed.
   */
// ---------------------------------------------------------------------------------------
void RealEncoding::bracket( Encoding* src ) {
  // -------------------------------------------------------------------------------------
  real8_t* temp = static_cast<real8_t*>(0);
  if ( static_cast<Encoding*>(0) != src ) {
    temp = dynamic_cast<RealEncoding*>(src)->get_data();
  }

  tk->bracket( data, n_dat, min_value, max_value, temp );
}


// =======================================================================================
  /** @brief Noise.
   *  @param[in] scale  scale of the noise (see {@link Encoding.N_SIGMA_SCALE})
   *
   *  Add Gaussian random noise to each element.
   */
// ---------------------------------------------------------------------------------------
void RealEncoding::noise( const real8_t scale, Encoding* src ) {
  // -------------------------------------------------------------------------------------
  const real8_t sigma = (max_value - min_value) * scale / N_SIGMA_SCALE;
  real8_t* temp = static_cast<real8_t*>(0);
  if ( static_cast<Encoding*>(0) != src ) {
    temp = dynamic_cast<RealEncoding*>(src)->get_data();
  }

  tk->noise( data, n_dat, sigma, min_value, max_value, temp );
}

// =======================================================================================
  /** @brief Crossover.
   *  @param[in] ac2 pointer to child number two.
   *  @param[in] ap1 pointer to parent number one.
   *  @param[in] ap2 pointer to parent number two.
   *  @return true if crossover took place.
   *
   *  (this) is child number one.
   *
   *  @note The go/no-go decision was made higher up. At this point we are going
   *        to perform Crossover.
   *
   *  @todo alter this to allow concave data clouds.
   */
// ---------------------------------------------------------------------------------------
void RealEncoding::crossover( Encoding* ac2, Encoding* ap1, Encoding* ap2 ) {
  // -------------------------------------------------------------------------------------
  real8_t* c2 = dynamic_cast<RealEncoding*>(ac2)->get_data();
  real8_t* p1 = dynamic_cast<RealEncoding*>(ap1)->get_data();
  real8_t* p2 = dynamic_cast<RealEncoding*>(ap2)->get_data();

  const real8_t t = (is_concave) ?
      (dd->uniform()) :
      (3.0*dd->uniform() - 1.5);

  tk->crossover( data, c2, p1, p2, n_dat, t, min_value, max_value );
}


// =======================================================================================
  /** @brief Mutation.
   *  @param[in] src    pointer to original Encoding.
   *  @param[in] perc   percentage of elements that get mutated.
   *  @param[in] scale  scale of the noise (see {@link Encoding.N_SIGMA_SCALE})
   *  @return number of elements mutated.
   *
   *  @note The go/no-go decision was made higher up. At this point we are going
   *        to perform Mutation.
   */
// ---------------------------------------------------------------------------------------
void RealEncoding::mutate( Encoding* src, const real8_t perc, const real8_t scale ) {
  // -------------------------------------------------------------------------------------
  const real8_t sigma = (max_value - min_value) * scale / N_SIGMA_SCALE;
  real8_t* p = dynamic_cast<RealEncoding*>(src)->get_data();

  tk->mutate( data, n_dat, sigma, perc, min_value, max_value, p );
}


}; // end namespace evo


// =======================================================================================
// **                         E V O : : R E A L E N C O D I N G                         **
// =========================================================================== END FILE ==
