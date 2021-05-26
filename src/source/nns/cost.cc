// ====================================================================== BEGIN FILE =====
// **                                 N N S : : C O S T                                 **
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
/** @brief  Neural Network Cost Functions.
 *  @file   cost.cc
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-18.
 *
 *  Provides the methods for various neural network cost functions.
 */
// =======================================================================================


#include <nns/cost.hh>


namespace nns {


// =======================================================================================
/** @brief Quadratic Cost.
 *  @param[in] target desired target vector.
 *  @param[in] output network output vector.
 *  @param[in] n      number of vector elements.
 *  @return mean squared error.
 *
 *  Quadratic cost function, also known as mean squared error.
 */
// --------------------------------------------------------------------------------------- 
real8_t quadratic( real8_t* target, real8_t* output, size_t n ) {
  // -------------------------------------------------------------------------------------
  real8_t mse = D_ZERO;
  for (size_t i=0; i<n; i++) {
    real8_t diff = output[i] - target[i];
    mse += (diff * diff);
  }

  return mse / ( D_TWO * static_cast<real8_t>(n) );
}


// =======================================================================================
/** @brief Gradient Quadratic Cost.
 *  @param[out] err    gradient of each element.
 *  @param[in]  target desired target vector.
 *  @param[in]  output network output vector.
 *  @param[in]  n      number of vector elements.
 *
 *  Gradient of the Quadratic cost function, also known as mean squared error.
 */
// --------------------------------------------------------------------------------------- 
void quadratic_grad( real8_t* err, real8_t* target, real8_t* output, size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    err[i] = output[i] - target[i];
  }
}




// =======================================================================================
/** @brief Cross-entropy Cost.
 *  @param[in] target desired target vector.
 *  @param[in] output network output vector.
 *  @param[in] n      number of vector elements.
 *  @return cross entropy.
 *
 *  Cross-entropy cost function.
 */
// --------------------------------------------------------------------------------------- 
real8_t cross_entropy( real8_t* target, real8_t* output, size_t n ) {
  // -------------------------------------------------------------------------------------
  real8_t mse = D_ZERO;
  for (size_t i=0; i<n; i++) {
    mse += (target[i]*log(output[i]) + (D_ONE-target[i])*log(D_ONE-output[i]));
  }

  return mse / static_cast<real8_t>(n);
}


// =======================================================================================
/** @brief Gradient Cross-entropy Cost.
 *  @param[out] err    gradient of each element.
 *  @param[in]  target desired target vector.
 *  @param[in]  output network output vector.
 *  @param[in]  n      number of vector elements.
 *
 *  Gradient of the Cross-entropy cost function.
 */
// --------------------------------------------------------------------------------------- 
void cross_entropy_grad( real8_t* err, real8_t* target, real8_t* output, size_t n ) {
  // -------------------------------------------------------------------------------------
  for (size_t i=0; i<n; i++) {
    err[i] = (output[i] - target[i]) / (output[i]*(D_ONE - output[i]));
  }
}




// =======================================================================================
/** @brief Get Cost Function
 *  @param[in] name name of the function.
 *  @return pointer to a cost function.
 *
 *  Retrieve a pointer to a cost function by name.
 */
// ---------------------------------------------------------------------------------------
cost_function_t getCostFunction( std::string name ) {
  // -------------------------------------------------------------------------------------
  if ( 'M' == name[0] ) { return quadratic; }
  if ( 'm' == name[0] ) { return quadratic; }
  if ( 'Q' == name[0] ) { return quadratic; }
  if ( 'q' == name[0] ) { return quadratic; }

  if ( 'C' == name[0] ) { return cross_entropy; }
  if ( 'c' == name[0] ) { return cross_entropy; }

  std::cerr << "No matching cost function for name = [" << name << "]\n";
  return static_cast<cost_function_t>(0);
}


// =======================================================================================
/** @brief Get Gradient Cost Function
 *  @param[in] name name of the function.
 *  @return pointer to a cost function's gradient.
 *
 *  Retrieve a pointer to a cost function's gradient by name.
 */
// ---------------------------------------------------------------------------------------
cost_function_gradient_t getCostFunctionGradient( std::string name ) {
  // -------------------------------------------------------------------------------------
  if ( 'M' == name[0] ) { return quadratic_grad; }
  if ( 'm' == name[0] ) { return quadratic_grad; }
  if ( 'Q' == name[0] ) { return quadratic_grad; }
  if ( 'q' == name[0] ) { return quadratic_grad; }

  if ( 'C' == name[0] ) { return cross_entropy_grad; }
  if ( 'c' == name[0] ) { return cross_entropy_grad; }

  std::cerr << "No matching cost function gradient for name = [" << name << "]\n";
  return static_cast<cost_function_gradient_t>(0);
}


}; // end namespace nns


// =======================================================================================
// **                                 N N S : : C O S T                                 **
// ======================================================================== END FILE =====
