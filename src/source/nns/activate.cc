// ====================================================================== BEGIN FILE =====
// **                             N N S : : A C T I V A T E                             **
// =======================================================================================
// **                                                                                   **
// **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
// **                                                                                   **
// **  Copyright (c) 2011-2020, Stephen W. Soliday                                      **
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
/** @brief  Neural Network Activation Functions.
 *  @file   activate.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-18.
 *
 *  Provides the methods for various neural network activation functions.
 */
// =======================================================================================


#include <nns/activate.hh>


namespace nns {


// =======================================================================================
/** @brief Linear Activation.
 *  @param[out] a activated vector.
 *  @param[in]  z input vector.g
 *  @param[in]  n number of vector elements.
 *
 *  Activation.
 */
// --------------------------------------------------------------------------------------- 
void linear( real8_t* a, real8_t* z, const size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    a[i] = z[i];
  }
}


// =======================================================================================
/** @brief Gradient of Linear Activation.
 *  @param[out] d derivative activated vector.
 *  @param[in]  a activated vector.
 *  @param[in]  z input vector.
 *  @param[in]  n number of vector elements.
 *
 *  Gradient of the Activation.
 */
// --------------------------------------------------------------------------------------- 
void linear_gradient( real8_t* d, real8_t*, real8_t*, const size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    d[i] = D_ONE;
  }
}




// =======================================================================================
/** @brief Sigmoidal Activation.
 *  @param[out] a activated vector.
 *  @param[in]  z input vector.
 *  @param[in]  n number of vector elements.
 *
 *  Activation.
 */
// --------------------------------------------------------------------------------------- 
void sigmoid( real8_t* a, real8_t* z, const size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    a[i] = D_ONE / ( D_ONE + exp(-z[i]) );
  }
}


// =======================================================================================
/** @brief Gradient of Sigmoidal Activation.
 *  @param[out] d derivative activated vector.
 *  @param[in]  a activated vector.
 *  @param[in]  z input vector.
 *  @param[in]  n number of vector elements.
 *
 *  Gradient of the Activation.
 */
// --------------------------------------------------------------------------------------- 
void sigmoid_gradient( real8_t* d, real8_t* a, real8_t*, const size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    d[i] = a[i] * ( D_ONE - a[i] );
  }
}




// =======================================================================================
/** @brief Hyperbolic Tangent Activation.
 *  @param[out] a activated vector.
 *  @param[in]  z input vector.
 *  @param[in]  n number of vector elements.
 *
 *  Activation.
 */
// --------------------------------------------------------------------------------------- 
void hypertan( real8_t* a, real8_t* z, const size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    a[i] = tanh( z[i] );
  }
}


// =======================================================================================
/** @brief Gradient of Hyperbolic Tangent Activation.
 *  @param[out] d derivative activated vector.
 *  @param[in]  a activated vector.
 *  @param[in]  z input vector.
 *  @param[in]  n number of vector elements.
 *
 *  Gradient of the Activation.
 */
// --------------------------------------------------------------------------------------- 
void hypertan_gradient( real8_t* d, real8_t* a, real8_t*, const size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    d[i] = D_ONE - (a[i]*a[i]);
  }
}








// =======================================================================================
/** @brief Get Activation Function
 *  @param[in] name name of the function.
 *  @return pointer to an activation function.
 *
 *  Retrieve a pointer to an activation function by name.
 */
// ---------------------------------------------------------------------------------------
activate_t getActivation( std::string name ) {
  // -------------------------------------------------------------------------------------
  if ( 'L' == name[0] ) { return linear; }
  if ( 'l' == name[0] ) { return linear; }
  if ( 'S' == name[0] ) { return sigmoid; }
  if ( 's' == name[0] ) { return sigmoid; }
  if ( 'T' == name[0] ) { return hypertan; }
  if ( 't' == name[0] ) { return hypertan; }

  std::cerr << "No matching activation function for name = [" << name << "]\n";
  return static_cast<activate_t>(0);
}


// =======================================================================================
/** @brief Get Gradient Activation Function
 *  @param[in] name name of the function.
 *  @return pointer to an activation function's gradient.
 *
 *  Retrieve a pointer to an activation function's gradient by name.
 */
// ---------------------------------------------------------------------------------------
activate_gradient_t getActivationGradient( std::string name ) {
  // -------------------------------------------------------------------------------------
  if ( 'L' == name[0] ) { return linear_gradient;   }
  if ( 'l' == name[0] ) { return linear_gradient;   }
  if ( 'S' == name[0] ) { return sigmoid_gradient;  }
  if ( 's' == name[0] ) { return sigmoid_gradient;  }
  if ( 'T' == name[0] ) { return hypertan_gradient; }
  if ( 't' == name[0] ) { return hypertan_gradient; }

  std::cerr << "No matching activation function gradient for name = [" << name << "]\n";
  return static_cast<activate_gradient_t>(0);
}


}; // end namespace nns


// =======================================================================================
// **                             N N S : : A C T I V A T E                             **
// ======================================================================== END FILE =====
