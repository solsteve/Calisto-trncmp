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
    
  Layer  ( void );
  Layer  ( const int32_t n_in, const int32_t n_out );
  Layer  ( std::ifstream& inf );

  ~Layer ( void );

  void     setTransfer ( std::string str );
  void     setTransfer ( transfer_e  ttype = SIGMOID );

  void     resize      ( const int32_t n_in, const int32_t n_out );
  void     destroy     ( void );
  
  bool     read        ( std::ifstream& inf );
  bool     write       ( std::ofstream& outf, std::string sfmt = "%23.16e" );

  void     debug       ( int32_t i );
  void     randomize   ( Dice* dd = static_cast<Dice*>(0) );

  void     reset       ( void );
  real8_t* forward     ( real8_t* input );
  void     backward    ( real8_t* input, real8_t* delta = static_cast<real8_t*>(0) );
  void     update      ( const real8_t eta );
    
}; // end class nns::Layer

}; // end namespace nns


#endif 


// =======================================================================================
// **                                N N S : : L A Y E R                                **
// ======================================================================== END FILE =====
