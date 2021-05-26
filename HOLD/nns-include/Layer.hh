// ====================================================================== BEGIN FILE =====
// **                                N N S : : L A Y E R                                **
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
/** @brief  Neural Network Layer.
 *  @file   Layer.hh
 *  @author Stephen W. Soliday
 *  @date   2019-Sep-12.
 *
 *  Provides the interface for a neural network layer.
 */
// =======================================================================================

#ifndef __HH_NNS_LAYER_TRNCMP
#define __HH_NNS_LAYER_TRNCMP

#include <Dice.hh>
#include <TLogger.hh>
#include <nns/Transfer.hh>

namespace nns {

// =======================================================================================
class Layer {                                                                // nns::Layer
  // -------------------------------------------------------------------------------------
 protected:
  TLOGGER_HEADER( logger );
  EMPTY_PROTOTYPE( Layer );

  Layer( const int32_t n_in, const int32_t n_out, const bool is_first );

  void resize  ( const int32_t n_in, const int32_t n_out );
  void destroy ( void );

 public:
  
  // =====================================================================================
  class Builder {                                                   // nns::Layer::Builder
    // -----------------------------------------------------------------------------------
   private:
    size_t      num_con;  ///< Number of previous connections.
    size_t      num_nod;  ///< Number of nodes in the layer.
    transfer_e  act_func; ///< Activation function by enum.
    std::string act_name; ///< Activation function by name.
    bool        use_enum; ///< use the enum to associate an activation function,
    bool        is_first; ///< Flag to indicate the input layer.
    bool        do_init;  ///< Flag to indicate the input layer.
    
   public:
    Builder  ( size_t n_con, size_t n_nod );
    ~Builder ( void );
    
    Builder& activate   ( transfer_e act );
    Builder& activate   ( std::string act );
    Builder& first      ( void );
    Builder& initialize ( bool init=true );
    Layer*   build      ( void );
  }; // end class Layer::Builder


 public:
  int32_t   nIn;   ///< number of inputs/connections
  int32_t   nOut;  ///< number of outputs/nodes
  int32_t   nBuf;
  real8_t*  W_buffer;  
  real8_t*  dW_buffer;
    
  real8_t** W;  ///< Weights           ( [out][in] ) Each column is the weights of one node
  real8_t*  b;  ///< Bias              ( [out] )
  real8_t** dW; ///< Delta Weights     ( [out][in] )
  real8_t*  db; ///< Delta Bias        ( [out] )
  real8_t*  z;  ///< Weighted Sum      ( [out] )
  real8_t*  a;  ///< Non-linear output ( [out] )

  real8_t*  E;
  real8_t*  d;

  Transfer* trans; ///< pointer to an transfer function.
    
  ~Layer ( void );

  void     setTransfer ( std::string str );
  void     setTransfer ( transfer_e  ttype );

  void     randomize   ( void );

  void     reset       ( void );
  real8_t* forward     ( real8_t* input );
  void     backward    ( real8_t* input, real8_t* delta = static_cast<real8_t*>(0) );
  void     update      ( const real8_t eta );

  void     summary     ( std::ostream& os = std::cout );

  void     debug       ( int32_t i );
  
  void    
    
}; // end class nns::Layer




// =======================================================================================
/** @brief Builder for Layers.
 *  @param[in] n_con Number of connections to a previous Layer (input)
 *  @param[in] n_nod Number of nodes in this Layer (output)
 *  @return instance of a Layer builder
 *
 *  Create an instance of a layer builder.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder::Builder( size_t n_con, size_t n_nod ) {
  // -------------------------------------------------------------------------------------
  num_con  = n_con;
  num_nod  = n_nod;
  act_enum = SIGMOID;
  act_name = "sigmoid";
  use_enum = true;
  is_first = false;
  do_init  = false;
}
      
// =======================================================================================
/** @brief Destructor procedure.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder::~Builder( void ) {
  // -------------------------------------------------------------------------------------
}

// =======================================================================================
/** @brief assign an activation function.
 *  @param[in] act enumeration for the activation function. @See nns::Transfer.
 *  @return reference to this Builder. Used for chaining.
 *
 *  Assign the activation function using enumeration.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::activate( transfer_e act ) {
  // -------------------------------------------------------------------------------------
  act_func = act;
  use_enum = true;
  return *this;
}
      
// =======================================================================================
/** @brief assign an activation function.
 *  @param[in] act name for the activation function. @See nns::Transfer.
 *  @return reference to this Builder. Used for chaining.
 *
 *  Assign the activation function using a name.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::activate( std::string act ) {
  // -------------------------------------------------------------------------------------
  act_name = act;
  use_enum = false;
  return *this;
}
      
// =======================================================================================
/** @brief Is this the first Layer?
 *  @return reference to this Builder. Used for chaining.
 *
 *  The first layer does not compute a sifference error for a previous layer.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::first( void ) {
  // -------------------------------------------------------------------------------------
  is_first = true;
  return *this;
}

// =======================================================================================
/** @brief Set initialization.
 *  @return reference to this Builder. Used for chaining.
 *
 *  If this is used then the Layer will be initialized.
 */
// ---------------------------------------------------------------------------------------
inline Layer::Builder& Layer::Builder::initialize( bool init ) {
  // -------------------------------------------------------------------------------------
  do_init = init;
  return *this;
}
    
}; // end namespace nns


#endif 


// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
