// ====================================================================== BEGIN FILE =====
// **                             N N S : : T R A N S F E R                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2019, Stephen W. Soliday                                      **
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
/** @brief  Tarnsfer Functions.
 *  @file   nns/Transfer.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-12.
 *
 *  Provides the interface for basic transfer functions.
 */
// =======================================================================================

#ifndef __HH_NNS_TRANSFER_TRNCMP
#define __HH_NNS_TRANSFER_TRNCMP

#include <trncmp.hh>

namespace nns {

typedef enum { SIGMOID=0, RELU=1, TANH=2, GAUSSIAN=3 } transfer_e;

// =======================================================================================
class Transfer {                                                          // nns::Transfer
  // -------------------------------------------------------------------------------------
 protected:
  std::string _name;
  
 public:
  Transfer( void ) : _name() {};
  virtual ~Transfer( void ) {};
  
  virtual real8_t     activate  ( const real8_t z ) const = 0;
  virtual real8_t     gradient  ( const real8_t a, const real8_t z ) const = 0;

  std::string name( void ) const { return _name; };
  
  static  Transfer* createPtr ( std::string str   );
  static  Transfer* createPtr ( transfer_e  ttype );
  
}; // end class nns::Transfer

// =======================================================================================
class Sigmoid : public Transfer {                                          // nns::Sigmoid
  // -------------------------------------------------------------------------------------
 public:
  Sigmoid( void ) { _name = "Sigmoid"; };
  virtual ~Sigmoid( void ) {};
  virtual real8_t activate  ( const real8_t z ) const;
  virtual real8_t gradient  ( const real8_t a, const real8_t z ) const;
}; // end class nns::Transfer


// =======================================================================================
class TanH : public Transfer {                                                // nns::TanH
  // -------------------------------------------------------------------------------------
 public:
  TanH( void ) { _name = "TanH"; };
  virtual ~TanH( void ) {};
  virtual real8_t activate  ( const real8_t z ) const;
  virtual real8_t gradient  ( const real8_t a, const real8_t z ) const;
}; // end class nns::Transfer


// =======================================================================================
class ReLU : public Transfer {                                                // nns::ReLU
  // -------------------------------------------------------------------------------------
 public:
  ReLU( void ) { _name = "ReLU"; };
  virtual ~ReLU( void ) {};
  virtual real8_t activate  ( const real8_t z ) const;
  virtual real8_t gradient  ( const real8_t a, const real8_t z ) const;
}; // end class nns::Transfer


// =======================================================================================
class Gaussian : public Transfer {                                        // nns::Gaussian
  // -------------------------------------------------------------------------------------
 public:
  Gaussian( void ) { _name = "Gaussian"; };
  virtual ~Gaussian( void ) {};
  virtual real8_t activate  ( const real8_t z ) const;
  virtual real8_t gradient  ( const real8_t a, const real8_t z ) const;
}; // end class nns::Transfer


// =======================================================================================
/** @brief Activate.
 *  @param[in] z linear input.
 *  @return non-linear activation of z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Sigmoid::activate( const real8_t z ) const {
  // -------------------------------------------------------------------------------------
  return D_ONE / (D_ONE + exp(-z));
}


// =======================================================================================
/** @brief Gradient.
 *  @param[in] a non-linear activation of z.
 *  @param[in] z linear input.
 *  @return derivative of the activation.
 *
 *  Compute the derivative of the activation function at z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Sigmoid::gradient( const real8_t a, const real8_t ) const {
  // -------------------------------------------------------------------------------------
  return a*(D_ONE - a);  
}


// =======================================================================================
/** @brief Activate.
 *  @param[in] z linear input.
 *  @return non-linear activation of z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t ReLU::activate( const real8_t z ) const {
  // -------------------------------------------------------------------------------------
  return (z>D_ZERO) ? (z) : (D_ZERO);
}


// =======================================================================================
/** @brief Gradient.
 *  @param[in] a non-linear activation of z.
 *  @param[in] z linear input.
 *  @return derivative of the activation.
 *
 *  Compute the derivative of the activation function at z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t ReLU::gradient( const real8_t, const real8_t z ) const {
  // -------------------------------------------------------------------------------------
  const real8_t E = exp( 12.0 * z );
  return E / (D_ONE + E);
}


// =======================================================================================
/** @brief Activate.
 *  @param[in] z linear input.
 *  @return non-linear activation of z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t TanH::activate( const real8_t z ) const {
  // -------------------------------------------------------------------------------------
  const real8_t E = exp(D_TWO * z );
  return (E-D_ONE) / (E+D_ONE);
}


// =======================================================================================
/** @brief Gradient.
 *  @param[in] a non-linear activation of z.
 *  @param[in] z linear input.
 *  @return derivative of the activation.
 *
 *  Compute the derivative of the activation function at z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t TanH::gradient( const real8_t a, const real8_t ) const {
  // -------------------------------------------------------------------------------------
  return D_ONE - (a*a);  
}


// =======================================================================================
/** @brief Activate.
 *  @param[in] z linear input.
 *  @return non-linear activation of z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Gaussian::activate( const real8_t z ) const {
  // -------------------------------------------------------------------------------------
  return exp(-z*z);
}


// =======================================================================================
/** @brief Gradient.
 *  @param[in] a non-linear activation of z.
 *  @param[in] z linear input.
 *  @return derivative of the activation.
 *
 *  Compute the derivative of the activation function at z.
 */
// ---------------------------------------------------------------------------------------
inline  real8_t Gaussian::gradient( const real8_t a, const real8_t z ) const {
  // -------------------------------------------------------------------------------------
  return -D_TWO*z*a;
}


}; // end namespace nns


#endif 


// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
