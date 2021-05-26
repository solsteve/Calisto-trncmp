// ====================================================================== BEGIN FILE =====
// **                                N N S : : L A Y E R                                **
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
/** @brief  Feed Forward Neural Network Layers.
 *  @file   layer.hh
 *  @author Stephen W. Soliday
 *  @date   2020-Jul-18.
 *
 *  Provides the interface for a vector implementation of a BLAS enabled
 *  back-propagation neural network layer.
 */
// =======================================================================================


#ifndef __HH_NNS_LAYER_TRNCMP
#define __HH_NNS_LAYER_TRNCMP

#include <nns/activate.hh>

namespace nns {

// =======================================================================================
class Layer {                                                                // nns::Layer
  // -------------------------------------------------------------------------------------
 protected:
  size_t    num_con;
  size_t    num_nod;
  size_t    num_bat;
  real8_t** W;  ///< Weights           (   con, node )
  real8_t*  b;  ///< Bias              (     1, node )
  real8_t** dW; ///< Delta Weights     (   con, node )
  real8_t*  db; ///< Delta Bias        (     1, node )
  real8_t** Z;  ///< Input Summation   ( batch, node )
  real8_t** a;  ///< Activation        ( batch, node )
  real8_t** d;  ///< derivative error  ( batch,  con )
  real8_t** E;  ///< error matrix      ( batch, node )

  std::string              act_name;  ///< Activation Name @todo make part of Activate class
  nns::activate_t          G;         ///< Activation function
  nns::activate_gradient_t Gp;        ///< Activation function gradient

  Layer             ( void );
  void destroy      ( void );
  void resize       ( size_t n_con, size_t n_nod, size_t mx_bat );
  void set_activate ( std::string name );
  
  // -------------------------------------------------------------------------------------
 public:
  // =====================================================================================
  class Builder {                                                   // nns::Layer::Builder
    // -----------------------------------------------------------------------------------
   protected:
    size_t      num_con;         ///< number of connections to the previous layer
    size_t      num_nod;         ///< number of nodes in this layer
    size_t      max_batch;       ///< maximum batch size
    std::string act_name;        ///< name for the activation function
     
    // -----------------------------------------------------------------------------------
   public:
    Builder  ( void );
    ~Builder ( void );

    Builder& IO       ( size_t n_con, size_t n_nod );
    Builder& activate ( std::string name );
    Builder& batch    ( size_t mxb );
    Layer*   build    ( std::ifstream& inf );
    Layer*   build    ( void );
  }; // end class Layer::Builder

  // -------------------------------------------------------------------------------------
 public:

  ~Layer( void );
  
  void      reset      ( void );
  void      initialize ( bool debug=false );
  void      forward    ( real8_t** input,                     size_t bs );
  void      backward   ( real8_t** previous, real8_t** delta, size_t bs );
  void      update     ( real8_t   alpha );
  real8_t** output     ( void );

  real8_t*  store      ( real8_t *dst );
  real8_t*  load       ( real8_t *src );
  size_t    size       ( int axis=-1 );
  
  void      set_max_batch_size ( const size_t bs );

  void      read       ( std::ifstream& inf );
  void      write      ( std::ofstream& outf, std::string fmt="%17.10e" );
  
}; // end class Layer





// =======================================================================================
/** @brief Input/output
 *  @param[in] n_con number of connections to the previous layer.
 *  @param[in] n_nod number of nodes in this layer.
 *  @return reference to this Builder.
 *
 *  Set the input/output shape.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::IO( size_t n_con, size_t n_nod ) {
  // -------------------------------------------------------------------------------------
  num_con = n_con;
  num_nod = n_nod;
  return *this;
}


// =======================================================================================
/** @brief Assign an activation function.
 *  @param[in] name name for the activation function. @See nns::activate.
 *  @return reference to this Builder.
 *
 *  Assign the activation function using a name.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::activate( std::string name ) {
  // -------------------------------------------------------------------------------------
  act_name = name;
  return *this;
}


// =======================================================================================
/** @brief Set Maximum Batch Size.
 *  @param[in] mxb maximum batch size.
 *  @return reference to this Builder.
 *
 *  Set the maximum batch size. This will preallocate work space.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::batch( size_t mxb ) {
  // -------------------------------------------------------------------------------------
  max_batch = mxb;
  return *this;
}


// =======================================================================================
/** @brief Size of things
 *  @param[in] axis axis to querry.
 *  @return 0=number of connections, 1=number of nodes, 2=maximum batch size,
 *          default=weight/bias buffer size in elements of double.
 *
 *  Querry various sizes.
 */
// ---------------------------------------------------------------------------------------
inline size_t Layer::size( int axis ) {
  // -------------------------------------------------------------------------------------
  if ( 0 == axis ) { return num_con; }
  if ( 1 == axis ) { return num_nod; }
  if ( 2 == axis ) { return num_bat; }

  return ( num_con + 1 ) * num_nod;
}


// =======================================================================================
/** @brief Output
 *  @return pointer to the activation array.
 *  
 *  Return a pointer to the output activation array for this Layer.
 */
// ---------------------------------------------------------------------------------------
inline real8_t** Layer::output( void ) {
  // -------------------------------------------------------------------------------------
  return a;
}


}; // end namespace nns


#endif

// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
